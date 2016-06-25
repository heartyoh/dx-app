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

#ifndef __DEMO_CONST_H
#define __DEMO_CONST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "dx.h"

#include "dx_debug_malloc.h"
#include "dx_debug_assert.h"

#include "dx_util_schedule.h"
#include "dx_util_log.h"

#include "dx_file_avi.h"

#include "dx_console.h"

#include "dx_event_mplexer.h"

#include "dx_net_discovery.h"
#include "dx_net_server.h"
#include "dx_net_client.h"
#include "dx_net_packet.h"
#include "dx_net_packet_file.h"
#include "dx_net_packet_io.h"
#include "dx_net_packet_movie_playback.h"

#include "dx_camera.h"

/*
 * Definitions
 */
typedef struct server_value {
	uint8_t				state;
	dx_primitive_data_t	data;
} server_value_t;

extern server_value_t server_settings[];
extern server_value_t server_status[];

typedef struct client_value {
	uint8_t				state;
	dx_primitive_data_t	data;
} client_value_t;

extern client_value_t client_settings[];
extern client_value_t client_status[];

int server_handler_hb(int fd, dx_packet_t* packet);
int server_handler_get_setting(int fd, dx_packet_t* packet);
int server_handler_set_setting(int fd, dx_packet_t* packet);
int server_handler_get_state(int fd, dx_packet_t* packet);
int server_handler_set_state(int fd, dx_packet_t* packet);
int server_handler_event(int fd, dx_packet_t* packet);
int server_handler_command(int fd, dx_packet_t* packet);
int server_handler_file(int fd, dx_packet_t* packet);
int server_handler_movie(int fd, dx_packet_t* packet);

int client_handler_hb(int fd, dx_packet_t* packet);
int client_handler_get_setting(int fd, dx_packet_t* packet);
int client_handler_set_setting(int fd, dx_packet_t* packet);
int client_handler_get_state(int fd, dx_packet_t* packet);
int client_handler_set_state(int fd, dx_packet_t* packet);
int client_handler_event(int fd, dx_packet_t* packet);
int client_handler_command(int fd, dx_packet_t* packet);
int client_handler_get_file_list(int fd, dx_packet_t* packet);
int client_handler_file_list(int fd, dx_packet_t* packet);
int client_handler_get_file(int fd, dx_packet_t* packet);
int client_handler_file(int fd, dx_packet_t* packet);
int client_handler_stream(int fd, dx_packet_t* packet);
int client_handler_movie(int fd, dx_packet_t* packet);

/* codes */
/* Streaming View Modes */

#define DEMO_VIEW_NONE                    0x00    /* 스트리밍을 오프시킴 */
#define DEMO_VIEW_TOP_FRONT               0x01    /* 탑뷰 + 전방 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_TOP_REAR                0x02    /* 탑뷰 + 후방 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_TOP_LEFT                0x03    /* 탑뷰 + 좌측 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_TOP_RIGHT               0x04    /* 탑뷰 + 우측 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_TOP_LEFT_RIGHT          0x05    /* 탑뷰 + 양측 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_FULL_TOP                0x06    /* 전면 탑뷰 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_FULL_FRONT              0x07    /* 전면 전방 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_FULL_REAR               0x08    /* 전면 후방 : 800 x 480 or 680 x 480 */
#define DEMO_VIEW_TOP                     0x09    /* 탑뷰 : 264 x 600 or 264 x 480 */
#define DEMO_VIEW_4CH                     0x0A    /* 4분면의 RAW 영상 : 1440 x 960 */
#define DEMO_VIEW_HD						          0x0B	/* HD 카메라 영상 : 1280 X 720 */

/* Discovery Code */
#define DEMO_DISCOVERY_BASE				0x00
#define DEMO_DISCOVERY_REQ				(DEMO_DISCOVERY_BASE + 0)	/* Discovery 요청 */
#define DEMO_DISCOVERY_RESP				(DEMO_DISCOVERY_BASE + 1)	/* Discovery 응답 */

/* Settings */

