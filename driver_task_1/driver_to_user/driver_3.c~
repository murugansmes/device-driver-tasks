/*this driver sends a string to buffer from which the user reads it*/
#include<linux/kernel.h>
#include<linux/module.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MURUGAN S");

static const char string[]="HELLO WORLD FROM KERNEL..\n\0";
static const ssize_t size=sizeof(string);
static ssize_t read(struct file *file,char __user *buffer,size_t count,loff_t *pos);
static int major;
struct file_operations fops=
{
	.owner=THIS_MODULE,
	.read=read
};
int init_module(void)
{
	major=register_chrdev(0,"myDev",&fops);
		if(major<0) 
		 printk("Registration failed at %d",major);
	        else 
		 printk("Successfully registered the device with major number %d.\n",major);
return 0;
}
void cleanup_module(void)
{
	unregister_chrdev(0,"myDev");
	printk("Device %d has been successfully unregistered",major);
}
static ssize_t read(struct file *file,char __user *buffer,size_t count,loff_t *pos)
{
	printk(KERN_NOTICE "\n\rDevice file ready to read at offset =%i,read bytes count=%u.",(int)*pos,(unsigned int)count);
		if(*pos>=size)
		 return 0;

		if((*pos+count)>size)
		 count=size-(*pos);

		if(copy_to_user(buffer,string+*pos,count)!=0)
		 return -EFAULT;

		*pos+=count;
		return count;

}
