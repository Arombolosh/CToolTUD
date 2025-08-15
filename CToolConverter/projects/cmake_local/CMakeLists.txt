# CMakeLists.txt file for CToolConverter

project( CToolConverter )

if (COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
  cmake_policy(SET CMP0020 NEW)
endif (COMMAND cmake_policy)

# add include directories
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../../src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/IBK/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/IBKMK/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/TiCPP/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/Nandrad/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/CToolImporter/src
	${Qt5Network_INCLUDE_DIRS}
	${Qt5Xml_INCLUDE_DIRS}
	#${Qt5Svg_INCLUDE_DIRS}
)

# collect a list of all source files
file( GLOB APP_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.cpp )

# collect a list of all header files (to be used in MOC compiler)
# file( GLOB APP_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.h )

# collect a list of all form files
# file( GLOB APP_UIS ${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.ui )

set( APP_SRCS 
	${APP_SRCS} 
)
#set( APP_HDRS 
#	${APP_HDRS} 
#)

# The Qt resource file (*.qrc)
#set( APP_QRCS	
#	${CMAKE_CURRENT_SOURCE_DIR}/../../resources/LabDataReport.qrc
#)

# set rc file
#set ( APP_WIN_RC
#	${CMAKE_CURRENT_SOURCE_DIR}/../../resources/LabDataReport.rc
#)

# run uic and moc compilers, add resources
#qt5_add_resources( APP_RC_SRCS ${APP_QRCS} )
#qt5_wrap_ui( APP_UI_SRCS ${APP_UIS} )
#qt5_wrap_cpp( APP_MOC_SRCS ${APP_HDRS} )

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

# build application executable for the different platforms
if( WIN32 )
	add_executable( ${PROJECT_NAME} WIN32 
		${APP_SRCS} #${APP_MOC_SRCS} ${APP_RC_SRCS} #${APP_UI_SRCS} #${APP_WIN_RC}
	)
	
endif( WIN32 ) 

if( UNIX )
	add_executable( ${PROJECT_NAME} 
		${APP_SRCS} #${APP_MOC_SRCS} ${APP_RC_SRCS} #${APP_UI_SRCS}
	)
endif( UNIX )


# -------------------------------------------------------------
# Support for build flags
# -------------------------------------------------------------
include( ../../../externals/IBK/projects/cmake_local/cmake_pri/CMakeLists.txt  )

# link against the dependent libraries
target_link_libraries( ${PROJECT_NAME} 
	IBK
	IBKMK
	Nandrad
	TiCPP
	CToolImporter
	${QT_LIBRARIES}
)


# Support for 'make install' on Unix/Linux (not on MacOS!)
if (UNIX AND NOT APPLE)

	# installation targets for Unix systems
	include(GNUInstallDirs)

	# executable -> /usr/bin
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin )

	# Databases
	# file( GLOB DB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../../data/*.xml )
	# install(FILES  ${DB_FILES}
	#		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/LabDataReport)

endif (UNIX AND NOT APPLE)
