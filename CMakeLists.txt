cmake_minimum_required(VERSION 3.6)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -pedantic -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)


set(SFML_ROOT "W:/Programs/Programming environment/Librares/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics network audio window system)

add_executable(${PROJECT_NAME}
        main.cpp

        ErrorPrinter/ErrorPrinter.cpp
        ErrorPrinter/ErrorPrinter.hpp

        Coord/Coord.cpp
        Coord/Coord.hpp

        CellsPool/DefaultRectangle/Configurator.cpp
        CellsPool/DefaultRectangle/DefaultRectangle.cpp
        CellsPool/DefaultRectangle/DefaultRectangle.hpp

        CellsPool/Cell/Filler/Filler.cpp
        CellsPool/Cell/Cell.cpp
        CellsPool/Cell/Cell.hpp

        TimeCounter/TimeCounter.hpp

        TextureStorage/TextureStorage.cpp
        TextureStorage/TextureStorage.hpp

        CellsPool/NotFoundFreeCell/NotFoundFreeCell.cpp
        CellsPool/NotFoundFreeCell/NotFoundFreeCell.hpp

        CellsPool/RequestedCell/RequestedCell.hpp
        CellsPool/RequestedCell/RequestedCell.cpp

        CellsPool/CellsPool.cpp
        CellsPool/CellsPool.hpp

        Snake/Snake.cpp
        Snake/Snake.hpp

        BonusManager/BonusManager.cpp
        BonusManager/BonusManager.hpp

        BonusManager/Bonus/Bonus.cpp
        BonusManager/Bonus/Bonus.hpp

        BonusManager/Eat/Eat.cpp
        BonusManager/Eat/Eat.hpp

        CellsPool/Cell/Filler/Filler.hpp)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
