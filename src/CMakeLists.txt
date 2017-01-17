#####################################
# APPLICATIONS
#####################################

ADD_SUBDIRECTORY(app)
ADD_SUBDIRECTORY(quiz)
ADD_SUBDIRECTORY(scoped_enums)
ADD_SUBDIRECTORY(uniform_initialization)
ADD_SUBDIRECTORY(null_ptr)
ADD_SUBDIRECTORY(range_based_loops)
ADD_SUBDIRECTORY(bool_pitfall)
ADD_SUBDIRECTORY(observer)
if(COMPILER_SUPPORTS_CXX14)
  ADD_SUBDIRECTORY(auto_decltype)
endif()

#####################################
# LIBRARIES
#####################################
ADD_SUBDIRECTORY(dynamic_library)
ADD_SUBDIRECTORY(dynamic_library2)
ADD_SUBDIRECTORY(static_library)
