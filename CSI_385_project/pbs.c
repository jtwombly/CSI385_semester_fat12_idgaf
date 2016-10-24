/*
 * pbs.c
 *
 *  Created on: Oct 21, 2016
 *      Author: victoria
 */

#include "shell_code.h"

struct boot_sector rbs() {
	struct boot_sector BS;
	unsigned char* boot;
	// Set it to this only to read the boot sector
	BYTES_PER_SECTOR = BYTES_TO_READ_IN_BOOT_SECTOR;
	// Then reset it per the value in the boot sector

	boot = (unsigned char*) malloc(BYTES_PER_SECTOR * sizeof(unsigned char));

	if (read_sector(0, boot) == -1)
		printf("Something has gone wrong -- could not read the boot sector\n");
	BS.vol_label = malloc(11 * sizeof(char));
	BS.sys_type = malloc(8 * sizeof(char));
	BS.vol_id = malloc(4 * sizeof(char));
	BS.bp_sector = get_large_int(boot, 11);
	BS.sp_cluster = (int) boot[13];
	BS.num_fats = (int) boot[16];
	BS.num_res_sectors = get_large_int(boot, 14);
	BS.num_root = get_large_int(boot, 17);
	BS.num_sector = get_large_int(boot, 19);
	BS.sp_fat = get_large_int(boot, 22);
	BS.sp_track = get_large_int(boot, 24);
	BS.num_heads = get_large_int(boot, 26);
	BS.boot_sig = boot[38];
	for (int i = 0; i < 4; i++) {
		BS.vol_id[i] = boot[39 + i];
	}
	for (int i = 0; i < 8; i++) {
		BS.sys_type[i] = boot[54 + i];
	}
	for (int i = 0; i < 11; i++) {
		BS.vol_label[i] = boot[43 + i];
	}
	BYTES_PER_SECTOR = BS.bp_sector;
	return BS;
}

int get_large_int(char* boot, int val) {
	int mostSignificantBits;
	int leastSignificantBits;
	int bytesPerSector;

	mostSignificantBits = (((int) boot[val + 1]) << 8) & 0x0000ff00;
	leastSignificantBits = ((int) boot[val]) & 0x000000ff;
	bytesPerSector = mostSignificantBits | leastSignificantBits;

	return bytesPerSector;
}

int get_huge_int(char* boot, int val) {
	int sum = 0;
	sum = boot[val] | (boot[val + 1] << 8) | (boot[val + 2] << 16)
			| (boot[val + 3] << 24);
	return sum;
}
void pbs(struct boot_sector BS) {
	printf("Bytes per sector			=%d\n", BS.bp_sector);
	printf("Sectors per cluster			=%d\n", BS.sp_cluster);
	printf("Number of FATs				=%d\n", BS.num_fats);
	printf("Number of Reserved Sectors		=%d\n", BS.num_res_sectors);
	printf("Number of root entries 			=%d\n", BS.num_root);
	printf("Total sector count			=%d\n", BS.num_sector);
	printf("Sectors per FAT				=%d\n", BS.sp_fat);
	printf("Sectors per track			=%d\n", BS.sp_track);
	printf("Number of heads				=%d\n", BS.num_heads);
	printf("Boot signature (in hex)			=0x%2x\n", BS.boot_sig);
	printf("Volume ID (in hex)			=0x8%2x\n", BS.vol_id);
	printf("Volume Label				=%s\n", BS.vol_label);
	printf("File System Type			=%s\n", BS.sys_type);
}
