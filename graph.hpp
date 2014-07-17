#include <vector>
#include <memory>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


class graph
{
	private:
		boost::numeric::ublas::matrix<int> m;

	public:
		graph();
		addEdge(int,int);

}
