
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

class Graph {
public:
    void addUser(const std::string& user);
    void addFriendship(const std::string& u1, const std::string& u2);
    std::vector<std::string> getFriends(const std::string& user) const;
    std::vector<std::string> getAllUsers() const;
    bool hasUser(const std::string& user) const;
private:
    std::unordered_map<std::string, std::vector<std::string>> adj;
};

#endif // GRAPH_H


