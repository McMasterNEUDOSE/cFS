/**
  * @file 	csp_app_subtbl.c
  * @brief 	CSP app subscription table
  * @author Stephen Scott
  */

/* Table includes*/
#include "csp_app_tbldefs.h"
#include "cfe_tbl_filedef.h"
/* CFS App Subscriptions */
#include "csp_app_msgids.h"
/* Mission Specific App Subscriptions */
#include "comms_msgids.h"
#include "eps_msgids.h"
#include "payload_msgids.h"
/* cFE Core Subscriptions */
#include "cfe_msgids.h"

/**
  * @brief 	Definition of the CSP app subscription table.
  * 		Assoicates message IDs with a CSP packet priority
  */
CSP_App_SubTable_t CSP_App_SubTbl = 
{
	{
		/* CFS App Subscriptions */
		{CSP_APP_HK_TLM_MID, 			CSP_PRIO_NORM},

		/* Mission Specific App Subscriptions */
		{COMMS_HK_TLM_MID, 				CSP_PRIO_HIGH},
		{EPS_HK_TLM_MID, 				CSP_PRIO_HIGH},
		{PAYLOAD_HK_TLM_MID, 			CSP_PRIO_HIGH},

		/* cFE Core Subscriptions */
		{CFE_ES_HK_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_EVS_HK_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_SB_HK_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_TBL_HK_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_TIME_HK_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_TIME_DIAG_TLM_MID, 		CSP_PRIO_NORM},
		{CFE_SB_STATS_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_TBL_REG_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_EVS_LONG_EVENT_MSG_MID, 	CSP_PRIO_NORM},
		{CFE_ES_APP_TLM_MID, 			CSP_PRIO_NORM},
		{CFE_ES_MEMSTATS_TLM_MID, 		CSP_PRIO_NORM}
	}
};

/* Definition of table file that is built */
CFE_TBL_FILEDEF(CSP_App_SubTbl, CSP_APP.CSP_App_SubTbl, CSP App Sub Tbl, csp_app_subtbl.tbl)
