#ifndef _TYPES_H_
#define _TYPES_H_

/******************************************************************************
* SECTION: Type def
*******************************************************************************/
typedef int          boolean;
typedef uint16_t     flag16;

typedef enum tfs_file_type
{
    TFS_REG_FILE,
    TFS_DIR,
    TFS_SYM_LINK
} TFS_FILE_TYPE;

/******************************************************************************
* SECTION: Macro
*******************************************************************************/
#define TRUE                    1
#define FALSE                   0
#define UINT32_BITS             32
#define UINT8_BITS              8

#define TFS_MAGIC_NUM           0x52415453  
#define TFS_SUPER_OFS           0
#define TFS_ROOT_INO            0

/* 规定各区间占的 BLK 数 */
#define TFS_SUPER_BLKS          1
#define TFS_MAP_INODE_BLKS      1
#define TFS_MAP_DATA_BLKS       1
#define TFS_INODE_BLKS          512
#define TFS_DATA_BLKS           2048

#define TFS_ERROR_NONE          0
#define TFS_ERROR_ACCESS        EACCES
#define TFS_ERROR_SEEK          ESPIPE     
#define TFS_ERROR_ISDIR         EISDIR
#define TFS_ERROR_NOSPACE       ENOSPC
#define TFS_ERROR_EXISTS        EEXIST
#define TFS_ERROR_NOTFOUND      ENOENT
#define TFS_ERROR_UNSUPPORTED   ENXIO
#define TFS_ERROR_IO            EIO     /* Error Input/Output */
#define TFS_ERROR_INVAL         EINVAL  /* Invalid Args */

#define TFS_MAX_FILE_NAME       128
#define TFS_INODE_PER_FILE      1
#define TFS_DATA_PER_FILE       16
#define TFS_DEFAULT_PERM        0777

#define TFS_IOC_MAGIC           'S'
#define TFS_IOC_SEEK            _IO(TFS_IOC_MAGIC, 0)

#define TFS_FLAG_BUF_DIRTY      0x1
#define TFS_FLAG_BUF_OCCUPY     0x2
/******************************************************************************
* SECTION: Macro Function
*******************************************************************************/
#define TFS_IO_SZ()                     (tfs_super.sz_io)
#define TFS_BLK_SZ()                    (tfs_super.sz_blk)      /* 1024B*/
#define TFS_DISK_SZ()                   (tfs_super.sz_disk)
#define TFS_DRIVER()                    (tfs_super.driver_fd)

#define TFS_ROUND_DOWN(value, round)    ((value) % (round) == 0 ? (value) : ((value) / (round)) * (round))
#define TFS_ROUND_UP(value, round)      ((value) % (round) == 0 ? (value) : ((value) / (round) + 1) * (round))

#define TFS_BLKS_SZ(blks)               ((blks) * TFS_IO_SZ())
#define TFS_ASSIGN_FNAME(pnfs_dentry, _fname) memcpy(pnfs_dentry->fname, _fname, strlen(_fname))
#define TFS_INO_OFS(ino)                (tfs_super.inode_offset + (ino) * TFS_BLK_SZ())
#define TFS_DATA_OFS(bno)               (tfs_super.data_offset + (bno) * TFS_BLK_SZ())

#define TFS_IS_DIR(pinode)              (pinode->dentry->ftype == TFS_DIR)
#define TFS_IS_REG(pinode)              (pinode->dentry->ftype == TFS_REG_FILE)
/******************************************************************************
* SECTION: FS Specific Structure - In memory structure
*******************************************************************************/
struct tfs_dentry;
struct tfs_inode;
struct tfs_super;


struct custom_options
{
    const char *device;
};

struct tfs_super
{
    int                 driver_fd;          /* 打开的磁盘句柄 */

    int                 sz_io;              /* 512B */
    int                 sz_blk;             /* 1024B */
    int                 sz_disk;            /* 4MB */
    int                 sz_usage;           /* ioctl 相关信息 */

    int                 max_ino;
    int                 max_data;

    uint8_t *map_inode;          /* 指向 inode 位图的内存起点 */
    int                 map_inode_blks;     /* inode 位图占用的块数 */
    int                 map_inode_offset;   /* inode 位图在磁盘上的偏移 */

    uint8_t *map_data;           /* 指向 data 位图的内存起点 */
    int                 map_data_blks;      /* data 位图占用的块数 */
    int                 map_data_offset;    /* data 位图在磁盘上的偏移 */

    int                 inode_offset;       /* 索引结点的偏移 */
    int                 data_offset;        /* 数据块的偏移*/

    boolean             is_mounted;

    struct tfs_dentry *root_dentry;
};

struct tfs_inode
{
    uint32_t            ino;
    int                 size;                               /* 文件已占用空间 */
    int                 dir_cnt;
    struct tfs_dentry *dentry;                             /* 指向该 inode 的 父dentry */
    struct tfs_dentry *dentrys;                            /* 如果是 DIR，指向其所有子项（用链表串接）*/
    uint8_t *block_pointer[TFS_DATA_PER_FILE];   /* 如果是 FILE，指向 4 个数据块，四倍结构 */
    int                 bno[TFS_DATA_PER_FILE];             /* 数据块在磁盘中的块号 */
};

struct tfs_dentry
{
    char                fname[TFS_MAX_FILE_NAME];
    struct tfs_dentry *parent;             /* 父亲 Inode 的 dentry */
    struct tfs_dentry *brother;            /* 下一个兄弟 Inode 的 dentry */
    uint32_t            ino;
    struct tfs_inode *inode;              /* 指向inode */
    TFS_FILE_TYPE       ftype;
};


static inline struct tfs_dentry *new_dentry(char *fname, TFS_FILE_TYPE ftype)
{
    struct tfs_dentry *dentry = (struct tfs_dentry *)malloc(sizeof(struct tfs_dentry)); /* dentry 在内存空间也是随机分配 */
    memset(dentry, 0, sizeof(struct tfs_dentry));
    TFS_ASSIGN_FNAME(dentry, fname);
    dentry->ftype = ftype;
    dentry->ino = -1;
    dentry->inode = NULL;
    dentry->parent = NULL;
    dentry->brother = NULL;
    return dentry;
}

/******************************************************************************
* SECTION: FS Specific Structure - Disk structure
*******************************************************************************/
struct tfs_super_d
{
    uint32_t    magic_num;
    int         sz_usage;

    int         map_inode_blks;     /* inode 位图占用的块数 */
    int         map_inode_offset;   /* inode 位图在磁盘上的偏移 */

    int         map_data_blks;      /* data 位图占用的块数 */
    int         map_data_offset;    /* data 位图在磁盘上的偏移 */

    int         inode_offset;       /* 索引结点的偏移 */
    int         data_offset;        /* 数据块的偏移*/
};

struct tfs_inode_d
{
    uint32_t        ino;            /* 在inode位图中的下标 */
    int             size;           /* 文件已占用空间 */
    int             dir_cnt;
    TFS_FILE_TYPE   ftype;
    int             bno[TFS_DATA_PER_FILE];       /* 数据块在磁盘中的块号 */
};

struct tfs_dentry_d
{
    char            fname[TFS_MAX_FILE_NAME];
    TFS_FILE_TYPE   ftype;
    uint32_t        ino;            /* 指向的 ino 号 */
};

#endif /* _TYPES_H_ */