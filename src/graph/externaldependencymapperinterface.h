#ifndef EXTERNALDEPENDENCYMAPPERINTERFACE_H
#define EXTERNALDEPENDENCYMAPPERINTERFACE_H
#include "externaldependency.h"

namespace hive {

class ExternalDependencyMapperInterface {
public:
	ExternalDependencyMapperInterface() {}
	virtual ~ExternalDependencyMapperInterface() {}

	virtual std::string map(std::string const& package_name) const = 0;
};
} //hive

#endif //EXTERNALDEPENDENCYMAPPERINTERFACE_H