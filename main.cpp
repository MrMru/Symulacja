#include <iostream>
#include "WirelessNetwork.h"
#include "BaseStation.h"
#include "EventGeneratePackage.h"
#include "Logger.h"
#include "Simulation.h"
#include <fstream>
#include <vector>
#include <queue>


int main()
{
	Logger logger = Logger();
	logger.set_level(Logger::Level::Info);
	logger.set_level();
	//double variable_L_ = 0.001;
	//double variable_P_ = 0.8;
	std::fstream seeds;
	std::string seed;
	std::queue<int> queue_of_seeds;
	seeds.open("./seeds.txt");
	std::vector <std::queue<int>> vector_of_seeds;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 41; j++)
		{
			std::getline(seeds, seed);
			queue_of_seeds.push(stoi(seed));
		}
		vector_of_seeds.push_back(queue_of_seeds);
		while(!queue_of_seeds.empty())
		{
			queue_of_seeds.pop();
		}
	}

	int a;
	std::cout << "Mode " << std::endl;
	std::cout << "1 -> step" << std::endl;
	std::cout << "2 -> normal" << std::endl;
	std::cin >> a;
	


	size_t time_of_simulation;
	std::cout << "Time of Simulation : ";
	std::cin >> time_of_simulation;

	double variable_L_;
	std::cout << "Lambda : ";
	std::cin >> variable_L_;

	double variable_P_;
	std::cout << "Probability of error TER : ";
	std::cin >> variable_P_;
	
	
	size_t length;
	std::cout << "Number of received packages : ";
	std::cin >> length;

	
	
	for (int i = 0; i < 10; i++)
	{
		WirelessNetwork* network_ = new WirelessNetwork(logger, variable_L_, variable_P_, &vector_of_seeds[i]);
		network_->setInitialPhaseLength(length);
		Simulation* sim = new Simulation(logger, variable_L_, variable_P_, &vector_of_seeds[i], network_);
		sim->which_mode(a);
		sim->M2(time_of_simulation);
	}
	

	
	
	std::cin.get();
	return 0;
}
