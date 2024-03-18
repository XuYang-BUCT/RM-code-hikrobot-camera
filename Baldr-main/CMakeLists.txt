# Cmake最小版本
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Baldr)
project(${PROJECT_NAME})
set(CMAKE_BUILD_TYPE RELEASE)
# SET(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 11)

# 可执行文件生成路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/build)

# 找到OpenCV包
find_package(OpenCV REQUIRED)
# 查找和添加X11, pthread库
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)

# 如果MVCAM_COMMON_RUNENV环境变量未设置，需要手动设置或报错
if(NOT DEFINED ENV{MVCAM_COMMON_RUNENV})
  message(FATAL_ERROR "MVCAM_COMMON_RUNENV is not set")
endif()

# 添加库目录
link_directories("$ENV{MVCAM_COMMON_RUNENV}/64")

# 引用库
include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include/eigen-3.3.7)
include_directories(${PROJECT_SOURCE_DIR}/Src)
# 添加include目录，直接使用绝对路径
include_directories("/opt/MVS/include")

# 生成指定目标
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/Src/*.cpp")
add_executable(${PROJECT_NAME} Src/main.cpp ${SOURCE_FILES})

# 将第三方的库链接到可执行文件
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
# target_link_libraries(${PROJECT_NAME}
# "/opt/DahuaTech/MVviewer/lib/libMVSDK.so")
# target_link_libraries(${PROJECT_NAME}
# "/opt/DahuaTech/MVviewer/module/USBDriver/libu3v-core.a") 链接库到我们的可执行文件
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} MvCameraControl
                      ${CMAKE_THREAD_LIBS_INIT})
# 设置运行时库搜索路径
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH
                                                 "$ENV{MVCAM_COMMON_RUNENV}/64")
