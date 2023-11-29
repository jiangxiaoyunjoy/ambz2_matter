/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      ble_matter_scatternet_adapter_at_cmd.c
   * @brief     This file handles BLE central application routines.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

/*============================================================================*
 *                              Header Files
 *============================================================================*/
#if (defined(CONFIG_BLE_MATTER_SCATTERNET_ADAPTER) && CONFIG_BLE_MATTER_SCATTERNET_ADAPTER)
#include "app_msg.h"
#include "log_service.h"
#include <gap_scan.h>
#include <profile_client.h>
#include <gap.h>
#include <gap_msg.h>
#include <gap_bond_le.h>
#include <gap_conn_le.h>
//#include "ble_matter_scatternet_adapter_app_task.h"
#include "ble_matter_scatternet_adapter_at_cmd.h"
#include <ble_matter_scatternet_adapter_app_flags.h>
#include "os_msg.h"
#include "os_sched.h"
#include "os_mem.h"


#define MAX_ARGC 12
#define UUID_16_LEN		2
#define UUID_128_LEN	16
char ble_at_cmd_buf[256] = {0};

static u8 ctoi(char c)
{
	if((c >= 'A') && (c <= 'F')) {
		return (c - 'A' + 0x0A);
	}

	if((c >= 'a') && (c <= 'f')) {
		return (c - 'a' + 0x0A);
	}

	if((c >= '0') && (c <= '9')) {
		return (c - '0' + 0x00);
	}

	return 0xFF;
}

static u8 hex_str_to_bd_addr(u32 str_len, s8 *str, u8 *num_arr)
{
	num_arr += str_len/2 -1;
	u32 n = 0;
	u8 num = 0;

	if (str_len < 2) {
		return FALSE;
	}
	while (n < str_len) {
		if ((num = ctoi(str[n++])) == 0xFF) {
			return FALSE;
		}
		*num_arr = num << 4;
		if ((num = ctoi(str[n++])) == 0xFF) {
			return FALSE;
		}
		*num_arr |= num;
		num_arr--;
	}
	return TRUE;
}

static int hex_str_to_int(u32 str_len, s8*str)
{
	int result = 0;
	unsigned int n = 2;
	if((str_len < 3) || (str[0] != '0') || ((str[1] != 'x') && (str[1] != 'X'))){
		return -1;
	}
	while(n < str_len){
		result = (result << 4) | (ctoi(str[n++]));
	}
	return result;
}

void fATBS(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(1, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBS] Scan:ATBS=scan_enable/disable\n");
	printf("[ATBS] eg:ATBS=1\n");
	printf("[ATBS] eg:ATBS=0\n");
}

void fATBC(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
		strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 3) {
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}
	
	ble_matter_scatternet_adapter_at_cmd_send_msg(2, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBC] Connect:ATBC=AddrType,Addr\n");
	printf("[ATBC] eg:ATBC=P,665544778899\n");
}

void fATBD(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(3, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBD] Disconnect:ATBD=Conn_id\n");
	printf("[ATBD] eg:ATBD=0\n");
}

void fATBI(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
    memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2) {
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(4, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBI] Get active device information:ATBI=Conn_id\n");
	printf("[ATBI] eg:ATBI=0\n");
}

