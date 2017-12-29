/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                      MULTIPLE OBJECTS MANAGEMENT
*
*
* File : OS_MULTI.C
* By   : Nicolas Pinault
*********************************************************************************************************
*/

#ifndef  OS_MASTER_FILE
#include "includes.h"
#endif

#if OS_MULTI_EN > 0

/*
*********************************************************************************************************
*                                           PEND ON MULTI
*
* Description: This function waits on multiple events (semaphores, mailboxes and/or queues)
*
* Arguments  : ppevent_multi  is a pointer to a table of events control block (NULL terminated) 
*
*              n_events      Is a pointer to the size of the event table
                             Contains the number of the event wich has readied the task (0 based counter)
*
*              timeout       is an optional timeout period (in clock ticks).  If non-zero, your task will
*                            wait for the resource up to the amount of time specified by this argument.
*                            If you specify 0, however, your task will wait forever at the specified
*                            semaphore or, until the resource becomes available (or the event occurs).
*
*              perr          is a pointer to where an error message will be deposited.  Possible error
*                            messages are:
*
*                            OS_NO_ERR           The call was successful and your task owns the resource
*                                                or, the event you are waiting for occurred.
*                            OS_TIMEOUT          The semaphore was not received within the specified
*                                                timeout.
*                            OS_ERR_EVENT_TYPE   If the last pointer of the table is not NULL.
*                                                If one element of the table does not point to a semaphore, 
*                                                queue or mailbox.
*                            OS_ERR_PEND_ISR     If you called this function from an ISR and the result
*                                                would lead to a suspension.
*                            OS_ERR_PEVENT_NULL  If 'ppevent_multi' or 'n_events' is a NULL pointer.
*                            OS_ERR_INVALID_OPT  *n_events = 0
*
* Returns    : the message of a mailbox or queue
*********************************************************************************************************
*/

