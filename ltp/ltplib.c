enum { __FILE_NUM__= 0 };

/**********************************************************************!KA****
*
* $Header: /var/lib/cvs/sw/src/clib/libbt/ltplib.c,v 1.61 2014/05/12 09:47:36 mj Exp $
*
* File:        $RCSfile: ltplib.c,v $
* Version:     $Name: P_SRP0007_U_KA_BLB1290_RC1 $
*
* Archive:     $Source: /var/lib/cvs/sw/src/clib/libbt/ltplib.c,v $
* Revision:    $Revision: 1.61 $
* Date:        $Date: 2014/05/12 09:47:36 $
* Author:      $Author: mj $
*
* ---------------------------------------------------------------------------
* !MODULE      [  ]
* ---------------------------------------------------------------------------
* !FILE        [  ]
* !PROGRAM     [  ]
* !VERSION     [$Name: P_SRP0007_U_KA_BLB1290_RC1 $]
* !GROUP       [  ]
* !AUTHOR      [$Author: mj $]
* ---------------------------------------------------------------------------
*
*          Copyright (c)           2008 Stollmann E+V GmbH
*                                  Mendelssohnstr. 15
*                                  22761 Hamburg
*                                  Phone: 040/89088-0
*          All Rights Reserved
*
* ---------------------------------------------------------------------------
* !DESCRIPTION
*
*         LTP protocol handler
* ---------------------------------------------------------------------------
* !INDEX
*  ...
* ---------------------------------------------------------------------------
* !CONTENTS
* ---------------------------------------------------------------------------
* !INCLUDE_REFERENCES
* ---------------------------------------------------------------------------
* !HISTORY
*  Date      Author          Comment
*  tt.mm.jj                  Initial revision
*  tt.mm.jj
* ---------------------------------------------------------------------------
*
* $Log: ltplib.c,v $
* Revision 1.61  2014/05/12 09:47:36  mj
* issue #0012459
* Compile with F_LTPLIB_STANDALONE_SUPPORT=0 failed.
*
* Revision 1.60  2014/04/25 13:40:42  ka
* issue 0012122# Prepare SDK release candidate
*
* Revision 1.59  2014/03/28 10:12:23  pm
* issue #0012269: BlueAPI: implement OBEX LTP interface
*
* Revision 1.58  2014/03/28 09:44:35  pm
* issue #00012267: received LTP command can not be handled sometimes
*
* Revision 1.57  2014/03/24 16:10:23  ka
* issue 0012122#
* Create Vendor Project with source base from PM Handover (P_BLB_U_PM_D_20140312)
*
* Revision 1.55.2.2  2014/03/12 07:57:52  pm
* issue #0011680: BlueAPI: implement HID interface
*
* Revision 1.55.2.1  2013/10/18 09:41:12  mn
* issue 0011138
* Non OSIF.
*
* Revision 1.55  2013/09/25 14:33:51  ore
* issue 0010651
* BlueAPI: allow application to set SSP display value for LE authentication
*
* Revision 1.54  2013/09/24 14:18:12  ore
* issue 0008066
* BlueAPI: Support for max TX Power needed
*
* Revision 1.53  2013/09/24 14:08:55  ore
* issue 0008067
* BlueAPI: Support for Absolute RSSI needed
*
* Revision 1.52  2013/09/18 09:50:24  ore
* issue 0008368
* BlueAPI: Add configuration Interface for sniff mode
*
* Revision 1.51  2013/09/18 09:40:00  ore
* issue 0010994
* BlueAPI: add API for link policy configuration
*
* Revision 1.50  2013/08/28 09:06:38  ore
* issue 0010843
* BlueAPI: add pagescan- and linkpolicy configuration
*
* Revision 1.49  2013/08/21 13:37:06  ore
* issue 0010803
* BlueAPI: split up DeviceConfigSetReq
*
* Revision 1.48  2013/07/12 16:14:56  ore
* issue 0009823
* LE: add random resolvable address resolution / privacy mode
*
* Revision 1.47  2013/07/10 14:25:16  ore
* issue 0009823
* LE: add random resolvable address resolution / privacy mode
*
* Revision 1.46  2013/05/28 13:21:05  ore
* issue 0009141
* GATT: extended ATT_WRITE_COMMAND handling
*
* Revision 1.45  2013/04/12 14:51:19  mj
* issue #0009484
* cleanup F_BT_GATT_CLIENT/SERVER flag handling.
*
* Revision 1.44  2013/02/03 15:31:02  ore
* issue 0008536
* LE: remove patching of advertising data with discoverable mode / device name
*
* Revision 1.43  2013/02/03 13:45:09  ore
* issue 0008217
* add GATTMtuSizeInfo
*
* Revision 1.42  2013/01/09 14:16:44  ore
* issue 0008354
* implement LTP BLE/GATT messages
*
* Revision 1.41  2012/11/30 17:05:28  ore
* issue #0006776
* fix for MDH side
*
* Revision 1.40  2012/08/08 10:22:51  or
* correct LTPLibSendDeviceConfigSetReq
*
* Revision 1.39  2012/05/31 12:02:34  odr
* issue #0006776 Add DeviceConfiguration to message interface
* Added DeviceConfigSetReq, DeviceNameSetReq and response messages
*
* Revision 1.38  2012/03/20 08:49:17  odr
* Internal Change 7216: API renaming and cleaning
* Contains changes from API_RENAMED branch
*
* Revision 1.37.4.1  2012/03/06 16:12:47  odr
* - replaced: F_BTMED... -> F_BLUE_API
*
* Revision 1.37  2011/06/30 10:26:18  ore
* merge 1.36.4.4
* - ltplib cleanup & standalone support
*
* Revision 1.36.4.4  2011/06/30 10:14:28  ore
* review with small cleanups
*
* Revision 1.36.4.3  2011/06/03 08:09:00  odr
* Removed copmsk parameter of non deprecated MDH functions
*
* Revision 1.36.4.2  2011/06/03 07:58:33  odr
* Cleanup LTPLibSendMessageDataReq
*
* Revision 1.36.4.1  2011/05/20 08:12:56  odr
* - ltplib cleanup for ieee devkit / porting guide
* - reordering of functions / use generic functions
* - full MDH support
* - standalone support (use internal crc & queue functions)
*
* Revision 1.35  2011/03/07 15:12:20  ore
* cleanup previous commit
*
* Revision 1.34  2011/03/04 17:31:11  ka
* 0005577: function of BTSEC feature request 0005576 shall be made available foe BlueHDP+ and LTP
*
* Revision 1.33  2011/03/02 08:52:49  ore
* add missing DIDDeviceInfo into message table
*
* Revision 1.32  2011/02/17 17:13:33  ore
* 0005853: LTP: use generic header write function in ltplib
*
* Revision 1.31  2011/02/17 16:35:24  ore
* 0005851: LTP: Remove P_CONFIG_CONTROL handling
*
* Revision 1.30  2011/02/10 18:43:03  mj
* 0005817: LTP lib: Remove unused LTPCmdInfo.maxAddLen, <target.h>
* no longer needed.
*
* Revision 1.29  2010/11/30 14:06:46  mn
* Removed warning.
*
* Revision 1.28  2010/08/26 09:17:36  ore
* fix 0005047: LTP: Async ResetReq Parser corrupts data
* - all data shall be forwarded unmodified to the LTP parser
*
* Revision 1.27  2010/08/20 13:17:49  ka
* implement: 0004990: rename 'HDPDevice' related messages to 'DIDDevice'
*
* Revision 1.26  2010/07/21 16:39:17  ore
* fix 0004771: Reconnect acceptance not working
*
* Revision 1.25  2010/06/08 14:12:01  ka
* Fix: 0004380: [LTP] handling of "LTP_NotSupported" Confirmation messages
*
* Revision 1.24  2010/05/14 15:01:11  ka
* - added ACL status info signalling for HDP and LTP
* - added ACL and MDL status info filter compile flags
*
* Revision 1.23  2010/05/05 12:08:53  ka
* - fixed asyncronus ResetReq with CRC
* - fixed missing actInfo after configurator exit
*
* Revision 1.22  2010/04/28 13:10:30  ore
* fix integer overflow with fragmented optional parameters
*
* Revision 1.21  2010/04/20 11:46:14  ore
* flagged out reconnect support (#0004382)
*
* Revision 1.20  2010/04/19 13:48:12  ore
* - add LinkKey to AuthResultInd
* - fix typo
*
* Revision 1.19  2010/04/15 16:41:39  ore
* fix RegSPPMDEPReq
*
* Revision 1.18  2010/04/15 16:06:09  ka
* - bugfix for CRC check with additional optional parameters
* - added max rx-msg as optional to actInfo msg
*
* Revision 1.17  2010/04/15 13:55:19  ore
* add keytype to AuthResultInd and AuthListInfo Msg
*
* Revision 1.16  2010/04/15 12:45:09  ka
* updated LTP module (add CRC, msg check)
*
* Revision 1.15  2010/03/29 09:59:53  ore
* add local_BD to ActInfo
*
* Revision 1.14  2010/03/26 12:38:51  ore
* - add BD to PasskeyNotificationInfo
* - add BD to KeypressNotificationInfo
* - add DisplayValue to UserConfRequestInd
* - add cause/BD to UserConfRequestCnf
*
* Revision 1.13  2010/03/23 18:27:20  ka
* interim version for LTP1.3 bootstrap (introduced auth result handling)
*
* Revision 1.12  2010/03/23 17:59:49  ore
* fix LTPLibSendAuthListInfo
*
* Revision 1.11  2010/03/22 15:22:06  ore
* fix DeviceNameRsp
*
* Revision 1.10  2010/03/22 09:38:57  ore
* fix DeviceNameRsp
*
* Revision 1.9  2010/03/19 12:31:11  ka
* interim version for LTP1.3 bootstrap
*
* Revision 1.8  2010/03/16 17:57:43  ka
* interim version for LTP1.3 bootstrap
*
* Revision 1.7  2009/07/03 06:13:24  pm
* added Config Button (GPIO8)
*
* Revision 1.6  2009/03/26 10:03:59  ka
* added asynchronus LTP_RESET_REQ detection
*
* Revision 1.5  2009/03/13 14:45:14  ka
* - bugfix for messages without parameters (len=4)
* - if BTLTPTgtHandleLTPMessage consumes buffer (no reuse allowed),
*   buffer will NOT be released by LTP lib
* - some text formating
*
* Revision 1.4  2008/10/27 10:59:45  lv
* fix for authentication
*
* Revision 1.3  2008/10/23 13:16:44  lv
* code formatting
*
* Revision 1.2  2008-09-15 11:20:02  lv
* added various ...Send... commands
* toggled TRUE/FALSE return values
* removed comment blocks contained in ltplib.h
* fixed bugs in ...TransferData...
*
* Revision 1.1  2008/08/20 13:34:36  ka
* - introduced LTP-Library
*
*
************************************************************************!KA*/
#include <ltplib.h>
#include "mem.h"
#include "strproc.h"
#include "auto_test.h"
#include "patch_application.h"
#include "aci_low_power.h"

#define LTP_SOURCE_FILE_ID 0x83

/* see LAP_TABLE */

