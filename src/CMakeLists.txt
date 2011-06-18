
option(PACKAGEKIT_GLIB2 "Use glib2" ON)


include(FindPkgConfig)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(Gettext REQUIRED)
include_directories(${GETTEXT_INCLUDE_DIR})
find_package(Boost COMPONENTS iostreams REQUIRED)
pkg_check_modules(LIBXERCES REQUIRED xerces-c)
include_directories(${LIBXERCES_INCLUDE_DIR})

list(APPEND LIBS ${GETTEXT_LIBRARY} ${LIBXERCES_LIBRARIES})

set(GRAPH_SRC graph/nodeparser.cpp graph/externaldependencyresolver.cpp
graph/node.cpp graph/externaldependency.cpp graph/dummyexternaldependencymapper.cpp graph/externaldependencymapper.cpp
graph/nodesax2handler.cpp graph/mapsax2handler.cpp graph/mapparser.cpp
graph/graph.cpp)
set(GRAPH_EXCEPTIONS graph/exceptions/graphexception.cpp graph/exceptions/externalmappingexception.cpp
graph/exceptions/unknownmapexception.cpp graph/exceptions/parserexception.cpp graph/exceptions/invalidparserrequestexception.cpp)
list(APPEND GRAPH_SRC ${GRAPH_EXCEPTIONS})

set(SPACE_SRC space/space.cpp)

set(IO_SRC util/io/resourcereference.cpp util/io/file.cpp util/io/directory.cpp)
set(IO_EXCEPTION util/io/exception/filesystemexception.cpp util/io/exception/filesystemopenexception.cpp)
list(APPEND IO_SRC ${IO_EXCEPTION})

set(XML_SRC util/xml/xercessax2parser.cpp util/xml/xercesparser.cpp)

set(CLI_SRC cli/argumentparser.cpp cli/interstateargument.cpp cli/statechangeargument.cpp cli/argument.cpp cli/argumentparserstate.cpp)

if(PACKAGEKIT_GLIB2)
        pkg_check_modules(LIBDBUSGLIB REQUIRED dbus-glib-1)
        list(APPEND GRAPH_SRC graph/packagekitinterface.cpp)
        list(APPEND LIBS ${LIBDBUSGLIB_LIBRARIES})
        include_directories(${LIBDBUSGLIB_INCLUDE_DIRS})
endif(PACKAGEKIT_GLIB2)

add_executable(hive main.cpp  ${PROTO_SRCS} ${PROTO_HDRS} ${GRAPH_SRC} ${IO_SRC} ${SPACE_SRC} ${L10N_SRC}
${CLI_SRC} ${XML_SRC} util/exception/hiveexception.cpp)
target_link_libraries(hive ${LIBS})
