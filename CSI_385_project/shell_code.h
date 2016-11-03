/*
 * shell_code.h
 *
 *  Created on: Oct 18, 2016
 *      Author: victoria
 */

#ifndef SHELL_CODE_H_
#define SHELL_CODE_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include "fatSupport.h"
#include "boot_sector.h"
#include "file_data.h"

int shell();
//in pbs.c
struct boot_sector rbs();
int get_large_int(char* boot, int val);
int get_huge_int(char* boot, int val);
void pbs(struct boot_sector BS);

//in pfe.c
void pfe(int min, int max, struct boot_sector BS);
int checkRange(int min, int max);
char* read_fat_table(struct boot_sector BS, int x);

//in cd.c
char* cd(struct boot_sector BS, char** fields, int num_params,
		char* current_dir);
char* get_absolute_path(char* cwd, char* param);
int find_target(char* abs_path, struct boot_sector BS, struct file_data* MF);
int search_dir(char* filename, struct boot_sector BS, struct file_data* MF);
char* clean_filename(char* string);

//in ls.c
void ls(struct boot_sector BS, char** fields, int num_params, char* current_dir);
int list_dir(struct boot_sector BS, struct file_data* MF);
char* find_parent_dir(char* child_file);
int list_file(struct boot_sector BS, struct file_data* MF, char* file_name);


#endif /* SHELL_CODE_H_ */
