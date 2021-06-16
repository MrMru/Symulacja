#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "Logger.h"
#include "WirelessNetwork.h"
#include <queue>
#include <vector>

class Simulation
{
public:
	Simulation(Logger logger, double L, double P, std::queue<int>* queue_of_seeds, WirelessNetwork* network);
	~Simulation();
	void M2(int time);
	void which_mode(int a);
private:
	Logger logger_;
	BaseStation* base_station_;
	size_t clock_ = 0;
	WirelessNetwork* network_ = nullptr;
	bool checking_mode;
	double variable_L_;
	double variable_P_;
	std::queue<int>* queue_of_seeds_;
	
};

#endif
