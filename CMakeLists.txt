cmake_minimum_required(VERSION 3.15)
project(asteroids)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)

file(GLOB SRC_FILES src/*.h src/*.cpp)
add_executable(${PROJECT_NAME}
        ${SRC_FILES}
#        src/main.cpp
#        src/Explosion.h
#        src/Bullet.h
#        src/Utils.h
#        src/Constants.h
#        src/Window.h
#        src/Asteroid.h
#        src/Rocket.h
#        src/SoundBoard.h
        )

target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libraylib.dylib)
#target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libraylib.a)

