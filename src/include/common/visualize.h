#ifndef VISUALIZE_H__
#define VISUALIZE_H__
#include <string>
#include <iostream>
#include <map>
#include "glog/logging.h"

class Visualize {
private:
    std::string* store_graph;
    std::multimap<const std::string, const std::string>* map_store;
public:
    Visualize() {
        this->store_graph = new std::string("");
        this->map_store = new std::multimap<const std::string, const std::string>();
    }
    ~Visualize() {
        delete this->store_graph;
        delete this->map_store;
    }
    const std::string &output(void) {
        return *(this->store_graph);
    }
    void init_visualize(void) {
        *(this->store_graph) += "digraph G {\n";
    }
    void end_visualize(void) {
        *(this->store_graph) += "\n}\n";
    }
    void add_pair(const std::string& father, const std::string& child, bool add_mapping) {
        *(this->store_graph) += "  " + father + " -> " + child + "\n";
        if (add_mapping) {
            this->map_store->insert(std::make_pair(father, child));
        }
    }
    int find_map(const std::string& key, std::string& value_name) {
        int cnt = 0;
        for (auto it = map_store->begin(); it != map_store->end(); ++it) {
            if (it->first == key) {
                value_name = it->second;
                cnt++;
            }
        }

        return cnt;
    }
    void remove_map(const std::string& key, const std::string& value) {
        for (auto it = map_store->begin(); it != map_store->end(); ++it) {
            if (it->first == key && it->second == value) {
                this->map_store->erase(it);
                break;
            }
        }
    }
};
#endif