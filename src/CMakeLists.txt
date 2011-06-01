
option(PACKAGEKIT_GLIB2 "Use glib2" ON)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(Gettext REQUIRED)
include_directories(${GETTEXT_INCLUDE_DIR})

list(APPEND LIBS ${PROTOBUF_LIBRARY} ${GETTEXT_LIBRARY})

set(GRAPH_SRC graph/externaldependencypool.cpp graph/nodeparser.cpp graph/nodefactory.cpp graph/externaldependencyresolver.cpp
graph/node.cpp graph/externaldependency.cpp graph/dummyexternaldependencymapper.cpp
graph/externaldependencymapperfactory.cpp graph/externaldependencymapper.cpp)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS graph/protocolbuffers/packagemapcontainer.proto
graph/protocolbuffers/packagedescription.proto)

set(SPACE_SRC space/space.cpp)

set(IO_SRC util/io/resourcereference.cpp util/io/file.cpp util/io/directory.cpp)

if(PACKAGEKIT_GLIB2)
        include(FindPkgConfig)
        pkg_check_modules(LIBDBUSGLIB REQUIRED dbus-glib-1)
        list(APPEND GRAPH_SRC graph/packagekitinterface.cpp)
        list(APPEND LIBS ${LIBDBUSGLIB_LIBRARIES})
        include_directories(${LIBDBUSGLIB_INCLUDE_DIRS})
endif(PACKAGEKIT_GLIB2)

add_executable(hive main.cpp  ${PROTO_SRCS} ${PROTO_HDRS} ${GRAPH_SRC} ${IO_SRC} ${SPACE_SRC})
target_link_libraries(hive ${LIBS})
