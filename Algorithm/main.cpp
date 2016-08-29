#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include "Node.h"

struct NodePath
{
	Node inNode;
	Node toNode;
	int weigth;
};


typedef std::vector<Node> ArrayCitys;
typedef std::vector<NodePath> ArrayRoads;

NodePath GetRoad(ArrayRoads roads, Node inNode, Node toNode);
ArrayRoads GetRoads(ArrayRoads roads, Node node, std::set<Node> old);
ArrayRoads GetRoads(ArrayRoads roads, Node node);

int SumPathCities(Node start, Node goal, ArrayRoads roads, ArrayCitys citys)
{
	int result = 0;

	std::queue<Node> queryTop;
	queryTop.push(start);

	std::map<Node, bool> usedCity;
	usedCity[start] = true;

	Node falseCity{};

	std::set<Node> oldCity;
	oldCity.insert(start);

	ArrayRoads currentRoad = GetRoads(roads, start);

	while (!queryTop.empty())
	{
		Node vertex = queryTop.front();
		queryTop.pop();
		currentRoad = GetRoads(roads, vertex);

		for (auto road : currentRoad)
		{
			if (!usedCity[road.toNode])
			{
				usedCity[road.toNode] = true;
				queryTop.push(road.toNode);
				
			}

		}
	}

	if (!usedCity[goal])
		std::cout << "No path!";
	else {
		std::vector<Node> path;
		
		reverse(path.begin(), path.end());


		for (size_t i = 1; i < path.size(); ++i)
			result += GetRoad(roads, path[i - 1], path[i]).weigth;

	}
	return result;
}


NodePath GetRoad(ArrayRoads roads, Node inNode, Node toNode)
{
	ArrayRoads currentRoads = GetRoads(roads, inNode);
	NodePath result;
	for (auto road : currentRoads)
	{
		if (road.toNode == toNode)
		{
			result = road;
			break;
		}
	}
	return result;
}

ArrayRoads GetRoads(ArrayRoads roads, Node node, std::set<Node> old)
{
	auto arrayRoads = GetRoads(roads, node);
	ArrayRoads result;

	for (auto road : arrayRoads)
	{
		bool add = true;
		for (auto usedCity : old)
		{
			if (road.toNode == usedCity)
			{
				add = false;
				break;
			}
		}
		if (add)
			result.push_back(road);
	}
	return result;
}

ArrayRoads GetRoads(ArrayRoads roads, Node node)
{
	ArrayRoads result;
	for (auto road : roads)
		if (node == road.inNode)
			result.push_back(road);
	return result;
}

//ArrayRoadsTotalCost GetTotalCostRoads(ArrayRoads roads, ArrayCitys citys, int beforeCost) {
//	ArrayRoadsTotalCost result;
//	for (auto it : roads) {
//		result.push_back({
//			it.in,
//			it.to,
//			it.cost + citys[it.to].range + beforeCost
//		});	
//	}
//	return result;
//}

//vector<City> A(int start, int goal, ArrayRoads roads, ArrayCitys citys) {
//
//	ArrayRoadsTotalCost myPath;
//	ArrayRoadsTotalCost otherPath;
//
//	set<int> usedCity;
//	usedCity.insert(start);
//	int beforeCost = 0;
//	int currentCity = start;
//
//	while (currentCity != goal) {
//		ArrayRoads currentRoad = GetRoads(roads, currentCity, usedCity);
//
//		ArrayRoadsTotalCost currentRoadsTotlCost = GetTotalCostRoads(currentRoad, citys, beforeCost);
//
//		RoadTotalCost min_before;
//
//
//		RoadTotalCost min_iterator = *min_element(currentRoadsTotlCost.begin(), currentRoadsTotlCost.end(), [](RoadTotalCost a, RoadTotalCost b) -> bool {
//			return (a.totalCost < b.totalCost);
//		});
//
//		
//		
//		for(size_t i= 0; i < currentRoadsTotlCost.size(); i++)
//		{
//			RoadTotalCost it = currentRoadsTotlCost[i];
//			if ((it.in == min_iterator.in)
//				&& (it.to == min_iterator.to)
//				&& (it.totalCost == min_iterator.totalCost))
//			{
//				currentRoadsTotlCost.erase(currentRoadsTotlCost.begin() + i);
//				break;
//			}
//		}	
//		myPath.push_back(min_iterator);
//
//		otherPath.insert(otherPath.end(), currentRoadsTotlCost.begin(), currentRoadsTotlCost.end());
//		if (!otherPath.empty())
//			min_before = *min_element(otherPath.begin(), otherPath.end(), [](RoadTotalCost a, RoadTotalCost b) -> bool {
//			return (a.totalCost < b.totalCost);
//		});
//
//		if (min_before.totalCost < min_iterator.totalCost) {
//			otherPath.push_back(min_iterator);
//			min_iterator = min_before;
//			for (size_t i = 0; i < otherPath.size(); i++)
//			{
//				RoadTotalCost it = otherPath[i];
//				if ((it.in == min_iterator.in)
//					&& (it.to == min_iterator.to)
//					&& (it.totalCost == min_iterator.totalCost))
//				{
//					otherPath.erase(otherPath.begin() + i);
//					break;
//				}
//			}
//		}
//		currentCity = min_iterator.to;
//		usedCity.insert(min_iterator.to);
//		beforeCost = SumPathCities(start, min_iterator.to, roads, citys);
//	
//		
//		std::cout <<  citys[min_iterator.to].name[0] << "-";
//		
//	}
//	std::cout << endl;
//	
//	return vector<City>();
//}

