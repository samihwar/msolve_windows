#ifndef COMPAT_H
#define COMPAT_H

#include <stdlib.h>

#ifdef _WIN32
#include <malloc.h>
#include <errno.h>
#define posix_memalign(p, a, s) (*(p) = _aligned_malloc((s), (a)), *(p) ? 0 : errno)
#define aligned_free _aligned_free
#else
#define posix_memalign(p, a, s) ((*(p)) = aligned_alloc((a), (s)), (*(p)) ? 0 : errno)
#define aligned_free free
#endif

#endif // COMPAT_H
