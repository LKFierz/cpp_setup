cmake_minimum_required(VERSION 3.10)
project(project_creator)

# Add executable target
add_executable(project_creator src/main.cpp)

# Specify installation directory for the executable
install(TARGETS project_creator DESTINATION bin)

