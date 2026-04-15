#include <xstdlib/xstring.h>

#include "../include/cmd_def.h"

void test_cmd_run(ReplContext *ctx,const XArray *cmd_args) {
    const XString *message = xarray_at(cmd_args, 0);
    fprintf(ctx->fadisk_ptr, "%s\n", message->c_str);
    fflush(ctx->fadisk_ptr);
}