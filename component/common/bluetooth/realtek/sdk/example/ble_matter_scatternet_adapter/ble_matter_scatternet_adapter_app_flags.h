/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      ble_matter_scatternet_adapter_app_flags.h
   * @brief     This file is used to config app functions.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _BLE_MATTER_SCATTERNET_ADAPTER_APP_FLAGS_H_
#define _BLE_MATTER_SCATTERNET_ADAPTER_APP_FLAGS_H_

#include <bt_flags.h>
#include <app_common_flags.h>

/*============================================================================*
 *                              Constants
 *============================================================================*/
/** @brief  Config APP LE link number */
#if defined(CONFIG_PLATFORM_8721D)
#define BLE_MATTER_SCATTERNET_ADAPTER_APP_MAX_LINKS  4
#define BLE_MATTER_SCATTERNET_ADAPTER_PERIPHERAL_APP_MAX_LINKS   1 //for max slave link num
#define BLE_MATTER_SCATTERNET_ADAPTER_CENTRAL_APP_MAX_LINKS      3 //for max master link num
#elif defined(CONFIG_PLATFORM_8710C)
#define BLE_MATTER_SCATTERNET_ADAPTER_APP_MAX_LINKS  2
#define BLE_MATTER_SCATTERNET_ADAPTER_PERIPHERAL_APP_MAX_LINKS   1 //for max slave link num
#define BLE_MATTER_SCATTERNET_ADAPTER_CENTRAL_APP_MAX_LINKS      1 //for max master link num
#endif

/** @brief  Config the discovery table number of gcs_client */
#define BLE_MATTER_SCATTERNET_ADAPTER_APP_MAX_DISCOV_TABLE_NUM 40

#endif
