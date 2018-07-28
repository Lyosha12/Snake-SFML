cmake_minimum_required(VERSION 3.12)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -pedantic -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME}
        SRC/main.cpp


        SRC/Utility/TextureStorage/TextureStorage.cpp
        SRC/Utility/TextureStorage/TextureStorage.hpp

        SRC/Utility/ErrorPrinter/ErrorPrinter.cpp
        SRC/Utility/ErrorPrinter/ErrorPrinter.hpp

        SRC/Utility/Coord/Coord.cpp
        SRC/Utility/Coord/Coord.hpp

        SRC/Utility/ThreadGuard/ThreadGuard.hpp
        SRC/Utility/ThreadGuard/ThreadGuard.cpp

        SRC/Utility/ThreadGuard/LiveStorage/LiveStorage.cpp
        SRC/Utility/ThreadGuard/LiveStorage/LiveStorage.hpp

        SRC/Utility/WindowForTests/WindowForTests.cpp
        SRC/Utility/WindowForTests/WindowForTests.hpp

        SRC/Utility/RandomGenerator/RandomGenerator.hpp
        SRC/Utility/RandomGenerator/RandomGenerator.cpp

        SRC/Utility/ListRunner.hpp
        SRC/Utility/Stopwatch.hpp
        SRC/Utility/TimeProfiler.hpp
        SRC/Utility/Timer.hpp



        SRC/CellsPool/DefaultRectangle/Configurator.cpp
        SRC/CellsPool/DefaultRectangle/DefaultRectangle.cpp
        SRC/CellsPool/DefaultRectangle/DefaultRectangle.hpp

        SRC/CellsPool/Cell/Filler/Filler.cpp
        SRC/CellsPool/Cell/Cell.cpp
        SRC/CellsPool/Cell/Cell.hpp

        SRC/CellsPool/NotFoundFreeCell/NotFoundFreeCell.cpp
        SRC/CellsPool/NotFoundFreeCell/NotFoundFreeCell.hpp

        SRC/CellsPool/Cell/Fillers/FreeCellFiller.hpp
        SRC/CellsPool/Cell/Fillers/EatFiller.hpp
        SRC/CellsPool/Cell/Fillers/Head.hpp
        SRC/CellsPool/Cell/Fillers/Body.hpp

        SRC/CellsPool/CellsPool.cpp
        SRC/CellsPool/CellsPool.hpp

        SRC/CellsPool/Cell/Filler/Filler.hpp



        SRC/Snake/Snake.cpp
        SRC/Snake/Snake.hpp



        SRC/BonusManager/BonusManager.cpp
        SRC/BonusManager/BonusManager.hpp

        SRC/BonusManager/Bonus/Bonus.cpp
        SRC/BonusManager/Bonus/Bonus.hpp

        SRC/BonusManager/Eat/Eat.cpp
        SRC/BonusManager/Eat/Eat.hpp

        SRC/BonusManager/SteppedOnBody/SteppedOnBody.cpp
        SRC/BonusManager/SteppedOnBody/SteppedOnBody.hpp

        SRC/BonusManager/SteppedOnHead/SteppedOnHead.cpp
        SRC/BonusManager/SteppedOnHead/SteppedOnHead.hpp

        SRC/BonusManager/Move/Move.cpp
        SRC/BonusManager/Move/Move.hpp

        SRC/BonusManager/SteppedOnBody/SteppedOnBody.cpp
        SRC/BonusManager/SteppedOnBody/SteppedOnBody.hpp

        SRC/BonusManager/SteppedOnHead/SteppedOnHead.cpp
        SRC/BonusManager/SteppedOnHead/SteppedOnHead.hpp


        SRC/AudioPlayer/AudioController.cpp
        SRC/AudioPlayer/AudioController.hpp

        SRC/AudioPlayer/MusicPlayer/MusicPlayer.cpp
        SRC/AudioPlayer/MusicPlayer/MusicPlayer.hpp

        SRC/AudioPlayer/SoundPlayer/SoundPlayer.cpp
        SRC/AudioPlayer/SoundPlayer/SoundPlayer.hpp

        SRC/Snake/GameEnd.hpp SRC/Utility/RandomSort.hpp)

include_directories(SRC)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_ROOT "D:/Programs/ProgrammingEnvironment/Librares/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()



set (Boost_USE_MULTITHREADED  ON)
set (Boost_USE_STATIC_LIBS    ON)
set (Boost_USE_STATIC_RUNTIME ON)
set (BOOST_ALL_DYN_LINK       OFF)

set(BOOST_ROOT "D:/Programs/ProgrammingEnvironment/Librares/boost_1_67_0/Build")
find_package(Boost 1.67.0 REQUIRED filesystem system)

if(Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

