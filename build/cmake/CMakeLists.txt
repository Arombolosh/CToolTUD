# CMakeLists.txt file for ClimateGenerator and dependent libraries

# Require a fairly recent cmake version
cmake_minimum_required( VERSION 2.8...3.10 )

# The project name
project( CToolConverter )

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Concurrent REQUIRED) 
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
#find_package(QuaZipQt5 REQUIRED)

# automatically add CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_BINARY_DIR to the include directories in every processed CMakeLists.txt
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# -------------------------------------------------------------
# Support for build flags
# -------------------------------------------------------------
include( ../../externals/IBK/projects/cmake_local/cmake_pri/CMakeLists.txt  )

# Include subdirectories
# NandradCodeGenerator
add_subdirectory( ../../NandradCodeGenerator/projects/cmake_local NandradCodeGenerator )

# Libs
add_subdirectory(../../externals/IBK/projects/cmake_local IBK)
add_subdirectory(../../externals/QtExt/projects/cmake_local QtExt)
add_subdirectory(../../externals/IBKMK/projects/cmake_local IBKMK)
add_subdirectory(../../externals/TiCPP/projects/cmake_local TiCPP)
add_subdirectory(../../externals/sundials/src sundials)
add_subdirectory(../../externals/SuiteSparse/projects/cmake_local SuiteSparse)
add_subdirectory(../../externals/CToolImporter/projects/cmake_local CToolImporter)
add_subdirectory(../../externals/Nandrad/projects/cmake_local Nandrad)

# CToolConverter
add_subdirectory(../../CToolConverter/projects/cmake_local CToolConverter)


# Set dependencies
add_dependencies(IBKMK IBK)
add_dependencies(TiCPP IBK)
add_dependencies(QtExt IBK IBKMK)
add_dependencies(NandradCodeGenerator QtExt)
add_dependencies(Nandrad IBK TiCPP IBKMK NandradCodeGenerator)
add_dependencies(CToolImporter IBK IBKMK Nandrad TiCPP)
add_dependencies(CToolConverter IBK IBKMK Nandrad TiCPP CToolImporter)
