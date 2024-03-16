#include "../include/tfs.h"

extern struct tfs_super      tfs_super;
extern struct custom_options tfs_options;

/**
 * @brief 获取文件名
 *
 * @param path
 * @return char*
 */
char *tfs_get_fname(const char *path)
{
    char ch = '/';
    char *q = strrchr(path, ch) + 1;
    return q;
}

/**
 * @brief 计算路径的层级
 * exm: /av/c/d/f
 * -> lvl = 4
 * @param path
 * @return int
 */
int tfs_calc_lvl(const char *path)
{
    // char* path_cpy = (char *)malloc(strlen(path));
    // strcpy(path_cpy, path);
    char *str = path;
    int   lvl = 0;
    if (strcmp(path, "/") == 0)
    {
        return lvl;
    }
    while (*str != NULL)
    {
        if (*str == '/')
        {
            lvl++;
        }
        str++;
    }
    return lvl;
}

/**
 * @brief 驱动读
 *
 * @param offset
 * @param out_content
 * @param size
 * @return int
 */
int tfs_driver_read(int offset, uint8_t *out_content, int size)
{
    int      offset_aligned = TFS_ROUND_DOWN(offset, TFS_IO_SZ());
    int      bias = offset - offset_aligned;
    int      size_aligned = TFS_ROUND_UP((size + bias), TFS_IO_SZ());
    uint8_t *temp_content = (uint8_t *)malloc(size_aligned);
    uint8_t *cur = temp_content;
    // lseek(TFS_DRIVER(), offset_aligned, SEEK_SET);
    ddriver_seek(TFS_DRIVER(), offset_aligned, SEEK_SET);
    while (size_aligned != 0)
    {
        // read(TFS_DRIVER(), cur, TFS_IO_SZ());
        ddriver_read(TFS_DRIVER(), cur, TFS_IO_SZ());
        cur += TFS_IO_SZ();
        size_aligned -= TFS_IO_SZ();
    }
    memcpy(out_content, temp_content + bias, size);
    free(temp_content);
    return TFS_ERROR_NONE;
}
/**
 * @brief 驱动写
 *
 * @param offset
 * @param in_content
 * @param size
 * @return int
 */
int tfs_driver_write(int offset, uint8_t *in_content, int size)
{
    int      offset_aligned = TFS_ROUND_DOWN(offset, TFS_IO_SZ());
    int      bias = offset - offset_aligned;
    int      size_aligned = TFS_ROUND_UP((size + bias), TFS_IO_SZ());
    uint8_t *temp_content = (uint8_t *)malloc(size_aligned);
    uint8_t *cur = temp_content;
    tfs_driver_read(offset_aligned, temp_content, size_aligned);
    memcpy(temp_content + bias, in_content, size);

    // lseek(TFS_DRIVER(), offset_aligned, SEEK_SET);
    ddriver_seek(TFS_DRIVER(), offset_aligned, SEEK_SET);
    while (size_aligned != 0)
    {
        // write(TFS_DRIVER(), cur, TFS_IO_SZ());
        ddriver_write(TFS_DRIVER(), cur, TFS_IO_SZ());
        cur += TFS_IO_SZ();
        size_aligned -= TFS_IO_SZ();
    }

    free(temp_content);
    return TFS_ERROR_NONE;
}

/**
 * @brief 为一个inode分配dentry，采用头插法
 *
 * @param inode
 * @param dentry
 * @return int
 */
int tfs_alloc_dentry(struct tfs_inode *inode, struct tfs_dentry *dentry)
{
    if (inode->dentrys == NULL)
    {
        inode->dentrys = dentry;
    }
    else
    {
        dentry->brother = inode->dentrys;
        inode->dentrys = dentry;
    }
    inode->dir_cnt++;
    return inode->dir_cnt;
}


/**
 * @brief 分配一个inode，占用位图
 *
 * @param dentry 该dentry指向分配的inode
 * @return tfs_inode
 */
