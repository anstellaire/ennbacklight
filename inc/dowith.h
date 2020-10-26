#ifndef ENN_BACKLIGHT_DOWITH_H
#define ENN_BACKLIGHT_DOWITH_H

#include <dirent.h>
#include <stdio.h>

int do_with_dir(
    const char* dpath,
    int (*cback)(DIR*, void*), void* args);

int do_with_file(
    const char* fpath, const char* fmode,
    int (*cback)(FILE*, void*), void* args);

#endif /* ENN_BACKLIGHT_DOWITH_H */
