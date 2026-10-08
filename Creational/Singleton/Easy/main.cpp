#include "Singleton.hpp"

#include <iostream>


void	connectToDatabase()
{
	Logger&	logger = Logger::getInstance();

	logger.info("Connecting to database...");
	logger.warning("Connection is slow");
	logger.error("Connection failed");
}

void	logAllLevels(Logger& logger)
{
	logger.info("Application started");
	logger.warning("Config file not found, using defaults");
	logger.error("Failed to open output file");
}

int	main()
{
	Logger&	logger = Logger::getInstance();

	std::cout << "=== 1. Default level (INFO): everything is printed ===" << std::endl;
	logAllLevels(logger);

	std::cout << std::endl << "=== 2. Level WARNING: info is hidden ===" << std::endl;
	logger.setLevel(LogLevel::WARNING);
	logAllLevels(logger);

	std::cout << std::endl << "=== 3. Level ERR: only errors are printed ===" << std::endl;
	logger.setLevel(LogLevel::ERR);
	logAllLevels(logger);

	std::cout << std::endl << "=== 4. getLevel() ===" << std::endl;
	std::cout << "Current level is ERR: "
				<< (logger.getLevel() == LogLevel::ERR ? "yes" : "no") << std::endl;

	std::cout << std::endl << "=== 5. Same instance everywhere ===" << std::endl;
	Logger&	another = Logger::getInstance();
	std::cout << "&logger  = " << &logger << std::endl;
	std::cout << "&another = " << &another << std::endl;
	std::cout << "Same object: " << (&logger == &another ? "yes" : "no") << std::endl;

	std::cout << std::endl << "=== 6. Level set in main applies in other functions ===" << std::endl;
	logger.setLevel(LogLevel::WARNING);
	connectToDatabase();	// its info() is hidden, because there is only one logger

	// These must NOT compile (uncomment one to check):
	// Logger	copy = logger;					// copy constructor is deleted
	// Logger	moved = std::move(logger);		// move constructor is deleted
	// another = logger;						// copy assignment is deleted
	// Logger	direct;							// constructor is private

	return (0);
}
