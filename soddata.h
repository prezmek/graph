#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <set>

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

    std::vector<Node>& GetNodes() { return nodes; }
    std::vector<Edge>& GetEdges() { return edges; }

    bool has_coordinates {false};
private:
    std::vector<Edge> edges;
    std::vector<Node> nodes;

    int AddNode(std::string category, std::string value, double x = 0, double y = 0);
};

#endif // DATA_H
