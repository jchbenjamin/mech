#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <boost/graph/adjacency_list.hpp>

#include "mech.hpp"

/*
class ordering
{
	
};
*/

//BOOST EXAMPLE

using namespace boost;

int main(void)
{

	adjacency_list<listS, vecS, undirectedS> g;
	add_edge(0,1,g);
	add_edge(0,3,g);
	add_edge(1,2,g);
	add_edge(2,3,g);

	return 0;
}