void main()
{
	ArrayCitys citys = {
		{ "Arard", 366 },	    //0
		{ "Bucharest", 0 },     //1
		{ "Craiova", 160 },	    //2
		{ "Drobeta", 242 },		//3
		{ "Eforie", 161 },		//4
		{ "Fagaras", 176 },		//5
		{ "Giurgiu", 77 },		//6
		{ "Hirsiva", 151 },		//7
		{ "Iasi", 226 },		//8
		{ "Lugoj", 244 },		//9
		{ "Mehadia", 241 },		//10
		{ "Neamt", 234 },		//11
		{ "Oradea", 380 },		//12
		{ "Pitesti", 100 },		//13
		{ "RimnicuVilcea", 193 },//14
		{ "Sibiu", 253 },		//15
		{ "Timisoara", 329 },	//16
		{ "Urziceni", 80 },		//17
		{ "Vaslui", 199 },		//18
		{ "Zerind", 374 }		//19
	};
	ArrayRoads roads = {
		{ citys[0], citys[15], 140 }, { citys[0], citys[16], 118 }, { citys[0], citys[19], 75 },
		{ citys[1], citys[5], 211 }, { citys[1], citys[6], 90 }, { citys[1], citys[13], 101 },  { citys[1], citys[17], 85 },
		{ citys[2], citys[3], 120 }, { citys[2], citys[13], 138 }, { citys[2], citys[14], 146 },
		{ citys[3], citys[2], 120 }, { citys[3], citys[10], 75 },
		{ citys[4], citys[7], 86 },
		{ citys[5], citys[1], 211 }, { citys[5], citys[15], 99 },
		{ citys[6], citys[1], 90 },
		{ citys[7], citys[4], 86 }, { citys[7], citys[17], 98 },
		{ citys[8], citys[11], 87 }, { citys[8], citys[18], 92 },
		{ citys[9], citys[10], 70 }, { citys[9], citys[16], 111 },
		{ citys[10], citys[3], 75 }, { citys[10], citys[9], 70 },
		{ citys[11], citys[8], 87 },
		{ citys[12], citys[15], 151 }, { citys[12], citys[19], 71 },
		{ citys[13], citys[1], 101 }, { citys[13], citys[2], 138 }, { citys[13], citys[14], 97 },
		{ citys[14], citys[2], 146 }, { citys[14], citys[13], 97 }, { citys[14], citys[15], 80 },
		{ citys[15], citys[0], 140 }, { citys[15], citys[5], 99 }, { citys[15], citys[12], 151 }, { citys[15], citys[14], 80 },
		{ citys[16], citys[0], 118 }, { citys[16], citys[9], 111 },
		{ citys[17],citys[1], 85 }, { citys[17], citys[7], 98 }, { citys[17], citys[18], 142 },
		{ citys[18], citys[8], 92 }, { citys[18], citys[17], 142 },
		{ citys[19], citys[0], 75 }, { citys[19], citys[12], 71 }
	};

}

