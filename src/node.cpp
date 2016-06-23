#include <cmath>
#include <cstdlib>
#include "node.h"

Statistic::Statistic() :
    currentCounter(0), transmittedPacket(0), packetDelay(0),
    packetDelayCount(0), collisionCount(0), totalTransmission(0)
{

}

ll Statistic::getCurrentCounter(void)
{
    return currentCounter;
}

ll Statistic::getTransmittedPacket(void)
{
    return transmittedPacket;
}

ll Statistic::getPacketDelay(void)
{
    return packetDelay;
}

ll Statistic::getPacketDelayCount(void)
{
    return packetDelayCount;
}

ll Statistic::getCollisionCount(void)
{
    return collisionCount;
}

ll Statistic::getTotalTransmission(void)
{
    return totalTransmission;
}

void Statistic::addCurrentCounter(ll count)
{
    currentCounter += count;
}

void Statistic::addTransmittedPacket(ll packets)
{
    transmittedPacket += packets;
}

void Statistic::addPacketDelay(ll delay)
{
    packetDelay += delay;
}

void Statistic::addPacketDelayCount(ll count)
{
    packetDelayCount += count;
}

void Statistic::addCollisionCount(ll count)
{
    collisionCount += count;
}

void Statistic::addTotalTransmission(ll transmissions)
{
    totalTransmission += transmissions;
}

Node::Node(int _strategy, Channel *_channel, Statistic *_stats) :
    strategy(_strategy), channel(_channel), state(0), stats(_stats)
{
    double x = dis(gen);
    leftCounter = (ll)(-10 * log(x) * 1000);
}

void Node::setState(int _state)
{
    state = _state;
}

void Node::setCW(ll _cw)
{
    cw = _cw;
}

void Node::setChannel(Channel *_channel)
{
    channel = _channel;
}

void Node::setLeftCounter(ll _left)
{
    leftCounter = _left;
}

void Node::generate(void)
{
    double x = dis(gen);

    state = 0;
    leftCounter = (ll)(-10 * log(x) * 1000);
}

void Node::process(void)
{
    if ((state == 2 || state == 3) && leftcollisionDetection) {
        leftcollisionDetection--;
        if (!leftcollisionDetection)
            channel->setState(1);
    }
    if (--leftCounter)
        return;

    if (state == 0) {
        state = 1;
        leftCounter = 1;
        lastGeneratedCount = stats->getCurrentCounter();
    }
    else if (state == 1) {
        if (channel->getState() == 1) {
            leftCounter = 1;
            return;
        }

        state = 2;
        leftCounter = (ll)781.25; // 전송 시 걸리는 시간 대입
        leftcollisionDetection = 50;
        channel->add(this);
        stats->addTotalTransmission(1);
    }
    else if (state == 2) {
        channel->remove(this);
        channel->setState(0);
        generate();

        stats->addTransmittedPacket(1);
        stats->addPacketDelay(stats->getCurrentCounter() - lastGeneratedCount);
        stats->addPacketDelayCount(1);
        if (strategy == 1) cw = 2;
    }
    else {
        state = 1;
        leftCounter = 50 * (rand() % cw + 1); // 전략에 맞는 delay time 대입
        if (strategy == 1 && cw < 1024) cw *= 2;

        channel->remove(this);
        if (channel->getNodes().size() == 0) {
            channel->setState(0);
            // channel->setColDetected(false);
        }

        stats->addCollisionCount(1);
    }
}
