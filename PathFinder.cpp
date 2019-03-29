//Created by Dale Sinnott
#include "PathFinder.h"

const int width = 7; // width of the map
const int height = 5; // height of the map
static int nodeMap[width][height]; //the 2d map array
static int closed[width][height]; // map of closed (tested) nodes
static int open[width][height]; // map of open (Untested) nodes
static int dir_map[width][height]; // map of directions
const int dir = 8; // number of possible directions to go at any position
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

class Node
{
private:
	Vector2f m_position;// position of node
	int distanceMoved; // distance already travelled to goal
	int priority;  // priority = distanceMoved + remaining distance estimated
public:
	Node(int xp, int yp, int d, int p) :
		m_position(Vector2f(xp, yp)),
		distanceMoved(d),
		priority(p)
	{ //constructor 

		//initialise Node
		
	}

	//getters
	
	int getxPos() const { return m_position.x; }
	int getyPos() const { return m_position.y; }
	int getDistanceMoved() const { return distanceMoved; }
	int getPriority() const { return priority; }
	//setters
	void setxPos(int val) { m_position.x = val; }
	void setyPos(int val) { m_position.y = val; }
	void setDistanceMoved(int val) { distanceMoved = val; }
	void setPriority(int val) { priority = val; }
	//update priority
	void updatePriority(const int & xDest, const int & yDest)
	{
		priority = distanceMoved + estimate(xDest, yDest) * 10; //A*
	}

	// give better priority to going straight instead of diagonally
	void nextDistanceMoved(const int & i) // i: direction
	{
		distanceMoved += (i % 2 == 0 ? 10 : 14);
	}
	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const
	{ // http://stackoverflow.com/questions/16869920/a-heuristic-calculation-with-euclidean-distance
		
		static int xd, yd, d;
		xd = xDest - m_position.x;
		yd = yDest - m_position.y;
		// Euclidian heurictic ( distance ) 
		d = static_cast<int>(sqrt(xd*xd + yd*yd));
		return(d);
	}
};

// Determine priority (in the priority queue)
bool operator<(const Node & a, const Node & b)
{
	return a.getPriority() > b.getPriority();
}


