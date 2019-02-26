#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <set>
#include <algorithm>

class SodData
{
public:
    void ReadFile(char* filename);

    struct Edge {
        Edge(int l, int r, int w = 1) : l(l), r(r), w(w) {}
        int l;
        int r;
        int w;
    };

    struct Node {
        Node(std::string name, std::string category, std::string value, int x = 0, int y = 0)
            : name(name)
            , category(category)
            , value(value)
            , x(x)
            , y(y)
        {}
        std::string name;
        std::string category;
        std::string value;
        int x {0};
        int y {0};
        std::set<int> neighs;
    };

    struct Triple {
        int v1;
        int v2;
        int v3;

        Triple(int w1, int w2, int w3) {
            std::vector<int> v;
            v.push_back(w1);
            v.push_back(w2);
            v.push_back(w3);
            std::sort(v.begin(), v.end());
            v1 = v[0];
            v2 = v[1];
            v3 = v[2];
        }

        bool operator<(const Triple& c2) const {
            if(v1 < c2.v1)
                return true;
            if(v1 > c2.v1)
                return false;
            if(v2 < c2.v2)
                return true;
            if(v2 > c2.v2)
                return false;
            return v3 < c2.v3;
        }
    };

    std::vector<Node>& GetNodes() { return nodes; }
    std::vector<Edge>& GetEdges() { return edges; }
    std::vector<Triple> CalculateTriples();

    bool has_coordinates {false};
private:
    std::vector<Edge> edges;
    std::vector<Node> nodes;

    int AddNode(std::string category, std::string value, double x = 0, double y = 0);
};

#endif // DATA_H
