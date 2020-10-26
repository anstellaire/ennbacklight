#ifndef ENN_BACKLIGHT_API_H
#define ENN_BACKLIGHT_API_H

int get_val(
    const char* dev_name, const char* opt_name, unsigned* brightness);

int set_val(
    const char* dev_name, const char* opt_name, unsigned brightness);

int upd_val(
    const char* dev_name, const char* opt_name, unsigned* brightness,
    unsigned (*cback)(unsigned, void*), void* args);

int print_dev();

#endif /* ENN_BACKLIGHT_API_H */