#define DEMO_SETTING_BASE                 0x00
#define DEMO_SET_VIEW_DEFAULT             (DEMO_SETTING_BASE + 0)   /* 디폴트 뷰 */
#define DEMO_SET_VIEW_ON_R_GEAR           (DEMO_SETTING_BASE + 1)   /* 후진기어모드 상태시 뷰 */
#define DEMO_SET_VIEW_ON_TURN_RIGHT       (DEMO_SETTING_BASE + 2)   /* 우측 방향지시등 상태시 뷰 */
#define DEMO_SET_VIEW_ON_TURN_LEFT        (DEMO_SETTING_BASE + 3)   /* 좌측 방향지시등 상태시 뷰 */
#define DEMO_SET_VIEW_ON_EMERGENCY_SIGNAL (DEMO_SETTING_BASE + 4)   /* 비상등 점멸시 뷰 */
#define DEMO_SET_VIEW_ON_PARKING          (DEMO_SETTING_BASE + 5)   /* 주차 상황시 뷰 */
#define DEMO_SET_VIEW_ON_CROSSING         (DEMO_SETTING_BASE + 6)   /* 교차로 주행 상황시 뷰 */
#define DEMO_SET_VIEW_ON_ALLEY            (DEMO_SETTING_BASE + 7)   /* 좁은 골목길 주행 상황시 뷰 */
#define DEMO_SET_FRONT_VIEW_HOLDING_TIME  (DEMO_SETTING_BASE + 8)   /* 전방 뷰 유지 시간 - OFF 상태에서 후진기어 입력 후 해제시 전방 뷰 화면 유지시간 */
#define DEMO_SET_SPEED_LIMIT_USE          (DEMO_SETTING_BASE + 9)   /* 설정 속도 이상으로 주행시 화면 꺼짐 동작 여부 */
#define DEMO_SET_SPEED_LIMIT              (DEMO_SETTING_BASE + 10)  /* 제한 속도 */
#define DEMO_SET_VIEW_ON_DRIVING          (DEMO_SETTING_BASE + 11)  /* 속도 제한 이상 주행시 뷰 */
#define DEMO_SET_PARKING_ASSIST_LINE      (DEMO_SETTING_BASE + 12)  /* 파킹 가이드라인 표시 여부 */

#define DEMO_SET_ALARM_BSD                (DEMO_SETTING_BASE + 14)  /* 후측방 사각지대 물체 인식시 경고 여부 */
#define DEMO_SET_ALARM_LDWS               (DEMO_SETTING_BASE + 15)  /* 차선 이탈시 경고 여부 */
#define DEMO_SET_INFO_ON_DASHBOARD        (DEMO_SETTING_BASE + 16)  /* 화면의 특정위치에 표시할 정보 (시계/주행속도) */
#ifdef  DEMO_SET_INFO_ON_DASHBOARD
    #define DEMO_VAL_CLOCK    0x00
    #define DEMO_VAL_SPEED    0x01
#endif
#define DEMO_SET_DUAL_MODE                (DEMO_SETTING_BASE + 17)  /* 듀얼화면 사용 여부 */
#define DEMO_SET_APP_AUTO_START           (DEMO_SETTING_BASE + 18)  /* 패드 부팅시 앱 자동 시작 */
#define DEMO_SET_SHOW_HELP                (DEMO_SETTING_BASE + 19)  /* 도움말 화면 표시 여부 */

#define DEMO_SET_APP_VERSION              (DEMO_SETTING_BASE + 20)  /* 어플리케이션 버전 - READ ONLY */
#define DEMO_SET_FW_VERSION               (DEMO_SETTING_BASE + 21)  /* 펌웨어 버전 - READ ONLY */
#define DEMO_SET_MICOM_VERSION            (DEMO_SETTING_BASE + 22)  /* 마이콤 버전 - READ ONLY */

#define DEMO_SET_SPEED_INFO_FROM_ECU		(DEMO_SETTING_BASE + 23)  /* ECU의 속도정보를 받는지 여부. */

/* My Car Settings */

#define DEMO_SET_MYCAR_BASE               0x20
#define DEMO_SET_CAR_FULL_WIDTH           (DEMO_SET_MYCAR_BASE + 0)     /* 전폭 */
#define DEMO_SET_CAR_FULL_LENGTH          (DEMO_SET_MYCAR_BASE + 1)     /* 전장 */
#define DEMO_SET_CAR_WHEEL_BASE           (DEMO_SET_MYCAR_BASE + 2)     /* 축거 */

/* Camera Settings */

