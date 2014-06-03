#include "Util.h"
#include <fstream>


std::string readFile(std::string filename) {
	/* Implementation adapted from
	 * http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html */

	std::ifstream filestream;

	filestream.open(filename);
	if (!filestream.is_open()) {
		return "";
	}

	std::string str;
	filestream.seekg(0, std::ios::end);
	str.resize( (unsigned int)filestream.tellg() );
	filestream.seekg(0, std::ios::beg);
	filestream.read(&str[0], str.size());
	filestream.close();

	return str;
}