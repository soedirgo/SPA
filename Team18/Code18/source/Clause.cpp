#include <string>
#include "Clause.h"
using namespace std;

Clause::Clause(string type, string lhs, string rhs)
    : type(type), lhs(lhs), rhs(rhs) {}

string Clause::getType() {
    return this->type;
}

string Clause::getLhs() {
    return this->lhs;
}

string Clause::getRhs() {
    return this->rhs;
}
