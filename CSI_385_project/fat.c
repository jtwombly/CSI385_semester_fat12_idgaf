/******************************************************************************
 * main: Sample for starting the FAT project.
 *
 * Authors:  Andy Kinley, Archana Chidanandan, David Mutchler and others.
 *           March, 2004.
 *****************************************************************************/

#include <stdio.h>
#include "shell_code.h"
#include "fatSupport.h"

/*
 * Parses command lines args, if given.
 * If arg is non-existent, continues as normal.
 * If arg is 0, 1, 2, 3, opens appropriate file.
 * If incorrect arg is given, it is changed to 0
 * If too many args are given, exits with error.
 */

int main(int argc, char * argv[])
{
	int file_choice = 0;
	if (argc == 2 || argc == 1)
	{
		int file_choice = 0;
		if (argc > 1){
			file_choice = atoi(argv[1]);
		}
		if (file_choice > 3 || file_choice <  0)
		{
			file_choice = 0;
		}
		switch(file_choice)
		{
		case 0:
		case 1:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy1", "r+");
			printf("floppy 1\n");
			break;
		case 2:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy2", "r+");
			printf("floppy 2\n");
			break;
		case 3:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy3", "r+");
			printf("floppy 3\n");
			break;
		default:
			printf("error in handler\n");
			break;
		}
		shell();
	}
	else if (argc > 2){
		printf("Incorrect number of arguments\n");
		return 1;
	}
   return 0;
}
