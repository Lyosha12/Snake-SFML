cmake_minimum_required(VERSION 3.12)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -pedantic -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

set(SRT_ROOT "SRC")

add_executable(${PROJECT_NAME}
        ${SRT_ROOT}/main.cpp

        ${SRT_ROOT}/CellsPool/DefaultRectangle/Configurator.cpp
        ${SRT_ROOT}/CellsPool/DefaultRectangle/DefaultRectangle.cpp
        ${SRT_ROOT}/CellsPool/DefaultRectangle/DefaultRectangle.hpp

        ${SRT_ROOT}/CellsPool/Cell/Filler/Filler.cpp
        ${SRT_ROOT}/CellsPool/Cell/Cell.cpp
        ${SRT_ROOT}/CellsPool/Cell/Cell.hpp

        ${SRT_ROOT}/CellsPool/NotFoundFreeCell/NotFoundFreeCell.cpp
        ${SRT_ROOT}/CellsPool/NotFoundFreeCell/NotFoundFreeCell.hpp

        ${SRT_ROOT}/CellsPool/CellsPool.cpp
        ${SRT_ROOT}/CellsPool/CellsPool.hpp

        ${SRT_ROOT}/CellsPool/Cell/Filler/Filler.hpp
        ${SRT_ROOT}/CellsPool/Cell/Fillers/FreeCellFiller.hpp

        ${SRT_ROOT}/Snake/Snake.cpp
        ${SRT_ROOT}/Snake/Snake.hpp

        ${SRT_ROOT}/CellsPool/Cell/Fillers/Head.hpp

        ${SRT_ROOT}/CellsPool/Cell/Fillers/Body.hpp


        ${SRT_ROOT}/BonusManager/BonusManager.cpp
        ${SRT_ROOT}/BonusManager/BonusManager.hpp

        ${SRT_ROOT}/BonusManager/Bonus/Bonus.cpp
        ${SRT_ROOT}/BonusManager/Bonus/Bonus.hpp

        ${SRT_ROOT}/BonusManager/Eat/Eat.cpp
        ${SRT_ROOT}/BonusManager/Eat/Eat.hpp

        ${SRT_ROOT}/BonusManager/SteppedOnBody/SteppedOnBody.cpp
        ${SRT_ROOT}/BonusManager/SteppedOnBody/SteppedOnBody.hpp

        ${SRT_ROOT}/BonusManager/SteppedOnHead/SteppedOnHead.cpp
        ${SRT_ROOT}/BonusManager/SteppedOnHead/SteppedOnHead.hpp

        ${SRT_ROOT}/BonusManager/Move/Move.cpp
        ${SRT_ROOT}/BonusManager/Move/Move.hpp

        ${SRT_ROOT}/BonusManager/SteppedOnBody/SteppedOnBody.cpp
        ${SRT_ROOT}/BonusManager/SteppedOnBody/SteppedOnBody.hpp

        ${SRT_ROOT}/BonusManager/SteppedOnHead/SteppedOnHead.cpp
        ${SRT_ROOT}/BonusManager/SteppedOnHead/SteppedOnHead.hpp

        ${SRT_ROOT}/CellsPool/Cell/Fillers/EatFiller.hpp


        ${SRT_ROOT}/Utilites/TextureStorage/TextureStorage.cpp
        ${SRT_ROOT}/Utilites/TextureStorage/TextureStorage.hpp

        ${SRT_ROOT}/Utilites/Timer.hpp

        ${SRT_ROOT}/Utilites/ErrorPrinter/ErrorPrinter.cpp
        ${SRT_ROOT}/Utilites/ErrorPrinter/ErrorPrinter.hpp

        ${SRT_ROOT}/Utilites/Coord/Coord.cpp
        ${SRT_ROOT}/Utilites/Coord/Coord.hpp

        ${SRT_ROOT}/Utilites/ListRunner.hpp

        ${SRT_ROOT}/Utilites/ThreadGuard/ThreadGuard.hpp
        ${SRT_ROOT}/Utilites/ThreadGuard/ThreadGuard.cpp

        ${SRT_ROOT}/Utilites/ThreadGuard/LiveStorage/LiveStorage.cpp
        ${SRT_ROOT}/Utilites/ThreadGuard/LiveStorage/LiveStorage.hpp

        ${SRT_ROOT}/Utilites/TimeProfiler/TimeProfiler.cpp
        ${SRT_ROOT}/Utilites/TimeProfiler/TimeProfiler.hpp

        ${SRT_ROOT}/Utilites/Stopwatch/Stopwatch.cpp
        ${SRT_ROOT}/Utilites/Stopwatch/Stopwatch.hpp

        ${SRT_ROOT}/Utilites/WindowForTests/WindowForTests.cpp
        ${SRT_ROOT}/Utilites/WindowForTests/WindowForTests.hpp


        )


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