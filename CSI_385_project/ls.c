/*
 * ls.c
 *
 *  Created on: Nov 2, 2016
 *      Author: vhayes-dev
 */
#include "shell_code.h"

void ls(struct boot_sector BS, char** fields, int num_params, char* current_dir)
{
	/*
	 * Goals:
	 * Check to see if ls command was given a path paramter
	 * if not, use cwd
	 * if so, find absolute path and verify if it exists.
	 * if directory, list its contents.
	 * if file, list information on it
	 */
	char* mdir;
	if(num_params == 1)
	{
		 mdir= current_dir;
	}
	else if (strcmp(fields[1],"/")==0)
	{
		mdir = "/";
	}
	else{
		mdir = get_absolute_path(current_dir, fields[1]);
	}
	//printf("%s\n", mdir);
	char* tmpdir = malloc(strlen(mdir));
	strcpy(tmpdir, mdir);
	struct file_data m_file;
	int success = 0;
	success = find_target(tmpdir, BS, &m_file);
	if(success == 0)
	{
		printf("File %s does not exist.\n", mdir);
		free(tmpdir);
	}
	else if (m_file.attr != 16){
		//file is a file, not a directory
		setvbuf (stdout, NULL, _IONBF, 0);
		char* parent_dir = find_parent_dir(mdir);
		//printf("%s, %s\n", parent_dir, mdir);
		find_target(parent_dir, BS, &m_file);
		list_file(BS, &m_file, mdir);
		free(tmpdir);
	}
	else{
		printf("listing directory...\n");
		list_dir(BS, &m_file);
		free(tmpdir);
		free(mdir);
	}
}

char* find_parent_dir(char* child_file){
	/*
	 * removes the last block of a path, turning a
	 * path for a file into the path for its parent
	 * directory
	 */
	char * pdir;
	char** fields;
	int size = 1;
	int num_params = 1;
	fields = malloc(num_params * sizeof(char*));
	fields[0] = strtok(child_file, "/");

	while (fields[num_params - 1] != NULL) {
		//find number of parameters
		num_params += 1;
		fields = realloc(fields, num_params * sizeof(char*));
		fields[num_params - 1] = strtok(NULL, "/");
	}
	num_params -= 2;
	for(int i=0; i<num_params; i++){
		size += strlen(fields[i] + 1);
	}
	pdir = malloc(size * sizeof(char));
	strcpy(pdir, "/");
	for(int j=0; j<num_params; j++){
		strcpy(pdir, fields[j]);
		strcpy(pdir, "/");
	}
	strcpy(child_file, fields[num_params]);
	//printf("%s, %s\n", child_file, pdir);
	return pdir;
}

int list_dir(struct boot_sector BS, struct file_data* MF)
{
	printf("here1, %s, %d\n", MF->filename, MF->first_logical_cluster);
	printf("ls for a directory\n");
	setvbuf (stdout, NULL, _IONBF, 0);
	int fin = 0;

	int start_sector = (BS.num_fats * BS.sp_fat) + 1;

	if(MF->filename != NULL && MF->first_logical_cluster > 1){
		start_sector += 12 + MF->first_logical_cluster;
	}
	printf("Reading sector: %d\n", start_sector);
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
			MF->filename = clean_filename(MF->filename);
			for (int k = 0; k<3; k++)
			{
				MF->ext[k] = sector[(j*32)+ 8 + k];
			}

			MF->attr = sector[(j*32) + 11];
			MF->first_logical_cluster = get_large_int(sector, (j*32) + 26);
			MF->file_size = get_huge_int(sector, (j*32) + 28);
			if(strlen(MF->filename)>0){
				printf("%s,%s, %d, %d, %d\n", MF->filename, MF->ext, MF-> attr, MF->first_logical_cluster, MF->file_size);
			}
			free(MF->filename);
			free(MF->ext);
		}
		free(sector);
		start_sector +=1;
	}
	return 0;
}

int list_file(struct boot_sector BS, struct file_data* MF, char* file_name)
{
	setvbuf (stdout, NULL, _IONBF, 0);
	int fin = 0;
	//printf("ls for a file\n file %s", file_name);
	int start_sector = (BS.num_fats * BS.sp_fat) + 1;

	if(MF->filename != NULL && MF->first_logical_cluster > 1){
			start_sector += 12 + MF->first_logical_cluster;
		}
	char* f_name = strtok(file_name, ".");
		char* f_ext = strtok(NULL, ".");
		if(f_ext){
			for(int j=0; j<strlen(f_ext); j++){
				f_ext[j] = toupper(f_ext[j]);
			}
		}
		char* temp_string = malloc(strlen(f_name));
		for(int i=0; i< strlen(file_name); i++)
		{
			temp_string[i] = toupper(file_name[i]);
		}

		file_name = strcpy(file_name, temp_string);
		free(temp_string);
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
			MF->filename = clean_filename(MF->filename);
			for (int k = 0; k<3; k++)
			{
				MF->ext[k] = sector[(j*32)+ 8 + k];
			}

			MF->attr = sector[(j*32) + 11];
			MF->first_logical_cluster = get_large_int(sector, (j*32) + 26);
			MF->file_size = get_huge_int(sector, (j*32) + 28);
			if(strcmp(MF->filename, file_name) == 0){
				if(strncmp(MF->ext, f_ext, strlen(f_ext)) == 0){
					printf("%s,%s, %d, %d, %d\n", MF->filename, MF->ext, MF-> attr, MF->first_logical_cluster, MF->file_size);
				}
			}
			free(MF->filename);
			free(MF->ext);
		}
		start_sector +=1;
	}
	return 0;
}
