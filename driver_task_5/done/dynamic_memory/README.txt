PARENT DIRECTORY:dynamic_memory.	
a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question:1)Write a simple module to allocate the requested memory dynamically.

a)Open the folder "dynamic_memory" in terminal.
b)type :sudo insmod dynamic_memory.ko .
c)dmesg will show the values of some variables whose memory was allocated using kmalloc.The allocated memory is deallocated during dealloc.
d)sudo rmmod dynamic_memory.
e)make clean



