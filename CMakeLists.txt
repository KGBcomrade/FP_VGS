cmake_minimum_required(VERSION 3.13)
project(FP2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
#link_directories(tinyxml)
#find_package(TinyXML 2.6.2)
find_package(SFML 2.5 COMPONENTS graphics window system network audio)

add_executable(FP2
        tinyxml/tinystr.cpp
        tinyxml/tinystr.h
        tinyxml/tinyxml.cpp
        tinyxml/tinyxml.h
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        main.cpp
        view.h
        Entities/Entity.cpp
        Entities/Entity.h
        Utils/ContentManager.cpp
        Utils/ContentManager.h Entities/Player.cpp Entities/Player.h Misc/Object.cpp Misc/Object.h Misc/Layer.h Misc/Level.cpp Misc/Level.h Entities/Enemy.cpp Entities/Enemy.h Misc/Layer.cpp Utils/Utils.h)

target_link_libraries(FP2 sfml-graphics sfml-audio sfml-network sfml-system sfml-window)

#add_library(tinyxml SHARED IMPORTED)
