// Copyright (c) 2015 - 2015 All Right Reserved, http://hatiolab.com
//
// This source is subject to the Hatio, Lab. Permissive License.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WIHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//

#ifndef __DX_NET_COMMON_H
#define __DX_NET_COMMON_H

#include <netinet/in.h>   // For uint16_t

/*
 * Definitions
 */

/* Discovery Code */
#define DX_DISCOVERY_BASE       0x00
#define DX_DISCOVERY_REQ        (DX_DISCOVERY_BASE + 0) /* Discovery 요청 */
#define DX_DISCOVERY_RESP       (DX_DISCOVERY_BASE + 1) /* Discovery 응답 */

/* Settings */

#define DX_SET_BASE                 0x00

/* Volatile Status - 상태 */

#define DX_STAT_BASE                    0x00

/* Event Types */

#define DX_EVT_BASE                     0x00
#define DX_EVT_CONNECT                  (DX_EVT_BASE + 0)   /* 연결되었을 때 발생 */
#define DX_EVT_DISCONNECT               (DX_EVT_BASE + 1)   /* 연결이 끊겼을 때 발생 */

/* Alarm Code */

#define DX_ALM_BASE                     0x00

/* Error Code */

#define DX_ERR_BASE                     0x00

/* Commands */

#define DX_CMD_BASE                         0x00

/* File */
#define DX_FILE_BASE                    0x00
#define DX_FILE_GET_LIST                (DX_FILE_BASE + 0)
#define DX_FILE_LIST                    (DX_FILE_BASE + 1)
#define DX_FILE_GET                     (DX_FILE_BASE + 2)
#define DX_FILE                         (DX_FILE_BASE + 3)
#define DX_FILE_DELETE                  (DX_FILE_BASE + 4)

/* Stream */
#define DX_STREAM_BASE          		0x00
#define DX_STREAM           			(DX_STREAM_BASE + 0)
#define DX_STREAM_PLAYBACK				(DX_STREAM_BASE + 1)
#define DX_STREAM_LIVE_MCH			    (DX_STREAM_BASE + 2)
#define DX_STREAM_LIVE				    (DX_STREAM_BASE + 3)

/* Movie Playback */
#define DX_MOVIE_BASE					0x00
#define DX_MOVIE_GET_INFO				(DX_MOVIE_BASE + 0)
#define DX_MOVIE_INFO					(DX_MOVIE_BASE + 1)
#define DX_MOVIE_COMMAND_START			(DX_MOVIE_BASE + 2)
#define DX_MOVIE_COMMAND_STOP			(DX_MOVIE_BASE + 3)
#define DX_MOVIE_COMMAND_RESUME			(DX_MOVIE_BASE + 4)
#define DX_MOVIE_COMMAND_PAUSE			(DX_MOVIE_BASE + 5)
#define DX_MOVIE_FRAME					(DX_MOVIE_BASE + 6)

/* NET */

#define DX_DEFAULT_SERVICE_PORT 2015
#define DX_SOCKET_BUF_SIZE  (8192 * 4)
#define DX_DGRAM_BUF_SIZE  (8192 * 4)

#define ntohll(x) (((uint64_t)(ntohl((uint32_t)((x<<32)>>32))) << 32) | ntohl( ((uint32_t)(x >> 32))))
#define htonll(x) ntohll(x)

#endif /* __DX_NET_COMMON_H */
