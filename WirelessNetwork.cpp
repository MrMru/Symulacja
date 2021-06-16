#include "WirelessNetwork.h"

#include <iostream>

#include "EventCheckingChannel.h"
#include "EventTransmission.h"
#include "EventGeneratePackage.h"
#include "EventSendACK.h"


WirelessNetwork::WirelessNetwork(Logger logger, double L, double P, std::queue<int>* queue_of_seeds)
{
	logger.Debug("Creating new network");
	logger_ = logger;
	is_channel_free_ = true;
	succesful_transmissions_ = 0;
	unsuccessful_transmissions_ = 0;
	queue_of_seeds_ = queue_of_seeds;
	for (int i = 0; i < k_; i++)
	{
		base_stations_.push_back(new BaseStation(i, logger,queue_of_seeds_));
	}
	generator_TER_ = new Generators(queue_of_seeds_->front());
	queue_of_seeds->pop();
	variable_L_ = L;
	variable_P_ = P;

	

	average_retransmission_txt.open("2average_retransmission.txt", std::ios::out);
	sent_packages.open("2sent_packages.txt", std::ios::out);
}


WirelessNetwork::~WirelessNetwork()
{
}

int WirelessNetwork::returnK()
{
	return k_;
}

void WirelessNetwork::IncrementSuccesfulTransmissions()
{
	++succesful_transmissions_;
}

void WirelessNetwork::IncrementUnsuccesfulTransmissions()
{
	++unsuccessful_transmissions_;
}

int WirelessNetwork::returnSuccesfulTransmissions()
{
	return succesful_transmissions_;
}

int WirelessNetwork::returnUnsuccesfulTransmissions()
{
	return unsuccessful_transmissions_;
}

void WirelessNetwork::generatePackage(BaseStation* base_station, size_t time, Logger logger)
{
	Package* p = new Package(this->howMuchPackages(), base_station->returnBaseStationID(), logger, time, base_station->return_generator_ctpk()->Rand(1,10)); 
	packages_.push_back(p);//dodanie pakietu do wektora pakietow
	base_stations_.at(base_station->returnBaseStationID())->addToBuffer(p); //dodanie pakietu do kolejki buffer_ stacji bazowej
}

int WirelessNetwork::howMuchPackages()
{
	return packages_.size();
}

void WirelessNetwork::addToChannel(Package* package)
{
	channel_queue_.push(package);
}

void WirelessNetwork::set_is_channel_free(bool free)
{
	if (free)
	{
		is_channel_free_ = true;
	}
	else
	{
		is_channel_free_ = false;
	}
}

bool WirelessNetwork::checkingChannel()
{
	
	if (this->channel_queue_.size() == 0) 
	{
		is_channel_free_ = true;
		return is_channel_free_;
	}
	else
	{
		is_channel_free_ = false;
		return is_channel_free_;
	}
}

bool WirelessNetwork::return_is_channel_free()
{
	return is_channel_free_;
}

std::queue<Package*> WirelessNetwork::returnChannelQueue()
{
	return channel_queue_;
}

void WirelessNetwork::remove_package_from_channel(int package_id)
{
	int channel_size_ = channel_queue_.size();
	for(int i = 0; i < channel_size_; i++)
	{
		Package* pom = channel_queue_.front();
		channel_queue_.pop();
		if(package_id != pom->return_packade_id())
		{
			channel_queue_.push(pom);
		}
	}
	if(channel_queue_.size()==0)
	{
		set_is_channel_free(true);
	}
}

void WirelessNetwork::EventStartTransmission(Logger logger, size_t start_time, Package* package, WirelessNetwork* network, BaseStation* base_station)
{
	logger.Debug("Event Start Transmission");
	package = base_stations_.at(base_station->returnBaseStationID())->returnNextPackage();
	if (package->returnRetransmissionCounter() == 0)
	{
		package->setTimeOfStartTransmission(start_time);
	}
	addToChannel(package);	
}

void WirelessNetwork::EventGenerateACK(Logger logger, size_t start_time, Package* package, WirelessNetwork* network, BaseStation* base_station)
{
	logger.Debug("Event Generate ACK");
}

void WirelessNetwork::EventRetransmission(Logger logger, size_t start_time, Package* package, WirelessNetwork* network, BaseStation* base_station)
{
	logger.Debug("Event Retransmission. Package ID " + std::to_string(package->return_packade_id()));
	package->increaseRetransmissionCounter();

	size_t R_ = base_station->return_generator_R()->Rand(0, (pow(2, package->returnRetransmissionCounter()) - 1));
	size_t crp_ = R_ * package->returnCTP();
	package->setR(R_);
	package->setCRP(crp_);
}

void WirelessNetwork::EventEndTransmission(Logger logger, size_t start_time, Package* package, WirelessNetwork* network, BaseStation* base_station)
{
	logger.Debug("Event End Transmission");
	remove_package_from_channel(package->return_packade_id());
	package->setIsEnd();
	package->setTimeOfEndTransmission(start_time);
	base_stations_.at(base_station->returnBaseStationID())->remove_package_from_buffer(package->return_packade_id());
	if (channel_queue_.size() == 0)
	{
		set_is_channel_free(true);
	}
}

int WirelessNetwork::returnPackageInChannelID()
{
	Package* pom = channel_queue_.front();
	return pom->return_packade_id();
}

