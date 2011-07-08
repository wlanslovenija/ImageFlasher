#ifndef _SYS_ARCH
#define _SYS_ARCH

#include "arch/cc.h"

typedef s32_t sys_sem_t;
typedef s32_t sys_mbox_t;

#define MAX_MAIL_SIZE 100

#define LWIP_SEM_KEY 31337
#define LWIP_MBOX_KEY 31337

#define SYS_ARCH_TIMEDOUT
#define LWIP_UNIX

int errlog;


#endif /* _SYS_ARCH */
