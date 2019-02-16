#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

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
        Node(std::string name, std::string category, std::string value)
            : name(name)
            , category(category)
            , value(value)
        {}
        std::string name;
        std::string category;
        std::string value;
    };

    std::vector<Node>& GetNodes() { return nodes; }
    std::vector<Edge>& GetEdges() { return edges; }

private:
    std::vector<Edge> edges;
    std::vector<Node> nodes;

    int AddNode(std::string category, std::string value);
};

#endif // DATA_H
