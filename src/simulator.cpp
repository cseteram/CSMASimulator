#include <cstdio>
#include "simulator.h"

Simulator::Simulator(int _duration, int _scheme, int _nodeCnt, int _initialCW)
    : scheme(_scheme), nodeCnt(_nodeCnt), initialCW(_initialCW)
{
    leftSimulationCounter = (int)(_duration * 1e6);
}

void Simulator::simulate(void) {
    printf("simulation start (scheme = %d, n = %d, cw = %d)\n", scheme, nodeCnt, initialCW);

    int strategy = (scheme == 2) ? 1 : 0;
    Channel channel;

    for (int i = 0; i < nodeCnt; i++) {
        Node node(strategy, channel);
        nodes.push_back(node);
        node.setCW(initialCW);
    }

    while (leftSimulationCounter--) {
        for (auto &node : nodes) {
            node.process();
        }

        auto nodesInChannel = channel.GetNodes();
        if (nodesInChannel.size() > 1) {
            /* collision occured! */
            printf("collsion occured!\n");
            for (auto &node : nodesInChannel) {
                node->setState(3);
                if (scheme != 0)
                    node->setLeftCounter(1);
            }
        }
    }

    printf("simulation end\n");
}
