#####################################
# APPLICATIONS
#####################################

ADD_SUBDIRECTORY(quiz)
ADD_SUBDIRECTORY(auto_decltype)
ADD_SUBDIRECTORY(scoped_enums)
ADD_SUBDIRECTORY(uniform_initialization)
ADD_SUBDIRECTORY(null_ptr)
ADD_SUBDIRECTORY(range_based_loops)
ADD_SUBDIRECTORY(bool_pitfall)
ADD_SUBDIRECTORY(observer)
ADD_SUBDIRECTORY(trailing_return_types)
ADD_SUBDIRECTORY(threads)
ADD_SUBDIRECTORY(file_handler)
ADD_SUBDIRECTORY(static_assertion)
ADD_SUBDIRECTORY(override)
ADD_SUBDIRECTORY(lambda)
ADD_SUBDIRECTORY(smart_pointers)
ADD_SUBDIRECTORY(variadic_templates)

#####################################
# LIBRARIES
#####################################
IF(Boost_FOUND)
	ADD_SUBDIRECTORY(linking_libraries_app)
	ADD_SUBDIRECTORY(dynamic_library)
ELSE()
	MESSAGE("Skipping dynamic_library because Boost is not found")
ENDIF(Boost_FOUND)

ADD_SUBDIRECTORY(dynamic_library2)
ADD_SUBDIRECTORY(static_library)
