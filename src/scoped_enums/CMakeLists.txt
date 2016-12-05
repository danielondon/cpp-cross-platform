SET(TARGET scoped_enums)
ADD_EXECUTABLE (${TARGET} scoped_enums.cpp)
TARGET_LINK_LIBRARIES(${TARGET} static_library)