const LTPCmdInfo FAR LTPCmdTable[] =
{
    /* name,                                				min length,                                   					flags */
    /* MDC -> MDH */
    { LTP_CONNECT_MDL_INFO,                 LTP_CONNECT_MDL_INFO_LENGTH,                  LTP_CONNECT_MDL_INFO_FLAGS                  },
    { LTP_CONNECT_MDL_RSP,                  LTP_CONNECT_MDL_RSP_LENGTH,                   LTP_CONNECT_MDL_RSP_FLAGS                   },
    { LTP_CREATE_MDL_CNF,                   LTP_CREATE_MDL_CNF_LENGTH,                    LTP_CREATE_MDL_CNF_FLAGS                    },
    { LTP_DELETE_MDL_INFO,                  LTP_DELETE_MDL_INFO_LENGTH,                   LTP_DELETE_MDL_INFO_FLAGS                   },
    { LTP_DISCONNECT_MDL_RSP,               LTP_DISCONNECT_MDL_RSP_LENGTH,                LTP_DISCONNECT_MDL_RSP_FLAGS                },
    { LTP_DISCONNECT_MDL_CNF,               LTP_DISCONNECT_MDL_CNF_LENGTH,                LTP_DISCONNECT_MDL_CNF_FLAGS                },
    { LTP_REGISTER_STACK_REQ,				LTP_REGISTER_STACK_REQ_LENGTH,				  LTP_REGISTER_STACK_REQ_FLAGS				  },
    { LTP_CONFIG_DLPS_REQ,				    LTP_CONFIG_DLPS_REQ_LENGTH,			          LTP_CONFIG_DLPS_REQ_FLAGS			          },
    { LTP_EXIT_RSP,                         LTP_EXIT_RSP_LENGTH,                          LTP_EXIT_RSP_FLAGS                          },
    { LTP_CONFIG_DLPS_RSP,				    LTP_CONFIG_DLPS_RSP_LENGTH,			          LTP_CONFIG_DLPS_RSP_FLAGS			          },
    { LTP_ACT_INFO,                         LTP_ACT_INFO_LENGTH,                          LTP_ACT_INFO_FLAGS                          },
    { LTP_ACL_STATUS_INFO,                  LTP_ACL_STATUS_INFO_LENGTH,                   LTP_ACL_STATUS_INFO_FLAGS                   },
    //{ LTP_AUTH_REQUEST_CNF,                 LTP_AUTH_REQUEST_CNF_LENGTH,                  LTP_AUTH_REQUEST_CNF_FLAGS                  },
    //{ LTP_REGISTER_HDP_MDEP_RSP,            LTP_REGISTER_HDP_MDEP_RSP_LENGTH,             LTP_REGISTER_HDP_MDEP_RSP_FLAGS             },
    //{ LTP_RELEASE_MDEP_RSP,                 LTP_RELEASE_MDEP_RSP_LENGTH,                  LTP_RELEASE_MDEP_RSP_FLAGS                  },
    { LTP_RESET_RSP,                        LTP_RESET_RSP_LENGTH,                         LTP_RESET_RSP_FLAGS                         },
    //{ LTP_INQUIRY_RSP,                      LTP_INQUIRY_RSP_LENGTH,                       LTP_INQUIRY_RSP_FLAGS                       },
    //{ LTP_INQUIRY_DEVICE_INFO,              LTP_INQUIRY_DEVICE_INFO_LENGTH,               LTP_INQUIRY_DEVICE_INFO_FLAGS               },
    //{ LTP_HDP_DISCOVERY_RSP,                LTP_HDP_DISCOVERY_RSP_LENGTH,                 LTP_HDP_DISCOVERY_RSP_FLAGS                 },
    //{ LTP_DID_DEVICE_INFO,                  LTP_DID_DEVICE_INFO_LENGTH,                   LTP_DID_DEVICE_INFO_FLAGS                   },
    //{ LTP_HDP_SERVICE_INFO,                 LTP_HDP_SERVICE_INFO_LENGTH,                  LTP_HDP_SERVICE_INFO_FLAGS                  },
    //{ LTP_HDP_ENDPOINT_INFO,                LTP_HDP_ENDPOINT_INFO_LENGTH,                 LTP_HDP_ENDPOINT_INFO_FLAGS                 },
    //{ LTP_AUTH_RSP,                         LTP_AUTH_RSP_LENGTH,                          LTP_AUTH_RSP_FLAGS                          },
    //{ LTP_AUTH_RESULT_REQUEST_CNF,          LTP_AUTH_RESULT_REQUEST_CNF_LENGTH,           LTP_AUTH_RESULT_REQUEST_CNF_FLAGS           },
    //{ LTP_AUTH_DELETE_RSP,                  LTP_AUTH_DELETE_RSP_LENGTH,                   LTP_AUTH_DELETE_RSP_FLAGS                   },
    { LTP_INTERNAL_EVENT_INFO,              LTP_INTERNAL_EVENT_INFO_LENGTH,               LTP_INTERNAL_EVENT_INFO_FLAGS               },
    //{ LTP_USER_CONF_REQUEST_CNF,            LTP_USER_CONF_REQUEST_CNF_LENGTH,             LTP_USER_CONF_REQUEST_CNF_FLAGS             },
    { LTP_PASSKEY_REQUEST_CNF,              LTP_PASSKEY_REQUEST_CNF_LENGTH,               LTP_PASSKEY_REQUEST_CNF_FLAGS               },
    { LTP_REMOTE_OOB_REQUEST_CNF,           LTP_REMOTE_OOB_REQUEST_CNF_LENGTH,            LTP_REMOTE_OOB_REQUEST_CNF_FLAGS            },
    { LTP_AUTH_RESULT_CNF,                  LTP_AUTH_RESULT_CNF_LENGTH,                   LTP_AUTH_RESULT_CNF_FLAGS                   },
    { LTP_CONFIG_TUNNEL_RSP,                LTP_CONFIG_TUNNEL_RSP_LENGTH,                 LTP_CONFIG_TUNNEL_RSP_FLAGS                 },
    { LTP_CONFIG_TUNNEL_INFO,               LTP_CONFIG_TUNNEL_INFO_LENGTH,                LTP_CONFIG_TUNNEL_INFO_FLAGS                },
    { LTP_RADIO_MODE_SET_RSP,               LTP_RADIO_MODE_SET_RSP_LENGTH,                LTP_RADIO_MODE_SET_RSP_FLAGS                },
    { LTP_MCL_STATUS_INFO,                  LTP_MCL_STATUS_INFO_LENGTH,                   LTP_MCL_STATUS_INFO_FLAGS                   },
    { LTP_PAIRABLE_MODE_SET_RSP,            LTP_PAIRABLE_MODE_SET_RSP_LENGTH,             LTP_PAIRABLE_MODE_SET_RSP_FLAGS             },
    { LTP_PASSKEY_REQ_REPLY_RSP,            LTP_PASSKEY_REQ_REPLY_RSP_LENGTH,             LTP_PASSKEY_REQ_REPLY_RSP_FLAGS             },
    { LTP_PASSKEY_NOTIFICATION_INFO,        LTP_PASSKEY_NOTIFICATION_INFO_LENGTH,         LTP_PASSKEY_NOTIFICATION_INFO_FLAGS         },
    //{ LTP_KEYPRESS_NOTIFICATION_RSP,        LTP_KEYPRESS_NOTIFICATION_RSP_LENGTH,         LTP_KEYPRESS_NOTIFICATION_RSP_FLAGS         },
    //{ LTP_KEYPRESS_NOTIFICATION_INFO,       LTP_KEYPRESS_NOTIFICATION_INFO_LENGTH,        LTP_KEYPRESS_NOTIFICATION_INFO_FLAGS        },
    //{ LTP_LOCAL_OOB_RSP,                    LTP_LOCAL_OOB_RSP_LENGTH,                     LTP_LOCAL_OOB_RSP_FLAGS                     },
    //{ LTP_AUTH_LIST_RSP,                    LTP_AUTH_LIST_RSP_LENGTH,                     LTP_AUTH_LIST_RSP_FLAGS                     },
    //{ LTP_AUTH_LIST_INFO,                   LTP_AUTH_LIST_INFO_LENGTH,                    LTP_AUTH_LIST_INFO_FLAGS                    },
    //{ LTP_DEVICE_NAME_RSP,                  LTP_DEVICE_NAME_RSP_LENGTH,                   LTP_DEVICE_NAME_RSP_FLAGS                   },
    //{ LTP_SPP_DISCOVERY_RSP,                LTP_SPP_DISCOVERY_RSP_LENGTH,                 LTP_SPP_DISCOVERY_RSP_FLAGS                 },
    //{ LTP_SPP_ENDPOINT_INFO,                LTP_SPP_ENDPOINT_INFO_LENGTH,                 LTP_SPP_ENDPOINT_INFO_FLAGS                 },
    //{ LTP_REGISTER_SPP_MDEP_RSP,            LTP_REGISTER_SPP_MDEP_RSP_LENGTH,             LTP_REGISTER_SPP_MDEP_RSP_FLAGS             },
    { LTP_AUTHORIZATION_REQ_CNF,            LTP_AUTHORIZATION_REQ_CNF_LENGTH,             LTP_AUTHORIZATION_REQ_CNF_FLAGS             },
    { LTP_DEVICE_CONFIG_DEVICE_SET_RSP,     LTP_DEVICE_CONFIG_DEVICE_SET_RSP_LENGTH,      LTP_DEVICE_CONFIG_DEVICE_SET_RSP_FLAGS      },
    { LTP_DEVICE_CONFIG_DID_SET_RSP,        LTP_DEVICE_CONFIG_DID_SET_RSP_LENGTH,         LTP_DEVICE_CONFIG_DID_SET_RSP_FLAGS         },
    { LTP_DEVICE_CONFIG_SECURITY_SET_RSP,   LTP_DEVICE_CONFIG_SECURITY_SET_RSP_LENGTH,    LTP_DEVICE_CONFIG_SECURITY_SET_RSP_FLAGS    },
    { LTP_DEVICE_CONFIG_HDP_SET_RSP,        LTP_DEVICE_CONFIG_HDP_SET_RSP_LENGTH,         LTP_DEVICE_CONFIG_HDP_SET_RSP_FLAGS         },
    //{ LTP_DEVICE_CONFIG_SPP_SET_RSP,        LTP_DEVICE_CONFIG_SPP_SET_RSP_LENGTH,         LTP_DEVICE_CONFIG_SPP_SET_RSP_FLAGS         },
    //{ LTP_DEVICE_CONFIG_PAGESCAN_SET_RSP,   LTP_DEVICE_CONFIG_PAGESCAN_SET_RSP_LENGTH,    LTP_DEVICE_CONFIG_PAGESCAN_SET_RSP_FLAGS    },
    //{ LTP_DEVICE_CONFIG_LINKPOLICY_SET_RSP, LTP_DEVICE_CONFIG_LINKPOLICY_SET_RSP_LENGTH,  LTP_DEVICE_CONFIG_LINKPOLICY_SET_RSP_FLAGS  },
    //{ LTP_DEVICE_CONFIG_MAXTXPOWER_SET_RSP, LTP_DEVICE_CONFIG_MAXTXPOWER_SET_RSP_LENGTH,  LTP_DEVICE_CONFIG_MAXTXPOWER_SET_RSP_FLAGS  },
    /* DATA */
    { LTP_DATA_UNSEGMENTED,                 LTP_DATA_UNSEGMENTED_LENGTH,                  LTP_DATA_UNSEGMENTED_FLAGS                  },
    { LTP_DATA_START_SEGMENT,               LTP_DATA_START_SEGMENT_LENGTH,                LTP_DATA_START_SEGMENT_FLAGS                },
    { LTP_DATA_END_SEGMENT,                 LTP_DATA_END_SEGMENT_LENGTH,                  LTP_DATA_END_SEGMENT_FLAGS                  },
    { LTP_DATA_CONTINUE_SEGMENT,            LTP_DATA_CONTINUE_SEGMENT_LENGTH,             LTP_DATA_CONTINUE_SEGMENT_FLAGS             },
    /* MDC -> MDH */
    { LTP_CONNECT_GATT_MDL_RSP,             LTP_CONNECT_GATT_MDL_RSP_LENGTH,              LTP_CONNECT_GATT_MDL_RSP_FLAGS              },
    { LTP_GATT_SERVICE_REGISTER_RSP,        LTP_GATT_SERVICE_REGISTER_RSP_LENGTH,         LTP_GATT_SERVICE_REGISTER_RSP_FLAGS         },
    { LTP_GATT_SERVICE_RELEASE_RSP,         LTP_GATT_SERVICE_RELEASE_RSP_LENGTH,          LTP_GATT_SERVICE_RELEASE_RSP_FLAGS          },
    { LTP_GATT_ATTRIBUTE_UPDATE_RSP,        LTP_GATT_ATTRIBUTE_UPDATE_RSP_LENGTH,         LTP_GATT_ATTRIBUTE_UPDATE_RSP_FLAGS         },
    { LTP_GATT_ATTRIBUTE_UPDATE_STATUS_CNF, LTP_GATT_ATTRIBUTE_UPDATE_STATUS_CNF_LENGTH,  LTP_GATT_ATTRIBUTE_UPDATE_STATUS_CNF_FLAGS  },
    { LTP_GATT_ATTRIBUTE_READ_CNF,          LTP_GATT_ATTRIBUTE_READ_CNF_LENGTH,           LTP_GATT_ATTRIBUTE_READ_CNF_FLAGS           },
    { LTP_GATT_ATTRIBUTE_WRITE_CNF,         LTP_GATT_ATTRIBUTE_WRITE_CNF_LENGTH,          LTP_GATT_ATTRIBUTE_WRITE_CNF_FLAGS          },
    { LTP_GATT_CCCD_INFO,                   LTP_GATT_CCCD_INFO_LENGTH,                    LTP_GATT_CCCD_INFO_FLAGS                    },
    { LTP_GATT_DISCOVERY_RSP,               LTP_GATT_DISCOVERY_RSP_LENGTH,                LTP_GATT_DISCOVERY_RSP_FLAGS                },
    { LTP_GATT_DISCOVERY_CNF,               LTP_GATT_DISCOVERY_CNF_LENGTH,                LTP_GATT_DISCOVERY_CNF_FLAGS                },
    { LTP_GATT_ATTRIBUTE_READ_RSP,          LTP_GATT_ATTRIBUTE_READ_RSP_LENGTH,           LTP_GATT_ATTRIBUTE_READ_RSP_FLAGS           },
    { LTP_GATT_ATTRIBUTE_WRITE_RSP,         LTP_GATT_ATTRIBUTE_WRITE_RSP_LENGTH,          LTP_GATT_ATTRIBUTE_WRITE_RSP_FLAGS          },
    { LTP_GATT_ATTRIBUTE_CNF,               LTP_GATT_ATTRIBUTE_CNF_LENGTH,                LTP_GATT_ATTRIBUTE_CNF_FLAGS                },
    { LTP_GATT_ATTRIBUTE_NOTIFICATION_INFO, LTP_GATT_ATTRIBUTE_NOTIFICATION_INFO_LENGTH,  LTP_GATT_ATTRIBUTE_NOTIFICATION_INFO_FLAGS  },
    //{ LTP_GATT_SDP_DISCOVERY_RSP,           LTP_GATT_SDP_DISCOVERY_RSP_LENGTH,            LTP_GATT_SDP_DISCOVERY_RSP_FLAGS            },
    //{ LTP_GATT_SDP_DISCOVERY_INFO,          LTP_GATT_SDP_DISCOVERY_INFO_LENGTH,           LTP_GATT_SDP_DISCOVERY_INFO_FLAGS           },
    { LTP_LE_ADVERTISE_RSP,                 LTP_LE_ADVERTISE_RSP_LENGTH,                  LTP_LE_ADVERTISE_RSP_FLAGS                  },
    { LTP_LE_ADVERTISE_PARAMETER_SET_RSP,   LTP_LE_ADVERTISE_PARAMETER_SET_RSP_LENGTH,    LTP_LE_ADVERTISE_PARAMETER_SET_RSP_FLAGS    },
    { LTP_LE_ADVERTISE_DATA_SET_RSP,        LTP_LE_ADVERTISE_DATA_SET_RSP_LENGTH,         LTP_LE_ADVERTISE_DATA_SET_RSP_FLAGS         },
    { LTP_LE_SCAN_RSP,                      LTP_LE_SCAN_RSP_LENGTH,                       LTP_LE_SCAN_RSP_FLAGS                       },
    { LTP_LE_SCAN_INFO,                     LTP_LE_SCAN_INFO_LENGTH,                      LTP_LE_SCAN_INFO_FLAGS                      },
    { LTP_LE_MODIFY_WHITELIST_RSP,          LTP_LE_MODIFY_WHITELIST_RSP_LENGTH,           LTP_LE_MODIFY_WHITELIST_RSP_FLAGS           },
    { LTP_LE_CONNECTION_UPDATE_RSP,         LTP_LE_CONNECTION_UPDATE_RSP_LENGTH,          LTP_LE_CONNECTION_UPDATE_RSP_FLAGS          },
    { LTP_LE_CONNECTION_UPDATE_CNF,         LTP_LE_CONNECTION_UPDATE_CNF_LENGTH,          LTP_LE_CONNECTION_UPDATE_CNF_FLAGS          },
    { LTP_LE_CONNECTION_PARAMETER_INFO,     LTP_LE_CONNECTION_PARAMETER_INFO_LENGTH,      LTP_LE_CONNECTION_PARAMETER_INFO_FLAGS      },
    { LTP_GATT_SERVER_STORE_CNF,            LTP_GATT_SERVER_STORE_CNF_LENGTH,             LTP_GATT_SERVER_STORE_CNF_FLAGS             },
    { LTP_AUTH_RESULT_EXT_CNF,              LTP_AUTH_RESULT_EXT_CNF_LENGTH,               LTP_AUTH_RESULT_EXT_CNF_FLAGS               },
    { LTP_AUTH_RESULT_REQUEST_EXT_CNF,      LTP_AUTH_RESULT_REQUEST_EXT_CNF_LENGTH,       LTP_AUTH_RESULT_REQUEST_EXT_CNF_FLAGS       },
    { LTP_GATT_SECURITY_RSP,                LTP_GATT_SECURITY_RSP_LENGTH,                 LTP_GATT_SECURITY_RSP_FLAGS                 },
    { LTP_GATT_MTU_INFO,                    LTP_GATT_MTU_INFO_LENGTH,                     LTP_GATT_MTU_INFO_FLAGS                     },
    { LTP_GATT_ATTRIBUTE_WRITE_COMMAND_INFO, LTP_GATT_ATTRIBUTE_WRITE_COMMAND_INFO_LENGTH, LTP_GATT_ATTRIBUTE_WRITE_COMMAND_INFO_FLAGS },
    { LTP_LE_PRIVACY_MODE_RSP,              LTP_LE_PRIVACY_MODE_RSP_LENGTH,               LTP_LE_PRIVACY_MODE_RSP_FLAGS               },
    { LTP_ACL_BD_RESOLVED_INFO,             LTP_ACL_BD_RESOLVED_INFO_LENGTH,              LTP_ACL_BD_RESOLVED_INFO_FLAGS              },
    { LTP_ACL_CONFIG_LINKPOLICY_RSP,        LTP_ACL_CONFIG_LINKPOLICY_RSP_LENGTH,         LTP_ACL_CONFIG_LINKPOLICY_RSP_FLAGS         },
    { LTP_ACL_CONFIG_SNIFFMODE_RSP,         LTP_ACL_CONFIG_SNIFFMODE_RSP_LENGTH,          LTP_ACL_CONFIG_SNIFFMODE_RSP_FLAGS          },
    //{ LTP_ACL_SNIFF_SUBRATE_INFO,           LTP_ACL_SNIFF_SUBRATE_INFO_LENGTH,            LTP_ACL_SNIFF_SUBRATE_INFO_FLAGS            },
    { LTP_ACL_CONFIG_LINKSTATUS_RSP,        LTP_ACL_CONFIG_LINKSTATUS_RSP_LENGTH,         LTP_ACL_CONFIG_LINKSTATUS_RSP_FLAGS         },
    { LTP_ACL_LINKSTATUS_INFO,              LTP_ACL_LINKSTATUS_INFO_LENGTH,               LTP_ACL_LINKSTATUS_INFO_FLAGS               },
    /* MDH -> MDC */
    { LTP_CONNECT_MDL_REQ,                  LTP_CONNECT_MDL_REQ_LENGTH,                   LTP_CONNECT_MDL_REQ_FLAGS                   },
    { LTP_CREATE_MDL_IND,                   LTP_CREATE_MDL_IND_LENGTH,                    LTP_CREATE_MDL_IND_FLAGS                    },
    { LTP_DISCONNECT_MDL_REQ,               LTP_DISCONNECT_MDL_REQ_LENGTH,                LTP_DISCONNECT_MDL_REQ_FLAGS                },
    { LTP_DISCONNECT_MDL_IND,               LTP_DISCONNECT_MDL_IND_LENGTH,                LTP_DISCONNECT_MDL_IND_FLAGS                },
    { LTP_RECONNECT_MDL_REQ,                LTP_RECONNECT_MDL_REQ_LENGTH,                 LTP_RECONNECT_MDL_REQ_FLAGS                 },
    { LTP_RECONNECT_MDL_IND,                LTP_RECONNECT_MDL_IND_LENGTH,                 LTP_RECONNECT_MDL_IND_FLAGS                 },
    { LTP_EXIT_REQ,                         LTP_EXIT_REQ_LENGTH,                          LTP_EXIT_REQ_FLAGS                          },
    { LTP_AUTH_REQUEST_IND,                 LTP_AUTH_REQUEST_IND_LENGTH,                  LTP_AUTH_REQUEST_IND_FLAGS                  },
    { LTP_REGISTER_HDP_MDEP_REQ,            LTP_REGISTER_HDP_MDEP_REQ_LENGTH,             LTP_REGISTER_HDP_MDEP_REQ_FLAGS             },
    { LTP_RELEASE_MDEP_REQ,                 LTP_RELEASE_MDEP_REQ_LENGTH,                  LTP_RELEASE_MDEP_REQ_FLAGS                  },
    { LTP_RESET_REQ,                        LTP_RESET_REQ_LENGTH,                         LTP_RESET_REQ_FLAGS                         },
    //{ LTP_INQUIRY_REQ,                      LTP_INQUIRY_REQ_LENGTH,                       LTP_INQUIRY_REQ_FLAGS                       },
    //{ LTP_HDP_DISCOVERY_REQ,                LTP_HDP_DISCOVERY_REQ_LENGTH,                 LTP_HDP_DISCOVERY_REQ_FLAGS                 },
    { LTP_AUTH_REQ,                         LTP_AUTH_REQ_LENGTH,                          LTP_AUTH_REQ_FLAGS                          },
    { LTP_AUTH_RESULT_REQUEST_IND,          LTP_AUTH_RESULT_REQUEST_IND_LENGTH,           LTP_AUTH_RESULT_REQUEST_IND_FLAGS           },
    { LTP_AUTH_DELETE_REQ,                  LTP_AUTH_DELETE_REQ_LENGTH,                   LTP_AUTH_DELETE_REQ_FLAGS                   },
    { LTP_USER_CONF_REQUEST_IND,            LTP_USER_CONF_REQUEST_IND_LENGTH,             LTP_USER_CONF_REQUEST_IND_FLAGS             },
    { LTP_PASSKEY_REQUEST_IND,              LTP_PASSKEY_REQUEST_IND_LENGTH,               LTP_PASSKEY_REQUEST_IND_FLAGS               },
    { LTP_REMOTE_OOB_REQUEST_IND,           LTP_REMOTE_OOB_REQUEST_IND_LENGTH,            LTP_REMOTE_OOB_REQUEST_IND_FLAGS            },
    { LTP_AUTH_RESULT_IND,                  LTP_AUTH_RESULT_IND_LENGTH,                   LTP_AUTH_RESULT_IND_FLAGS                   },
    { LTP_CONFIG_TUNNEL_REQ,                LTP_CONFIG_TUNNEL_REQ_LENGTH,                 LTP_CONFIG_TUNNEL_REQ_FLAGS                 },
    { LTP_RADIO_MODE_SET_REQ,               LTP_RADIO_MODE_SET_REQ_LENGTH,                LTP_RADIO_MODE_SET_REQ_FLAGS                },
    { LTP_PAIRABLE_MODE_SET_REQ,            LTP_PAIRABLE_MODE_SET_REQ_LENGTH,             LTP_PAIRABLE_MODE_SET_REQ_FLAGS             },
    { LTP_PASSKEY_REQ_REPLY_REQ,            LTP_PASSKEY_REQ_REPLY_REQ_LENGTH,             LTP_PASSKEY_REQ_REPLY_REQ_FLAGS             },
    //{ LTP_KEYPRESS_NOTIFICATION_REQ,        LTP_KEYPRESS_NOTIFICATION_REQ_LENGTH,         LTP_KEYPRESS_NOTIFICATION_REQ_FLAGS         },
    //{ LTP_LOCAL_OOB_REQ,                    LTP_LOCAL_OOB_REQ_LENGTH,                     LTP_LOCAL_OOB_REQ_FLAGS                     },
    //{ LTP_AUTH_LIST_REQ,                    LTP_AUTH_LIST_REQ_LENGTH,                     LTP_AUTH_LIST_REQ_FLAGS                     },
    { LTP_DEVICE_NAME_REQ,                  LTP_DEVICE_NAME_REQ_LENGTH,                   LTP_DEVICE_NAME_REQ_FLAGS                   },
    //{ LTP_SPP_DISCOVERY_REQ,                LTP_SPP_DISCOVERY_REQ_LENGTH,                 LTP_SPP_DISCOVERY_REQ_FLAGS                 },
    //{ LTP_REGISTER_SPP_MDEP_REQ,            LTP_REGISTER_SPP_MDEP_REQ_LENGTH,             LTP_REGISTER_SPP_MDEP_REQ_FLAGS             },
    //{ LTP_AUTHORIZATION_REQ_IND,            LTP_AUTHORIZATION_REQ_IND_LENGTH,             LTP_AUTHORIZATION_REQ_IND_FLAGS             },
    { LTP_DEVICE_CONFIG_DEVICE_SET_REQ,     LTP_DEVICE_CONFIG_DEVICE_SET_REQ_LENGTH,      LTP_DEVICE_CONFIG_DEVICE_SET_REQ_FLAGS      },
    { LTP_DEVICE_CONFIG_DID_SET_REQ,        LTP_DEVICE_CONFIG_DID_SET_REQ_LENGTH,         LTP_DEVICE_CONFIG_DID_SET_REQ_FLAGS         },
    { LTP_DEVICE_CONFIG_SECURITY_SET_REQ,   LTP_DEVICE_CONFIG_SECURITY_SET_REQ_LENGTH,    LTP_DEVICE_CONFIG_SECURITY_SET_REQ_FLAGS    },
    { LTP_DEVICE_CONFIG_HDP_SET_REQ,        LTP_DEVICE_CONFIG_HDP_SET_REQ_LENGTH,         LTP_DEVICE_CONFIG_HDP_SET_REQ_FLAGS         },
    //{ LTP_DEVICE_CONFIG_SPP_SET_REQ,        LTP_DEVICE_CONFIG_SPP_SET_REQ_LENGTH,         LTP_DEVICE_CONFIG_SPP_SET_REQ_FLAGS         },
    //{ LTP_DEVICE_CONFIG_PAGESCAN_SET_REQ,   LTP_DEVICE_CONFIG_PAGESCAN_SET_REQ_LENGTH,    LTP_DEVICE_CONFIG_PAGESCAN_SET_REQ_FLAGS    },
    { LTP_DEVICE_CONFIG_LINKPOLICY_SET_REQ, LTP_DEVICE_CONFIG_LINKPOLICY_SET_REQ_LENGTH,  LTP_DEVICE_CONFIG_LINKPOLICY_SET_REQ_FLAGS  },
    { LTP_DEVICE_CONFIG_MAXTXPOWER_SET_REQ, LTP_DEVICE_CONFIG_MAXTXPOWER_SET_REQ_LENGTH,  LTP_DEVICE_CONFIG_MAXTXPOWER_SET_REQ_FLAGS  },
    { LTP_REGISTER_HID_MDEP_REQ,            LTP_REGISTER_HID_MDEP_REQ_LENGTH,             LTP_REGISTER_HID_MDEP_REQ_FLAGS             },
    { LTP_REGISTER_HID_MDEP_RSP,            LTP_REGISTER_HID_MDEP_RSP_LENGTH,             LTP_REGISTER_HID_MDEP_RSP_FLAGS             },  /* MDC -> MDH */
    //{ LTP_HID_MESSAGE_REQ,                  LTP_HID_MESSAGE_REQ_LENGTH,                   LTP_HID_MESSAGE_REQ_FLAGS                   },
    //{ LTP_HID_MESSAGE_RSP,                  LTP_HID_MESSAGE_RSP_LENGTH,                   LTP_HID_MESSAGE_RSP_FLAGS                   },  /* MDC -> MDH */
    //{ LTP_HID_MESSAGE_CONF,                 LTP_HID_MESSAGE_CONF_LENGTH,                  LTP_HID_MESSAGE_CONF_FLAGS                  },
    //{ LTP_HID_MESSAGE_IND,                  LTP_HID_MESSAGE_IND_LENGTH,                   LTP_HID_MESSAGE_IND_FLAGS                   },  /* MDC -> MDH */
    //{ LTP_REGISTER_OBEX_MDEP_REQ,           LTP_REGISTER_OBEX_MDEP_REQ_LENGTH,            LTP_REGISTER_OBEX_MDEP_REQ_FLAGS            },
    //{ LTP_REGISTER_OBEX_MDEP_RSP,           LTP_REGISTER_OBEX_MDEP_RSP_LENGTH,            LTP_REGISTER_OBEX_MDEP_RSP_FLAGS            },  /* MDC -> MDH */
    //{ LTP_OBEX_DISCOVERY_REQ,               LTP_OBEX_DISCOVERY_REQ_LENGTH,                LTP_OBEX_DISCOVERY_REQ_FLAGS                          },
    //{ LTP_OBEX_DISCOVERY_RSP,               LTP_OBEX_DISCOVERY_RSP_LENGTH,                LTP_OBEX_DISCOVERY_RSP_FLAGS                          },  /* MDC -> MDH */
    //{ LTP_OBEX_ENDPOINT_CONF,               LTP_OBEX_ENDPOINT_CONF_LENGTH,                LTP_OBEX_ENDPOINT_CONF_FLAGS                          },
    //{ LTP_OBEX_ENDPOINT_IND,                LTP_OBEX_ENDPOINT_IND_LENGTH,                 LTP_OBEX_ENDPOINT_IND_FLAGS                           },  /* MDC -> MDH */
    { LTP_CONNECT_GATT_MDL_REQ,             LTP_CONNECT_GATT_MDL_REQ_LENGTH,              LTP_CONNECT_GATT_MDL_REQ_FLAGS              },
    { LTP_GATT_SERVICE_REGISTER_REQ,        LTP_GATT_SERVICE_REGISTER_REQ_LENGTH,         LTP_GATT_SERVICE_REGISTER_REQ_FLAGS         },
    { LTP_GATT_SERVICE_RELEASE_REQ,         LTP_GATT_SERVICE_RELEASE_REQ_LENGTH,          LTP_GATT_SERVICE_RELEASE_REQ_FLAGS          },
    { LTP_GATT_ATTRIBUTE_UPDATE_REQ,        LTP_GATT_ATTRIBUTE_UPDATE_REQ_LENGTH,         LTP_GATT_ATTRIBUTE_UPDATE_REQ_FLAGS         },
    { LTP_GATT_ATTRIBUTE_UPDATE_STATUS_IND, LTP_GATT_ATTRIBUTE_UPDATE_STATUS_IND_LENGTH,  LTP_GATT_ATTRIBUTE_UPDATE_STATUS_IND_FLAGS  },
    { LTP_GATT_ATTRIBUTE_READ_IND,          LTP_GATT_ATTRIBUTE_READ_IND_LENGTH,           LTP_GATT_ATTRIBUTE_READ_IND_FLAGS           },
    { LTP_GATT_ATTRIBUTE_WRITE_IND,         LTP_GATT_ATTRIBUTE_WRITE_IND_LENGTH,          LTP_GATT_ATTRIBUTE_WRITE_IND_FLAGS          },
    { LTP_GATT_DISCOVERY_REQ,               LTP_GATT_DISCOVERY_REQ_LENGTH,                LTP_GATT_DISCOVERY_REQ_FLAGS                },
    { LTP_GATT_DISCOVERY_IND,               LTP_GATT_DISCOVERY_IND_LENGTH,                LTP_GATT_DISCOVERY_IND_FLAGS                },
    { LTP_GATT_ATTRIBUTE_READ_REQ,          LTP_GATT_ATTRIBUTE_READ_REQ_LENGTH,           LTP_GATT_ATTRIBUTE_READ_REQ_FLAGS           },
    { LTP_GATT_ATTRIBUTE_WRITE_REQ,         LTP_GATT_ATTRIBUTE_WRITE_REQ_LENGTH,          LTP_GATT_ATTRIBUTE_WRITE_REQ_FLAGS          },
    { LTP_GATT_ATTRIBUTE_IND,               LTP_GATT_ATTRIBUTE_IND_LENGTH,                LTP_GATT_ATTRIBUTE_IND_FLAGS                },
    //{ LTP_GATT_SDP_DISCOVERY_REQ,           LTP_GATT_SDP_DISCOVERY_REQ_LENGTH,            LTP_GATT_SDP_DISCOVERY_REQ_FLAGS            },
    { LTP_LE_ADVERTISE_REQ,                 LTP_LE_ADVERTISE_REQ_LENGTH,                  LTP_LE_ADVERTISE_REQ_FLAGS                  },
    { LTP_LE_ADVERTISE_PARAMETER_SET_REQ,   LTP_LE_ADVERTISE_PARAMETER_SET_REQ_LENGTH,    LTP_LE_ADVERTISE_PARAMETER_SET_REQ_FLAGS    },
    { LTP_LE_ADVERTISE_DATA_SET_REQ,        LTP_LE_ADVERTISE_DATA_SET_REQ_LENGTH,         LTP_LE_ADVERTISE_DATA_SET_REQ_FLAGS         },
    { LTP_LE_SCAN_REQ,                      LTP_LE_SCAN_REQ_LENGTH,                       LTP_LE_SCAN_REQ_FLAGS                       },
    { LTP_LE_MODIFY_WHITELIST_REQ,          LTP_LE_MODIFY_WHITELIST_REQ_LENGTH,           LTP_LE_MODIFY_WHITELIST_REQ_FLAGS           },
    { LTP_LE_CONNECTION_UPDATE_REQ,         LTP_LE_CONNECTION_UPDATE_REQ_LENGTH,          LTP_LE_CONNECTION_UPDATE_REQ_FLAGS          },
    { LTP_LE_CONNECTION_UPDATE_IND,         LTP_LE_CONNECTION_UPDATE_IND_LENGTH,          LTP_LE_CONNECTION_UPDATE_IND_FLAGS          },
    { LTP_GATT_SERVER_STORE_IND,            LTP_GATT_SERVER_STORE_IND_LENGTH,             LTP_GATT_SERVER_STORE_IND_FLAGS             },
    { LTP_AUTH_RESULT_EXT_IND,              LTP_AUTH_RESULT_EXT_IND_LENGTH,               LTP_AUTH_RESULT_EXT_IND_FLAGS               },
    { LTP_AUTH_RESULT_REQUEST_EXT_IND,      LTP_AUTH_RESULT_REQUEST_EXT_IND_LENGTH,       LTP_AUTH_RESULT_REQUEST_EXT_IND_FLAGS       },
    { LTP_GATT_SECURITY_REQ,                LTP_GATT_SECURITY_REQ_LENGTH,                 LTP_GATT_SECURITY_REQ_FLAGS                 },
    { LTP_LE_PRIVACY_MODE_REQ,              LTP_LE_PRIVACY_MODE_REQ_LENGTH,               LTP_LE_PRIVACY_MODE_REQ_FLAGS               },
    //{ LTP_ACL_CONFIG_LINKPOLICY_REQ,        LTP_ACL_CONFIG_LINKPOLICY_REQ_LENGTH,         LTP_ACL_CONFIG_LINKPOLICY_REQ_FLAGS         },
    //{ LTP_ACL_CONFIG_SNIFFMODE_REQ,         LTP_ACL_CONFIG_SNIFFMODE_REQ_LENGTH,          LTP_ACL_CONFIG_SNIFFMODE_REQ_FLAGS          },
    //{ LTP_ACL_CONFIG_LINKSTATUS_REQ,        LTP_ACL_CONFIG_LINKSTATUS_REQ_LENGTH,         LTP_ACL_CONFIG_LINKSTATUS_REQ_FLAGS         },
    { LTP_OPCODE_RESERVED,                  0,                                            0                                           },
};

