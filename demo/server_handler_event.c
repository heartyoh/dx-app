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

int demo_client_fd_in_server = -1;

int server_handler_evt_connect(int fd, dx_packet_t* packet);
int server_handler_evt_disconnect(int fd, dx_packet_t* packet);

int server_handler_event(int fd, dx_packet_t* packet) {
    printf("(Server Event Handling) Event(%d)\n", packet->header.code);

    switch(packet->header.code) {

    case DEMO_EVT_CONNECT                  :   /* 서버가 연결되었을 때 발생 */
    	demo_client_fd_in_server = fd;
    	server_handler_evt_connect(fd, packet);
        break;
    case DEMO_EVT_DISCONNECT               :   /* 서버 연결이 끊겼을 때 발생 */
    	server_handler_evt_disconnect(fd, packet);
    	demo_client_fd_in_server = -1;
        break;
    case DEMO_EVT_ERROR                    :   /* 오류 발생 이벤트 */
        break;
    case DEMO_EVT_ALARM                    :   /* 경고 발생 이벤트 */
        break;
    case DEMO_EVT_CHANGE_VIEW_MODE         :   /* 현재 뷰모드의 변화 */
        break;
    case DEMO_EVT_CHANGE_TURN_SIGNAL       :   /* 방향지시등 상태 변화 : LEFT, WRITE, NONE */
        break;
    case DEMO_EVT_CHANGE_R_GEAR      :   /* 후진 기어 상태 변화 : ON/OFF */
        break;
    case DEMO_EVT_CHANGE_EMERGENCY_SIGNAL  :   /* 비상등 상태 변화 : ON/OFF */
        break;
    case DEMO_EVT_CHANGE_GPS_ONOFF         :   /* GPS 상태 변화 : ON/OFF */
        break;
    case DEMO_EVT_CHANGE_EMERGENCY_RECORD  :   /* 긴급녹화 상태 변화 : BEGIN / END */
        break;
    case DEMO_EVT_CHANGE_RECORD            :   /* 블랙박스 상시녹화 상태 변화 : BEGIN / END */
        break;
    case DEMO_EVT_CHANGE_STORAGE_USAGE     :   /* 자장장치 사용량 변화 */
        break;
    case DEMO_EVT_UPDATE_BEGIN             :   /* 서버 프로그램 업데이트 시작 */
        break;
    case DEMO_EVT_UPDATE_PROGRESS          :   /* 서버 프로그램 업데이트 진행율 변화 */
        break;
    case DEMO_EVT_UPDATE_END               :   /* 서버 프로그램 업데이트 종료 */
        break;
    case DEMO_EVT_CHANGE_RECORDING_TIME    :   /* 녹화 진행 시간 변화 */
        break;
    case DEMO_EVT_RECORD_EVENT_FINISH      :   /* 이벤트 녹화 완료 */
    	break;
    case DEMO_EVT_FORMAT_SDCARD_1_FINISH   :   /* SD카드 1 포맷 완료 */
    	break;
    case DEMO_EVT_FORMAT_SDCARD_2_FINISH   :   /* SD카드 2 포맷 완료 */
    	break;
    default :
        break;

    }

    return 0;
}

int server_handler_evt_connect(int fd, dx_packet_t* packet) {
	CONSOLE("(Server Event Handler) Client Connected\n");

    return 0;
}

int server_handler_evt_disconnect(int fd, dx_packet_t* packet) {
	CONSOLE("(Server Event Handler) Client Disconnected\n");

    return 0;
}
