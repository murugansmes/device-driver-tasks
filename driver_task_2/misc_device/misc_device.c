/***********************************************************************

*   Project Name : misc_device.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 14/6/2017
*
*   Description  : Program to rotate the given byte to left or right. The input byte should be taken as command line.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/miscdevice.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/module.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/

/**********************************************************************
*   Global variable declerations 
***********************************************************************/

/***********************************************************************
*   Function Prototypes 
************************************************************************/
int misc_init(void);
void misc_exit(void);
/**********************************************************************/

MODULE_DESCRIPTION("Simple Misc Driver");
MODULE_AUTHOR("MURUGAN S <murugan.s@fossilshale.com>");
MODULE_LICENSE("GPL");

static struct miscdevice my_dev;
static int open(struct inode *inode,struct file *file );
static int close(struct inode *inode,struct file *file);
static ssize_t write(struct file *file,const char __user *buffer,size_t len,loff_t *pos);

static const struct file_operations fops={
	.owner   =THIS_MODULE,
	.write   =write,
	.open    =open,
	.release =close,
};


static int open(struct inode *inode,struct file *file )
{
	pr_info("my_dev has been opened.");
	return 0;
}


static int close(struct inode *inode,struct file *file)
{
	pr_info("my_dev has been closed.");
	return 0;
}


static ssize_t write(struct file *file,const char __user *buffer,size_t len,loff_t *pos)
{
	pr_info("my_dev read %d bytes.",len);
	return len;
}


static struct miscdevice my_dev={
	.minor=MISC_DYNAMIC_MINOR,
	.name="my_dev",
	.fops=&fops,
};

/**********************************************************************

*   Function    : misc_init()
*
*   Description : init function of this module.
*
*   Parameters  : none.
*
*   Return value: 0.

***********************************************************************/
int misc_init(void)
{
	int retval;
	retval = misc_register(&my_dev);
	if(retval) return retval;
	printk("my_dev got minor %i\n",my_dev.minor);
	return 0;
}

/**********************************************************************

*   Function    : misc_exit()
*
*   Description : exit function of this module.
*
*   Parameters  : none.
*
*   Return value: none.

***********************************************************************/
void misc_exit(void)
{
       misc_deregister(&my_dev);
       printk("my_dev successfully unregistered.");
}


module_init(misc_init)
module_exit(misc_exit)
