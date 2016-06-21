#include <cmath>
#include <cstdlib>
#include "node.h"

Node::Node(int _strategy, Channel &_channel) :
	strategy(_strategy), channel(_channel), state(0)
{
	double x = rand() / (double)RAND_MAX;
	leftCounter = (int)(-10 * log(x) * 1000);
}

void Node::setState(int _state)
{
	state = _state;
}

void Node::setCW(int _cw)
{
	cw = _cw;
}

void Node::setChannel(Channel &_channel)
{
	channel = _channel;
}

void Node::setLeftCounter(int _left)
{
	leftCounter = _left;
}

void Node::generate(void)
{
	double x = rand() / (double)RAND_MAX;

	state = 0;	
	leftCounter = (int)(-10 * log(x) * 1000);
}

void Node::process(void)
{
	if (state == 2 && leftcollisionDetection) {
		leftcollisionDetection--;
		if (!leftcollisionDetection)
			channel.SetState(1);
	}
	if (--leftCounter)
		return;

	if (state == 0) {
		state = 1;
		leftCounter = 1;
	}
	else if (state == 1) {
		if (channel.GetState() == 0) {
			leftCounter = 1;
			return;
		}

		state = 2;
		leftCounter = (int)819.2; // 전송 시 걸리는 시간 대입
		leftcollisionDetection = 50;
		channel.add(this);
	}
	else if (state == 2) {
		channel.remove(this);
		channel.SetState(0);
		generate();
	}
	else {
		state = 1;
		leftCounter = 50 * (rand() % cw + 1); // 전략에 맞는 delay time 대입
		if (strategy == 1) cw *= 2;
	}
}
