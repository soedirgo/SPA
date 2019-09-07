#pragma once
#include <string>

class Clause {
public:
    Clause(std::string type, std::string lhs, std::string rhs);
    std::string getType();
    std::string getLhs();
    std::string getRhs();
private:
    std::string type;
    std::string lhs;
    std::string rhs;
};
