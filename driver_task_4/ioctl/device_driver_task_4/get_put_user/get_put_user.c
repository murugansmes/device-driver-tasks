/***********************************************************************

*   Project Name : get_put_user.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 26/6/2017
*
*   Description  : Module that demonstrate the use of get_user and put_user functions.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/
#define MAJOR_NUM 100
#define SUCCESS 0
#define DEVICE_NAME "ioctl_buffer"
#define BUF_LEN 80
/**********************************************************************
*   Global variable declerations 
***********************************************************************/
static int Device_Open=0;
static char Message[BUF_LEN];
static char *Message_Ptr;

/***********************************************************************
*   Function Prototypes 
************************************************************************/
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

*   Function    : init_module().
*
*   Description : initialiaiton function of this module.
*
*   Parameters  : void.
*
*   Return value: 0.

***********************************************************************/
int init_module(void)
{
 	 int ret_val;
	 ret_val=register_chrdev(MAJOR_NUM,DEVICE_NAME,&Fops);
 	 if(ret_val<0)
 	 {
 	 	printk("%s failed with %d\n","Sorry,registering the character device",ret_val);
 	 	return ret_val;
       	 }
       	printk("%s The major device number is %d.\n","Registration is success",MAJOR_NUM);
	return 0;
}
/**********************************************************************

*   Function    : cleanup_module().
*
*   Description : cleanup function of this module.
*
*   Parameters  : void.
*
*   Return value: none.

***********************************************************************/
void cleanup_module(void)
{
	unregister_chrdev(MAJOR_NUM,DEVICE_NAME);
	printk("Successfully unregistered the driver.\n");
}

MODULE_LICENSE("GPL");

