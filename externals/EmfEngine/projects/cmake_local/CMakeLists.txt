# CMakeLists.txt file for EmfEngine library

project( EmfEngine )

# collect a list of all source files
file( GLOB LIB_SRCS ${PROJECT_SOURCE_DIR}/../../src/*.cpp )

# collect a list of all header files (to be used in MOC compiler)
file( GLOB LIB_HDRS ${PROJECT_SOURCE_DIR}/../../src/*.h )

# run uic and moc compilers
if (Qt5Widgets_INCLUDE_DIRS)
  
	include_directories(
		${Qt5Widgets_INCLUDE_DIRS}
	)

	qt5_wrap_cpp( LIB_MOC_SRCS ${LIB_HDRS} )

else (Qt5Widgets_INCLUDE_DIRS)

	qt4_wrap_cpp( LIB_MOC_SRCS ${LIB_HDRS} )

endif (Qt5Widgets_INCLUDE_DIRS)

# add build target for library
add_library( ${PROJECT_NAME} STATIC 
	${LIB_SRCS}  
	${LIB_MOC_SRCS}  
)

