cmake_minimum_required(VERSION 3.19)
project(DonkeyKong)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

add_executable(DonkeyKong src/client/View.cpp
        src/controller/Controller.cpp
        src/server/Entity.cpp
        src/server/CollisionManager.cpp
        src/server/Game.cpp
        src/server/entities/Barrel.cpp
        src/server/entities/Character.cpp
        src/server/entities/Ember.cpp
        src/server/entities/Fire.cpp
        src/server/entities/Flame.cpp
        src/server/entities/Monkey.cpp
        src/server/entities/Movement.cpp
        src/server/entities/Platform.cpp
        src/server/entities/Princess.cpp
        src/server/entities/Stair.cpp
        src/Message.cpp
        src/main.cpp
        src/common/Logger.cpp
        src/server/Config.cpp
        )
target_link_libraries(DonkeyKong jsoncpp SDL2 SDL2_image nlohmann_json::nlohmann_json)
