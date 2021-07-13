cmake_minimum_required(VERSION 3.5)

project(rasteredBeam LANGUAGES CXX)

#----------------------------------------------------------------------------
# Implement user-defined items here
# The generated shared library will be named lib$(PACKAGE).so/dylib 
set(PACKAGE frb)

# Sources 
set(src 
  FadcBPM.cxx
  FadcRaster.cxx
  FadcRasteredBeam.cxx
  )

# Headers
string(REPLACE .cxx .h headers "${src}")

# Sources live in dedicated src directory
list(TRANSFORM src PREPEND "${CMAKE_CURRENT_LIST_DIR}/src/")

# Headers live in dedicated include directory
list(TRANSFORM headers PREPEND "${CMAKE_CURRENT_LIST_DIR}/include/")

#----------------------------------------------------------------------------
# Find Podd, if necessary, and load its CMake module
set(ANALYZER_PATH "/adaqfs/home/a-onl/dflay/ANALYZER/install") 
if(NOT TARGET Podd::HallA)
  if(DEFINED ENV{ANALYZER})
    set(CMAKE_PREFIX_PATH "${ANALYZER_PATH}" "${CMAKE_PREFIX_PATH}")
  endif()

  find_package(Podd 1.7 REQUIRED)
endif()
include(PoddCMakeEnv)

set_diagnostic_flags(WALL WEXTRA)

#----------------------------------------------------------------------------
# Library
add_library(${PACKAGE} SHARED ${src} ${headers} ${PACKAGE}Dict.cxx)

target_compile_options(${PACKAGE} PRIVATE ${${PROJECT_NAME_UC}_DIAG_FLAGS_LIST})

target_include_directories(${PACKAGE}
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  )
target_link_libraries(${PACKAGE} PUBLIC ${ROOT_LIBRARIES})

include(GNUInstallDirs)

install(TARGETS ${PACKAGE}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#----------------------------------------------------------------------------
# ROOT dictionary
build_root_dictionary(${PACKAGE} ${headers}
  TARGETS ${PACKAGE}
  LINKDEF ${CMAKE_CURRENT_LIST_DIR}/include/${PACKAGE}_LinkDef.h
  )
