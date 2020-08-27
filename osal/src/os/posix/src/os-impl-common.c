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
 * \ingroup  FreeRTOS
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-shared-common.h"

/*---------------------------------------------------------------------------------------
   Name: OS_API_Impl_Init

   Purpose: Initialize the tables that the OS API uses to keep track of information
            about objects

   returns: OS_SUCCESS or OS_ERROR
---------------------------------------------------------------------------------------*/
int32 OS_API_Impl_Init(uint32 idtype)
{
    return OS_ERR_NOT_IMPLEMENTED;
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

} /* end OS_ApplicationShutdown_Impl */
