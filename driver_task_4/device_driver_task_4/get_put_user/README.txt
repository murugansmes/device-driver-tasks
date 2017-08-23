PARENT DIRECTORY:get_put_user

	
a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question:4)A character driver to use get_user() and put_user().

a)Open the folder "get_put_user" in terminal.
b)sudo insmod get_put_user.ko .Default major number is 100.
c)sudo mknod /dev/get_put_user c 100 0.
d)sudo chmod 666 /dev/get_put_user.
e)echo "some text" > /dev/get_put_user.
f)cat /dev/get_put_user.
f)sudo rmmod get_put_user.
e)make clean.



