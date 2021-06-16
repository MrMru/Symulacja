#include "Logger.h"

#include <iostream>
#include <ostream>

Logger::Logger()
{
	
}


Logger::~Logger()
{
	
}

void Logger::Info(std::string message)
{
	//tylko info-> wyniki symulacji
	if (level_ != Level::Error)
	{
		std::cout << "[Info]" << message << std::endl;
	}
	
}

void Logger::Debug(std::string message)
{
	//wszystko
	if (level_ == Level::Debug)
	{
		std::cout << "[Debug]" << message << std::endl;
	}
	
}

void Logger::Error(std::string message)
{
	//error , bledy, kolizje, koniec wysylania pakietu
	if(level_ != Level::Info)
	std::cout << "[Error]" << message << std::endl;
}

void Logger::set_level()
{
	int a;
	std::cout << "1 -> Info" << std::endl;
	std::cout << "2 -> Debug" << std::endl;
	std::cout << "3 -> Error" << std::endl;
	while(true)
	{
		std::cin >> a;
		if ((a >= 1) || (a <= 3)) break;
	}
	if (a == 1) level_ = Level::Info;
	if (a == 2) level_ = Level::Debug;
	if (a == 3) level_ = Level::Error;
	
}




