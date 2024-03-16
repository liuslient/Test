#ifndef _TFS_H_
#define _TFS_H_

#define FUSE_USE_VERSION 26
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "fcntl.h"
#include "string.h"
#include "fuse.h"
#include <stddef.h>
#include "ddriver.h"
#include "errno.h"
#include "types.h"
#include "stdint.h"
#include "types.h"

#define TFS_MAGIC                  /* TODO: Define by yourself */
#define TFS_DEFAULT_PERM    0777   /* 全权限打开 */

/******************************************************************************
* SECTION: macro debug
*******************************************************************************/
#define TFS_DBG(fmt, ...) do { printf("SFS_DBG: " fmt, ##__VA_ARGS__); } while(0) 
/******************************************************************************
* SECTION: tfs_utils.c
*******************************************************************************/
char *tfs_get_fname(const char *path);
int 			   tfs_calc_lvl(const char *path);
int 			   tfs_driver_read(int offset, uint8_t *out_content, int size);
int 			   tfs_driver_write(int offset, uint8_t *in_content, int size);


int 			   tfs_mount(struct custom_options options);
int 			   tfs_umount();

int 			   tfs_alloc_dentry(struct tfs_inode *inode, struct tfs_dentry *dentry);
int 			   tfs_drop_dentry(struct tfs_inode *inode, struct tfs_dentry *dentry);
struct tfs_inode *tfs_alloc_inode(struct tfs_dentry *dentry);
int 			   tfs_sync_inode(struct tfs_inode *inode);
int 			   tfs_drop_inode(struct tfs_inode *inode);
struct tfs_inode *tfs_read_inode(struct tfs_dentry *dentry, int ino);
struct tfs_dentry *tfs_get_dentry(struct tfs_inode *inode, int dir);

struct tfs_dentry *tfs_lookup(const char *path, boolean *is_find, boolean *is_root);

/******************************************************************************
* SECTION: tfs.c
*******************************************************************************/
void *tfs_init(struct fuse_conn_info *);
void  			   tfs_destroy(void *);
int   			   tfs_mkdir(const char *, mode_t);
int   			   tfs_getattr(const char *, struct stat *);
int   			   tfs_readdir(const char *, void *, fuse_fill_dir_t, off_t,
	struct fuse_file_info *);
int   			   tfs_mknod(const char *, mode_t, dev_t);
int   			   tfs_write(const char *, const char *, size_t, off_t,
	struct fuse_file_info *);
int   			   tfs_read(const char *, char *, size_t, off_t,
	struct fuse_file_info *);
int   			   tfs_access(const char *, int);
int   			   tfs_unlink(const char *);
int   			   tfs_rmdir(const char *);
int   			   tfs_rename(const char *, const char *);
int   			   tfs_utimens(const char *, const struct timespec tv[2]);
int   			   tfs_truncate(const char *, off_t);

int   			   tfs_open(const char *, struct fuse_file_info *);
int   			   tfs_opendir(const char *, struct fuse_file_info *);

#endif  /* _tfs_H_ */