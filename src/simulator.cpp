#include <cstdio>
#include "simulator.h"

Simulator::Simulator(ll _duration, int _scheme, int _nodeCnt, ll _initialCW)
    : scheme(_scheme), nodeCnt(_nodeCnt), initialCW(_initialCW)
{
    leftSimulationCounter = (int)(_duration * 1e6);
}

void Simulator::simulate(void)
{

    int strategy = (scheme == 2) ? 1 : 0;
    Channel channel;
    Statistic stats;

    for (int i = 0; i < nodeCnt; i++) {
        Node node(strategy, &channel, &stats);
        node.setCW(initialCW);
        nodes.push_back(node);      
    }

    while (leftSimulationCounter--) {
        stats.addCurrentCounter(1);

        for (auto &node : nodes) {
            node.process();
        }

        auto nodesInChannel = channel.getNodes();
        if (nodesInChannel.size() > 1) {
            for (auto &node : nodesInChannel) {
                node->setState(3);
                if (scheme != 0)
                    node->setLeftCounter(1);
            }
        }
    }

    throughput = 
        stats.getTransmittedPacket() / (double)stats.getCurrentCounter() * 1e6;
    meanPacketDelay = 
        stats.getPacketDelay() / (double)stats.getPacketDelayCount();
    transmissionCollisionProb = 
        stats.getCollisionCount() / (double)stats.getTotalTransmission();

}

td3 Simulator::getResult(void) const
{
    return td3(throughput, meanPacketDelay, transmissionCollisionProb);
}
