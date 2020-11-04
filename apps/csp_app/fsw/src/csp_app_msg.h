/**
  * @file 	csp_app_msg.h
  * @brief 	Define CSP App Messages and info
  * @author Stephen Scott
  */
#ifndef _csp_app_msg_h_
#define _csp_app_msg_h_

/* CSP App command codes */
#define CSP_APP_NOOP_CC                 0
#define CSP_APP_RESET_COUNTERS_CC       1

/**
  * @struct CSP_NoArgsCmd_t
  * @brief 	Command type with no arguments
  */
typedef struct
{
   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE]; /*!< Command header bytes */
} CSP_NoArgsCmd_t;

/* The following commands all share the "NoArgs" format */
typedef CSP_NoArgsCmd_t CSP_Noop_t;
typedef CSP_NoArgsCmd_t CSP_ResetCounters_t;

/**
  * @struct CSP_HkTlm_Payload_t
  * @brief 	CSP app housekeeping telemetry payload
  */
typedef struct
{
    uint8 	CommandErrorCounter;	/*!< Byte for command error counter */
    uint8 	CommandCounter; 		/*!< Byte for command counter */
    uint8 	spare[2];				/*!< Two spare bytes */
} CSP_HkTlm_Payload_t;

/**
  * @struct CSP_HkTlm_t
  * @brief 	CSP app housekeeping telemetry packet
  */
typedef struct
{
    uint8                  TlmHeader[CFE_SB_TLM_HDR_SIZE]; 	/*!< Housekeeping telemetry header */
    CSP_HkTlm_Payload_t    Payload; 						/*!< Housekeeping telemetry payload */
} OS_PACK CSP_HkTlm_t;

#endif /* _csp_app_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
