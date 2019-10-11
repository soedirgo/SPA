#include <string>
#include <vector>
#include "Clause.h"
using namespace std;

Clause::Clause(string type, vector<string> fields)
    : type(type), fields(fields) {}

string Clause::getType() const {
    return this->type;
}

vector<string> Clause::getFields() const {
    return this->fields;
}

bool Clause::operator== (const Clause& other) const {
    return this->type == other.getType()
        && this->fields == other.getFields();
}
