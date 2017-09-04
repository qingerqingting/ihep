#include "TopologyCategory.h"
#include <algorithm>
#include <cstdlib>
#include "TEventList.h"
#include <stdio.h>  

// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopologyCategory::BubbleSort(std::vector<int> &pid,
		std::vector<int> &midx)
{
	if ( (int) pid.size() != (int) midx.size() )
	{
		std::cout << "the two vector have different length!" << std::endl;
		std::cout << "the size of pid is " << (int) pid.size() << std::endl;
		std::cout << "the size of midx is " << (int) midx.size() << std::endl;
		std::cout << "Please check your code!" << std::endl; 
		exit(1);
	}

	int vsize = midx.size();

	// sort max->min 
	int pidtemp;
	int idxtemp;
	for ( int i=0; i<vsize-1; i++ )
	{
		for ( int j=i+1; j<vsize; j++ )
		{
			if ( midx[i] < midx[j] )
			{
				pidtemp = pid[i]; idxtemp = midx[i];
				pid[i] = pid[j];  midx[i] = midx[j];
				pid[j] = pidtemp; midx[j] = idxtemp;
			}
		} // for j
	} // for i

}
std::string TopologyCategory::TopoString(std::vector<int> pid, 
		std::vector<int> midx)
{
	Vint TopoChain;
	TopoChain.clear();
	Vint iChain;
	iChain.clear();
	Vint vorder1;
	vorder1.clear();
	Vint vorder2;
	vorder2.clear();
	//int NewOrder = -1;
	int vsize = midx.size();
begin:
	for ( int i=0; i<vsize; i++ )
	{
		if (vorder1.empty())
		{
			vorder1.push_back(i);
			TopoChain.push_back(pid[i]);
			continue;
		}
		for (int j=0; j<vorder1.size(); j++)
		{
			if (midx[i] == vorder1[j]) 
			{
				vorder2.push_back(i);
				iChain.push_back(pid[i]);
			}
		}
	}
	if (!vorder2.empty())
	{
		std::sort(iChain.begin(), iChain.end());
		for (int k=0; k<iChain.size(); k++)
		{
			TopoChain.push_back(iChain[k]);
		}
		vorder1.clear();
		vorder1 = vorder2;
		vorder2.clear();
		iChain.clear();
		goto begin;
	}

	std::string tempLine = "";
	//convert int to string
	for (int i=0; i<TopoChain.size(); i++)
	{
		stringstream s;
		s << TopoChain[i];
		tempLine += s.str();
		tempLine += " ";
	}
	//std::cout << tempLine << std::endl;

	return tempLine;
}


TopologyCategory::TopologyCategory(const Vstr& strTTreeTFile, const std::string& strTCut)
{
	m_treeName = strTTreeTFile[0];
	//cout<<" >>>>  Tree Name "<<m_treeName<<endl;
	printf("\t \033[5m\033[1;42;31m%s\033[0m"," Tree Name  >>>> ");
	cout<<" "<<m_treeName<<endl<<endl;
	m_fileName = strTTreeTFile[1];
	printf("\t \033[5m\033[1;42;31m%s\033[0m"," File Name  >>>> ");
	cout<<" "<<m_fileName<<endl<<endl;
	m_cut = strTCut.c_str();
	printf("\t \033[5m\033[1;42;31m%s\033[0m","    Cut     >>>> ");
	cout<<" "<<strTCut.c_str()<<endl<<endl;

	Vtopo.clear();
	topoIdx.clear();
	VtopoNpar.clear();
	VtopoStr.clear();
	VcomTPI.clear();
}

TopologyCategory::~TopologyCategory()
{
	delete m_tree;
}

void TopologyCategory::getSignalTopo(const Vstr& avstr)
{
	VsignalTopoStr = avstr;
}

void TopologyCategory::openRootFile()
{
	m_file = TFile::Open(m_fileName.c_str());
	m_tree = (TTree*)m_file->Get(m_treeName.c_str());

	m_tree->Draw(">>elist",m_cut);
	m_eventlist = (TEventList*)gDirectory->Get("elist");

	m_tree->SetBranchAddress("indexmc", &indexmc);
	m_tree->SetBranchAddress("pdgid", pdgid);
	m_tree->SetBranchAddress("motheridx", motheridx);

	//m_tree->SetBranchAddress("indexmc_p", &indexmc);
	//m_tree->SetBranchAddress("pdgid_p", pdgid);
	//m_tree->SetBranchAddress("motheridx_p", motheridx);

	//m_tree->SetBranchAddress("indexmc_m", &indexmc);
	//m_tree->SetBranchAddress("pdgid_m", pdgid);
	//m_tree->SetBranchAddress("motheridx_m", motheridx);

}

