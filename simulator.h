#pragma once
#include <vector>
#include "node.h"

class Simulator {
private:
	/* MAC scheme
	 * 0 : 1-persistent CSMA + uniform
	 * 1 : 1-persistent CSMA + CD + uniform
	 * 2 : 1-persistent CSMA + CD + binary exponential
	 */
	int scheme;

	/* if this value is 0, simulation end */
	int leftSimulationCounter;

	/* the number of nodes */
	int nodeCnt;

	/* initial cw */
	int initialCW;

	/* nodes used in simulation */
	std::vector<Node> nodes;

public:
	Simulator(int _duration, int _scheme, int _nodeCnt, int _initialCW);

	void simulate(void);
};