/***********************************************************************

*   Project Name : ioctl_user.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 27/6/2017
*
*   Description  : User space application that makes ioctl calls.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include "ioctl_header.h"
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/
#define SIG_TEST 44
/**********************************************************************
*   Global variable declerations 
***********************************************************************/

/***********************************************************************
*   Function Prototypes 
************************************************************************/
ioctl_set_msg(int file_desc,char *message);
ioctl_get_msg(int file_desc);
/**********************************************************************

*   Function    : ioctl_set_msg().
*
*   Description : Function to send message to kernel using ioctl call.
*
*   Parameters  : an integer, pointer which holds the message to be sent.
*
*   Return value: none.

***********************************************************************/

ioctl_set_msg(int file_desc,char *message)
{
	int ret_val;
	ret_val=ioctl(file_desc,IOCTL_SET_MSG,message);
	if(ret_val<0)
	{
		printf("	ioctl_set_msg failed :%d\n",ret_val);
		exit(-1);
	}
}
/**********************************************************************

*   Function    : ioctl_get_msg().
*
*   Description : Function to get message from kernel using an ioctl call.
*
*   Parameters  : an integer.
*
*   Return value: none.

***********************************************************************/
void recieveData(int n,siginfo_t *info,void *unused)
{
	printf("\n\t\tThe recieved value is %i.\n\n",info->si_int);
}

ioctl_get_msg(int file_desc)
{
	int ret_val;
	char message[100];
	ret_val=ioctl(file_desc,IOCTL_GET_MSG,message);
	if(ret_val<0)
	{
		printf("	ioctl_get_msg failed:%d\n",ret_val);
		exit(-1);
	}
	printf("\n\n\t\tMESSAGE READ FROM THE DEVICE FILE IS	    :%s\n\n",message);
}

void main()
{
	char buf[10];
	system("clear");
	struct sigaction sig;
	sig.sa_sigaction=recieveData;
	sig.sa_flags=SA_SIGINFO;
	sigaction(SIG_TEST,&sig,NULL);
	int file_desc,ret_val,i=0,Option,configfd;
	char *msg,y;
	msg=malloc(10*sizeof(char));
	system("clear");
	/*file_desc=open(DEVICE_FILE_NAME,0);
	if(file_desc<0)
	{
		printf("	Cant open device file:%s\n",DEVICE_FILE_NAME);
		exit(-1);
	}
	/*here:
	printf("\t\tCHOOSE THE ACTION TO BE PERFORMED:\n\n\t\t1)WRITE TO DEVICE FILE. 2)READ FROM DEVICE FILE\n\n\t\tOption:");
	scanf("%d",&Option);
	switch(Option){
	case 1:
	{
	/*printf("\t\tENTER THE MESSAGE TO BE SENT TO KERNEL SPACE:");
	scanf("%c",msg);
	while(1)
	{	
		scanf("%c",(msg+i));
		if(*(msg+i)=='\n')
		{
			*(msg+i)='\0';
			break;
		}
	i++;
	}*/
	configfd = open("/dev/ioctl_buffer",O_WRONLY);
	if(configfd<0)
	{
		perror("Open.");
		//return -1;
	}
	sprintf(buf,"%i",getpid());
	if(write(configfd,buf,strlen(buf)+1)<0)
	{
		perror("fWrite");
		//return -1;
	}
	//return 0;
	//sprintf(msg,"%i",getpid());
	printf("\n\n\t\tmy pid is %s.\n\n",buf);
	ioctl_set_msg(configfd,buf);
	//break;
	/*}
	case 2:ioctl_get_msg(file_desc);
	default:printf("\n\t\tINVALID CHOICE!");
	}
	printf("\n\t\tDo you want to continue(y/n)?:");
	scanf("%c",&y);
	if(y=='y')
	{
		y=' ';
		goto here;
	}*/
	//close(file_desc);
	//while(1);
}
