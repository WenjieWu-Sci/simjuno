cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(simjuno)

option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

include(${Geant4_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS} ${Geant4_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include)

# We presume the existence of three directories
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE macros RELATIVE ${PROJECT_SOURCE_DIR} macros/*.mac)

# Enable macros for out-of-source build
foreach(_file ${macros})
  configure_file(
    ${_file}
    ${PROJECT_BINARY_DIR}/${_file}
    COPYONLY
    )
endforeach()

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/RecTimeLikeAlg/include")
add_subdirectory(RecTimeLikeAlg)

add_executable(simjuno main.cc ${sources} ${headers})
target_link_libraries(simjuno ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} RecTimeLikeAlg)

install(TARGETS simjuno DESTINATION bin)
