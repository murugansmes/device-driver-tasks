parent directory:driver_task_1

a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question 1:SIMPLE MODULE TO PERFORM module_param, MODULE_AUTHOR,MODULE-DESCRIPTION also accessing global values inside the module.

a)Open the folder "simple_module" in terminal.
b)type :sudo insmod module_1.ko
c)"dmesg" command will show the values of the module parameters.
d)modinfo module_1.ko will show the details of the module.
e)To change the default values of a module_parameter while loading the module.
		i)sudo insmod age=50 (this will change the value of the module parameter 'age'to 50).
f)sudo rmmod driver_task_1.
g)Type sudo rmmod driver_1 to remove the driver.

Question 2:Simple character driver (Register as the character driver),with init, exit, open file operations.

a)Open the folder "simple_driver" in terminal.
b)type :sudo insmod driver_2.ko
c)"dmesg" command will show the dynamically allocated value of the major number.
d)To create  a node type sudo mknod /dev/driver_2 c major_number minor_number. 
e)To open the device node type cat /dev/driver_2.
f)dmesg will show the number of time the device node has been accessed by the user.
g)Type sudo rmmod driver_2 to remove the driver.
		
Question 3:Inserting character driver, creating device node for the module and User space application to open the driver (using node).

Driver side:
a)Open the folder "driver_to_user" in terminal.
b)type :sudo insmod driver_3.ko
c)"dmesg" command will show the dynamically allocated value of the major number.
d)To create  a node type sudo mknod /dev/simple_driver c major_number minor_number. 

User application:
a)Compile the driver_user.c in the parent folder.(gcc -o output driver_user.c)
b)execute the object file.(./output)
c)A message will be printed in the terminal.This message was read from the kernel space using copy_to_user() function.
d)To remove the driver type sudo rmmod driver_3.
