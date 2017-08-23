/***********************************************************************

*   Project Name : simple_jprobe.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 15/6/2017
*
*   Description  : Program to rotate the given byte to left or right. The input byte should be taken as command line.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/kprobes.h>
#include<linux/version.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/

/**********************************************************************
*   Global variable declerations 
***********************************************************************/

/***********************************************************************
*   Function Prototypes 
************************************************************************/
int probe_init(void);
void probe_exit(void);
static int jprobe_handler(int i);
/**********************************************************************/
MODULE_AUTHOR("MURUGAN ");
MODULE_DESCRIPTION("KPROBE");
MODULE_LICENSE("GPL");
/**********************************************************************

*   Function    : jprobe_handler()
*
*   Description : This functions handles when the probe is hit.
*
*   Parameters  : Same as that of the function being probed.
*
*   Return value: none. 

***********************************************************************/

static int jprobe_handler(int i)
{
 pr_info("\nJprobe:The value passed to the function mod1_func is %d",i);
 jprobe_return();
 return 0;
}

static struct jprobe jp;
/**********************************************************************

*   Function    : probe_init(void)
*
*   Description : init function of this module.
*
*   Parameters  : none.
*
*   Return value: 0.

***********************************************************************/
int probe_init(void)
{
 pr_info("\nJprobe has been created.");
 jp.kp.addr=(kprobe_opcode_t *)0xffffffffc0328000;
 jp.entry=(kprobe_opcode_t *)jprobe_handler;
 register_jprobe(&jp);
 return 0;
 }
 /**********************************************************************

*   Function    : probe_exit(void)
*
*   Description : exit function of this module.
*
*   Parameters  : none.
*
*   Return value: none.

***********************************************************************/
 void probe_exit(void)
 {
  unregister_jprobe(&jp);
  pr_info("\nJprobe has been removed.");
  }
  module_init(probe_init);
  module_exit(probe_exit);
