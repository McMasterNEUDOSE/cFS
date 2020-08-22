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
 * \ingroup  posix
 * \author   joseph.p.hickey@nasa.gov
 *
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/

#include "os-posix.h"
#include "bsp-impl.h"

#include "os-impl-queues.h"
#include "os-shared-queue.h"
#include "os-shared-idmap.h"

/* Tables where the OS object information is stored */
OS_impl_queue_internal_record_t     OS_impl_queue_table         [OS_MAX_QUEUES];

/****************************************************************************************
                                MESSAGE QUEUE API
 ***************************************************************************************/

/*---------------------------------------------------------------------------------------
   Name: OS_Posix_QueueAPI_Impl_Init

   Purpose: Initialize the Queue data structures

 ----------------------------------------------------------------------------------------*/
int32 OS_Posix_QueueAPI_Impl_Init(void)
{


   /*
    * Automatic truncation is dependent on the OSAL_CONFIG_DEBUG_PERMISSIVE_MODE compile-time define - so
    * creating a too-large message queue on a target without OSAL_CONFIG_DEBUG_PERMISSIVE_MODE will fail
    * with an OS error as intended.
    */

   /*
    * Use the BSP-provided limit
    */


   /*
    * Initialize this to zero to indicate no limit
    */


   return OS_SUCCESS;
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
   int32     return_code;

   /* Try to delete and unlink the queue */

   return_code = OS_SUCCESS;


    return return_code;
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
   int32 return_code;

   /*
    ** Read the message queue for data
    */

      /*
       ** A signal can interrupt the mq_receive call, so the call has to be done with
       ** a loop
       */


      /*
       * NOTE - a prior implementation of OS_CHECK would check the mq_attr for a nonzero depth
       * and then call mq_receive().  This is insufficient since another thread might do the same
       * thing at the same time in which case one thread will read and the other will block.
       *
       * Calling mq_timedreceive with a zero timeout effectively does the same thing in the typical
       * case, but for the case where two threads do a simultaneous read, one will get the message
       * while the other will NOT block (as expected).
       */


      /*
       ** If the mq_timedreceive call is interrupted by a system call or signal,
       ** call it again.
       */


    /* END timeout */

   /* Figure out the return code */


      /* Map the system errno to the most appropriate OSAL return code */

         /* OS_PEND was supposed to pend forever until a message arrived
          * so something else is wrong.  Otherwise, at this point the only
          * "acceptable" errno is TIMEDOUT for the other cases.
          */

   return_code  = OS_SUCCESS;

   return return_code;
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
   int32 return_code;


   /*
    * NOTE - using a zero timeout here for the same reason that QueueGet does ---
    * checking the attributes and doing the actual send is non-atomic, and if
    * two threads call QueuePut() at the same time on a nearly-full queue,
    * one could block.
    */

   /* send message */


      /* Something else went wrong */

   return_code = OS_SUCCESS;

   return return_code;

} /* end OS_QueuePut_Impl */


