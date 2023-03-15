# Set the name and the supported language of the project
project(hello-gtk C)
# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.6...3.13)
# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
# Add executables compiled from sources
add_executable(userinput userinput.c)
add_executable(gtktest gtktest.c)
add_executable(treeview treeview.c)
add_executable(menu menu.c)
add_executable(dialogs dialogs.c)
add_executable(mylayout mylayout.c)
# Copy glade file for mylayout target
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mylayout.glade ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/mylayout.glade
        ${PROJECT_BINARY_DIR}/mylayout.glade
        COMMENT "Copying mylayout.glade into binary directory")

add_dependencies(mylayout copy_resources)
# Link the target to the GTK+ libraries
target_link_libraries(userinput ${GTK3_LIBRARIES})
target_link_libraries(gtktest ${GTK3_LIBRARIES})
target_link_libraries(treeview ${GTK3_LIBRARIES})
target_link_libraries(menu ${GTK3_LIBRARIES})
target_link_libraries(dialogs ${GTK3_LIBRARIES})
target_link_libraries(mylayout ${GTK3_LIBRARIES})
