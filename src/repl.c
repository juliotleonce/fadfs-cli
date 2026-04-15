#include <xstdlib/xmemctl.h>
#include <xstdlib/xarray.h>
#include <xstdlib/xstring.h>
#include <xstdlib/xhashmap.h>
#include "../include/repl.h"

#include <string.h>

#include "../include/cmd_def.h"

static XString *get_command_line();

void repl_run(ReplContext *ctx) {
    bool running = true;
    XHashMap *repl_commands = xhashmap_new(sizeof(ReplCommand));
    xhashmap_put(repl_commands, "test", (ReplCommand []){ &test_cmd_run });

    while (running) {
        XMEM_SCOPE {
            const XString *command_line = get_command_line();
            const XArray *command_line_split = xstring_split(command_line, " ");
            const XString *command_name = xarray_at(command_line_split, 0);
            if (xstring_equal_c_str(command_name, "exit")) {
                fclose(ctx->fadisk_ptr);
                running = false;
            } else {
                const ReplCommand *command = (ReplCommand *) xhashmap_get(repl_commands, command_name->c_str);
                const XArray *cmd_args = xarray_slice(command_line_split, 1, command_line_split->length);
                if (command) (*command)(ctx, cmd_args);
                else printf("erreur: commande inconnue.\n");
            }
        }
    }
}


ReplContext *repl_init(const int argc, char **argv) {
    ReplContext *ctx = xmem_alloc(sizeof(ReplContext));

    XMEM_SCOPE {
        char *last_arg = argv[argc - 1];

        if (!last_arg || strcmp(last_arg, "-r") == 0) {
            printf("erreur: argument manquante.\n");
            exit(1);
        }

        const XString *filename = xstring_new(last_arg);

        if (!xstring_contains(filename, ".fadisk")) {
            printf("erreur: le fichier doit avoir l'extension .fadisk.\n");
            exit(1);
        }

        ctx->fadisk_ptr = fopen(filename->c_str, "a+");
    }

    if (ctx->fadisk_ptr == NULL) {
        printf("erreur: impossible d'ouvrir ou creer le fichier.\n");
        exit(1);
    }

    return ctx;
}

XString *get_command_line() {
    printf("fadfs > ");
    fflush(stdout);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((read = getline(&line, &len, stdin)) != -1) {
        if (line[read - 1] == '\n') { line[read - 1] = '\0'; }
        XString *command_line = xstring_new(line);
        free(line);
        return command_line;
    }

    return NULL;
}