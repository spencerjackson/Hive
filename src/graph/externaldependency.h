#ifndef EXTERNALDEPENDENCY_H
#define EXTERNALDEPENDENCY_H

#include <string>

namespace hive {

class ExternalDependency {
public:
	ExternalDependency(const std::string& dependency_name);
	~ExternalDependency();

	std::string get_dependency_name() const;

private:
	std::string dependency_name;
};

} //hive

#endif // EXTERNALDEPENDENCY_H
