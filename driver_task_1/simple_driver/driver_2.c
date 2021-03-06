#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>
#include<linux/fs.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DEVICE DRIVER TEST");
MODULE_AUTHOR("MURUGAN S");


#define BUF_LEN 80

static int open(struct inode *,struct file *);
static int close(struct inode *,struct file *);
static int major;
static int Device_Open=0;
static char *msg_ptr;
static char msg[BUF_LEN];
struct file_operations fops=
{
	.open=open,
	.release=close
};

int init_module(void) 
{
	major=register_chrdev(0,"myDev",&fops);
	if(major<0) printk("Registration failed.\n");
	else printk("Successfully registered with major number:%d\n",major);
	return 0;
		
}

void cleanup_module(void)
{
	unregister_chrdev(major,"myDev");
	printk("Successfully unregistered device with major number:%d\n",major);
}

static int open(struct inode *inode,struct file *file)
{
static int counter=0;
if(Device_Open) return -EBUSY;
Device_Open++;
sprintf(msg,"This driver file has been opened %d times.",counter++);
msg_ptr=msg;
printk(KERN_ALERT "This driver file has been opened %d times.",counter);
return 0;
}

static int close(struct inode *inode,struct file *file)
{
Device_Open--;
return 0;
}

