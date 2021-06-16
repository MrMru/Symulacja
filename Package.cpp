#include "Package.h"

#include <iostream>


Package::Package(int package_id,int base_station_id,Logger logger, size_t cgpk, size_t ctpk)  
{
	package_id_ = package_id;
	cgpk_ = cgpk;
	ctp_ = ctpk;
	retransmission_counter_ = 0;
	is_collision_ = false;
	is_end_ = false;
	is_rejected_ = false;
	actual_base_station = base_station_id;
	to_statistics_ = true;
	logger.Debug("Generating new package. Package ID: " + std::to_string(package_id_) + "; Package was generated in station: " + std::to_string(actual_base_station) + "; Time of package transmission: " + std::to_string(ctp_) + " [ms].");
}
Package::~Package()
{
	
}

int Package::return_packade_id()
{
	return package_id_;
}


void Package::increaseRetransmissionCounter()
{
	retransmission_counter_++;
}

int Package::returnRetransmissionCounter()
{
	return retransmission_counter_;
}

int Package::returnCTP()
{
	// ctp * 10 bo 1 jednostka czasu to 0.1 ms
	return ctp_*10;
}

bool Package::returnIsCollision()
{
	
	return is_collision_;
}

void Package::setCollision()
{
	is_collision_ = true;
}

void Package::unsetCollision()
{
	is_collision_ = false;
}

void Package::setAck()
{
	is_confirmation_ACK_ = true;
}

void Package::unsetAck()
{
	is_confirmation_ACK_ = false;
}

bool Package::isACK()
{
	return is_confirmation_ACK_;
}

void Package::setR(size_t R)
{
	R_ = R;
}

void Package::setCRP(size_t CRP)
{
	crp_ = CRP;
}

size_t Package::returnCRP()
{
	return crp_;
}

size_t Package::returnCGPk()
{
	return cgpk_;
}

void Package::setIsEnd()
{
	is_end_ = true;
}

bool Package::returnIsEnd()
{
	return is_end_;
}

int Package::returnActualBSid()
{
	return actual_base_station;
}

void Package::setTimeOfStartTransmission(size_t time)
{
	time_of_start_transmission_ = time;
}

size_t Package::returnTimeOfStartTransmission()
{
	return time_of_start_transmission_;
}

void Package::setTimeOfEndTransmission(size_t time)
{
	time_of_end_transmission_ = time;
}

size_t Package::returnTimeOfEndTransmission()
{
	return time_of_end_transmission_;
}

void Package::setIsRejected(bool is_rejected)
{
	is_rejected_ = is_rejected;
}

bool Package::returnIsRejected()
{
	return is_rejected_;
}

void Package::setToStatistics(bool to_statistics)
{
	to_statistics_ = to_statistics;
}

bool Package::returnToStatistics()
{
	return to_statistics_;
}
