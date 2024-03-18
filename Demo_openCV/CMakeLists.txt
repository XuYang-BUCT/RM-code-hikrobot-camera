# 指定CMake的最小版本要求
cmake_minimum_required(VERSION 3.0)

# 设置项目名称
project(demo001)

# 查找OpenCV库
find_package(OpenCV REQUIRED)

# 包含OpenCV的头文件目录
include_directories(${OpenCV_INCLUDE_DIRS})

# 定义可执行文件，命名为your_executable_name，由main.cpp源文件生成
add_executable(try_demo main.cpp)

# 将OpenCV库链接到你的可执行文件上
target_link_libraries(try_demo ${OpenCV_LIBS})

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE INTERNAL "")
