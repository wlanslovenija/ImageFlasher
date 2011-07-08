

#include "lwip/def.h"
#include "arch/sys_arch.h"
#include "lwip/sys.h"

#ifdef LWIP_UNIX
#include <errno.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <time.h>
#endif


#ifndef _CC
#include "arch/cc.h"
#endif

void sys_init()
{
  // OS Abstraction layer initialization code goes here
}

err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
  // Create a semaphore and set its initial value = count

#if defined(LWIP_UNIX)
  *sem = semget(LWIP_SEM_KEY,1,0666|IPC_CREAT);
  if(*sem == -1){
    log_error("semget",errno);
    *sem = (sys_sem_t *)NULL;
    return errno;
  }
     
  if(semctl(*sem ,0,SETVAL,count) == -1){
    log_error("semctl: ",errno);
    *sem = (sys_sem_t *)NULL;
    return errno;
  }

  return 0;

#elif defined(LWIP_WIN)
  *sem = CreateSemaphore(NULL,count,SEM_MAX_CNT,NULL);
  if(*sem == NULL){
    log_error("CreateSemaphore: %d",GetLastError());
    return GetLastError();
  }
  return 0;
#endif

}

void sys_sem_free(sys_sem_t *sem)
{
  // Deallocate a semaphore
#if defined(LWIP_UNIX)
  if(semctl(*sem,0,IPC_RMID,0) == -1)
    log_error("semctl: ",errno);
#elif defined(LWIP_WIN)
  if(CloseHandle(*sem) == 0)
    log_error("CloseHandle: %d",GetLastError());
#endif
  return;
}

void sys_sem_signal(sys_sem_t *sem)
{
  // Signal a semaphore
#if defined(LWIP_UNIX)
  struct sembuf operation[1];
  operation[0].sem_op = 1;
  operation[0].sem_num = 0;
  operation[0].sem_flg = 0;
  
  if(semop(*sem,operation,1) == -1)
    log_error("semop",errno);
#elif defined(LWIP_WIN)
  if(ReleaseSemaphore(*sem,1,NULL) == 0)
    log_error("ReleaseSemaphore",GetLastError());
#endif
}

u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
  // Block the thread waiting for a semaphore to be signalled within 'timeout' milliseconds.
  u32_t retval;
#if defined(LWIP_UNIX)
  struct timespec to,start,stop;
  to.tv_sec = timeout/1000;
  to.tv_nsec = (timeout%1000)*1000*1000;
  clock_gettime(CLOCK_MONOTONIC,&start);
  retval = timeout == 0 ? sem_wait(*sem) : sem_timedwait(*sem,&to);
  clock_gettime(CLOCK_MONOTONIC,&stop);
  
  if(retval == -1)
    if(errno == ETIMEDOUT)
      return SYS_ARCH_TIMEDOUT;
    else 
      log_error("sem_wait/sem_timedwait",errno);
  u32_t timegap = (stop.tv_sec*1000+stop.tv_nsec/1000)-(start.tv_sec*1000+start.tv_nsec/1000);
  return timegap;
#elif defined(LWIP_WIN)
  SYSTEMTIME start,stop;
  GetSystemTime(&start);
  retval = WaitForSingleObject(*sem,timeout == 0 ? INFINITE : timeout);
  GetSystemTime(&stop);

  if(retval == WAIT_OBJECT_0){
    //return calculated time
  }elseif(retval == WAIT_TIMEOUT){ 
    return SYS_ARCH_TIMEOUT;
  }else{
    log_error("WaitForSingleObject",GetLastError());
    return -1;
  }
#endif
}

err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
  // Create a message box that can hold size messages.
#if defined(LWIP_UNIX)
   *mbox = msgget(LWIP_MBOX_KEY, 0666|IPC_CREAT);
  if(*mbox == -1){
    log_error("msgget",errno);
    *mbox = (sys_mbox_t) NULL;
    return errno;
  }
  return 0;
#elif defined(LWIP_WINDOWS)
  *mbox = CreateMailslot(LWIP_MBOX_KEY, MAX_MAIL_SIZE,0,NULL);
  if(*mbox == INVALID_HANDLE_VALUE){
    log_error("CreateMailslot",GetLastError());
    *mbox = (sys_mbox_t *) NULL;
    return GetLastError();
  }
#endif
}

