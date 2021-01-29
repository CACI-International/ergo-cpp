#if defined(_WIN32)
    ^^windows^^
#elif defined(__linux__)
    ^^linux^^
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
    ^^ios-simulator^^
    #elif TARGET_OS_IPHONE
    ^^ios^^
    #elif TARGET_OS_MAC
    ^^macos^^
    #else
    ^^unknown^^
    #endif
#else
    ^^unknown^^
#endif
