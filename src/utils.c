#include "utils.h"
#include "assert.h"

#include <stdlib.h>

int is_dot_dotdot_dname(const char* dname) {
    ENN_ASSERT(dname != NULL);

    if (dname[dname[0] == '.'] && dname[1 + (dname[1] == '.')])
        return 0;
    return 1;
}

int is_hidden_dname(const char* dname) {
    ENN_ASSERT(dname != NULL);

    if (dname[0] != '.')
        return 0;
    return 1;
}

int is_separator(char chr, const char* seps, unsigned sep_size) {
    ENN_ASSERT(seps != NULL);

    for(unsigned i = 0; i < sep_size; ++i)
        if (chr == seps[i])
            return 1;
    return 0;
}

int is_dev_dname(const char* dname) {
    /* TODO: change implementation */
    return !is_hidden_dname(dname);
}

int is_brightness_val(const char* str, int* val) {
    ENN_ASSERT(str != NULL);

    char* convert_end;
    int tmp = strtol(str, &convert_end, 10);

    if (*str == '\0' || !is_separator(*convert_end, "\t\n\0", 3))
        return 0;

    if (val != NULL)
        *val = tmp;

    return 1;
}

int get_per_val(int abs_val, int max_abs_val) {
    return abs_val / (max_abs_val / 100);
}

int get_abs_val(int per_val, int max_abs_val) {
    return per_val * (max_abs_val / 100);
}

int bound_val(int val, int lbound, int ubound) {
    if (val > ubound)
        return ubound;
    if (val < lbound)
        return lbound;
    return val;
}
