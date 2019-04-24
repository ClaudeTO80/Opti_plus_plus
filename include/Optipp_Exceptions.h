#pragma once
#include <exception>

class Optipp_MissionOptionException : public std::exception
{
public:
	Optipp_MissionOptionException(std::string msg)
	{
		msg_ = "Optipp_MissionOptionException: " + msg;
	}

	const char * what() const throw () 
	{
		return msg_.c_str();
	}

private:
	std::string msg_;
};