struct tfs_inode *tfs_alloc_inode(struct tfs_dentry *dentry)
{
    struct tfs_inode *inode;
    int byte_cursor = 0;
    int bit_cursor = 0;
    int ino_cursor = 0;
    int bno_cursor = 0;
    int data_blk_cnt = 0;
    boolean is_find_free_entry = FALSE;
    boolean is_enough_data_blk = FALSE;

    /* 从索引位图中取空闲 */
    for (byte_cursor = 0; byte_cursor < TFS_BLKS_SZ(tfs_super.map_inode_blks);
        byte_cursor++)
    {
        for (bit_cursor = 0; bit_cursor < UINT8_BITS; bit_cursor++)
        {
            if ((tfs_super.map_inode[byte_cursor] & (0x1 << bit_cursor)) == 0)
            {
                /* 当前ino_cursor位置空闲 */
                tfs_super.map_inode[byte_cursor] |= (0x1 << bit_cursor);
                is_find_free_entry = TRUE;
                break;
            }
            ino_cursor++;
        }
        if (is_find_free_entry)
        {
            break;
        }
    }

    if (!is_find_free_entry || ino_cursor == tfs_super.max_ino)
        return -TFS_ERROR_NOSPACE;

    /* 先分配一个 inode */
    inode = (struct tfs_inode *)malloc(sizeof(struct tfs_inode));
    inode->ino = ino_cursor;
    inode->size = 0;

    /* 从数据位图中取空闲，要取出若干个 */
    for (byte_cursor = 0; byte_cursor < TFS_BLKS_SZ(tfs_super.map_data_blks);
        byte_cursor++)
    {
        for (bit_cursor = 0; bit_cursor < UINT8_BITS; bit_cursor++)
        {
            if ((tfs_super.map_data[byte_cursor] & (0x1 << bit_cursor)) == 0)
            {
                /* 当前ino_cursor位置空闲 */
                tfs_super.map_data[byte_cursor] |= (0x1 << bit_cursor);

                /* 找到的块号立刻记入 inode，并判断找够了没 */
                inode->bno[data_blk_cnt++] = bno_cursor;
                if (data_blk_cnt == TFS_DATA_PER_FILE)
                {
                    is_enough_data_blk = TRUE;
                    break;
                }
            }
            bno_cursor++;
        }
        if (is_enough_data_blk)
        {
            break;
        }
    }

    if (!is_enough_data_blk || bno_cursor == tfs_super.max_data)
        return -TFS_ERROR_NOSPACE;

    /* dentry指向inode */
    dentry->inode = inode;
    dentry->ino = inode->ino;

    /* inode指回dentry */
    inode->dentry = dentry;

    inode->dir_cnt = 0;
    inode->dentrys = NULL;

    /* 对于文件，还需要预分配 pointer，指向内存中的随机块 */
    if (TFS_IS_REG(inode))
    {
        int p_count = 0;
        for (p_count = 0; p_count < TFS_DATA_PER_FILE; p_count++)
        {
            inode->block_pointer[p_count] = (uint8_t *)malloc(TFS_BLK_SZ());
        }
    }

    return inode;
}
/**
 * @brief 将内存inode及其下方结构全部刷回磁盘
 *
 * @param inode
 * @return int
 */
