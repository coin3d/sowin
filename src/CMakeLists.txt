configure_file(config.h.cmake.in config.h)

# Processing files and headers common to all SoGui libraries
# This is pulled from the subrepo SoGui.
add_subdirectory(Inventor/${Gui}/common)

file(GLOB_RECURSE COMMON_HDRS ${CMAKE_CURRENT_BINARY_DIR}/*.h)
file(GLOB_RECURSE COMMON_SRCS ${CMAKE_CURRENT_BINARY_DIR}/*.cpp)

set(HDRS
  Inventor/${Gui}/So${Gui}Def.h
  Inventor/${Gui}/So${Gui}Res.h
  Inventor/${Gui}/So${Gui}Resource.h
  Inventor/${Gui}/So${Gui}BeginStrict.h
  Inventor/${Gui}/So${Gui}EndStrict.h
  Inventor/${Gui}/So${Gui}ComponentP.h
  Inventor/${Gui}/So${Gui}GLWidgetP.h
  Inventor/${Gui}/Win32API.h
  Inventor/${Gui}/devices/So${Gui}DeviceP.h
  Inventor/${Gui}/devices/So${Gui}SpacenavDevice.h
  Inventor/${Gui}/viewers/So${Gui}ExaminerViewerP.h
  Inventor/${Gui}/viewers/So${Gui}FullViewerP.h
  Inventor/${Gui}/viewers/So${Gui}PlaneViewerP.h
  Inventor/${Gui}/viewers/So${Gui}ViewerResource.h
  Inventor/${Gui}/widgets/So${Gui}BitmapButton.h
  Inventor/${Gui}/widgets/So${Gui}ThumbWheel.h
  Inventor/${Gui}/widgets/${Gui}NativePopupMenu.h
)

set(SRCS
  Inventor/${Gui}/So${Gui}.cpp
  Inventor/${Gui}/So${Gui}Component.cpp
  Inventor/${Gui}/So${Gui}GLWidget.cpp
  #Inventor/${Gui}/So${Gui}MaterialList.cpp
  Inventor/${Gui}/Win32API.cpp
  Inventor/${Gui}/devices/So${Gui}Device.cpp
  Inventor/${Gui}/devices/So${Gui}InputFocus.cpp
  Inventor/${Gui}/devices/So${Gui}Keyboard.cpp
  Inventor/${Gui}/devices/So${Gui}Mouse.cpp
  Inventor/${Gui}/devices/So${Gui}SpacenavDevice.cpp
  Inventor/${Gui}/viewers/ExaminerViewer.cpp
  Inventor/${Gui}/viewers/FullViewer.cpp
  Inventor/${Gui}/viewers/PlaneViewer.cpp
  #Inventor/${Gui}/viewers/WalkViewer.cpp
  Inventor/${Gui}/widgets/So${Gui}BitmapButton.cpp
  Inventor/${Gui}/widgets/So${Gui}ThumbWheel.cpp
  Inventor/${Gui}/widgets/${Gui}NativePopupMenu.cpp
)

file(GLOB_RECURSE COMMON_RESOURCES ${CMAKE_BINARY_DIR}/data/materials/*.h)

# Create the library target
if(SO${GUI}_BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME} SHARED ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${COMMON_RESOURCES})
else()
  add_library(${PROJECT_NAME} STATIC ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${COMMON_RESOURCES})
endif()

if(WIN32 AND NOT MINGW)
  set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${SO${GUI}_SO_VERSION})
else()
  set_target_properties(${PROJECT_NAME} PROPERTIES VERSION "${SO${GUI}_SO_VERSION}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}" SOVERSION ${SO${GUI}_SO_VERSION})
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H SO${GUI}_INTERNAL SO${GUI}_DEBUG=$<CONFIG:Debug>)

if(WIN32)
  if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_NONSTDC_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _USE_MATH_DEFINES)
  endif()
  if(SO${GUI}_BUILD_SHARED_LIBS)
    configure_file(${PROJECT_NAME}.rc.cmake.in ${PROJECT_NAME}.rc)
    target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc")
    target_compile_definitions(${PROJECT_NAME} PRIVATE SO${GUI}_MAKE_DLL INTERFACE SO${GUI}_DLL)
  else()
    target_compile_definitions(${PROJECT_NAME} INTERFACE SO${GUI}_NOT_DLL)
    if(MSVC)
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")                       # Override default /Zi to embed
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Z7")     # debugging info in the .lib.
    endif()
  endif()
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC Coin::Coin ${OPENGL_LIBRARY})

# Add a target to generate API documentation with Doxygen
if(SO${GUI}_BUILD_DOCUMENTATION)
  find_package(Doxygen)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  if(NOT "${Coin_DOC_DIR}" STREQUAL "")
    get_filename_component(_coin_versioned_dir ${Coin_DOC_DIR} NAME)
    set(DOXYGEN_TAGFILES "${Coin_DOC_DIR}/html/Coin.tag=../../${_coin_versioned_dir}/html")
  endif()

# ############################################################################
# Setup documentation options
# ############################################################################
  set(GENERATE_HTMLHELP NO)
  set(DOXYGEN_GENERATE_MAN NO)
  set(GENERATE_QHP NO)
  set(GENERATE_TREEVIEW YES)
  set(HHC_PROGRAM)
  if(WIN32)
    if(SO${GUI}_BUILD_DOC_CHM)
      find_program(HHC_PROGRAM NAMES hhc.exe PATHS "C:/Program Files/HTML Help Workshop" "C:/Program Files (x86)/HTML Help Workshop" DOC "HTML Help Compiler program")
      if(NOT HHC_PROGRAM)
        message(FATAL_ERROR "Missing program HTML Help Compiler")
      else()
        set(GENERATE_HTMLHELP YES)
        set(GENERATE_TREEVIEW NO)
        mark_as_advanced(HHC_PROGRAM)
      endif()
    endif()
  else()
    if(SO${GUI}_BUILD_DOC_MAN)
      set(DOXYGEN_GENERATE_MAN YES)
    endif()
  endif()
  if(SO${GUI}_BUILD_DOC_QTHELP)
    find_program(QHG_LOCATION NAMES qhelpgenerator qhelpgenerator-qt5 DOC "Qt qhelpgenerator")
    if(NOT QHG_LOCATION)
      message(FATAL_ERROR "Missing program Qt qhelpgenerator")
    else()
      set(GENERATE_QHP YES)
      mark_as_advanced(QHG_LOCATION)
    endif()
  endif()

  set(DOXYGEN_INTERNAL_DOCS NO)
  set(DOXYGEN_EXTRACT_PRIVATE NO)
  set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
  set(DOXYGEN_EXCLUDE)

  set(DOXYFILE "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
  set(DOXYGEN_OUTPUT "${CMAKE_BINARY_DIR}/html/index.html")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Inventor/${Gui}/common/sogui.doxygen.cmake.in" ${DOXYFILE} @ONLY)

# ############################################################################
# Setup documentation targets
# ############################################################################
  add_custom_command(
    OUTPUT ${DOXYGEN_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E echo_append "Generating API documentation with Doxygen "
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
    COMMAND ${CMAKE_COMMAND} -E echo "done."
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS ${DOXYFILE}
  )
  add_custom_target(documentation ALL DEPENDS ${DOXYGEN_OUTPUT})

# ############################################################################
# Install built documentation files
# ############################################################################
  install(DIRECTORY "${CMAKE_BINARY_DIR}/html" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation REGEX ".*\\.(chm|qch)" EXCLUDE)
  if(GENERATE_HTMLHELP)
    install(FILES "${CMAKE_BINARY_DIR}/html/${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.chm" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation)
  endif()
  if(GENERATE_QHP)
    install(FILES "${CMAKE_BINARY_DIR}/html/${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.qch" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation)
  endif()
  if(DOXYGEN_GENERATE_MAN)
    install(DIRECTORY "${CMAKE_BINARY_DIR}/man/man3" DESTINATION ${CMAKE_INSTALL_MANDIR} COMPONENT documentation)
  endif()
endif()

# Add a target to generate new modern API documentation with Doxygen
if(SO${GUI}_BUILD_AWESOME_DOCUMENTATION)
  find_package(Doxygen)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  if(NOT "${Coin_DOC_DIR}" STREQUAL "")
    get_filename_component(_coin_versioned_dir ${Coin_DOC_DIR} NAME)
    set(DOXYGEN_TAGFILES "${Coin_DOC_DIR}/html/Coin.tag=../../${_coin_versioned_dir}/html")
  endif()

# ############################################################################
# Setup documentation options
# ############################################################################
  set(GENERATE_HTMLHELP NO)
  set(DOXYGEN_GENERATE_MAN NO)
  set(GENERATE_QHP NO)
  set(GENERATE_TREEVIEW YES)
  set(DOXYGEN_INTERNAL_DOCS NO)
  set(DOXYGEN_EXTRACT_PRIVATE NO)
  set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
  set(DOXYGEN_EXCLUDE)
  set(GITHUB_LINK "https://github.com/coin3d/so${gui}")

  set(DOXYFILE_AWESOME "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile_awesome")
  set(HTML_HEADER_AWESOME "${CMAKE_BINARY_DIR}/header_awesome.html")
  set(DOXYGEN_OUTPUT_AWESOME "${CMAKE_BINARY_DIR}/html_awesome/index.html")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Inventor/${Gui}/common/sogui.doxygen.awesome.cmake.in" ${DOXYFILE_AWESOME} @ONLY)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Inventor/${Gui}/common/docs/doxygen-awesome/doxygen-custom/header.html.cmake.in" ${HTML_HEADER_AWESOME} @ONLY)

# ############################################################################
# Setup documentation targets
# ############################################################################
  add_custom_command(
    OUTPUT ${DOXYGEN_OUTPUT_AWESOME}
    COMMAND ${CMAKE_COMMAND} -E echo_append "Generating modern API documentation with Doxygen "
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_AWESOME}
    COMMAND ${CMAKE_COMMAND} -E echo "done."
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS ${DOXYFILE_AWESOME}
  )
  add_custom_target(documentation_awesome ALL DEPENDS ${DOXYGEN_OUTPUT_AWESOME})

# ############################################################################
# Install built documentation files
# ############################################################################
  install(DIRECTORY "${CMAKE_BINARY_DIR}/html_awesome" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation REGEX ".*\\.(chm|qch)" EXCLUDE)
endif()

# ############################################################################
# Installation headers
# ############################################################################

set(INST_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Basic.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}ColorEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Component.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Cursor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}GLWidget.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}MaterialEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Object.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}RenderArea.h"
)

set(INST_DEVICES_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}Device.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}InputFocus.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}Keyboard.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}Mouse.h"
)

set(INST_EDITORS_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/editors/So${Gui}ColorEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/editors/So${Gui}MaterialEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}SpacenavDevice.h"
)

set(INST_NODES_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/nodes/SoGuiColorEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/nodes/SoGuiMaterialEditor.h"
)

set(INST_VIEWERS_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}ConstrainedViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}FlyViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}FullViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}PlaneViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}Viewer.h"
  #"${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}WalkViewer.h"
)

set(INST_WIDGETS_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/widgets/So${Gui}PopupMenu.h"
)

# ############################################################################
# Install headers
# ############################################################################

install(FILES ${INST_HDRS}         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}         COMPONENT development)
install(FILES ${INST_DEVICES_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/devices COMPONENT development)
install(FILES ${INST_EDITORS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/editors COMPONENT development)
install(FILES ${INST_NODES_HDRS}   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/nodes   COMPONENT development)
install(FILES ${INST_VIEWERS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/viewers COMPONENT development)
install(FILES ${INST_WIDGETS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/widgets COMPONENT development)

# ############################################################################
# Install data files
# ############################################################################

install(DIRECTORY ${CMAKE_BINARY_DIR}/data/materials/ DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/materials)

# ############################################################################
# Install target
# ############################################################################

if(NOT CMAKE_VERSION VERSION_LESS 3.12)
  install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime NAMELINK_COMPONENT development
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT development
    RESOURCE DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME} COMPONENT development
  )
  if(SO${GUI}_BUILD_SHARED_LIBS)
    if(MSVC)
      install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION ${CMAKE_INSTALL_BINDIR} CONFIGURATIONS Debug RelWithDebInfo COMPONENT debug)
    endif()
  endif()
else()
  install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime NAMELINK_SKIP
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT development
    RESOURCE DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME} COMPONENT development
  )
  if(SO${GUI}_BUILD_SHARED_LIBS)
    install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development NAMELINK_ONLY)
    if(MSVC)
      install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION ${CMAKE_INSTALL_BINDIR} CONFIGURATIONS Debug RelWithDebInfo COMPONENT debug)
    endif()
  endif()
endif()

# ############################################################################
# Install pkgconfig file and CMake config package
# ############################################################################

if(UNIX OR MINGW)
  list(APPEND INCLUDE_DEPENDENCIES_PRIVATE ${OPENGL_INCLUDE_DIR})
  list(APPEND LIB_DEPENDENCIES_PRIVATE ${OPENGL_LIBRARY})

  list(REMOVE_DUPLICATES LIB_DEPENDENCIES)
  foreach(_lib ${LIB_DEPENDENCIES})
    if(_lib MATCHES "^/")
      get_filename_component(_lib ${_lib} NAME_WE)
      string(REGEX REPLACE "^lib" "" _lib ${_lib})
    endif()
    if(_lib MATCHES "^-")
      list(APPEND PKG_CONFIG_LIBS "${_lib}")
    else()
      list(APPEND PKG_CONFIG_LIBS "-l${_lib}")
    endif()
  endforeach()
  list(REMOVE_DUPLICATES LIB_DEPENDENCIES_PRIVATE)
  foreach(_lib ${LIB_DEPENDENCIES_PRIVATE})
    if(_lib MATCHES "^/")
      get_filename_component(_lib ${_lib} NAME_WE)
      string(REGEX REPLACE "^lib" "" _lib ${_lib})
    endif()
    if(_lib MATCHES "^-")
      list(APPEND PKG_CONFIG_LIBS_PRIVATE "${_lib}")
    else()
      list(APPEND PKG_CONFIG_LIBS_PRIVATE "-l${_lib}")
    endif()
  endforeach()
  set(PKG_CONFIG_REQUIRES "$<$<BOOL:${PKG_CONFIG_REQUIRES}>:$<JOIN:${PKG_CONFIG_REQUIRES}, >>")
  set(PKG_CONFIG_REQUIRES_PRIVATE "$<$<BOOL:${PKG_CONFIG_REQUIRES_PRIVATE}>:$<JOIN:${PKG_CONFIG_REQUIRES_PRIVATE}, >>")
  set(PKG_CONFIG_LIBS "$<$<BOOL:${PKG_CONFIG_LIBS}>:$<JOIN:${PKG_CONFIG_LIBS}, >>")
  set(PKG_CONFIG_LIBS_PRIVATE "$<$<BOOL:${PKG_CONFIG_LIBS_PRIVATE}>:$<JOIN:${PKG_CONFIG_LIBS_PRIVATE}, >>")
  set(PKG_CONFIG_CPPFLAGS "${PKG_CONFIG_CPPFLAGS} -I${CMAKE_INSTALL_FULL_INCLUDEDIR}")
  string(REGEX REPLACE "-I${CMAKE_INSTALL_PREFIX}" "-I\${prefix}" PKG_CONFIG_CPPFLAGS "${PKG_CONFIG_CPPFLAGS}")
  list(REMOVE_DUPLICATES INCLUDE_DEPENDENCIES)
  foreach(_inc ${INCLUDE_DEPENDENCIES})
    set(PKG_CONFIG_CPPFLAGS "${PKG_CONFIG_CPPFLAGS} -I${_inc}")
  endforeach()
  set(PKG_CONFIG_CFLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} ${PKG_CONFIG_CFLAGS}")
  set(PKG_CONFIG_CXXFLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} ${PKG_CONFIG_CXXFLAGS}")
  set(PKG_CONFIG_LDFLAGS "${PKG_CONFIG_LDFLAGS} -L${CMAKE_INSTALL_FULL_LIBDIR}")
  string(REGEX REPLACE "-L${CMAKE_INSTALL_PREFIX}" "-L\${exec_prefix}" PKG_CONFIG_LDFLAGS "${PKG_CONFIG_LDFLAGS}")

  # PKG-CONFIG settings
  # according to https://www.gnu.org/prep/standards/html_node/Directory-Variables.html
  # .pc files should be written as ${prefix}/include instead of /usr/local/include
  set(prefix "${CMAKE_INSTALL_PREFIX}")
  set(exec_prefix "\${prefix}")
  string(REGEX REPLACE "^${CMAKE_INSTALL_PREFIX}" "\${exec_prefix}" bindir "${CMAKE_INSTALL_FULL_BINDIR}")
  string(REGEX REPLACE "^${CMAKE_INSTALL_PREFIX}" "\${exec_prefix}" libdir "${CMAKE_INSTALL_FULL_LIBDIR}")
  string(REGEX REPLACE "^${CMAKE_INSTALL_PREFIX}" "\${prefix}" includedir "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
  string(REGEX REPLACE "^${CMAKE_INSTALL_PREFIX}" "\${prefix}" datarootdir "${CMAKE_INSTALL_FULL_DATAROOTDIR}")

  string(REGEX REPLACE "^${CMAKE_INSTALL_FULL_DATAROOTDIR}" "\${datarootdir}" datadir "${CMAKE_INSTALL_FULL_DATADIR}")
  string(REGEX REPLACE "^${CMAKE_INSTALL_FULL_DATAROOTDIR}" "\${datarootdir}" infodir "${CMAKE_INSTALL_FULL_INFODIR}")
  string(REGEX REPLACE "^${CMAKE_INSTALL_FULL_DATAROOTDIR}" "\${datarootdir}" mandir "${CMAKE_INSTALL_FULL_MANDIR}")
  string(REGEX REPLACE "^${CMAKE_INSTALL_FULL_DATAROOTDIR}" "\${datarootdir}" docdir "${CMAKE_INSTALL_FULL_DOCDIR}")

  # HTMLDIR is not defined in GNUInstallDirs.cmake as of CMake 3.18
  #string(REGEX REPLACE "^${CMAKE_INSTALL_FULL_DOCDIR}" "\${docdir}" htmldir "${CMAKE_INSTALL_FULL_HTMLDIR}")
  set(htmldir "\${docdir}/html")
  #set(frameworkdir "${COIN_PKGCFG_FRAMEWORK_DIR}")

  set(PKG_CONFIG_URL "https://www.github.com/coin3d/sowin")
  set(PKG_CONFIG_HOST "${CMAKE_CXX_LIBRARY_ARCHITECTURE}")
  set(PKG_CONFIG_COMPILER "${CMAKE_CXX_COMPILER}")
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(PKG_CONFIG_COMPILER_IS_GCC "yes")
  else()
    set(PKG_CONFIG_COMPILER_IS_GCC "no")
  endif()
  string(REPLACE "." "" PKG_CONFIG_OBJEXT "${CMAKE_CXX_OUTPUT_EXTENSION}")

  configure_file("${CMAKE_SOURCE_DIR}/SoWin.pc.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/SoWin.pc.in" @ONLY)
  # Deal with items configured with generator expressions:
  file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/SoWin.pc" INPUT "${CMAKE_CURRENT_BINARY_DIR}/SoWin.pc.in")
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/SoWin.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Inventor/${Gui}/common/sogui-config.in" "${CMAKE_CURRENT_BINARY_DIR}/sowin-config" @ONLY)
  install(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/sowin-config" DESTINATION ${CMAKE_INSTALL_BINDIR})
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Inventor/${Gui}/common/sogui.cfg.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/sowin-default.cfg.in" @ONLY)
  # Deal with items configured with generator expressions:
  file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/sowin-default.cfg" INPUT "${CMAKE_CURRENT_BINARY_DIR}/sowin-default.cfg.in")
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/sowin-default.cfg" DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Coin/conf)
endif()

include(CMakePackageConfigHelpers)

configure_package_config_file("${CMAKE_SOURCE_DIR}/${PROJECT_NAME_LOWER}-config.cmake.in" ${PROJECT_NAME_LOWER}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  PATH_VARS CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY ExactVersion
)

# To make the component usable not only from the install directory but also from the build directory
export(
  TARGETS ${PROJECT_NAME}
  FILE ${PROJECT_NAME_LOWER}-export.cmake
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  COMPONENT development
)

install(EXPORT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${PROJECT_NAME_LOWER}-export.cmake
  COMPONENT development
)
