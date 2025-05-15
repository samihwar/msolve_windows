#ifndef SORT_R_H
#define SORT_R_H

#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>

    typedef int (*sort_r_compar)(const void *, const void *, void *);

    struct sort_r_data {
        void *arg;
        sort_r_compar compar;
    };

    static int __cdecl sort_r_thunk(void *thunk, const void *a, const void *b) {
        struct sort_r_data *data = (struct sort_r_data *)thunk;
        return data->compar(a, b, data->arg);
    }

    static void sort_r(void *base, size_t nmemb, size_t size,
                       void *arg, sort_r_compar compar) {
        struct sort_r_data data = { arg, compar };
        qsort_s(base, nmemb, size, sort_r_thunk, &data);
    }

#else
    // POSIX version
    typedef int (*sort_r_compar)(const void *, const void *, void *);

    static void sort_r(void *base, size_t nmemb, size_t size,
                       void *arg, sort_r_compar compar) {
        qsort_r(base, nmemb, size, compar, arg);
    }
#endif

// Now define macro to swap the 4th and 5th parameters
#define sort_r(base, nmemb, size, compar, arg) \
    sort_r(base, nmemb, size, arg, compar)

#endif // SORT_R_H
