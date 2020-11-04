/**
  * @file 	csp_app_tbldefs.h
  * @brief 	CSP table definitions
  * @author Stephen Scott
  */

#ifndef _csp_tbldefs_
#define _csp_tbldefs_

#include "cfe_sb.h"
#include "cfe_platform_cfg.h"
/* CSP include necessary for csp_prio_t */
#include "csp/csp_types.h"

/**
  * @struct CSP_App_Sub_t
  * @brief CSP app table entry definition
  */
typedef struct
{
	CFE_SB_MsgId_t 	Stream; 	/*!< Software bus message ID */
	csp_prio_t 		Priority; 	/*!< CSP packet priority for corresponding message ID */
} CSP_App_Sub_t;

/**
  * @struct CSP_App_SubTable_t
  * @brief CSP app table definition
  */
typedef struct
{
	CSP_App_Sub_t Subs[CFE_PLATFORM_SB_MAX_MSG_IDS]; /*!< Array of entries in table */
} CSP_App_SubTable_t;

#endif
