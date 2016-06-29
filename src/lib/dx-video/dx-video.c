#include "dx-core.h"
#include "dx-video.h"

#include <errno.h>
#include <sys/ioctl.h>

int dx_ioctl(int fd, int request, void *arg) {
	int r;

    do {
		r = ioctl(fd, request, arg);
	} while (-1 == r && EINTR == errno);

    return r;
}
