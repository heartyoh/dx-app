#include "demo.h"

int demo_server_event_handler(dx_event_context_t* context, dx_packet_t* packet) {

	switch(packet->header.type) {
	case DX_PACKET_TYPE_HB : /* Heart Beat */
		server_handler_hb(context->fd, packet);
//		dx_event_context_touch(context);
		break;
	case DX_PACKET_TYPE_GET_SETTING	: /* Get Setting */
		server_handler_get_setting(context->fd, packet);
		break;
	case DX_PACKET_TYPE_SET_SETTING : /* Set Setting */
		server_handler_set_setting(context->fd, packet);
		break;
	case DX_PACKET_TYPE_GET_STATE : /* Get State */
		server_handler_get_state(context->fd, packet);
		break;
	case DX_PACKET_TYPE_SET_STATE : /* Set State */
		server_handler_set_state(context->fd, packet);
		break;
	case DX_PACKET_TYPE_EVENT : /* Event */
		server_handler_event(context->fd, packet);
		break;
	case DX_PACKET_TYPE_COMMAND : /* Command */
		server_handler_command(context->fd, packet);
		break;
	case DX_PACKET_TYPE_FILE 	: /* File */
		server_handler_file(context->fd, packet);
		break;
	case DX_PACKET_TYPE_STREAM 	: /* Stream */
		printf("Why here.\n");
//		server_handler_stream(context->fd, packet);
		break;
	case DX_PACKET_TYPE_MOVIE 	: /* Movie Playback */
		server_handler_movie(context->fd, packet);
		break;
	default:	/* Should not reach to here */
		ASSERT("Server Event Handling.. should not reach to here.", !!0);
		break;
	}

	return 0;
}
