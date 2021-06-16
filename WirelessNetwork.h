#ifndef WIRELESSNETWORK_H_
#define WIRELESSNETWORK_H_

#include <queue>
#include <vector>

#include "BaseStation.h"
#include "Channel.h"
#include "Event.h"
#include "Package.h"
class BaseStation;

class WirelessNetwork
{
private:
	const int k_ = 8; //number of base stations
	const int lr_ = 10; //maximum number of retransmissions
	std::vector<Package* > packages_; //vector of Packages
	std::queue<Package* > channel_queue_; //kolejka transmitowanych pakietow w kanale
	bool is_channel_free_; //TRUE - channel is free, FALSE - channel is busy
	int succesful_transmissions_; //counter of successful transmissions
	int unsuccessful_transmissions_; //counter of unsuccessful transmissions
	bool is_error_TER_; //TRUE - there is error TER, FALSE - there isn't error TER
	double variable_L_;
	double variable_P_;
	Logger logger_;
	Package* package_;
	BaseStation* base_station_;
	Generators* generator_TER_;
	std::queue<int>* queue_of_seeds_;
	size_t initial_phase_length_ = 0; //length of initial phase
	
public:
	WirelessNetwork(Logger logger, double L, double P, std::queue<int>* queue_of_seeds);
	~WirelessNetwork();
	int returnK(); //returns k_
	void IncrementSuccesfulTransmissions(); //increases succesful_transmissions_
	void IncrementUnsuccesfulTransmissions();//increases unsuccesful_transmissions_
	int returnSuccesfulTransmissions();//returns succesful_transmissions_
	int returnUnsuccesfulTransmissions();//returns unsuccesful_transmissions_
	void generatePackage(BaseStation* base_station, size_t time, Logger logger); //generation of packages
	int howMuchPackages(); //returns size of packages_ vevector
	void addToChannel(Package* package); //adding package to channel_queue_
	void set_is_channel_free(bool free); //free = true -> is_channel_free = true; free = false -> is_channel_free = false
	bool checkingChannel(); //TRUE channel is free, FALSE channel is busy
	bool return_is_channel_free();//TRUE channel is free, FALSE channel is busy
	std::queue<Package*> returnChannelQueue();
	void remove_package_from_channel(int package_id);//removes package from channel_queue_
	void EventStartTransmission(Logger logger, size_t start_time, Package* package, WirelessNetwork* network, BaseStation* base_station);
	void EventGenerateACK(Logger logger, size_t start_time, Package*package, WirelessNetwork* network, BaseStation* base_station);
	void EventRetransmission(Logger logger, size_t start_time, Package*package, WirelessNetwork* network, BaseStation* base_station);
	void EventEndTransmission(Logger logger, size_t start_time, Package*package, WirelessNetwork* network, BaseStation* base_station);
	std::vector<BaseStation* > base_stations_; //vector of Base Stations
	int returnPackageInChannelID();
	Package* returnPackageInChannel();
	Package* returnNextPackageInChannel();
	bool is_next_package_in_channel(); //TRUE - jest next pakiet w kanale, FALSE - nie ma pakietow w kanale
	bool return_is_error_TER();//TRUE - error TER, FALSE - no error TER
	void set_error_TER();//sets is_error_TER_ = TRUE
	double return_variable_L_();
	double return_variable_P_();

	//statistics
	double average_retransmission();
	void average_time_of_waiting();
	void average_delay_of_package();
	void average_package_error_rate();
	double average_system_bit_rate();
	size_t returnInitialPhaseLength();
	void setInitialPhaseLength(size_t time);

	std::ofstream average_retransmission_txt;
	std::ofstream sent_packages;

};




#endif 
