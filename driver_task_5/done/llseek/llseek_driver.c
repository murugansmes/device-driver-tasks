/***********************************************************************

*   Project Name : llseek_driver.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 5/7/2017
*
*   Description  : Simple character driver to implement "llseek" using ramdisk.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/uaccess.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/
#define BUFFER_SIZE 1024
#define MAJOR_NUM 100
#define DEVICE_NAME "llseek_driver"
/**********************************************************************
*   Global variable declerations 
***********************************************************************/
int chardev_init(void);
void chardev_exit(void);
static int device_open(struct inode *, struct file *);
static int device_close(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static loff_t device_lseek(struct file *file, loff_t offset, int orig);
static char device_buffer[BUFFER_SIZE];
static int Device_Open=0;
int major_number;
int ret;
struct file_operations fops = {
    .owner	 = THIS_MODULE, 
    .open	 = device_open, 
    .write	 = device_write,
    .read 	 = device_read,
    .release     = device_close,
    .llseek	 = device_lseek
};
/***********************************************************************
*   Function Prototypes 
************************************************************************/
static int device_open(struct inode *inode, struct file *filp);
static ssize_t device_read(struct file *fp, char *buff, size_t length, loff_t *ppos);
static ssize_t device_write(struct file *fp, const char *buff, size_t length, loff_t *ppos);
static loff_t device_lseek(struct file *file, loff_t offset, int orig);
static int device_close(struct inode *inode, struct file *filp);
/**********************************************************************

*   Function    : device_open()
*
*   Description : This function is called whenever the device file is opened.
*
*   Parameters  : inode structure,file pointer.
*
*   Return value: 0.

***********************************************************************/
static int device_open(struct inode *inode, struct file *filp) {
    		if(Device_Open)
		{
			return -EBUSY;
		}
		Device_Open++;
    		printk(KERN_INFO "Device opened succesfully\n");
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
static ssize_t device_read(struct file *fp, char *buff, size_t length, loff_t *ppos)
 {
    int maxbytes; 
    int bytes_to_read; 
    int bytes_read;
    maxbytes = BUFFER_SIZE - *ppos;
    if(maxbytes > length) 
    {
        bytes_to_read = length;
    }
    else
    {
        bytes_to_read = maxbytes;
    }
    if(bytes_to_read == 0)
    {
        printk(KERN_INFO "Reached the end of the device\n");
    }
    bytes_read = bytes_to_read - copy_to_user(buff, device_buffer + *ppos, bytes_to_read);
    printk(KERN_INFO "device has been read %d\n",bytes_read);
    *ppos += bytes_read;
    printk(KERN_INFO "device has been read\n");
    return bytes_read;
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
static ssize_t device_write(struct file *fp, const char *buff, size_t length, loff_t *ppos)
 {
    int maxbytes; 
    int bytes_to_write;
    int bytes_writen;
    maxbytes = BUFFER_SIZE - *ppos;
    if(maxbytes > length) 
    {
        bytes_to_write = length;
    }
    else
    {
        bytes_to_write = maxbytes;
    }
    bytes_writen = bytes_to_write - copy_from_user(device_buffer + *ppos, buff, bytes_to_write);
    printk(KERN_INFO "device has been written %d\n",bytes_writen);
    *ppos += bytes_writen;
    printk(KERN_INFO "device has been written\n");
    return bytes_writen;
}
/**********************************************************************

*   Function    : device_llseek()
*
*   Description : This function is called when lseek system call is made from user application.
*
*   Parameters  : file pointer,offset,choice of seek opertaion to be performed.
*
*   Return value:  

***********************************************************************/
static loff_t device_lseek(struct file *file, loff_t offset, int choice) {
    loff_t new_pos = 0;
    printk(KERN_INFO "lseek function in work\n");
    switch(choice) {
        case 0 : /*seek set*/
            new_pos = offset;
            break;
        case 1 : /*seek cur*/
            new_pos = file->f_pos + offset;
            break;
        case 2 : /*seek end*/
            new_pos = BUFFER_SIZE - offset;
            break;
    }
    if(new_pos > BUFFER_SIZE)
        new_pos = BUFFER_SIZE;
    if(new_pos < 0)
        new_pos = 0;
    file->f_pos = new_pos;
    return new_pos;
}
/**********************************************************************

*   Function    : device_close().
*
*   Description : This funtion is called whenever the device file is closed.
*
*   Parameters  : inode pointer,file pointer.
*
*   Return value: 0.

***********************************************************************/
static int device_close(struct inode *inode, struct file *filp) 
{
    Device_Open--;
    printk(KERN_INFO "device has been closed\n");
    return ret;
}


int my_init(void) 
{
     int ret_val;
	 ret_val=register_chrdev(MAJOR_NUM,DEVICE_NAME,&fops);
 	 if(ret_val<0)
 	 {
 	 	printk("%s failed with %d\n","Sorry,registering the character device",ret_val);
 	 	return ret_val;
       	 }
       	printk("%s The major device number is %d.\n","Registration is success",MAJOR_NUM);
	return 0;
}

void my_exit(void)
{
  	 unregister_chrdev(MAJOR_NUM,DEVICE_NAME);
	 printk("Successfully unregistered the driver.\n");
}

MODULE_AUTHOR("MURUGAN S");
MODULE_DESCRIPTION("LLSEEK DRIVER");
MODULE_LICENSE("GPL");    
module_init(my_init);
module_exit(my_exit);
