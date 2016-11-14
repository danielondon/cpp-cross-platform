SET(TARGET dynamic_library)
add_library (${TARGET} SHARED singleton_container.h singleton_container.cpp)
