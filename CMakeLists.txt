cmake_minimum_required(VERSION 3.19)
project(DonkeyKong)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
add_executable(DonkeyKong src/controller/main.cpp)
target_link_libraries(DonkeyKong jsoncpp)

#get_target_property(JSON_INC_PATH jsoncpp_lib)
#include_directories(${JSON_INC_PATH})

#target_link_libraries(${PROJECT_NAME} jsoncpp_lib)
#add_executable(DonkeyKong src/main.cpp src/model/Stair.cpp src/model/Barrel.cpp  src/controller/Config.cpp)



#target_link_libraries(DonkeyKong ${jsoncpp})

#target_link_libraries(game /src/controller/Config.cpp ${YAMLCPP_LIBRARIES})