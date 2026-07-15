cmake_minimum_required(VERSION 3.16)
project(csm_gui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(CSM_GUI_BUILD_EXAMPLES "Build examples" OFF)

include(FetchContent)

# ============================================================================
# CSM-CMD - fetched as source
# ============================================================================
FetchContent_Declare(
        csm_cmd
        GIT_REPOSITORY https://github.com/abnaclut/CSM-CMD.git
        GIT_TAG        1.0.0
)

FetchContent_MakeAvailable(csm_cmd)

# ============================================================================
# GLFW (must be before ImGui because ImGui needs GLFW)
# ============================================================================
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)

FetchContent_MakeAvailable(glfw)

# ============================================================================
# ImGui - using thirdparty directory
# ============================================================================
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui)

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(IMGUI_HEADERS
        ${IMGUI_DIR}/imgui.h
        ${IMGUI_DIR}/imconfig.h
        ${IMGUI_DIR}/imgui_internal.h
        ${IMGUI_DIR}/backends/imgui_impl_glfw.h
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.h
)

# ============================================================================
# Find Threads
# ============================================================================
find_package(Threads REQUIRED)

# ============================================================================
# Main GUI library
# ============================================================================
add_library(csm_gui STATIC
        src/gui_application.cpp
        src/gui_terminal.cpp
        src/gui_theme.cpp
        src/gui_cmd_output.cpp
        ${IMGUI_SOURCES}
)

target_include_directories(csm_gui
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(csm_gui
        PUBLIC
        csm_cmd
        glfw
        Threads::Threads
)

target_compile_options(csm_gui
        PRIVATE
        -Wall -Wextra -Wpedantic
)

# ============================================================================
# GUI application
# ============================================================================
add_executable(csm_gui_app src/main.cpp)
target_link_libraries(csm_gui_app PRIVATE csm_gui)
target_compile_options(csm_gui_app PRIVATE -Wall -Wextra -Wpedantic)

# ============================================================================
# Examples
# ============================================================================
if(CSM_GUI_BUILD_EXAMPLES)
    add_executable(example_custom_theme examples/custom_theme/main.cpp)
    target_link_libraries(example_custom_theme PRIVATE csm_gui)
endif()

# ============================================================================
# Installation
# ============================================================================
install(TARGETS csm_gui csm_gui_app
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*.h"
)