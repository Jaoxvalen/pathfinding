#pragma once
#include "CGraph.h"
#include <vector>

using namespace std;

namespace DS
{

	template<class G>
	class CNode
	{
		public :

		typedef typename G::NodeData N;
		typedef typename G::Edge Edge;
		
        int id;
        bool isVisit=false;
        //bool isClose=false;
        //bool isOpen=false;
        bool isAlone=false;
        int idCluster;
		N data;
		vector<Edge*> edges;
		vector<Edge*> edges_back;

		CNode( N node_data, int _id )
		{
            id=_id;
			data = node_data;
		}
	};
	
}