Package* WirelessNetwork::returnPackageInChannel()
{
	Package* pom = channel_queue_.front();
	return pom;
}

Package* WirelessNetwork::returnNextPackageInChannel()
{
	Package* pom = channel_queue_.front();
	channel_queue_.pop();
	return pom;
}

bool WirelessNetwork::is_next_package_in_channel()
{
	Package* pom = channel_queue_.front();
	channel_queue_.pop();
	if (channel_queue_.size()==0)
	{
		addToChannel(pom);
		return false;
	}
	else
	{
		addToChannel(pom);
		return true;
	}
}

bool WirelessNetwork::return_is_error_TER()
{
	set_error_TER();
	return is_error_TER_;
}

void WirelessNetwork::set_error_TER()
{	
	if (generator_TER_->RandZeroOne(variable_P_) == 0)
	{
		is_error_TER_ = true;
	}
	else
	{
		is_error_TER_ = false;
	}
}

double WirelessNetwork::return_variable_L_()
{
	return variable_L_;
}

double WirelessNetwork::return_variable_P_()
{
	return variable_P_;
}

double WirelessNetwork::average_retransmission()
{
	double sum_of_retransmissions = 0;
	double succesfull_packages = 0;
	for (int i = 0; i < packages_.size(); i++)
	{
		if (packages_.at(i)->returnIsEnd())
		{
			if (packages_.at(i)->returnToStatistics())
			{
				succesfull_packages++;
				sum_of_retransmissions = sum_of_retransmissions + packages_.at(i)->returnRetransmissionCounter();
			}
		}
	}
	if (succesfull_packages == 0)
	{
		return 0;
	}else
	{
		return (sum_of_retransmissions / succesfull_packages);
	}
}

void WirelessNetwork::average_time_of_waiting()
{
	double sum_time_of_waiting = 0;
	double succesfull_packages = 0;
	for (int i = 0; i < packages_.size(); i++)
	{
		if (packages_.at(i)->returnIsEnd())
		{
			if (packages_.at(i)->returnToStatistics())
			{
				succesfull_packages++;
				sum_time_of_waiting = sum_time_of_waiting + (packages_.at(i)->returnTimeOfStartTransmission() - packages_.at(i)->returnCGPk());
			}
		}
	}
	
	logger_.Info("Average time of waiting to leave buffer : " + std::to_string(sum_time_of_waiting / (succesfull_packages * 10)) + " ms");
	
}

void WirelessNetwork::average_delay_of_package()
{
	double sum_time_delay = 0;
	double succesfull_packages = 0;
	for (int i = 0; i < packages_.size(); i++)
	{
		if (packages_.at(i)->returnIsEnd() && packages_.at(i)->isACK())
		{
			if (packages_.at(i)->returnToStatistics())
			{
				succesfull_packages++;
				sum_time_delay = sum_time_delay + (packages_.at(i)->returnTimeOfEndTransmission() - packages_.at(i)->returnCGPk());
			}
		}
	}
	
	logger_.Info("Average delay of Package : " + std::to_string(sum_time_delay / (succesfull_packages * 10)) + " ms");
}

void WirelessNetwork::average_package_error_rate()
{
	std::vector<double> succesfull_packages;
	std::vector<double> unsuccesfull_packages;
	double average_PER = 0;
	double max_PER = 0;
	for (int i = 0; i < 8; i++)
	{
		succesfull_packages.push_back(0);
		unsuccesfull_packages.push_back(0);
	}

	for (int i = 0; i < packages_.size(); i++)
	{
		if (packages_.at(i)->returnIsEnd() && packages_.at(i)->isACK() && packages_.at(i)->returnToStatistics())
		{
			++succesfull_packages[packages_[i]->returnActualBSid()];
		}
		if (packages_.at(i)->returnIsEnd() && !packages_.at(i)->isACK() && packages_.at(i)->returnIsRejected() && packages_.at(i)->returnToStatistics())
		{
			++unsuccesfull_packages[packages_[i]->returnActualBSid()];
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (max_PER < unsuccesfull_packages[i]/succesfull_packages[i])
		{
			max_PER = unsuccesfull_packages[i] / succesfull_packages[i];
		}
		average_PER += unsuccesfull_packages[i] / succesfull_packages[i];
		//logger_.Info("BS " + std::to_string(i) + "\n -> succesfull transmissions : " + std::to_string(succesfull_packages[i]) + "\n -> unsuccesfull transmissions : " + std::to_string(unsuccesfull_packages[i]) + "\n PER = " + std::to_string(unsuccesfull_packages[i] / succesfull_packages[i]));
	}
	logger_.Info("Average PER for all Base Stations = " + std::to_string(average_PER / 8));
	logger_.Info("Max PER = " + std::to_string(max_PER));
	
}

double WirelessNetwork::average_system_bit_rate()
{
	double succesfull_packages = 0;
	for (int i = 0; i < packages_.size(); i++)
	{
		if (packages_.at(i)->returnIsEnd() && packages_.at(i)->isACK())
		{
			++succesfull_packages;
		}
	}
	return succesfull_packages;
}

size_t WirelessNetwork::returnInitialPhaseLength()
{
	return initial_phase_length_;
}

void WirelessNetwork::setInitialPhaseLength(size_t time)
{
	initial_phase_length_ = time;
	/*size_t time;
	std::cout << "Enter the Initial Phase Time : ";
	std::cin >> time;
	initial_phase_length_ = time;*/
}









