#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <string>

class RecommendationEngine {
public:
    RecommendationEngine(const Graph& graph,
        const std::unordered_map<std::string,std::vector<std::string>>& interests);

    // Returns top N recommendations as (username, score)
    std::vector<std::pair<std::string,int>> recommend(const std::string& user, int topN=5);

private:
    const Graph& g;
    std::unordered_map<std::string,std::vector<std::string>> interests;

    int countMutualFriends(const std::string& u1, const std::string& u2) const;
    int countSharedInterests(const std::string& u1, const std::string& u2) const;
};

#endif // RECOMMENDATION_ENGINE_H