cmake_minimum_required(VERSION 3.6)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -pedantic -Wall -Wextra ")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)


set(SFML_ROOT "D:/Programs/ProgrammingEnvironment/Librares/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics network audio window system)

add_executable(${PROJECT_NAME}
        main.cpp


        CellsPool/DefaultRectangle/Configurator.cpp
        CellsPool/DefaultRectangle/DefaultRectangle.cpp
        CellsPool/DefaultRectangle/DefaultRectangle.hpp

        CellsPool/Cell/Filler/Filler.cpp
        CellsPool/Cell/Cell.cpp
        CellsPool/Cell/Cell.hpp

        CellsPool/NotFoundFreeCell/NotFoundFreeCell.cpp
        CellsPool/NotFoundFreeCell/NotFoundFreeCell.hpp

        CellsPool/CellsPool.cpp
        CellsPool/CellsPool.hpp

        CellsPool/Cell/Filler/Filler.hpp
        CellsPool/Cell/Fillers/FreeCellFiller.hpp

       # CellsPool/CellsPool.tpl.cpp

        Snake/Snake.cpp
        Snake/Snake.hpp

        CellsPool/Cell/Fillers/Head.hpp

        CellsPool/Cell/Fillers/Body.hpp


        BonusManager/BonusManager.cpp
        BonusManager/BonusManager.hpp

        BonusManager/Bonus/Bonus.cpp
        BonusManager/Bonus/Bonus.hpp

        BonusManager/Eat/Eat.cpp
        BonusManager/Eat/Eat.hpp

        BonusManager/SteppedOnBody/SteppedOnBody.cpp
        BonusManager/SteppedOnBody/SteppedOnBody.hpp

        BonusManager/SteppedOnHead/SteppedOnHead.cpp
        BonusManager/SteppedOnHead/SteppedOnHead.hpp

        BonusManager/Move/Move.cpp
        BonusManager/Move/Move.hpp

        BonusManager/SteppedOnBody/SteppedOnBody.cpp
        BonusManager/SteppedOnBody/SteppedOnBody.hpp

        BonusManager/SteppedOnHead/SteppedOnHead.cpp
        BonusManager/SteppedOnHead/SteppedOnHead.hpp

        CellsPool/Cell/Fillers/EatFiller.hpp


        Utilites/TextureStorage/TextureStorage.cpp
        Utilites/TextureStorage/TextureStorage.hpp

        Utilites/TimeCounter/IntervalChecker.hpp

        Utilites/ErrorPrinter/ErrorPrinter.cpp
        Utilites/ErrorPrinter/ErrorPrinter.hpp

        Utilites/Coord/Coord.cpp
        Utilites/Coord/Coord.hpp

        Utilites/ListRunner.hpp

        Utilites/ThreadGuard/ThreadGuard.hpp
        Utilites/ThreadGuard/ThreadGuard.cpp

        Utilites/ThreadGuard/LiveStorage/LiveStorage.cpp
        Utilites/ThreadGuard/LiveStorage/LiveStorage.hpp

        Utilites/TimeProfiler/TimeProfiler.cpp
        Utilites/TimeProfiler/TimeProfiler.hpp

        Utilites/Timer/Timer.cpp
        Utilites/Timer/Timer.hpp

        Utilites/WindowForTests/WindowForTests.cpp
        Utilites/WindowForTests/WindowForTests.hpp


        )
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
