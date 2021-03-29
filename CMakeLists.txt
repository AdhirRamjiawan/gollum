# CMakeList.txt : CMake project for Gollum, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Gollum")

# Add source to this project's executable.
add_executable (Gollum "Gollum.cpp" "Gollum.h" "Encrypt.cpp" "Encrypt.h" "AbstractAction.h" "AbstractAction.cpp" "Actions/AddAction.cpp" "Actions/AddAction.h" "GollumStrings.h" "Actions/ListAction.h" "Actions/ListAction.cpp")

# TODO: Add tests and install targets if needed.

target_link_libraries(Gollum LINK_PUBLIC "C:\\Program Files\\OpenSSL-Win64\\lib\\libcrypto.lib")

include_directories(Gollum "C:\\Program Files\\OpenSSL-Win64\\include")