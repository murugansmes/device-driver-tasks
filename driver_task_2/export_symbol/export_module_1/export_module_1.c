/***********************************************************************

*   Project Name : export_module_1.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 14/6/17
*
*   Description  : 
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/module.h>
#include<linux/kernel.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/

/**********************************************************************
*   Global variable declerations 
***********************************************************************/

/***********************************************************************
*   Function Prototypes 
************************************************************************/
static int mod1_func(int i);
static int mod1_init(void);
static void mod1_exit(void);
/**********************************************************************

*   Function    : mod1_func()
*
*   Description : Prints the integer value sent by the module who called this function.
*
*   Parameters  : integer value that was passed.
*
*   Return value: 0.

***********************************************************************/

static int mod1_func(int i)
{
	 printk(KERN_ALERT "\n\nThe other module sent %d to module 1.",i);
	 return 0;
}

EXPORT_SYMBOL(mod1_func);
/**********************************************************************

*   Function    : int mod1_init(void)
*
*   Description : init function of this module.
*
*   Parameters  : none.
*
*   Return value: 0.

***********************************************************************/

static int mod1_init(void)
{
	 pr_info("MODULE 1 HAS BEEN INSERTED.\n");
	 return 0;
}
/**********************************************************************

*   Function    : mod1_exit()
*
*   Description : exit function of this module.
*
*   Parameters  : none.
*
*   Return value: none.

***********************************************************************/

static void mod1_exit(void)
{
 	pr_info("MODULE 1 HAS BEEN REMOVED");
}

module_init(mod1_init);
module_exit(mod1_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MURUGAN S");
MODULE_DESCRIPTION("MODULE 1");

