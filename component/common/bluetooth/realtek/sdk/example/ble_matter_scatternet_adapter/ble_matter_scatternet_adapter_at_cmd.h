/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      ble_matter_scatternet_adapter_at_cmd.h
   * @brief     This file handles BLE peripheral application routines.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _BLE_MATTER_SCATTERNET_ADAPTER_AT_CMD_H__
#define _BLE_MATTER_SCATTERNET_ADAPTER_AT_CMD_H__

#ifdef __cplusplus
extern "C" {
#endif
/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <app_msg.h>
#include <profile_server.h>

/*============================================================================*
 *                              Variables
 *============================================================================*/


/*============================================================================*
 *                              Functions
 *============================================================================*/
void fATBS(void *arg);

void fATBn(void *arg);

void fATBC(void *arg);

void fATBD(void *arg);

void fATBI(void *arg);

void fATBK(void *arg);

void fATBO(void *arg);

void fATBG(void *arg);

void fATBR(void *arg);

void fATBW(void *arg);

int ble_matter_scatternet_adapter_handle_at_cmd(uint16_t subtype, void *arg);

#ifdef __cplusplus
};
#endif

#endif