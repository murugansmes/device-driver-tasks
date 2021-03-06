/***********************************************************************

*   Project Name : send_signal.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 30/6/2017
*
*   Description  : Kernel module to send signal to user application using its PID.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/siginfo.h>	
#include <linux/rcupdate.h>	
#include <linux/sched.h>	
#include <linux/debugfs.h>
#include <linux/uaccess.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/
#define SIG_TEST 44
/**********************************************************************
*   Global variable declerations 
***********************************************************************/
static struct denrty *file=0;
/***********************************************************************
*   Function Prototypes 
************************************************************************/
static ssize_t write_pid(struct file *file,const char __user *buf,size_t count,loff_t *ppos);
static int init(void);
void exit_module(void);
/**********************************************************************

*   Function    : write_pid()
*
*   Description : write function for the debug file(executed when PID is written on the debug file by the user application).
*
*   Parameters  : file pointer,buffer pointer,count of data to be read,seek position.
*
*   Return value: count of data to be read
***********************************************************************/
static ssize_t write_pid(struct file *file,const char __user *buf,size_t count,loff_t *ppos)
{
	char mybuf[10];
	int pid=0;
	int ret;
	struct siginfo info;
	struct task_struct *t;
	if(count>10)
	{
		return -EINVAL;
	}
	copy_from_user(mybuf,buf,count);
	sscanf(mybuf,"%d",&pid);
	printk("pid=%d\n",pid);
	memset(&info,0,sizeof(struct siginfo));
	info.si_signo=SIG_TEST;
	info.si_code=SI_QUEUE;
	info.si_int=7323;
	rcu_read_lock();
	t=pid_task(find_vpid(pid),PIDTYPE_PID);
	if(t==NULL)
	{
		printk("INVALID PID.\n");
	}
	rcu_read_unlock();
	ret=send_sig_info(SIG_TEST,&info,t);
	if(ret<0)
	{
		printk("error sending signal\n");
		return ret;
	}
	return count;
}
static const struct file_operations my_fops={
	.write=write_pid,
};
/**********************************************************************

*   Function    : init()
*
*   Description : initialization function of this module.
*
*   Parameters  : none.
*
*   Return value: 0.

***********************************************************************/
static int init(void)
{
	file=debugfs_create_file("signalconfpid",0200,NULL,NULL,&my_fops);
	return 0;
}
/**********************************************************************

*   Function    : exit_module()
*
*   Description : deinitialization function of this module.
*
*   Parameters  : none.
*
*   Return value: none.

***********************************************************************/
void exit_module(void)
{
	debugfs_remove(file);
	printk("THE SIGNAL SENDING MODULE HAS BEEN UNLOADED..");
}
module_init(init);
module_exit(exit_module);
MODULE_LICENSE("GPL");
