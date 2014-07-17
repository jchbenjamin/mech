#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <boost/graph/adjacency_list.hpp>

namespace mech {
	using std::shared_ptr;
	using std::vector;

//auction item
class itemRep {
	private:
		std::string desc; //description
		int order;
	public:
		itemRep(const std::string d, const int o) : order(o), desc(d) {};
};

typedef shared_ptr< itemRep > item;

class orderRep {
	private:
		int value;
		item before;
		item after;
		bool active;
	public:
		orderRep(const item a, const item b, const int v) : after(a), before(b), value(v) { active = false; };
};

typedef shared_ptr< orderRep > order;


class mechRep {
	private:
		std::vector< order > orders;
		std::vector< item > items;
		//boost::adjacency_list<> graph;
	public:
		mechRep(void) {};
		void addOrder(const order);
		void addItem(const item);
		std::vector< item> solve();
};

typedef shared_ptr< mechRep > mech;

int testfunc(void);

};
