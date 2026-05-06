//
// Created by ajl420 on 4/15/26.
//

#ifndef FADFS_CLI_TEST_CMD_H
#define FADFS_CLI_TEST_CMD_H
#include <xstdlib/xarray.h>

#include "repl.h"

int test_cmd_run(ReplContext *ctx, const XArray *cmd_args);
int ls_cmd_run(ReplContext *ctx, const XArray *cmd_args);
int stat_cmd_run(ReplContext *ctx,const XArray *cmd_args);
int sb_read_cmd_run(ReplContext *cmd_def, const XArray *cmd_args);

#endif //FADFS_CLI_TEST_CMD_H
