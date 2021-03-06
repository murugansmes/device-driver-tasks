/***********************************************************************

*   Project Name : mouse_interrupt.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 5/7/2017
*
*   Description  : A driver which handles mouse interrupts.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/workqueue.h>
#include<linux/interrupt.h>
#include<asm/io.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/

/**********************************************************************
*   Global variable declerations 
***********************************************************************/
static struct workqueue_struct *queue;
static void got_click(struct work_struct *work1);
static int count=0;
/***********************************************************************
*   Function Prototypes 
************************************************************************/

/**********************************************************************
*   Function    : got_click()
*
*   Description : Bottom half function of our interrupt handling.
*
*   Parameters  : a pointer of type work_struct.
*
*   Return value:  none.
***********************************************************************/
static void got_click(struct work_struct *work1)
{
	printk(KERN_ALERT "\nMOUSE interrupt has been raised %d times.\n",++count);
}
DECLARE_WORK(work1,got_click);

/**********************************************************************
*   Function    : irq_handler()
*
*   Description : Top half interrupt handling funtion.This function is first invoked when the interrupt is generated.
*
*   Parameters  : irq number,dev_id.
*
*   Return value:  none.
***********************************************************************/
irqreturn_t irq_handler(int irq,void *dev_id)
{
	queue_work(queue,&work1);
	return IRQ_HANDLED;
}
/**********************************************************************

*   Function    : init_module()
*
*   Description : Initialization module of this function.
*
*   Parameters  : void.
*
*   Return value:  0.

***********************************************************************/
int init_module(void)
{
	printk("\nMouse interrupt module has been loaded.\n");
	free_irq(18,(void*)(irq_handler));
	queue=create_singlethread_workqueue("myworkqueue");
	return request_irq(18,irq_handler,IRQF_SHARED,"test_mouse_interrupt",(void*)(irq_handler));
	return 0;
}/**********************************************************************

*   Function    : cleanup_module()
*
*   Description : Deinitialization module of this function.
*
*   Parameters  : void.
*
*   Return value: none.

***********************************************************************/
void cleanup_module(void)
{
	free_irq(18,(void*)(irq_handler));
	cancel_work_sync(&work1);
	destroy_workqueue(queue);
	printk("\nMouse interrupt module has been unloaded.\n");
	
}
MODULE_LICENSE("GPL");
