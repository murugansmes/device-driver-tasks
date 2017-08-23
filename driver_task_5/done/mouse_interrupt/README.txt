PARENT DIRECTORY:mouse_interrupt.

a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question:2)Write a character device driver to share the irq , register and execute your interupt handler  with mouse/Network card.

a)Open the folder "mouse_interrupt" in terminal.
b)type :sudo insmod mouse_interrupt.ko.
c)dmesg will show the number of interrupts raised by the mouse.
d)sudo rmmod mouse_interrupt.
e)make clean.



