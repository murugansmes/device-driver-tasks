PARENT DIRECTORY:llseek.
a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question:3)Write a simple character driver to implement "llseek".

a)Open the folder "llseek" in terminal.
b)type :sudo insmod llseek_driver.ko .Default major number is 100.
c)sudo mknod /dev/my_llseek c 100 0.
d)sudo chmod 666 /dev/my_llseek.
e)gcc -o output llseek_user.c
g)./output
f)sudo rmmod llseek_driver.
g)make clean.



