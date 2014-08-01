#ifndef __MECH_HPP__
#define __MECH_HPP__

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include "graph.hpp"

namespace mech {

	using std::shared_ptr;
	using std::vector;
	using std::list;

class orderRep {
	public:
		item before;
		item after;
		int value;
		orderRep(item b, item a, int v) : before(b), after(a), value(v) { }
};

class mechRep {
	private:
		graph g;
		list< item > solution;
		vector< orderRep > orders;
		void topoSort(graph);
		void topoVisit(node);
		void fillOrders(graph);

	public:
		mechRep(void);
		void addOrder(const item, const item, const int);
		void addItem(const item);
		void solve();
};

typedef shared_ptr< mechRep > mechanism;

};

#endif