int tfs_sync_inode(struct tfs_inode *inode)
{
    struct tfs_inode_d  inode_d;
    struct tfs_dentry *dentry_cursor;
    struct tfs_dentry_d dentry_d;
    int ino = inode->ino;
    inode_d.ino = ino;
    inode_d.size = inode->size;
    inode_d.ftype = inode->dentry->ftype;
    inode_d.dir_cnt = inode->dir_cnt;

    int blk_cnt = 0;
    for (blk_cnt = 0; blk_cnt < TFS_DATA_PER_FILE; blk_cnt++)
        inode_d.bno[blk_cnt] = inode->bno[blk_cnt]; /* 数据块的块号也要赋值 */

    int offset, offset_limit;  /* 用于密集写回 dentry */

    /* inode 非密集写回，间隔一个 BLK */
    if (tfs_driver_write(TFS_INO_OFS(ino), (uint8_t *)&inode_d,
        sizeof(struct tfs_inode_d)) != TFS_ERROR_NONE)
    {
        TFS_DBG("[%s] io error\n", __func__);
        return -TFS_ERROR_IO;
    }
    /* Cycle 1: 写 INODE */
    /* Cycle 2: 写 数据 */
    if (TFS_IS_DIR(inode))
    {
        blk_cnt = 0;
        dentry_cursor = inode->dentrys;
        /* dentry 要存满 4 个不连续的 blk 块 */
        while (dentry_cursor != NULL && blk_cnt < TFS_DATA_PER_FILE)
        {
            offset = TFS_DATA_OFS(inode->bno[blk_cnt]); // dentry 从 inode 分配的首个数据块开始存
            offset_limit = TFS_DATA_OFS(inode->bno[blk_cnt] + 1);
            /* 写满一个 blk 时换到下一个 bno */
            while (dentry_cursor != NULL)
            {
                memcpy(dentry_d.fname, dentry_cursor->fname, TFS_MAX_FILE_NAME);
                dentry_d.ftype = dentry_cursor->ftype;
                dentry_d.ino = dentry_cursor->ino;
                /* dentry 密集写回 */
                if (tfs_driver_write(offset, (uint8_t *)&dentry_d,
                    sizeof(struct tfs_dentry_d)) != TFS_ERROR_NONE)
                {
                    TFS_DBG("[%s] io error\n", __func__);
                    return -TFS_ERROR_IO;
                }

                if (dentry_cursor->inode != NULL)
                {
                    tfs_sync_inode(dentry_cursor->inode); /* 递归 */
                }

                dentry_cursor = dentry_cursor->brother; /* 深搜 */
                offset += sizeof(struct tfs_dentry_d);
                if (offset + sizeof(struct tfs_dentry_d) > offset_limit)
                    break;
            }
            blk_cnt++; /* 访问下一个指向的数据块 */
        }
    }
    else if (TFS_IS_REG(inode))
    {
        for (blk_cnt = 0; blk_cnt < TFS_DATA_PER_FILE; blk_cnt++)
        {
            if (tfs_driver_write(TFS_DATA_OFS(inode->bno[blk_cnt]),
                inode->block_pointer[blk_cnt], TFS_BLK_SZ()) != TFS_ERROR_NONE)
            {
                TFS_DBG("[%s] io error\n", __func__);
                return -TFS_ERROR_IO;
            }
        }
    }
    return TFS_ERROR_NONE;
}
/**
 * @brief
 *
 * @param dentry dentry指向ino，读取该inode
 * @param ino inode唯一编号
 * @return struct tfs_inode*
 */
struct tfs_inode *tfs_read_inode(struct tfs_dentry *dentry, int ino)
{
    struct tfs_inode *inode = (struct tfs_inode *)malloc(sizeof(struct tfs_inode));
    struct tfs_inode_d inode_d;
    struct tfs_dentry *sub_dentry; /* 指向 子dentry 数组 */
    struct tfs_dentry_d dentry_d;
    int    blk_cnt = 0; /* 用于读取多个 bno */
    int    dir_cnt = 0, offset, offset_limit; /* 用于读取目录项 不连续的 dentrys */

    if (tfs_driver_read(TFS_INO_OFS(ino), (uint8_t *)&inode_d,
        sizeof(struct tfs_inode_d)) != TFS_ERROR_NONE)
    {
        TFS_DBG("[%s] io error\n", __func__);
        return NULL;
    }
    inode->dir_cnt = 0;
    inode->ino = inode_d.ino;
    inode->size = inode_d.size;
    inode->dentry = dentry;     /* 指回父级 dentry*/
    inode->dentrys = NULL;
    for (blk_cnt = 0; blk_cnt < TFS_DATA_PER_FILE; blk_cnt++)
        inode->bno[blk_cnt] = inode_d.bno[blk_cnt]; /* 数据块的块号也要赋值 */

