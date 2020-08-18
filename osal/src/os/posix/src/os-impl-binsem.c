/*
 *  NASA Docket No. GSC-18,370-1, and identified as "Operating System Abstraction Layer"
 *
 *  Copyright (c) 2019 United States Government as represented by
 *  the Administrator of the National Aeronautics and Space Administration.
 *  All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
 * \file     os-impl-binsem.c
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 * Purpose: This file contains some of the OS APIs abstraction layer
 *    implementation for POSIX
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-posix.h"
#include "os-shared-binsem.h"
#include "os-impl-binsem.h"

/*
 * This controls the maximum time the that the calling thread will wait to
 * acquire the condition mutex before returning an error.
 *
 * Under normal conditions, this lock is held by giving/taking threads very
 * briefly, so the lock should be available with minimal delay.  However,
 * if the "taking" thread is canceled or exits abnormally without releasing the
 * lock, it means any other task accessing the sem can get blocked indefinitely.
 *
 * There should be no reason for a user to configure this, as it should
 * not be relevant in a normally operating system.  This only prevents a
 * deadlock condition in off-nominal circumstances.
 */
#define  OS_POSIX_BINSEM_MAX_WAIT_SECONDS       2


/* Tables where the OS object information is stored */
OS_impl_binsem_internal_record_t    OS_impl_bin_sem_table       [OS_MAX_BIN_SEMAPHORES];

/*---------------------------------------------------------------------------------------
 * Helper function for acquiring the mutex when beginning a binary sem operation
 * This uses timedlock to avoid waiting forever, and is put into a wrapper function
 * to avoid pending forever.  The code should never pend on these for a long time.
 ----------------------------------------------------------------------------------------*/
int32 OS_Posix_BinSemAcquireMutex(pthread_mutex_t *mut)
{

    return OS_SUCCESS;
}

/*---------------------------------------------------------------------------------------
 * Helper function for releasing the mutex in case the thread
 * executing pthread_condwait() is canceled.
 ----------------------------------------------------------------------------------------*/
void OS_Posix_BinSemReleaseMutex(void *mut)
{

}

/****************************************************************************************
                               BINARY SEMAPHORE API
 ***************************************************************************************/

/*
 * Note that the pthreads world does not provide VxWorks-style binary semaphores that the OSAL API is modeled after.
 * Instead, semaphores are simulated using pthreads mutexes, condition variables, and a bit of internal state.
 *
 * IMPORTANT: the side effect of this is that Binary Semaphores are not usable from signal handlers / ISRs.
 * Use Counting Semaphores instead.
 */

/*---------------------------------------------------------------------------------------
   Name: OS_Posix_BinSemAPI_Impl_Init

   Purpose: Initialize the Binary Semaphore data structures

 ----------------------------------------------------------------------------------------*/
int32 OS_Posix_BinSemAPI_Impl_Init(void)
{
   return OS_SUCCESS;
} /* end OS_Posix_BinSemAPI_Impl_Init */


/*----------------------------------------------------------------
 *
 * Function: OS_BinSemCreate_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_BinSemCreate_Impl (uint32 sem_id, uint32 initial_value, uint32 options)
{
    int32 return_code;

    return return_code;

} /* end OS_BinSemCreate_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_BinSemDelete_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_BinSemDelete_Impl (uint32 sem_id)
{
    int32 return_code;

       /* sem could be busy, i.e. some task is pending on it already.
        * that means it cannot be deleted at this time. */

       /* Now that the CV is destroyed this sem is unusable,
        * so we must do our best to clean everything else.  Even if cleanup
        * does not fully work, returning anything other than OS_SUCCESS would
        * suggest to the caller that the sem is still usable which it is not.
        */
       return_code = OS_SUCCESS;

       /* destroy the associated mutex --
        * Note that this might fail if the mutex is locked,
        * but there is no sane way to recover from that (see above). */

    return return_code;
} /* end OS_BinSemDelete_Impl */



