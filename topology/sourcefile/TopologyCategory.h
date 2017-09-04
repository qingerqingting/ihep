/* @(#)TopologyCategory.h
 */

#ifndef _TOPOLOGYCATEGORY_H
#define _TOPOLOGYCATEGORY_H 1

#include "ParticleObject.h"

#include <iostream>
#include <iomanip> //for setw
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <TROOT.h>
#include <TTree.h>
#include <TCut.h>
#include <TChain.h>
#include <TFile.h>
#include "TTree.h"
#include "TFile.h"
#include "TCut.h"
#include "TString.h"
#include "TEventList.h"

using namespace std;

typedef std::vector<int> Vint;
typedef std::vector<std::string> Vstr;

class TopologyCategory 
{
public:
  TopologyCategory(const Vstr& avstr, const std::string& strTCut);
  ~TopologyCategory();

  void getSignalTopo(const Vstr&);
  void openRootFile();
  void TopoRead();
  void TopoWrite();
  void TopoLog();

  void BubbleSort(std::vector<int> &, std::vector<int> &);
  std::string TopoString(std::vector<int>, std::vector<int>);

private:

  std::vector<std::string> VsignalTopoStr;

  std::string m_treeName;
  std::string  m_fileName;

  std::ofstream m_outputFile;
  std::string m_outputFileName;

  TFile *m_file;
  TTree *m_tree;
  TCut  m_cut;
	TEventList *m_eventlist;

  // Declaration of leave types
  int           indexmc;
  int           pdgid[100];   //[indexmc]
  int           motheridx[100];   //[indexmc]

  // List of branches
  TBranch        *b_indexmc;   //!
  TBranch        *b_pdgid;   //!
  TBranch        *b_motheridx;   //!

  ParticleObject aParticleObject;
  // counter the number of topology category 
  // and the number of events in this topology
  Vint Vtopo; 
  Vint topoIdx;
  Vstr VtopoStr;
  // counter the number of particles in this topology
  Vint VtopoNpar;

  struct comTopoPIDIdx
  {
    int Topo;
    int PID;
    int Idx;
  };
  comTopoPIDIdx acomTPI;
  std::vector<comTopoPIDIdx> VcomTPI;
};

#endif /* _TOPOLOGYCATEGORY_H */