    if (TFS_IS_DIR(inode))
    {
        dir_cnt = inode_d.dir_cnt;
        blk_cnt = 0; /* 离散的块号 */

        while (dir_cnt != 0)
        {
            offset = TFS_DATA_OFS(inode->bno[blk_cnt]); // dentry 从 inode 分配的首个数据块开始存
            offset_limit = TFS_DATA_OFS(inode->bno[blk_cnt] + 1);
            /* 写满一个 blk 时换到下一个 bno */
            while (offset + sizeof(struct tfs_dentry_d) < offset_limit)
            {
                if (tfs_driver_read(offset, (uint8_t *)&dentry_d,
                    sizeof(struct tfs_dentry_d)) != TFS_ERROR_NONE)
                {
                    TFS_DBG("[%s] io error\n", __func__);
                    return NULL;
                }

                sub_dentry = new_dentry(dentry_d.fname, dentry_d.ftype);
                sub_dentry->parent = inode->dentry;
                sub_dentry->ino = dentry_d.ino;
                tfs_alloc_dentry(inode, sub_dentry);

                offset += sizeof(struct tfs_dentry_d);
                dir_cnt--;
                if (dir_cnt == 0)
                    break;  /* 减到 0 后提前退出 */
            }
            blk_cnt++; /* 访问下一个指向的数据块 */
        }
    }
    else if (TFS_IS_REG(inode))
    {
        for (blk_cnt = 0; blk_cnt < TFS_DATA_PER_FILE; blk_cnt++)
        {
            inode->block_pointer[blk_cnt] = (uint8_t *)malloc(TFS_BLK_SZ()); /* 只分配一个块 */
            if (tfs_driver_read(TFS_DATA_OFS(inode->bno[blk_cnt]), inode->block_pointer[blk_cnt],
                TFS_BLK_SZ()) != TFS_ERROR_NONE)
            {
                TFS_DBG("[%s] io error\n", __func__);
                return NULL;
            }
        }
    }
    return inode;
}
/**
 * @brief
 *
 * @param inode
 * @param dir [0...]
 * @return struct tfs_dentry*
 */
struct tfs_dentry *tfs_get_dentry(struct tfs_inode *inode, int dir)
{
    struct tfs_dentry *dentry_cursor = inode->dentrys;
    int    cnt = 0;
    while (dentry_cursor)
    {
        if (dir == cnt)
        {
            return dentry_cursor;
        }
        cnt++;
        dentry_cursor = dentry_cursor->brother;
    }
    return NULL;
}
/**
 * @brief
 * path: /qwe/ad  total_lvl = 2,
 *      1) find /'s inode       lvl = 1
 *      2) find qwe's dentry
 *      3) find qwe's inode     lvl = 2
 *      4) find ad's dentry
 *
 * path: /qwe     total_lvl = 1,
 *      1) find /'s inode       lvl = 1
 *      2) find qwe's dentry
 *
 * @param path
 * @return struct tfs_inode*
 */
struct tfs_dentry *tfs_lookup(const char *path, boolean *is_find, boolean *is_root)
{
    struct tfs_dentry *dentry_cursor = tfs_super.root_dentry;
    struct tfs_dentry *dentry_ret = NULL;
    struct tfs_inode *inode;
    int   total_lvl = tfs_calc_lvl(path);
    int   lvl = 0;
    boolean is_hit;
    char *fname = NULL;
    char *path_cpy = (char *)malloc(sizeof(path));
    *is_root = FALSE;
    strcpy(path_cpy, path);

    if (total_lvl == 0)
    {                           /* 根目录 */
        *is_find = TRUE;
        *is_root = TRUE;
        dentry_ret = tfs_super.root_dentry;
    }
    fname = strtok(path_cpy, "/");
    while (fname)
    {
        lvl++;
        if (dentry_cursor->inode == NULL)
        {           /* Cache机制，如果没有可能是被换出了 */
            tfs_read_inode(dentry_cursor, dentry_cursor->ino);
        }
        /* 注意，这里有 bug，因为没考虑 dentry 块也会被换出 */
        /* 但是因为这里根本没有实现换出（假设内存大于 4MiB）所以没事 */

        inode = dentry_cursor->inode;

        if (TFS_IS_REG(inode) && lvl < total_lvl)
        {
            TFS_DBG("[%s] not a dir\n", __func__);
            dentry_ret = inode->dentry;
            break;
        }
        if (TFS_IS_DIR(inode))
        {
            dentry_cursor = inode->dentrys;
            is_hit = FALSE;

            while (dentry_cursor)
            {
                if (memcmp(dentry_cursor->fname, fname, strlen(fname)) == 0)
                {
                    is_hit = TRUE;
                    break;
                }
                dentry_cursor = dentry_cursor->brother; /* 遍历目录下的子文件 */
            }

            if (!is_hit)
            {
                *is_find = FALSE;
                TFS_DBG("[%s] not found %s\n", __func__, fname);
                dentry_ret = inode->dentry;
                break;
            }

            if (is_hit && lvl == total_lvl)
            {
                *is_find = TRUE;
                dentry_ret = dentry_cursor;
                break;
            }
        }
        fname = strtok(NULL, "/");
    }