#define DEMO_SET_CAMERA_BASE              0x30
#define DEMO_SET_CAR_IMAGE_ID             (DEMO_SET_CAMERA_BASE + 0)    /* TOP_VIEW에서 블라인드 영역에 사용되는 차량 TOP 이미지 */
#define DEMO_SET_CAR_IMAGE_WIDTH          (DEMO_SET_CAMERA_BASE + 1)    /* 이미지가 디스플레이될 영역의 폭 */
#define DEMO_SET_CAR_IMAGE_HEIGHT         (DEMO_SET_CAMERA_BASE + 2)    /* 이미지가 디스플레이될 영역의 높이 */
#define DEMO_SET_CAR_IMAGE_X              (DEMO_SET_CAMERA_BASE + 3)    /* 이미지가 디스플레이될 영역의 X 포지션 */
#define DEMO_SET_CAR_IMAGE_Y              (DEMO_SET_CAMERA_BASE + 4)    /* 이미지가 디스플레이될 영역의 Y 포지션 */
#define DEMO_SET_BLIND_MASK_WIDTH         (DEMO_SET_CAMERA_BASE + 5)    /* 블라인드 영역의 폭 */
#define DEMO_SET_BLIND_MASK_HEIGHT        (DEMO_SET_CAMERA_BASE + 6)    /* 블라인드 영역의 높이 */
#define DEMO_SET_BLIND_MASK_X             (DEMO_SET_CAMERA_BASE + 7)    /* 블라인드 영역의 X 포지션 */
#define DEMO_SET_BLIND_MASK_Y             (DEMO_SET_CAMERA_BASE + 8)    /* 블라인드 영역의 Y 포지션 */
#define DEMO_SET_VIDEO_PARAMS             (DEMO_SET_CAMERA_BASE + 9)    /* 공차보정 후 생성되는 영상 변환 파라미터들 */

#define DEMO_SET_VIEW_TOP_FRONT_X         (DEMO_SET_CAMERA_BASE + 10)   /* TOP-FRONT VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_TOP_FRONT_Y         (DEMO_SET_CAMERA_BASE + 11)   /* TOP-FRONT VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_TOP_FRONT_WIDTH     (DEMO_SET_CAMERA_BASE + 12)   /* TOP-FRONT VIEW의 WIDTH */
#define DEMO_SET_VIEW_TOP_FRONT_HEIGHT    (DEMO_SET_CAMERA_BASE + 13)   /* TOP-FRONT VIEW의 HEIGHT */
#define DEMO_SET_VIEW_TOP_FRONT_ZOOM      (DEMO_SET_CAMERA_BASE + 14)   /* TOP-FRONT VIEW의 ZOOM */
#define DEMO_SET_VIEW_TOP_FRONT_ROTATE    (DEMO_SET_CAMERA_BASE + 15)   /* TOP-FRONT VIEW의 ROTATE */

#define DEMO_SET_VIEW_TOP_REAR_X          (DEMO_SET_CAMERA_BASE + 16)   /* TOP-REAR VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_TOP_REAR_Y          (DEMO_SET_CAMERA_BASE + 17)   /* TOP-REAR VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_TOP_REAR_WIDTH      (DEMO_SET_CAMERA_BASE + 18)   /* TOP-REAR VIEW의 WIDTH */
#define DEMO_SET_VIEW_TOP_REAR_HEIGHT     (DEMO_SET_CAMERA_BASE + 19)   /* TOP-REAR VIEW의 HEIGHT */
#define DEMO_SET_VIEW_TOP_REAR_ZOOM       (DEMO_SET_CAMERA_BASE + 20)   /* TOP-REAR VIEW의 ZOOM */
#define DEMO_SET_VIEW_TOP_REAR_ROTATE     (DEMO_SET_CAMERA_BASE + 21)   /* TOP-REAR VIEW의 ROTATE */

#define DEMO_SET_VIEW_TOP_LEFT_X          (DEMO_SET_CAMERA_BASE + 22)   /* TOP-LEFT VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_TOP_LEFT_Y          (DEMO_SET_CAMERA_BASE + 23)   /* TOP-LEFT VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_TOP_LEFT_WIDTH      (DEMO_SET_CAMERA_BASE + 24)   /* TOP-LEFT VIEW의 WIDTH */
#define DEMO_SET_VIEW_TOP_LEFT_HEIGHT     (DEMO_SET_CAMERA_BASE + 25)   /* TOP-LEFT VIEW의 HEIGHT */
#define DEMO_SET_VIEW_TOP_LEFT_ZOOM       (DEMO_SET_CAMERA_BASE + 26)   /* TOP-LEFT VIEW의 ZOOM */
#define DEMO_SET_VIEW_TOP_LEFT_ROTATE     (DEMO_SET_CAMERA_BASE + 27)   /* TOP-LEFT VIEW의 ROTATE */

