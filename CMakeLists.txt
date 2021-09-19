cmake_minimum_required(VERSION 3.15)
project(asteroids)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/entities/Explosion.h
        src/entities/Explosion.cpp
        src/entities/Entity.h
        src/entities/Entity.cpp
        src/entities/Bullet.h
        src/entities/Bullet.cpp
        src/Utils.h
        src/Utils.cpp
        src/Constants.h
        src/Window.h
        src/Window.cpp
        src/entities/Rock.h
        src/entities/Rock.cpp
        src/entities/Rocket.h
        src/entities/Rocket.cpp
        src/SoundBoard.h
        src/SoundBoard.cpp
        src/Scene.h
        src/Scene.cpp
        src/events/Event.h
        src/events/Event.cpp
        src/events/EventBus.h
        src/events/EventBus.cpp
        src/events/EventListener.h
        src/events/EventListener.cpp
        src/events/EventNames.h
        src/events/EventNames.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/vendor/libraylib.dylib)

