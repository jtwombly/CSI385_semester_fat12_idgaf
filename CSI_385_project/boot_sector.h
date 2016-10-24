/*
 * boot_sector.h
 *
 *  Created on: Oct 21, 2016
 *      Author: victoria
 */

#ifndef BOOT_SECTOR_H_
#define BOOT_SECTOR_H_

struct boot_sector {
	int bp_sector;
	int sp_cluster;
	int num_fats;
	int num_res_sectors;
	int num_root;
	int num_sector;
	int sp_fat;
	int sp_track;
	int num_heads;
	char boot_sig;
	char* vol_id;
	char* sys_type;
	char* vol_label;
};

#endif /* BOOT_SECTOR_H_ */