void TopologyCategory::TopoRead()
{

	//Create a new tree
	//write the clone of old tree and the new tree into one new file
	TFile *newfile = new TFile("topo.root","recreate");
	TTree *newtree = m_tree->CloneTree(0);
	//newtree->SetBasketSize("*", 100000);

	Int_t n_signal;
	Int_t n_itopo;
	newtree->Branch("signal", &n_signal,  "n_signal/I");
	newtree->Branch("itopo",  &n_itopo,   "n_itopo/I");

	Long64_t totalEvent = 0;
	Long64_t totalTopo = 0;
	Long64_t nevent = m_tree->GetEntries();
	printf("\t \033[5m\033[1;42;31m%s\033[0m"," total entries:  ");
	cout<<" "<<nevent<<endl<<endl;

	int entriesAftCut = m_eventlist->GetN();
	printf("\t \033[5m\033[1;42;31m%s\033[0m"," entriesAftCut:  ");
	cout<<" "<<entriesAftCut<<endl<<endl;
	for(Int_t i=0; i<entriesAftCut; i++){
		Long64_t treei = m_eventlist->GetEntry(i);
		m_tree->GetEntry(treei);

		totalEvent++;
		Vint parid;
		Vint midx;
		parid.clear();
		midx.clear();
		for (int j=0; j<indexmc; j++)
		{
			midx.push_back(motheridx[j]);
			parid.push_back(pdgid[j]);
		}
		std::string tempLine = TopoString(parid, midx);
		//std::cout << tempLine << std::endl;

		n_signal = 0;
		for (int k=0; k < VsignalTopoStr.size(); k++)
		{
			//std::cout << VsignalTopoStr[k] << std::endl;
			if (tempLine == VsignalTopoStr[k]) { n_signal = 1; break; }
		}

		Bool_t newType = true;
		if (totalTopo != 0)
		{
			int xtopo = 0;
			for (int istr = 0; istr < VtopoStr.size(); istr++)
			{
				if (tempLine == VtopoStr[istr]) 
				{
					newType = false;
					n_itopo = xtopo;
					Vtopo[xtopo]++;
					break; 
				}
				xtopo++;
			}// end of while      
		}// if the first topology type

		if (newType)
		{
			Vtopo.push_back(1);
			VtopoNpar.push_back(indexmc);
			VtopoStr.push_back(tempLine);
			n_itopo = totalTopo;
			for (int k=0; k<indexmc; k++)
			{
				acomTPI.Topo = totalTopo;
				acomTPI.PID = pdgid[k];
				acomTPI.Idx = motheridx[k];
				VcomTPI.push_back(acomTPI);
			}//end loop particle in one new type
			totalTopo++;
		}//end of new type
		newtree->Fill();
	}// loop for all entries

	newtree->Write();
	newfile->Close();
}

void TopologyCategory::TopoLog()
{
	std::ofstream m_outputFile;
	m_outputFile.open("log.txt", ios_base::out);

	Vint Vtopoback = Vtopo;
	int totalTopo = Vtopo.size();
	for (int i = 0; i < totalTopo; i++)
	{
		topoIdx.push_back(i);
	}
	BubbleSort(topoIdx, Vtopo);
	BubbleSort(VtopoNpar, Vtopoback);

	std::cout << "the total topology number is: " << totalTopo << std::endl;
	m_outputFile << "the topology category statisticcal information" 
		<< std::endl;
	m_outputFile << "the total topology number is: " << totalTopo << std::endl;
	m_outputFile << "type      " << "Event Number" << std::endl;
	for (int i=0; i<totalTopo; i++)
	{
		m_outputFile.flags(ios::left | ios::fixed);
		m_outputFile << setw(10) << topoIdx[i] 
			<< setw(10) << Vtopo[i] << std::endl;
	}
	m_outputFile.close();

}

void TopologyCategory::TopoWrite()
{

	//open the file to write
	ofstream m_outputFile;
	if (m_outputFileName.empty()) { m_outputFileName = "mclist.txt"; }
	m_outputFile.open(m_outputFileName.c_str(), ios_base::out); 
	if (!m_outputFile)
	{
		std::cout << "can't open the file: mclist.txt " << std::endl;
		exit(-1);
	}

	int totalTopo = Vtopo.size();

	m_outputFile << "the topology category statisticcal information" 
		<< std::endl;
	m_outputFile << "the total topology number is: " << totalTopo << std::endl;

	for (int i=0; i<totalTopo; i++)
	{
		m_outputFile.flags(ios::left | ios::fixed);
		m_outputFile << "\ntopology: " << setw(10) << topoIdx[i]
			<< " Events: "    << setw(10) << Vtopo[i] 
			<< std::endl << std::endl;
		m_outputFile.flags(ios::right | ios::fixed);
		m_outputFile << std::setw(30) <<"Event listing (summary)" << endl;
		m_outputFile.flags(ios::left | ios::fixed);
		m_outputFile << std::setw(10) << "I";
		m_outputFile << std::setw(15) << "particle/jet";
		m_outputFile.flags(ios::right | ios::fixed);
		m_outputFile << std::setw(8) << "KF";
		m_outputFile << std::setw(8) << "orig" << endl;
		//m_outputFile << endl << endl;

		int index = 0;
		for (int j=0; j<VcomTPI.size(); j++)
		{
			if (index == VtopoNpar[i]) break;
			if (topoIdx[i] == VcomTPI[j].Topo)
			{
				std::string mcname = aParticleObject.GetParName(VcomTPI[j].PID);
				m_outputFile.flags(ios::left | ios::fixed);
				m_outputFile << setw(10) << index; 
				m_outputFile << setw(15) << mcname;
				m_outputFile.flags(ios::right | ios::fixed);
				m_outputFile << setw(8) << setprecision(0) << VcomTPI[j].PID;
				m_outputFile << setw(8) << setprecision(0) << VcomTPI[j].Idx;
				m_outputFile.flags(ios::right | ios::showpoint | ios::fixed);
				m_outputFile << endl;
				index++;
			}
		}
	}
	m_outputFile.close();
}
