/*******************************************************************************
**
** File: csp_app_tbldefs.h
**
** Purpose:
**   This file is for the CSP table definitions.
**
** Author:
**   Stephen Scott
**
*******************************************************************************/

/*
** Ensure the header is only included once
*/
#ifndef _csp_tbldefs_
#define _csp_tbldefs_

/*
** CFE includes
*/
#include "cfe_sb.h"
#include "cfe_platform_cfg.h"

/*
** CSP include necessary for csp_prio_t
*/
#include "csp/csp_types.h"

/*******************************************************************************
**
** CSP table structure definitions
**
*******************************************************************************/

/*
** CSP definition table entry
*/
typedef struct
{
	CFE_SB_MsgId_t 	Stream;
	csp_prio_t 		Priority;
} CSP_App_Sub_t;

typedef struct
{
	CSP_App_Sub_t Subs[CFE_PLATFORM_SB_MAX_MSG_IDS];
} CSP_App_SubTable_t;

#endif
