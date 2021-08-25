cmake_minimum_required ( VERSION 3.15 )

project ( MY_FLAT_Test LANGUAGES C CXX )

set ( PRJ_SRC_LIST )
set ( PRJ_LIBRARIES )
set ( PRJ_INCLUDE_DIRS )

#set ( GLFW_HOME "d:/software/GLFW" )
#set ( GLAD_HOME "d:/software/glad_old" )
#set ( SDL2_HOME "d:/software/SDL2" )
#set ( SDL1_HOME "d:/software/SDL" )
#set ( AntTweakBar_HOME "d:/software/AntTweakBar" )

set ( UTIL_HOME "${CMAKE_CURRENT_SOURCE_DIR}/util" )
set ( GLFW_HOME "${UTIL_HOME}/GLFW" )
set ( GLAD_HOME "${UTIL_HOME}/glad_old" )
set ( SDL1_HOME "${UTIL_HOME}/SDL" )
set ( AntTweakBar_HOME "${UTIL_HOME}/AntTweakBar" )
set ( AntTweakBar_INC "${AntTweakBar_HOME}/include" )
set ( AntTweakBar_LIB "${AntTweakBar_HOME}/lib/AntTweakBar64.lib" )

set ( SDL1_INC "${SDL1_HOME}/include" )
set ( SDL1_LIB "${SDL1_HOME}/lib/SDL.lib" )

set ( GLFW_INC "${GLFW_HOME}/include" )
set ( GLFW_LIB "${GLFW_HOME}/lib/glfw3dll.lib" )

set ( GLAD_INC "${GLAD_HOME}/include" )
set ( GLAD_SRC "${GLAD_HOME}/src" )

#message ( STATUS "GLAD_SRC = ${GLAD_SRC}" )

set ( glad_c_files "${GLAD_SRC}/glad.c" )

file ( GLOB root_header_files "${CMAKE_SOURCE_DIR}/*.h" )
file ( GLOB root_src_files "${CMAKE_SOURCE_DIR}/*.cpp" )
list ( APPEND root_src_files ${glad_c_files} )

message ( STATUS "root_header_files = ${root_header_files}" )
message ( STATUS "root_src_files = ${root_src_files}" )

list ( APPEND PRJ_INCLUDE_DIRS . )
list ( APPEND PRJ_INCLUDE_DIRS ${GLAD_INC} )
list ( APPEND PRJ_INCLUDE_DIRS ${GLFW_INC} )
list ( APPEND PRJ_INCLUDE_DIRS ${SDL1_INC} )
list ( APPEND PRJ_INCLUDE_DIRS ${AntTweakBar_INC} )

list ( APPEND PRJ_SRC_LIST ${root_src_files} ${root_header_files} )

list ( APPEND PRJ_LIBRARIES ${AntTweakBar_LIB} )
list ( APPEND PRJ_LIBRARIES ${GLFW_LIB} )
list ( APPEND PRJ_LIBRARIES ${SDL1_LIB} )

add_executable ( ${PROJECT_NAME} ${PRJ_SRC_LIST} )

target_include_directories ( ${PROJECT_NAME}
	PRIVATE 
        ${PRJ_INCLUDE_DIRS}
)

target_link_libraries ( ${PROJECT_NAME} 
    PRIVATE 
        ${PRJ_LIBRARIES}
)
