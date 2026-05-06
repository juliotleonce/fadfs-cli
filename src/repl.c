#include <xstdlib/xmemctl.h>
#include <xstdlib/xarray.h>
#include <xstdlib/xstring.h>
#include <xstdlib/xhashmap.h>
#include <xstdlib/xio_utils.h>

#include <fadfs_core/api.h>
#include <fadfs_core/error.h>

#include <stdio.h>

#include "../include/cmd_def.h"
#include "../include/repl.h"

static int command_exec(ReplContext *ctx, const char *command_name,const XArray *cmd_args);
static void add_command(const ReplContext *ctx, const char *name, ReplCommand command);
static void mkfs_process(const char *filename);

void repl_setup_cmd(const ReplContext *ctx) {
    ctx->add_command(ctx, "test", &test_cmd_run);
    ctx->add_command(ctx, "ls", &ls_cmd_run);
    ctx->add_command(ctx, "stat", &stat_cmd_run);
    ctx->add_command(ctx, "sb", &sb_read_cmd_run);
}

void repl_run(ReplContext *ctx) {

    while (ctx->running) {
        XMEM_SCOPE {
            const XString *command_line = xio_read_console_line("fadfs > ");
            const XArray *command_line_split = xstring_split(command_line, " ");
            const XString *command_name = xarray_at(command_line_split,0);
            const XArray *cmd_args = xarray_slice(command_line_split, 1, command_line_split->length);

            if (xstring_equal_c_str(command_name, "exit")) {
                ctx->fadfs_unmount();
                ctx->running = false;
            } else {
                ctx->exec(ctx, command_name->c_str, cmd_args);
            }
        }
    }
}

void repl_before_run(const ReplContext *ctx) {
    const XString *filename = xarray_at(ctx->cli_args, ctx->cli_args->length - 1);

    if (ctx->cli_args->length == 1) {
        printf("erreur: argument manquante.\n");
        exit(1);
    }

    if (!xstring_contains(filename, ".fadisk")) {
        printf("erreur: le fichier doit avoir l'extension .fadisk.\n");
        exit(1);
    }

    const int mount_res = ctx->fadfs_mount(filename->c_str);
    if (mount_res == -INVALID_FILE_SYSTEM) {
        mkfs_process(filename->c_str);
        EXIT_ON_ERROR(ctx->fadfs_mount(filename->c_str));
    } else {
        EXIT_ON_ERROR(mount_res);
    }
}


ReplContext *repl_init(const int argc, char **argv) {
    ReplContext *ctx = xmem_alloc(sizeof(ReplContext));
    ctx->repl_commands = xhashmap_new(sizeof(ReplCommand));
    ctx->cli_args = xarray_new(sizeof(XString));
    ctx->fadfs_mount = &fadfs_mount;
    ctx->fadfs_unmount = &fadfs_umount;
    ctx->exec = &command_exec;
    ctx->add_command = &add_command;
    ctx->running = true;

    for (int i = 0; i < argc; i++)
        xarray_push(ctx->cli_args, xstring_new(argv[i]));

    return ctx;
}

int command_exec(ReplContext *ctx, const char *command_name,const XArray *cmd_args) {
    const ReplCommand *command =
        (ReplCommand *) xhashmap_get(ctx->repl_commands, command_name);
    if (command) (*command)(ctx, cmd_args);
    else printf("erreur: commande inconnue.\n");
    return 0;
}

void add_command(const ReplContext *ctx, const char *name, const ReplCommand command) {
    xhashmap_put(ctx->repl_commands, name, (ReplCommand[]){ command });
}

void mkfs_process(const char *filename) {
    bool is_valid_input = false;
    while (!is_valid_input) {
        char *endptr;
        const char *prompt = "Combien d'espace voulez-vous allouer? (en Mo) : ";
        const XString *response = xio_read_console_line(prompt);
        const unsigned long size = strtol(response->c_str, &endptr, 10);

        if (endptr == response->c_str || *endptr != '\0') {
            printf("erreur: valeur invalide.\n");
        } else {
            const unsigned long size_in_bytes = size << 20;
            const int mkfs_res = fadfs_mkfs(filename, size_in_bytes);
            if (mkfs_res != NO_ERROR)
                printf("errno: %d\n", mkfs_res);
            else is_valid_input = true;
        }
    }
}
