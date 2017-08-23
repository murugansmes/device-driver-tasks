/***********************************************************************
*   Project Name : dynamic_memory.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 5/7/2017
*
*   Description  : A module to allocate requested memory dynamically.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.
***********************************************************************/
/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<asm/uaccess.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/

/**********************************************************************
*   Global variable declerations 
**********************************************************************/
struct student{
	char name[10];
	int roll;
	int mark;
};
struct student *stud1;
/***********************************************************************

*   Function Prototypes 

************************************************************************/
int my_init(void);
void  my_exit(void);
/**********************************************************************
*   Function    : my_init()

*   Description : intialization function of this module.

*   Parameters  : void.

*   Return value: 0.
***********************************************************************/
int my_init(void)
{
	printk("\nDynamic memory allocation module inserted.\n");
	stud1=kmalloc(sizeof(*stud1),GFP_KERNEL);
	strcpy(stud1->name,"murugan");
	stud1->roll=1;
	stud1->mark=50;
	printk(KERN_ALERT "\nNAME:%s.\n",stud1->name);
	printk(KERN_ALERT "\nroll:%d.\n",stud1->roll);
	printk(KERN_ALERT "\nmarks:%d.\n",stud1->mark);
	return 0;
}
/**********************************************************************
*   Function    : my_exit()

*   Description : deintialization function of this module.

*   Parameters  : void.

*   Return value: none.
***********************************************************************/
void  my_exit(void)
{
	kfree(stud1);	
	printk("\nDynamic memory allocation module removed.\n");
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MURUGAN S");
MODULE_DESCRIPTION("DYNAMIC MEMORY MODULE");
