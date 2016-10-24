/*
 * cd.c
 *
 *  Created on: Oct 23, 2016
 *      Author: vhayes-dev
 */

#include "shell_code.h"


char* cd(struct boot_sector BS,char** fields, int num_params, char* current_dir)
{
	if(num_params == 1)
	{
		 current_dir= "/";
	}
	else if (strcmp(fields[1],"/")==0)
	{
		current_dir = "/";
	}
	else{
		char* mdir = get_absolute_path(current_dir, fields[1]);

		char* tmpdir = malloc(strlen(mdir));
		strcpy(tmpdir, mdir);
		struct file_data m_file;
		int success = 0;
		success = find_target(tmpdir, BS, &m_file);
		if(success == 0)
		{
			printf("Directory %s does not exist.\n", mdir);
			free(tmpdir);
		}
		else if (m_file.attr != 16){
			printf("%s is not a directory.\n", mdir);
			free(tmpdir);
		}
		else{
			free(tmpdir);
			printf("bye");
			current_dir = malloc(strlen(mdir));
			current_dir = strcpy(current_dir, mdir);
			printf("%s\n", current_dir);
			free(mdir);
		}
	}
	return current_dir;
}

/*
 * Checks to see if a given path is absolute or relative.
 * If relative, creates absolute path.
 */
char* get_absolute_path(char* cwd, char* param)
{
	char* target_dir = "";
	if( strncmp(param, "/", 1) != 0)
	{
		target_dir = malloc(strlen(cwd)+ strlen(param)+2);
		strcpy(target_dir, cwd);
		strcat(target_dir, param);
	}
	else {
		//absolute path given
		target_dir = param;
	}
	return target_dir;
}

int find_target(char* abs_path, struct boot_sector BS, struct file_data* MF)
{

	int found = 0;
	char ** fields;
	int num_params = 1;
	fields = malloc(num_params * sizeof(char*));
	abs_path = strtok(abs_path, "/");
	fields[0] = strtok(abs_path, "/");
	while (fields[num_params-1] != NULL) {
		//find number of parameters
		num_params += 1;
		fields = realloc(fields, num_params * sizeof(char*));
		fields[num_params - 1] = strtok(NULL, "/");
	}
	printf("Num_params = %d\n", num_params);
	for(int i=0; i< num_params - 1; i++)
		{
			fields[i] = strtok(fields[i], "\n");
			printf("%s\n", fields[i]);
			//search child directories
			if(MF->attr==16 || !MF->attr)
			{
				found = search_dir(fields[i], BS, MF);
				if (found == 0){
					return 0;
				}
			}
			else{
				if(i == num_params-2)
				{
					return 1;
				}
				else{
					return 0;
				}
			}
		}
	return 1;
}

int search_dir(char* filename, struct boot_sector BS, struct file_data* MF)
{
	setvbuf (stdout, NULL, _IONBF, 0);
	int fin = 0;
	char* temp_string = malloc(strlen(filename));
	for(int i=0; i< strlen(filename); i++)
	{
		temp_string[i] = toupper(filename[i]);
	}

	filename = strcpy(filename, temp_string);
	free(temp_string);

	int start_sector = (BS.num_fats * BS.sp_fat) + 1;

	if(MF->filename != NULL){
		start_sector = MF->first_logical_cluster;
	}
	while(fin == 0){
		char * sector = malloc(BYTES_PER_SECTOR*(sizeof(char)));
		read_sector(start_sector, sector);
		for(int j=0; j<16; j++)
		{
			MF->filename = malloc(8 * sizeof(char));
			MF->ext = malloc(3 * sizeof(char));
			for (int k = 0; k<8; k++)
			{
				MF -> filename[k] = sector[(j*32) + k];
				if(k == 0){
					if(sector[(j*32)] == (char)0x00)
					{
						fin = 1;
						break;
					}
				}
			}
			for (int k = 0; k<3; k++)
			{
				MF->ext[k] = sector[(j*32)+ 8 + k];
			}

			MF->attr = sector[(j*32) + 11];
			MF->first_logical_cluster = get_large_int(sector, (j*32) + 26);
			MF->file_size = get_huge_int(sector, (j*32) + 28);
			if (strncmp(MF->filename, filename, strlen(filename)) == 0)
			{
				return 1;

			}
			free(MF->filename);
			free(MF->ext);
		}
		start_sector +=1;
	}
	return 0;
}


