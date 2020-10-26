#include "static.h"
#include "assert.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/*   DETAILS                                                                  */
/* -------------------------------------------------------------------------- */

#ifndef NDEBUG
    static const char class_path[] = "dbg/backlight";
#else
    static const char class_path[] = "/sys/class/backlight";
#endif

/* string sizes without terminating null character */
#define CLASS_PATH_SIZE ((sizeof class_path) - 1)

/* class_path + dirent name + file name + slash/slash/null */
#define BR_PATH_SIZE (CLASS_PATH_SIZE + 255 + 255 + 3)

static char br_path[BR_PATH_SIZE] = {0};

static const char* version_message = "0.1.0";

static const char* help_message =
    "Usage: ennbacklight [command [arguments]]                        \n"
    "Commands:                                                        \n"
    "  devices             print a list of available devices          \n"
    "  get <dev>           get <dev> brightness value in percents     \n"
    "  set <dev>  <val>    set <dev> brightness value to <val>%       \n"
    "            +<val>    increase <dev> brightness value by +<val>% \n"
    "            -<val>    decrease <dev> brightness value by -<val>% \n"
    "  version             print program version information          \n"
    "  help                print this information                     \n";

/* -------------------------------------------------------------------------- */
/*   INTERFACE                                                                */
/* -------------------------------------------------------------------------- */

char* get_path(const char* dev_name, const char* br_name) {
    ENN_ASSERT(dev_name != NULL && br_name != NULL);

    int wbytes = snprintf(br_path, BR_PATH_SIZE,
        "%s/%s/%s", class_path, dev_name, br_name);
    ENN_EXPECT(wbytes > 0 && wbytes < BR_PATH_SIZE, strerror(EINVAL));

    return br_path;
}

const char* get_class_path() {
    return class_path;
}

const char* get_version() {
    return version_message;
}

const char* get_help() {
    return help_message;
}