/*----------------------------------------------------------------
 *
 * Function: OS_BinSemGive_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_BinSemGive_Impl ( uint32 sem_id )
{


    /*
     * Note there is a possibility that another thread is concurrently taking this sem,
     * and has just checked the current_value but not yet inside the cond_wait call.
     *
     * To address this possibility - the lock must be taken here.  This is unfortunate
     * as it means there may be a task switch when _giving_ a binary semaphore.  But the
     * alternative of having a BinSemGive not wake up the other thread is a bigger issue.
     *
     * Counting sems do not suffer from this, as there is a native POSIX mechanism for those.
     *
     * Note: This lock should be readily available, with only minimal delay if any.
     * If a long delay occurs here, it means something is fundamentally wrong.
     */

    /* Lock the mutex ( not the table! ) */

    /* Binary semaphores are always set as "1" when given */

    /* unblock one thread that is waiting on this sem */


    return OS_SUCCESS;
} /* end OS_BinSemGive_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_BinSemFlush_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_BinSemFlush_Impl (uint32 sem_id)
{

    /* Lock the mutex ( not the table! ) */


    /* increment the flush counter.  Any other threads that are
     * currently pending in SemTake() will see the counter change and
     * return _without_ modifying the semaphore count.
     */

    /* unblock all threads that are be waiting on this sem */


    return OS_SUCCESS;
} /* end OS_BinSemFlush_Impl */

/*---------------------------------------------------------------------------------------
   Name: OS_GenericBinSemTake_Impl

   Purpose: Helper function that takes a simulated binary semaphore with a "timespec" timeout
            If the value is zero this will block until either the value
            becomes nonzero (via SemGive) or the semaphore gets flushed.

---------------------------------------------------------------------------------------*/
static int32 OS_GenericBinSemTake_Impl (OS_impl_binsem_internal_record_t *sem, const struct timespec *timeout)
{
   int32 return_code;

   /*
    * Note - this lock should be quickly available - should not delay here.
    * The main delay is in the pthread_cond_wait() below.
    */
   /* Lock the mutex ( not the table! ) */

   /* because pthread_cond_wait() is also a cancellation point,
    * this uses a cleanup handler to ensure that if canceled during this call,
    * the mutex is also released */

   return_code = OS_SUCCESS;

   /*
    * Note that for vxWorks compatibility, we need to stop pending on the semaphore
    * and return from this function under two possible circumstances:
    *
    *  a) the semaphore count was nonzero (may be pre-existing or due to a give)
    *     this is the normal case, we should decrement the count by 1 and return.
    *  b) the semaphore got "flushed"
    *     in this case ALL tasks are un-blocked and we do NOT decrement the count.
    */

   /*
    * first take a local snapshot of the flush request counter,
    * if it changes, we know that someone else called SemFlush.
    */

   /* Note - the condition must be checked in a while loop because
    * even if pthread_cond_wait() returns, it does NOT guarantee that
    * the condition we are looking for has been met.
    *
    * Also if the current_value is already nonzero we will not wait.
    */


   /* If the flush counter did not change, set the value to zero */


   /*
    * Pop the cleanup handler.
    * Passing "true" means it will be executed, which
    * handles releasing the mutex.
    */

   return return_code;
} /* end OS_GenericBinSemTake_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_BinSemTake_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_BinSemTake_Impl ( uint32 sem_id )
{
   return (OS_GenericBinSemTake_Impl (&OS_impl_bin_sem_table[sem_id], NULL));
} /* end OS_BinSemTake_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_BinSemTimedWait_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_BinSemTimedWait_Impl ( uint32 sem_id, uint32 msecs )
{
 int a; //had to add in for the return
   /*
    ** Compute an absolute time for the delay
    */
//   return (OS_GenericBinSemTake_Impl (&OS_impl_bin_sem_table[sem_id], &ts));
 return a;

} /* end OS_BinSemTimedWait_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_BinSemGetInfo_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_BinSemGetInfo_Impl (uint32 sem_id, OS_bin_sem_prop_t *sem_prop)
{
    /* put the info into the stucture */

    return OS_SUCCESS;
} /* end OS_BinSemGetInfo_Impl */

