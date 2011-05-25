
option(PACKAGEKIT_GLIB2 "Use glib2" ON)

set(GRAPH_SRC graph/externaldependencyresolver.cpp graph/node.cpp graph/externaldependency.cpp
graph/dummyexternaldependencymapper.cpp)

add_executable(hive ${GRAPH_SRC})
target_link_libraries(hive ${LIBS})
