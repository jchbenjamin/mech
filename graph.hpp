#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>
#include <memory>
#include <list>
#include <set>
#include <algorithm>
#include <iostream>

namespace mech {

using std::list;
using std::vector;
using std::sort;
using std::shared_ptr;
using std::set;
using std::string;

enum nodeColor { white, gray, black };

class itemRep;
class nodeRep;
class graphRep;
class edgeRep;

typedef shared_ptr< itemRep > item;
typedef shared_ptr< nodeRep > node;
typedef shared_ptr< graphRep > graph;
typedef shared_ptr< edgeRep > edge;

class itemRep {
	private:
		string desc;
		int id; //key from database
	public:
		itemRep(const string d) : desc(d), id(0) { }
		itemRep(const string d, const int i) : desc(d), id(i) { }
		string print(void) const { return desc; }
};

class nodeRep
{
	friend class graphRep;
	friend class mechRep;
	private:
		item myItem;
		vector< edgeRep > edges;
		nodeColor color;
		int incoming;

	public:
		nodeRep(item i) : myItem(i), color(white), incoming(0) { }
		int getIncoming(void) const { return incoming; }
		void addEdge(const node, const int);
		void delEdge(const node);
		//void delEdge(const node, const int);
		item getItem(void) const { return myItem; }
		void printNode(void);
};

class edgeRep
{
	friend class graphRep;
	friend class nodeRep;
	friend class mechRep;
	private:
		node edgeTo;
		int value;
	public:
		edgeRep(node a, int v) : edgeTo(a), value(v) { }
		item getItem(void) const { return edgeTo->getItem(); }
		int getVal(void) const { return value; }
		node getNode(void) const { return edgeTo; }
};	

class graphRep
{
	friend class mechRep;
	private:
		vector< node > nodes;
		int totalValue;
		void sortNodesByIncoming(void);
		void addNode(item);
		node checkAddNode(item);
		void nodeAddOrder(node, node, int);
		bool DFSvisit(node);
		graph copyWithout(const int, const int);
	public:
		graphRep() : totalValue(0) { }

		void test(void);

		//interface for building mechanism
		void addItem(const item);
		void addOrder(const item,const item,const int);

		bool hasCycle();

		void printGraph(void);
		int getTotalValue(void) const { return totalValue; }
		graph optimize();
};

};

#endif