#if F_LTPLIB_STANDALONE_SUPPORT
/*--------------------------------------------------------------------------*/
/* FCS lookup table.                                                        */
/* generator polynomial: x**8 + x**2 + x + 1                                */
/* -------------------------------------------------------------------------*/
//STATIC const BYTE FAR crc8EtsTable[256] =
static const BYTE crc8EtsTable[256] =
{
    0x00, 0x91, 0xE3, 0x72, 0x07, 0x96, 0xE4, 0x75,
    0x0E, 0x9F, 0xED, 0x7C, 0x09, 0x98, 0xEA, 0x7B,
    0x1C, 0x8D, 0xFF, 0x6E, 0x1B, 0x8A, 0xF8, 0x69,
    0x12, 0x83, 0xF1, 0x60, 0x15, 0x84, 0xF6, 0x67,
    0x38, 0xA9, 0xDB, 0x4A, 0x3F, 0xAE, 0xDC, 0x4D,
    0x36, 0xA7, 0xD5, 0x44, 0x31, 0xA0, 0xD2, 0x43,
    0x24, 0xB5, 0xC7, 0x56, 0x23, 0xB2, 0xC0, 0x51,
    0x2A, 0xBB, 0xC9, 0x58, 0x2D, 0xBC, 0xCE, 0x5F,
    0x70, 0xE1, 0x93, 0x02, 0x77, 0xE6, 0x94, 0x05,
    0x7E, 0xEF, 0x9D, 0x0C, 0x79, 0xE8, 0x9A, 0x0B,
    0x6C, 0xFD, 0x8F, 0x1E, 0x6B, 0xFA, 0x88, 0x19,
    0x62, 0xF3, 0x81, 0x10, 0x65, 0xF4, 0x86, 0x17,
    0x48, 0xD9, 0xAB, 0x3A, 0x4F, 0xDE, 0xAC, 0x3D,
    0x46, 0xD7, 0xA5, 0x34, 0x41, 0xD0, 0xA2, 0x33,
    0x54, 0xC5, 0xB7, 0x26, 0x53, 0xC2, 0xB0, 0x21,
    0x5A, 0xCB, 0xB9, 0x28, 0x5D, 0xCC, 0xBE, 0x2F,
    0xE0, 0x71, 0x03, 0x92, 0xE7, 0x76, 0x04, 0x95,
    0xEE, 0x7F, 0x0D, 0x9C, 0xE9, 0x78, 0x0A, 0x9B,
    0xFC, 0x6D, 0x1F, 0x8E, 0xFB, 0x6A, 0x18, 0x89,
    0xF2, 0x63, 0x11, 0x80, 0xF5, 0x64, 0x16, 0x87,
    0xD8, 0x49, 0x3B, 0xAA, 0xDF, 0x4E, 0x3C, 0xAD,
    0xD6, 0x47, 0x35, 0xA4, 0xD1, 0x40, 0x32, 0xA3,
    0xC4, 0x55, 0x27, 0xB6, 0xC3, 0x52, 0x20, 0xB1,
    0xCA, 0x5B, 0x29, 0xB8, 0xCD, 0x5C, 0x2E, 0xBF,
    0x90, 0x01, 0x73, 0xE2, 0x97, 0x06, 0x74, 0xE5,
    0x9E, 0x0F, 0x7D, 0xEC, 0x99, 0x08, 0x7A, 0xEB,
    0x8C, 0x1D, 0x6F, 0xFE, 0x8B, 0x1A, 0x68, 0xF9,
    0x82, 0x13, 0x61, 0xF0, 0x85, 0x14, 0x66, 0xF7,
    0xA8, 0x39, 0x4B, 0xDA, 0xAF, 0x3E, 0x4C, 0xDD,
    0xA6, 0x37, 0x45, 0xD4, 0xA1, 0x30, 0x42, 0xD3,
    0xB4, 0x25, 0x57, 0xC6, 0xB3, 0x22, 0x50, 0xC1,
    0xBA, 0x2B, 0x59, 0xC8, 0xBD, 0x2C, 0x5E, 0xCF
}; /* end of crc8EtsTable */


