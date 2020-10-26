#include "dowith.h"
#include "assert.h"

#include <errno.h>
#include <string.h>

int do_with_dir(
    const char* dpath,
    int (*cback)(DIR*, void*), void* args) {

    ENN_ASSERT(dpath != NULL && cback != NULL);

    DIR* dstream = opendir(dpath);
    ENN_EXPECT(dstream != NULL, strerror(errno));

    cback(dstream, args);

    int err = closedir(dstream);
    ENN_EXPECT(!err, strerror(errno));

    return 0;
}

int do_with_file(
    const char* fpath, const char* fmode,
    int (*cback)(FILE*, void*), void* args) {

    ENN_ASSERT(fpath != NULL && fmode != NULL && cback != NULL);

    FILE* fstream = fopen(fpath, fmode);
    ENN_EXPECT(fstream != NULL, strerror(errno));

    cback(fstream, args);

    int err = fclose(fstream);
    ENN_EXPECT(!err, strerror(errno));

    return 0;
}