    /* 如果对应 dentry 的 inode 还没读进来（因为 cache），则重新读 */
    if (dentry_ret->inode == NULL)
    {
        dentry_ret->inode = tfs_read_inode(dentry_ret, dentry_ret->ino);
    }

    return dentry_ret;
}
/**
 * @brief 挂载tfs, Layout 如下
 *
 * Layout
 * | Super | Inode Map | Data Map | Data |
 *
 *  BLK_SZ = 2 * IO_SZ
 *
 * 每个Inode占用一个Blk
 * @param options
 * @return int
 */
int tfs_mount(struct custom_options options)
{
    int                 ret = TFS_ERROR_NONE;
    int                 driver_fd;
    struct tfs_super_d  tfs_super_d;    /* 临时存放 driver 读出的超级块 */
    struct tfs_dentry *root_dentry;
    struct tfs_inode *root_inode;

    int                 super_blks;

    int                 inode_num;
    int                 data_num;
    int                 map_inode_blks;
    int                 map_data_blks;

    boolean             is_init = FALSE;

    tfs_super.is_mounted = FALSE;

    // driver_fd = open(options.device, O_RDWR);
    driver_fd = ddriver_open(options.device);

    if (driver_fd < 0)
    {
        return driver_fd;
    }

    tfs_super.driver_fd = driver_fd;
    ddriver_ioctl(TFS_DRIVER(), IOC_REQ_DEVICE_SIZE, &tfs_super.sz_disk);  /* 请求查看设备大小 4MB */
    ddriver_ioctl(TFS_DRIVER(), IOC_REQ_DEVICE_IO_SZ, &tfs_super.sz_io);    /* 请求设备IO大小 512B */
    tfs_super.sz_blk = tfs_super.sz_io * 2;                                 /* EXT2文件系统实际块大小 1024B */

    root_dentry = new_dentry("/", TFS_DIR);

    /* 读取 super 到临时空间 */
    if (tfs_driver_read(TFS_SUPER_OFS, (uint8_t *)(&tfs_super_d),
        sizeof(struct tfs_super_d)) != TFS_ERROR_NONE)
    {
        return -TFS_ERROR_IO;
    }
    /* 读取super */
    if (tfs_super_d.magic_num != TFS_MAGIC_NUM)
    {     /* 幻数无，重建整个磁盘 */
         /* 估算各部分大小 */
/* 规定各部分大小 */
        super_blks = TFS_SUPER_BLKS;
        map_inode_blks = TFS_MAP_INODE_BLKS;
        map_data_blks = TFS_MAP_DATA_BLKS;
        inode_num = TFS_INODE_BLKS;
        data_num = TFS_DATA_BLKS;

        /* 布局layout */
        tfs_super.max_ino = inode_num;
        tfs_super.max_data = data_num;

        tfs_super_d.magic_num = TFS_MAGIC_NUM;
        tfs_super_d.map_inode_offset = TFS_SUPER_OFS + TFS_BLKS_SZ(super_blks);
        tfs_super_d.map_data_offset = tfs_super_d.map_inode_offset + TFS_BLKS_SZ(map_inode_blks);

        tfs_super_d.inode_offset = tfs_super_d.map_data_offset + TFS_BLKS_SZ(map_data_blks);
        tfs_super_d.data_offset = tfs_super_d.inode_offset + TFS_BLKS_SZ(inode_num);

        tfs_super_d.map_inode_blks = map_inode_blks;
        tfs_super_d.map_data_blks = map_data_blks;

        tfs_super_d.sz_usage = 0;

        is_init = TRUE;
    }
    tfs_super.sz_usage = tfs_super_d.sz_usage;      /* 建立 in-memory 结构 */

    tfs_super.map_inode = (uint8_t *)malloc(TFS_BLKS_SZ(tfs_super_d.map_inode_blks));
    tfs_super.map_inode_blks = tfs_super_d.map_inode_blks;
    tfs_super.map_inode_offset = tfs_super_d.map_inode_offset;

    tfs_super.map_data = (uint8_t *)malloc(TFS_BLKS_SZ(tfs_super_d.map_data_blks));
    tfs_super.map_data_blks = tfs_super_d.map_data_blks;
    tfs_super.map_data_offset = tfs_super_d.map_data_offset;

    tfs_super.inode_offset = tfs_super_d.inode_offset;
    tfs_super.data_offset = tfs_super_d.data_offset;

    /* 读取两个位图到内存空间 */
    if (tfs_driver_read(tfs_super_d.map_inode_offset, (uint8_t *)(tfs_super.map_inode),
        TFS_BLKS_SZ(tfs_super_d.map_inode_blks)) != TFS_ERROR_NONE)
    {
        return -TFS_ERROR_IO;
    }
    if (tfs_driver_read(tfs_super_d.map_data_offset, (uint8_t *)(tfs_super.map_data),
        TFS_BLKS_SZ(tfs_super_d.map_data_blks)) != TFS_ERROR_NONE)
    {
        return -TFS_ERROR_IO;
    }

    if (is_init)
    {                                    /* 如果进行了重建，则分配根节点 */
        root_inode = tfs_alloc_inode(root_dentry);
        tfs_sync_inode(root_inode);  /* 将重建后的 根inode 写回磁盘 */
    }

    /* 如果磁盘有数据，则先读入根结点，其他暂时不读 (Cache) */
    root_inode = tfs_read_inode(root_dentry, TFS_ROOT_INO);
    root_dentry->inode = root_inode;
    tfs_super.root_dentry = root_dentry;
    tfs_super.is_mounted = TRUE;

    return ret;
}
/**
 * @brief
 *
 * @return int
 */
