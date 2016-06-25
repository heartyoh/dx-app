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

int server_handler_hb(int fd, dx_packet_t* packet) {
	printf("(Server Event Handling) HeartBeat\n");

	dx_packet_send_heartbeat(fd, 0);

	printf("(Server Event Handling) HeartBeat.. Sent back.\n");

	return 0;
}
