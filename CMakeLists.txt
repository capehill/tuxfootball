# This is the minimum version I tested against. Might work with earlier, but
# currently untested
cmake_minimum_required(VERSION 2.8.6)

# By default look for modules (e.g. Findsdl2.cmake) in the cmake-folder
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Let's give our project a wonderful name
project(tuxfootball CXX C)
set(PROJECT_VERSION 0.3.90)
add_definitions( -DPACKAGE_NAME="${PROJECT_NAME}" -DPACKAGE_VERSION="${PROJECT_VERSION}" -DPACKAGE_DATA_DIR="${CMAKE_INSTALL_PREFIX}/share/tuxfootball" )

# Set global error and warning options (will likely fail on windows builds)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g -fno-omit-frame-pointer")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	message(STATUS "using Clang")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	message(STATUS "using GCC")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	message(STATUS "using Intel C++")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	message(STATUS "using Visual Studio C++")
else()
	message(STATUS "using unkown ${CMAKE_CXX_COMPILER_ID}")
endif()
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(Gettext)
if (GETTEXT_FOUND)
	add_definitions( -DENABLE_NLS=1 -DHAVE_GETTEXT=1 -DLOCALEDIR="${CMAKE_INSTALL_PREFIX}/share/locale" )
endif (GETTEXT_FOUND)
FIND_PACKAGE(GTest)

IF (GTEST_FOUND)
	ENABLE_TESTING()
	ADD_EXECUTABLE(point3dtest tests/point3dtest.cpp src/point3d.cpp src/matrix.cpp)
	TARGET_LINK_LIBRARIES(point3dtest gtest_main gtest boost_regex)
	ADD_TEST(NAME point3dtest WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COMMAND point3dtest)
ENDIF (GTEST_FOUND)

# Let's continue in the src-directory
add_subdirectory(src)
add_subdirectory(data)

# Build translations if gettext was found
if (GETTEXT_FOUND)
	add_subdirectory(po)
endif (GETTEXT_FOUND)

install(FILES tuxfootball.desktop DESTINATION share/applications/)
install(
	FILES
	icons/128x128/apps/tuxfootball.png
	icons/256x256/apps/tuxfootball.png
	icons/64x64/apps/tuxfootball.png
	icons/16x16/apps/tuxfootball.png
	icons/24x24/apps/tuxfootball.png
	icons/32x32/apps/tuxfootball.png
	icons/48x48/apps/tuxfootball.png
	icons/512x512/apps/tuxfootball.png
	DESTINATION
	share/icons/hicolor
)
install(FILES AUTHORS COPYING NEWS README DESTINATION doc/tuxfootball)
install(FILES tuxfootball.appdata.xml DESTINATION share/appdata)