void fATBK(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
    memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if ((argc != 3) && (argc != 4) && (argc != 6)){
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(5, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBK] Config and set authentication information\n");
	printf("[ATBK] eg:ATBK=SEND,conn_id\n");
}

void fATBO(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
    memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc != 2){
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(6, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBO] Get bond information:ATBO=INFO\n");
	printf("[ATBO] Clear bond information:ATBO=CLEAR\n");
}

void fATBG(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
    memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if ((argc != 3) && (argc != 5) && (argc != 7)){
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(7, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBG] Get all services: ATBG=ALL,connect_id\n");
	printf("[ATBG] Discover services by uuid: ATBG=SRV,connect_id,uuid_type,uuid\n");
	printf("[ATBG] Discover characteristic: ATBG=CHARDIS,connect_id,start_handle,end_handle\n");
	printf("[ATBG] Discover characteristic by uuid: ATBG=CHARUUID,connect_id,start_handle,end_handle,type,uuid\n");
	printf("[ATBG] Discover characteristic descriptor: ATBG=CHARDDIS,connect_id,start_handle,end_handle\n");
	printf("[ATBG] eg:ATBG=ALL,0\n");
	printf("[ATBG] eg(uuid16):ATBG=SRV,0,0,1803\n");
	printf("[ATBG] eg(uuid128):ATBG=SRV,0,1,00112233445566778899aabbccddeeff\n");
	printf("[ATBG] eg:ATBG=CHARDIS,0,0x8,0xFF\n");
	printf("[ATBG] eg(uuid16):ATBG=CHARUUID,0,0x1,0xFFFF,0,B001\n");
	printf("[ATBG] eg(uuid128):ATBG=CHARUUID,0,0x1,0xFFFF,1,00112233445566778899aabbccddeeff\n");
	printf("[ATBG] eg:ATBG=CHARDDIS,0,0xe,0x10\n");
}

void fATBR(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
    memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if ((argc != 3) && (argc != 6)){
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(8, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBR] Read characteristic: ATBR=conn_id,handle\n");
	printf("[ATBR] Read characterristic value by uuid: ATBR=conn_id,start_handle,end_handle,uuid_type,uuid\n");
	printf("[ATBR] eg:ATBR=0,0xa\n");
	printf("[ATBR] eg(uuid16):ATBR=0,0x1,0xFFFF,0,B001\n");
	printf("[ATBR] eg(uuid128):ATBR=0,0x1,0xFFFF,1,00112233445566778899aabbccddeeff\n");
}

void fATBW(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
    memset(ble_at_cmd_buf, 0, 256);

	if (arg) {
        strncpy(ble_at_cmd_buf, arg, sizeof(ble_at_cmd_buf));
		argc = parse_param(arg, argv);
	} else {
		goto exit;
	}

	if (argc < 5){
		printf("[printf] ERROR: input parameter error!\n\r");
		goto exit;
	}

	ble_matter_scatternet_adapter_at_cmd_send_msg(9, ble_at_cmd_buf);
	return;

exit:
	printf("[ATBW] Write data to service: ATBW=conn_id,type,handle,length,value\n");
	printf("[ATBW] [type]: write type: 1-(write request), 2-(write command)\n");
	printf("[ATBW] [handle]: attribute handle\n");
	printf("[ATBW] [length]: value length\n");
	printf("[ATBW] [lvalue]: overwrite the value\n");
	printf("[ATBW] eg:ATBW=0,1,0x11,0x2,0x1,0x2\n");
}

int ble_matter_scatternet_adapter_handle_at_cmd(uint16_t subtype, void *arg)
{
    int argc=0;
	char *argv[12] = {0};
	if (arg) {
		argc = parse_param(arg, argv);
	}

    switch(subtype){
        case 1://scan
        {
            if(strcmp(argv[1], "0") == 0)
            {
                printf("Stop scan...\n");
                le_scan_stop();
            }
            else if(strcmp(argv[1], "1") == 0)
            {
                printf("Start scan...\n");
                le_scan_start();
            }
        }
        break;

        case 2://connect
        {
            u8 DestAddr[6] = {0};
            u8 DestAddrType = GAP_REMOTE_ADDR_LE_PUBLIC;
            T_GAP_LE_CONN_REQ_PARAM conn_req_param;

            if(strcmp(argv[1], "P") == 0)
                DestAddrType = GAP_REMOTE_ADDR_LE_PUBLIC;
            else if(strcmp(argv[1], "R") == 0)
                DestAddrType = GAP_REMOTE_ADDR_LE_RANDOM;
            if (strlen(argv[2]) != 12) {
                printf("ERROR: mac address length error!\r\n");
                return -1;
            }

            hex_str_to_bd_addr(strlen(argv[2]), ( s8 *)argv[2], (u8*)DestAddr);

            conn_req_param.scan_interval = 0xA0;	//100ms
            conn_req_param.scan_window = 0x80;		//80ms
            conn_req_param.conn_interval_min = 0x60;	//120ms
            conn_req_param.conn_interval_max = 0x60;	//120ms
            conn_req_param.conn_latency = 0;
            conn_req_param.supv_tout = 1000;
            conn_req_param.ce_len_min = 2 * (conn_req_param.conn_interval_min - 1);
            conn_req_param.ce_len_max = 2 * (conn_req_param.conn_interval_max - 1);
            le_set_conn_param(GAP_CONN_PARAM_1M, &conn_req_param);

            printf("cmd_con, DestAddr: 0x%02X:0x%02X:0x%02X:0x%02X:0x%02X:0x%02X\r\n",
                    DestAddr[5], DestAddr[4], DestAddr[3], DestAddr[2], DestAddr[1], DestAddr[0]);

            le_connect(0, DestAddr, (T_GAP_REMOTE_ADDR_TYPE)DestAddrType, GAP_LOCAL_ADDR_LE_PUBLIC, 1000);
        }
        break;

        case 3://disconnect
        {
			uint8_t conn_id = atoi(argv[1]);
            le_disconnect(conn_id);
        }
        break;

        case 4://infomation
        {
            uint8_t conn_id = atoi(argv[1]);
            u8 conn_max_link = BLE_MATTER_SCATTERNET_ADAPTER_CENTRAL_APP_MAX_LINKS;
            T_GAP_CONN_INFO conn_info;

            if (le_get_conn_info(conn_id, &conn_info))
            {
                printf("ShowCon conn_id %d state 0x%x role %d\r\n", conn_id,
                                conn_info.conn_state, conn_info.role);
                printf("RemoteBd = [%02x:%02x:%02x:%02x:%02x:%02x] type = %d\r\n",
                                conn_info.remote_bd[5], conn_info.remote_bd[4],
                                conn_info.remote_bd[3], conn_info.remote_bd[2],
                                conn_info.remote_bd[1], conn_info.remote_bd[0],
                                conn_info.remote_bd_type);
                printf("active link num %d, idle link num %d\r\n", le_get_active_link_num(), le_get_idle_link_num());
            }
        }
        break;

        case 5://auth
        {
            uint8_t conn_id = atoi(argv[2]);
            if(strcmp(argv[1],"SEND") == 0) {
                if(argc != 3){
                    printf("ERROR:input parameter error!\r\n");
                    return -1;
                }
                le_bond_pair(conn_id);
            }
        }
        break;

        case 6://bond
        {
            if(strcmp(argv[1],"CLEAR") == 0) {
		        le_bond_clear_all_keys();
	        }else if(strcmp(argv[1], "INFO") == 0){
	        	u8 i;
	        	T_LE_KEY_ENTRY *p_entry;
	        	for (i = 0; i < bond_storage_num; i++) {    
	    		p_entry = le_find_key_entry_by_idx(i);
	    		if (p_entry != NULL) {
	        		printf("bond_dev[%d]: bd 0x%02x%02x%02x%02x%02x%02x, addr_type %d, flags 0x%x\r\n",
							p_entry->idx,
							p_entry->remote_bd.addr[5],
							p_entry->remote_bd.addr[4],
							p_entry->remote_bd.addr[3],
							p_entry->remote_bd.addr[2],
							p_entry->remote_bd.addr[1],
							p_entry->remote_bd.addr[0],
							p_entry->remote_bd.remote_bd_type,
							p_entry->flags);
		        	}
	        	}
        	}else{
		        printf("ERROR:input command error!\r\n");
        	}
        }
        break;

        case 7://discover
        {
            u8 conn_id;
            u8 uuid_type;
            u8 uuid[16] = {0};
            u16 start_handle;
            u16 end_handle;
            u16 uuid16;

            conn_id = atoi(argv[2]);

            if(strcmp(argv[1], "ALL") == 0) {
                gcs_all_primary_srv_discovery(conn_id);
            }else if(strcmp(argv[1], "SRV") == 0){
                if(argc != 5){
                    printf("ERROR:input parameter error!\r\n");
                    return -1;
                }
                uuid_type = atoi(argv[3]);
                if(uuid_type == 0){
                    if (strlen(argv[4]) != 2 * UUID_16_LEN){
                        printf("ERROR:uuid length error!\r\n");
                        return -1;
                    }
                    hex_str_to_bd_addr(strlen(argv[4]), (s8 *)argv[4], (u8 *)uuid);
                    uuid16 = (uuid[1]<<8) | uuid[0];
                    gcs_by_uuid_srv_discovery(conn_id, uuid16);
                }else if(uuid_type == 1){
                    if (strlen(argv[4]) != 2 * UUID_128_LEN){
                        printf("ERROR:uuid length error!\r\n");
                        return -1;
                    }
                    hex_str_to_bd_addr(strlen(argv[4]), (s8 *)argv[4],	(u8 *)uuid);
                    gcs_by_uuid128_srv_discovery(conn_id, uuid);
                }else{
                    printf("ERROR:uuid type error!\r\n");
                    return -1;
                }
            }else if(strcmp(argv[1], "CHARDIS") == 0){
                if(argc != 5){
                    printf("ERROR:input parameter error!\r\n");
                    return -1;
                }
                start_handle = hex_str_to_int(strlen(argv[3]), (s8 *)argv[3]);
                end_handle = hex_str_to_int(strlen(argv[4]), (s8 *)argv[4]);
                gcs_all_char_discovery(conn_id, start_handle, end_handle);
            }else if(strcmp(argv[1], "CHARUUID") == 0){
                if(argc != 7){
                    printf("ERROR:input parameter error!\r\n");
                    return -1;
                }

                start_handle = hex_str_to_int(strlen(argv[3]), (s8 *)argv[3]);
                end_handle = hex_str_to_int(strlen(argv[4]), (s8 *)argv[4]);
                uuid_type = atoi(argv[5]);
                if(uuid_type == 0){
                    if (strlen(argv[6]) != 2 * UUID_16_LEN){
                        printf("ERROR:uuid length error!\r\n");
                        return -1;
                    }
                    hex_str_to_bd_addr(strlen(argv[6]), (s8 *)argv[6], (u8 *)uuid);
                    uuid16 = (uuid[1]<<8) | uuid[0];
                    gcs_by_uuid_char_discovery(conn_id, start_handle, end_handle, uuid16);
                }else if(uuid_type == 1){
                    if (strlen(argv[6]) != 2 * UUID_128_LEN){
                        printf("ERROR:uuid length error!\r\n");
                        return -1;
                    }
                    hex_str_to_bd_addr(strlen(argv[6]), (s8 *)argv[6], (u8 *)uuid);
                    gcs_by_uuid128_char_discovery(conn_id, start_handle, end_handle, uuid);
                }else{
                    printf("ERROR:uuid type error!\r\n");
                    return -1;
                }

            }else if(strcmp(argv[1], "CHARDDIS") == 0){
                if(argc != 5)
                    return -1;
                start_handle = hex_str_to_int(strlen(argv[3]), (s8 *)argv[3]);
                end_handle = hex_str_to_int(strlen(argv[4]), (s8 *)argv[4]);
                gcs_all_char_descriptor_discovery(conn_id, start_handle, end_handle);
            }
        }

        case 8://read
        {
            u8 conn_id;
            u16 handle;
            u16 start_handle;
            u16 end_handle;
            u8 uuid_type;
            u8 uuid[16] = {0};
            u16 uuid16;

            conn_id = atoi(argv[1]);

            if(argc == 3){
                handle = hex_str_to_int(strlen(argv[2]), (s8 *)argv[2]);
                gcs_attr_read(conn_id, handle);
            }

            if(argc == 6){
                start_handle = hex_str_to_int(strlen(argv[2]), (s8 *)argv[2]);
                end_handle = hex_str_to_int(strlen(argv[3]), (s8 *)argv[3]);
                uuid_type = atoi(argv[4]);
                printf("conn_id = %d, start_handle = 0x%x, end_handle = 0x%x, uuid_type = %d\r\n", conn_id, start_handle, end_handle, uuid_type);
                if(uuid_type == 0){
                    if (strlen(argv[5]) != 2 * UUID_16_LEN){
                        printf("ERROR:uuid length error!\r\n");
                        return -1;
                    }
                    hex_str_to_bd_addr(strlen(argv[5]), (s8 *)argv[5], (u8 *)uuid);
                    uuid16 = uuid[1]<<8 | uuid[0];
                    printf("uuid16 = 0x%x\r\n", uuid16);
                    gcs_attr_read_using_uuid16(conn_id, start_handle, end_handle, uuid16);

                }else if(uuid_type == 1){
                    if (strlen(argv[5]) != 2 * UUID_128_LEN){
                        printf("ERROR:uuid length error!\r\n");
                        return -1;
                    }
                    hex_str_to_bd_addr(strlen(argv[5]), (s8 *)argv[5], (u8 *)uuid);
                    gcs_attr_read_using_uuid128(conn_id, start_handle, end_handle, uuid);
                }else{
                    printf("ERROR:uuid type error!\r\n");
                    return -1;
                }

            }
        }
        break;

        case 9://write
        {
            u8 conn_id;
            u8 write_type;
            u16 handle;
            int length;
            int data_count;

            conn_id = atoi(argv[1]);
            write_type = atoi(argv[2]);
            handle = hex_str_to_int(strlen(argv[3]), (s8 *)argv[3]);
            length = hex_str_to_int(strlen(argv[4]), (s8 *)argv[4]);

            if (length == -1) {
                printf("Error:value length should be hexadecimal and start with '0X' or '0x'\r\n");
                return -1;
            } else if (length == 0) {
                printf("Error:value length should larger than 0\r\n");
                return -1;
            }

            u8 *data = (u8 *)os_mem_alloc(0, length * sizeof(u8));

            data_count = argc - 5;
            for (u8 i = 0; i < length; ++ i) {
                if (i < data_count)
                    data[i] = hex_str_to_int(strlen(argv[i + 5]), (s8 *)argv[i + 5]);
                else
                    data[i] = 0xff;
            }

            T_GAP_CAUSE ret = (conn_id, (T_GATT_WRITE_TYPE)write_type, handle, length, data);

            if (data != NULL)
                os_mem_free(data);
            (void) ret;
        }
        break;

        default:
        break;
    }
}
#endif