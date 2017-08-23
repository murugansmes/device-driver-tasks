/***********************************************************************

*   Project Name : procfs_driver_read_write.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 20/6/2017
*
*   Description  : Driver that create entry in procfs.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/kernel.h>
#include<linux/module.h>
#include<asm/uaccess.h>
#include<linux/proc_fs.h>
#include<linux/sched.h>
#include<linux/slab.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/

/**********************************************************************
*   Global variable declerations 
***********************************************************************/
int len,temp;
char *msg;
static int major;
struct file_operations fops=
{
	.owner=THIS_MODULE
};
/***********************************************************************
*   Function Prototypes 
************************************************************************/
ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp);
ssize_t write_proc(struct file *filp,const char __user *buf,size_t count,loff_t *offp);
int proc_init(void);
void proc_cleanup(void);
/**********************************************************************

*   Function    : read_proc()
*
*   Description : Funtion to read from proc file and pass it to userspace through buffer.
*
*   Parameters  : file_pointer,buffer_pointer,size_of_data,offset. 
*
*   Return value: count.

***********************************************************************/
ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp)
{
	printk("read start:The value of count is %zu.\n",count);
	 if(count>temp)
	 {
	 	count=temp;
	 	printk("read temp=%d",temp);
	 }
	 
	 temp=temp-count;
	 copy_to_user(buf,msg,count);
	 
	 if(count==0)
	 {
	  	temp=len;
	 }
	 printk(KERN_ALERT "read stop:the value of count is %zd.\n",count);
	 return count;
}
/**********************************************************************

*   Function    : write_proc()
*
*   Description : Funtion to write to proc file from user space.
*
*   Parameters  : file_pointer,buffer_pointer,size_of_data,offset. 
*
*   Return value: count.

***********************************************************************/
ssize_t write_proc(struct file *filp,const char __user *buf,size_t count,loff_t *offp)
{	
	if(count >10)
	{
	 printk("size exceeded the limit (10bytes).\n");
	 goto here;
	}
	printk("write start:The value of count is %zu.\n",count);
	copy_from_user(msg,buf,count);
	len=count;
	temp=len;
	here:
	printk("write stop:The value of count is %zu.\n",count);
	return count;
}

struct file_operations proc_fops={
	.read=read_proc,
	.write=write_proc,
};
/**********************************************************************

*   Function    : proc_init()
*
*   Description : Module to initalize the device.
*
*   Parameters  : void.
*
*   Return value: error.(0 is returned on successful initialization)

***********************************************************************/
int proc_init(void)
{
	major=register_chrdev(0,"myProc",&fops);
	if(major<0)
	{
		printk("Registration failed at %d\n",major);
	}
	else 
	{	
		printk("Registration success at %d\n",major);
	}
	
	proc_create("hello1",0,NULL,&proc_fops);
	msg=kmalloc(sizeof(char),GFP_KERNEL);
	return 0;
}
/**********************************************************************

*   Function    : proc_cleanup().
*
*   Description : Module to uninitialize the device.
*
*   Parameters  : void.
*
*   Return value: void.

***********************************************************************/
void proc_cleanup(void)
{	
	unregister_chrdev(major,"myProc");
	printk("Successfully unregistered %d",major);
	remove_proc_entry("hello1",NULL);
	kfree(msg);
}
MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);
