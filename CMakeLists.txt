cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

include(CTest)
enable_testing()

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c11 -O0 -g" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks" )

#
# set (SOURCE ${SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/src/shmupwarz.c )
# if (EXISTS ${CMAKE_SOURCE_DIR}/data )
#     add_subdirectory (data)
#     list ( APPEND RESOURCES ${resources_gresource_xml_C_FILE} )
# endif ()

add_subdirectory ( libs/cfw )
add_subdirectory ( libs/dna )



add_executable( ${PROJECT_NAME}  #src/main.c ${SOURCE} )
    src/main.c 
    src/script.c 
    src/method.c 
    src/io/File.c
    src/io/Path.c
    src/io/Stream.c
    src/math/Vec2.c
    src/math/Vec3.c
    src/math/Vec4.c
    src/math/Mat.c
    src/wren/path.c 
    ${SOURCE} )

include_directories( include )
include_directories( libs/cfw/include )
include_directories( libs/dna/include )
include_directories( libs/wren/include )
include_directories( external/stb )
# include_directories( external/linmath.h )
 
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/libs" )

add_subdirectory(tests)
target_link_libraries ( ${PROJECT_NAME} dl m BlocksRuntime wren corefw glfw GL )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

