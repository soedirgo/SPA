#include <string>
#include <vector>
#include <utility>
#include "Entity.h"
#include "Evaluator.h"
#include "PKB.h"
#include "Query.h"
#include "Clause.h"
using namespace std;

// string Evaluator::evalQuery(Query q) {
//     Evaluator::declarations = q.getDeclarations();
//     clauses = q.getClause();
// }

namespace Evaluator {
    namespace {
        vector<pair<string, string> > declarations;
        vector<Clause> clauses;
    }

    string evalQuery(Query q) {
        Evaluator::declarations = q.getDeclarations();
        Evaluator::clauses = q.getClauses();

        for (auto iter = declarations.begin(); iter != declarations.end(); iter++) {
            pair<string, string> decl = *iter;
            cout << decl.second << " " << decl.first << "\n";
        }

        for (auto iter = clauses.begin(); iter != clauses.end(); iter++) {
            Clause clause = *iter;
            cout << clause.getType()
                 << "(" << clause.getLhs()
                 << " = " << clause.getRhs()
                 << ")\n";
        }
    }
}
