#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <unordered_map>
#include <string>
#include <unordered_set>

using namespace std;

struct Node {
    string id;
    unordered_set<string> neighbours;
    Node(){};
    Node(const string &id) : id(id) {}
    void add_edge(const string &neighbour) {
        neighbours.insert(neighbour);
    }
    string get_neighbours() const {
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


struct Graph {
    unordered_map<string, Node> nodes;
    Graph() {};
    void add_node(const string &node) {
        nodes.insert(make_pair(node, Node(node)));;
    }
    void add_edge(const string &node1, const string &node2) {
        nodes[node1].add_edge(node2);
        nodes[node2].add_edge(node1);
    }

    string __str__ () const {
        string res;
        string middle(" : ");
        string newline("\n");

        for (auto i : nodes) {
            res += i.first + middle + i.second.get_neighbours() + newline;
        }
        res.resize(res.size()-1);
        return res;
    }

};


namespace py = pybind11;

PYBIND11_MODULE(node, m) {
    py::class_<Node>(m, "Node")
        .def(py::init<const string &>())
        .def("__str__", &Node::__str__)
        .def("add_edge", &Node::add_edge);
}

PYBIND11_MODULE(graph, m) {
    py::class_<Graph>(m, "Graph")
        .def(py::init<>())
        .def("add_node", &Graph::add_node)
        .def("__str__", &Graph::__str__)

        .def("add_edge", &Graph::add_edge);
}