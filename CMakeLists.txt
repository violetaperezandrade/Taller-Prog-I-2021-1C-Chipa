cmake_minimum_required(VERSION 3.19)
project(DonkeyKong)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
add_executable(DonkeyKong src/view/View.cpp
        src/controller/Controller.cpp
        src/model/Entity.cpp
        src/model/CollisionManager.cpp
        src/model/Game.cpp
        src/model/entities/Barrel.cpp
        src/model/entities/Character.cpp
        src/model/entities/Ember.cpp
        src/model/entities/Fire.cpp
        src/model/entities/Flame.cpp
        src/model/entities/Monkey.cpp
        src/model/entities/Movement.cpp
        src/model/entities/Platform.cpp
        src/model/entities/Princess.cpp
        src/model/entities/Stair.cpp
        src/Message.cpp
        src/main.cpp
        )
target_link_libraries(DonkeyKong SDL2 SDL2_image nlohmann_json::nlohmann_json)

#target_link_libraries(game /src/controller/Config.cpp ${YAMLCPP_LIBRARIES})