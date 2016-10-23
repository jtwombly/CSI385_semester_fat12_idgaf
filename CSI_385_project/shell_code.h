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
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include "fatSupport.h"
#include "boot_sector.h"


int shell();

//in pbs.c
struct boot_sector rbs();
int get_large_int(char* boot, int val);
void pbs(struct boot_sector BS);

//in pfe.c
void pfe(int min, int max, struct boot_sector BS);
int checkRange(int min, int max);
char* read_fat_table(struct boot_sector BS, int x);

#endif /* SHELL_CODE_H_ */
