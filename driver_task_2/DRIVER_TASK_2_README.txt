parent directory:driver_task_3

a)A Makefile is included in the parent directory.
b)Open the parent directory in terminal.
c)Type "make" command in terminal.It will create the required object files in all the subdirectories.Same is true for "make clean" command.

Question:1)Write a driver to register as Misc device.

a)Open the folder "misc_device" in terminal.
b)type :sudo insmod misc_device.ko
c)The major number of all misc driver will be 10.To verify type cat /proc/devices and check major number of our device. 

Question:2)Write a driver with Export Symbols with multiple modules (pair of modules where the second one calls a function in the first one).

a)Open the folder "export_symbol" 
b)compile export_module_1 and export_module_ respectively.
c)copy the content of "Module.symvers" of export_module_1 to that of export_module_2.
d)insmod export_module_1 and export_module_ respectively.
e)dmesg will show you that the second module was able to call the EXPORTED SYMBOL of the first module.(viz mod1_func in our program).
f)rmmod both modules.

QUESTION 3). Write a driver to explain the use of jprobes and kprobes.

1)HERE WE ARE GOING TO PROBE THE FUNCTION mod1_func() which is the EXPORT_SYMBOL function in the previous question.There for load that module first.
2)Find the kernel address of the function mod1_func() using the command :# cat /proc/kallsyms | grep mod1_func  .
3)copy the address to the following field in the program :kp.addr=(kprobe_opcode_t *)copied_address;
4)Make and insmod simple_kprobe.c
5)Repeat the steps in previous question (question number 2)so that our function is called.
6)dmesg will show that the prehandler and post handler functions are invoked when the probed function is hit.

Jprobe has the same procedure.The difference is that dmesg of jprobe will also show the arguments passed to the probed function.
