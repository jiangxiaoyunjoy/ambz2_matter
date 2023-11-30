/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      ble_matter_scatternet_adapter_service.h
   * @brief     This file defined BLE profile data.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

/* Define to prevent recursive inclusion */
#ifndef _BLE_MATTER_SCATTERNET_ADAPTER_SERVICE_H_
#define _BLE_MATTER_SCATTERNET_ADAPTER_SERVICE_H_

#ifdef __cplusplus
extern "C"  {
#endif      /* __cplusplus */

#include <profile_server.h>
#include "platform_opts_bt.h"
/*============================================================================*
 *                              Constants
 *============================================================================*/
#define MATTER_SCATTERNET_NOTIFY_INDICATE_V3_ENABLE     1
#define MATTER_SCATTERNET_NOTIFY_INDICATE_V3_DISABLE    2

#define BT_MATTER_SCATTERNET_ADAPTER_SERVICE_CHAR_RX_INDEX                 0x02 //write characyeristic value in matter service
#define BT_MATTER_SCATTERNET_ADAPTER_SERVICE_CHAR_TX_INDEX                 0x04 //read/indicate characteristic value in matter service
#define BT_MATTER_SCATTERNET_ADAPTER_SERVICE_CHAR_INDICATE_CCCD_INDEX      (BT_MATTER_SCATTERNET_ADAPTER_SERVICE_CHAR_TX_INDEX + 1)
#define BT_MATTER_SCATTERNET_ADAPTER_SERVICE_C3_INDEX                      0x07

typedef struct
{
    uint16_t len;
    uint8_t *p_value;
} T_MATTER_WRITE_READ_MSG;

typedef union
{
    uint8_t notification_indification_index; //!< ref: @ref SIMP_Service_Notify_Indicate_Info
    T_MATTER_WRITE_READ_MSG write_read;
} T_MATTER_UPSTREAM_MSG_DATA;

typedef struct
{
    uint8_t                 conn_id;
    T_SERVICE_CALLBACK_TYPE msg_type;
    T_MATTER_UPSTREAM_MSG_DATA msg_data;
} T_MATTER_CALLBACK_DATA;
/*============================================================================*
 *                              Functions
 *============================================================================*/
T_APP_RESULT  ble_matter_adapter_service_attr_read_cb(uint8_t conn_id, T_SERVER_ID service_id,
                                            uint16_t attrib_index, uint16_t offset, uint16_t *p_length, uint8_t **pp_value);

T_APP_RESULT ble_matter_adapter_service_attr_write_cb(uint8_t conn_id, T_SERVER_ID service_id,
                                            uint16_t attrib_index, T_WRITE_TYPE write_type, uint16_t length, uint8_t *p_value,
                                            P_FUN_WRITE_IND_POST_PROC *p_write_ind_post_proc);

void ble_matter_adapter_service_cccd_update_cb(uint8_t conn_id, T_SERVER_ID service_id, uint16_t index,
                                     uint16_t cccbits);

T_SERVER_ID ble_matter_adapter_service_add_service(void *p_func);

#ifdef __cplusplus
}
#endif

#endif /* _BT_MATTER_ADAPTER_WIFI_SERVICE_H_ */
