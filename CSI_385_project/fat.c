/******************************************************************************
 * main: Sample for starting the FAT project.
 *
 * Authors:  Andy Kinley, Archana Chidanandan, David Mutchler and others.
 *           March, 2004.
 *****************************************************************************/

#include <stdio.h>
#include "shell_code.h"
#include "fatSupport.h"

// 13 is NOT the correct number -- you fix it!
#define BYTES_TO_READ_IN_BOOT_SECTOR 12

/******************************************************************************
 * You must set these global variables:
 *    FILE_SYSTEM_ID -- the file id for the file system (here, the floppy disk
 *                      filesystem)
 *    BYTES_PER_SECTOR -- the number of bytes in each sector of the filesystem
 *
 * You may use these support functions (defined in FatSupport.c)
 *    read_sector
 *    write_sector
 *    get_fat_entry
 *    set_fat_entry
 *****************************************************************************/

FILE* FILE_SYSTEM_ID;
int BYTES_PER_SECTOR;


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
			break;
		case 2:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy2", "r+");
			break;
		case 3:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy3", "r+");
			break;
		default:
			FILE_SYSTEM_ID = fopen("Sample_disks/floppy1", "r+");
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

int sample_code()
{
	unsigned char* boot;            // example buffer

	int mostSignificantBits;
	int leastSignificantBits;
	int bytesPerSector;

	// You must set two global variables for the disk access functions:
	//      FILE_SYSTEM_ID         BYTES_PER_SECTOR

	// Use this for an image of a floppy drive
	FILE_SYSTEM_ID = fopen("Sample_disks/floppy1", "r+");

	if (FILE_SYSTEM_ID == NULL)
	{
	  printf("Could not open the floppy drive or image.\n");
	  exit(1);
	}

	// Set it to this only to read the boot sector
	BYTES_PER_SECTOR = BYTES_TO_READ_IN_BOOT_SECTOR;

	// Then reset it per the value in the boot sector

	boot = (unsigned char*) malloc(BYTES_PER_SECTOR * sizeof(unsigned char));

	if (read_sector(0, boot) == -1)
	  printf("Something has gone wrong -- could not read the boot sector\n");


	// 12 (not 11) because little endian
	mostSignificantBits  = ( ( (int) boot[12] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) boot[11] )        & 0x000000ff;
	bytesPerSector = mostSignificantBits | leastSignificantBits;

	printf("%d\n", bytesPerSector);

	return 0;
}
