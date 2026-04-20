//
// Created by ajl420 on 4/15/26.
//

#ifndef FADFS_CLI_REPL_H
#define FADFS_CLI_REPL_H
#include <xstdlib/xarray.h>
#include <xstdlib/xhashmap.h>

typedef struct ReplContext ReplContext;
typedef int (*FadFSMount) (const char *fadisk_path);
typedef int (*FadFSUnMount) (void);
typedef int (*CommandExecutor) (ReplContext *ctx, const char *command_name,const XArray *cmd_args);
typedef void (*ReplCommand) (ReplContext *ctx, const XArray *cmd_args);
typedef void (*AddCommand) (const ReplContext *ctx, const char *name, ReplCommand command);

typedef struct ReplContext {
    FadFSMount fadfs_mount;
    FadFSUnMount fadfs_unmount;
    CommandExecutor exec;
    XHashMap *repl_commands;
    AddCommand add_command;
    XArray *cli_args;
    bool running;
} ReplContext;

void repl_setup_cmd(const ReplContext *ctx);

void repl_run(ReplContext *ctx);

void repl_before_run(const ReplContext *ctx);

ReplContext *repl_init(int argc, char **argv);

#endif //FADFS_CLI_REPL_H