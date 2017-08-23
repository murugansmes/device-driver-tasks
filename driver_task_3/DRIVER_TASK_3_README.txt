parent directory:driver_task_3

a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.
 
Question:1)DRIVER TO CREATE PROCFS ENTRY.

a)Open the folder "procfs_driver_read_write" in terminal.
b)type :sudo insmod procfs_driver_read_write.ko
c)"dmesg" command will show the dynamically allocated major number of the driver.
d)Once the driver is loaded,it will create an entry in /proc folder.In this program the entry name is "hello1".
e)To test the entry.

	i)sudo su
	ii)echo 17 > /proc/hello1
 	iii)cat /proc/hello1 will show the value echoed to the node (i.e 17 in this case).
 	
 		This means that the user can pass and read values to communicate with kernel through this entry.The intention of /proc file system is to share kernel process informations with the user.Writing random values in proc file system is not recommended.

f)rmmod procfs_driver_read_write


Question:2)DRIVER TO CREATE SYSFS ENTRY.

a)Open the folder "sysfs_driver" in terminal.
b)type :sudo insmod sysfs_driver.ko
c)"dmesg" command will show the dynamically allocated major number of the driver.
d)Once the driver is loaded,it will create an entry in /sys/kernel/kobject_example folder.In this program the entry name is "f".
e)To test the entry.

	i)sudo su
	ii)echo 17 > /sys/kernel/kobject_example/f
 	iii)cat /sys/kernel/kobject_example/f will show the value echoed to the node (i.e 17 in this case).
 	iv)"dmesg" command will show that the same value is printed by the kernel using printk.
 	
 		This means that the user can pass and read values to communicate with kernel through this entry.The intention of /sys file system is to share any kernel structure or attribute information with the user.sysfs strictly enforces one item per file rule.

f)rmmod sysfs_driver

Question:3)DRIVER TO CREATE DEBUGFS ENTRY.

a)Open the folder "debugfs_driver" in terminal.
b)type :sudo insmod debugfs_drive.ko
c)"dmesg" command will show the dynamically allocated major number of the driver.
d)Once the driver is loaded,it will create an entry in /sys/kernel/debug folder.In this program the entry name is "hello".
e)To test the entry:
This debug file store the number of times the driver files has been opened.(default value is 0.)
	i)sudo su
	ii)mknod /dev/debug_driver c major_number minor_number.
	iii)cat /dev/debug_driver will print "hello world from kernel.." in terminal.
 	iii)cat /sys/debug/hello will show the number of time the device file "debug_driver" has been accessed(i.e 1 in this case).
 	
 		This means that the user can store debug data from kernel space to user space using debugfs.The intention of debug file system is to store large amount of debug data so user can easily debug the kernel code.debugfs doesn't enforce any strict rules.
f)rmmod debugfs_driver 