/****************************************************************************/

BYTE BTLTPTgtDoCRC8(LTP_TGT_APPHANDLE AppHandle, LPBYTE pStart, WORD length)
{
    BYTE fcs = 0xff;

    while (length--)
    {
        fcs = crc8EtsTable[fcs ^ *pStart++];
    }
    return 0xff - fcs;
}

void ltpQueueIn(LTP_QUEUE_P QueuePtr, void *pQueueElement)
{
    LTP_ELEMENT_P QueueElementPtr = (LTP_ELEMENT_P)pQueueElement;
    LTP_ELEMENT_P LastPtr;

    if ((LastPtr = QueuePtr->Last) == (LTP_ELEMENT_P)0)    /* if queue is empty,  */
        QueuePtr->First = QueueElementPtr;    /* q->first = q->last = new entry */
    else                                    /* if it is not empty, new entry  */
        LastPtr->Next  = QueueElementPtr;     /* is next from last entry        */
    QueuePtr->Last = QueueElementPtr;
    QueueElementPtr->Next = (LTP_ELEMENT_P)0;
    QueuePtr->ElementCount++;               /* increment element count        */
}


void *ltpQueueOut(LTP_QUEUE_P QueuePtr)
{
    LTP_ELEMENT_P FirstPtr;

    if ((FirstPtr = QueuePtr->First) != (LTP_ELEMENT_P)0)
    {
        /* if queue not empty and    */
        /* it is the last entry      */
        if ((QueuePtr->First = FirstPtr->Next) == (LTP_ELEMENT_P)0)
            QueuePtr->Last = (LTP_ELEMENT_P)0;           /* set queue empty           */
        QueuePtr->ElementCount--;                  /* decrement element count   */
    }
    return (FirstPtr);
}
#else
void ltpQueueIn(LTP_QUEUE_P QueuePtr, void *pQueueElement)
{
    QueueIn(QueuePtr, pQueueElement);
}

void *ltpQueueOut(LTP_QUEUE_P QueuePtr)
{
    return ( QueueOut(QueuePtr) );
}
#endif /* !F_LTPLIB_STANDALONE_SUPPORT */

/****************************************************************************/

PLTPCmdInfo BTLTPGetMsgProperty(BYTE opcode)
{
	if(NULL != pPatch_Ltp_BTLTPGetMsgProperty)
	{
		return (PLTPCmdInfo)pPatch_Ltp_BTLTPGetMsgProperty(opcode);
	}
	
    BYTE minTabPos = 0;
    //BYTE maxTabPos = (BYTE)(sizeof(LTPCmdTable) / sizeof(LTPCmdInfo));		//M0 no divider
    BYTE maxTabPos = 124;
    BYTE tabPos    = 0;
    BYTE oldTabPos;

    while (TRUE)
    {
        oldTabPos = tabPos;
        tabPos    = minTabPos + ((maxTabPos - minTabPos) >> 1);	/* /2 */

        if (LTPCmdTable[tabPos].opcode == opcode)
        {
            return (PLTPCmdInfo) & (LTPCmdTable[tabPos]);
        }
        else if (LTPCmdTable[tabPos].opcode > opcode)
        {
            maxTabPos = tabPos;
        }
        else if (LTPCmdTable[tabPos].opcode < opcode)
        {
            minTabPos = tabPos;
        }

        if (oldTabPos == tabPos)
        {
            return NULL;
        }
    } /* end of while */
} /* end of BTLTPGetMsgProperty */


BOOL BTLTPTransferLTPElementData(PLTPLib pLTPLib, WORD copyLength)
{
    BOOL        retVal = FALSE;     /* ==> all requested data copied */
    PLTPElement pActiveElement = pLTPLib->pActiveElement;

    if (pActiveElement == NULL)
    {
        return TRUE;    /* ==> new queue element required                       */
    }

    if (copyLength > pActiveElement->DataCB.Length)
    {
        copyLength = pActiveElement->DataCB.Length;
        retVal = TRUE;    /* ==> not enough data in element!!!!!!                     */
    }

    /* copy element data to msg buffer                                        */
    memcpy(&pLTPLib->pLTPMsg[pLTPLib->LTPMsgPos],
           &pActiveElement->DataCB.BufferAddress[pActiveElement->DataCB.Offset],
           copyLength
          );

    /* updata data structures for element and msg buffer                      */
    pLTPLib->LTPDataCollected += copyLength;
    pLTPLib->LTPMsgPos        += copyLength;

    pActiveElement->DataCB.Offset += copyLength;
    pActiveElement->DataCB.Length -= copyLength;

    /* check if element is consumed completely                                */
    if (!pActiveElement->DataCB.Length)
    {
        BTLTPTgtReceiveBufferRelease(pLTPLib->AppHandle, pActiveElement->DataCB.BufferAddress);

        BTLTPTgtQueueElementRelease(pLTPLib->AppHandle, pActiveElement);

        pLTPLib->pActiveElement = NULL;
    }

    return retVal;
} /* end of BTLTPTransferLTPElementData */


void BTLTPInitLTPAssembly(PLTPLib pLTPLib, BOOL reUseBuffer, BOOL releaseBuffer)
{
    if (reUseBuffer)
    {
        pLTPLib->LTPMsgStart      = pLTPLib->ReceiveOffset;
        pLTPLib->LTPMsgPos        = pLTPLib->ReceiveOffset;
        pLTPLib->LTPDataCollected = 0;
        pLTPLib->LTPMsgLength     = 0; /* not known */
        //DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "BTLTPInitLTPAssembly:reuse buffer: = 0x%8x", 1, pLTPLib->pLTPMsg);
    }
    else
    {
        if (releaseBuffer)
        {
        	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "BTLTPInitLTPAssembly: release pLTPLib->pLTPMsg = ", 1, pLTPLib->pLTPMsg);
            BTLTPTgtAssemblyBufferRelease(pLTPLib->AppHandle, pLTPLib->pLTPMsg);
        }

        pLTPLib->pLTPMsg = NULL;
    }
} /* end of BTLTPInitLTPAssembly */


BOOL LTPLibTrigger(PLTPLib pLTPLib)
{
	if(NULL != pPatch_Ltp_LibTrigger)
	{
		return pPatch_Ltp_LibTrigger();
	}
	
    BYTE        cmd;
    BYTE        copmsk;
    WORD        lenPara;
    WORD        optLen;
    LPBYTE      pOpt;
    LPBYTE      pPara;
    WORD        copyLength;
    BOOL        reuseBuffer = FALSE;
    PLTPCmdInfo pCmdInfo;

	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLibTrigger enter", 0);
	
    /* if we have no assembly buffer => try to get one                        */
    if (!pLTPLib->pLTPMsg)
    {
        pLTPLib->pLTPMsg = BTLTPTgtAssemblyBufferAlloc(pLTPLib->AppHandle);

        if (pLTPLib->pLTPMsg)
        {
        	/* */
        	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "Allocate pLTPLib->pLTPMsg = 0x%8x", 1, pLTPLib->pLTPMsg);
            BTLTPInitLTPAssembly(pLTPLib, TRUE, FALSE);
        }
        else
        {
            return FALSE; /* no re-trigger                                        */
        }
    }

    /* if we have no LTP data element to work with => try to get one          */
    if (!pLTPLib->pActiveElement)
    {
        pLTPLib->pActiveElement = (PLTPElement)ltpQueueOut(&pLTPLib->UsedElementQueue);

        if (!pLTPLib->pActiveElement)
        {
            return FALSE; /* no re-trigger                                        */
        }
    }

    /* if we don't know how long the LTP msg is we try to assemble            */
    /* ==> try to determine LTP msg length                                    */
    if (!pLTPLib->LTPMsgLength)
    {
        if (pLTPLib->LTPDataCollected < LTP_DATA_MIN_HEADER_LENGTH)
        {
            copyLength = LTP_DATA_MIN_HEADER_LENGTH - pLTPLib->LTPDataCollected;    
            if (BTLTPTransferLTPElementData(pLTPLib, copyLength))
            {
                return TRUE; /* not enough data => re-trigger                       */
            }
        }

        /* basic mgs header complete, check for optional CRC                    */
        copmsk  = pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart + 1];

        /* if there is a CRC => use it for msg integrety check                  */
        if (copmsk & LTP_OPT_MASK_HEADER_CRC8)
        {
            optLen = LTPLibGetOptLength(copmsk);

            if (pLTPLib->LTPDataCollected < (LTP_DATA_MIN_HEADER_LENGTH + optLen))
            {
                copyLength = (LTP_DATA_MIN_HEADER_LENGTH + optLen) - pLTPLib->LTPDataCollected;
                if (BTLTPTransferLTPElementData(pLTPLib, copyLength))
                {
                    return TRUE; /* not enough data => re-trigger                     */
                }
            }

            /* we have the CRC => check msg header                                */
            if(BTLTPTgtDoCRC8(pLTPLib,&pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart],LTP_DATA_MIN_HEADER_LENGTH) 
                != pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart+LTP_DATA_MIN_HEADER_LENGTH + optLen - 1])
            {
#if F_LTPLIB_MDC_SUPPORT
                LTPLibSendInternalEventInfo(pLTPLib, 0, NULL, LTP_CAUSE_CONNECTION_LOST, LTP_INTERNAL_EVENT_COMMUNICATION_OUT_OF_SYNC, LTP_GENERATE_EVENT_ID);
#endif
                BTLTPInitLTPAssembly(pLTPLib, FALSE, TRUE);
                return TRUE;
            }
        }

        pLTPLib->LTPMsgLength = NETCHAR2SHORT(&pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart + 2]);
        //DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLibTrigger:pLTPLib->LTPMsgLength = %d", 1, pLTPLib->LTPMsgLength);

        if (pLTPLib->LTPMsgLength > pLTPLib->ReceiveMaxLength)
        {
            /* we are out of sync!                                                */
#if F_LTPLIB_MDC_SUPPORT
            LTPLibSendInternalEventInfo(pLTPLib, 0, NULL, LTP_CAUSE_INVALID_PARAMETER, LTP_INTERNAL_EVENT_COMMUNICATION_OUT_OF_SYNC, LTP_GENERATE_EVENT_ID);
#endif
            BTLTPInitLTPAssembly(pLTPLib, FALSE, TRUE);
            return TRUE;
        }
    }

    /* added by LV for robustness - module might send invalid data on reset...*/
    if (!pLTPLib->LTPMsgLength)
    {
        BTLTPInitLTPAssembly(pLTPLib, FALSE, TRUE);
        return TRUE;
    }

	/* wait for message completed */
    if (pLTPLib->LTPMsgLength > pLTPLib->LTPDataCollected)
    {
        /* try to complete LTP message                                         */
        if (BTLTPTransferLTPElementData(pLTPLib, pLTPLib->LTPMsgLength - pLTPLib->LTPDataCollected))
        {
            return TRUE; /* not enough data => re-trigger                        */
        }
    }
    /*------------------------------------------------------------------------*/
    /* message is completed => process it                                     */
    /*------------------------------------------------------------------------*/

    /* prepare optional parameter handling                                    */
    copmsk  = pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart + 1];

    if (copmsk)
    {
        /* if there are optiona parameters ==> set access parameter             */
        pOpt   = &pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart + 4];
        optLen = LTPLibGetOptLength(copmsk);
    }
    else
    {
        pOpt   = NULL;
        optLen = 0;
    }

    /* prepare mandatory parameter handling                                   */

    lenPara = pLTPLib->LTPMsgLength - 4 - optLen;

    if (lenPara)
    {
        /* if there are mandatory parameter ==> this is the pointer to them     */
        pPara = &pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart + 4 + optLen];
    }
    else
    {
        pPara = NULL;
    }

    /* we have a LTP message completely re assembled => handle it             */
    cmd     = pLTPLib->pLTPMsg[pLTPLib->LTPMsgStart];

    /* >= 0xF5 is auto_test command */
    if(cmd < 0xF5)
    {   	
        pCmdInfo = BTLTPGetMsgProperty(cmd);

        if (!pCmdInfo)
        {
        	/* no user command */
        	if(NULL == pPatch_Ltp_HaveUserCmd)
        	{
        		/* undefined opcode                                                     */
				LTPLibHandleUnkownCommand(pLTPLib, cmd);
				BTLTPInitLTPAssembly(pLTPLib, FALSE, TRUE);
				return TRUE; /* msg done => re-trigger  */  
        	}                              
        }

		if(pCmdInfo)
		{
			if (pCmdInfo->properties & LTP_VAR_LEN_MSG)
		    {
		        /* valiable length msg => check min length                              */
		        if (pLTPLib->LTPMsgLength < (pCmdInfo->length + optLen))
		        {
		            /* if not confirmations with cause "notSuppoerted"                   */
		            if (((pCmdInfo->properties & LTP_CNF_MSG) != LTP_CNF_MSG)                 ||
		                    (pLTPLib->LTPMsgLength             != LTP_DATA_MIN_HEADER_LENGTH + 1) ||
		                    (pOpt                              != NULL)                        ||
		                    (pPara[0]                          != LTP_CAUSE_NOT_SUPPORTED)
		               )
		            {
#if F_LTPLIB_MDC_SUPPORT
		                LTPLibSendInternalEventInfo(pLTPLib, 0, NULL, LTP_CAUSE_INVALID_PARAMETER, LTP_INTERNAL_EVENT_MALFORMED_MSG_RECEIVED, LTP_GENERATE_EVENT_ID);
#endif
		                LTPLibHandleUnkownCommand(pLTPLib, cmd);
		                BTLTPInitLTPAssembly(pLTPLib, FALSE, TRUE);
		                return TRUE; /* msg done => re-trigger                             */
		            }
		        }
		    }
		    else
		    {
		        /* fixed length msg => check length                                     */
		        if (pLTPLib->LTPMsgLength != (pCmdInfo->length + optLen))
		        {
		            /* if not confirmations with cause "notSuppoerted"                   */
		            if (((pCmdInfo->properties & LTP_CNF_MSG) != LTP_CNF_MSG)                 ||
		                    (pLTPLib->LTPMsgLength             != LTP_DATA_MIN_HEADER_LENGTH + 1) ||
		                    (pOpt                              != NULL)                        ||
		                    (pPara[0]                          != LTP_CAUSE_NOT_SUPPORTED)
		               )
		            {
#if F_LTPLIB_MDC_SUPPORT
		                LTPLibSendInternalEventInfo(pLTPLib, 0, NULL, LTP_CAUSE_INVALID_PARAMETER, LTP_INTERNAL_EVENT_MALFORMED_MSG_RECEIVED, LTP_GENERATE_EVENT_ID);
#endif
		                LTPLibHandleUnkownCommand(pLTPLib, cmd);
		                BTLTPInitLTPAssembly(pLTPLib, FALSE, TRUE);
		                return TRUE; /* msg done => re-trigger                             */
		            }
		        }
		    }
		}  
    }

	/* jsut for testing aci */
	if(cmd == 0xF5)
	{
		reuseBuffer = LTPLL_HandleLowPowerCmd(pLTPLib->pLTPMsg, cmd, copmsk, pOpt, lenPara, pPara);
	}
    /* add autotest code here */
    else if (cmd > 0xF5)  /* not ltp command */
    {
        //call auto test function here
        if(NULL != pPatch_Ltp_AutoTestEntry)
    	{
    		reuseBuffer = pPatch_Ltp_AutoTestEntry((void*)pLTPLib->AppHandle, pLTPLib->pLTPMsg, cmd, copmsk, pOpt, lenPara, pPara);
    	}
    }
    else
    {
        reuseBuffer = BTLTPTgtHandleLTPMessage(pLTPLib->AppHandle, pLTPLib->pLTPMsg, cmd, copmsk, pOpt, lenPara, pPara);
    }

    BTLTPInitLTPAssembly(pLTPLib, reuseBuffer, FALSE);

    return TRUE; /* msg done => re-trigger                                    */
} /* end of LTPLibTrigger */


