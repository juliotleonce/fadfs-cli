//
// Created by ajl420 on 4/15/26.
//

#ifndef FADFS_CLI_REPL_H
#define FADFS_CLI_REPL_H
#include <stdio.h>
#include <xstdlib/xarray.h>

typedef struct ReplContext {
    FILE *fadisk_ptr;
} ReplContext;

typedef void (*ReplCommand)(ReplContext *ctx, const XArray *cmd_args);

ReplContext *repl_init(int argc, char **argv);

void repl_run(ReplContext *ctx);

#endif //FADFS_CLI_REPL_H