#include "Singleton.hpp"

#include <iostream>

void	Logger::info(const std::string& msg)
{
	log(LogLevel::INFO, msg);
}

void	Logger::warning(const std::string& msg)
{
	log(LogLevel::WARNING, msg);
}

void	Logger::error(const std::string& msg)
{
	log(LogLevel::ERR, msg);
}

void	Logger::log(LogLevel lvl, const std::string& msg)
{
	if (lvl < current_lvl)
		return ;

	if (lvl == LogLevel::INFO)
		std::cout << "[INFO]: " << msg << std::endl;

	else if (lvl == LogLevel::WARNING)
		std::cout << "[WARNING]: " << msg << std::endl;

	else
		std::cerr << "[ERROR]: " << msg << std::endl;
}

LogLevel	Logger::getLevel() const
{
	return current_lvl;
}

void	Logger::setLevel(LogLevel lvl)
{
	current_lvl = lvl;
}

Logger&	Logger::getInstance()
{
	static Logger	instance;
	return (instance);
}