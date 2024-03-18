# !/bin/zsh
#set.sh

rm -rf build

# 创建并进入构建目录
mkdir -p build && cd build

# 运行CMake来配置项目并生成Makefile
cmake ..

# 构建项目
make
