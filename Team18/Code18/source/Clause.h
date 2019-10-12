#pragma once
#include <string>
#include <vector>

class Clause {
public:
	Clause(std::string type, std::vector<std::string> fields);
	std::string getType() const;
	std::vector<std::string> getFields() const;
	bool operator== (const Clause& other) const;
private:
	std::string type;
	std::vector<std::string> fields;
};
