// #define SEM_KEY
// #define MSG_KEY

void sys_init()
{
  // OS Abstraction layer initialization code goes here
}

sys_sem_t sys_sem_new(u8_t count)
{
  // Create a semaphore and set its initial value = count

#if defined(LWIP_UNIX)
  sys_sem_t sem = semget(LWIP_SEM_KEY,1,0666|IPC_CREAT);
  if(sem == -1){
    log_error("semget",errno);
    return NULL;
  }
     
  if(semctl(sem ,0,SETVAL,count) == -1){
    log_error("semctl: ",errno);
    return NULL;
  }

  return sem;

#elif defined(LWIP_WIN)
  sys_sem_t sem = CreateSemaphore(NULL,count,SEM_MAX_CNT,NULL);
  if(sem == NULL){
    log_error("CreateSemaphore: %d",GetLastError());
  return sem;
#endif

}

void sys_sem_free(sys_sem_t sem)
{
  // Deallocate a semaphore
#if defined(LWIP_UNIX)
  if(semctl(sem,0,IPC_RMID,0) == -1)
    log_error("semctl: ",errno);
#elif defined(LWIP_WIN)
  if(CloseHandle(sem) == 0)
    log_error("CloseHandle: %d",GetLastError());
#endif
  return;
}

void sys_sem_signal(sys_sem_t sem)
{
  // Signal a semaphore
#if defined(LWIP_UNIX)
  struct sembuf operation[1];
  operation[0].sem_op = 1;
  operation[0].sem_num = 0;
  operation[0].sem_flg = 0;
  
  if(semop(sem,operation,1) == -1)
    log_error("semop",errno);
#elif defined(LWIP_WIN)
  if(ReleaseSemaphore(sem,1,NULL) == 0)
    log_error("ReleaseSemaphore",GetLastError());
#endif
}

u32_t sys_arch_sem_wait(sys_sem_t sem, u32_t timeout)
{
  // Block the thread waiting for a semaphore to be signalled within 'timeout' milliseconds.
  u32_t retval;
#if defined(LWIP_UNIX)
  struct timespec to,start,stop;
  to.tv_sec = timeout/1000;
  to.tv_nsec = (timeout%1000)*1000*1000;
  clock_gettime(CLOCK_MONOTONIC,&start);
  retval = timeout == 0 ? sem_wait(sem) : sem_timedwait(sem,&to);
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
  retval = WaitForSingleObject(sem,timeout == 0 ? INFINITE : timeout);
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

sys_mbox_t sys_mbox_new(int size)
{
  // Create a message box that can hold size messages.
#if defined(LWIP_UNIX)
  sys_mbox_t mbox = msgget(MSG_KEY, 0666|IPC_CREAT);
  if(mbox == -1){
    log_error("msgget",errno);
    return NULL;
  }
  return mbox;
#elif defined(LWIP_WINDOWS)
  sys_mbox_t mbox = CreateMailslot(MSG_KEY, MAX_MAIL_SIZE,0,NULL);
  if(mbox == INVALID_HANDLE_VALUE){
    log_error("CreateMailslot",GetLastError());
    return NULL;
  }
#endif
}

void sys_mbox_free(sys_mbox_t mbox)
{
  // Free the message box
#if defined(LWIP_UNIX)
  if(msgctl(mbox,IPC_RMID,(struct msgqid_ds*) NULL) == -1)
    perror("msgctl");
#elif defined(LWIP_WIN)
  if(CloseHandle(sem) == 0)
    log_error("CloseHandle: %d",GetLastError());
#endif

  return;
}

void sys_mbox_post(sys_mbox_t mbox, void* msg)
{
  // Post 'msg' in the mailbox
#if defined(LWIP_UNIX)
  if(msgsnd(mbox,msg,sizeof(struct tcpip_msg),0) == -1)
    log_error("msgsnd",errno);    
#elif defined(LWIP_WIN)
  unsigned long written;
  if(WriteFile(mbox,(char*)msg,sizeof(struct tcpip_msg),&written,0) == 0)
    log_error("WriteFile",GetLastError());
#endif

return;
}

u32_t sys_arch_mbox_fetch(sys_mbox_t mbox, void** msg, u32_t timeout)
{
  // Fetch a 'msg' from mailbox
  char* buf = (char *) safe_malloc(MAX_MAIL_SIZE+sizeof(long));
  u32_t nbytes=0;
  u32_t time = timeout;

  /* If timeout is 0, wait indefinitely */
  if(timeout == 0){
#if defined(LWIP_UNIX)
    nbytes = msgrcv(mbox,buf,MAX_MAIL_SIZE,0);
    if(nbytes == -1){
      perror("msgrcv");
#elif defined(LWIP_WIN)
    if(SetMailslotInfo(mbox,MAILSLOT_WAIT_FOREVER) == 0)
      log_error("SetMailslotInfo",GetLastError());
    if(ReadFile(mbox,buf,MAX_MAIL_SIZE,&nbytes,0) == 0){
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
      nbytes = msgrcv(mbox,buf,MAX_MAIL_SIZE,IPC_NOWAIT);
      if(nbytes == -1 && errno == ENOMSG){
#elif defined(LWIP_WIN)
      if(SetMailslotInfo(mbox,0) == 0)
        log_error("SetMailslotInfo",GetLastError());
      if(ReadFile(mbox,buf,MAX_MAIL_SIZE,&nbytes,0) == 0)
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
u32_t sys_mbox_tryfetch(sys_mbox_t mbox, void **msg)
{
  char* buf = safe_malloc(MAX_MAIL_SIZE+sizeof(long));
  u32_t nbytes;

#if defined(LWIP_UNIX)
  nbytes = msgrcv(mbox,buf,MAX_MAIL_SIZE,IPC_NOWAIT);
  if(nbytes == -1){
    if(errno == ENOMSG)
      return SYS_MBOX_EMPTY;
    else
      return -1;
#elif defined(LWIP_WIN)
  if(SetMailslotInfo(mbox,0) == 0){
    log_error("SetMailslotInfo",GetLastError());
    return -1;
  }
  if(ReadFile(mbox,buf+sizeof(long),MAX_MAIL_SIZE,&nbytes,0) == 0){
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
#endif
}
