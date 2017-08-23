PARENT DIRECTORY:ioctl_buffer.
This folder contains 3 files:
	1)a kernel module file.
	2)a header file which defines the ioctl calls.
	3)a user space application.
	
a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question:4)simple IOCTL call and use this ioctl in the user space application Declare a global variable

a)Open the folder "set_global_ioctl" in terminal.
b)type :sudo insmod ioctl_global.ko .Default major number is 100.
c)sudo mknod /dev/ioctl_global c 100 0.
d)sudo chmod 666 /dev/ioctl_global.
e)gcc -o output ioctl_user.c
f)./output
g)sudo rmmod ioctl_global.
h)make clean.