#define DEMO_SET_VIEW_TOP_RIGHT_X         (DEMO_SET_CAMERA_BASE + 28)   /* TOP-RIGHT VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_TOP_RIGHT_Y         (DEMO_SET_CAMERA_BASE + 29)   /* TOP-RIGHT VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_TOP_RIGHT_WIDTH     (DEMO_SET_CAMERA_BASE + 30)   /* TOP-RIGHT VIEW의 WIDTH */
#define DEMO_SET_VIEW_TOP_RIGHT_HEIGHT    (DEMO_SET_CAMERA_BASE + 31)   /* TOP-RIGHT VIEW의 HEIGHT */
#define DEMO_SET_VIEW_TOP_RIGHT_ZOOM      (DEMO_SET_CAMERA_BASE + 32)   /* TOP-RIGHT VIEW의 ZOOM */
#define DEMO_SET_VIEW_TOP_RIGHT_ROTATE    (DEMO_SET_CAMERA_BASE + 33)   /* TOP-RIGHT VIEW의 ROTATE */

#define DEMO_SET_VIEW_TOP_LEFT_RIGHT_X         (DEMO_SET_CAMERA_BASE + 34)   /* TOP-LEFT-RIGHT VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_TOP_LEFT_RIGHT_Y         (DEMO_SET_CAMERA_BASE + 35)   /* TOP-LEFT-RIGHT VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_TOP_LEFT_RIGHT_WIDTH     (DEMO_SET_CAMERA_BASE + 36)   /* TOP-LEFT-RIGHT VIEW의 WIDTH */
#define DEMO_SET_VIEW_TOP_LEFT_RIGHT_HEIGHT    (DEMO_SET_CAMERA_BASE + 37)   /* TOP-LEFT-RIGHT VIEW의 HEIGHT */
#define DEMO_SET_VIEW_TOP_LEFT_RIGHT_ZOOM      (DEMO_SET_CAMERA_BASE + 38)   /* TOP-LEFT-RIGHT VIEW의 ZOOM */
#define DEMO_SET_VIEW_TOP_LEFT_RIGHT_ROTATE    (DEMO_SET_CAMERA_BASE + 39)   /* TOP-LEFT-RIGHT VIEW의 ROTATE */

#define DEMO_SET_VIEW_TOP_FULL_X          (DEMO_SET_CAMERA_BASE + 40)   /* TOP-FULL VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_TOP_FULL_Y          (DEMO_SET_CAMERA_BASE + 41)   /* TOP-FULL VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_TOP_FULL_WIDTH      (DEMO_SET_CAMERA_BASE + 42)   /* TOP-FULL VIEW의 WIDTH */
#define DEMO_SET_VIEW_TOP_FULL_HEIGHT     (DEMO_SET_CAMERA_BASE + 43)   /* TOP-FULL VIEW의 HEIGHT */
#define DEMO_SET_VIEW_TOP_FULL_ZOOM       (DEMO_SET_CAMERA_BASE + 44)   /* TOP-FULL VIEW의 ZOOM */
#define DEMO_SET_VIEW_TOP_FULL_ROTATE     (DEMO_SET_CAMERA_BASE + 45)   /* TOP-FULL VIEW의 ROTATE */

#define DEMO_SET_VIEW_FRONT_FULL_X        (DEMO_SET_CAMERA_BASE + 46)   /* FRONT-FULL VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_FRONT_FULL_Y        (DEMO_SET_CAMERA_BASE + 47)   /* FRONT-FULL VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_FRONT_FULL_WIDTH    (DEMO_SET_CAMERA_BASE + 48)   /* FRONT-FULL VIEW의 WIDTH */
#define DEMO_SET_VIEW_FRONT_FULL_HEIGHT   (DEMO_SET_CAMERA_BASE + 49)   /* FRONT-FULL VIEW의 HEIGHT */
#define DEMO_SET_VIEW_FRONT_FULL_ZOOM     (DEMO_SET_CAMERA_BASE + 50)   /* FRONT-FULL VIEW의 ZOOM */
#define DEMO_SET_VIEW_FRONT_FULL_ROTATE   (DEMO_SET_CAMERA_BASE + 51)   /* FRONT-FULL VIEW의 ROTATE */

