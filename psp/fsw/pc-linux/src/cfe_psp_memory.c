/*
**  GSC-18128-1, "Core Flight Executive Version 6.7"
**
**  Copyright (c) 2006-2019 United States Government as represented by
**  the Administrator of the National Aeronautics and Space Administration.
**  All Rights Reserved.
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

/******************************************************************************
** File:  cfe_psp_memory.c
**
**      OSX x86 Linux Version
**
** Purpose:
**   cFE PSP Memory related functions. This is the implementation of the cFE 
**   memory areas that have to be preserved, and the API that is designed to allow
**   acccess to them. It also contains memory related routines to return the
**   address of the kernel code used in the cFE checksum.
**
** History:
**   2006/09/29  A. Cudmore      | Initial version for OS X 
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>

/*
** cFE includes 
*/
#include "common_types.h"
#include "osapi.h"

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"
#include "cfe_psp_memory.h"
#include "cfe_psp_config.h"

#include <target_config.h>

/*
 * Define the PSP-supported capacities to be the maximum allowed,
 * (since the PC-linux PSP has the advantage of abundant disk space to hold this)
 */
#define CFE_PSP_CDS_SIZE            (GLOBAL_CONFIGDATA.CfeConfig->CdsSize)
#define CFE_PSP_RESET_AREA_SIZE     (GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize)
#define CFE_PSP_USER_RESERVED_SIZE  (GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize)


typedef struct
{
    CFE_PSP_ReservedMemoryBootRecord_t BootRecord;
    CFE_PSP_ExceptionStorage_t ExceptionStorage;
} CFE_PSP_FreeRTOSReservedAreaFixedLayout_t;



/*
**  External Declarations
*/

/*
** Global variables
*/
                                                                              
/*
** Pointer to the vxWorks USER_RESERVED_MEMORY area
** The sizes of each memory area is defined in os_processor.h for this architecture.
*/
CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap;

                                                                              
/*
*********************************************************************************
** CDS related functions
*********************************************************************************
*/
/*
**  
*/
/******************************************************************************
**  Function: CFE_PSP_InitCDS
**
**  Purpose: This function is used by the ES startup code to initialize the 
**            Critical Data store area
**  
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/

void CFE_PSP_InitCDS(void)
{

}


/******************************************************************************
**  Function: CFE_PSP_DeleteCDS
**
**  Purpose:
**   This is an internal function to delete the CDS Shared memory segment. 
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_DeleteCDS(void)
{

}

/******************************************************************************
**  Function: CFE_PSP_GetCDSSize
**
**  Purpose: 
**    This function fetches the size of the OS Critical Data Store area.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/

int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
	return 0;
}

/******************************************************************************
**  Function: CFE_PSP_WriteToCDS
**
**  Purpose:
**    This function writes to the CDS Block.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/

int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes)
{
	return 0;
}



/******************************************************************************
**  Function: CFE_PSP_ReadFromCDS
**
**  Purpose:
**   This function reads from the CDS Block
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/

int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes)
{
	return 0;
}

/*
*********************************************************************************
** ES Reset Area related functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_InitESResetArea
**
**  Purpose:
**    This function is used by the ES startup code to initialize the
**     ES Reset Area.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_InitResetArea(void)
{

}


/******************************************************************************
**  Function: CFE_PSP_DeleteResetArea
**
**  Purpose:
**   This is an internal function to delete the Reset Area Shared memory segment. 
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_DeleteResetArea(void)
{

}


/*
*/
/******************************************************************************
**  Function: CFE_PSP_GetResetArea
**
**  Purpose:
**     This function returns the location and size of the ES Reset information area. 
**     This area is preserved during a processor reset and is used to store the 
**     ER Log, System Log and reset related variables
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 CFE_PSP_GetResetArea (cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
	return 0;
}

/*
*********************************************************************************
** ES User Reserved Area related functions
*********************************************************************************
*/
   
/******************************************************************************
**  Function: CFE_PSP_InitUserReservedArea 
**
**  Purpose:
**    This function is used by the ES startup code to initialize the
**      ES user reserved area.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_InitUserReservedArea(void)
{

}

/******************************************************************************
**  Function: CFE_PSP_DeleteUserReservedArea
**
**  Purpose:
**   This is an internal function to delete the User Reserved Shared memory segment. 
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_DeleteUserReservedArea(void)
{

}


/******************************************************************************
**  Function: CFE_PSP_GetUserReservedArea
**
**  Purpose:
**    This function returns the location and size of the memory used for the cFE
**     User reserved area.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea )
{
   return 0;
}

/*
*********************************************************************************
** ES Volatile disk memory related functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_InitVolatileDiskMem
**
**  Purpose:
**   This function is used by the ES startup code to initialize the memory
**   used by the volatile disk. On a desktop/posix platform this is currently
**   a no-op, because the volatile disk is being mapped to the desktop.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_InitVolatileDiskMem(void)
{
   /*
   ** Here, we want to clear out the volatile ram disk contents
   ** on a power on reset 
   */
}


/*
*********************************************************************************
** ES BSP Top Level Reserved memory initialization
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_GetVolatileDiskMem
**
**  Purpose:
**    This function returns the location and size of the memory used for the cFE
**     volatile disk.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk )
{
   return 0;
}


/******************************************************************************
**  Function: CFE_PSP_SetupReservedMemoryMap
**
**  Purpose:
**    This function performs the top level reserved memory initialization.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_SetupReservedMemoryMap(void)
{

}


int32 CFE_PSP_InitProcessorReservedMemory( uint32 RestartType )
{
	return 0;
}

/*
*********************************************************************************
** ES BSP kernel memory segment functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_GetKernelTextSegmentInfo
**
**  Purpose:
**    This function returns the start and end address of the kernel text segment.
**     It may not be implemented on all architectures.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment)
{
   return 0;
}


/******************************************************************************
**  Function: CFE_PSP_GetCFETextSegmentInfo
**
**  Purpose:
**    This function returns the start and end address of the CFE text segment.
**     It may not be implemented on all architectures.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment)
{
   return 0;
}

