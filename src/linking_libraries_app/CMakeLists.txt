SET(TARGET linking_libraries_app)
ADD_EXECUTABLE (${TARGET} test_cpp.cpp)
TARGET_LINK_LIBRARIES(${TARGET} dynamic_library static_library)
