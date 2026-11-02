cmake_minimum_required(VERSION 3.16)
project(satk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Quick DBus)

add_executable(satk
    main.cpp
    stkapplication.cpp stkapplication.h
    stkmainwindow.cpp stkmainwindow.h
    stkmenumodel.cpp stkmenumodel.h
    stkofonoproperties.cpp stkofonoproperties.h
    stkofonoutils.cpp stkofonoutils.h
    simimageprovider.cpp simimageprovider.h
    stkagentservice.cpp stkagentservice.h
    ofonodbustypes.cpp ofonodbustypes.h
    resources.qrc
)

target_link_libraries(satk PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Quick
    Qt6::DBus
)

target_compile_definitions(satk PRIVATE SATK_DESKTOP_BUILD)

install(TARGETS satk DESTINATION bin)