void sys_mbox_free(sys_mbox_t *mbox)
{
  // Free the message box
#if defined(LWIP_UNIX)
  if(msgctl(*mbox,IPC_RMID,(struct msgqid_ds*) NULL) == -1)
    perror("msgctl");
#elif defined(LWIP_WIN)
  if(CloseHandle(*mbox) == 0)
    log_error("CloseHandle: %d",GetLastError());
#endif

  return;
}

void sys_mbox_post(sys_mbox_t *mbox, void* msg)
{
  // Post 'msg' in the mailbox
#if defined(LWIP_UNIX)
  if(msgsnd(*mbox,msg,sizeof(msg),0) == -1)
    log_error("msgsnd",errno);    
#elif defined(LWIP_WIN)
  unsigned long written;
  if(WriteFile(*mbox,(char*)msg,sizeof(msg),&written,0) == 0)
    log_error("WriteFile",GetLastError());
#endif

return;
}

u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void** msg, u32_t timeout)
{
  // Fetch a 'msg' from mailbox
  char* buf = (char *) safe_malloc(sizeof(msg)+sizeof(long));
  u32_t nbytes=0;
  u32_t time = timeout;

  /* If timeout is 0, wait indefinitely */
  if(timeout == 0){
#if defined(LWIP_UNIX)
    nbytes = msgrcv(*mbox,buf,sizeof(msg),0,0);
    if(nbytes == -1){
      perror("msgrcv");
#elif defined(LWIP_WIN)
    if(SetMailslotInfo(*mbox,MAILSLOT_WAIT_FOREVER) == 0)
      log_error("SetMailslotInfo",GetLastError());
    if(ReadFile(*mbox,buf,sizeof(msg),&nbytes,0) == 0){
      log_error("ReadFile",GetLastError()); 
#endif
    }else{
      if(msg == NULL){
        return 0;
      }else{
        *msg = buf;
        return nbytes;
      }    
    }

  }else{
  /* Check repeatedly for the msg until timeout */
    while(timeout>=0){
#if defined(LWIP_UNIX)
      nbytes = msgrcv(*mbox,buf,sizeof(msg),0,IPC_NOWAIT);
      if(nbytes == -1 && errno == ENOMSG){
#elif defined(LWIP_WIN)
      if(SetMailslotInfo(mbox,0) == 0)
        log_error("SetMailslotInfo",GetLastError());
      if(ReadFile(mbox,buf,sizeof(msg),&nbytes,0) == 0)
        log_error("ReadFile",GetLastError());
#endif
        if(timeout>10){

#if defined(LWIP_UNIX)
          usleep(10000);
#elif defined(LWIP_WIN)
          Sleep(10);
#endif
          timeout -= 10;

        }else{
#if defined(LWIP_UNIX)
          usleep(timeout*1000);
#elif defined(LWIP_WIN)
          Sleep(timeout);
#endif
          timeout = -1;
        }

      }else{
  /* If msg argument is NULL, drop the packet */
        if(msg =! NULL){
          *msg = buf;
        return timeout == -1 ? time : time-timeout;
        }    
      }
    }
  }
}
u32_t sys_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
  char* buf = safe_malloc(sizeof(msg)+sizeof(long));
  u32_t nbytes;

#if defined(LWIP_UNIX)
  nbytes = msgrcv(*mbox,buf,sizeof(msg),0,IPC_NOWAIT);
  if(nbytes == -1){
    if(errno == ENOMSG)
      return SYS_MBOX_EMPTY;
    else
      return -1;
#elif defined(LWIP_WIN)
  if(SetMailslotInfo(*mbox,0) == 0){
    log_error("SetMailslotInfo",GetLastError());
    return -1;
  }
  if(ReadFile(*mbox,buf+sizeof(long),MAX_MAIL_SIZE,&nbytes,0) == 0){
    log_error("ReadFile",GetLastError());
    return -1;   
  }
  if(nbytes == 0)
    return SYS_MBOX_EMPTY;
#endif
  }else{
    if(msg != NULL)
  
    return 0;
  }
}

void log_error(char *function, u32_t err_code)
{
#if defined(LWIP_UNIX)
  fprintf(errlog,"%s : %s\n",function,strerror(err_code));
#elif defined(LWIP_WIN)
  fprintf(errlog,"%s : Error code (%d)\n",function,err_code);
#endif
}
