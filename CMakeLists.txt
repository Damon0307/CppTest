cmake_minimum_required(VERSION 3.10)
project(a.out VERSION 1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置默认的构建类型为 Debug
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
 
# 添加源文件
set(SOURCES
    src/main.cpp
)

# 添加头文件目录
include_directories(include)

link_directories(lib)

# 添加可执行文件
add_executable(a.out ${SOURCES})

# 如果有库依赖，可以在这里链接
target_link_libraries(a.out  pthread)
#target_link_libraries(a.out PRIVATE hv)

# # 安装规则
# install(TARGETS a.out DESTINATION bin)
# install(DIRECTORY include/ DESTINATION include)

# # 测试
# enable_testing()
# add_test(NAME MyTest COMMAND a.out)

# # 打包
# set(CPACK_PACKAGE_NAME "a.out")
# set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
# include(CPack)

