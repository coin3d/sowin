configure_file(crash.cpp.in crash.cpp @ONLY)
add_executable(crash ${CMAKE_CURRENT_BINARY_DIR}/crash.cpp)
target_link_libraries(crash SoWin)

add_executable(embedded embedded.cpp)
target_link_libraries(embedded SoWin)
set_target_properties(embedded PROPERTIES WIN32_EXECUTABLE TRUE)

add_executable(multiview multiview.cpp)
target_link_libraries(multiview SoWin)
set_target_properties(multiview PROPERTIES WIN32_EXECUTABLE TRUE)

add_executable(standalone standalone.cpp)
target_link_libraries(standalone SoWin)
