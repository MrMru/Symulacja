#ifndef LOGGER_H_
#define  LOGGER_H_
#include <string>
#include <fstream>

class Logger
{
public:
	enum class Level { Info, Debug, Error };
	Logger();
	~Logger();

	void set_level(Level level)
	{
		level_ = level;
	}
	
	void Info(std::string message);
	void Debug(std::string message);
	void Error(std::string message);
	void set_level();
	
private:
	std::string file_path_;
	Level level_ = Level::Info; // level Info: Info Error, Debug:Info,Debug Error, Error: Error
	
};


#endif

