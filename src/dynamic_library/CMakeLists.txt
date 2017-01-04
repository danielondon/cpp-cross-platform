SET(TARGET dynamic_library)

ADD_LIBRARY(${TARGET} SHARED singleton_container.h singleton_container.cpp)

# rt is necessary
# In POSIX systems, Boost.Interprocess uses pthread system calls to implement classes like mutexes, condition variables, etc...
# In some operating systems, these POSIX calls are implemented in separate libraries that are not automatically linked by the compiler.
# For example, in some Linux systems POSIX pthread functions are implemented in librt.a library,
# so you might need to add that library when linking an executable or shared library that uses Boost.Interprocess.
if (${UNIX})
    MESSAGE("Linking to RT")
    TARGET_LINK_LIBRARIES(${TARGET} rt)
endif(${UNIX})