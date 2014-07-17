//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee, 
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>

using namespace boost;

struct cycle_detector : public dfs_visitor<>
{
  cycle_detector( bool& has_cycle) : _has_cycle(has_cycle) { }

    template <class Edge, class Graph>
    void back_edge(Edge, Graph&) {
      _has_cycle = true;
    }
  protected:
    bool& _has_cycle;
  };

enum family
{ Jeanie, Debbie, Rick, John, Amanda, Margaret, Benjamin, N };
int
main()
{
  using namespace boost;
  const char *name[] = { "Jeanie", "Debbie", "Rick", "John", "Amanda",
    "Margaret", "Benjamin"
  };

  adjacency_list <> g(N);
  add_edge(Jeanie, Debbie, g);
  add_edge(Jeanie, Rick, g);
  add_edge(Jeanie, John, g);
  add_edge(Debbie, Amanda, g);
  add_edge(Rick, Margaret, g);
  add_edge(John, Benjamin, g);
  add_edge(Benjamin, Jeanie, g);

  graph_traits < adjacency_list <> >::vertex_iterator i, end;
  graph_traits < adjacency_list <> >::adjacency_iterator ai, a_end;
  property_map < adjacency_list <>, vertex_index_t >::type
    index_map = get(vertex_index, g);

  for (boost::tie(i, end) = vertices(g); i != end; ++i) {
    std::cout << name[get(index_map, *i)];
    boost::tie(ai, a_end) = adjacent_vertices(*i, g);
    if (ai == a_end)
      std::cout << " has no children";
    else
      std::cout << " is the parent of ";
    for (; ai != a_end; ++ai) {
      std::cout << name[get(index_map, *ai)];
      if (boost::next(ai) != a_end)
        std::cout << ", ";
    }
    std::cout << std::endl;
  }

  bool has_cycle = false;
  cycle_detector vis(has_cycle);
  boost::depth_first_search(g, visitor(vis));
  std::cout << "The graph has a cycle? " << has_cycle << std::endl;


  return EXIT_SUCCESS;
}
