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
 * \file     os-impl-countsem.c
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-posix.h"
#include "os-impl-countsem.h"
#include "os-shared-countsem.h"

/*
 * Added SEM_VALUE_MAX Define
 */
#ifndef SEM_VALUE_MAX
#define SEM_VALUE_MAX       (UINT32_MAX/2)
#endif

/* Tables where the OS object information is stored */
OS_impl_countsem_internal_record_t  OS_impl_count_sem_table     [OS_MAX_COUNT_SEMAPHORES];


/****************************************************************************************
                               COUNTING SEMAPHORE API
 ***************************************************************************************/

/*
 * Unlike binary semaphores, counting semaphores can use the standard POSIX semaphore facility.
 * This has the advantage of more correct behavior on "give" operations:
 *  - give may be done from a signal / ISR context
 *  - give should not cause an unexpected task switch nor should it ever block
 */

/*---------------------------------------------------------------------------------------
   Name: OS_Posix_CountSemAPI_Impl_Init

   Purpose: Initialize the Counting Semaphore data structures

---------------------------------------------------------------------------------------*/
int32 OS_Posix_CountSemAPI_Impl_Init(void)
{
   memset(OS_impl_count_sem_table, 0, sizeof(OS_impl_count_sem_table));
   return OS_SUCCESS;
} /* end OS_Posix_CountSemAPI_Impl_Init */


/*----------------------------------------------------------------
 *
 * Function: OS_CountSemCreate_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_CountSemCreate_Impl (uint32 sem_id, uint32 sem_initial_value, uint32 options)
{
        return OS_SUCCESS;

} /* end OS_CountSemCreate_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_CountSemDelete_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_CountSemDelete_Impl (uint32 sem_id)
{

    return OS_SUCCESS;

} /* end OS_CountSemDelete_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_CountSemGive_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_CountSemGive_Impl ( uint32 sem_id )
{

    return OS_SUCCESS;

} /* end OS_CountSemGive_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_CountSemTake_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_CountSemTake_Impl ( uint32 sem_id )
{

    return OS_SUCCESS;
} /* end OS_CountSemTake_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_CountSemTimedWait_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_CountSemTimedWait_Impl ( uint32 sem_id, uint32 msecs )
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_CountSemTimedWait_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_CountSemGetInfo_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_CountSemGetInfo_Impl (uint32 sem_id, OS_count_sem_prop_t *count_prop)
{


    /* put the info into the stucture */
    return OS_SUCCESS;
} /* end OS_CountSemGetInfo_Impl */

