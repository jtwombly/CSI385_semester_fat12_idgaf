/*
 * directory_data.h
 *
 *  Created on: Oct 23, 2016
 *      Author: vhayes-dev
 */

#ifndef FILE_DATA_H_
#define FILE_DATA_H_

struct file_data{
	//all char* will be allocated at declaration
	char* filename; 				//0 size 8
	char* ext;						//8 size 3
	int attr;						//11
	int first_logical_cluster;		//26 size 2
	int file_size;					//28 size 4
};

#endif /* FILE_DATA_H_ */
