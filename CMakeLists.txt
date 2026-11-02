cmake_minimum_required(VERSION 3.16)
project(satk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Usando Qt5 disponível no sistema (Qt 6 será migrado em seguida)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick DBus Multimedia)

add_executable(satk
    main.cpp
    stkapplication.cpp stkapplication.h
    stkmainwindow.cpp stkmainwindow.h
    stkmenumodel.cpp stkmenumodel.h
    stkofonoproperties.cpp stkofonoproperties.h
    stkofonoutils.cpp stkofonoutils.h
    simimageprovider.cpp simimageprovider.h
    stkagentservice.cpp stkagentservice.h
    ofonodbustypes.h
    resources.qrc
)

target_link_libraries(satk PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Quick
    Qt5::DBus
    Qt5::Multimedia
)

target_compile_definitions(satk PRIVATE SATK_DESKTOP_BUILD)

install(TARGETS satk DESTINATION bin)
