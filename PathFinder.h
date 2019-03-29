////////////////////////////////////////////////////////////
//
// Created by Dale
//
////////////////////////////////////////////////////////////
#ifndef PATHFINDER_H
#define PATHFINDER_H
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//http://en.wikipedia.org/wiki/A*_search_algorithm

#include "SFML\Graphics.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <math.h>
#include <memory>
using namespace std;
using namespace sf;
class PathFinder{
private:
	vector<shared_ptr<Vector2f>> m_groundNodes;
	vector<shared_ptr<Vector2f>> m_airNodes;
	vector<shared_ptr<Vector2f>> m_foundNodes;
	shared_ptr<Vector2f> temp;
public:
	////////////////////////////////////////////////////////////
	/// finnds the shortest path
	///
	////////////////////////////////////////////////////////////
	void findPath(int _map[][5]);
	bool hasPath = false;
	string pathFind(int const & xStart, int const & yStart, int const & xFinish, int const & yFinish);
	vector<shared_ptr<Vector2f>> getGroundNodes();
	vector<shared_ptr<Vector2f>> getAirNodes();
	vector<shared_ptr<Vector2f>> getFoundNodes();

	////////////////////////////////////////////////////////////
	/// sets the nodes for the walking troops
	///
	////////////////////////////////////////////////////////////
	void setGroundNodes(vector<shared_ptr<Vector2f>> grNodes);

	////////////////////////////////////////////////////////////
	/// sets the nodes for the flying troops
	///
	////////////////////////////////////////////////////////////
	void setAirNodes(vector<shared_ptr<Vector2f>> airNodes);
};
#endif