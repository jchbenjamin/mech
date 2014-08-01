#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

#include "mech.hpp"


int main(void)
{

	using mech::item;
	using mech::mechanism;
	using mech::itemRep;
	using mech::mechRep;
	using mech::graph;
	using mech::graphRep;

	std::cout << "hello\n";

	mech::mechanism m = mech::mechanism(new mech::mechRep());


	item a = item(new itemRep("a"));
	item b = item(new itemRep("b"));
	item c = item(new itemRep("c"));
	item d = item(new itemRep("d"));
	item e = item(new itemRep("e"));
	item f = item(new itemRep("f"));
	item g = item(new itemRep("g"));


	m->addOrder(a,b,1);
	m->addOrder(b,c,10);
	m->addOrder(c,d,3);
	m->addOrder(d,e,5);
	m->addOrder(e,b,90);
	m->addOrder(e,c,3);
	m->addOrder(d,a,8);

	m->solve();

/*
	graph g = graph(new graphRep); 

	std::cout << "we heeerrrrre\n";
	g->addItem(a);
	g->addItem(b);
	g->addItem(c);
	g->addItem(d);
	g->addOrder(a,b,1);
	g->addOrder(b,c,2);
	g->addOrder(a,c,3);
	g->addOrder(b,d,2);
	g->addOrder(d,a,3);
	std::cout << "we here\n";

	graph h = g->optimize();
*/
	return 0;
}

