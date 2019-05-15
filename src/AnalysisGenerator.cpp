#include "AnalysisGenerator.h"
#include "STLHeaders.h"

using namespace std;
using namespace AnalysisGenerator;

bool Generator::dumpMatrix(	ostream& os, 
							bool headers, 
							string separator)
{  
	if (matrix_.empty())
		return false;

	int numSamples = (int)matrix_.size();
	int numVars = (int)matrix_[0].size();

	if (headers)
	{
		for (int j = 0; j < numVars; ++j)
		{
			if (j < (int)genopts_.names_.size())
				os << genopts_.names_[j].c_str() << separator.c_str();

			else
				os << "var_" + to_string(j) << separator.c_str();

		}
		os << endl;
	}

	for (int i = 0; i < numSamples; ++i)
	{
		for (int j = 0; j < numVars; ++j)
			os << matrix_[i][j] << separator.c_str();

		os << endl;
	}

	return true;
}

bool Generator::dumpMatrix(	const string& fileName,
							bool headers,
							ios_base::openmode mode,
							string separator)
{
	ofstream ofs(fileName, mode);

	if (!ofs.is_open())
		return false;

	return dumpMatrix(ofs, headers, separator);
}

