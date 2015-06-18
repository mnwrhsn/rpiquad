#ifndef __RRM_SOS_OS_SEM_H_
#define __RRM_SOS_OS_SEM_H_

#include "os_config.h"

//TODO define event types

typedef struct __os_semaphore
{
    uint8 event_type;
    uint8 counter;
    uint8 prev_prio;		//owner's previous elev_prio.. to help cascade
    void *event;		//may be unused
    void *owner;		//current owner to be used for prio inversion
    //list_t wait_list;		//TODO replace with appropriate
}os_sema_t;

#endif //__RRM_SOS_OS_SEM_H_
