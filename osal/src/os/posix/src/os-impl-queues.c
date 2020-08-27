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
 * \file     os-impl-queues.c
 * \ingroup  FreeRTOS
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-impl-queues.h"
#include "os-shared-queue.h"

/* Tables where the OS object information is stored */
OS_impl_queue_internal_record_t     OS_impl_queue_table         [OS_MAX_QUEUES];

/****************************************************************************************
                                MESSAGE QUEUE API
 ***************************************************************************************/

/*---------------------------------------------------------------------------------------
   Name: OS_Posix_QueueAPI_Impl_Init

   Purpose: Initialize the Queue data structures

 ----------------------------------------------------------------------------------------*/
int32 OS_FreeRTOS_QueueAPI_Impl_Init(void)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_Posix_QueueAPI_Impl_Init */



/*----------------------------------------------------------------
 *
 * Function: OS_QueueCreate_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_QueueCreate_Impl (uint32 queue_id, uint32 flags)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_QueueCreate_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_QueueDelete_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_QueueDelete_Impl (uint32 queue_id)
{
    return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_QueueDelete_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_QueueGet_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_QueueGet_Impl (uint32 queue_id, void *data, uint32 size, uint32 *size_copied, int32 timeout)
{
   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_QueueGet_Impl */


/*----------------------------------------------------------------
 *
 * Function: OS_QueuePut_Impl
 *
 *  Purpose: Implemented per internal OSAL API
 *           See prototype for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 OS_QueuePut_Impl (uint32 queue_id, const void *data, uint32 size, uint32 flags)
{

   return OS_ERR_NOT_IMPLEMENTED;
} /* end OS_QueuePut_Impl */