#define DEMO_SET_VIEW_REAR_FULL_X         (DEMO_SET_CAMERA_BASE + 52)   /* REAR-FULL VIEW의 OFFSET-X */
#define DEMO_SET_VIEW_REAR_FULL_Y         (DEMO_SET_CAMERA_BASE + 53)   /* REAR-FULL VIEW의 OFFSET-Y */
#define DEMO_SET_VIEW_REAR_FULL_WIDTH     (DEMO_SET_CAMERA_BASE + 54)   /* REAR-FULL VIEW의 WIDTH */
#define DEMO_SET_VIEW_REAR_FULL_HEIGHT    (DEMO_SET_CAMERA_BASE + 55)   /* REAR-FULL VIEW의 HEIGHT */
#define DEMO_SET_VIEW_REAR_FULL_ZOOM      (DEMO_SET_CAMERA_BASE + 56)   /* REAR-FULL VIEW의 ZOOM */
#define DEMO_SET_VIEW_REAR_FULL_ROTATE    (DEMO_SET_CAMERA_BASE + 57)   /* REAR-FULL VIEW의 ROTATE */

/* Dash Cam Settings */

#define DEMO_SET_DASHCAM_BASE            	0x80
#define	DEMO_SET_RECORD_MOTION_LEVEL		(DEMO_SET_DASHCAM_BASE)		/* 모션 센싱 레벨 (0-9) */
#define	DEMO_SET_RECORD_POWER_CUT_VOLTAGE	(DEMO_SET_DASHCAM_BASE + 1)	/* 전원 차단 레벨 전압 */
#define	DEMO_SET_RECORD_VOICE_ONOFF		(DEMO_SET_DASHCAM_BASE + 2)	/* 녹음 여부 */
#define	DEMO_SET_RECORD_MIC_VOLUME		(DEMO_SET_DASHCAM_BASE + 3)	/* 마이크 볼륨 */
#ifdef  DEMO_SET_RECORD_MIC_VOLUME
    #define DEMO_VAL_MIC_VOLUME_LOW		0x00
    #define DEMO_VAL_MIC_VOLUME_MID		0x01
    #define DEMO_VAL_MIC_VOLUME_HIGH		0x02
#endif
#define	DEMO_SET_RECORD_SPEAKER_VOLUME	(DEMO_SET_DASHCAM_BASE + 4)	/* 스피커 볼륨 */
#ifdef  DEMO_SET_RECORD_MIC_VOLUME
    #define DEMO_VAL_SPEAKER_VOLUME_LOW		0x00
    #define DEMO_VAL_SPEAKER_VOLUME_MID		0x01
    #define DEMO_VAL_SPEAKER_VOLUME_HIGH		0x02
#endif
#define	DEMO_SET_RECORD_MEANT_ONOFF		(DEMO_SET_DASHCAM_BASE + 5)	/* MEANT 설정 ? */
#define	DEMO_SET_RECORD_SD_CARD_FORMAT	(DEMO_SET_DASHCAM_BASE + 6)	/* SD 카드 포맷 ? */
#ifdef  DEMO_SET_RECORD_SD_CARD_FORMAT
    #define DEMO_VAL_SD_CARD_ACTION		0x00
    #define DEMO_VAL_SD_CARD_CANCEL		0x01
#endif
#define	DEMO_SET_RECORD_SD_CARD_CHECK		(DEMO_SET_DASHCAM_BASE + 7)	/* SD 카드 체크 ? */
#define DEMO_SET_G_SENSIBILITY            (DEMO_SET_DASHCAM_BASE + 8)	/* G-Sensor 감도 */
#ifdef  DEMO_SET_G_SENSIBILITY
    #define DEMO_VAL_SENSIBILITY_LOW      0x00
    #define DEMO_VAL_SENSIBILITY_NORMAL   0x01
    #define DEMO_VAL_SENSIBILITY_HIGH     0x02
#endif
#define DEMO_SET_RECORD_SELECT_CAMERA     (DEMO_SET_DASHCAM_BASE + 9)	/* 녹화 대상 카메라 */
#ifdef  DEMO_SET_RECORD_SELECT_CAMERA
    #define DEMO_VAL_CAMERA_HD			0x00
    #define DEMO_VAL_CAMERA_4VGA			0x01
    #define DEMO_VAL_CAMERA_AVM			0x02
#endif
#define DEMO_SET_RECORD_VIDEO_QUALITY     (DEMO_SET_DASHCAM_BASE + 10)	/* 녹화 영상 품질 */
#ifdef  DEMO_SET_RECORD_VIDEO_QUALITY
    #define DEMO_VAL_QUALITY_LOW			0x00
    #define DEMO_VAL_QUALITY_MID			0x01
    #define DEMO_VAL_QUALITY_HIGH			0x02
