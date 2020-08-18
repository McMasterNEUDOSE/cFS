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
 * \file     os-impl-common.c
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-posix.h"
#include "bsp-impl.h"

#include "os-impl-tasks.h"
#include "os-impl-queues.h"
#include "os-impl-binsem.h"
#include "os-impl-countsem.h"
#include "os-impl-mutex.h"

#include "os-shared-common.h"
#include "os-shared-idmap.h"
#include "os-shared-errors.h"


POSIX_GlobalVars_t   POSIX_GlobalVars = { 0 };


/*---------------------------------------------------------------------------------------
   Name: OS_API_Impl_Init

   Purpose: Initialize the tables that the OS API uses to keep track of information
            about objects

   returns: OS_SUCCESS or OS_ERROR
---------------------------------------------------------------------------------------*/
int32 OS_API_Impl_Init(uint32 idtype)
{
    int32               return_code;

    return_code = OS_SUCCESS;

    return(return_code);
} /* end OS_API_Impl_Init */


/*----------------------------------------------------------------
 *
 * Function: OS_IdleLoop_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
void OS_IdleLoop_Impl(void)
{
   /*
    * Unblock signals and wait for something to occur
    *
    * Note - "NormalSigMask" was calculated during task init to be the original signal mask
    * of the process PLUS all "RT" signals.  The RT signals are used by timers, so we want
    * to keep them masked here (this is different than the original POSIX impl).  The
    * timebase objects have a dedicated thread that will be doing "sigwait" on those.
    */
   sigsuspend(&POSIX_GlobalVars.NormalSigMask);
} /* end OS_IdleLoop_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_ApplicationShutdown_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
void OS_ApplicationShutdown_Impl(void)
{
   /*
    * Raise a signal that is unblocked in OS_IdleLoop(),
    * which should break it out of the sigsuspend() call.
    */
   kill(getpid(), SIGHUP);
} /* end OS_ApplicationShutdown_Impl */

/*----------------------------------------------------------------
 *
 * Function: OS_CompAbsDelayTime
 *
 * Purpose:  Local helper function
 *
 * This function accept time interval, msecs, as an input and
 * computes the absolute time at which this time interval will expire.
 * The absolute time is programmed into a struct.
 *
 *-----------------------------------------------------------------*/
void  OS_Posix_CompAbsDelayTime( uint32 msecs, struct timespec * tm)
{
    /* add the delay to the current time */

    /* convert residue ( msecs )  to nanoseconds */

} /* end OS_CompAbsDelayTime */


