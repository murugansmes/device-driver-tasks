/***********************************************************************

*   Project Name : recieve_signal.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 30/6/2017
*
*   Description  : User application to recieve signal from kernel.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

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
void recieveData(int n,siginfo_t *info,void *unused);
/**********************************************************************

*   Function    : recieveData()
*
*   Description : Print the value sent by the kernel as signal.
*
*   Parameters  : signal number,pointer of type siginfo_t,an anused data pointer.
*
*   Return value: none.

***********************************************************************/
void recieveData(int n,siginfo_t *info,void *unused)
{
	printf("\n\t\t\tThe recieved value is %i.\n\n",info->si_int);
}

int main(int argc,char **argv)
{
	int configfd;
	char buf[10];
	system("clear");
	struct sigaction sig;
	sig.sa_sigaction=recieveData;
	sig.sa_flags=SA_SIGINFO;
	sigaction(SIG_TEST,&sig,NULL);
	configfd = open("/sys/kernel/debug/signalconfpid",O_WRONLY);
	if(configfd<0)
	{
		perror("Open.");
		return -1;
	}
	sprintf(buf,"%i",getpid());
	if(write(configfd,buf,strlen(buf)+1)<0)
	{
		perror("fWrite");
		return -1;
	}
	return 0;
	
}
