#include "EventSendACK.h"

#include "EventCheckingChannel.h"


EventSendACK::EventSendACK(Logger logger, size_t start_time, Package* package, WirelessNetwork* network, BaseStation* base_station, EventList* event_list): Event(start_time, network)
{
	logger_ = logger;
	execution_time_ = start_time;
	package_ = package;
	network_ = network;
	base_station_ = base_station;
	event_list_ = event_list;
	logger_.Debug("Creating new EVENTSendACK. Execution time: " + std::to_string(execution_time_) + " in Base Station : " + std::to_string(base_station_->returnBaseStationID()));
}

void EventSendACK::Execute()
{
	
	
	logger_.Debug("Sending ACK in BS: " + std::to_string(base_station_->returnBaseStationID()) + " Package ID : " + std::to_string(package_->return_packade_id()));
	if(!package_->isACK()) //isn't ACK
	{
		if (package_->returnRetransmissionCounter() <= 6) 
		{
			network_->remove_package_from_channel(package_->return_packade_id());
			network_->EventRetransmission(logger_, execution_time_, package_, network_, base_station_);
			event_list_->push(new EventCheckingChannel(logger_, execution_time_ + package_->returnCRP(), package_, network_, base_station_, event_list_));
		}
		else
		{
			network_->IncrementUnsuccesfulTransmissions();
			package_->setIsRejected(true);
			
			if (network_->returnSuccesfulTransmissions() < network_->returnInitialPhaseLength())
			{
				package_->setToStatistics(false);
			}

			network_->EventEndTransmission(logger_, execution_time_ , package_, network_, base_station_);
			event_list_->push(new EventCheckingChannel(logger_, execution_time_, package_, network_, base_station_, event_list_));
		}		
	}	
	else //is ACK
	{
		network_->IncrementSuccesfulTransmissions();
		
		logger_.Debug("SUCCESFULL transmision of package ID : " + std::to_string(package_->return_packade_id()));
		network_->EventEndTransmission(logger_, execution_time_, package_, network_, base_station_);
		event_list_->push(new EventCheckingChannel(logger_, execution_time_, package_, network_, base_station_, event_list_));
		
		
		if (network_->returnSuccesfulTransmissions() < network_->returnInitialPhaseLength())
		{
			package_->setToStatistics(false);
		}
		
	}
}

EventSendACK::~EventSendACK()
{
}
