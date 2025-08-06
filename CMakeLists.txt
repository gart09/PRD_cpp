cmake_minimum_required(VERSION 3.16)
project(RandomDefenseGame)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 컴파일러 설정
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# 소스 파일들 수집
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})

# 헤더 파일 디렉터리 추가
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Windows 특정 라이브러리 연결
if(WIN32)
    target_link_libraries(${PROJECT_NAME} user32)
endif()

# 빌드 디렉터리 설정
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 디버그/릴리즈 설정
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG=1)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}") 