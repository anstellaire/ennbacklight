#ifndef ENN_BACKLIGHT_ASSERT_H
#define ENN_BACKLIGHT_ASSERT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
  ENN_EXPECT:
    expects expression to evaluate to true,
    otherwise prints failure message and terminates
  ENN_ASSERT:
    expects expression to evaluate to true,
    otherwise prints debug information and aborts
*/

#ifndef NDEBUG

    #define ENN_EXPECT(expr, errmsg)                        \
    if (!(expr)) {                                          \
        fprintf(stderr, "ERROR %s:%d : %s\n",               \
                __FILE__, __LINE__, (errmsg));              \
        exit(EXIT_FAILURE);                                 \
    }

    #define ENN_ASSERT(expr)                                \
    if (!(expr)) {                                          \
        fprintf(stderr, "ASSERTION FAILED %s:%d : %s\n",    \
                __FILE__, __LINE__, "Invalid argument");    \
        abort();                                            \
    }

#else

    #define ENN_EXPECT(expr, errmsg)                        \
    if (!(expr)) {                                          \
        fprintf(stderr, "ERROR: %s\n", (errmsg));           \
        exit(EXIT_FAILURE);                                 \
    }

    #define ENN_ASSERT(expr) ((void)0)

#endif /* NDEBUG */

#endif /* ENN_BACKLIGHT_ASSERT_H */
