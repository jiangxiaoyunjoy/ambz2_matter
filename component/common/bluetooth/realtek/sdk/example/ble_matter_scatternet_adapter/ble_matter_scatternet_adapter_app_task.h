/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      ble_matter_scatternet_adapter_app_task.h
   * @brief     Routines to create App task and handle events & messages
   * @author    jane
   * @date      2017-06-02
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef __BLE_MATTER_SCATTERNET_ADAPTER_APP_TASK_H_
#define __BLE_MATTER_SCATTERNET_ADAPTER_APP_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Initialize App task
 * @return void
 */
bool ble_matter_scatternet_adapter_app_send_api_msg(uint16_t sub_type, void *arg);
bool ble_matter_scatternet_adapter_send_callback_msg(uint16_t msg_type, uint8_t cb_type, void *arg);
void ble_matter_scatternet_adapter_callback_main_task(void *p_param);
void ble_matter_scatternet_adapter_app_main_task(void *p_param);
void ble_matter_scatternet_adapter_app_task_init(void);
void ble_matter_scatternet_adapter_app_task_deinit(void);
void ble_matter_scatternet_adapter_at_cmd_send_msg(uint16_t subtype, void *arg);
#ifdef __cplusplus
}
#endif
#endif
