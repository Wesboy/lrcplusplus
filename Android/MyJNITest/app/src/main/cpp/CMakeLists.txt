cmake_minimum_required(VERSION 3.4.1)

# 这一句用来导出编译生成的so库
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/jniLibs/${ANDROID_ABI})

find_library(log-lib log)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(wTest SHARED
        myjni.cpp)

target_link_libraries(
        wTest
        ${log-lib}
        ${LIB-Z}
)