void PathFinder::findPath(int _map[][5])
{
	// create map
	m_foundNodes.clear();
	m_foundNodes.shrink_to_fit();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (_map[x][y] == 0)
			{
				nodeMap[x][y] = 0;
			}
			else
			{
				nodeMap[x][y] = 1;
			}
		}
	}

	int xA = 0, yA = 2; //start location
	int xB = 6, yB = 2; //end location


	// get the path

	string path = pathFind(xA, yA, xB, yB);
	if (path == "")
	{
		hasPath = false;
	}
	else
	{
		hasPath = true;
		// follow the path on the map and display it 
		if (path.length() > 0)
		{
			int j; 
			char c; 
			int x = xA;
			int y = yA;

			nodeMap[x][y] = 2; //start
			temp = make_shared<Vector2f>(x * 96 + 48 + 304, y * 96 + 48 + 120);
			m_foundNodes.push_back(temp);
			for (int i = 0; i < path.length(); i++)
			{
				c = path.at(i); //number from path as character
				j = atoi(&c); // convert the character to a value
				x = x + dx[j]; 
				y = y + dy[j];

				nodeMap[x][y] = 3; //make this part of the path
				temp = make_shared<Vector2f>(x * 96 + 48 + 304, y * 96 + 48 + 120);
				m_foundNodes.push_back(temp);
			}

			nodeMap[x][y] = 4; //end
			temp = make_shared<Vector2f>(x * 96 + 96 + 304, y * 96 + 48 + 120);
			m_foundNodes.push_back(temp);

			
		}
	}

}
// The path returned is a string of direction digits
string PathFinder::pathFind(int const & xStart, int const & yStart, int const & xFinish, int const & yFinish)
{
	static priority_queue<Node> pq[2]; // list of open (untested) nodes
	static int queue_index; // pq index
	static std::shared_ptr<Node> currentNode;
	static std::shared_ptr<Node> childNode;
	static int i, j, x, y;
	static int xDir, yDir;
	static char c;
	queue_index = 0;

	// reset the node maps
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			closed[x][y] = 0;
			open[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	currentNode = make_shared<Node>(xStart, yStart, 0, 0);
	currentNode->updatePriority(xFinish, yFinish);
	pq[queue_index].push(*currentNode);
	open[x][y] = currentNode->getPriority(); // mark it on the open nodes map

	// A* search
	while (!pq[queue_index].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		currentNode = make_shared<Node>(pq[queue_index].top().getxPos(), pq[queue_index].top().getyPos(),
			pq[queue_index].top().getDistanceMoved(), pq[queue_index].top().getPriority());

		x = currentNode->getxPos(); 
		y = currentNode->getyPos();

		pq[queue_index].pop(); // remove the node from the open list
		open[x][y] = 0;
		// mark it on the closed nodes map
		closed[x][y] = 1;

		// quit searching when the goal state is reached
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}
			currentNode = nullptr;
			// empty the leftover nodes
			while (!pq[queue_index].empty()) pq[queue_index].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i < dir; i++)
		{
			xDir = x + dx[i]; yDir = y + dy[i];

			if (!(xDir < 0 || xDir > width - 1 || yDir < 0 || yDir > height - 1 || nodeMap[xDir][yDir] == 1
				|| closed[xDir][yDir] == 1))
			{
				// generate a child node
				childNode = make_shared<Node>(xDir, yDir, currentNode->getDistanceMoved(),
					currentNode->getPriority());
				childNode->nextDistanceMoved(i);
				childNode->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open[xDir][yDir] == 0)
				{
					open[xDir][yDir] = childNode->getPriority();
					pq[queue_index].push(*childNode);
					// mark its parent node direction
					dir_map[xDir][yDir] = (i + dir / 2) % dir;
				}
				else if (open[xDir][yDir]>childNode->getPriority())
				{
					// update the priority info
					open[xDir][yDir] = childNode->getPriority();

					// update the parent direction info
					dir_map[xDir][yDir] = (i + dir / 2) % dir;

					// replace the node by emptying one pq to the other one except the node 
					// to be replaced will be ignoredand the new node will be pushed in instead
					while (!(pq[queue_index].top().getxPos() == xDir &&
						pq[queue_index].top().getyPos() == yDir))
					{
						pq[1 - queue_index].push(pq[queue_index].top());
						pq[queue_index].pop();
					}
					pq[queue_index].pop(); // remove the wanted node

					// empty the larger size pq to the smaller one
					if (pq[queue_index].size()>pq[1 - queue_index].size()) queue_index = 1 - queue_index;
					while (!pq[queue_index].empty())
					{
						pq[1 - queue_index].push(pq[queue_index].top());
						pq[queue_index].pop();
					}
					queue_index = 1 - queue_index;
					pq[queue_index].push(*childNode); // add the better node instead
				}
			}
		}
	}
	return ""; // no path found 
}
vector<shared_ptr<Vector2f>> PathFinder::getGroundNodes()
{
	return m_groundNodes;
}
vector<shared_ptr<Vector2f>> PathFinder::getAirNodes()
{
	return m_airNodes;
}
vector<shared_ptr<Vector2f>> PathFinder::getFoundNodes()
{
	return m_foundNodes;
}
void PathFinder::setGroundNodes(vector<shared_ptr<Vector2f>> grNodes)
{
	m_groundNodes.clear();
	m_groundNodes.shrink_to_fit();
	m_groundNodes = grNodes;
}
void PathFinder::setAirNodes(vector<shared_ptr<Vector2f>> airNodes)
{
	m_airNodes.clear();
	m_airNodes.shrink_to_fit();
	m_airNodes = airNodes;
}