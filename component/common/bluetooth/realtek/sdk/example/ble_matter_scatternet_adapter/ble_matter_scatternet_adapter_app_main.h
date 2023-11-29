/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      ble_matter_scatternet_adapter_app_main.h
   * @brief     This file handles BLE peripheral application routines.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _BLE_MATTER_SCATTERNET_ADAPTER_APP_MAIN_H__
#define _BLE_MATTER_SCATTERNET_ADAPTER_APP_MAIN_H__

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
#ifndef PLATFORM_OHOS
void ble_matter_scatternet_adapter_bt_stack_config_init(void);
#else
void ble_matter_scatternet_adapter_bt_stack_config_init(void);
#endif

void ble_matter_scatternet_adapter_app_le_gap_init(void);

void ble_matter_scatternet_adapter_app_le_profile_init(void);

void ble_matter_scatternet_adapter_task_init(void);

int ble_matter_scatternet_adapter_app_main(void);

int ble_matter_scatternet_adapter_app_init(void);

void ble_matter_scatternet_adapter_app_deinit(void);

#ifdef __cplusplus
};
#endif

#endif
