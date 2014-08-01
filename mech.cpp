#include "mech.hpp"

namespace mech {

mechRep::mechRep(void)
{
	g = graph(new graphRep());
}

void mechRep::topoSort(graph s)
{
	vector< node >::iterator it;
	for(it = s->nodes.begin(); it != s->nodes.end(); ++it)
	{
		(*it)->color = white;
	}
	for(it = s->nodes.begin(); it != s->nodes.end(); ++it)
	{
		if( (*it)->color == white )
		{
			topoVisit(*it);
		}
	}
	return;
}

void mechRep::topoVisit(node v)
{
	std::cout << "DFSvisit  " << v->getItem()->print() << "\n";
	v->color = gray;
	for(vector< edgeRep >::iterator it = v->edges.begin(); it != v->edges.end(); ++it)
	{
		if(it->getNode()->color == white)
		{
			topoVisit(it->getNode());
		}
		else if(it->getNode()->color == gray)
		{
//			std::cout << "the next is gray! fail! something terrible has happened!!! NOT A DAG\n";
			return;
		}
	}
//	std::cout << "coloring black\n";
	v->color = black;
	solution.push_front(v->getItem());
	return;
}


void mechRep::addOrder(const item before, const item after, const int value) //if an item not in graph then graph adds a node. all items repped in graph object
{
	if(before == after) {
		return; //no orders to same
	}
	g->addOrder(before, after, value);
}

void mechRep::addItem(const item i)
{
	g->addItem(i);
}

void mechRep::fillOrders(graph o)
{
	for(vector< node >::iterator i = o->nodes.begin(); i != o->nodes.end(); ++i)
	{
		for(vector<edgeRep>::iterator j = (*i)->edges.begin(); j != (*i)->edges.end(); ++j)
		{
			orderRep order = orderRep((*i)->getItem(),j->getNode()->getItem(),j->getVal());
			orders.push_back(order);
		}
	}

}
void mechRep::solve(void)
{
	graph o = g->optimize();

	std::cout << "OK WE ARE HERE\n";
	//o is sorted graph that has workable set of orders	
	int v = o->getTotalValue();
	std::cout << "Value of orders: " << v << std::endl;
	topoSort(o);
	fillOrders(o);

	for(list< item >::iterator it = solution.begin(); it != solution.end(); ++it)
	{
		std::cout << (*it)->print() << "\n";
	}
	for(vector< orderRep >::iterator it = orders.begin(); it != orders.end(); ++it)
	{
		std::cout << it->before->print() << "->" << it->after->print() << ": " << it->value << "\n";
	}
	
}

};
