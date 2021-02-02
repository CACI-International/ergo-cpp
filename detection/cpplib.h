#include <cassert>
#if defined(__GLIBCXX__)
    "libstdc++"
#elif defined(_LIBCPP_VERSION)
    "libc++"
#elif defined(_MSC_VER)
    "msvc"
#else
    "unknown"
#endif
