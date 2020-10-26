#ifndef ENN_BACKLIGHT_UTILS_H
#define ENN_BACKLIGHT_UTILS_H

int is_dot_dotdot_dname(const char* dname);

int is_hidden_dname(const char* dname);

int is_separator(char chr, const char* seps, unsigned sep_size);

int is_dev_dname(const char* dname);

int is_brightness_val(const char* str, int* val);

int get_per_val(int abs_val, int max_abs_val);

int get_abs_val(int per_val, int max_abs_val);

int bound_val(int val, int lbound, int ubound);

#endif /* ENN_BACKLIGHT_UTILS_H */
