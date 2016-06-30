// Copyright (c) 2015 - 2015 All Right Reserved, http://hatiolab.com
//
// This source is subject to the Hatio Lab. Permissive License.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WIHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
#include "demo-const.h"

void demo_on_playback_start(int fd, dx_packet_t* packet);
void demo_on_playback_stop(int fd);

void demo_on_live_start(int fd);
void demo_on_live_stop(int fd);

int server_handler_command(int fd, dx_packet_t* packet) {
    printf("(Server Event Handling) Command(%d)\n", packet->header.code);

    switch(packet->header.code) {

    case DEMO_CMD_RECORD_EMERGENCY_VIDEO       :   /* 긴급 녹화 명령 */
        break;
    case DEMO_CMD_CAPTURE_EMERGENCY_STILLCUT   :   /* 긴급 사진캡쳐 명령 */
        break;

    case DEMO_CMD_START_PLAYBACK :   /* 플레이백 스트림 시작 명령 */
    	demo_on_playback_start(fd, packet);
    	break;

    case DEMO_CMD_STOP_PLAYBACK  :   /* 플레이백 스트림 종료 명령 */
    	demo_on_playback_stop(fd);
    	break;

    case DEMO_CMD_START_LIVE :   /* Live 스트림 시작 명령 */
    	demo_on_live_start(fd);
    	break;

    case DEMO_CMD_STOP_LIVE  :   /* Live 스트림 종료 명령 */
    	demo_on_live_stop(fd);
    	break;

    case DEMO_CMD_FORMAT_SDCARD_1 :  /* SD 카드 1 포맷 명령 */
    	break;
    case DEMO_CMD_FORMAT_SDCARD_2 :  /* SD 카드 2 포맷 명령 */
    	break;
    default :
        break;

    }

    return 0;
}

