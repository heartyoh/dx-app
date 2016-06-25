#include "demo.h"

int demo_client_event_handler(dx_event_context_t* context, dx_packet_t* packet) {
	switch(packet->header.type) {
	case DX_PACKET_TYPE_HB : /* Heart Beat */
		client_handler_hb(context->fd, packet);
		break;
	case DX_PACKET_TYPE_GET_SETTING	: /* Get Setting */
		client_handler_get_setting(context->fd, packet);
		break;
	case DX_PACKET_TYPE_SET_SETTING : /* Set Setting */
		client_handler_set_setting(context->fd, packet);
		break;
	case DX_PACKET_TYPE_GET_STATE : /* Get State */
		client_handler_get_state(context->fd, packet);
		break;
	case DX_PACKET_TYPE_SET_STATE : /* Set State */
		client_handler_set_state(context->fd, packet);
		break;
	case DX_PACKET_TYPE_EVENT : /* Event */
		client_handler_event(context->fd, packet);
		break;
	case DX_PACKET_TYPE_COMMAND : /* Command */
		client_handler_command(context->fd, packet);
		break;
	case DX_PACKET_TYPE_FILE : /* File */
		client_handler_file(context->fd, packet);
		break;
	case DX_PACKET_TYPE_STREAM : /* Stream */
		client_handler_stream(context->fd, packet);
		break;
	case DX_PACKET_TYPE_MOVIE : /* Movie Playback */
		client_handler_movie(context->fd, packet);
		break;
	default:	/* Should not reach to here */
		ASSERT("Client Event Handling.. should not reach to here.", !!0);
		break;
	}

	return 0;
}

