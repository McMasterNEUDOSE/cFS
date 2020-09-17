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
 * \file     os-impl-timebase.c
 * \ingroup  FreeRTOS
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-impl-timebase.h"
#include "os-freertos.h"


/****************************************************************************************
                                EXTERNAL FUNCTION PROTOTYPES
 ***************************************************************************************/

/****************************************************************************************
                                INTERNAL FUNCTION PROTOTYPES
 ***************************************************************************************/


/****************************************************************************************
                                     DEFINES
 ***************************************************************************************/

/*
 * Prefer to use the MONOTONIC clock if available, as it will not get distrupted by setting
 * the time like the REALTIME clock will.
 */
#ifndef OS_PREFERRED_CLOCK
#ifdef  _POSIX_MONOTONIC_CLOCK
#define OS_PREFERRED_CLOCK      CLOCK_MONOTONIC
#else
#define OS_PREFERRED_CLOCK      CLOCK_REALTIME
#endif
#endif

/****************************************************************************************
                                     GLOBALS
 ***************************************************************************************/

OS_impl_timebase_internal_record_t OS_impl_timebase_table[OS_MAX_TIMEBASES];

/****************************************************************************************
                                INTERNAL FUNCTIONS
 ***************************************************************************************/


/*----------------------------------------------------------------
 *
 * Function: OS_TimeBaseLock_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
void OS_TimeBaseLock_Impl(uint32 local_id)
{

} /* end OS_TimeBaseLock_Impl */

/*----------------------------------------------------------------
 *
 * Function: OS_TimeBaseUnlock_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
void OS_TimeBaseUnlock_Impl(uint32 local_id)
{

} /* end OS_TimeBaseUnlock_Impl */


/****************************************************************************************
                                INITIALIZATION FUNCTION
 ***************************************************************************************/

/******************************************************************************
 *  Function:  OS_Posix_TimeBaseAPI_Impl_Init
 *
 *  Purpose:  Initialize the timer implementation layer
 *
 *  Arguments:
 *
 *  Return:
 */
int32 OS_FreeRTOS_TimeBaseAPI_Impl_Init(void)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_Posix_TimeBaseAPI_Impl_Init */

/****************************************************************************************
                                   Time Base API
 ***************************************************************************************/

/*----------------------------------------------------------------
 *
 * Function: OS_TimeBaseCreate_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TimeBaseCreate_Impl(uint32 timer_id)
{
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TimeBaseCreate_Impl */

/*----------------------------------------------------------------
 *
 * Function: OS_TimeBaseSet_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TimeBaseSet_Impl(uint32 timer_id, int32 start_time, int32 interval_time)
{
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TimeBaseSet_Impl */



/*----------------------------------------------------------------
 *
 * Function: OS_TimeBaseDelete_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TimeBaseDelete_Impl(uint32 timer_id)
{
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TimeBaseDelete_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_TimeBaseGetInfo_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_TimeBaseGetInfo_Impl (uint32 timer_id, OS_timebase_prop_t *timer_prop)
{
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_TimeBaseGetInfo_Impl */