BOOL LTPLibInitialize(PLTPLib pLTPLib, LTP_TGT_APPHANDLE AppHandle, WORD ReceiveOffset, WORD ReceiveMaxLen, WORD SendOffset)
{
    /* first of all, clear context data                                       */
    memset(pLTPLib, 0, sizeof(TLTPLib));

    /* initialize context                                                     */
    pLTPLib->AppHandle        = AppHandle;
    pLTPLib->ReceiveOffset    = ReceiveOffset;
    pLTPLib->ReceiveMaxLength = ReceiveMaxLen;
    pLTPLib->SendOffset       = SendOffset;

    /* initialize message assembly                                            */
    BTLTPInitLTPAssembly(pLTPLib, TRUE, FALSE);

#if F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT
    /* initialize asyncronus message asse                                     */
    pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;

    BTLTPTgtTriggerTimer(pLTPLib->AppHandle, LTPLibTimerID_AsyncTimeout, 1000 /* 1s */);
#endif

    /* ready to rock...                                                       */
    pLTPLib->Status = LTPLibStatusIdle;

    return TRUE; /* OK */
} /* end of LTPLibInitialize */


BOOL LTPLibShutdown(PLTPLib pLTPLib)
{
    if (pLTPLib == NULL)
    {
        return FALSE;
    }

    if (pLTPLib->pLTPMsg != NULL)
    {
        BTLTPTgtAssemblyBufferRelease(pLTPLib, pLTPLib->pLTPMsg);
        pLTPLib->pLTPMsg = NULL;
    }

    if (pLTPLib->pActiveElement != NULL)
    {
        BTLTPTgtQueueElementRelease(pLTPLib->AppHandle, pLTPLib->pActiveElement);
        pLTPLib->pActiveElement = NULL;
    }

    return TRUE;
} /* end of LTPLibShutdown */


void LTPLibTriggerLTPProccess(PLTPLib pLTPLib)
{
    if (pLTPLib->Status >= LTPLibStatusBusy) /* off-sync or re-entrant          */
    {
        return;
    }
    else                                /* now we are busy                    */
    {
        pLTPLib->Status = LTPLibStatusBusy;
    }

    while (LTPLibTrigger(pLTPLib));

    if (pLTPLib->Status == LTPLibStatusBusy) /* might be off-sync               */
    {
        pLTPLib->Status = LTPLibStatusIdle;
    }
} /* end of LTPLibTriggerLTPProccess */

#if F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT
void LTPLibHandleTimeout(PLTPLib pLTPLib, TLTPTimerID timerID)
{
    switch (timerID)
    {
    case LTPLibTimerID_AsyncTimeout: /*-------------------------------------*/
        switch (pLTPLib->AsyncState)
        {
        case LTPLibAsyncStatusIgnore: /*....................................*/
            if (pLTPLib->LTPDataCollected)
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusWaitCMD;
            }
            /* next data will re-trigger timer                                */
            break;
        case LTPLibAsyncStatusWaitTimeout: /*...............................*/
            /* let App handle message                                         */
            BTLTPTgtHandleAsyncLTP_RESET_REQ(pLTPLib->AppHandle);
            /* reset assembly, but keep in mind that we just had 1s idle...   */
            pLTPLib->AsyncState     = LTPLibAsyncStatusIgnore;
            /* next data will re-trigger timer                                */
            break;
        default: /*.........................................................*/
            break; /* rest does not matter                                    */
        }
        break;

    default: /*-------------------------------------------------------------*/
        break; /* shall never happen!!!!!                                    */
    }
} /* end of LTPLibHandleTimeout */
#endif /* F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT */


BOOL LTPLibHandleReceiveData(PLTPLib pLTPLib, LPBYTE pRxBuffer, WORD rxLength, WORD rxOffset)
{
    PLTPElement pLTPElement;

    /* try to get new storage element                                         */
    pLTPElement = BTLTPTgtQueueElementAlloc(pLTPLib->AppHandle);
    if (pLTPElement)
    {
        /* store information                                                   */
        pLTPElement->DataCB.BufferAddress = pRxBuffer;
        pLTPElement->DataCB.Length        = rxLength;
        pLTPElement->DataCB.Offset        = rxOffset;

        ltpQueueIn(&pLTPLib->UsedElementQueue, pLTPElement);
        //DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLibHandleReceiveData: Alloc new element: address = 0x%8x, len = %d", 2, pRxBuffer, rxLength);
#if 0	/* for debug */
        //DBG_DIRECT("P_BtLtp->p_aci_tcb->P_RxBuffer = 0x%8x\n", P_BtLtp->p_aci_tcb->P_RxBuffer);
        uint16_t i = 0;
        for(i = 0; i < rxLength; i++)
        {
        	DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLibHandleReceiveData[0x%8x] = 0x%2x\t", 2, pRxBuffer + i, *(pRxBuffer + i));
        	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO,  "receive data[x%8x] = 0x%x\n", 2, P_BtLtp->p_aci_tcb->P_RxBuffer + i, *(P_BtLtp->p_aci_tcb->P_RxBuffer + i);
        	if(i == 13)
        	{
        		DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
        		//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "\n", 0);
        	}
        }
#endif
    }
    else
    {
    	//DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "LTPLibHandleReceiveData: Alloc new element failed!!!", 2);
    }

    /* handle of-sync command detection                                       */
#if F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT
    switch (pLTPLib->AsyncState)
    {
    case LTPLibAsyncStatusIgnore: /*----------------------------------------*/
        break;
    case LTPLibAsyncStatusWaitCMD: /*---------------------------------------*/
        if (pRxBuffer[rxOffset] == LTP_RESET_REQ)
        {
            pLTPLib->AsyncState = LTPLibAsyncStatusWaitCopMsk;
            rxLength--;
            rxOffset++;
        }
        else
        {
            pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
            rxLength            = 0;
            break;
        }
    /* no break */
    case LTPLibAsyncStatusWaitCopMsk: /*------------------------------------*/
        if (rxLength)
        {
            if (pRxBuffer[rxOffset] == 0x00) /* LTP_RESET_REQ CopMsk = 0x00        */
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusWaitLen1;
                rxLength--;
                rxOffset++;
            }
            else if (pRxBuffer[rxOffset] == LTP_OPT_MASK_HEADER_CRC8)
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusWaitLen1HeaderCRC;
                rxLength--;
                rxOffset++;
            }
            else
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
                rxLength            = 0;
                break;
            }
        }
    /* no break */
    case LTPLibAsyncStatusWaitLen1: /*--------------------------------------*/
    case LTPLibAsyncStatusWaitLen1HeaderCRC: /*-----------------------------*/
        if (rxLength)
        {
            if (pRxBuffer[rxOffset] == 0x00)   /* LTP_RESET_REQ len = 0x00 0x0X */
            {
                if (pLTPLib->AsyncState == LTPLibAsyncStatusWaitLen1)
                {
                    pLTPLib->AsyncState = LTPLibAsyncStatusWaitLen2;
                }
                else   /* pLTPLib->AsyncState==LTPLibAsyncStatusWaitLen1HeaderCRC */
                {
                    pLTPLib->AsyncState = LTPLibAsyncStatusWaitLen2HeaderCRC;
                }
                rxLength--;
                rxOffset++;
            }
            else
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
                rxLength            = 0;
                break;
            }
        }
    /* no break */
    case LTPLibAsyncStatusWaitLen2: /*--------------------------------------*/
    case LTPLibAsyncStatusWaitLen2HeaderCRC: /*-----------------------------*/
        if (rxLength)
        {
            if (pLTPLib->AsyncState == LTPLibAsyncStatusWaitLen2)
            {
                if ((pRxBuffer[rxOffset] == LTP_RESET_REQ_LENGTH) && (rxLength == 1))
                {
                    pLTPLib->AsyncState = LTPLibAsyncStatusWaitTimeout;
                    BTLTPTgtTriggerTimer(pLTPLib->AppHandle, LTPLibTimerID_AsyncTimeout, 1000 /* 1s */);
                    break;
                }
                else
                {
                    pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
                    rxLength            = 0;
                }
            }
            else if (pLTPLib->AsyncState == LTPLibAsyncStatusWaitLen2HeaderCRC)
            {
                if (pRxBuffer[rxOffset] == LTP_RESET_REQ_LENGTH + 1)
                {
                    pLTPLib->AsyncState = LTPLibAsyncStatusWaitHeaderCRC;
                    rxLength--;
                    rxOffset++;
                }
                else
                {
                    pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
                    rxLength            = 0;
                }
            }
            else
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
                rxLength            = 0;
            }
        }
    /* no break */
    case LTPLibAsyncStatusWaitHeaderCRC: /*---------------------------------*/
        if (rxLength)
        {
            if ((pRxBuffer[rxOffset] == LTP_RESET_REQ_HEADER_CRC) && (rxLength == 1))
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusWaitTimeout;
                BTLTPTgtTriggerTimer(pLTPLib->AppHandle, LTPLibTimerID_AsyncTimeout, 1000 /* 1s */);
            }
            else
            {
                pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
                rxLength            = 0;
            }
        }
        break;
    case LTPLibAsyncStatusWaitTimeout: /*-----------------------------------*/
        BTLTPTgtTriggerTimer(pLTPLib->AppHandle, LTPLibTimerID_AsyncTimeout, 1000 /* 1s */);
        pLTPLib->AsyncState = LTPLibAsyncStatusIgnore;
        break;
    default: /*-------------------------------------------------------------*/
        break; /* shall never happen!!!!!                                     */
    }

    if (pLTPLib->AsyncState == LTPLibAsyncStatusIgnore) /* tifnan: what the timer dose */
    {
        BTLTPTgtTriggerTimer(pLTPLib->AppHandle, LTPLibTimerID_AsyncTimeout, 1000 /* 1s */);
    }
#endif /* F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT */

    if (!pLTPElement)
    {
        return FALSE; /* data could not be handled, please re-try later...      */
    }

    /* trigger LTP statemachine                                               */
    LTPLibTriggerLTPProccess(pLTPLib);

    return TRUE; /* OK */
} /* end of LTPLibHandleReceiveData */


WORD LTPLibGetOptLength(BYTE copmsk)
{
    WORD mask   = 0x0001;
    WORD optLen = 0;

    do
    {
        if (mask & ((WORD)copmsk))
        {
            optLen++;
        }
        mask = mask << 1;

    }
    while (mask & 0x00FF);

    return optLen;
} /* end of LTPLibGetOptLength */


WORD LTPLibInsertHeader(PLTPLib pLTPLib, LPBYTE pBuffer, LPWORD offset, WORD dataLen, BYTE cmd, BYTE copmsk, LPBYTE pOpt, LPWORD posParam)
{
    PLTPCmdInfo pCmdInfo  = BTLTPGetMsgProperty(cmd);
    WORD        optLen    = LTPLibGetOptLength(copmsk);
    BYTE        DoCRC8    = ((copmsk & LTP_OPT_MASK_HEADER_CRC8) >> 7);
    WORD        pos       = *offset;

    /* unknown command, not a command with variable data length or */
    /* offset is too small to insert LTP header + parameters */
    if ((pCmdInfo == NULL) ||
            !(pCmdInfo->properties & LTP_VAR_LEN_MSG) ||
            (pos < (pCmdInfo->length + optLen))
       )
    {
        return 0;
    }

    /* set offset to first byte of the message */
    pos -= (pCmdInfo->length + optLen);
    *offset = pos;

    pBuffer[pos++] = pCmdInfo->opcode;
    pBuffer[pos++] = copmsk;
    NETSHORT2CHAR(&pBuffer[pos], pCmdInfo->length + optLen + dataLen);
    pos += 2;

    if (copmsk)
    {
        memcpy(&pBuffer[pos], pOpt, optLen - DoCRC8);
        pos += optLen - DoCRC8;
    }

    if (DoCRC8)
    {
        pBuffer[pos++] = BTLTPTgtDoCRC8(pLTPLib, &pBuffer[*offset], LTP_DATA_MIN_HEADER_LENGTH);
    }

    /* set offset to first parameter */
    *posParam = pos;

    /* return message length */
    return pCmdInfo->length + optLen + dataLen;
}


LPBYTE LTPLibWriteHeader(PLTPLib pLTPLib, LPWORD offset, BYTE cmd, BYTE copmsk, LPBYTE pOpt, WORD varLen)
{
    PLTPCmdInfo cmdInfo = BTLTPGetMsgProperty(cmd);
    WORD        optLen  = LTPLibGetOptLength(copmsk);
    BYTE        DoCRC8  = ((copmsk & LTP_OPT_MASK_HEADER_CRC8) >> 7);
    WORD        pos     = *offset;
    LPBYTE      pBuffer;

    if (cmdInfo == NULL)
    {
        return NULL;
    }

    if (!(cmdInfo->properties & LTP_VAR_LEN_MSG))
    {
        varLen = 0;
    }

    pBuffer = BTLTPTgtSendBufferAlloc(pLTPLib->AppHandle, *offset + cmdInfo->length + optLen + varLen);

   /* DBG_BUFFER(MODULE_LTP, LEVEL_INFO, "*offset = 0x%x, cmdInfo->length = 0x%x, optLen = 0x%x, varLen = 0x%x", 4,\
                    		*offset, cmdInfo->length, optLen, varLen); */
    
    if (pBuffer == NULL)
    {
        return NULL;
    }

    pBuffer[pos++] = cmd;
    pBuffer[pos++] = copmsk;
    NETSHORT2CHAR(&pBuffer[pos], cmdInfo->length + optLen + varLen);
    pos += 2;

    if (copmsk)
    {
        memcpy(&pBuffer[pos], pOpt, optLen - DoCRC8);
        pos += optLen - DoCRC8;
    }

    if (DoCRC8)
    {
        pBuffer[pos++] = BTLTPTgtDoCRC8(pLTPLib, &pBuffer[*offset], LTP_DATA_MIN_HEADER_LENGTH);
    }

    *offset = pos;
    return pBuffer;
} /* end of LTPLibWriteHeader */


BOOL LTPLibSendMessage_BYTE(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cmd, BYTE param)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, cmd, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = param;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendMessage_BYTE */


BOOL LTPLibSendMessage_BYTE_BYTE(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cmd, BYTE param1, BYTE param2)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, cmd, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = param1;
    pBuffer[pos++] = param2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendMessage_BYTE_BYTE */

#if 0
BOOL LTPLibSendMessage_BYTE_BD(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cmd, BYTE param, LPBYTE bd)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, cmd, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return TRUE;
    }

    pBuffer[pos++] = param;
    memcpy(&pBuffer[pos], bd, 6);
    pos += 6;

    return BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset);
} /* end of LTPLibSendMessage_BYTE_BD */
#endif

BOOL LTPLibSendMessage_BD(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cmd, LPBYTE bd)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, cmd, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return TRUE;
    }

    memcpy(&pBuffer[pos], bd, 6);
    pos += 6;

    return BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset);
} /* end of LTPLibSendMessage_BD */


BOOL LTPLibSendMessage_BD_BYTE(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cmd, LPBYTE bd, BYTE param)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, cmd, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return TRUE;
    }

    memcpy(&pBuffer[pos], bd, 6);
    pos += 6;
    pBuffer[pos++] = param;

    return BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset);
} /* end of LTPLibSendMessage_BD_BYTE */


BOOL LTPLibSendMessage_BD_DWORD(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cmd, LPBYTE bd, DWORD param)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, cmd, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    memcpy(&pBuffer[pos], bd, 6);
    pos += 6;
    NETLONG2CHAR(&pBuffer[pos], param);
    pos += 4;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendMessage_BD_DWORD */


