# By default include the current directory (this is a bit counterintuitive to
# me and might not be necessary)
include_directories(.)

# Include our toplevel sources and headers
file (GLOB SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.c)
file (GLOB SOURCE_FILES_CPP RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.cpp)
list(APPEND SOURCE_FILES ${SOURCE_FILES_CPP})
file (GLOB HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.h)
file (GLOB HEADER_FILES_HPP RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.hpp)
list(APPEND HEADER_FILES ${HEADER_FILES_HPP})

# Define the list of subpathes to add to SOURCE_FILES and HEADER_FILES
set(SUBPATH gamestates; logger; menu; menu/elements; resources;)

# Every subpath ...
foreach(path ${SUBPATH})

    # ... gets added to the include directories
    include_directories(${path})

    # ... and it's files get added to SOURCE_FILES and HEADER_FILES
    file (GLOB SOURCE_FILES_SUB_CPP RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" ${path}/*.cpp)
    list(APPEND SOURCE_FILES ${SOURCE_FILES_SUB_CPP})

    file (GLOB SOURCE_FILES_SUB_C RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" ${path}/*.c)
    list(APPEND SOURCE_FILES ${SOURCE_FILES_SUB_C})

    file (GLOB HEADER_FILES_SUB_HPP RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" ${path}/*.hpp)
    list(APPEND HEADER_FILES ${HEADER_FILES_SUB_HPP})

    file (GLOB HEADER_FILES_SUB_H RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" ${path}/*.h)
    list(APPEND HEADER_FILES ${HEADER_FILES_SUB_H})

endforeach()

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDLMIXER_INCLUDE_DIR})
include_directories(${SDL2IMAGE_INCLUDE_DIR})

add_executable(tuxfootball ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries (tuxfootball ${SDL2_LIBRARY})
target_link_libraries (tuxfootball ${SDL2_MIXER_LIBRARIES})
target_link_libraries (tuxfootball ${SDL2_IMAGE_LIBRARIES})

install(TARGETS tuxfootball DESTINATION bin)
install(FILES SFont-README DESTINATION doc/tuxfootball)

