#include "BaseStation.h"
#include <iostream>
#include "EventGeneratePackage.h"
#include "Package.h"


BaseStation::BaseStation(int id, Logger logger, std::queue<int>* queue_of_seeds)
{
	base_station_id_ = id;
	is_first_checking_channel_ = false;
	//logger_ = logger;
	logger.Debug("Creating new base station. Base Station ID: " + std::to_string(base_station_id_));
	queue_of_seeds_ = queue_of_seeds;
	generator_cgpk_ = new Generators(queue_of_seeds_->front());
	queue_of_seeds_->pop();
	generator_ctpk_ = new Generators(queue_of_seeds_->front());
	queue_of_seeds_->pop();
	generator_R_ = new Generators(queue_of_seeds_->front());
	queue_of_seeds_->pop();
}


BaseStation::~BaseStation()
{
}

int BaseStation::returnBaseStationID()
{
	return base_station_id_;
}

void BaseStation::addToBuffer(Package* package)
{
	buffer_.push(package);
}

int BaseStation::returnSizeOfBuffer()
{
	return buffer_.size();
}

Package* BaseStation::returnNextPackage()
{
	Package* p = buffer_.front();
	return p;
}


void BaseStation::set_is_first_checking_channel()
{
	is_first_checking_channel_ = true;
}

bool BaseStation::return_is_first_checking_channel()
{
	return is_first_checking_channel_;
}

void BaseStation::remove_package_from_buffer(int package_id)
{
	int buffer_size_ = buffer_.size();
	for (int i = 0; i < buffer_size_; i++)
	{
		Package* pom = buffer_.front();
		buffer_.pop();
		if (package_id != pom->return_packade_id())
		{
			buffer_.push(pom);
		}
	}
}

Generators* BaseStation::return_generator_cgpk()
{
	return generator_cgpk_;
}

Generators* BaseStation::return_generator_ctpk()
{
	return generator_ctpk_;
}

Generators* BaseStation::return_generator_R()
{
	return generator_R_;
}



