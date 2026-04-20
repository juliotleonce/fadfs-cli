#include "include/repl.h"
#include <xstdlib/xmemctl.h>

int main(int argc, char** argv) {
    ReplContext *ctx = repl_init(argc, argv);
    repl_setup_cmd(ctx);
    repl_before_run(ctx);
    repl_run(ctx);
    xmem_reset();
    return 0;
}