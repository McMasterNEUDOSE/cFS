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
 * \file     os-impl-tasks.c
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-posix.h"
#include "bsp-impl.h"
#include <sched.h>

#include "os-impl-tasks.h"

#include "os-shared-task.h"
#include "os-shared-idmap.h"

/*
 * Defines
 */
#ifndef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN   (8*1024)
#endif

/* Tables where the OS object information is stored */
OS_impl_task_internal_record_t      OS_impl_task_table          [OS_MAX_TASKS];

/*
 * Local Function Prototypes
 */

/*----------------------------------------------------------------------------
 * Name: OS_PriorityRemap
 *
 * Purpose: Remaps the OSAL priority into one that is viable for this OS
 *
 * Note: This implementation assumes that InputPri has already been verified
 * to be within the range of [0,OS_MAX_TASK_PRIORITY]
 *
----------------------------------------------------------------------------*/
static int OS_PriorityRemap(uint32 InputPri)
{
    int OutputPri;

        /* use the "MAX" local priority only for OSAL tasks with priority=0 */

        /* use the "MIN" local priority only for OSAL tasks with priority=255 */

        /*
         * Spread the remainder of OSAL priorities over the remainder of local priorities
         *
         * Note OSAL priorities use the VxWorks style with zero being the
         * highest and OS_MAX_TASK_PRIORITY being the lowest, this inverts it
         */

    return OutputPri;
} /* end OS_PriorityRemap */



/*----------------------------------------------------------------
 *
 * Function: OS_NoopSigHandler
 *
 *  Purpose: Local helper routine, not part of OSAL API.
 *           A POSIX signal handler that does nothing
 *
 *-----------------------------------------------------------------*/
static void  OS_NoopSigHandler (int signal)
{
} /* end OS_NoopSigHandler */



/*---------------------------------------------------------------------------------------
   Name: OS_PthreadEntry

   Purpose: A Simple pthread-compatible entry point that calls the real task function

   returns: NULL

    NOTES: This wrapper function is only used locally by OS_TaskCreate below

---------------------------------------------------------------------------------------*/
static void *OS_PthreadTaskEntry(void *arg)
{

   return NULL;
}

/*---------------------------------------------------------------------------------------
   Name: OS_Posix_GetSchedulerParams

   Purpose: Helper function to get the details of the given OS scheduling policy.
            Determines if the policy is usable by OSAL - namely, that it provides
            enough priority levels to be useful.

   returns: true if policy is suitable for use by OSAL

    NOTES: Only used locally by task API initialization

---------------------------------------------------------------------------------------*/
static bool OS_Posix_GetSchedulerParams(int sched_policy, POSIX_PriorityLimits_t *PriLim)
{

    /*
     * Set up the local Min/Max priority levels (varies by OS and scheduler policy)
     *
     * Per POSIX:
     *  - The sched_get_priority_min/max() returns a number >= 0 on success.
     *    (-1 indicates an error)
     *  - Numerically higher values are scheduled before numerically lower values
     *  - A compliant OS will have a spread of at least 32 between min and max
     */

    /*
     * For OSAL, the absolute minimum spread between min and max must be 4.
     *
     * Although POSIX stipulates 32, we don't necessarily need that many, but we
     * also want to confirm that there is an acceptable spread.
     *
     * - Highest is reserved for the root task
     * - Next highest is reserved for OSAL priority=0 task(s)
     * - Lowest is reserved for OSAL priority=255 tasks(s)
     * - Need at least 1 for everything else.
     */


    /* If we get here, then the sched_policy is potentially valid */

    return true;
} /* end OS_Posix_GetSchedulerParams */

/*
 *********************************************************************************
 *          TASK API
 *********************************************************************************
 */

/*---------------------------------------------------------------------------------------
   Name: OS_Posix_TaskAPI_Impl_Init

   Purpose: Initialize the Posix Task data structures

 ----------------------------------------------------------------------------------------*/
