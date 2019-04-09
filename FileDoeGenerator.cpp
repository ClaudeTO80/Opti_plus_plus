#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include "FileDoeGenerator.h"

//using namespace std;
//bool FileDoeGenerator::generateMatrix()
//{
//	ifstream ifs(fileName_);
//
//	if (!ifs.is_open())
//		return false;
//
//	string line("");
//	int begin_index = 0;
//	while (std::getline(ifs, line))
//	{
//		int found=-1;
//		int lastPos=0;
//		int numVars = -1;
//		vector<double> currSample;
//
//		while (found != string::npos) 
//		{
//			found = line.find_first_of(" ,\t", found+1);
//			
//			if (found == string::npos)
//				currSample.push_back(stod(line.substr(lastPos)));
//			else
//				currSample.push_back(stod(line.substr(lastPos,lastPos-found)));
//
//			lastPos = found;
//		}
//
//		matrix_.push_back(currSample);
//		if (numVars == -1)
//			numVars = currSample.size();
//
//		currSample.clear();
//		currSample.reserve(numVars);
//	}
//
//	return true;
//}