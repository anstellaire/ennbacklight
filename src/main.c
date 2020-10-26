#include "fileop.h"
#include "assert.h"
#include "dowith.h"
#include "static.h"
#include "utils.h"

#include <errno.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/*   MAIN                                                                     */
/* -------------------------------------------------------------------------- */

#define CMD_DEV 0
#define CMD_GET 1
#define CMD_SET 2
#define CMD_VER 3
#define CMD_HLP 4

static const char* cmds[] = {
    [CMD_DEV] =  "devices",
    [CMD_GET] =  "get",
    [CMD_SET] =  "set",
    [CMD_VER] =  "version",
    [CMD_HLP] =  "help",
    NULL,
};

static int parse_cmd(const char** cmds, const char* cmd) {
    ENN_ASSERT(cmds != NULL);

    int i = 0;

    for (; cmds[i] != NULL; ++i)
        if (cmd && strcmp(cmd, cmds[i]) == 0)
            return i;

    return i;
}

typedef struct _upd_val_cback_arg {
    int rel_val;
    int min_val;
    int max_val;
} upd_cb_arg_t;

unsigned upd_cb(unsigned old_val, void* raw_args) {
    upd_cb_arg_t* args = (upd_cb_arg_t*)raw_args;
    return bound_val(old_val + args->rel_val, args->min_val, args->max_val);
}

static void parse_args(int argc, char** argv) {
    const char* max_br_fname = "max_brightness";
    const char* br_fname = "brightness";
    unsigned max_br_val;
    unsigned br_val;
    int par_br_val;
    int err;

    switch (parse_cmd(cmds, argv[1])) {
        case CMD_DEV:
            ENN_EXPECT(argc == 2, strerror(EINVAL));

            print_dev();
            break;
        case CMD_GET:
            ENN_EXPECT(argc == 3 && is_dev_dname(argv[2]), strerror(EINVAL));

            err = get_val(argv[2], br_fname, &br_val);
            ENN_EXPECT(!err, strerror(err));

            err = get_val(argv[2], max_br_fname, &max_br_val);
            ENN_EXPECT(!err, strerror(err));

            printf("%i", get_per_val(br_val, max_br_val));
            break;
        case CMD_SET:
            ENN_EXPECT(argc == 4 && is_dev_dname(argv[2])
                && is_brightness_val(argv[3], &par_br_val),
                strerror(EINVAL));

            err = get_val(argv[2], max_br_fname, &max_br_val);
            ENN_EXPECT(!err, strerror(err));

            par_br_val = get_abs_val(
                bound_val(par_br_val, -100, 100), max_br_val);

            if (argv[3][0] == '+' || argv[3][0] == '-') {
                upd_cb_arg_t upd_cb_arg = { par_br_val, 0, max_br_val };
                err = upd_val(argv[2], br_fname, &br_val, &upd_cb, &upd_cb_arg);
                ENN_EXPECT(!err, strerror(err));
            } else {
                br_val = par_br_val;
                err = set_val(argv[2], br_fname, br_val);
                ENN_EXPECT(!err, strerror(err));
            }

            printf("%i", get_per_val(br_val, max_br_val));
            break;
        case CMD_VER:
            printf("%s\n", get_version());
            break;
        case CMD_HLP:
        default:
            printf("%s\n", get_help());
            break;
    }
}

int main(int argc, char** argv) {
    parse_args(argc, argv);
    return EXIT_SUCCESS;
}
