# This is the minimum version I tested against. Might work with earlier, but
# currently untested
cmake_minimum_required(VERSION 2.8.6)

# By default look for modules (e.g. Findsdl2.cmake) in the cmake-folder
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Let's give our project a wonderful name
project(tuxfootball CXX C)
add_definitions( -DPACKAGE_NAME="${PROJECT_NAME}" )

find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_mixer)
find_package(Gettext)
if (GETTEXT_FOUND)
  add_definitions( -DENABLE_NLS=1 -DHAVE_GETTEXT=1 -DLOCALEDIR="po" ) # TODO this is wrong
endif (GETTEXT_FOUND)

# Let's continue in the src-directory
add_subdirectory(src)
add_subdirectory(data)

# Build translations if gettext was found
if (GETTEXT_FOUND)
  add_subdirectory(po)
endif (GETTEXT_FOUND)

install(FILES tuxfootball.desktop DESTINATION share/applications/)
install(FILES tuxfootball.png DESTINATION share/icons/hicolor/128x128/apps)
install(FILES AUTHORS COPYING NEWS README DESTINATION doc/tuxfootball)
install(FILES tuxfootball.appdata.xml DESTINATION share/appdata)
