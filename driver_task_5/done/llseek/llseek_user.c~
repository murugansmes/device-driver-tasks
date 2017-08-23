/***********************************************************************

*   Project Name : llseek_user.c
*
*   Author       : MURUGAN S
*                  murugan.s@fossilshale.com
*   Date         : 5/7/2017 
*
*   Description  : User space application to read,write and seek a device file.
*
*   Copyright © Fossilshale Embedded Technologies Pvt. Ltd.

***********************************************************************/

/**********************************************************************
*   Header Files Inclusion 
***********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<malloc.h>
/**********************************************************************
*   Macro Substitutions
***********************************************************************/
#define DEVICE "/dev/my_llseek"
/**********************************************************************
*   Global variable declerations 
***********************************************************************/
int fd = 0;
/***********************************************************************
*   Function Prototypes 
************************************************************************/
int write_device();
int read_device();
int lseek_device();
int lseek_write();
int lseek_read();
/**********************************************************************
*   Function    : write_device()
*
*   Description : Fuction to write into device file.
*
*   Parameters  : none.
*
*   Return value: 0.
***********************************************************************/
int write_device() {
    int write_length = 0;
    ssize_t ret;
    char *data = (char *)malloc(1024 * sizeof(char));
    printf("\n\t\tEnter the data to write into device:\n\t\t");
    scanf(" %[^\n]",data);
    write_length = strlen(data);
    printf("\n\t\tThe length of data written:%d\n",write_length);
    ret = write(fd,data,write_length);
    if(ret == -1)
    {
        printf("\n\t\tWriting failed.\n");
    }
    else
        printf("\n\t\tWriting success.\n");
    free(data);
return 0;
}
/**********************************************************************
*   Function    : read_device()
*
*   Description : Fuction to read from device file.
*
*   Parameters  : none.
*
*   Return value: 0.
***********************************************************************/
int read_device() {
    int read_length = 0;
    ssize_t ret;
    char *data = (char *)malloc(1024 * sizeof(char));
    printf("\n\t\tEnter the length of the buffer to read:");
    scanf("%d",&read_length);
    printf("\n\t\tThe read length selected is %d\n",read_length);
    memset(data,0,sizeof(data));
    data[0] = '\0';
    ret = read(fd,data,read_length);
    printf("\n\t\tThe data read from the device is: %s\n\t\t",data);
    if(ret == -1)
        printf("\n\t\tReading failed\n");
    else
        printf("\n\t\tReading success\n");
    free(data);
return 0;
}
/**********************************************************************
*   Function    : llseek_device()
*
*   Description : Function to seek our device file.
*
*   Parameters  : none.
*
*   Return value: 0.
***********************************************************************/
int lseek_device(){
	int lseek_offset = 0,seek_value = 0;
	printf("\n\t\tEnter the seek offset:\n");
	scanf("%d",&lseek_offset);
	printf("seek_offset selected is %d\n",lseek_offset);
	printf("\t\t1)SEEK_SET\t\t2)SEEK_CUR\t\t3)SEEK_END\n");
	scanf("%d", &seek_value);
	printf("seek value = %d\n", seek_value);
	switch(seek_value)
	 {
		case 1: lseek(fd,lseek_offset,SEEK_SET);
		    return 0;
		    break;  
		case 2: lseek(fd,lseek_offset,SEEK_CUR);
		    return 0;
		    break;          
		case 3: lseek(fd,lseek_offset,SEEK_END);
		    return 0;
		    break;  
		default : printf("\t\tINVALID OPERATION!\n");
		    break;  
	 }
return 0;
}
/**********************************************************************
*   Function    : lseek_write() 
*
*   Description : Function to seek and write(combination of lseek_device() and write_device() functions).
*
*   Parameters  : none.
*
*   Return value: 0
***********************************************************************/
int lseek_write() 
{
	lseek_device();
	write_device();
	return 0;
}
/**********************************************************************
*   Function    : lseek_read() 
*
*   Description : Function to seek and read(combination of lseek_device() and read_device() functions).
*
*   Parameters  : none.
*
*   Return value: 0
***********************************************************************/
int lseek_read()
{
	lseek_device();
   	read_device();
	return 0;
}

int main()
{
    int value = 0;
    while(1) {
    printf("\n\n\t\tEnter the operation to be performed:\n\n\t\t1)Write\t\t\t2)Read\n\t\t3)Lseek and write\t4)Lseek and read\n\n\t\tchoice:");
    scanf("%d",&value);
        switch(value) {
            case 1 :printf("\n\t\tWrite option selected.\n");
            fd = open(DEVICE,O_RDWR);
            write_device();
            close(fd);
            break;
            case 2 :printf("\n\t\tRead option selected.\n"); 
            fd = open(DEVICE, O_RDWR);
            read_device();
            close(fd);
            break;
            case 3 :printf("\n\t\tLseek  option selected.\n");
            fd = open(DEVICE, O_RDWR);
            lseek_write();
            close(fd); 
            break;  
            case 4 :printf("\n\t\tLseek  option selected\n");
            fd = open(DEVICE, O_RDWR);
            lseek_read();   
            close(fd);
            break;
            default : printf("\n\t\tInvalid operation.\n");close(fd);exit(0);
        }
    }
    return 0;
}
