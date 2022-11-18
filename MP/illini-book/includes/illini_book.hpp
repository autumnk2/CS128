#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utilities.hpp"

class Graph {
public:
  Graph() = default;

  void AddVertex(int v) { graph_.insert({v, std::list<int>()}); }
  void AddEdge(int v1, int v2, const std::string& relation) {
    auto& v1_adj = graph_.at(v1);
    auto& v2_adj = graph_.at(v2);
    if (std::find(v1_adj.begin(), v1_adj.end(), v2) == v1_adj.end())
      v1_adj.push_back(v2);
    if (std::find(v2_adj.begin(), v2_adj.end(), v1) == v2_adj.end())
      v2_adj.push_back(v1);
    relations_.insert({std::to_string(std::min(v1, v2)) + "," +
                           std::to_string(std::max(v1, v2)),
                       relation});
  }
  bool AreAdj(int v1, int v2) const {
    return (std::find(graph_.at(v1).begin(), graph_.at(v1).end(), v2) !=
            graph_.at(v1).end()) &&
           (std::find(graph_.at(v2).begin(), graph_.at(v2).end(), v1) !=
            graph_.at(v2).end());
  }
  bool VertexInGraph(int v) const { return graph_.contains(v); }
  std::list<int>& GetAdjList(int v) { return graph_.at(v); }
  int HasPath(int v1, int v2) const {
    std::set<int> visited;
    std::queue<int> q;
    size_t q_size = 0;
    int step = 0;
    q.push(v1);
    visited.insert(v1);
    while (!q.empty()) {
      q_size = q.size();
      ++step;
      for (size_t i = 0; i < q_size; ++i) {
        int v = q.front();
        q.pop();
        const auto& adj_list = graph_.at(v);
        for (const auto& adj : adj_list) {
          if (!visited.contains(adj)) {
            if (adj == v2) return step;
            q.push(adj);
            visited.insert(adj);
          }
        }
      }
    }
    return -1;
  }
  int HasPath(int v1, int v2, const std::string& relation) const {
    std::set<int> visited;
    std::queue<int> q;
    size_t q_size = 0;
    int step = 0;
    q.push(v1);
    visited.insert(v1);
    while (!q.empty()) {
      q_size = q.size();
      ++step;
      for (size_t i = 0; i < q_size; ++i) {
        int v = q.front();
        q.pop();
        const auto& adj_list = graph_.at(v);
        for (const auto& adj : adj_list) {
          if (!visited.contains(adj) &&
              relations_.at(std::to_string(std::min(v, adj)) + "," +
                            std::to_string(std::max(v, adj))) == relation) {
            if (adj == v2) return step;
            q.push(adj);
            visited.insert(adj);
          }
        }
      }
    }
    return -1;
  }
  std::vector<int> VerticesReachedByNSteps(int vertex, int n) const {
    std::vector<int> res;
    std::set<int> visited;
    std::queue<int> q;
    size_t q_size = 0;
    int step = 0;
    q.push(vertex);
    visited.insert(vertex);
    while (!q.empty()) {
      q_size = q.size();
      ++step;
      for (size_t i = 0; i < q_size; ++i) {
        int v = q.front();
        q.pop();
        const auto& adj_list = graph_.at(v);
        for (const auto& adj : adj_list) {
          if (!visited.contains(adj)) {
            if (step == n) res.push_back(adj);
            q.push(adj);
            visited.insert(adj);
          }
        }
      }
      if (step == n) return res;
    }
    return res;
  }
  size_t CountParts() const {
    size_t cnt = 0;
    std::set<int> visited;
    for (const auto& list : graph_) {
      if (!visited.contains(list.first)) {
        ++cnt;
        std::queue<int> q;
        q.push(list.first);
        visited.insert(list.first);
        while (!q.empty()) {
          int v = q.front();
          q.pop();
          for (const auto& adj : graph_.at(v)) {
            if (!visited.contains(adj)) {
              q.push(adj);
              visited.insert(adj);
            }
          }
        }
      }
    }
    return cnt;
  }
  size_t CountPartsWithFilter(const std::string& relationship) const {
    size_t cnt = 0;
    std::set<int> visited;
    for (const auto& list : graph_) {
      if (!visited.contains(list.first)) {
        ++cnt;
        std::queue<int> q;
        q.push(list.first);
        visited.insert(list.first);
        while (!q.empty()) {
          int v = q.front();
          q.pop();
          for (const auto& adj : graph_.at(v)) {
            if (!visited.contains(adj) &&
                relations_.at(std::to_string(std::min(v, adj)) + "," +
                              std::to_string(std::max(v, adj))) ==
                    relationship) {
              q.push(adj);
              visited.insert(adj);
            }
          }
        }
      }
    }
    return cnt;
  }
  size_t CountPartsWithFilters(
      const std::vector<std::string>& relationships) const {
    size_t cnt = 0;
    std::set<int> visited;
    for (const auto& list : graph_) {
      if (!visited.contains(list.first)) {
        ++cnt;
        std::queue<int> q;
        q.push(list.first);
        visited.insert(list.first);
        while (!q.empty()) {
          int v = q.front();
          q.pop();
          for (const auto& adj : graph_.at(v)) {
            if (!visited.contains(adj) &&
                std::find(relationships.begin(),
                          relationships.end(),
                          relations_.at(std::to_string(std::min(v, adj)) + "," +
                                        std::to_string(std::max(v, adj)))) !=
                    relationships.end()) {
              q.push(adj);
              visited.insert(adj);
            }
          }
        }
      }
    }
    return cnt;
  }
  void Print() const {
    std::cout << "==============================\nGraph: \n";
    for (const auto& pair : graph_) {
      std::cout << " | {" << pair.first << "} | ";
      for (auto& adj : pair.second) std::cout << " -> {" << adj << "}";
      std::cout << '\n';
    }
    std::cout << "==============================\n";
  }

private:
  std::map<int, std::list<int>> graph_;
  std::map<std::string, std::string> relations_;
};

class IlliniBook {
public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath);
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string& relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string& relationship) const;
  size_t CountGroups(const std::vector<std::string>& relationships) const;

  void Print() const { graph_.Print(); }

private:
  Graph graph_;
};

#endif
