PARENT DIRECTORY:file_reader.
a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question 3: Simple module that loads file from the filesystem and prints it.

a)Open the folder "file_reader" in terminal.
b)type :sudo insmod kernel_file_reader.ko .
c)The file we are reading in the program is "/proc/devices" .dmesg will show the contents of that file.
d)sudo rmmod kernel_file_reader.
e)make clean.



