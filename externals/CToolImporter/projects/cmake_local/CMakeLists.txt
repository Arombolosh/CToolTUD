# CMakeLists.txt file for QtExt library

project( CToolImporter )

# collect a list of all source files
file( GLOB LIB_SRCS ${PROJECT_SOURCE_DIR}/../../src/*.cpp )

# collect a list of all header files (to be used in MOC compiler)
file( GLOB LIB_HDRS ${PROJECT_SOURCE_DIR}/../../src/*.h )

# collect a list of all form files
# file( GLOB LIB_UIS ${PROJECT_SOURCE_DIR}/../../src/*.ui )

# set resource files
# set( LIB_QRCS ${PROJECT_SOURCE_DIR}/../../resources/CToolImporter.qrc )

# generate list of all required QT_LIBRARIES
set ( QT_LIBRARIES 
	Qt5::Svg
	Qt5::Core
	Qt5::Widgets
	Qt5::PrintSupport
	Qt5::Xml
	Qt5::Network
	Qt5::Gui
)

# -------------------------------------------------------------
# Support for build flags
# -------------------------------------------------------------
include( ../../../IBK/projects/cmake_local/cmake_pri/CMakeLists.txt  )

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../../src			# needed so that ui-generated header files find our own headers
	${CMAKE_CURRENT_SOURCE_DIR}/../../../IBK/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../IBKMK/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Nandrad/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../TiCPPP/src
	#${Qt5Widgets_INCLUDE_DIRS}
	#${Qt5PrintSupport_INCLUDE_DIRS}
	${Qt5Network_INCLUDE_DIRS}
	#${Qt5Svg_INCLUDE_DIRS}
)

# run uic and moc compilers
#qt5_add_resources( LIB_RC_SRCS ${LIB_QRCS} )
#qt5_wrap_ui( LIB_UI_SRCS ${LIB_UIS} )
qt5_wrap_cpp( LIB_MOC_SRCS ${LIB_HDRS} )

# add build target for library
add_library( ${PROJECT_NAME} STATIC
	${LIB_SRCS}
	${LIB_MOC_SRCS}
	#${LIB_UI_SRCS}
	#${LIB_RC_SRCS}
)

# link against the dependent libraries
target_link_libraries( ${PROJECT_NAME}  PUBLIC
	Nandrad
	TiCPP
	IBK
	IBKMK
	${QT_LIBRARIES}
)
