# Version requise de CMake
cmake_minimum_required(VERSION 3.0)
# Nom de projet
project(hugottp)

add_library(init init.c)
add_library(request request.c)

# Commandes d'installation
add_executable(hugottp hugottp.c)
target_link_libraries(hugottp init request)
install(TARGETS init DESTINATION ${HUGOTTP_INSTALL_LIB_DIR})
install(TARGETS hugottp DESTINATION ${HUGOTTP_INSTALL_BIN_DIR})
