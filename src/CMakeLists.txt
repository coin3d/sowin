configure_file(config.h.cmake.in config.h)

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

if(SO${GUI}_BUILD_SHARED_LIBS)
  if(WIN32)
    configure_file(${PROJECT_NAME}.rc.cmake.in ${PROJECT_NAME}.rc)
    set(SO${GUI}_RESSOURCE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc" CACHE INTERNAL "SO${GUI}_RESSOURCE")
    set(CMAKE_RELEASE_POSTFIX ${PROJECT_VERSION_MAJOR})
    set(CMAKE_MINSIZEREL_POSTFIX ${PROJECT_VERSION_MAJOR})
    set(CMAKE_RELWITHDEBINFO_POSTFIX ${PROJECT_VERSION_MAJOR})
    set(CMAKE_DEBUG_POSTFIX ${PROJECT_VERSION_MAJOR}d)
  endif()
  add_library(${PROJECT_NAME} SHARED ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${SO${GUI}_RESSOURCE})
  target_compile_definitions(${PROJECT_NAME} PRIVATE SO${GUI}_MAKE_DLL INTERFACE SO${GUI}_DLL)
else()
  if(WIN32)
    set(CMAKE_RELEASE_POSTFIX ${PROJECT_VERSION_MAJOR}s)
    set(CMAKE_MINSIZEREL_POSTFIX ${PROJECT_VERSION_MAJOR}s)
    set(CMAKE_RELWITHDEBINFO_POSTFIX ${PROJECT_VERSION_MAJOR}s)
    set(CMAKE_DEBUG_POSTFIX ${PROJECT_VERSION_MAJOR}sd)
  endif()
  add_library(${PROJECT_NAME} STATIC ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS})
  target_compile_definitions(${PROJECT_NAME} INTERFACE SO${GUI}_NOT_DLL)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${SO${GUI}_VERSION} SOVERSION ${SO${GUI}_SO_VERSION})

target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H SO${GUI}_INTERNAL SO${GUI}_DEBUG=$<CONFIG:Debug>)
if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_NONSTDC_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS)
  if(NOT SO${GUI}_BUILD_SHARED_LIBS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")                       # Override default /Zi to embed
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Z7")     # debugging info in the .lib.
  endif()
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} PUBLIC Coin::Coin ${OPENGL_LIBRARIES})

# Add a target to generate API documentation with Doxygen
if(SO${GUI}_BUILD_DOCUMENTATION)
  find_package(Doxygen)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
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
    install(FILES "${CMAKE_BINARY_DIR}/html/${PROJECT_NAME}.chm" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation)
  endif()
  if(GENERATE_QHP)
    install(FILES "${CMAKE_BINARY_DIR}/html/${PROJECT_NAME}.qch" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation)
  endif()
  if(DOXYGEN_GENERATE_MAN)
    install(DIRECTORY "${CMAKE_BINARY_DIR}/man/man3" DESTINATION ${CMAKE_INSTALL_MANDIR} COMPONENT documentation)
    message(STATUS "CMAKE_INSTALL_MANDIR ${CMAKE_INSTALL_MANDIR}")
  endif()
endif()

# ############################################################################
# Install headers, binaries and config package
# ############################################################################

if(UNIX OR MINGW)
  configure_file("${CMAKE_SOURCE_DIR}/So${Gui}.pc.cmake.in" So${Gui}.pc @ONLY)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/So${Gui}.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()

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
  ${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/widgets/So${Gui}PopupMenu.h
)

install(FILES ${INST_HDRS}         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}         COMPONENT development)
install(FILES ${INST_DEVICES_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/devices COMPONENT development)
install(FILES ${INST_EDITORS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/editors COMPONENT development)
install(FILES ${INST_NODES_HDRS}   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/nodes   COMPONENT development)
install(FILES ${INST_VIEWERS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/viewers COMPONENT development)
install(FILES ${INST_WIDGETS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/widgets COMPONENT development)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime NAMELINK_SKIP
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
)

if(SO${GUI}_BUILD_SHARED_LIBS)
  install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development NAMELINK_ONLY)
  if(MSVC)
    install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION ${CMAKE_INSTALL_BINDIR} CONFIGURATIONS Debug RelWithDebInfo COMPONENT debug)
  endif()
endif()

configure_package_config_file("${CMAKE_BINARY_DIR}/${PROJECT_NAME_LOWER}-config.cmake.in" ${PROJECT_NAME_LOWER}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
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