BOOL LTPLibSendMessageDataReq(PLTPLib pLTPLib, BYTE returnCredits, LPBYTE payload, BYTE loc_MDL_ID, BYTE frameType, UINT frameLength, UINT payloadLength, WORD offset)
{
    LPBYTE pBuffer;
    BYTE   pOpt[2];
    BYTE   copmsk             = LTP_OPT_MASK_HEADER_CRC8 | LTP_DATA_OPT_MASK_LOC_MDL_ID | LTP_DATA_OPT_MASK_RETURN_CREDITS;
    WORD   pos                = offset;
    BYTE   posPOpt            = 0;

    /* make sure we do not get BlueHDP+ frameTypes */
    if (frameType < 0x40)
    {
        return FALSE;
    }

    pOpt[posPOpt++] = loc_MDL_ID;
    pOpt[posPOpt++] = returnCredits;

    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, frameType, copmsk, pOpt, frameLength);

    if (! pBuffer)
    {
        return FALSE;
    }

    if (frameType ==  LTP_DATA_START_SEGMENT)
    {
        NETSHORT2CHAR(&pBuffer[pos], payloadLength);
        pos += 2;
    }

    memcpy(&pBuffer[pos], payload + offset, frameLength);
    pos += frameLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, offset, pos - offset));
} /* end of LTPLibSendMessage_DataMessage */


BOOL LTPLibHandleUnkownCommand(PLTPLib pLTPLib, BYTE cmd)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer;

    if (cmd & 0x80) /* we have to generate a response                           */
    {
        pBuffer = BTLTPTgtSendBufferAlloc(pLTPLib->AppHandle, 5 + pLTPLib->SendOffset);

        if (pBuffer)
        {
            pBuffer[pos++] = cmd & 0x7F;              /* response opcode            */
            pBuffer[pos++] = 0x00;                    /* copmsk                     */
            NETSHORT2CHAR(&pBuffer[pos], 5);
            pos += 2; /* msg length                 */
            pBuffer[pos++] = LTP_CAUSE_NOT_SUPPORTED; /* cause                      */

            return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
        }
        else
        {
            /* todo: anything useful left to do? */
            return FALSE;
        }
    }
    else /* just ignore and dump                                              */
    {
        return TRUE;  /* OK */
    }
} /* end of LTPLibHandleUnkownCommand */


#if F_LTPLIB_MDC_SUPPORT
BOOL LTPLibSendConfigTunnelRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_CONFIG_TUNNEL_RSP, cause);
}


BOOL LTPLibSendRadioModeSetRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_RADIO_MODE_SET_RSP, cause);
}


BOOL LTPLibSendDeviceConfigDeviceSetRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_DEVICE_CONFIG_DEVICE_SET_RSP, cause);
}


BOOL LTPLibSendDeviceConfigSecuritySetRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_DEVICE_CONFIG_SECURITY_SET_RSP, cause);
}

BOOL LTPLibSendPairableModeSetRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_PAIRABLE_MODE_SET_RSP, cause);
}


BOOL LTPLibSendPasskeyReqReplyRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_PASSKEY_REQ_REPLY_RSP, cause);
}


BOOL LTPLibSendPasskeyNotificationInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD, DWORD displayValue)
{
    return LTPLibSendMessage_BD_DWORD(pLTPLib, copmsk, pOpt, LTP_PASSKEY_NOTIFICATION_INFO, rem_BD, displayValue);
}


BOOL LTPLibSendActInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, BYTE version, LPBYTE local_BD, LPBYTE FW_VersionString)
{
    WORD   strLen  = (WORD) strlen((char*)FW_VersionString) + 1;
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_ACT_INFO, copmsk, pOpt, strLen);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    pBuffer[pos++] = version;
    memcpy(&pBuffer[pos], local_BD, 6);
    pos += 6;
    memcpy(&pBuffer[pos], FW_VersionString, strLen);
    pos += strLen;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendActInfo */


BOOL LTPLibSendMCLStatusInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD, BYTE loc_MCL_ID, BYTE loc_MCL_Status)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_MCL_STATUS_INFO, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;

    pBuffer[pos++] = loc_MCL_ID;
    pBuffer[pos++] = loc_MCL_Status;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendMCLStatusInfo */


BOOL LTPLibSendACLStatusInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD, BYTE loc_ACL_Status)
{
    return LTPLibSendMessage_BD_BYTE(pLTPLib, copmsk, pOpt, LTP_ACL_STATUS_INFO, rem_BD, loc_ACL_Status);
} /* end of LTPLibSendACLStatusInfo */


BOOL LTPLibSendAuthRequestInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD)
{
    return LTPLibSendMessage_BD(pLTPLib, copmsk, pOpt, LTP_AUTH_REQUEST_IND, rem_BD);
}


BOOL LTPLibSendAuthResultRequestInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD)
{
    return LTPLibSendMessage_BD(pLTPLib, copmsk, pOpt, LTP_AUTH_RESULT_REQUEST_IND, rem_BD);
}

BOOL LTPLibSendPasskeyRequestInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD)
{
    return LTPLibSendMessage_BD(pLTPLib, copmsk, pOpt, LTP_PASSKEY_REQUEST_IND, rem_BD);
}


BOOL LTPLibSendRemoteOOBRequestInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD)
{
    return LTPLibSendMessage_BD(pLTPLib, copmsk, pOpt, LTP_REMOTE_OOB_REQUEST_IND, rem_BD);
}

BOOL LTPLibSendAuthResultInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, LPBYTE rem_BD, LPBYTE linkKey, BYTE keyType)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_AUTH_RESULT_IND, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return TRUE;
    }

    pBuffer[pos++] = cause;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    memcpy(&pBuffer[pos], linkKey, 16);
    pos += 16;
    pBuffer[pos++] = keyType;

    return BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset);
} /* end of LTPLibSendAuthResultInd */


BOOL LTPLibSendAuthResultExtInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, LPBYTE rem_BD, BYTE rem_BD_Type, BYTE keyType, LPBYTE linkKey, WORD linkKeyLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_AUTH_RESULT_EXT_IND, copmsk, pOpt, linkKeyLength);

    if (!pBuffer)
    {
        return TRUE;
    }

    pBuffer[pos++] = cause;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    pBuffer[pos++] = keyType;
    /* bee stack has no appdata parameter, add 4 byte 0x00 for serial tester */
	NETLONG2CHAR(&pBuffer[pos], 0x0000);
	pos += 4;
    memcpy(&pBuffer[pos], linkKey, linkKeyLength);	//0x1c
    pos += linkKeyLength;

    return BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset);
} /* LTPLibSendAuthResultExtInd */


BOOL LTPLibSendAuthResultRequestExtInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD, BYTE rem_BD_Type, BYTE keyType)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_AUTH_RESULT_REQUEST_EXT_IND, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return TRUE;
    }

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    pBuffer[pos++] = keyType;

    return BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset);
} /* LTPLibSendAuthResultRequestExtInd */


BOOL LTPLibSendInternalEventInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, BYTE eventType, DWORD eventInfo)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_INTERNAL_EVENT_INFO, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return TRUE;
    }

    pBuffer[pos++] = (BYTE)cause;
    pBuffer[pos++] = (BYTE)eventType;
    NETLONG2CHAR(&pBuffer[pos], eventInfo);
    pos += 4;

    return BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset);
} /* end of LTPLibSendInternalEventInfo */


BOOL LTPLibSendCreateMDLInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, LPBYTE rem_BD, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BD_BYTE(pLTPLib, copmsk, pOpt, LTP_CREATE_MDL_IND, rem_BD, loc_MDL_ID);
} /* end of LTPLibSendCreateMDLInd */


BOOL LTPLibSendConnectMDLRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, LPBYTE rem_BD, BYTE rem_MDEP_ID)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_CONNECT_MDL_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = (BYTE)cause;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = (BYTE)rem_MDEP_ID;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendConnectMDLRsp */


BOOL LTPLibSendConnectMDLInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE loc_MDL_ID, WORD maxLTPSize, WORD maxAPDUSize)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_CONNECT_MDL_INFO, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    NETSHORT2CHAR(&pBuffer[pos], maxLTPSize);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], maxAPDUSize);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendConnectMDLInfo */


BOOL LTPLibSendDisconnectMDLInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_DISCONNECT_MDL_IND, cause, loc_MDL_ID);
}


BOOL LTPLibSendDeleteMDLInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_DELETE_MDL_INFO, loc_MDL_ID);
}


BOOL LTPLibSendDisconnectMDLRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_DISCONNECT_MDL_RSP, cause, loc_MDL_ID);
}


BOOL LTPLibSendResetRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_RESET_RSP, cause);
}


#if (F_LTPLIB_RECONNECT_SUPPORT)
BOOL LTPLibSendReconnectMDLInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_RECONNECT_MDL_IND, loc_MDL_ID);
}


BOOL LTPLibSendReconnectMDLRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt, BYTE cause, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_RECONNECT_MDL_RSP, cause, loc_MDL_ID);
}
#endif /* (F_LTPLIB_RECONNECT_SUPPORT) */

#if (F_LTPLIB_GATT_SERVER_SUPPORT)
/****************************************************************************
 * LTPLibSendGATTServiceRegisterRsp
 ****************************************************************************/
BOOL LTPLibSendGATTServiceRegisterRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                      BYTE cause, WORD subCause, BYTE serviceHandle)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_SERVICE_REGISTER_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    NETSHORT2CHAR(&pBuffer[pos], subCause);
    pos += 2;
    pBuffer[pos++] = serviceHandle;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTServiceRegisterRsp */


/****************************************************************************
 * LTPLibSendGATTServiceReleaseRsp
 ****************************************************************************/
BOOL LTPLibSendGATTServiceReleaseRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                     BYTE cause, WORD subCause, BYTE serviceHandle)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_SERVICE_RELEASE_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    NETSHORT2CHAR(&pBuffer[pos], subCause);
    pos += 2;
    pBuffer[pos++] = serviceHandle;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTServiceReleaseRsp */


/****************************************************************************
 * LTPLibSendGATTAttributeUpdateStatusInd
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeUpdateStatusInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
        BYTE cause, WORD subCause, BYTE serviceHandle,
        BYTE requestHandle, WORD attribIndex,
        LPBYTE rem_BD, BYTE rem_BD_Type)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_UPDATE_STATUS_IND, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    NETSHORT2CHAR(&pBuffer[pos], subCause);
    pos += 2;
    pBuffer[pos++] = serviceHandle;
    pBuffer[pos++] = requestHandle;
    NETSHORT2CHAR(&pBuffer[pos], attribIndex);
    pos += 2;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeUpdateStatusInd */


/****************************************************************************
 * LTPLibSendGATTAttributeReadInd
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeReadInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                    BYTE loc_MDL_ID, BYTE serviceHandle,
                                    WORD attribIndex, WORD readOffset)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_READ_IND, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = serviceHandle;
    NETSHORT2CHAR(&pBuffer[pos], attribIndex);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], readOffset);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeReadInd */
#endif /* (F_LTPLIB_GATT_SERVER_SUPPORT) */


#if (F_LTPLIB_GATT_SERVER_SUPPORT) || (F_LTPLIB_LE_SUPPORT)
/****************************************************************************
 * LTPLibSendGATTServerStoreInd
 ****************************************************************************/
BOOL LTPLibSendGATTServerStoreInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                  BYTE opCode, LPBYTE rem_BD, BYTE rem_BD_Type,
                                  WORD restartHandle, LPBYTE data, WORD dataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_SERVER_STORE_IND, copmsk, pOpt, dataLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = opCode;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    NETSHORT2CHAR(&pBuffer[pos], restartHandle);
    pos += 2;
    memcpy(&pBuffer[pos], data, dataLength);
    pos += dataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTServerStoreInd */
#endif /* (F_LTPLIB_GATT_SERVER_SUPPORT) || (F_LTPLIB_LE_SUPPORT) */


#if (F_LTPLIB_GATT_CLIENT_SUPPORT)
/****************************************************************************
 * LTPLibSendConnectGATTMDLRsp
 ****************************************************************************/
BOOL LTPLibSendConnectGATTMDLRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                 BYTE cause, LPBYTE rem_BD, BYTE rem_BD_Type,
                                 BYTE loc_MDL_ID, BYTE loc_MDEP_ID)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_CONNECT_GATT_MDL_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = loc_MDEP_ID;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendConnectGATTMDLRsp */


/****************************************************************************
 * LTPLibSendGATTDiscoveryRsp
 ****************************************************************************/
BOOL LTPLibSendGATTDiscoveryRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                BYTE cause, WORD subCause, BYTE loc_MDL_ID,
                                BYTE discoveryType)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_DISCOVERY_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    NETSHORT2CHAR(&pBuffer[pos], subCause);
    pos += 2;
    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = discoveryType;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTDiscoveryRsp */


/****************************************************************************
 * LTPLibSendGATTAttributeWriteRsp
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeWriteRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                     BYTE cause, WORD subCause, BYTE loc_MDL_ID,
                                     BYTE writeType)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_WRITE_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    NETSHORT2CHAR(&pBuffer[pos], subCause);
    pos += 2;
    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = writeType;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeWriteRsp */


/****************************************************************************
 * LTPLibSendGATTAttributeNotificationInfo
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeNotificationInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
        BYTE loc_MDL_ID, WORD attribHandle,
        LPBYTE data, WORD dataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_NOTIFICATION_INFO, copmsk, pOpt, dataLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    NETSHORT2CHAR(&pBuffer[pos], attribHandle);
    pos += 2;
    memcpy(&pBuffer[pos], data, dataLength);
    pos += dataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeNotificationInfo */
#endif /* (F_LTPLIB_GATT_CLIENT_SUPPORT) */


#if (F_LTPLIB_GATT_SERVER_SUPPORT) || (F_LTPLIB_GATT_CLIENT_SUPPORT)
/****************************************************************************
 * LTPLibSendGATTSecurityRsp
 ****************************************************************************/
BOOL LTPLibSendGATTSecurityRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                               BYTE cause, BYTE loc_MDL_ID, BYTE keyType,
                               BYTE keySize)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_SECURITY_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = keyType;
    pBuffer[pos++] = keySize;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTSecurityRsp */
#endif /* (F_LTPLIB_GATT_SERVER_SUPPORT) || (F_LTPLIB_GATT_CLIENT_SUPPORT) */




#if (F_LTPLIB_LE_SUPPORT)
/****************************************************************************
 * LTPLibSendGATTMtuSizeInfo
 ****************************************************************************/
BOOL LTPLibSendGATTMtuSizeInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                               BYTE loc_MDL_ID, WORD mtuSize)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_MTU_INFO, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    NETSHORT2CHAR(&pBuffer[pos], mtuSize);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTSecurityRsp */

/****************************************************************************
 * LTPLibSendLEAdvertiseRsp
 ****************************************************************************/
BOOL LTPLibSendLEAdvertiseRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                              BYTE cause, BYTE advMode)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_LE_ADVERTISE_RSP, cause, advMode);
} /* LTPLibSendLEAdvertiseRsp */


/****************************************************************************
 * LTPLibSendLEAdvertiseParameterSetRsp
 ****************************************************************************/
BOOL LTPLibSendLEAdvertiseParameterSetRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
        BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_LE_ADVERTISE_PARAMETER_SET_RSP, cause);
} /* LTPLibSendLEAdvertiseParameterSetRsp */


/****************************************************************************
 * LTPLibSendLEAdvertiseDataSetRsp
 ****************************************************************************/
BOOL LTPLibSendLEAdvertiseDataSetRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                     BYTE cause, BYTE dataType)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_LE_ADVERTISE_DATA_SET_RSP, cause, dataType);
} /* LTPLibSendLEAdvertiseDataSetRsp */


/****************************************************************************
 * LTPLibSendLEScanRsp
 ****************************************************************************/
BOOL LTPLibSendLEScanRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                         BYTE cause)
{
    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_LE_SCAN_RSP, cause);
} /* LTPLibSendLEScanRsp */


/****************************************************************************
 * LTPLibSendLEScanInfo
 ****************************************************************************/
BOOL LTPLibSendLEScanInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                          LPBYTE rem_BD, BYTE rem_BD_Type, BYTE advType,
                          BYTE rssi, LPBYTE data, WORD dataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_SCAN_INFO, copmsk, pOpt, dataLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    pBuffer[pos++] = advType;
    pBuffer[pos++] = rssi;
    memcpy(&pBuffer[pos], data, dataLength);
    pos += dataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEScanInfo */


/****************************************************************************
 * LTPLibSendLEModifyWhitelistRsp
 ****************************************************************************/
BOOL LTPLibSendLEModifyWhitelistRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                    BYTE cause, BYTE whitelistOp)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_LE_MODIFY_WHITELIST_RSP, cause, whitelistOp);
} /* LTPLibSendLEModifyWhitelistRsp */


/****************************************************************************
 * LTPLibSendLEConnectionUpdateRsp
 ****************************************************************************/
BOOL LTPLibSendLEConnectionUpdateRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                     BYTE cause, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_LE_CONNECTION_UPDATE_RSP, cause, loc_MDL_ID);
} /* LTPLibSendLEConnectionUpdateRsp */


