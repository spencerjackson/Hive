
option(PACKAGEKIT_GLIB2 "Use glib2" ON)

set(GRAPH_SRC graph/externaldependencyresolver.cpp graph/node.cpp graph/externaldependency.cpp
graph/dummyexternaldependencymapper.cpp)

if(PACKAGEKIT_GLIB2)
        include(FindPkgConfig)
        pkg_check_modules(LIBDBUSGLIB REQUIRED dbus-glib-1)
        list(APPEND GRAPH_SRC graph/packagekitinterface.cpp)
        list(APPEND LIBS ${LIBDBUSGLIB_LIBRARIES})
        include_directories(${LIBDBUSGLIB_INCLUDE_DIRS})
endif(PACKAGEKIT_GLIB2)

add_executable(hive main.cpp ${GRAPH_SRC})
target_link_libraries(hive ${LIBS})
