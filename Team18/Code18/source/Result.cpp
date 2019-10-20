#include "Result.h"
#include "AbstractType.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
namespace Evaluator {
    Result::Result(bool resExists,
                   unordered_map<string, int> syn,
                   TABLE res)
        : resultExists(resExists),
          synonyms(syn),
          results(res) {}

    Result Result::merge(Result& r1, Result& r2) {
        bool resultExists = r1.hasResults() && r2.hasResults();
        if (!r1.getResults().size()) {
            if (!r2.getResults().size()) {
                // both empty
                return Result(resultExists, {}, {});
            } else {
                // only r1 empty
                return Result(resultExists, r2.getSynonyms(), r2.getResults());
            }
        } else if (!r2.getResults().size()) {
            // only r2 empty
            return Result(r1.hasResults() && r2.hasResults(),
                          r1.getSynonyms(), r1.getResults());
        } else {
            // both non-empty
            unordered_map<string, int> r1Synonyms = r1.getSynonyms();
            unordered_map<string, int> r2Synonyms = r2.getSynonyms();
            unordered_map<string, int> synonyms = r1Synonyms;
            vector<string> overlappingSynonyms;
            vector<string> newSynonyms;
            for (const auto& it : r2Synonyms) {
                if (r1Synonyms.count(it.first)) {
                    overlappingSynonyms.push_back(it.first);
                } else {
                    newSynonyms.push_back(it.first);
                    synonyms[it.first] = synonyms.size();
                }
            }

            TABLE results;
            for (auto r1e : r1.getResults()) {
                for (auto r2e : r2.getResults()) {
                    // if overlaps don't match, continue
                    bool overlapMatches = true;
                    for (const auto& syn : overlappingSynonyms) {
                        if (r1e[r1Synonyms[syn]] != r2e[r2Synonyms[syn]]) {
                            overlapMatches = false;
                            break;
                        }
                    }
                    if (!overlapMatches) {
                        continue;
                    }

                    // cross-product new synonyms
                    vector<string> mergedResult = r1e;
                    for (const auto& syn : newSynonyms) {
                        mergedResult.push_back(r2e[r2Synonyms[syn]]);
                    }
                    results.insert(mergedResult);
                }
            }

            return Result(resultExists, synonyms, results);
        }
    }

    bool Result::hasResults() const {
        return this->resultExists;
    }

    unordered_map<string, int> Result::getSynonyms() const {
        return this->synonyms;
    }

    TABLE Result::getResults() const {
        return this->results;
    }
} // namespace Evaluator
