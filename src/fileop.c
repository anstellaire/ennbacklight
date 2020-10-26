#include "fileop.h"
#include "assert.h"
#include "dowith.h"
#include "static.h"
#include "utils.h"

#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/*   DETAILS                                                                  */
/* -------------------------------------------------------------------------- */

static int cb_dir_print_lnkdir(DIR* dstream, void* unused) {
    ENN_ASSERT(dstream != NULL);

    struct dirent* dentry;
    while ((dentry = readdir(dstream)) != NULL) {
        if (is_dev_dname(dentry->d_name)) {
            fprintf(stdout, "%s\n", dentry->d_name);
        }
    }

    return 0;
}

static int cb_file_read_uint(FILE* fstream, void* uvalue) {
    ENN_ASSERT(fstream != NULL && uvalue != NULL);

    char rbuffer[11];
    size_t rbytes = fread(rbuffer, 1, 10, fstream);
    ENN_EXPECT(!ferror(fstream) && rbytes, strerror(EIO));

    rbuffer[rbytes] = '\0';

    int tmp;
    ENN_EXPECT(is_brightness_val(rbuffer, &tmp), strerror(EIO));

    *(unsigned*)uvalue = (unsigned)tmp;

    return 0;
}

static int cb_file_write_uint(FILE* fstream, void* uvalue) {
    ENN_ASSERT(fstream != NULL && uvalue != NULL);

    char wbuffer[11];
    size_t pchars = snprintf(wbuffer, 11, "%u", *(unsigned*)uvalue);
    ENN_EXPECT(pchars > 0 && pchars < 11, strerror(ERANGE));

    size_t wbytes = fwrite(wbuffer, 1, pchars, fstream);
    ENN_EXPECT(wbytes == pchars, strerror(EIO));

    return 0;
}

/* -------------------------------------------------------------------------- */
/*   INTERFACE                                                                */
/* -------------------------------------------------------------------------- */

int get_val(
    const char* dev_name, const char* opt_name, unsigned* brightness) {

    ENN_ASSERT(dev_name != NULL && opt_name != NULL && brightness != NULL);

    /* TODO: Pass through the error flag */
    int err = do_with_file(
        get_path(dev_name, opt_name), "r",
        cb_file_read_uint, brightness);
    ENN_EXPECT(!err, strerror(err));

    return 0;
}

int set_val(
    const char* dev_name, const char* opt_name, unsigned brightness) {

    ENN_ASSERT(dev_name != NULL && opt_name != NULL);

    /* TODO: Pass through the error flag */
    int err = do_with_file(
        get_path(dev_name, opt_name), "w",
        cb_file_write_uint, &brightness);
    ENN_EXPECT(!err, strerror(err));

    return 0;
}

int upd_val(
    const char* dev_name, const char* opt_name, unsigned* brightness,
    unsigned (*cback)(unsigned, void*), void* args) {

    ENN_ASSERT(dev_name != NULL && opt_name != NULL && brightness != NULL);

    /* TODO: Pass through the error flag */
    /* TODO: Change implementation */
    unsigned ubrightness;
    int err;

    err = get_val(dev_name, opt_name, &ubrightness);
    ENN_EXPECT(!err, strerror(err));

    ubrightness = cback(ubrightness, args);

    err = set_val(dev_name, opt_name, ubrightness);
    ENN_EXPECT(!err, strerror(err));

    *brightness = ubrightness;

    return 0;
}

int print_dev() {
    /* TODO: Pass through the error flag */
    int err = do_with_dir(
        get_class_path(),
        cb_dir_print_lnkdir, NULL);
    ENN_EXPECT(!err, strerror(err));

    return 0;
}