int32 OS_Posix_TaskAPI_Impl_Init(void)
{


   /* Initialize Local Tables */


   /* Clear the "limits" structs otherwise the compiler may warn
    * about possibly being used uninitialized (false warning)
    */


   /*
    * Create the key used to store OSAL task IDs
    */

   /*
   ** Disable Signals to parent thread and therefore all
   ** child threads create will block all signals
   ** Note: Timers will not work in the application unless
   **       threads are spawned in OS_Application_Startup.
   */

   /*
    * Keep these signals unblocked so the process can be interrupted
    */

   /*
    * One should not typically block ANY of the synchronous error
    * signals, i.e. SIGSEGV, SIGFPE, SIGILL, SIGBUS
    *
    * The kernel generates these signals in response to hardware events
    * and they get routed to the _specific thread_ that was executing when
    * the problem occurred.
    *
    * While it is technically possible to block these signals, the result is
    * undefined, and it makes debugging _REALLY_ hard.  If the kernel ever does
    * send one it means there really is a major problem, best to listen to it,
    * and not ignore it.
    */

   /*
    * Set the mask and store the original (default) mask in the POSIX_GlobalVars.NormalSigMask
    */


   /*
    * Add all "RT" signals into the POSIX_GlobalVars.NormalSigMask
    * This will be used for the signal mask of the main thread
    * (This way it will end up as the default/original signal mask plus all RT sigs)
    */


   /*
    * SIGHUP is used to wake up the main thread when necessary,
    * so make sure it is NOT in the set.
    */

   /*
   ** Install noop as the signal handler for SIGUP.
   */

   /*
   ** Raise the priority of the current (main) thread so that subsequent
   ** application initialization will complete.  This had previously been
   ** done by the BSP and but it is moved here.
   **
   ** This will only work if the user owning this process has permission
   ** to create real time threads.  Otherwise, the default priority will
   ** be retained.  Typically this is only the root user, but finer grained
   ** permission controls are out there.  So if it works, great, but if
   ** a permission denied error is generated, that is OK too - this allows
   ** easily debugging code as a normal user.
   */

           /*
            * If both policies are valid, choose the best. In general, FIFO is preferred
            * since it is simpler.
            *
            * But, RR is preferred if mapping several OSAL priority levels into the
            * same local priority level. For instance, if 2 OSAL tasks are created at priorities
            * "2" and "1", both may get mapped to local priority 98, and if using FIFO then the
            * task at priority "2" could run indefinitely, never letting priority "1" execute.
            *
            * This violates the original intent, which would be to have priority "1" preempt
            * priority "2" tasks.  RR is less bad since it at least guarantees both tasks some
            * CPU time,
            */

               /*
                * If the spread from min->max is greater than what OSAL actually needs,
                * then FIFO is the preferred scheduler.  Must take into account one extra level
                * for the root task.
                */


           /*
            * This OSAL POSIX implementation will reserve the absolute highest priority
            * for the root thread, which ultimately will just pend in sigsuspend() so
            * it will not actually DO anything, except if sent a signal.  This way,
            * that thread will still be able to preempt a high-priority user thread that
            * has gone awry (i.e. using 100% cpu in FIFO mode).
            */


           /*
            * If the spread from min->max is greater than what OSAL actually needs,
            * then truncate it at the number of OSAL priorities.  This will end up mapping 1:1.
            * and leaving the highest priority numbers unused.
            */


           /*
            * Set the boolean to indicate that "setschedparam" worked --
            * This means that it is also expected to work for future calls.
            */


   /*
    * In strict (non-permissive) mode, if the task priority setting did not work, fail with an error.
    * This would be used on a real target where it needs to be ensured that priorities are active
    * and the "silent fallback" of debug mode operation is not desired.
    */

   return OS_SUCCESS;
} /* end OS_Posix_TaskAPI_Impl_Init */


/*----------------------------------------------------------------
 *
 * Function: OS_Posix_InternalTaskCreate_Impl
 *
 *  Purpose: Local helper routine, not part of OSAL API.
 *
 *-----------------------------------------------------------------*/
int32 OS_Posix_InternalTaskCreate_Impl(pthread_t *pthr, uint32 priority, size_t stacksz, PthreadFuncPtr_t entry, void *entry_arg)
{



    /*
     ** Initialize the pthread_attr structure.
     ** The structure is used to set the stack and priority
     */

    /*
     * Adjust the stack size parameter.
     *
     * POSIX has additional restrictions/limitations on the stack size of tasks that
     * other RTOS environments may not have.  Specifically POSIX says that the stack
     * size must be at least PTHREAD_STACK_MIN and may also need to be a multiple of the
     * system page size.
     *
     * Rounding up means the user might get a bigger stack than they requested, but
     * that should not break anything aside from consuming extra memory.
     */


    /*
    ** Set the Stack Size
    */


    /*
    ** Test to see if the original main task scheduling priority worked.
    ** If so, then also set the attributes for this task.  Otherwise attributes
    ** are left at default.
    */

    return OS_SUCCESS;
} /* end OS_Posix_InternalTaskCreate_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskCreate_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskCreate_Impl (uint32 task_id, uint32 flags)
{
   return OS_SUCCESS;
} /* end OS_TaskCreate_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskMatch_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskMatch_Impl(uint32 task_id)
{

   return OS_SUCCESS;
} /* end OS_TaskMatch_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskDelete_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskDelete_Impl (uint32 task_id)
{
    /*
    ** Try to delete the task
    ** If this fails, not much recourse - the only potential cause of failure
    ** to cancel here is that the thread ID is invalid because it already exited itself,
    ** and if that is true there is nothing wrong - everything is OK to continue normally.
    */
    return OS_SUCCESS;

} /* end OS_TaskDelete_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskExit_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
void OS_TaskExit_Impl()
{

} /* end OS_TaskExit_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskDelay_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskDelay_Impl(uint32 millisecond)
{

  return OS_SUCCESS;
} /* end OS_TaskDelay_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskSetPriority_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskSetPriority_Impl (uint32 task_id, uint32 new_priority)
{

   return OS_SUCCESS;
} /* end OS_TaskSetPriority_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskRegister_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskRegister_Impl(uint32 global_task_id)
{

   return OS_SUCCESS;
} /* end OS_TaskRegister_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskGetId_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 OS_TaskGetId_Impl (void)
{
   OS_U32ValueWrapper_t self_record;

   self_record.opaque_arg = pthread_getspecific(POSIX_GlobalVars.ThreadKey);

   return(self_record.value);
} /* end OS_TaskGetId_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskGetInfo_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskGetInfo_Impl (uint32 task_id, OS_task_prop_t *task_prop)
{
   /*
    * NOTE - this is not really valid, as you can't officially
    * cast a pthread_t to an integer
    * (in fact this fails on cygwin where pthread_t is NOT an integral type)
    *
    * This is just a hack to fill the value with something.
    * To be portable, the application should _NOT_ be using OStask_id for anything.
    */

   return OS_SUCCESS;
} /* end OS_TaskGetInfo_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TaskIdMatchSystemData_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
bool OS_TaskIdMatchSystemData_Impl(void *ref, uint32 local_id, const OS_common_record_t *obj)
{
    return true;
}

/*----------------------------------------------------------------
 *
 * Function: OS_TaskValidateSystemData_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TaskValidateSystemData_Impl(const void *sysdata, uint32 sysdata_size)
{

    return OS_SUCCESS;
}



