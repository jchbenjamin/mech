#include "graph.hpp"

namespace mech {

/*
void nodeRep::addEdge(node i)
{
//	std::list::iterator it;
//	bool in = false;
//	for(it = edges.begin(); it != edges.end(); ++it)
//	{
//		if( (*it) == i )
//		{
//			in = true;
//			break;
//		}
//	}

	edges.push_back(i);
}
*/
/*
node nodeRep::copy(void)
{
	node n = node(new nodeRep(this->myItem));
	return n;
}
*/

void nodeRep::addEdge(const node a, const int v)
{
	incoming++;
	edges.push_back(edgeRep(a,v));
}
/*
void nodeRep::delEdge(const node a, const int v)
{
	incoming--;
	for(list< edgeRep >::iterator it = edges.begin();it!=edges.end();++it)
	{
		if( a == it->edgeTo ) { edges.remove(it); }
	}
	edgeRep p = edgeRep(a,v);
	edges.remove(p);
}
*/

void graphRep::sortNodesByIncoming(void)
{
	sort(
		nodes.begin(),
		nodes.end(),
		[](node const & a, node const & b) -> bool
		{ return a->getIncoming() < b->getIncoming(); }
	);
}

/*
graph graphRep::copyWithout(const edge e)
{
	graphRep& thisP = *this;
	graph g = graph(new graphRep(thisP));
	vector< node >::iterator it;
	for(it = g->nodes.begin(); it != g->nodes.end(); ++it)
	{
		if((*it) == e->before)
		{
			(*it) = (*it)->copyWithout(e->after);
			break;
		}
	}
	g->edges.remove(e);
	return g;
}
*/
node graphRep::checkAddNode(const item a)
{
	vector< node >::iterator it;
	for(it = nodes.begin(); it != nodes.end(); ++it)
	{
		if((*it)->myItem == a)
		{
			return *it;
		}
	}
	node n = node(new nodeRep(a));
	nodes.push_back(n);
	return n;
}

void graphRep::addNode(const item a)
{
	node n = node(new nodeRep(a));
	nodes.push_back(n);
}

void graphRep::addItem(const item a)
{
	node n = checkAddNode(a);
}

bool graphRep::hasCycle(void)
{
//	std::cout << "start hasCycle\n";
	sortNodesByIncoming();
	vector< node >::iterator it;
/*	 not necessary since this DFS run only once per graph and node color always initialized to white on copy
	for(it = nodes.begin(); it != nodes.end(); ++it)
	{
		(*it)->color = white;
	}
*/
	for(it = nodes.begin(); it != nodes.end(); ++it)
	{
		if( (*it)->color == white )
		{
			if(DFSvisit(*it))
			{
//				std::cout << "finished true!\n";
				return true;
			}
		}
	}
//	std::cout << "no cycle detected!\n";
	return false;
}

bool graphRep::DFSvisit(node v)
{
//	std::cout << "DFSvisit  " << v->getItem()->print() << "\n";
	v->color = gray;
	for(vector< edgeRep >::iterator it = v->edges.begin(); it != v->edges.end(); ++it)
	{
		if(it->getNode()->color == white)
		{
			if(DFSvisit(it->getNode()))
			{
//				std::cout << "going along white path" << v->getItem()->print();
				return true;
			}
		}
		else if(it->getNode()->color == gray)
		{
//			std::cout << "the next is gray! fail!\n";
			return true;
		}
	}
//	std::cout << "coloring black\n";
	v->color = black;
	return false;
}

void graphRep::addOrder(const item b, const item a, const int v)
{
	if(b == a) { return; } //no self-cycles allowed!!!
	vector< node >::iterator it;
	node nB = checkAddNode(b);
	node nA = checkAddNode(a);
	
	for(it = nodes.begin(); it != nodes.end(); ++it)
	{
		if(*it == nB)
		{
			for(vector< edgeRep >::iterator j = (*it)->edges.begin(); j != (*it)->edges.end(); ++j)
			{
				if(j->getNode() == nA) { return; } //this is for case where edge already exists
			}
			(*it)->edges.push_back( edgeRep(nA, v) );
			totalValue = totalValue + v;
			return;
		}
	}
	return;
}

void graphRep::nodeAddOrder(const node b, const node a, const int v)
{
	node nA;
	for(vector< node >::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		if((*it)->getItem() == a->getItem())
		{
			nA = *it;
			break;
		}
	}
	for(vector< node >::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		if((*it)->getItem() == b->getItem())
		{
			(*it)->edges.push_back( edgeRep(nA,v) );
			totalValue = totalValue + v;
			return;
		}
	}
}

graph graphRep::copyWithout(const int nodeNum, const int edgeNum)
{
	int n = 0;
	int e = 0;
	graph g = graph(new graphRep());

	for( vector< node >::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		g->addNode( (*it)->myItem );
	}

	for( vector< node >::iterator it = nodes.begin(); it != nodes.end(); ++it, ++n)
	{
		e=0;
		for( vector< edgeRep >::iterator j = (*it)->edges.begin(); j != (*it)->edges.end(); ++j,++e)
		{
			if( n != nodeNum || e != edgeNum )
			{
//				std::cout << "ADDING LINKE" << n << " " << e << "\n";
				g->nodeAddOrder((*it),	(j)->getNode(), (j)->getVal() );
			}
		}
	}	
	return g;
}

void nodeRep::printNode(void) 
{
	std::cout << "NODE: " << myItem->print() << " has:\n";
	if(color == white) { std::cout << "white color\n"; }
	for(vector< edgeRep >::iterator it = edges.begin(); it != edges.end(); ++it)
	{
		std::cout << "\tEdge: " << it->getNode()->getItem()->print() << "\n";
	}
}

void graphRep::printGraph(void)
{
	std::cout << "\t\tGRAPH\n";
	for(vector<node>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		(*it)->printNode();
	}

}

graph graphRep::optimize(void)
{

//	std::cout << "!!! start optimize !!!\n";
//	printGraph();	
	sortNodesByIncoming();
	
	if( hasCycle() )
	{
//		std::cout << "optimize has scycle\n";
		int nodeNum=0;
		int edgeNum=0;
		int thisVal=0;	
		int maxVal = 0;
		graph top = 0;
		vector< node >::iterator it;
		for(it = nodes.begin(); it != nodes.end(); ++it, ++nodeNum)
		{
			edgeNum=0;
			vector< edgeRep >::iterator j;
			for(j = (*it)->edges.begin(); j!= (*it)->edges.end(); ++j, ++edgeNum)
			{
				graph n = this->copyWithout(nodeNum, edgeNum)->optimize();
				thisVal = n->getTotalValue();
				if(maxVal < thisVal)
				{
					maxVal = thisVal;
					top = n;
				}
			}
		}
		return top;
		
		//return graph(this);
	}
	else
	{
//		std::cout << "nocycle\n";
		graph g = graph(new graphRep(*this));
		return g;
	}
}

}