#endif
#define DEMO_SET_RECORD_TIMEZONE			(DEMO_SET_DASHCAM_BASE + 11)	/* 타임존 설정 */
#ifdef  DEMO_SET_RECORD_TIMEZONE
#define DEMO_VAL_UTC						0x00
#define	DEMO_VAL_TIMEZONE					0x01
#endif

/* Fleet Management Settings */

#define DEMO_SET_FLEET_MANAGEMENT_BASE    0x90
#define DEMO_SET_FLEET_SERVER_URL         (DEMO_SET_FLEET_MANAGEMENT_BASE + 0)  /* 관제 서버 연결 정보 */
#define DEMO_SET_FLEET_ID                 (DEMO_SET_FLEET_MANAGEMENT_BASE + 1)  /* 관리 차량 고유 아이디 */
#define DEMO_SET_FLEET_SIGNATURE          (DEMO_SET_FLEET_MANAGEMENT_BASE + 2)  /* 관제 서버에 연결하기위한 단말기 인증 정보 */

/* Volatile Status - 상태 */

#define DEMO_STAT_BASE                    0x00
#define DEMO_STAT_VIEW_MODE               (DEMO_STAT_BASE + 0)  /* 현재 뷰모드 설정 */
#define DEMO_STAT_VIDEO_PARAMS            (DEMO_STAT_BASE + 1)  /* 영상 변환 파라미터들 */
#define DEMO_STAT_GPS                     (DEMO_STAT_BASE + 2)  /* GPS 수신 상태 */
#define DEMO_STAT_RECORDING               (DEMO_STAT_BASE + 3)  /* 블랙박스 상시 녹화 상태 */
#define DEMO_STAT_UNCONFIRMED_EVENT       (DEMO_STAT_BASE + 4)  /* 미확인 충격 이벤트 등 알림 여부 */
#define DEMO_STAT_LDWS                    (DEMO_STAT_BASE + 5)  /* 차선 이탈 상태 */
#define DEMO_STAT_BSD                     (DEMO_STAT_BASE + 6)  /* 후측방 물체 감지 여부 */
#define DEMO_STAT_STORAGE_USAGE           (DEMO_STAT_BASE + 7)  /* 블랙박스용 스토리지 전체 사용량 */
#define DEMO_STAT_SPEED                   (DEMO_STAT_BASE + 8)  /* 현재 속도 */
#define DEMO_STAT_REVERSE_GEAR            (DEMO_STAT_BASE + 9)  /* 후진 기어 상태 */
#define DEMO_STAT_TURN_SIGNAL             (DEMO_STAT_BASE + 10) /* 방향 지시등 상태 */
#define DEMO_STAT_EMERGENCY_SIGNAL        (DEMO_STAT_BASE + 11) /* 비상등 상태 */
#define DEMO_STAT_EMERGENCY_RECORDING     (DEMO_STAT_BASE + 12) /* 블랙박스 비상 녹화 상태 */
#define DEMO_STAT_RECORDING_TIME          (DEMO_STAT_BASE + 13) /* 블랙박스 상시 녹화 경과 시간 */
#define DEMO_STAT_STORAGE_1_USAGE			(DEMO_STAT_BASE + 14) /* SD카드 1 사용량 */
#define DEMO_STAT_STORAGE_2_USAGE			(DEMO_STAT_BASE + 15) /* SD카드 2 사용량 */

/* Event Types */

