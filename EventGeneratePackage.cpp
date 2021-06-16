#include "EventGeneratePackage.h"

#include "EventCheckingChannel.h"


EventGeneratePackage::EventGeneratePackage(Logger logger, size_t start_time, BaseStation* base_station, WirelessNetwork* network, EventList* event_list) : Event(start_time, network)
{
	execution_time_ = start_time;
	logger_ = logger;
	network_ = network;
	base_station_ = base_station;
	event_list_ = event_list;
	logger_.Debug("Next generation of package in : " + std::to_string(execution_time_) + " BS : " + std::to_string(base_station->returnBaseStationID()));
}


void EventGeneratePackage::Execute()
{
	network_->generatePackage(base_station_, execution_time_, logger_);
	
	if (base_station_->returnSizeOfBuffer() == 1 && !base_station_->return_is_first_checking_channel())
	{
		event_list_->push(new EventCheckingChannel(logger_, execution_time_, package_, network_, base_station_, event_list_));
		base_station_->set_is_first_checking_channel();
	}
	
	event_list_->push(new EventGeneratePackage(logger_, execution_time_ + (base_station_->return_generator_cgpk()->RandEXP(network_->return_variable_L_())), base_station_, network_, event_list_));
	
	
}

