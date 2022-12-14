cmake_minimum_required(VERSION 3.14)

project(render_sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# Add evolution simulator headers and sources
add_subdirectory(include)
add_subdirectory(src)


# Fetch external dependencies
add_subdirectory(ext)


# Add evolution simulator executable target
add_executable(render_sandbox
    ${RENDER_SANDBOX_HEADERS}
    ${RENDER_SANDBOX_SOURCES}
)

target_include_directories(render_sandbox
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(render_sandbox
PUBLIC
    gut_opengl
)

target_compile_definitions(render_sandbox
PUBLIC
    -DRES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/res/\"
)
