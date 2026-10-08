#ifndef	SINGLETON_HPP

# define SINGLETON_HPP

# include <string>

enum class	LogLevel
{
	INFO,
	WARNING,
	ERR
};

class	Logger
{
	private:
		LogLevel	current_lvl;

		Logger() : current_lvl(LogLevel::INFO) {}

		void	log(LogLevel lvl, const std::string& msg);

	public:
		Logger(const Logger& copy) = delete;
		Logger(Logger&& move) = delete;
		Logger&	operator=(const Logger& copy) = delete;
		Logger&	operator=(Logger&& move) = delete;

		void			info(const std::string& msg);
		void			warning(const std::string& msg);
		void			error(const std::string& msg);

		LogLevel		getLevel() const;
		void			setLevel(LogLevel lvl);

		static Logger&	getInstance();
};

#endif //SINGLETON_HPP