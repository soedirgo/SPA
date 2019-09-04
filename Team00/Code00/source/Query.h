#include <string>

using namespace std;

class Query {
public:
    string getType();
    string getClause();
    Query(string type, string clause);
private:
    string type;
    // "such that" clause (if any, could be none: point to null)
    string clause;
}
