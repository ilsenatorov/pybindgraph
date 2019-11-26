#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <map>
#include <string>
#include <set>

using namespace std;

class Node {
    private:
    string id;
    set<string> neighbours;
    public:
    Node(){};
    ~Node(){};
    Node(const string &id) : id(id) {}
    void add_edge(const string &neighbour) {
        neighbours.insert(neighbour);
    }

    void remove_edge(const string &node) {
        neighbours.erase(node);
    }

    bool has_edge_to(const string &node) const {
        return neighbours.count(node);
    }

    bool has_neighbours() const {
        return !(neighbours.empty());
    }

    set<string> get_neighbours() const {
        return neighbours;
    }

    string print_neighbours() const {
        if (neighbours.empty()) {
            return "[]";
        }
        string res("[");
        string comma(", ");
        for (auto i : neighbours) {
            res += i + ", ";
        }
        res.resize(res.size()-2);
        res += "]";
        return res;
    }
    int degree() const {
        return neighbours.size();
    }
};


class Graph {
    private:
    map<string, Node> nodes;
    public:
    Graph() {};
    ~Graph(){};

    void add_node(const string &node) {
        nodes[node] = Node(node);
    }

    void add_edge(const string &node1, const string &node2) {
        nodes[node1].add_edge(node2);
        nodes[node2].add_edge(node1);
    }

    void remove_node(const string &node) {
        if (nodes[node].has_neighbours()) {
            for (auto i : nodes[node].get_neighbours()) {
                nodes[i].remove_edge(node);
            }
        }
        nodes.erase(node);
    }

    void remove_edge(const string &node1, const string &node2) {
        nodes[node1].remove_edge(node2);
        nodes[node2].remove_edge(node1);
    }

    bool has_edge(const string &node1, const string &node2) {
        return nodes[node1].has_edge_to(node2);
    }

    int size() const {
        return nodes.size();
    }

    string __str__ () const {
        string res;
        string middle(" : ");
        string newline("\n");
        for (auto i : nodes) {
            res += i.first + middle + i.second.print_neighbours() + newline;
        }
        res.resize(res.size()-1);
        return res;
    }
};


namespace py = pybind11;
PYBIND11_MODULE(node, m) {
    py::class_<Node>(m, "Node")
        .def(py::init<const string &>())
        .def("add_edge", &Node::add_edge)
        .def("remove_edge", &Node::remove_edge)
        .def("has_edge_to", &Node::has_edge_to)
        .def("degree", &Node::degree);
}

PYBIND11_MODULE(graph, m) {
    py::class_<Graph>(m, "Graph")
        .def(py::init<>())
        .def("add_node", &Graph::add_node)
        .def("add_edge", &Graph::add_edge)
        .def("remove_node", &Graph::remove_node)
        .def("remove_edge", &Graph::remove_edge)
        .def("has_edge", &Graph::has_edge)
        .def("size", &Graph::size)
        .def("__str__", &Graph::__str__);
}