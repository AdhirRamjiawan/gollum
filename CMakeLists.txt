# CMakeList.txt : CMake project for Gollum, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Gollum")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add source to this project's executable.
add_executable (Gollum "Gollum.cpp" "Gollum.h" "Encryption/Encrypt.cpp" "Encryption/Encrypt.h" "AbstractAction.h" "AbstractAction.cpp" "Actions/AddAction.cpp" "Actions/AddAction.h" "GollumStrings.h" "Actions/ListAction.h" "Actions/ListAction.cpp" "Models.h" "FileManager.cpp" "FileManager.h" "Actions/RemoveAction.cpp" "Tests/hello_test.cc")
enable_testing()
# TODO: Add tests and install targets if needed.

#target_link_libraries(Gollum LINK_PUBLIC "C:\\Program Files\\OpenSSL-Win64\\lib\\libcrypto.lib")

#include_directories(Gollum "C:\\Program Files\\OpenSSL-Win64\\include")

target_link_libraries(Gollum LINK_PUBLIC gtest_main "C:\\users\\adhir\\libs\\tiny-eas\\aes.a")
include_directories(Gollum "C:\\users\\adhir\\libs\\tiny-eas")

include(GoogleTest)
gtest_discover_tests(Gollum)

# RUN TESTS BY:
# cd out\build\x64-Debug
# ctest
# See ref: https://google.github.io/googletest/quickstart-cmake.html