int tfs_umount()
{
    struct tfs_super_d  tfs_super_d;

    if (!tfs_super.is_mounted)
    {
        return TFS_ERROR_NONE;
    }

    tfs_sync_inode(tfs_super.root_dentry->inode);     /* 从根节点向下刷写节点 */

    tfs_super_d.magic_num = TFS_MAGIC_NUM;
    tfs_super_d.sz_usage = tfs_super.sz_usage;

    tfs_super_d.map_inode_blks = tfs_super.map_inode_blks;
    tfs_super_d.map_inode_offset = tfs_super.map_inode_offset;
    tfs_super_d.map_data_blks = tfs_super.map_data_blks;
    tfs_super_d.map_data_offset = tfs_super.map_data_offset;

    tfs_super_d.inode_offset = tfs_super.inode_offset;
    tfs_super_d.data_offset = tfs_super.data_offset;


    if (tfs_driver_write(TFS_SUPER_OFS, (uint8_t *)&tfs_super_d,
        sizeof(struct tfs_super_d)) != TFS_ERROR_NONE)
    {
        return -TFS_ERROR_IO;
    }

    if (tfs_driver_write(tfs_super_d.map_inode_offset, (uint8_t *)(tfs_super.map_inode),
        TFS_BLKS_SZ(tfs_super_d.map_inode_blks)) != TFS_ERROR_NONE)
    {
        return -TFS_ERROR_IO;
    }

    if (tfs_driver_write(tfs_super_d.map_data_offset, (uint8_t *)(tfs_super.map_data),
        TFS_BLKS_SZ(tfs_super_d.map_data_blks)) != TFS_ERROR_NONE)
    {
        return -TFS_ERROR_IO;
    }

    free(tfs_super.map_inode);
    free(tfs_super.map_data);
    ddriver_close(TFS_DRIVER());

    return TFS_ERROR_NONE;
}