/****************************************************************************
 * LTPLibSendLEConnectionUpdateInd
 ****************************************************************************/
BOOL LTPLibSendLEConnectionUpdateInd(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                     BYTE loc_MDL_ID, WORD connIntervalMin,
                                     WORD connIntervalMax, WORD connLatency,
                                     WORD supervisionTimeout)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_CONNECTION_UPDATE_IND, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    NETSHORT2CHAR(&pBuffer[pos], connIntervalMin);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connIntervalMax);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connLatency);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], supervisionTimeout);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEConnectionUpdateInd */


/****************************************************************************
 * LTPLibSendLEConnectionParameterInfo
 ****************************************************************************/
BOOL LTPLibSendLEConnectionParameterInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
        BYTE loc_MDL_ID, WORD connInterval,
        WORD connLatency, WORD supervisionTimeout)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_CONNECTION_PARAMETER_INFO, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    NETSHORT2CHAR(&pBuffer[pos], connInterval);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connLatency);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], supervisionTimeout);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEConnectionParameterInfo */


#if (F_LTPLIB_LE_PRIVACY_SUPPORT)
/****************************************************************************
 * LTPLibSendLEConnectionParameterInfo
 ****************************************************************************/
BOOL LTPLibSendLEPrivacyModeRsp(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                BYTE cause, LPBYTE loc_BD, BYTE loc_BD_Type)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_PRIVACY_MODE_RSP, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    memcpy(&pBuffer[pos], loc_BD, 6);
    pos += 6;
    pBuffer[pos++] = loc_BD_Type;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEConnectionParameterInfo */

/****************************************************************************
 * LTPLibSendACLBDResolvedInfo
 ****************************************************************************/
BOOL LTPLibSendACLBDResolvedInfo(PLTPLib pLTPLib, BYTE copmsk, LPBYTE pOpt,
                                 LPBYTE rem_BD, BYTE rem_BD_Type,
                                 LPBYTE resolved_BD, BYTE resolved_BD_Type
                                )
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_ACL_BD_RESOLVED_INFO, copmsk, pOpt, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    memcpy(&pBuffer[pos], resolved_BD, 6);
    pos += 6;
    pBuffer[pos++] = resolved_BD_Type;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendACLBDResolvedInfo */
#endif /* (F_LTPLIB_LE_PRIVACY_SUPPORT) */
#endif /* (F_LTPLIB_LE_SUPPORT) */
#endif /* F_LTPLIB_MDC_SUPPORT */

#if F_LTPLIB_MDH_SUPPORT
BOOL LTPLibSendAuthListReq(PLTPLib pLTPLib, LPBYTE rem_BD, BYTE rem_BD_Type)
{
    BYTE pOpt[1];
    BYTE copmsk = LTP_OPT_MASK_HEADER_CRC8 | LTP_AUTH_LIST_REQ_OPT_MASK_BD_TYPE;

    pOpt[0] = rem_BD_Type;

    return LTPLibSendMessage_BD(pLTPLib, copmsk, pOpt, LTP_AUTH_LIST_REQ, rem_BD);
}


BOOL LTPLibSendAuthReq(PLTPLib pLTPLib, LPBYTE rem_BD)
{
    return LTPLibSendMessage_BD(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_AUTH_REQ, rem_BD);
}


BOOL LTPLibSendConfigTunnelReq(PLTPLib pLTPLib, LPBYTE configCmd)
{
    WORD   strLen  = (WORD) strlen((char*)configCmd) + 1;
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_CONFIG_TUNNEL_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, strLen);

    if (!pBuffer)
    {
        return FALSE;
    }

    memcpy(&pBuffer[pos], configCmd, strLen);
    pos += strLen;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendConfigTunnelReq */


BOOL LTPLibSendDeviceNameReq(PLTPLib pLTPLib, LPBYTE rem_BD)
{
    return LTPLibSendMessage_BD(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_DEVICE_NAME_REQ, rem_BD);
}

BOOL LTPLibSendPairableModeSetReq(PLTPLib pLTPLib, BYTE enablePairableMode, BYTE AuthRequirements, BYTE IOCapabilities, BYTE remoteOOBDataPresent)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_PAIRABLE_MODE_SET_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = enablePairableMode;
    pBuffer[pos++] = AuthRequirements;
    pBuffer[pos++] = IOCapabilities;
    pBuffer[pos++] = remoteOOBDataPresent;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendPairableModeSetReq */


BOOL LTPLibSendPasskeyReqReplyReq(PLTPLib pLTPLib, LPBYTE rem_BD, DWORD passKey, BYTE cause )
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_PASSKEY_REQ_REPLY_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (! pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;

    NETLONG2CHAR(&pBuffer[pos], passKey);
    pos += 4;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendPasskeyReqReplyReq */


BOOL LTPLibSendRadioModeSetReq(PLTPLib pLTPLib, BYTE radioMode, BYTE limitedDiscoverable)
{
    BYTE pOpt[1];
    BYTE copmsk = LTP_OPT_MASK_HEADER_CRC8 | LTP_RADIO_MODE_SET_REQ_OPT_MASK_LIMITED_DISCOVERABLE;

    pOpt[0] = limitedDiscoverable;

    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_RADIO_MODE_SET_REQ, radioMode);
} /* end of LTPLibSendRadioModeSetReq */


BOOL LTPLibSendDeviceConfigDeviceSetReq(PLTPLib pLTPLib, DWORD classOfDevice, LPBYTE deviceName)
{
    BYTE   copmsk   = LTP_OPT_MASK_HEADER_CRC8;
    WORD   pos      = pLTPLib->SendOffset;
    WORD   nameSize;
    LPBYTE pBuffer;

    nameSize = (WORD) strlen((char*)deviceName) + 1;

    /* build packet */
    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_DEVICE_CONFIG_DEVICE_SET_REQ, copmsk, NULL, nameSize);
    if (!pBuffer)
    {
        return FALSE;
    }

    /* set mandatory parameters */
    classOfDevice   = (classOfDevice << 8) & 0xFFFFFF00;
    NETLONG2CHAR(&pBuffer[pos], classOfDevice);
    pos += 3;
    memcpy(&pBuffer[pos], deviceName, nameSize);
    pos += nameSize;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendDeviceConfigDeviceSetReq */


BOOL LTPLibSendDeviceConfigDIDSetReq(PLTPLib pLTPLib, WORD vendorID, BYTE vendorIDSource, WORD productID, WORD productVersion)
{
    BYTE   copmsk   = LTP_OPT_MASK_HEADER_CRC8;
    WORD   pos      = pLTPLib->SendOffset;
    LPBYTE pBuffer;

    /* build packet */
    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_DEVICE_CONFIG_DID_SET_REQ, copmsk, NULL, 0);
    if (!pBuffer)
    {
        return FALSE;
    }

    /* set mandatory parameters */
    NETSHORT2CHAR(&pBuffer[pos], vendorID);
    pos += 2;
    pBuffer[pos++] = vendorIDSource;
    NETSHORT2CHAR(&pBuffer[pos], productID);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], productVersion);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendDeviceConfigDIDSetReq */


BOOL LTPLibSendDeviceConfigSecuritySetReq(PLTPLib pLTPLib, BYTE storeBondMode, BYTE storeBondSize, DWORD leFixedDisplayValue)
{
    BYTE   copmsk   = LTP_OPT_MASK_HEADER_CRC8;
    WORD   pos      = pLTPLib->SendOffset;
    LPBYTE pBuffer;

    /* build packet */
    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_DEVICE_CONFIG_SECURITY_SET_REQ, copmsk, NULL, 0);
    if (!pBuffer)
    {
        return FALSE;
    }

    /* set mandatory parameters */
    pBuffer[pos++] = storeBondMode;
    pBuffer[pos++] = storeBondSize;
    NETLONG2CHAR(&pBuffer[pos], leFixedDisplayValue);
    pos += 4;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendDeviceConfigSecuritySetReq */


BOOL LTPLibSendDeviceConfigHDPSetReq(PLTPLib pLTPLib, BYTE reconnectEnable, WORD maxRxAPDUSize,
                                     BYTE secMITMout, BYTE secAUTHORout, BYTE secMITMin, BYTE secAUTHORin,
                                     LPBYTE serviceName)
{
    BYTE   copmsk   = LTP_OPT_MASK_HEADER_CRC8;
    WORD   pos      = pLTPLib->SendOffset;
    WORD   serviceSize;
    LPBYTE pBuffer;

    serviceSize = (WORD) strlen((char*)serviceName) + 1;

    /* build packet */
    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_DEVICE_CONFIG_HDP_SET_REQ, copmsk, NULL, serviceSize);
    if (!pBuffer)
    {
        return FALSE;
    }

    /* set mandatory parameters */
    pBuffer[pos++] = reconnectEnable;
    NETSHORT2CHAR(&pBuffer[pos], maxRxAPDUSize);
    pos += 2;
    pBuffer[pos++] = secMITMout;
    pBuffer[pos++] = secAUTHORout;
    pBuffer[pos++] = secMITMin;
    pBuffer[pos++] = secAUTHORin;

    memcpy(&pBuffer[pos], serviceName, serviceSize);
    pos += serviceSize;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendDeviceConfigHDPSetReq */

BOOL LTPLibSendDeviceConfigPagescanSetReq(PLTPLib pLTPLib, BYTE scanType, BYTE repMode, WORD repInterval, WORD repWindow, WORD pageTimeout)
{
    BYTE   copmsk   = LTP_OPT_MASK_HEADER_CRC8;
    WORD   pos      = pLTPLib->SendOffset;
    LPBYTE pBuffer;

    /* build packet */
    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_DEVICE_CONFIG_PAGESCAN_SET_REQ, copmsk, NULL, 0);
    if (!pBuffer)
    {
        return FALSE;
    }

    /* set mandatory parameters */
    pBuffer[pos++] = scanType;
    pBuffer[pos++] = repMode;
    NETSHORT2CHAR(&pBuffer[pos], repInterval);
    NETSHORT2CHAR(&pBuffer[pos], repWindow);
    NETSHORT2CHAR(&pBuffer[pos], pageTimeout);

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendDeviceConfigPagescanSetReq */

BOOL LTPLibSendDeviceConfigMaxTxPowerSetReq(PLTPLib pLTPLib, BYTE txPower)
{
    BYTE   copmsk   = LTP_OPT_MASK_HEADER_CRC8;
    WORD   pos      = pLTPLib->SendOffset;
    LPBYTE pBuffer;

    /* build packet */
    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_DEVICE_CONFIG_MAXTXPOWER_SET_REQ, copmsk, NULL, 0);
    if (!pBuffer)
    {
        return FALSE;
    }

    /* set mandatory parameters */
    pBuffer[pos++] = txPower;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
}


BOOL LTPLibSendRegisterOBEXMDEPReq( PLTPLib pLTPLib, BYTE loc_MDEP_ID, WORD DataType, LPBYTE Name,
                                    WORD MDEP_OBEXDataMask, BYTE reqAuthenticationIn, BYTE reqAuthorizationIn, BYTE reqMITMIn, BYTE reqEncryptionIn
                                  )
{
    WORD   pos;
    LPBYTE pBuffer;
    WORD   nameSize;

    pos       = pLTPLib->SendOffset;
    nameSize  = (WORD) strlen((char*)Name) + 1;
    pBuffer   = LTPLibWriteHeader(pLTPLib, &pos, LTP_REGISTER_OBEX_MDEP_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, nameSize);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDEP_ID;
    NETSHORT2CHAR(&pBuffer[pos], DataType);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], MDEP_OBEXDataMask);
    pos += 2;
    pBuffer[pos++] = reqAuthenticationIn;
    pBuffer[pos++] = reqAuthorizationIn;
    pBuffer[pos++] = reqMITMIn;
    pBuffer[pos++] = reqEncryptionIn;
    memcpy(&pBuffer[pos], Name, nameSize);
    pos += nameSize;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendRegisterOBEXMDEPReq */

BOOL LTPLibSendPasskeyRequestCnf(PLTPLib pLTPLib, LPBYTE rem_BD, BYTE cause)
{
    return LTPLibSendMessage_BYTE_BD(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_PASSKEY_REQUEST_CNF, cause, rem_BD);
}


BOOL LTPLibSendRemoteOOBReqCnf(PLTPLib pLTPLib, LPBYTE rem_BD, LPBYTE C, LPBYTE R, BYTE cause)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_REMOTE_OOB_REQUEST_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return TRUE;
    }

    pBuffer[pos++] = cause;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    memcpy(&pBuffer[pos], C, 16);
    pos += 16;
    memcpy(&pBuffer[pos], R, 16);
    pos += 16;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));

} /* end of LTPLibSendRemoteOOBReqCnf */


BOOL LTPLibSendDataUnsegmented(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE returnCredits, LPBYTE payload, UINT payloadLength)
{
    return LTPLibSendMessageDataReq(pLTPLib, returnCredits, payload, loc_MDL_ID, LTP_DATA_UNSEGMENTED, payloadLength, 0, pLTPLib->SendOffset);
}


BOOL LTPLibSendDataStartSegment(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE returnCredits, UINT length_APDU, LPBYTE payload, UINT payloadLength)
{
    return LTPLibSendMessageDataReq(pLTPLib, returnCredits, payload, loc_MDL_ID, LTP_DATA_START_SEGMENT, payloadLength, length_APDU, pLTPLib->SendOffset);
}


BOOL LTPLibSendDataEndSegment(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE returnCredits, LPBYTE payload, UINT payloadLength)
{
    return LTPLibSendMessageDataReq(pLTPLib, returnCredits, payload, loc_MDL_ID, LTP_DATA_END_SEGMENT, payloadLength, 0, pLTPLib->SendOffset);
}


BOOL LTPLibSendDataContinueSegment(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE returnCredits, LPBYTE payload, UINT payloadLength)
{
    return LTPLibSendMessageDataReq(pLTPLib, returnCredits, payload, loc_MDL_ID, LTP_DATA_CONTINUE_SEGMENT, payloadLength, 0, pLTPLib->SendOffset);
}


BOOL LTPLibSendConnectMDLReq(PLTPLib pLTPLib, LPBYTE rem_BD, BYTE rem_MDEP_ID, BYTE loc_MDEP_ID,
                             WORD rem_C_PSM, WORD rem_D_PSM, BYTE LinkConfigType)
{
    BYTE   pOpt[2];
    BYTE   copmsk  = LTP_OPT_MASK_HEADER_CRC8 | LTP_CONNECT_MDL_REQ_OPT_MASK_LINK_TYPE | LTP_CONNECT_MDL_REQ_OPT_MASK_LOC_MDEP_ID;
    BYTE   posPOpt = 0;
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer;

    /* set optional parameters */
    pOpt[posPOpt++] = LinkConfigType;
    pOpt[posPOpt++] = loc_MDEP_ID;

    /* build packet */
    pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_CONNECT_MDL_REQ, copmsk, pOpt, 0);

    if (! pBuffer)
    {
        return FALSE;
    }

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;

    pBuffer[pos++] = rem_MDEP_ID;

    NETSHORT2CHAR(&pBuffer[pos], rem_C_PSM);
    pos += 2;

    NETSHORT2CHAR(&pBuffer[pos], rem_D_PSM);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendConnectMDLReq */


BOOL LTPLibSendCreateMDLCnf(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE LinkConfigType, BYTE maxTPDUusCredits, BYTE cause)
{
    BYTE pOpt[2];
    BYTE copmsk   = LTP_OPT_MASK_HEADER_CRC8 | LTP_CREATE_MDL_CNF_OPT_MASK_LINK_TYPE | LTP_CREATE_MDL_CNF_OPT_MASK_MAX_TPDU_US_CREDITS;
    BYTE pos      = 0;

    pOpt[pos++] = LinkConfigType;
    pOpt[pos++] = maxTPDUusCredits;

    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, copmsk, pOpt, LTP_CREATE_MDL_CNF, cause, loc_MDL_ID);
} /* end of LTPLibSendCreateMDLCnf */


BOOL LTPLibSendDisconnectMDLReq(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE cause)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_DISCONNECT_MDL_REQ, cause, loc_MDL_ID);
}


BOOL LTPLibSendDisconnectMDLCnf(PLTPLib pLTPLib, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_DISCONNECT_MDL_CNF, loc_MDL_ID);
}

