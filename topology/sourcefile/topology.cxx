#include "TopologyCategory.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

std::string Vint2String(std::vector<int>);

std::string Vint2String(std::vector<int> Vint)
{

	std::sort(Vint.begin(), Vint.end());

	//convert int to string
	std::string tempLine = "";
	int vsize = Vint.size();
	for (int i=0; i<vsize; i++)
	{
		stringstream s;
		s << Vint[i];
		tempLine += s.str();
		tempLine += " ";
	}
	return tempLine;
}

int main(int argc, const char* argv[])
{

	std::vector<std::string> strTTreeTFile;
	//std::vector<std::string> strTCut;
	std::string strTCut;

	std::ifstream m_inputCards;
	m_inputCards.open("topo.cards", std::ios::in);

	if (m_inputCards.is_open())
	{
		std::string line;
		int particleIndex;
		int particleID;
		bool topoStart = false;
		bool ifuseCut = false;
		std::string TopoChainStr = "";
		static int NewOrder = 0;
		while (!m_inputCards.eof())
		{
			getline (m_inputCards, line);
			if (line.empty()) continue;
			if (line[0] == '#') continue;
			if (line[0] == ' ') continue;
			if (line == "TOPO START USE Cut 0") 
			{
				topoStart = true;
				ifuseCut = false;
				continue;
			}
			if (line == "TOPO START USE Cut 1") 
			{
				topoStart = true;
				ifuseCut = true;
				continue;
			}
			if (!topoStart)
			{
				strTTreeTFile.push_back(line);
			}
			else if(ifuseCut)
			{
				strTCut = line;

			}
		} // end of while 
		m_inputCards.close();

		if ( strTTreeTFile.size()!=2 )
		{
			std::cout << "too few string for use !" << std::endl;
			std::cout << "you must give the treeName and ROOT file name!" 
				<< std::endl;
			std::cout << "Please check file \"topo.cards\"! " << std::endl;
			return 1;
		}else if ( ifuseCut && strTCut.empty() )
		{
			std::cout << "no cut for use!" << std::endl;
			std::cout << "Please check file \"topo.cards\"! " << std::endl;
			return 1;
		}
	}

	TopologyCategory aTopoCat(strTTreeTFile, strTCut);
	aTopoCat.openRootFile();
	aTopoCat.TopoRead();
	aTopoCat.TopoLog();
	aTopoCat.TopoWrite();
	return 0;
}
