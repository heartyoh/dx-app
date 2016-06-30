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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

#include "dx-core.h"
#include "dx-camera-query.h"

int dx_camera_enum_fmt(int dev) {
	struct v4l2_fmtdesc fmtdesc = {0};

	fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	char fourcc[5] = {0};
	char c, e;

	CONSOLE("  FMT : CE Desc\n--------------------\n");
	while (0 == IOCTL(dev, VIDIOC_ENUM_FMT, &fmtdesc)) {
		strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
		c = fmtdesc.flags & 1? 'C' : ' '; // C means COMPRESSED
		e = fmtdesc.flags & 2? 'E' : ' '; // E means EMULATED
		CONSOLE("  %s: %c%c %s\n", fourcc, c, e, fmtdesc.description);
		fmtdesc.index++;
	}

	return 0;
}

int dx_camera_query_cap(int dev) {

	struct v4l2_capability caps = {};
	if (-1 == IOCTL(dev, VIDIOC_QUERYCAP, &caps)) {
		ERROR("Querying Capabilities");
		return 1;
	}

	CONSOLE("Driver Caps:\n"
			"  Driver: \"%s\"\n"
			"  Card: \"%s\"\n"
			"  Bus: \"%s\"\n"
			"  Version: %d.%d\n"
			"  Capabilities: %08x\n",
			caps.driver,
			caps.card,
			caps.bus_info,
			(caps.version>>16)&&0xff,
			(caps.version>>24)&&0xff,
			caps.capabilities);


	struct v4l2_cropcap cropcap = {0};
	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == IOCTL (dev, VIDIOC_CROPCAP, &cropcap)) {
		ERROR("Querying Cropping Capabilities");
		return 1;
	}

	CONSOLE("Camera Cropping:\n"
			"  Bounds: %dx%d+%d+%d\n"
			"  Default: %dx%d+%d+%d\n"
			"  Aspect: %d/%d\n",
			cropcap.bounds.width, cropcap.bounds.height, cropcap.bounds.left, cropcap.bounds.top,
			cropcap.defrect.width, cropcap.defrect.height, cropcap.defrect.left, cropcap.defrect.top,
			cropcap.pixelaspect.numerator, cropcap.pixelaspect.denominator);

	return 0;
}

