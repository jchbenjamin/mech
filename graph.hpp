#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include "mech.hpp"

namespace mech {

using std::list;
using std::vector;
using std::sort;
using std::shared_ptr;

enum color { white, gray, black };

class nodeRep;
class graphRep;

typedef shared_ptr< nodeRep > node;
typedef shared_ptr< graphRep > graph;

class nodeRep
{
	friend class graph;
	private:
		item myItem;
		list< node > edges;
		color c;
		int incoming;
	public:
		nodeRep(item i) : myItem(i), c(white), incoming(0) { };
		int getIncoming(void) { return incoming; };
		void incIncoming() { incoming++; };
		void decIncoming() { incoming--; };
		void addEdge(node);
		void delEdge(node);
		node copy(void);
};

class graphRep
{
	private:
		vector< node > nodes;
		void sortNodesByIncoming(void);
	public:
		graph();
		graph copyWithout(node&);
		void addNode(item);
		void addEdge(item,item);
		bool hasCycle();
		//DFS

};

}
