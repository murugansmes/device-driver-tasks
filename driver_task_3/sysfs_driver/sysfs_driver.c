/***********************************************************************

*   Project Name : sysfs_driver.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 21/6/2017
*
*   Description  : Driver that creates entries in sysfs.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include <linux/module.h> 
#include <linux/printk.h> 
#include <linux/kobject.h>
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h>
#include<linux/kernel.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/

/**********************************************************************
*   Global variable declerations 
***********************************************************************/
static struct kobject *my_kobject;
static int f;
static int major;
struct file_operations fops=
{
	.owner=THIS_MODULE
};
/***********************************************************************
*   Function Prototypes 
************************************************************************/
static ssize_t my_show(struct kobject *kobj, struct kobj_attribute *attr,char *buf);
static ssize_t my_store(struct kobject *kobj, struct kobj_attribute *attr,char *buf, size_t count);
static int __init mymodule_init (void);
static void __exit mymodule_exit (void);
/**********************************************************************

*   Function    : my_show()
*
*   Description : Function to show the attribute stored in the kobject file in userspace.
*
*   Parameters  : kobject pointer,pointer to attribute structure,buffer pointer.
*
*   Return value: Total number of characters.

***********************************************************************/
static ssize_t my_show(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
        return sprintf(buf,"%d\n",f);
}
/**********************************************************************

*   Function    : my_store()
*
*   Description : Function to store the attribute to kobject file.
*
*   Parameters  : kobject pointer,pointer to attribute structure,buffer pointer,size of the attribute.
*
*   Return value: Total number of characters.

***********************************************************************/
static ssize_t my_store(struct kobject *kobj, struct kobj_attribute *attr,char *buf, size_t count)
{
        sscanf(buf, "%du", &f);
        printk("\nThe value of the attribute changed to %d.",f);
        return count;
}

static struct kobj_attribute my_attribute =__ATTR(f,0660,my_show,my_store);

/**********************************************************************

*   Function    : mymodule_init()
*
*   Description : Module to initalize the device.
*
*   Parameters  : void.
*
*   Return value: error.(0 is return on successful initialization)

***********************************************************************/
static int __init mymodule_init (void)
{
        int error = 0;
	major=register_chrdev(0,"mySysfs",&fops);
	if(major<0)
	{
		printk("Registration failed at %d\n",major);
	}
	else 
	{	
		printk("Registration success at %d\n",major);
	}
        my_kobject = kobject_create_and_add("kobject_example",kernel_kobj);
        if(!my_kobject)
                return -ENOMEM;
        error = sysfs_create_file(my_kobject,&my_attribute.attr);
        if (error) {
                pr_info("failed to create the f file in /sys/kernel/kobject_example \n");
        }
        return error;
}
/**********************************************************************

*   Function    : mymodule_exit()
*
*   Description : Module to uninitialize the device.
*
*   Parameters  : void.
*
*   Return value: void.

***********************************************************************/
static void __exit mymodule_exit (void)
{
	unregister_chrdev(major,"mySysfs");
        pr_info("Device removed successfully:%d \n",f);
        kobject_put(my_kobject);
}
module_init(mymodule_init);
module_exit(mymodule_exit);
MODULE_LICENSE("GPL");
