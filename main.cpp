
#include <iostream>
#include "./Graph.h"
#include "./RecommendationEngine.h"
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void Graph::addUser(const string &user)
{
    if (!adj.count(user))
    {
        adj[user] = {};
    }
}

void Graph::addFriendship(const string &u1, const string &u2)
{
    addUser(u1);
    addUser(u2);
    auto &f1 = adj[u1];
    if (find(f1.begin(), f1.end(), u2) == f1.end())
        f1.push_back(u2);
    auto &f2 = adj[u2];
    if (find(f2.begin(), f2.end(), u1) == f2.end())
        f2.push_back(u1);
}

vector<string> Graph::getFriends(const string &user) const
{
    if (adj.count(user))
        return adj.at(user);
    return {};
}

vector<string> Graph::getAllUsers() const
{
    vector<string> users;
    users.reserve(adj.size());
    for (auto &kv : adj)
        users.push_back(kv.first);
    return users;
}

bool Graph::hasUser(const string &user) const
{
    return adj.count(user) > 0;
}

RecommendationEngine::RecommendationEngine(
    const Graph &graph,
    const unordered_map<string, vector<string>> &interestsMap) : g(graph), interests(interestsMap) {}

int RecommendationEngine::countMutualFriends(
    const string &u1, const string &u2) const
{
    auto f1 = g.getFriends(u1);
    auto f2 = g.getFriends(u2);
    unordered_set<string> set1(f1.begin(), f1.end());
    int count = 0;
    for (auto &f : f2)
        if (set1.count(f))
            ++count;
    return count;
}

int RecommendationEngine::countSharedInterests(
    const string &u1, const string &u2) const
{
    if (!interests.count(u1) || !interests.count(u2))
        return 0;
    auto &i1 = interests.at(u1);
    auto &i2 = interests.at(u2);
    unordered_set<string> set1(i1.begin(), i1.end());
    int count = 0;
    for (auto &it : i2)
        if (set1.count(it))
            ++count;
    return count;
}

vector<pair<string, int>> RecommendationEngine::recommend(
    const string &user, int topN)
{
    vector<pair<string, int>> results;
    if (!g.hasUser(user))
        return results;
    auto friends = g.getFriends(user);
    unordered_set<string> friendSet(friends.begin(), friends.end());
    for (auto &candidate : g.getAllUsers())
    {
        if (candidate == user)
            continue;
        if (friendSet.count(candidate))
            continue;
        int mf = countMutualFriends(user, candidate);
        int si = countSharedInterests(user, candidate);
        int score = mf * 10 + si;
        if (score > 0)
            results.emplace_back(candidate, score);
    }
    sort(results.begin(), results.end(),
         [](auto &a, auto &b)
         { return a.second > b.second; });
    if ((int)results.size() > topN)
        results.resize(topN);
    return results;
}

int main()
{
    Graph g;
    // Sample users
    g.addUser("Alice");
    g.addUser("Bob");
    g.addUser("Charlie");
    g.addUser("David");
    g.addUser("Eve");
    g.addUser("Frank");

    // Sample friendships
    g.addFriendship("Alice", "Bob");
    g.addFriendship("Alice", "Charlie");
    g.addFriendship("Bob", "David");
    g.addFriendship("Charlie", "Eve");
    g.addFriendship("David", "Eve");
    g.addFriendship("Eve", "Frank");

    // Sample interests
    unordered_map<string, vector<string>> interests = {
        {"Alice", {"Music", "Sports", "Reading"}},
        {"Bob", {"Movies", "Sports", "Cooking"}},
        {"Charlie", {"Music", "Art", "Travel"}},
        {"David", {"Travel", "Cooking", "Sports"}},
        {"Eve", {"Reading", "Art", "Music"}},
        {"Frank", {"Sports", "Gaming", "Movies"}}};

    RecommendationEngine engine(g, interests);

    string user;
    cout << "Enter username: ";
    cin >> user;

    auto recs = engine.recommend(user, 5);
    if (recs.empty())
    {
        cout << "No recommendations found for " << user << endl;
    }
    else
    {
        cout << "Top " << recs.size() << " recommendations for " << user << ":\n";
        for (auto &p : recs)
        {
            cout << " - " << p.first << " (score: " << p.second << ")\n";
        }
    }

    return 0;
}