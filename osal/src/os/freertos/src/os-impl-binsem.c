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
 * \ingroup  FreeRTOS
 *
 * Purpose: This file contains some of the OS APIs abstraction layer
 *    implementation for POSIX
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-shared-binsem.h"



/*---------------------------------------------------------------------------------------
 * Helper function for acquiring the mutex when beginning a binary sem operation
 * This uses timedlock to avoid waiting forever, and is put into a wrapper function
 * to avoid pending forever.  The code should never pend on these for a long time.
 ----------------------------------------------------------------------------------------*/
int32 OS_Posix_BinSemAcquireMutex(pthread_mutex_t *mut)
{

    return OS_ERR_NOT_IMPLEMENTED;
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


/*---------------------------------------------------------------------------------------
   Name: OS_Posix_BinSemAPI_Impl_Init

   Purpose: Initialize the Binary Semaphore data structures

 ----------------------------------------------------------------------------------------*/
int32 OS_FreeRTOS_BinSemAPI_Impl_Init(void)
{
   return OS_ERR_NOT_IMPLEMENTED;
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

    return OS_ERR_NOT_IMPLEMENTED;

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
    return OS_ERR_NOT_IMPLEMENTED;
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
    return OS_ERR_NOT_IMPLEMENTED;
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
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_BinSemFlush_Impl */


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
   return OS_ERR_NOT_IMPLEMENTED;
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

 return OS_ERR_NOT_IMPLEMENTED;

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
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_BinSemGetInfo_Impl */

