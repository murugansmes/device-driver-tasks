PARENT DIRECTORY:send_signal.
This folder contains 2 files:
	1)a kernel module file.
	2)a user space application.
	
a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question:3)A simple module that send signals to user space.

a)Open the folder "send_signal" in terminal.
b)type :sudo insmod send_signal.ko .
c)A debug file called "signalconfpid" will be created in /sys/kernel/debug folder to which the user application writes its PID. 
d)gcc -o output recieve_signal.c
e)sudo chmod 666 /sys/kernel/debug/signalconfpid .
f)sudo su .
g)./output .
h)sudo rmmod send_signal .
e)make clean.