#if (F_LTPLIB_RECONNECT_SUPPORT)
BOOL LTPLibSendReconnectMDLReq(PLTPLib pLTPLib, BYTE loc_MDL_ID, WORD rem_C_PSM, WORD rem_D_PSM)
{
    BYTE pOpt[4];
    BYTE copmsk   = LTP_OPT_MASK_HEADER_CRC8 | LTP_RECONNECT_MDL_REQ_OPT_MASK_REM_C_PSM | LTP_RECONNECT_MDL_REQ_OPT_MASK_REM_D_PSM;
    BYTE pos      = 0;

    NETSHORT2CHAR(&pOpt[pos], rem_C_PSM);
    pos += 2;
    NETSHORT2CHAR(&pOpt[pos], rem_D_PSM);
    pos += 2;

    return LTPLibSendMessage_BYTE(pLTPLib, copmsk, pOpt, LTP_RECONNECT_MDL_REQ, loc_MDL_ID);
} /* end of LTPLibSendReconnectMDLReq */


BOOL LTPLibSendReconnectMDLCnf(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE cause)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_RECONNECT_MDL_CNF, cause, loc_MDL_ID);
}
#endif /* (F_LTPLIB_RECONNECT_SUPPORT) */


BOOL LTPLibSendExitReq(PLTPLib pLTPLib, BYTE status)
{
    return LTPLibSendMessage_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_EXIT_REQ, status);
} /* end of LTPLibSendExitReq */

BOOL LTPLibSendRegisterHDPMDEPReq(PLTPLib pLTPLib, BYTE loc_MDEP_ID, WORD dataType, BYTE role, LPBYTE name)
{
    WORD   pos     = pLTPLib->SendOffset;
    WORD   strLen  = (WORD) strlen((char *)name) + 1;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_REGISTER_HDP_MDEP_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, strLen);

    if (! pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDEP_ID;

    NETSHORT2CHAR(&pBuffer[pos], dataType);
    pos += 2;

    pBuffer[pos++] = role;

    memcpy(&pBuffer[pos], name, strLen);
    pos += strLen;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendRegisterHDPMDEPReq */


BOOL LTPLibSendRegisterMDEPReq(PLTPLib pLTPLib, BYTE loc_MDEP_ID, WORD dataType, BYTE role, LPBYTE name)
{
    return LTPLibSendRegisterHDPMDEPReq(pLTPLib, loc_MDEP_ID, dataType, role, name);
} /* end of LTPLibSendRegisterMDEPReq */


BOOL LTPLibSendReleaseMDEPReq(PLTPLib pLTPLib, BYTE MDEP_Handle)
{
    return LTPLibSendMessage_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_RELEASE_MDEP_REQ, MDEP_Handle);
} /* end of LTPLibSendReleaseMDEPReq */s


BOOL LTPLibSendResetReq(PLTPLib pLTPLib)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_RESET_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (! pBuffer)
    {
        return FALSE;
    }

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendResetReq */


BOOL LTPLibSendAuthResultCnf(PLTPLib pLTPLib, LPBYTE rem_BD, DWORD AppData, BYTE cause)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_AUTH_RESULT_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (! pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;

    NETLONG2CHAR(&pBuffer[pos], AppData);
    pos += 4;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* end of LTPLibSendAuthResultCnf */

BOOL LTPLibSendAuthResultExtCnf(PLTPLib pLTPLib, BYTE cause, LPBYTE rem_BD, BYTE rem_BD_Type, DWORD AppData)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_AUTH_RESULT_EXT_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    NETLONG2CHAR(&pBuffer[pos], AppData);
    pos += 4;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendAuthResultExtCnf */


BOOL LTPLibSendAuthResultRequestExtCnf(PLTPLib pLTPLib, BYTE cause, LPBYTE rem_BD, BYTE rem_BD_Type, BYTE keyType, LPBYTE linkKey, WORD linkKeyLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_AUTH_RESULT_REQUEST_EXT_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, linkKeyLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    pBuffer[pos++] = keyType;
    memcpy(&pBuffer[pos], linkKey, linkKeyLength);
    pos += linkKeyLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendAuthResultRequestExtCnf */

#if (F_LTPLIB_GATT_SERVER_SUPPORT)
/****************************************************************************
 * LTPLibSendGATTServiceRegisterReq
 ****************************************************************************/
BOOL LTPLibSendGATTServiceRegisterReq(PLTPLib pLTPLib, BYTE serviceID,
                                      WORD nbrOfAttrib, BYTE MDL_ID,
                                      BYTE serviceChanged)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_SERVICE_REGISTER_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = serviceID;
    NETSHORT2CHAR(&pBuffer[pos], nbrOfAttrib);
    pos += 2;
    pBuffer[pos++] = MDL_ID;
    pBuffer[pos++] = serviceChanged;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTServiceRegisterReq */


/****************************************************************************
 * LTPLibSendGATTAttributeUpdateReq
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeUpdateReq(PLTPLib pLTPLib, BYTE serviceHandle,
                                      BYTE requestHandle, WORD attribIndex,
                                      LPBYTE attribData, WORD attribDataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_UPDATE_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, attribDataLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = serviceHandle;
    pBuffer[pos++] = requestHandle;
    NETSHORT2CHAR(&pBuffer[pos], attribIndex);
    pos += 2;
    memcpy(&pBuffer[pos], attribData, attribDataLength);
    pos += attribDataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeUpdateReq */


/****************************************************************************
 * LTPLibSendGATTAttributeUpdateStatusCnf
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeUpdateStatusCnf(PLTPLib pLTPLib, BYTE serviceHandle,
        BYTE requestHandle, WORD attribIndex)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_UPDATE_STATUS_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = serviceHandle;
    pBuffer[pos++] = requestHandle;
    NETSHORT2CHAR(&pBuffer[pos], attribIndex);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeUpdateStatusCnf */


/****************************************************************************
 * LTPLibSendGATTAttributeReadCnf
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeReadCnf(PLTPLib pLTPLib, BYTE cause,
                                    WORD subCause, BYTE loc_MDL_ID,
                                    BYTE serviceHandle, WORD attribIndex,
                                    LPBYTE attribData, WORD attribDataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_READ_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, attribDataLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    NETSHORT2CHAR(&pBuffer[pos], subCause);
    pos += 2;
    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = serviceHandle;
    NETSHORT2CHAR(&pBuffer[pos], attribIndex);
    pos += 2;
    memcpy(&pBuffer[pos], attribData, attribDataLength);
    pos += attribDataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeReadCnf */


/****************************************************************************
 * LTPLibSendGATTAttributeWriteCnf
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeWriteCnf(PLTPLib pLTPLib, BYTE cause,
                                     WORD subCause, BYTE loc_MDL_ID,
                                     BYTE serviceHandle, WORD attribIndex)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_WRITE_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    NETSHORT2CHAR(&pBuffer[pos], subCause);
    pos += 2;
    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = serviceHandle;
    NETSHORT2CHAR(&pBuffer[pos], attribIndex);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeWriteCnf */
#endif /* (F_LTPLIB_GATT_SERVER_SUPPORT) */


#if (F_LTPLIB_GATT_SERVER_SUPPORT) || (F_LTPLIB_LE_SUPPORT)
/****************************************************************************
 * LTPLibSendGATTServerStoreCnf
 ****************************************************************************/
BOOL LTPLibSendGATTServerStoreCnf(PLTPLib pLTPLib, BYTE cause,
                                  BYTE opCode, LPBYTE rem_BD,
                                  BYTE rem_BD_Type, WORD restartHandle,
                                  LPBYTE data, WORD dataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_SERVER_STORE_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    pBuffer[pos++] = opCode;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    NETSHORT2CHAR(&pBuffer[pos], restartHandle);
    pos += 2;
    memcpy(&pBuffer[pos], data, dataLength);
    pos += dataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTServerStoreCnf */
#endif /* (F_LTPLIB_GATT_SERVER_SUPPORT) || (F_LTPLIB_LE_SUPPORT) */


#if (F_LTPLIB_GATT_CLIENT_SUPPORT)
/****************************************************************************
 * LTPLibSendConnectGATTMDLReq
 ****************************************************************************/
BOOL LTPLibSendConnectGATTMDLReq(PLTPLib pLTPLib, LPBYTE rem_BD,
                                 BYTE rem_BD_Type, WORD scanInterval,
                                 WORD scanWindow, WORD scanTimeout,
                                 WORD connIntervalMin, WORD connIntervalMax,
                                 WORD connLatency, WORD supervisionTimeout)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_CONNECT_GATT_MDL_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;
    NETSHORT2CHAR(&pBuffer[pos], scanInterval);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], scanWindow);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], scanTimeout);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connIntervalMin);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connIntervalMax);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connLatency);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], supervisionTimeout);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendConnectGATTMDLReq */


/****************************************************************************
 * LTPLibSendGATTDiscoveryReq
 ****************************************************************************/
BOOL LTPLibSendGATTDiscoveryReq(PLTPLib pLTPLib, BYTE loc_MDL_ID,
                                BYTE discoveryType, WORD startHandle,
                                WORD endHandle, WORD uuid16,
                                LPBYTE uuid128)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_DISCOVERY_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = discoveryType;
    NETSHORT2CHAR(&pBuffer[pos], startHandle);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], endHandle);
    pos += 2;
    if ((uuid16 == 0x0000) && (uuid128 != NULL))
    {
        memcpy(&pBuffer[pos], uuid128, 16);
        pos += 16;
    }
    else
    {
        NETSHORT2CHAR(&pBuffer[pos], uuid16);
        pos += 2;
    }

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTDiscoveryReq */


/****************************************************************************
 * LTPLibSendGATTDiscoveryCnf
 ****************************************************************************/
BOOL LTPLibSendGATTDiscoveryCnf(PLTPLib pLTPLib, BYTE cause,
                                BYTE loc_MDL_ID, BYTE discoveryType,
                                WORD startHandle, WORD endHandle)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_DISCOVERY_CNF, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = cause;
    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = discoveryType;
    NETSHORT2CHAR(&pBuffer[pos], startHandle);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], endHandle);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTDiscoveryCnf */


/****************************************************************************
 * LTPLibSendGATTAttributeReadReq
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeReadReq(PLTPLib pLTPLib, BYTE loc_MDL_ID,
                                    BYTE readType, WORD readOffset,
                                    WORD startHandle, WORD endHandle,
                                    WORD uuid16, LPBYTE uuid128)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_READ_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = readType;
    NETSHORT2CHAR(&pBuffer[pos], readOffset);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], startHandle);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], endHandle);
    pos += 2;
    if ((uuid16 == 0x0000) && (uuid128 != NULL))
    {
        memcpy(&pBuffer[pos], uuid128, 16);
        pos += 16;
    }
    else
    {
        NETSHORT2CHAR(&pBuffer[pos], uuid16);
        pos += 2;
    }

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeReadReq */


/****************************************************************************
 * LTPLibSendGATTAttributeWriteReq
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeWriteReq(PLTPLib pLTPLib, BYTE loc_MDL_ID,
                                     BYTE writeType, WORD attribHandle,
                                     WORD writeOffset, LPBYTE data,
                                     WORD dataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_GATT_ATTRIBUTE_WRITE_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, dataLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    pBuffer[pos++] = writeType;
    NETSHORT2CHAR(&pBuffer[pos], attribHandle);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], writeOffset);
    pos += 2;
    memcpy(&pBuffer[pos], data, dataLength);
    pos += dataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendGATTAttributeWriteReq */


/****************************************************************************
 * LTPLibSendGATTAttributeCnf
 ****************************************************************************/
BOOL LTPLibSendGATTAttributeCnf(PLTPLib pLTPLib, BYTE cause, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_GATT_ATTRIBUTE_CNF, cause, loc_MDL_ID);
} /* LTPLibSendGATTAttributeCnf */ 


#endif /* (F_LTPLIB_GATT_CLIENT_SUPPORT) */

#if (F_LTPLIB_LE_SUPPORT)
/****************************************************************************
 * LTPLibSendLEAdvertiseReq
 ****************************************************************************/
BOOL LTPLibSendLEAdvertiseReq(PLTPLib pLTPLib, BYTE advMode,
                              LPBYTE rem_BD, BYTE rem_BD_Type)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_ADVERTISE_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = advMode;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEAdvertiseReq */


/****************************************************************************
 * LTPLibSendLEAdvertiseParameterSetReq
 ****************************************************************************/
BOOL LTPLibSendLEAdvertiseParameterSetReq(PLTPLib pLTPLib, BYTE advType,
        BYTE filterScanReq, BYTE filterConnectReq,
        WORD minAdvInterval, WORD maxAdvInterval
                                         )
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_ADVERTISE_PARAMETER_SET_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = advType;
    pBuffer[pos++] = filterScanReq;
    pBuffer[pos++] = filterConnectReq;
    NETSHORT2CHAR(&pBuffer[pos], minAdvInterval);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], maxAdvInterval);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEAdvertiseParameterSetReq */


/****************************************************************************
 * LTPLibSendLEAdvertiseDataSetReq
 ****************************************************************************/
BOOL LTPLibSendLEAdvertiseDataSetReq(PLTPLib pLTPLib, BYTE dataType,
                                     LPBYTE data, WORD dataLength)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_ADVERTISE_DATA_SET_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, dataLength);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = dataType;
    memcpy(&pBuffer[pos], data, dataLength);
    pos += dataLength;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEAdvertiseDataSetReq */


/****************************************************************************
 * LTPLibSendLEScanReq
 ****************************************************************************/
BOOL LTPLibSendLEScanReq(PLTPLib pLTPLib, BYTE scanMode,
                         WORD scanInterval, WORD scanWindow,
                         BYTE filterPolicy, BYTE filterDuplicates)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_SCAN_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = scanMode;
    NETSHORT2CHAR(&pBuffer[pos], scanInterval);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], scanWindow);
    pos += 2;
    pBuffer[pos++] = filterPolicy;
    pBuffer[pos++] = filterDuplicates;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEScanReq */


/****************************************************************************
 * LTPLibSendLEModifyWhitelistReq
 ****************************************************************************/
BOOL LTPLibSendLEModifyWhitelistReq(PLTPLib pLTPLib, BYTE whitelistOp,
                                    LPBYTE rem_BD, BYTE rem_BD_Type)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_MODIFY_WHITELIST_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = whitelistOp;
    memcpy(&pBuffer[pos], rem_BD, 6);
    pos += 6;
    pBuffer[pos++] = rem_BD_Type;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEModifyWhitelistReq */


/****************************************************************************
 * LTPLibSendLEConnectionUpdateReq
 ****************************************************************************/
BOOL LTPLibSendLEConnectionUpdateReq(PLTPLib pLTPLib, BYTE loc_MDL_ID,
                                     WORD connIntervalMin, WORD connIntervalMax,
                                     WORD connLatency, WORD supervisionTimeout)
{
    WORD   pos     = pLTPLib->SendOffset;
    LPBYTE pBuffer = LTPLibWriteHeader(pLTPLib, &pos, LTP_LE_CONNECTION_UPDATE_REQ, LTP_OPT_MASK_HEADER_CRC8, NULL, 0);

    if (!pBuffer)
    {
        return FALSE;
    }

    pBuffer[pos++] = loc_MDL_ID;
    NETSHORT2CHAR(&pBuffer[pos], connIntervalMin);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connIntervalMax);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], connLatency);
    pos += 2;
    NETSHORT2CHAR(&pBuffer[pos], supervisionTimeout);
    pos += 2;

    return (BTLTPTgtSendLTPMessage(pLTPLib->AppHandle, pBuffer, pLTPLib->SendOffset, pos - pLTPLib->SendOffset));
} /* LTPLibSendLEConnectionUpdateReq */


/****************************************************************************
 * LTPLibSendLEConnectionUpdateCnf
 ****************************************************************************/
BOOL LTPLibSendLEConnectionUpdateCnf(PLTPLib pLTPLib, BYTE cause, BYTE loc_MDL_ID)
{
    return LTPLibSendMessage_BYTE_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_LE_CONNECTION_UPDATE_CNF, cause, loc_MDL_ID);
} /* LTPLibSendLEConnectionUpdateCnf */

#if (F_LTPLIB_LE_PRIVACY_SUPPORT)
/****************************************************************************
 * LTPLibSendLEPrivacyModeReq
 ****************************************************************************/
BOOL LTPLibSendLEPrivacyModeReq(PLTPLib pLTPLib, BYTE privacyMode)
{
    return LTPLibSendMessage_BYTE(pLTPLib, LTP_OPT_MASK_HEADER_CRC8, NULL, LTP_LE_PRIVACY_MODE_REQ, privacyMode);
} /* LTPLibSendLEConnectionUpdateCnf */
#endif /* (F_LTPLIB_LE_PRIVACY_SUPPORT) */
#endif /* (F_LTPLIB_LE_SUPPORT) */


BOOL LTPLibSendDataUnsegmented(PLTPLib pLTPLib, BYTE loc_MDL_ID, BYTE returnCredits, LPBYTE payload, UINT payloadLength)
{
    return LTPLibSendMessageDataReq(pLTPLib, returnCredits, payload, loc_MDL_ID, LTP_DATA_UNSEGMENTED, payloadLength, 0, pLTPLib->SendOffset);
}

#endif /* F_LTPLIB_MDH_SUPPORT */
