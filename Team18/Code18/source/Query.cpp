#include <string>
#include "Query.h"
using namespace std;

string Query::getType() {
    return this.type;
}

string Query::getClause() {
    return this.clause;
}
