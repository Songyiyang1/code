#include "../lib/operations.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int
fs_mkdir(file_system *fs, char *path)
{
	int i=find_free_inode(fs);
	fs->inodes[i].n_type=directory;
	char* name=strrchr(path, '/');
	if (strlen(name)>NAME_MAX_LENGTH)
		return -1;
	strncpy(fs->inodes[i].name,name,NAME_MAX_LENGTH);
	char* parent=strrchr(path-strlen(name),'/');
	uint16_t parent_len = name-parent-1;
	if (parent_len==0) {
		fs->inodes[i].parent=fs->root_node;
		for (int j=0;j<DIRECT_BLOCKS_COUNT;j++) {
			if (fs->inodes[fs->root_node].direct_blocks[j]==-1) {
				fs->inodes[fs->root_node].direct_blocks[j]=i;
				return 0;
			}
		}
	}
	int parent_index=-1;
	strncpy(parent,parent,parent_len);
	for (int j=0; j<fs->s_block->num_blocks; j++) {
		if(fs->inodes[j].name==parent){
			parent_index=j;
			break;
		}
	}
	if (parent_index==-1)
		return -1;
	fs->inodes[i].parent=parent_index;
	for (int j=0;j<DIRECT_BLOCKS_COUNT;j++) {
		if (fs->inodes[parent_index].direct_blocks[j]==-1) {
			fs->inodes[parent_index].direct_blocks[j]=i;
			return 0;
		}
	}
	return 0;

}

int
fs_mkfile(file_system *fs, char *path_and_name)
{
	return -1;
}

int
fs_cp(file_system *fs, char *src_path, char *dst_path_and_name)
{
	return -1;
}

char *
fs_list(file_system *fs, char *path)
{
	return NULL;
}

int
fs_writef(file_system *fs, char *filename, char *text)
{
	return -1;
}

uint8_t *
fs_readf(file_system *fs, char *filename, int *file_size)
{
	return NULL;
}


int
fs_rm(file_system *fs, char *path)
{
	return -1;
}

int
fs_import(file_system *fs, char *int_path, char *ext_path)
{
	return -1;
}

int
fs_export(file_system *fs, char *int_path, char *ext_path)
{
	return -1;
}
