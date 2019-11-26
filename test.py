#!/usr/bin/env python
from graph import Graph

G = Graph()
G.add_node("first")
G.add_node("second")
G.add_node("third")
G.add_node("fourth")

G.add_edge("first", "second")
G.add_edge("first", "third")
G.add_edge("third", "fourth")
print(G)
print()
G.remove_node("third")
print(G)