#define DEMO_EVT_BASE                     0x00
#define DEMO_EVT_CONNECT                  (DEMO_EVT_BASE + 0)   /* 서버가 연결되었을 때 발생 */
#define DEMO_EVT_DISCONNECT               (DEMO_EVT_BASE + 1)   /* 서버 연결이 끊겼을 때 발생 */
#define DEMO_EVT_ERROR                    (DEMO_EVT_BASE + 2)   /* 오류 발생 이벤트 */
#define DEMO_EVT_ALARM                    (DEMO_EVT_BASE + 3)   /* 경고 발생 이벤트 */
#define DEMO_EVT_CHANGE_VIEW_MODE         (DEMO_EVT_BASE + 4)   /* 현재 뷰모드의 변화 */
#define DEMO_EVT_CHANGE_TURN_SIGNAL       (DEMO_EVT_BASE + 5)   /* 방향지시등 상태 변화 : LEFT, WRITE, NONE */
#define DEMO_EVT_CHANGE_R_GEAR            (DEMO_EVT_BASE + 6)   /* 후진 기어 상태 변화 : ON/OFF */
#define DEMO_EVT_CHANGE_EMERGENCY_SIGNAL  (DEMO_EVT_BASE + 7)   /* 비상등 상태 변화 : ON/OFF - 사용안함. (DEMO_EVT_CHANGE_TURN_SIGNAL로 커버함) */
#define DEMO_EVT_CHANGE_GPS_ONOFF         (DEMO_EVT_BASE + 8)   /* GPS 상태 변화 : ON/OFF */
#define DEMO_EVT_CHANGE_EMERGENCY_RECORD  (DEMO_EVT_BASE + 9)   /* 긴급녹화 상태 변화 : BEGIN / END */
#define DEMO_EVT_CHANGE_RECORD            (DEMO_EVT_BASE + 10)  /* 블랙박스 상시녹화 상태 변화 : BEGIN / END */
#define DEMO_EVT_CHANGE_STORAGE_USAGE     (DEMO_EVT_BASE + 11)  /* 자장장치 사용량 변화 */
#define DEMO_EVT_UPDATE_BEGIN             (DEMO_EVT_BASE + 12)  /* 서버 프로그램 업데이트 시작 */
#define DEMO_EVT_UPDATE_PROGRESS          (DEMO_EVT_BASE + 13)  /* 서버 프로그램 업데이트 진행율 변화 */
#define DEMO_EVT_UPDATE_END               (DEMO_EVT_BASE + 14)  /* 서버 프로그램 업데이트 종료 */
#define DEMO_EVT_CHANGE_RECORDING_TIME    (DEMO_EVT_BASE + 15)  /* 녹화 진행 시간 변화 */
#define DEMO_EVT_RECORD_EVENT_FINISH		  (DEMO_EVT_BASE + 16)	/* 이벤트 녹화 완료 */
#define DEMO_EVT_FORMAT_SDCARD_1_FINISH	  (DEMO_EVT_BASE + 17)  /* SD카드 1 포맷 완료 */
#define DEMO_EVT_FORMAT_SDCARD_2_FINISH	  (DEMO_EVT_BASE + 18)  /* SD카드 2 포맷 완료 */
#define DEMO_EVT_NEXT_VIEW_MODE			      (DEMO_EVT_BASE + 19)  /* 다음 뷰모드로 전환 */
#define DEMO_EVT_APP_ON_OFF				        (DEMO_EVT_BASE + 20)  /* APP시작/종료 */

/* Alarm Code */

#define DEMO_ALM_BASE                     0x00
#define DEMO_ALM_EVENT_UNCONFIRMED        (DEMO_ALM_BASE + 0)   /* 확인하지 않은 이벤트가 있습니다. */
#define DEMO_ALM_EVENT_G_SENSOR           (DEMO_ALM_BASE + 1)   /* 충격 이벤트가 발생했습니다. */
#define DEMO_ALM_EVENT_EMERGENCY_BUTTON   (DEMO_ALM_BASE + 2)   /* 비상 버튼이 실행되었습니다. */
#define DEMO_ALM_REAR_BLINDSPOT           (DEMO_ALM_BASE + 3)   /* 후방측면에 물체가 감지되었습니다. */
#define DEMO_ALM_LANE_DEPARTURE           (DEMO_ALM_BASE + 4)   /* 차선을 벗어났습니다. */
#define DEMO_ALM_FLASH_CARD_1_EMPTY       (DEMO_ALM_BASE + 5)   /* 플래쉬 카드 1번이 없습니다. */
#define DEMO_ALM_FLASH_CARD_2_EMPTY       (DEMO_ALM_BASE + 6)   /* 플래쉬 카드 2번이 없습니다. */

/* Error Code */

#define DEMO_ERR_BASE                     0x00
#define DEMO_ERR_UNKNOWN                  (DEMO_ERR_BASE + 0)   /* 비정상적인 시스템 오류 */
#define DEMO_ERR_SETTING_NOT_FOUND        (DEMO_ERR_BASE + 1)   /* 설정 파일을 찾을 수 없습니다. */
#define DEMO_ERR_FLASH_CARD_IO            (DEMO_ERR_BASE + 2)   /* 저장장치에 쓰거나 읽을 수가 없습니다. */
#define DEMO_ERR_CAMERA_IO                (DEMO_ERR_BASE + 3)   /* 카메라로부터 영상을 받을 수 없습니다. */

/* Commands */

