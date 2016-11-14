SET(TARGET cpp_test)
ADD_EXECUTABLE (${TARGET} test_cpp.cpp)
TARGET_LINK_LIBRARIES(${TARGET} dynamic_library static_library)
