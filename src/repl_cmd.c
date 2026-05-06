#include <error.h>
#include <stdio.h>
#include <xstdlib/xstring.h>
#include <fadfs_core/api.h>

#include "../include/cmd_def.h"

int test_cmd_run(ReplContext *ctx,const XArray *cmd_args) {
    const XString *message = xarray_at(cmd_args, 0);
    printf("%s\n", message->c_str);
    return NO_ERROR;
}

int ls_cmd_run(ReplContext *ctx,const XArray *cmd_args) {
    if (cmd_args->length == 0) {
        printf("erreur: argument manquant.\n");
        return NO_ERROR;
    }

    const XString *path = xarray_at(cmd_args, 0);
    fadfs_file_t dir;
    const int res = fadfs_opendir(path->c_str, &dir);
    PRINT_IF_ERROR(res, "erreur: impossible d'ouvrir le dossier.\n");

    fadfs_dirent_t entry;
    int read_dir_res = fadfs_readdir(&dir, &entry);
    while (read_dir_res != -END_OF_FILE) {
        PRINT_IF_ERROR(read_dir_res, "erreur: impossible de lire le dossier.\n");
        printf("name: %s, ino: %d\n", entry.name, entry.ino);
        read_dir_res = fadfs_readdir(&dir, &entry);
    }

    return NO_ERROR;
}

int stat_cmd_run(ReplContext *ctx,const XArray *cmd_args) {
    if (cmd_args->length == 0) {
        printf("erreur: argument manquant.\n");
        return NO_ERROR;
    }

    const XString *path = xarray_at(cmd_args, 0);
    fadfs_stat_t stat;
    const int stat_resp = fadfs_stat(path->c_str, &stat);
    if (stat_resp == NO_ERROR) {
        printf("file name: %s \n", path->c_str);
        printf("ino: %d \n", stat.ino);
        printf("type: %c \n", stat.type == FADFS_TYPE_FILE ? 'f' : 'd');
        printf("size: %d \n", stat.size);
    } else {
        PRINT_IF_ERROR(stat_resp, "erreur: impossible de lire le stat du fichier.\n");
    }
    return NO_ERROR;
}

int sb_read_cmd_run(ReplContext *cmd_def, const XArray *cmd_args) {
    fadfs_superblock_t sb;
    fadfs_read_superblock(&sb);

    printf("Superblock: \n");
    printf("block size: %d\n", sb.block_size);
    printf("inode size: %d\n", sb.inode_size);
    printf("root ino: %d \n", sb.root_ino);
    printf("block count: %d \n", sb.block_count);
    return NO_ERROR;
}
