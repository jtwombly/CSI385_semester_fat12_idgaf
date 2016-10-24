/*
 * pfe.c
 *
 *  Created on: Oct 22, 2016
 *      Author: vhayes-dev
 */

#include "shell_code.h"

int checkRange(int min, int max)
{
	if(min > max)
	{
		printf("First parameter must be less than second.\n");
		return 1;
	}
	else if(min < 2){
		printf("First parameter must be greater than 2.\n");
		return 1;
	}
	return 0;
}

void pfe(int min, int max, struct boot_sector BS)
{
	if (checkRange(min, max) == 0)
	{
		char* fat_table = read_fat_table(BS, 0);

		for (int i = min; i < max; i++)
		{
			int val = get_fat_entry(i, fat_table);
			printf("Entry %d: %0x\n", i, val);
		}
		free(fat_table);
	}
}

char* read_fat_table(struct boot_sector BS, int x)
{
	//reads one entire fat table to giant string
	//approx. size = 4K
	char * fat_sector = malloc(BYTES_PER_SECTOR*(sizeof(char)));
	char * fat_table = malloc(BS.sp_fat * BYTES_PER_SECTOR*(sizeof(char)));
	int start = 1 + (x* BS.sp_fat);
	int end = (x + 1) * BS.sp_fat;
	if (x > BS.num_fats)
	{
		printf("Error: tried to read non-existent FAT table.\n");
		return NULL;
	}
	else{
		for(int i = start; i <= end; i++)
		{
			read_sector(i, fat_sector);
			fat_table = strncat(fat_table, fat_sector, BYTES_PER_SECTOR);
		}
	}
	free(fat_sector);
	return fat_table;
}
