/***********************************************************************

*   Project Name : export_module_2.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 15/6/17
*
*   Description  : Program to rotate the given byte to left or right. The input byte should be taken as command line.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
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
static int mod2_init(void);
static void mod2_exit(void);
/**********************************************************************

*   Function    : mod2_init()
*
*   Description : init function of this module.
*
*   Parameters  : none.
*
*   Return value: 0.  

***********************************************************************/


extern int mod1_func(int);

static int mod2_init(void)
{
	pr_info("MODULE 2 HAS BEEN LOADED.."); 
 	pr_info("MODULE 2 IS CALLING MODULE 1");
 	mod1_func(7);
 	return 0;
}
/**********************************************************************

*   Function    : mod2_exit()
*
*   Description : exit function of this module.
*
*   Parameters  : none.
*
*   Return value: none.  

***********************************************************************/
static void mod2_exit(void)
{
	pr_info("MODULE 2 HAS BEEN REMOVED.");
}
module_init(mod2_init);
module_exit(mod2_exit);
MODULE_LICENSE("GPL");

