/******************************************************************************
 * main: Sample for starting the FAT project.
 *
 * Authors:  Andy Kinley, Archana Chidanandan, David Mutchler and others.
 *           March, 2004.
 *****************************************************************************/

#include <stdio.h>
#include "shell_code.h"
#include "fatSupport.h"


/******************************************************************************
 * main: an example of reading an item in the boot sector
 *****************************************************************************/

int main(int argc, char * argv[])
{
	int file_choice = 0;
	if (argc == 2)
	{
		int file_choice = atoi(argv[1]);
		if (file_choice > 3 || file_choice <  0)
		{
			file_choice = 0;
		}
		switch(file_choice)
		{
		case 0:
		case 1:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy1", "r+");
			printf("floppy 1");
			break;
		case 2:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy2", "r+");
			printf("floppy 2");
			break;
		case 3:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy3", "r+");
			printf("floppy 3");
			break;
		default:
			printf("error in handler\n");
			break;
		}
		shell();
	}
	else if (argc == 1){
		FILE_SYSTEM_ID = fopen("Sample_disks/floppy1", "r+");
		shell();
	}
	else if (argc > 2){
		printf("Incorrect number of arguments\n");
		return 1;
	}
   return 0;
}
