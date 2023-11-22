cmake_minimum_required(VERSION 3.5)

project(nfs2se)

set(SDL_LIB_NAME ${CMAKE_SHARED_LIBRARY_PREFIX}SDL2-2.0${CMAKE_SHARED_LIBRARY_SUFFIX})

# find SDL
find_library(SDL 
    NAMES ${SDL_LIB_NAME} 
    HINTS ${SDL_PATH} 
    PATH_SUFFIXES build 
    NO_CMAKE_FIND_ROOT_PATH
)
find_path(SDL_INCL 
    NAMES SDL.h 
    HINTS ${SDL_PATH} 
    PATH_SUFFIXES include 
    NO_CMAKE_FIND_ROOT_PATH
)
message("'SDL' found: " ${SDL}) 
message("'SDL_INCL' found: " ${SDL_INCL}) 

link_libraries(
    ${SDL} 
)
include_directories(
    .
    ${SDL_INCL} 
)

set(CMAKE_CXX_STANDARD 20)
add_definitions(
    -DOPENGL1X
)

# Add an executable
add_executable(nfs2se 
    src/Cpp/NFS2SE.cpp
    src/DInput.c
    src/EAcsnd.c
    src/FetchTrackRecords.c
    src/Glide2x.c
    src/Kernel32.c
    src/Timer.c
    src/User32.c
    src/WinMM.c
    src/Wrapper.c
    src/Wsock32.c
    src/Glide2x/rrx.cpp
)

target_compile_options(nfs2se 
    PRIVATE 
        -std=gnu89
        -std=c++14
        -fpermissive 
        -Wno-narrowing
        -fno-rtti 
        -fno-exceptions
        -lm
)
target_link_libraries(nfs2se 
    PRIVATE gl spdlog::spdlog dmaproxy
)

if (VARIANT_RRXIF)
    add_compile_definitions(VARIANT_RRXIF=1)
endif()
if (VARIANT_RRXEF)
    add_compile_definitions(VARIANT_RRXEF=1)
endif()

add_subdirectory(Rasterix)