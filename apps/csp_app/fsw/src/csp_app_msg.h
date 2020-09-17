/*******************************************************************************
**
** File: csp_app_msg.h
**
** Purpose:
**  Define CSP App Messages and info
**
** Author:
**   Stephen Scott
**
*******************************************************************************/
#ifndef _csp_app_msg_h_
#define _csp_app_msg_h_

/*
** CSP App command codes
*/
#define CSP_APP_NOOP_CC                 0
#define CSP_APP_RESET_COUNTERS_CC       1

/*************************************************************************/

/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];

} CSP_NoArgsCmd_t;

/*
** The following commands all share the "NoArgs" format
**
** They are each given their own type name matching the command name, which_open_mode
** allows them to change independently in the future without changing the prototype
** of the handler function
*/
typedef CSP_NoArgsCmd_t      CSP_Noop_t;
typedef CSP_NoArgsCmd_t      CSP_ResetCounters_t;

/*************************************************************************/
/*
** Type definition (CSP App housekeeping)
*/

typedef struct
{
    uint8              CommandErrorCounter;
    uint8              CommandCounter;
    uint8              spare[2];
} CSP_HkTlm_Payload_t;

typedef struct
{
    uint8                  TlmHeader[CFE_SB_TLM_HDR_SIZE];
    CSP_HkTlm_Payload_t    Payload;

} OS_PACK CSP_HkTlm_t;

#endif /* _csp_app_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
