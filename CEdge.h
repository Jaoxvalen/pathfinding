#pragma once
#include "CGraph.h"

namespace DS
{

	template<class G>
	class CEdge
	{
		public :

		typedef typename G::EdgeData E;
		typedef typename G::Node Node;

		E data;
		Node* nodes[2];
		bool bidir;

		CEdge( E edge_data, bool edge_bidir )
		{
			data = edge_data;
			bidir = edge_bidir;
		}
	};
	
}