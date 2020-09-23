#pragma once

#include <string>
#include <fstream>

class Logger
{
public:
	static void Write( const std::string& fileData )
	{
		// std::ofstream out{ "Logs/Log.txt",std::ofstream::app };
		// 
		// out << fileData << '\n';
	}
};