#ifndef BASESTATION_H_
#define BASESTATION_H_
#include <queue>
#include "Generators.h"
#include "Package.h"
#include "Logger.h"
class WirelessNetwork;

class BaseStation
{
private:
	bool is_first_checking_channel_; //ustawiana na true jezeli juz zaplanowano pierwsze sprawdzenie kana³u
	int counterDIFS = 8; //licznik DIFS
	std::queue<Package*> buffer_;
	Package* package_; //wskaznik na obiekty klasy package
	Logger logger_;
	Generators* generator_cgpk_;
	Generators* generator_ctpk_;
	Generators* generator_R_;
	std::queue<int>* queue_of_seeds_;
	
public:
	BaseStation(int id, Logger logger, std::queue<int>* queue_of_seeds);
	~BaseStation();
	void set_is_first_checking_channel();
	bool return_is_first_checking_channel();
	int base_station_id_;//BS's ID
	void addToBuffer(Package* package); //adds package to buffer_
	int returnBaseStationID(); //returns BS ID
	int returnSizeOfBuffer(); //returns the size of buffer_
	void resetDIFScounter(); //resets DIFS counter
	void decrementDIFScounter(); //decrements DIFS counter
	bool checkingDIFS(); //TRUE - channel free for DIFS time (4ms)
	void remove_package_from_buffer(int package_id); //removes package from buffer_
	Package* returnNextPackage(); //returns first package from buffer_
	Generators* return_generator_cgpk();
	Generators* return_generator_ctpk();
	Generators* return_generator_R();
};

#endif 
