
#ifndef IOCTL_HEADER_H
#define IOCTL_HEADER_H

#include<linux/ioctl.h>

#define MAJOR_NUM 100
#define TEST_IOCTL_SET_VARIABLE _IOR(MAJOR_NUM,0,char*)
#define TEST_IOCTL_GET_VARIABLE _IOW(MAJOR_NUM,1,char*)
#define DEVICE_FILE_NAME "/dev/ioctl_global"


#endif
