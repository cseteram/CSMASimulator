#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "node.h"

typedef std::tuple<double, double, double> td3;

class Simulator {
private:
    /* MAC scheme
    * 0 : 1-persistent CSMA + uniform
    * 1 : 1-persistent CSMA + CD + uniform
    * 2 : 1-persistent CSMA + CD + binary exponential
    */
    int scheme;

    /* if this value is 0, simulation end */
    ll leftSimulationCounter;

    /* the number of nodes */
    int nodeCnt;

    /* initial cw */
    ll initialCW;

    /* nodes used in simulation */
    std::vector<Node> nodes;

    /* measures */
    double throughput;
    double meanPacketDelay;
    double transmissionCollisionProb;

public:
    Simulator() { }
    Simulator(ll _duration, int _scheme, int _nodeCnt, ll _initialCW);

    /* do simulation and store measures */
    void simulate(void);

    /* get throughput, mean packet delay, transmission collsion prob. 
     * this function must be called after simulate().
     */
    td3 getResult(void) const;
};
