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
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 * This file contains the OSAL Timebase API for POSIX systems.
 *
 * This implementation depends on the POSIX Timer API which may not be available
 * in older versions of the Linux kernel. It was developed and tested on
 * RHEL 5 ./ CentOS 5 with Linux kernel 2.6.18
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-posix.h"
#include "os-impl-timebase.h"

#include "os-shared-timebase.h"
#include "os-shared-idmap.h"
#include "os-shared-common.h"


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
int32 OS_Posix_TimeBaseAPI_Impl_Init(void)
{

   int32  return_code;

   return_code = OS_SUCCESS;

       /*
       ** Mark all timers as available
       */

       /*
       ** get the resolution of the selected clock
       */

      /*
      ** Convert to microseconds
      ** Note that the resolution MUST be in the sub-second range, if not then
      ** it looks like the POSIX timer API in the C library is broken.
      ** Note for any flavor of RTOS we would expect <= 1ms.  Even a "desktop"
      ** linux or development system should be <= 100ms absolute worst-case.
      */

       /* Round to the nearest microsecond */

       /*
       ** initialize the attribute with default values
       */

       /*
       ** Allow the mutex to use priority inheritance
       */
           /*
           ** create the timebase sync mutex
           ** This gives a mechanism to synchronize updates to the timer chain with the
           ** expiration of the timer and processing the chain.
           */

       /*
        * Pre-calculate the clock tick to microsecond conversion factor.
        * This is used by OS_Tick2Micros(), OS_Milli2Ticks(), etc.
        */


       /*
        * Calculate microseconds per tick
        *  - If the ratio is not an integer, this will round to the nearest integer value
        *  - This is used internally for reporting accuracy,
        *  - TicksPerSecond values over 2M will return zero
        */


   return(return_code);
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
    /*
    ** Delete the timer
    */

    return OS_SUCCESS;
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
    return OS_SUCCESS;

} /* end OS_TimeBaseGetInfo_Impl */