#define DEMO_CMD_BASE                         0x00
#define DEMO_CMD_CONNECT                      (DEMO_CMD_BASE + 0)   /* 연결 시작 명령 */
#define DEMO_CMD_DISCONNECT                   (DEMO_CMD_BASE + 1)   /* 연결 종료 명령 */
#define DEMO_CMD_RECORD_EMERGENCY_VIDEO       (DEMO_CMD_BASE + 2)   /* 긴급 녹화 명령 */
#define DEMO_CMD_CAPTURE_EMERGENCY_STILLCUT   (DEMO_CMD_BASE + 3)   /* 긴급 사진캡쳐 명령 */
#define DEMO_CMD_CHANGE_VIEW_MODE             (DEMO_CMD_BASE + 4)   /* 뷰모드 변경 명령 */
#define DEMO_CMD_CAPTURE_STILLCUT             (DEMO_CMD_BASE + 5)   /* 현재 뷰모드 영상 스틸컷 캡쳐 명령 */
#define DEMO_CMD_START_UPGRADE                (DEMO_CMD_BASE + 6)   /* 소프트웨어 업그레이드 시작 명령 */
#define DEMO_CMD_START_PLAYBACK             	(DEMO_CMD_BASE + 7)   /* 프레이백 스트림 시작 명령 */
#define DEMO_CMD_STOP_PLAYBACK              	(DEMO_CMD_BASE + 8)   /* 프레이백 스트림 종료 명령 */
#define DEMO_CMD_START_STREAM             	  (DEMO_CMD_BASE + 9)   /* 영상 스트림 시작 명령 */
#define DEMO_CMD_STOP_STREAM              	  (DEMO_CMD_BASE + 10)  /* 영상 스트림 종료 명령 */
#define DEMO_CMD_START_LIVE_4CH               (DEMO_CMD_BASE + 11)
#define DEMO_CMD_START_LIVE_HD             	  (DEMO_CMD_BASE + 12)
#define DEMO_CMD_STOP_LIVE_4CH	              (DEMO_CMD_BASE + 13)
#define DEMO_CMD_STOP_LIVE_HD	            	  (DEMO_CMD_BASE + 14)
#define DEMO_CMD_FORMAT_SDCARD_1				      (DEMO_CMD_BASE + 15)  /* SD 카드 1 포맷 명령 */
#define DEMO_CMD_FORMAT_SDCARD_2				      (DEMO_CMD_BASE + 16)  /* SD 카드 2 포맷 명령 */

/* File */
#define DEMO_FILE_BASE                    0x00
#define DEMO_FILE_GET_LIST                (DEMO_FILE_BASE + 0)
#define DEMO_FILE_LIST                    (DEMO_FILE_BASE + 1)
#define DEMO_FILE_GET                     (DEMO_FILE_BASE + 2)
#define DEMO_FILE                         (DEMO_FILE_BASE + 3)
#define DEMO_FILE_DELETE                  (DEMO_FILE_BASE + 4)
#define DEMO_FILE_GET_CALIBRATION_INFO	  (DEMO_FILE_BASE + 10)		/* Calibration 정보 파일 요청 */
#define DEMO_FILE_SET_CALIBRATION_INFO	  (DEMO_FILE_BASE + 11)		/* Calibration 정보 파일 업로드/다운로드 */

/* Stream */
#define DEMO_STREAM_BASE					  0x00
#define DEMO_STREAM						      (DEMO_STREAM_BASE + 0)
#define DEMO_STREAM_PLAYBACK				(DEMO_STREAM_BASE + 1)
#define DEMO_STREAM_LIVE_4CH				(DEMO_STREAM_BASE + 2)
#define DEMO_STREAM_LIVE_HD				  (DEMO_STREAM_BASE + 3)

/* Movie Playback */
#define DEMO_MOVIE_BASE					    0x00
#define DEMO_MOVIE_GET_INFO				  (DEMO_MOVIE_BASE + 0)
#define DEMO_MOVIE_INFO					    (DEMO_MOVIE_BASE + 1)
#define DEMO_MOVIE_COMMAND_START		(DEMO_MOVIE_BASE + 2)
#define DEMO_MOVIE_COMMAND_STOP			(DEMO_MOVIE_BASE + 3)
#define DEMO_MOVIE_COMMAND_RESUME		(DEMO_MOVIE_BASE + 4)
#define DEMO_MOVIE_COMMAND_PAUSE		(DEMO_MOVIE_BASE + 5)
#define DEMO_MOVIE_FRAME					  (DEMO_MOVIE_BASE + 6)

#endif /* __DEMO_CONST_H */