void *OSMultiPend (OS_EVENT **ppevent_multi, INT8U *n_events, INT16U timeout, INT8U *perr)
{
#if OS_CRITICAL_METHOD == 3                           /* Allocate storage for CPU status register      */
    OS_CPU_SR  cpu_sr;
#endif    
    OS_EVENT   event;
    OS_EVENT  *pevent;
    INT8U      i;
    void      *pmsg;
    OS_Q      *pq;

    

    if (OSIntNesting > 0) {                           /* See if called from ISR ...                    */
        *perr = OS_ERR_PEND_ISR;                      /* ... can't PEND from an ISR                    */
        return ((void *)0);
    }

    if (ppevent_multi == (OS_EVENT **)0) {
        *perr = OS_ERR_PEVENT_NULL;
        return ((void *)0);
    }
    
    if (n_events == (INT8U *)0) {
        *perr = OS_ERR_PEVENT_NULL;
        return ((void *)0);
    }
    
    if (*n_events == 0) {
        *perr = OS_ERR_INVALID_OPT;
        return ((void *)0);
    }
    
    if (ppevent_multi[*n_events] != (OS_EVENT *)0) {               
        *perr = OS_ERR_EVENT_TYPE;
        return ((void *)0);
    }     

    event.OSEventType = OS_EVENT_TYPE_MULTI;
    event.OSEventPtr  = ppevent_multi;

    pevent = ppevent_multi[0];
    for (i = 0; i < *n_events; i++) {
        if (pevent == (OS_EVENT *)0) {                        /* Validate 'pevent'                                  */
            *perr = OS_ERR_PEVENT_NULL;
            return ((void *)0);
        }
        
        if ((pevent->OSEventType != OS_EVENT_TYPE_SEM)  &&
            (pevent->OSEventType != OS_EVENT_TYPE_MBOX) &&
            (pevent->OSEventType != OS_EVENT_TYPE_Q)) {
            *perr = OS_ERR_EVENT_TYPE;
            return ((void *)0);
        }
        pevent++;
    }

    OS_ENTER_CRITICAL();
    pevent = ppevent_multi[0];
    for (i = 0; i < *n_events; i++) {

        switch (pevent->OSEventType) {
            case OS_EVENT_TYPE_SEM:
                 if (pevent->OSEventCnt > 0) {                /* If sem. is positive, resource available ...        */
                     pevent->OSEventCnt--;                    /* ... decrement semaphore only if positive.          */
                     OS_EXIT_CRITICAL();
                     *n_events = i;
                     *perr = OS_NO_ERR;
                     return ((void *)0);
                 }
                 break;
            
            case OS_EVENT_TYPE_MBOX:
                 pmsg = pevent->OSEventPtr;
                 if (pmsg != (void *)0) {                     /* See if there is already a message                  */
                     pevent->OSEventPtr = (void *)0;          /* Clear the mailbox                                  */
                     OS_EXIT_CRITICAL();
                     *n_events = i;
                     *perr     = OS_NO_ERR;
                     return (pmsg);                           /* Return the message received (or NULL)              */
                 }
                 break;
            
            case OS_EVENT_TYPE_Q:
                 pq = (OS_Q *)pevent->OSEventPtr;             /* Point at queue control block                       */
                 if (pq->OSQEntries > 0) {                    /* See if any messages in the queue                   */
                     pmsg = *pq->OSQOut++;                    /* Yes, extract oldest message from the queue         */
                     pq->OSQEntries--;                        /* Update the number of entries in the queue          */
                     if (pq->OSQOut == pq->OSQEnd) {          /* Wrap OUT pointer if we are at the end of the queue */
                         pq->OSQOut = pq->OSQStart;
                     }
                     OS_EXIT_CRITICAL();
                     *n_events = i;
                     *perr     = OS_NO_ERR;
                     return (pmsg);                           /* Return message received                            */
                 }
                 break;
                    
            default:
                 *perr = OS_ERR_EVENT_TYPE; 
                 return ((void *)0);
                 break;
        }
        pevent++;
    }
    

    pevent = ppevent_multi[0];    
    for (i = 0; i < *n_events; i++) {
        pevent->OSEventTbl[OSTCBCur->OSTCBY] |= OSTCBCur->OSTCBBitX;          /* Put task in waiting list           */
        pevent->OSEventGrp                   |= OSTCBCur->OSTCBBitY;
        pevent++;
    }
    
    OSTCBCur->OSTCBEventNumberRdy = 0;                        /* No event has readied the task                      */
    OSTCBCur->OSTCBStat          |= OS_STAT_MULTI;
    OSTCBCur->OSTCBDly            = timeout;                  /* Load timeout into TCB                              */
    OS_EventTaskWait(&event);                                 /* Suspend task until event or timeout occurs         */
    OS_EXIT_CRITICAL();
    OS_Sched();                                               /* Find next highest priority task ready              */

    pmsg = (void *)0;
    OS_ENTER_CRITICAL();
    if (OSTCBCur->OSTCBStat & OS_STAT_MULTI) {                /* Must have timed out if still waiting for event     */
        for (i = 0; i < *n_events; i++) {
            pevent = ppevent_multi[i];
            OS_EventTO(pevent);
        }
        OS_EXIT_CRITICAL();
        *n_events = 0;
        *perr     = OS_TIMEOUT;                               /* Indicate that didn't get event within TO           */
        return ((void *)0);
    } else {
        *n_events  = OSTCBCur->OSTCBEventNumberRdy; 
        pevent     = ppevent_multi[*n_events];

        switch (pevent->OSEventType) {
            case OS_EVENT_TYPE_SEM:
                 pmsg = (void *)0;
                 break;
            
            case OS_EVENT_TYPE_MBOX:
            case OS_EVENT_TYPE_Q:
                 pmsg                = OSTCBCur->OSTCBMsg; /* Extract message from TCB (Put there by QPost or MPost)  */
                 OSTCBCur->OSTCBMsg  = (void *)0;          /* clear message received                                  */
                 /*OSTCBCur->OSTCBStat = OS_STAT_RDY;*/
                 break;
                    
            default :
                 break;
        }
    }
    OSTCBCur->OSTCBEventPtr = (OS_EVENT *)0;
    OS_EXIT_CRITICAL();
    *perr                   = OS_NO_ERR;
    
    return (pmsg);
}

#endif                                                     /* OS_MULTI_EN                                */
