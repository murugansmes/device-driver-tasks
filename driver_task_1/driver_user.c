#include<stdio.h>
void main()
{
FILE *p;
p=fopen("/dev/driver_3","r");
printf("The driver file has been opened");
fclose(p);
}
