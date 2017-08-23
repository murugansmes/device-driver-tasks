/***********************************************************************

*   Project Name : tasklet.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 29/6/2017
*
*   Description  : Driver that uses tasklet concept.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/module.h>
#include<linux/interrupt.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/
#define MAJOR_NUM 100
#define SUCCESS 0
#define BUF_LEN 80
#define DEVICE_NAME "mytasklet"
/**********************************************************************
*   Global variable declerations 
***********************************************************************/
static unsigned long volatile onesec;
static int Device_Open=0;
static char Message[BUF_LEN];
static char *Message_Ptr;

/***********************************************************************
*   Function Prototypes 
************************************************************************/
void tasklet_action(unsigned long t);
void normal_action(unsigned long t);
void my_actions(void);
int __init tasklet_module_init(void);
void __exit tasklet_module_exit(void);
static int device_open(struct inode *inode,struct file *file);
static int device_release(struct inode *inode,struct file *file);
static ssize_t device_read(struct file *file,char *buffer,size_t length,loff_t *offset);
static ssize_t device_write(struct file *file,const char *buffer,size_t length,loff_t *offset);
struct file_operations Fops={
	.read			= device_read,
	.write			= device_write,
	.open			= device_open,
	.release		= device_release,
	};
struct tasklet_struct my_tasklet={
	.next=NULL,
	.state=0,
	.count=ATOMIC_INIT(0),
	.func=tasklet_action,
	.data=0
};
/**********************************************************************

*   Function    : device_open()
*
*   Description : This function is called whenever the device file is opened.
*
*   Parameters  : inode structure,file pointer.
*
*   Return value: SUCCESS.(a macro whose default value is 0.)

***********************************************************************/
static int device_open(struct inode *inode,struct file *file)
{
	if(Device_Open)
		{
			return -EBUSY;
		}
	Device_Open++;
	Message_Ptr=Message;
	return SUCCESS;
}
/**********************************************************************

*   Function    : device_release().
*
*   Description : This funtion is called whenever the device file is closed.
*
*   Parameters  : inode pointer,file pointer.
*
*   Return value: 0.

***********************************************************************/
static int device_release(struct inode *inode,struct file *file)
{
	printk("device_release(%p,%p)\n",inode,file);
	Device_Open--;
	return 0;
}
/**********************************************************************

*   Function    : device_read()
*
*   Description : This function is called whenever the device file is read. 
*
*   Parameters  : file pointer,buffer pointer,count of data to be read,seek position.
*
*   Return value: number of bytes read. 

***********************************************************************/
static ssize_t device_read(struct file *file,char *buffer,size_t length,loff_t *offset)
{
	int bytes_read=0;
	printk("device_read(%p,%p,%zu)\n",file,buffer,length);
	if(*Message_Ptr==0)
	{
	return 0;
	}
	else
	{
	while(length && *Message_Ptr)
	{
		put_user(*(Message_Ptr++),buffer++);
		length--;
		bytes_read++;
	}
	printk("Read %d bytes,%zu left\n",bytes_read,length);
	return bytes_read;	
	}
}
/**********************************************************************

*   Function    : device_write()
*
*   Description : This function is called whenever data is written on the device file.
*
*   Parameters  : file pointer,buffer pointer,count of data to be read,seek position.
*
*   Return value: number of bytes written.

***********************************************************************/
static ssize_t device_write(struct file *file,const char *buffer,size_t length,loff_t *offset)
{
	int i;
	printk("device_write(%p,%s,%zu)\n",file,buffer,length);
	
	for(i=0;i<length && i<BUF_LEN;i++)
	{
		get_user(Message[i],buffer+i);
	}
	Message_Ptr=Message;
	printk("Kernel recieved the message:%s\n",Message_Ptr);
	return i;
}
/**********************************************************************

*   Function    : tasklet_action().
*
*   Description : A tasklet action that is excuted on a later time when the cpu is free.
*
*   Parameters  : unsigned long integer(not necessary).
*
*   Return value: none.

***********************************************************************/
void tasklet_action(unsigned long t)
{
	printk("tasklet action is being executed..\n");
}
/**********************************************************************

*   Function    : normal_action().
*
*   Description : A normal function is executed without any delays.
*
*   Parameters  : unsigned long integer(not necessary).
*
*   Return value:  none.

***********************************************************************/
void normal_action(unsigned long t)
{
	onesec = jiffies;
	printk("normal action is being executed..\n");
}

/**********************************************************************

*   Function    : my_actions().
*
*   Description : A function that calls tasklet_action and normal_action respectively.
*
*   Parameters  : unsigned long integer(not necessary).
*
*   Return value:  none.

***********************************************************************/
void my_actions(void)
{
	printk("tasklet:do_work()\n");
	tasklet_schedule(&my_tasklet);
	normal_action(1);
}
/**********************************************************************

*   Function    : tasklet_module_init().
*
*   Description : initialiaiton function of this module.
*
*   Parameters  : void.
*
*   Return value: 0.

***********************************************************************/

int __init tasklet_module_init(void)
{
	 int ret_val;
	 ret_val=register_chrdev(MAJOR_NUM,DEVICE_NAME,&Fops);
 	 if(ret_val<0)
 	 {
 	 	printk("%s failed with %d\n","Sorry,registering the character device",ret_val);
 	 	return ret_val;
       	 }
	onesec = jiffies;
	printk("tasklet:tasklet_module_init()\n");
	printk("module loaded %lu jiffies\n",jiffies);
	my_actions();
	return 0;
}
/**********************************************************************

*   Function    : tasklet_module_exit().
*
*   Description : cleanup function of this module.
*
*   Parameters  : void.
*
*   Return value: none.

***********************************************************************/
void __exit tasklet_module_exit(void)
{
	unregister_chrdev(MAJOR_NUM,DEVICE_NAME);
	printk("tasklet:tasklet_module_exit");
	
}
module_init(tasklet_module_init);
module_exit(tasklet_module_exit);
