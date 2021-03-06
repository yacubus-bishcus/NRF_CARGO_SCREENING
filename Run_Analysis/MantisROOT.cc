//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Author:
// Jacob E Bickus, 2021
// MIT, NSE
// jbickus@mit.edu
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
///////////////////////////////////////////////////////////////////////////////
bool debug;

class MantisROOT
{
public:
    MantisROOT(bool debug_in=false);
    ~MantisROOT();

  public:
    static MantisROOT *GetInstance();
    static void Destroy();
    static MantisROOT *instance;

    void CheckAngles(const char* filename, const char* obj1, const char* obj2,
                    int estimate=-1);
    void CheckDet(const char* filename, bool weighted=false, int estimate=-1);
    void CheckEvents(const char* filename, bool Weighted=false,
                    bool Corrected=false, bool copy_to_original_file=false);
    void CheckEventsWResponse(const char* filename, bool Weighted=false);
    void CheckIntObj(const char* onFile, const char* offFile, double Er=1.73354,
                    bool Weighted=false);
    void CheckIntObjRegion(const char* onFilename, const char* offFilename,
                          double regionCutE, TCut regionCut);
    void ChopperWeightandCost(string material, double chopper_thickness,
                              double chopper_radius=7.5);
    void CombineFiles(std::vector<string> filenames,
                      std::vector<string> objects_to_combine,
                      const char* outfilename);
    void CopyTrees(const char* filename, std::vector<string> trees_to_copy,
                  const char* outfilename);
    void CreateDetectorResponseFunction(const char* filename,
                                        const char* outfilename, double maxE=1.8,
                                        bool drawFigures=false);
    void CreateDetEfficiencyCurve(std::vector<double> list_of_energies,
                                  std::vector<double> list_of_efficiencies,
                                  string DetType);
    void CreateDetEfficiencyCurve(string DetType);
    void CreateOptPerEnergy(const char* filename, double e_cut=1.4);
    TGraph* CreateScintillationDistribution(std::vector<double> list_of_energies, std::vector<double> list_of_cross_sections);
    void CreateScintillationDistribution(string a, string b, string c, string d);
    TGraph* CreateScintillationDistribution(double scale=1.);
    void DrawWeights(TGraph* input, TGraph* sample, string canvas_name="c1");
    double Energy2Wave(double energy, string unit="eV");
    void GetCountIntegralAndError(const char* filename, bool weighted=false);
    double GetCounts(const char* filename, bool weighted=false);
    //void GetCounts(string filebase, int filestart=0, int filenum=1, bool weighted=false);
    void GetScintillationDistribution(const char* filename, bool Corrected=true);
    void Integral(TTree* tree);
    void Integral(std::vector<TTree*> trees);
    void Integral(std::vector<TTree*> trees, TCut cut1);
    TFile* OpenFile(const char* filename);
    void PredictThickness(std::vector<string> objects, bool write2file=false);
    void PredictThickness(std::vector<string> objects, double resonance_energy,
                          bool write2file=false);
    void PrepInputSpectrum(const char*, bool drawPlots=false, bool smooth=false,
                          const char* object="ChopIn", bool Weighted=false,
                          double deltaE=0.000005, double minimum_energy=0.0);
    void PrepIntObjInputSpectrum(const char* filename, const char* ObjName,
                                std::vector<double> energy_regions,
                                std::vector<double> bin_widths,
                                bool Weighted=false, bool normalize=true,
                                bool drawWeights=false);
    void RunSummary(const char* onFile, const char* offFile, bool intObjIn=true,
                    bool weighted=false, bool drawPlots=false,
                    bool drawBeamEnergyPlots=false);
    void Sampling(const char *filename, const char* object_to_sample,
                  bool drawPlots=false, bool smooth=false,
                  bool Weighted=false, string sample_element="U",
                  double deltaE=0.000005, bool checkZero=false,
                  double non_nrf_energy_cut=1.5, double weighting_factor=10000);
    void Sig2Noise(std::vector<string> filenames, string object,
                  bool Weighted=false, bool Corrected=false,
                  bool place_cut=false, TCut cut1="NA");
    void SimpleSampling(const char* filename, const char* object_to_sample,
                        bool smooth=false, bool Weighted=false,
                        double deltaE_large_bin_width=0.001,
                        double deltaE_small_bin_width=0.000005,
                        double cut_energy1=0.5, double cut_energy2=1.0,
                        double weighting_factor=1000,
                        double weighting_factor2=10, bool checkZero=false,
                        bool drawWeights=false);
    TGraph* VariableBinWidthRebin(const char* filename, const char* ObjName,
                                  std::vector<double> energy_regions,
                                  std::vector<double> bin_widths,
                                  std::vector<double> samplev,
                                  bool weighted=false, bool normalize=true,
                                  bool for_weighted_spectrum=false);
    double Wave2Energy(double wavelength, string unit="m");
    void ZScore(const char* filenameOn, bool weightedOn, const char* filenameOff,
                bool weightedOff);
    void ZScore(double countsOn, double countsOff);
    void ZScore(double countsOn, double errorOn, double countsOff,
                double errorOff);

private:

    // Zip Tuple 5
    template<typename A, typename B, typename C, typename D, typename E>
    void zip(const std::vector<A> &a, const std::vector<B> &b, const std::vector<C> &c,
      const std::vector<D> &d, const std::vector<E> &e,
              std::vector<std::tuple<A,B,C,D,E>> &zipped)
    {
      for(size_t i=0;i<a.size();++i)
      {
        zipped.push_back(std::make_tuple(a[i],b[i],c[i],d[i],e[i]));
      }
    }

    template<typename A, typename B, typename C, typename D, typename E>
    void unzip(const std::vector<std::tuple<A,B,C,D,E>> &zipped,
                std::vector<A> &a, std::vector<B> &b, std::vector<C> &c, std::vector<D> &d, std::vector<E> &e)
    {
      for(size_t i=0;i<a.size();++i)
      {
        a[i] = std::get<0>(zipped[i]);
        b[i] = std::get<1>(zipped[i]);
        c[i] = std::get<2>(zipped[i]);
        d[i] = std::get<3>(zipped[i]);
        e[i] = std::get<4>(zipped[i]);
      }
    }

    // Zip tuple 4

    template<typename A, typename B, typename C, typename D>
    void zip(const std::vector<A> &a, const std::vector<B> &b, const std::vector<C> &c, const std::vector<D> &d,
              std::vector<std::tuple<A,B,C,D>> &zipped)
    {
      for(size_t i=0;i<a.size();++i)
      {
        zipped.push_back(std::make_tuple(a[i],b[i],c[i],d[i]));
      }
    }

    template<typename A, typename B, typename C, typename D>
    void unzip(const std::vector<std::tuple<A,B,C,D>> &zipped,
                std::vector<A> &a, std::vector<B> &b, std::vector<C> &c, std::vector<D> &d)
    {
      for(size_t i=0;i<a.size();++i)
      {
        a[i] = std::get<0>(zipped[i]);
        b[i] = std::get<1>(zipped[i]);
        c[i] = std::get<2>(zipped[i]);
        d[i] = std::get<3>(zipped[i]);
      }
    }
    // Zip tuple 3

    template<typename A, typename B, typename C>
    void zip(const std::vector<A> &a, const std::vector<B> &b, const std::vector<C> &c,
              std::vector<std::tuple<A,B,C>> &zipped)
    {
      for(size_t i=0;i<a.size();++i)
      {
        zipped.push_back(std::make_tuple(a[i],b[i],c[i]));
      }
    }

    template<typename A, typename B, typename C>
    void unzip(const std::vector<std::tuple<A,B,C>> &zipped,
                std::vector<A> &a, std::vector<B> &b, std::vector<C> &c)
    {
      for(size_t i=0;i<a.size();++i)
      {
        a[i] = std::get<0>(zipped[i]);
        b[i] = std::get<1>(zipped[i]);
        c[i] = std::get<2>(zipped[i]);
      }
    }


    // Zip Pair

    template<typename A, typename B>
    void zip(const std::vector<A> &a, const std::vector<B> &b,
              std::vector<std::pair<A,B>> &zipped)
    {
      for(size_t i=0;i<a.size();++i)
      {
        zipped.push_back(std::make_pair(a[i],b[i]));
      }
    }

    template<typename A, typename B>
    void unzip(const std::vector<std::pair<A,B>> &zipped,
                std::vector<A> &a, std::vector<B> &b)
    {
      for(size_t i=0;i<a.size();++i)
      {
        a[i] = zipped[i].first;
        b[i] = zipped[i].second;
      }
    }

  private:
    TH1D* BuildBremSampling(const std::vector<double> E_below_threshold, double non_nrf_energy_cut, double deltaE, double Emax, double theweight);
    TH1D* BuildSimpleSample(const char* filename, const char* obj, double deltaE, double cut_energy1, double cut_energy2, double weight1, double weight2);
    void CheckFile(const char*);
    void Compute(const char*, time_t, bool, bool);
    void CopyATree(const char*, const char*, const char*);
    void CopyATreeNoWeight(const char*, const char*, const char*);
    string EraseSubStr(string&, const string&);
    void GetCountIntegralAndError(const char*, bool weighted, double& counts, double& error);
    void hIntegral(TH1*);
    double hIntegralReturn(TTree*, bool, TCut cut1="NA");
    double hIntegralReturnWeightedCounts(TTree*, double cut_energy=5e-6);
    double hIntegralReturnWeightedEnergy(TTree*, double cut_energy=5e-6);
    void hIntegral(TTree*, TCut);
    TGraph* PrepInputSpectrum(const char* filename, const char* obj, bool smooth, bool Weighted, double deltaE, bool checkZero);
    void Rescale(const char*, double, bool write2file=false);
    void Rescale(const char*, bool write2file=false);
    double ReturnMax(const char*, const char*);
    double ReturnMin(const char*, const char*);
    void SNR_IntObj(const char*, bool);
    void SNR_Det(const char*, bool, bool, bool, TCut cut1="NA");
    void WriteSampling(TGraph*, TGraph*, TH1D*, double);
    void WriteSampling(TGraph*, double);
    void WriteSampling(TH1D*);
    void CheckZeros(TH1D* &hin, int nbins);

    double hc = 6.62607004e-34*299792458;

};

MantisROOT *MantisROOT::instance = 0;


MantisROOT *MantisROOT::GetInstance()
{
  if(instance == 0)
  {
    instance = new MantisROOT();
  }
  std::cout << "Mantis ROOT Analysis Package for Mantis Output Analysis" << std::endl;
  std::cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << std::endl;
  std::cout << "Author:" <<std::endl;
  std::cout << "Jacob E Bickus, 2021" << std::endl;
  std::cout << "MIT, NSE" << std::endl;
  std::cout << "jbickus@mit.edu" << std::endl;
  std::cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << std::endl;
  return instance;
}

MantisROOT::MantisROOT(bool debug_in=false)
{
  debug = debug_in;
  if(debug)
    std::cout << "Set to Debugging Mode!" << std::endl;
}

MantisROOT::~MantisROOT()
{}

void MantisROOT::Destroy()
{
  if(instance != 0)
  {
   delete instance;
   instance = 0;
  }
}

// PUBLIC MEMBER FUNCTIONS
// ************************************************************************** //
// ************************************************************************** //
// ************************************************************************** //

void MantisROOT::CheckAngles(const char* filename, const char* obj1, const char* obj2, int estimate=-1)
{
  if(debug)
    std::cout << "MantisROOT::CheckAngles -> Checking Angles..." << std::endl;

  CheckFile(filename);

  if(debug)
    std::cout << "MantisROOT::CheckAngles -> Opening File." << std::endl;

  TFile *f = new TFile(filename);
  f->cd();

  if(debug)
    std::cout << "MantisROOT::CheckAngles -> File opened." << std::endl;

  TTree *t1, *t2;
  f->GetObject(obj1,t1);
  f->GetObject(obj2,t2);
  t1->SetEstimate(estimate);
  t2->SetEstimate(estimate);

  int entries = t1->Draw("Theta:Phi:EventID","","goff");

  if(debug)
    std::cout << "MantisROOT::CheckAngles -> IntObjOut Entries: " << entries << std::endl;

  Double_t* thetas = t1->GetVal(0);
  Double_t* phis = t1->GetVal(1);
  Double_t* eventID = t1->GetVal(2);

  std::vector<double> thetasv;
  std::vector<double> phisv;
  std::vector<int> eventsv;

  if(estimate == -1)
  {
    for(int i=0;i<entries;++i)
    {
      thetasv.push_back(thetas[i]);
      phisv.push_back(phis[i]);
      eventsv.push_back((int)eventID[i]);
    }
  }
  else
  {
    for(int i=0;i<estimate;++i)
    {
      thetasv.push_back(thetas[i]);
      phisv.push_back(phis[i]);
      eventsv.push_back((int)eventID[i]);
    }
  }

  int entries2 = t2->Draw("EventID","","goff");

  if(debug)
    std::cout << "MantisROOT::CheckAngles -> DetInfo Entries: " << entries2 << std::endl;

  Double_t* eventID2 = t2->GetVal(0);
  std::vector<int> events2v;

  if(estimate == -1)
  {
    for(int i=0;i<entries2;++i)
      events2v.push_back((int)eventID2[i]);
  }
  else
  {
    for(int i=0;i<estimate;++i)
      events2v.push_back((int)eventID2[i]);
  }

  //std::cout << "MantisROOT::CheckAngles -> DetInfo Events Grabbed." << std::endl;

  std::cout << "MantisROOT::CheckAngles -> Removing Duplicates and Sorting..." << std::endl;
  std::sort(events2v.begin(),events2v.end());
  events2v.erase(unique(events2v.begin(),events2v.end()),events2v.end());
  if(debug)
    std::cout << "MantisROOT::CheckAngles -> Duplicates Removed. New Vector Size: " << events2v.size() << std::endl;

  // Compare Event IDs
  std::vector<double> det_thetasv;
  std::vector<double> det_phisv;
  std::vector<int> det_eventsv;
  int x;

  if(estimate == -1)
  {
    for(int i=0;i<eventsv.size();++i)
    {
      if(i % 100 == 0)
        std::cout << "\r** Checking Entry: " << i << std::flush;
      // Grab IntObjOut EventID
      x = eventsv[i];
      // Check if DetInfo EventID matches IntObjOut EventID
      auto exists = std::find(events2v.begin(),events2v.end(), x);

      if(exists != events2v.end())
      {
        det_eventsv.push_back(x);
        det_thetasv.push_back(thetasv[i]);
        det_phisv.push_back(phisv[i]);
      }

    }
  }
  else
  {
    for(int i=0;i<estimate;++i)
    {
      if(i % 100 == 0)
        std::cout << "\r** Checking Entry: " << i << std::flush;
      // Grab IntObjOut EventID
      x = eventsv[i];
      // Check if DetInfo EventID matches IntObjOut EventID
      auto exists = std::find(events2v.begin(),events2v.end(), x);

      if(exists != events2v.end())
      {
        det_eventsv.push_back(x);
        det_thetasv.push_back(thetasv[i]);
        det_phisv.push_back(phisv[i]);
      }

    }
  }

  std::cout << std::endl << "MantisROOT::CheckAngles -> Search complete." << std::endl;
  string filename_string = string(filename);
  string filenamebase = EraseSubStr(filename_string, ".root");
  string outfile = "Check_Angles_" + filenamebase + ".root";
  TFile *fout = new TFile(outfile.c_str(),"RECREATE");
  fout->cd();
  string ttree_name = string(obj1) + " Emission Angles for Events found in " + string(obj2);
  TTree *tAngle = new TTree("tAngle",ttree_name.c_str());
  int theEvent;
  double theTheta, thePhi;

  if(debug)
    std::cout << "MantisROOT::CheckAngles -> Assigning Branches..." << std::endl;

  tAngle->Branch("EventID",&theEvent);
  tAngle->Branch("Theta", &theTheta);
  tAngle->Branch("Phi", &thePhi);

  if(debug)
    std::cout << "MantisROOT::CheckAngles -> Filling TTree..." << std::endl;

  for(int i=0;i<det_eventsv.size();++i)
  {
    theEvent = det_eventsv[i];
    theTheta = det_thetasv[i];
    thePhi = det_phisv[i];
    tAngle->Fill();
  }

  if(debug)
    std::cout << "MantisROOT::CheckAngles -> Writing..." << std::endl;

  tAngle->Write();
  std::cout << "MantisROOT::CheckAngles -> Events and Angles written to Check_Angles.root" << std::endl;
  fout->Close();
  f->cd();
  f->Close();


} // end of CheckAngles




void MantisROOT::CheckDet(const char* filename, bool weighted=false, int estimate=-1)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  f->cd();
  TTree *tDet, *tIntObjOut;
  f->GetObject("IntObjOut",tIntObjOut);
  f->GetObject("DetInfo",tDet);
  tIntObjOut->SetEstimate(estimate);
  tDet->SetEstimate(estimate);

  int intObj_entries = tIntObjOut->Draw("EventID","","goff");
  Double_t* intObj_ids = tIntObjOut->GetVal(0);

  int det_entries = 0;

  if(weighted)
    det_entries = tDet->Draw("EventID:Energy:Time:Weight","","goff");
  else
    det_entries = tDet->Draw("EventID:Energy:Time","","goff");

  Double_t* det_ids = tDet->GetVal(0);
  Double_t* det_energies = tDet->GetVal(1);
  Double_t* det_times = tDet->GetVal(2);

  int n_intObj = 0;
  int n_det = 0;
  if(estimate == -1)
  {
    n_intObj = intObj_entries;
    n_det = det_entries;
  }
  else
  {
    n_intObj = estimate;
    n_det = estimate;
  }

  Double_t *det_weights = new Double_t[n_det];

  if(weighted)
    det_weights = tDet->GetVal(3);

  if(debug)
    std::cout << "MantisROOT::CheckDet -> All Objects Grabbed!" << std::endl;

  std::vector<int> intObj_eventsv, det_eventsv;
  std::vector<Double_t> det_energiesv, det_weightsv, det_timesv;
  std::vector<string> det_creationsv;

  for(int i=0;i<n_intObj;++i)
    intObj_eventsv.push_back((int)intObj_ids[i]);

  Char_t creations[16];
  tDet->SetBranchAddress("CreatorProcess", &creations);

  for(int i=0;i<n_det;++i)
  {
    det_eventsv.push_back((int)det_ids[i]);
    det_energiesv.push_back(det_energies[i]);
    tDet->GetEntry(i);
    string creator_string = string(creations);
    det_creationsv.push_back(creator_string);
    det_timesv.push_back(det_times[i]);
    if(weighted)
      det_weightsv.push_back(det_weights[i]);
  }

  std::sort(intObj_eventsv.begin(), intObj_eventsv.end());
  intObj_eventsv.erase(unique(intObj_eventsv.begin(),intObj_eventsv.end()),intObj_eventsv.end());
  std::cout << "MantisROOT::CheckDet -> IntObj Event Vector Size: " << intObj_eventsv.size() << std::endl;
  std::cout << "MantisROOT::CheckDet -> DetInfo Event Vector Size: " << det_eventsv.size() << std::endl;

  // Zipping Method sorting
  std::vector<std::tuple<int, double, string, double>> zipped4; // no weights
  std::vector<std::tuple<int, double, string, double, double>> zipped5; // weights

  if(weighted)
  {
    zip(det_eventsv, det_energiesv, det_creationsv, det_timesv, det_weightsv, zipped5);
    std::sort(zipped5.begin(),zipped5.end());
    unzip(zipped5, det_eventsv, det_energiesv, det_creationsv, det_timesv, det_weightsv);
  }
  else
  {
    zip(det_eventsv, det_energiesv, det_creationsv, det_timesv, zipped4);
    std::sort(zipped4.begin(),zipped4.end());
    unzip(zipped4, det_eventsv, det_energiesv, det_creationsv, det_timesv);
  }

  std::vector<int> final_det_eventsv;
  std::vector<double> final_det_energiesv, final_det_weightsv, final_det_timesv;
  std::vector<string> final_det_creationsv;

  std::vector<int> errorneous_det_eventsv;
  std::vector<double> errorneous_det_weightsv;
  int x=0;
  int index = 0;
  int tmp_index;
  // Now Complete check
  while(index < det_eventsv.size())
  {
    if(!debug)
      std::cout << "\r** Checking Entry: " << index << std::flush;
    else
      std::cout << "Checking Entry: " << index << std::endl;

    // Grab Det EventID
    x = det_eventsv[index];

    if(debug)
      std::cout << "X: " << x << std::endl;

    // Check if DetInfo EventID matches IntObjOut EventID
    auto exists = std::find(intObj_eventsv.begin(),intObj_eventsv.end(), x);

    // if found write event info to new vectors
    if(exists != intObj_eventsv.end())
    {
      final_det_eventsv.push_back(x);
      final_det_energiesv.push_back(det_energiesv[index]);
      final_det_creationsv.push_back(det_creationsv[index]);
      final_det_timesv.push_back(det_timesv[index]);

      if(weighted)
        final_det_weightsv.push_back(det_weightsv[index]);

      int counter = 0;
      while(counter >= 0)
      {
        counter++;
        tmp_index = index + counter;
        if(x == det_eventsv[index+counter])
        {
          final_det_eventsv.push_back(x);
          final_det_energiesv.push_back(det_energiesv[index+counter]);
          final_det_creationsv.push_back(det_creationsv[index+counter]);
          final_det_timesv.push_back(det_timesv[index+counter]);

          if(weighted)
            final_det_weightsv.push_back(det_weightsv[index+counter]);

        } // end of if(x == det_eventsv[index+counter])
        else
        {
          index = tmp_index;
          counter = -1;
          if(debug)
          {
            //std::cout << "While Else Counter: " << counter << std::endl;
            std::cout << "While Else Index: " << index << std::endl;
          }
        } // end of else
      } // end of while counter > 0
    } // end of if exists !=
    else
    {
      errorneous_det_eventsv.push_back(x);

      if(weighted)
        errorneous_det_weightsv.push_back(det_weightsv[index]);

      index++;

      if(debug)
        std::cout << "Else Index: " << index << std::endl;
    } // end of else

  } // end of while index < det_eventsv.size()

  // Write vectors to new TTree
  string outfile = "Corrected_DetInfo_" + string(filename);

  if(debug)
  {
    std::cout << "MantisROOT::CheckDet -> Writing Corrected DetInfo to file: "
              << outfile << std::endl;
  }

  TFile *fout = new TFile(outfile.c_str(),"RECREATE");
  fout->cd();

  int a;
  double b,d,e;
  string c;
  TTree* Corrected_DetInfo = new TTree("Corrected_DetInfo","Corrected Detector Information");
  Corrected_DetInfo->Branch("EventID",&a);
  Corrected_DetInfo->Branch("Energy",&b);
  Corrected_DetInfo->Branch("CreatorProcess",&c);
  Corrected_DetInfo->Branch("Time",&d);

  if(weighted)
    Corrected_DetInfo->Branch("Weight",&e);

  if(debug)
    std::cout << "MantisROOT::CheckDet -> Corrected DetInfo Filling..." << std::endl;

  for(int i=0;i<final_det_eventsv.size();++i)
  {
    a = final_det_eventsv[i];
    b = final_det_energiesv[i];
    c = final_det_creationsv[i];
    d = final_det_timesv[i];

    if(weighted)
      e = final_det_weightsv[i];

    Corrected_DetInfo->Fill();
  }

  int h;
  double g;
  TTree* Errorneous_DetInfo = new TTree("Erroneous_DetInfo","Erroneous Detector Information");
  Errorneous_DetInfo->Branch("EventID",&h);

  if(weighted)
    Errorneous_DetInfo->Branch("Weight",&g);

  for(int i=0;i<errorneous_det_eventsv.size();++i)
  {
    h = errorneous_det_eventsv[i];

    if(weighted)
      g = errorneous_det_weightsv[i];

    Errorneous_DetInfo->Fill();
  }

  if(debug)
    std::cout << std::endl << "MantisROOT::CheckDet -> Corrected DetInfo Filled." << std::endl;

  Corrected_DetInfo->Write();
  Errorneous_DetInfo->Write();
  std::cout << std::endl << "MantisROOT::CheckDet -> Corrected DetInfo Written to file: " << outfile << std::endl;

  fout->Close();

  std::cout <<"MantisROOT::CheckDet -> Complete." << std::endl;

} // end of CheckDet Function



void MantisROOT::CheckEvents(const char* filename, bool Weighted=false, bool Corrected=false, bool copy_to_original_file=false)
{
  CheckFile(filename);
  time_t timer;
  time_t time_start = std::time(&timer);
  Compute(filename, time_start, Weighted, Corrected);
  string file_ce = "w_events_" + string(filename);

  if(copy_to_original_file)
  {
    if(Weighted)
      CopyTrees(file_ce.c_str(), {"Weight","event_tree","event_tree2"}, filename);
    else
      CopyTrees(file_ce.c_str(), {"event_tree","event_tree2"}, filename);
  }

  std::cout << "MantisROOT::CheckEvents -> COMPLETE!" << std::endl;
} // end of CheckEvents Function


void MantisROOT::CheckEventsWResponse(const char* filename, bool Weighted=false)
{
  CheckFile(filename);
  TFile* f = TFile::Open(filename);
  f->cd();
  TTree *t_nrf, *t_det;
  f->GetObject("NRF",t_nrf);
  f->GetObject("DetInfo",t_det);
  if(debug)
  {
    t_nrf->SetEstimate(1000);
    t_det->SetEstimate(1000);
    std::cout << "MantisROOT::CheckEventsWResponse -> Debugging checking 1000 Events" << std::endl;
  }
  else
  {
    t_nrf->SetEstimate(-1);
    t_det->SetEstimate(-1);
  }

  int nrf_event, det_event;
  double nrf_energy;
  double det_numpe, weight, beamEnergy;
  t_nrf->SetBranchAddress("EventID", &nrf_event);
  t_nrf->SetBranchAddress("Energy", &nrf_energy);

  t_det->SetBranchAddress("EventID", &det_event);
  t_det->SetBranchAddress("NumPE2",  &det_numpe);
  t_det->SetBranchAddress("BeamEnergy", &beamEnergy);
  t_det->SetBranchAddress("Weight",  &weight);

  std::vector<int> nrf_eventsv, det_eventsv;
  std::vector<double> det_pev, det_weightv;
  if(debug)
  {
    for(int i=0;i<1000;++i)
    {
      t_nrf->GetEntry(i);
      if(nrf_energy > 1.65)
        nrf_eventsv.push_back(nrf_event);
    }

    for(int i=0;i<1000;++i)
    {
      t_det->GetEntry(i);
      if((beamEnergy < 1.66 && beamEnergy > 1.64) || (beamEnergy < 1.74 && beamEnergy > 1.73))
      {
        det_eventsv.push_back(det_event);
        det_pev.push_back(det_numpe);
        det_weightv.push_back(weight);
      }
    }

  }
  else
  {
    for(unsigned long int i=0;i<t_nrf->GetEntries();++i)
    {
      t_nrf->GetEntry(i);
      if(nrf_energy > 1.65)
        nrf_eventsv.push_back(nrf_event);
    }

    for(unsigned long int i=0;i<t_det->GetEntries();++i)
    {
      t_det->GetEntry(i);
      if((beamEnergy < 1.66 && beamEnergy > 1.64) || (beamEnergy < 1.74 && beamEnergy > 1.73))
      {
        det_eventsv.push_back(det_event);
        det_pev.push_back(det_numpe);
        det_weightv.push_back(weight);
      }
    }
  }
  // erase duplicate NRF events
  std::sort(nrf_eventsv.begin(), nrf_eventsv.end());
  nrf_eventsv.erase(unique(nrf_eventsv.begin(), nrf_eventsv.end()),nrf_eventsv.end());

  std::cout << "Checking " << nrf_eventsv.size() << " NRF Events." << std::endl
  << "Checking " << det_eventsv.size() << " Detected Events." << std::endl;

  int x = 0;
  std::vector<int> matching_events;
  std::vector<double> nrf_to_detpe, nrf_to_detweight;
  for(int i=0;i<det_eventsv.size();++i)
  {
    if(i%100==0)
    {
      std::cout << "\r** Checking Entry: " << i << std::flush;
    }

    x = det_eventsv.at(i);
    // Check if NRF EventID is found in DetInfo Vector
    auto exists = std::find(nrf_eventsv.begin(),nrf_eventsv.end(), x);

    if(exists != nrf_eventsv.end())
    {
      // if the eventID is found in detinfo write to new vector
      matching_events.push_back(x);
      nrf_to_detpe.push_back(det_pev.at(i));
      nrf_to_detweight.push_back(det_weightv.at(i));
    }
  }
  
  string check_filename = "Checked_" + string(filename);
  TFile* fout = new TFile(check_filename.c_str(),"RECREATE");
  fout->cd();
  TTree* t_out = new TTree("DetInfo","Detected NRF Events");
  int events;
  double numpe, detweight;
  t_out->Branch("EventID", &events);
  t_out->Branch("NumPE2", &numpe);
  t_out->Branch("Weight", &detweight);

  for(int i=0;i<matching_events.size();++i)
  {
    events = matching_events.at(i);
    numpe = nrf_to_detpe.at(i);
    detweight = nrf_to_detweight.at(i);
    t_out->Fill();
  }

  std::cout << "Total Detected NRF Events: " << t_out->GetEntries() << std::endl;

  t_out->Write();
  std::cout << "MantisROOT::CheckEventsWResponse -> Written to file: " << check_filename << std::endl;
  fout->Close();

  std::cout << "MantisROOT::CheckEventsWResponse -> COMPLETE." << std::endl;
}



void MantisROOT::CheckIntObj(const char* onFile, const char* offFile, double Er=1.73354, bool Weighted=false)
{
  CheckFile(onFile);
  CheckFile(offFile);

  // On Analysis
  TFile *f = new TFile(onFile);
  if(f ==0)
  {
    std::cout << "MantisROOT::CheckIntObj -> File " << onFile << " NULL!" << std::endl;
    exit(1);
  }
  bool confirmf = f->cd();
  if(!confirmf)
  {
    std::cout << "MantisROOT::CheckIntObj -> Cound Not Change into " << onFile << " directory." << std::endl;
    exit(1);
  }
  TTree *inTree, *inTree3;
  f->GetObject("IntObjIn", inTree);
  f->GetObject("DetInfo", inTree3);
  double teMax = inTree->GetMaximum("Energy");
  std::cout << "MantisROOT::CheckIntObj -> " << onFile << " IntObjIn grabbed." << std::endl;
  double emin = Er - 100e-6;
  double emax = Er + 100e-6;
  TH1D *e1 = new TH1D("e1","Incident Interrogation Object 2eV Binning", 100, emin, emax);
  TH1D *e3 = new TH1D("e3","Incident Interrogation Object Full Spectrum", 500, 0., teMax);
  TH1D *e5 = new TH1D("e5","Detected",100, 0., 5e-6);
  if(Weighted)
  {
    inTree->Draw("Energy>>e1","Weight","goff");
    inTree3->Draw("Energy>>e5","Weight","goff");
  }
  else
  {
    inTree->Draw("Energy>>e1","","goff");
    inTree3->Draw("Energy>>e5","","goff");
  }

  e1->SetStats(0);
  e5->SetStats(0);
  e1->Sumw2();
  e5->Sumw2();
  e1->Print();
  e5->Print();

  if(Weighted)
    inTree->Draw("Energy>>e3","Weight","goff");
  else
    inTree->Draw("Energy>>e3","","goff");

  e3->SetStats(0);
  e3->Sumw2();
  e3->Print();

  // Off Analysis
  TFile *f2 = new TFile(offFile);
  if(f2 ==0)
  {
    std::cout << "MantisROOT::CheckIntObj -> ERROR File " << offFile << " NULL!" << std::endl;
    exit(1);
  }
  bool confirmf2 = f2->cd();
  if(!confirmf2)
  {
    std::cout << "MantisROOT::CheckIntObj -> ERROR Could NOT Change into " << offFile << " directory." << std::endl;
    exit(1);
  }

  TTree *inTree2, *inTree4;
  f2->GetObject("IntObjIn", inTree2);
  f2->GetObject("DetInfo", inTree4);
  std::cout << "MantisROOT::CheckIntObj -> " << offFile << " IntObjIn grabbed." << std::endl;

  TH1D *e2 = new TH1D("e2","Incident Interrogation Object 2eV Binning", 100, emin, emax);
  TH1D *e4 = new TH1D("e4", "Incident Interrogation Object Full Spectrum", 500, 0., teMax);
  TH1D *e6 = new TH1D("e6", "Detected",100,0.,5e-6);
  if(Weighted)
  {
    inTree2->Draw("Energy>>e2","Weight","goff");
    inTree4->Draw("Energy>>e6","Weight","goff");
  }
  else
  {
    inTree2->Draw("Energy>>e2","","goff");
    inTree4->Draw("Energy>>e6","","goff");
  }

  e2->SetStats(0);
  e6->SetStats(0);
  e2->Sumw2();
  e6->Sumw2();
  e2->SetLineColor(kRed);
  e6->SetLineColor(kRed);
  e2->Print();
  e6->Print();

  if(Weighted)
    inTree2->Draw("Energy>>e4","Weight","goff");
  else
    inTree2->Draw("Energy>>e4","","goff");

  e4->SetStats(0);
  e4->Sumw2();
  e4->SetLineColor(kRed);
  e4->Print();

  TCanvas *c1 = new TCanvas("c1","Incident Interrogation Object 2eV Binning",600,400);
  c1->cd();
  e2->Draw("h");
  f->cd();

  e1->Draw("h,SAME");

  e2->GetXaxis()->SetTitle("Incident Energy [MeV]");
  e2->GetYaxis()->SetTitle("Counts/2eV");

  auto legend = new TLegend();
  legend->SetHeader("Chopper State", "C");
  legend->AddEntry(e1, "Chopper On");
  legend->AddEntry(e2, "Chopper Off");
  legend->Draw();

  TCanvas *c2 = new TCanvas("c2","Incident Interrogation Object Full Spetrum",600,400);
  c2->cd();
  e3->Draw("h");
  f2->cd();

  e4->Draw("h,SAME");

  e3->GetXaxis()->SetTitle("Incident Energy [MeV]");
  e3->GetYaxis()->SetTitle("Counts");

  auto legend2 = new TLegend();
  legend2->SetHeader("Chopper State","C");
  legend2->AddEntry(e3, "Chopper On");
  legend2->AddEntry(e4, "Chopper Off");
  legend2->Draw();

  TCanvas* c3 = new TCanvas("c3","Detected",600,400);
  c3->cd();
  f->cd();
  e5->Draw("h");
  f2->cd();
  e6->Draw("h,SAME");

  e5->GetXaxis()->SetTitle("Energy [MeV]");
  e5->GetYaxis()->SetTitle("Counts");

  auto legend3 = new TLegend();
  legend3->SetHeader("Chopper State","C");
  legend3->AddEntry(e5, "Chopper On");
  legend3->AddEntry(e6, "Chopper Off");
  legend3->Draw();

  ZScore(e3->Integral(), e4->Integral());
  ZScore(e5->Integral(), e6->Integral());

  std::cout << "MantisROOT::CheckIntObj -> Complete." << std::endl;

} // end of CheckIntObj Function



void MantisROOT::CheckIntObjRegion(const char* onFilename, const char* offFilename, double regionCutE, TCut regionCut)
{
  CheckFile(onFilename);
  CheckFile(offFilename);
  TFile* fon = new TFile(onFilename);
  fon->cd();
  TTree* tobj;
  fon->GetObject("IntObjIn",tobj);
  double maxE = tobj->GetMaximum("Energy");
  TH1D* hon = new TH1D("hon","Incident Interrogation Object",100,regionCutE, maxE);
  tobj->Draw("Energy>>hon",regionCut, "goff");
  hon->Sumw2();
  hon->GetXaxis()->SetTitle("Energy [MeV]");
  hon->SetLineColor(kBlue);

  TFile* foff = new TFile(offFilename);
  foff->cd();
  TTree* tobj_off;
  foff->GetObject("IntObjIn",tobj_off);
  TH1D* hoff = new TH1D("hoff","Incident Interrogation Object",100, regionCutE, maxE);
  tobj_off->Draw("Energy>>hoff",regionCut,"goff");
  hoff->SetLineColor(kRed);
  hoff->Sumw2();

  TCanvas* c1 = new TCanvas("c1","Incident Interrogation Object",600,400);
  c1->cd();
  hon->Draw("h");
  hoff->Draw("h,SAME");
  auto legend = new TLegend();
  legend->SetHeader("Chopper State","C");
  legend->AddEntry(hon, "Chopper On");
  legend->AddEntry(hoff, "Chopper Off");
  legend->Draw();
  std::cout << "Chopper On Counts: " << hon->Integral() << std::endl
  << "Chopper On Mean: " << hon->GetMean() << std::endl
  << "Chopper Off Counts: " << hoff->Integral() << std::endl
  << "Chopper Off Mean: " << hoff->GetMean() << std::endl;
  ZScore(hon->Integral(), hoff->Integral());

  std::cout << "MantisROOT::CheckIntObjRegion -> COMPLETE." << std::endl;
} // end of CheckIntObjRegion Function



void MantisROOT::ChopperWeightandCost(string material, double chopper_thickness, double chopper_radius=7.5)
{
  double u_price = 29.75; // dollars per pound
  double t_price = 25.00;
  double l_price = 1.10;
  double u_density = 19.1; // g/cm^3
  double t_density = 19.3;
  double l_density = 11.34;

  double chop_price = 0.;
  double chop_density = 0.;

  if(!material.compare("U"))
  {
    chop_price = u_price;
    chop_density = u_density;
  }
  else if(!material.compare("W"))
  {
    chop_price = t_price;
    chop_density = t_density;
  }
  else if(!material.compare("Pb"))
  {
    chop_price = l_price;
    chop_density = l_density;
  }
  else
  {
    std::cout << "MantisROOT::ChopperWeightandCost -> Material not found."
    << std::endl << "Material Options:"
    << std::endl << "U" << std::endl << "W" << std::endl << "Pb" << std::endl;
    return;
  }
  double chop_volume = 3.14*pow(chopper_radius,2)*chopper_thickness;
  chop_volume = chop_volume/2.;
  double chop_weight = chop_volume*chop_density;
  double g_lbs_conversion = 1./454.;
  chop_weight = chop_weight*g_lbs_conversion;
  std::cout << "MantisROOT::ChopperWeightandCost -> Weight: " << chop_weight
              << " lbs." << std::endl;
  double chop_cost = chop_weight*chop_price;
  std::cout << "MantisROOT::ChopperWeightandCost -> Cost: $" << chop_cost << std::endl;

  std::cout << "MantisROOT::ChopperWeightandCost -> Complete." << std::endl;
} // end of ChopperWeightandCost Function



void MantisROOT::CombineFiles(std::vector<string> filenames, std::vector<string> objects_to_combine, const char* outfilename)
{
  for(int i=0;i<objects_to_combine.size();++i)
  {
    TFile *f = new TFile(outfilename, "update");
    f->cd();
    TChain ch(objects_to_combine[i].c_str());
    for(int i=0;i<filenames.size();++i)
      ch.Add(filenames[i].c_str());

    ch.Merge(f,1000);

    std::cout << objects_to_combine[i] << " merged to " << outfilename << std::endl;
  }

} // end of CombineFiles Function



void MantisROOT::CopyTrees(const char* filename, std::vector<string> trees_to_copy, const char* outfilename)
{
  std::vector<bool> dataList = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  std::vector<string> optList = {"Weight","Brem","ChopIn","ChopOut","NRF","AirIn",
                                  "IntObjIn","IntObjOut","Water","Cherenkov",
                                  "DetInfo","IncDetInfo", "Corrected_DetInfo", "Erroneous_DetInfo",
                                  "event_tree","event_tree2"};
  // check which trees to copy
  for(int i=0;i<trees_to_copy.size();++i)
  {
    for(int j=0;j<optList.size();++j)
    {
      int counter = 0;
      if(!trees_to_copy[i].compare(optList[j]))
      {
        dataList[j] = true;
        continue;
      }
      else
        counter++;

      if(counter == optList.size())
        std::cout << trees_to_copy[i] << " option not found!" << std::endl;

    }
  }

  std::cout << "MantisROOT::CopyTrees -> Copying Tree Status: " << std::endl;
  for(int i=0;i<optList.size();++i)
    std::cout << "\t\t " << optList[i] << " = " << dataList[i] << std::endl;

  for(int i=1;i<optList.size();++i)
  {
    if(dataList[0])
    {
      if(dataList[i])
        CopyATree(filename, optList[i].c_str(), outfilename);
    }
    else
    {
      if(dataList[i])
        CopyATreeNoWeight(filename, optList[i].c_str(), outfilename);
    }
  }

  std::cout << "MantisROOT::CopyTrees -> Complete." << std::endl;
} // end of CopyTrees Function



void MantisROOT::CreateDetectorResponseFunction(const char* filename, const char* outfilename, double maxE=1.8, bool drawFigures=false)
{
  CheckFile(filename);
  TFile* fin = TFile::Open(filename);
  fin->cd();
  TTree* tdet_response;
  tdet_response = (TTree*) fin->Get("DetResponse");
  tdet_response->SetEstimate(-1);

  int x_bins = maxE/10e-3; // set bin width to 10 keV
  double ymax = tdet_response->GetMaximum("NumPE");
  ymax = ymax + 50;
  std::vector<TH1D*> projections;

  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Creating Detector Response Function..." << std::endl;
  TProfile* DetectorResponse = new TProfile("DetectorResponse","Detector Response Function Profile",x_bins, 0., maxE);
  TProfile* ScintillationResponse = new TProfile("ScintillationResponse","Detector Scintillation Response Function Profile",x_bins,0.,maxE);
  TProfile* CherenkovResponse = new TProfile("CherenkovResponse","Detector Cherenkov Response Function Profile",x_bins,0.,maxE);
  TH2D* hDetectorResponse = new TH2D("hDetectorResponse","Detector Response Function",x_bins,0.,maxE, ymax,0.,ymax);
  hDetectorResponse->SetMinimum(10);

  tdet_response->Draw("NumPE:IncidentEnergy>>DetectorResponse","","prof,goff");
  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Detector Response Function Profile Created." << std::endl;
  tdet_response->Draw("NumPE:IncidentEnergy>>hDetectorResponse","","colz,goff");
  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Detector Response Function Histogram Created." << std::endl;
  tdet_response->Draw("NumScintillation:IncidentEnergy>>ScintillationResponse","","prof,goff");
  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Detector Scintillation Response Created." << std::endl;
  tdet_response->Draw("NumCherenkov:IncidentEnergy>>CherenkovResponse","","prof,goff");
  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Detector Cherenkov Response Created." << std::endl;

  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Creating Projection Vector..." << std::endl;
  string hn = "projY_";
  for(int i=0;i<x_bins+1;++i)
  {
    string h_name = hn + std::to_string(i) + "_" + std::to_string(i+1);
    TH1D* h = new TH1D();
    h = hDetectorResponse->ProjectionY(h_name.c_str(),i,i+1);
    if(debug)
    {
      if(i < 2)
      {
        h->Print();
      }
    }
    projections.push_back(h);
    //delete h;
  }

  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Projection Vector complete." << std::endl;

  if(debug)
  {
    for(int i=0;i<5;++i)
      projections[i]->Print();
  }

  if(drawFigures)
  {
    TCanvas* c1 = new TCanvas("c1","Detector Response Function Profile",600,400);
    c1->cd();
    DetectorResponse->GetXaxis()->SetTitle("Incident Plexiglass Energy [MeV]");
    DetectorResponse->GetYaxis()->SetTitle("Number of Detector Photoelectrons");
    DetectorResponse->SetLineColor(kRed);
    DetectorResponse->Draw();

    TCanvas* c2 = new TCanvas("c2","Detector Scintillation Response",600,400);
    c2->cd();
    ScintillationResponse->GetXaxis()->SetTitle("Incident Plexiglass Energy [MeV]");
    ScintillationResponse->GetYaxis()->SetTitle("Number of Detector Scintillation Photoelectrons");
    ScintillationResponse->Draw();

    TCanvas* c3 = new TCanvas("c3","Detector Cherenkov Response",600,400);
    c3->cd();
    CherenkovResponse->GetXaxis()->SetTitle("Incident Plexiglass Energy [MeV]");
    CherenkovResponse->GetYaxis()->SetTitle("Number of Detector Cherenkov Photoelectrons");
    CherenkovResponse->Draw();

    TCanvas* c4 = new TCanvas("c4", "Detector Response Function",600,400);
    c4->cd();
    hDetectorResponse->GetXaxis()->SetTitle("Incident Plexiglass Energy [MeV]");
    hDetectorResponse->GetYaxis()->SetTitle("Number of Detector Photoelectrons");
    hDetectorResponse->SetStats(0);
    gPad->SetLogz();
    hDetectorResponse->Draw("colz");
    DetectorResponse->Draw("SAME");

    auto legend = new TLegend();
    legend->SetHeader("Detector Response","C");
    legend->AddEntry(hDetectorResponse, "Response 2D Histogram");
    legend->AddEntry(DetectorResponse, "Response Profile");
    legend->Draw();
  }


  TFile* fout = new TFile(outfilename,"RECREATE");
  fout->cd();
  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Writting to file: " << outfilename << std::endl;
  for(int i=0;i<projections.size();++i)
    projections[i]->Write();

  DetectorResponse->Write();
  hDetectorResponse->Write();
  ScintillationResponse->Write();
  CherenkovResponse->Write();
  fout->Close();
  std::cout << "MantisROOT::CreateDetectorResponseFunction -> Written to file: " << outfilename << std::endl;
} // end of CreateDetectorResponseFunction Function




void MantisROOT::CreateDetEfficiencyCurve(std::vector<double> list_of_energies, std::vector<double> list_of_efficiencies, string DetType)
{
  std::vector<double> energies, wavelengths, eff;
  int n = list_of_energies.size();
  for(int i=0;i<n;++i)
  {
    energies.push_back(list_of_energies[i]);
    wavelengths.push_back(Energy2Wave(list_of_energies[i],"eV")*1e9); // units nm
    eff.push_back(list_of_efficiencies[i]);
  }

  std::cout << "Energy Range: " << energies[0] << " - " << energies[n-1] << std::endl;

  TF1* f1 = new TF1("f1","(6.62607004e-34*299792458/(x/1e9))/1.60218e-19",wavelengths[0],wavelengths[n-1]);
  TCanvas* c2 = new TCanvas("c2","Input",900,700);
  c2->cd();
  f1->Draw();
  string title = DetType + " Quantum Efficiency";

  TGraph* gDete = new TGraph(n, &energies[0], &eff[0]);
  gDete->GetXaxis()->SetTitle("Energy [eV]");
  gDete->GetYaxis()->SetTitle("Efficiency [%]");
  gDete->SetTitle(title.c_str());

  TCanvas* c1 = new TCanvas("c1","Efficiencies",900,700);
  c1->cd();
  gDete->Draw("AC");
  c1->Update();
  double xmin = energies[0];
  double xmax = c1->GetFrame()->GetX2();
  double ypos = c1->GetFrame()->GetY2();
  TGaxis* axis1 = new TGaxis(xmin, ypos, xmax, ypos, "f1", 510, "-L");
  axis1->SetName("axis1");
  axis1->SetTitle("Wavelength [nm]");
  axis1->SetTitleOffset(-1.1);
  axis1->CenterTitle(kTRUE);
  axis1->SetLabelFont(42);
  axis1->SetLabelSize(0.03);
  axis1->SetTitleSize(0.03);
  //axis1->SetLabelOffset(0.03);
  axis1->SetTitleColor(kRed);
  axis1->SetLineColor(kRed);
  axis1->SetLabelColor(kRed);
  axis1->Draw("same");
  axis1->Print();

  std::cout << "MantisROOT::CreateDetEfficiencyCurve -> Efficiencies Drawn." << std::endl;
} // end of CreateDetEfficiencyCurve Function 1




void MantisROOT::CreateDetEfficiencyCurve(string DetType)
{
  std::vector<double> energies = {1.5400, 1.6500, 1.7711, 1.9074,
                                  2.0663, 2.2959, 2.4796, 2.6000,
                                  2.7551, 2.8500, 3.0995, 3.1500,
                                  3.3300, 3.5000, 3.6000, 3.7500,
                                  3.9000, 4.1330, 4.2750, 4.3500,
                                  4.7686, 4.9590, 5.2500, 5.5000,
                                  5.7500, 5.900, 6.1990, 6.300,
                                  6.5200, 6.8800, 8.2500
                                  };

  std::vector<double> GaAsP_eff = {0.00010, 0.00100, 0.25000, 38.2460,
                                   39.8000, 40.4000, 38.9110, 37.9000,
                                   36.4918, 34.3912, 26.8072, 25.0000,
                                   23.0000, 20.6876, 18.1882, 12.1406,
                                   9.00000, 4.93730, 3.00000, 1.50000,
                                   0.75000, 0.25000, 0.20000, 0.15000,
                                   0.12000, 0.10000, 0.0800, 0.0500,
                                   0.01000, 0.0010, 0.00010
                                  };

  std::vector<double> Bi_eff    = {0.00010, 0.001,  0.6000, 1.5000,
                                   5.00000, 11.0000, 16.000, 20.000,
                                   25.0000, 26.5000, 26.900, 27.100,
                                   27.4637, 28.1950, 28.430, 29.102,
                                   29.1418, 29.3400, 29.450, 29.590,
                                   30.4000, 29.7000, 28.900, 28.150,
                                   27.5000, 27.2500, 26.900, 25.900,
                                   10.0000, 2.50000, 0.2500
                                  };

  if(!DetType.compare("GaAsP"))
    CreateDetEfficiencyCurve(energies, GaAsP_eff, DetType);
  else if(!DetType.compare("Bialkali"))
    CreateDetEfficiencyCurve(energies, Bi_eff, DetType);
  else
  {
    std::cout << "MantisROOT::CreateDetEfficiencyCurve -> ERROR Det Type must either be GaAsP or Bialkali" << std::endl;
    return;
  }

  std::cout << "MantisROOT::CreateDetEfficiencyCurve -> Complete." << std::endl;
} // end of CreateDetEfficiencyCurve Function 2




void MantisROOT::CreateOptPerEnergy(const char* filename, double e_cut=1.4)
{
  CheckFile(filename);
  TFile* f = new TFile(filename);
  f->cd();
  TTree *t_cher, *t_scint;
  f->GetObject("Cherenkov",t_cher);
  f->GetObject("Scintillation",t_scint);
  t_cher->SetEstimate(-1);
  t_scint->SetEstimate(-1);
  TProfile* p1 = new TProfile("p1","Number of Optical Photons Emitted vs Incident Photon Energy",100,0.,e_cut);
  TProfile* p2 = new TProfile("p2","Number of Optical Photons Emitted vs Incident Photon Energy",100,0.,e_cut);
  TProfile* p3 = new TProfile("p3","Number of Optical Photons Emitted vs Incident Photon Energy",100,0.,e_cut);
  string cut_s = "Energy < " + std::to_string(e_cut);
  TCut cut_tcut = cut_s.c_str();
  std::cout << "MantisROOT::CreateOptPerEnergy -> Setting TCut: " << cut_s << std::endl;
  t_cher->Draw("NumSecondaries:Energy>>p1",cut_tcut,"prof,goff");
  t_scint->Draw("NumSecondaries:Energy>>p2",cut_tcut,"prof,goff");

  for(int i=0;i<100;++i)
  {
    double p3_value = p1->GetBinContent(i) + p2->GetBinContent(i);
    p3->Fill(p3->GetBinCenter(i),p3_value);
  }

  double maxCounts = p3->GetBinContent(99);

  p1->SetName("Cherenkov");
  p2->SetName("Scintillation");
  p3->SetName("Optical Photon Sum");
  p1->SetLineColor(kBlue);
  p2->SetLineColor(kRed);
  p3->SetLineColor(kBlack);
  p1->GetXaxis()->SetTitle("Incident Photon Energy [MeV]");
  p1->GetYaxis()->SetTitle("Average Number of Optical Photons Emitted");
  p1->SetStats(1);
  p2->SetStats(1);
  p3->SetStats(0);
  p1->GetYaxis()->SetRangeUser(0,maxCounts);

  TCanvas* c1 = new TCanvas("c1","Optical Photons", 600, 400);
  c1->cd();

  p1->Draw("h");
  p2->Draw("h,SAMES");
  p3->Draw("h,SAME");
  auto legend = new TLegend();
  legend->SetHeader("Optical Process","C");
  legend->AddEntry(p1, "Cherenkov");
  legend->AddEntry(p2, "Scintillation");
  legend->AddEntry(p3, "Sum");
  legend->Draw();
  c1->Update();

  std::cout << "MantisROOT::CreateOptPerEnergy -> COMPLETE." << std::endl;

} // end of CreateOptPerEnergy Function



TGraph* MantisROOT::CreateScintillationDistribution(std::vector<double> list_of_energies, std::vector<double> list_of_cross_sections)
{
  std::vector<double> energies, crossX, wavelengths;
  int n = list_of_energies.size();
  for(int i=0;i<n;++i)
  {
    energies.push_back(list_of_energies[i]);
    crossX.push_back(list_of_cross_sections[i]);
    wavelengths.push_back(Energy2Wave(list_of_energies[i],"eV")*1e9); // units nm
  }

  TGraph* gScint = new TGraph(n, &energies[0], &crossX[0]);
  gScint->GetXaxis()->SetTitle("Energy [eV]");
  gScint->GetYaxis()->SetTitle("Cross Section");
  gScint->SetTitle("Scintillation in Water Emission Distribution");

  TCanvas *c1 = new TCanvas();
  c1->cd();

  double xmin = energies[0];
  double xmax = energies[n-1];
  double ypos = c1->GetFrame()->GetY2();

  TF1* f1 = new TF1("f1","(6.62607004e-34*299792458/(x/1e9))/1.60218e-19",wavelengths[0],wavelengths[n-1]);
  TGaxis* axis1 = new TGaxis(xmin, ypos + 0.03, xmax, ypos + 0.03, "f1", 510, "-L");

  axis1->SetName("axis1");
  axis1->SetTitle("Wavelength [nm]");
  axis1->SetTitleOffset(-1.);
  //axis1->CenterTitle(kTRUE);
  axis1->SetLabelFont(42);
  axis1->SetLabelSize(0.03);
  axis1->SetTitleSize(0.03);
  //axis1->SetLabelOffset(0.03);
  axis1->SetTitleColor(kRed);
  axis1->SetLineColor(kRed);
  axis1->SetLabelColor(kRed);
  axis1->Print();

  gScint->Draw("AC");
  axis1->Draw("same");
  std::cout << "MantisROOT::CreateScintillationDistribution -> Scintillation Distribution Drawn." << std::endl;
  return gScint;
} // end of CreateScintillationDistribution Function 1




void MantisROOT::CreateScintillationDistribution(string a, string b, string c, string d)
{
  std::vector<double> energies = {1.90744, 1.9837, 2.0664, 2.156, 2.25425, 2.3615,
                                  2.4796, 2.6101, 2.75520, 2.9173, 3.0996, 3.306,
                                  3.44400, 3.542405, 3.64659, 3.8149, 4.132806, 4.95936};

  string cmd = a + "*exp(" + b + "*x)";
  string cmd2 = c + "*exp(" + d + "*x)";
  string cmd3 = "(x<3.44400)*" + cmd + " + " + "(x>3.44400)*" + cmd2;

  const char* cmd_cstr = cmd.c_str();
  const char* cmd2_cstr = cmd2.c_str();
  const char* cmd3_cstr = cmd3.c_str();

  TF1* f0 = new TF1("f0","0.0004731*exp(2.215*x)",energies[0], energies[12]);
  TF1* f01 = new TF1("f01","4.687e8*exp(-5.812*x)",energies[12], energies[energies.size() - 1]);
  TF1* f02 = new TF1("f02","(x<3.44400)*0.0004731*exp(2.215*x) + (x>3.44400)*4.687e8*exp(-5.812*x)", energies[0], energies[energies.size() - 1]);

  TF1* f1 = new TF1("f1",cmd_cstr,energies[0],energies[12]);
  TF1* f2 = new TF1("f2",cmd2_cstr, energies[12], energies[energies.size()-1]);
  TF1* f3 = new TF1("f3",cmd3_cstr, energies[0], energies[energies.size() - 1]);

  TCanvas* c2 = new TCanvas("c2","Exponential Rise",600,400);
  TCanvas* c3 = new TCanvas("c3","Exponential Decay",600,400);
  TCanvas* c4 = new TCanvas("c4","Combined Distro",600,400);

  c2->cd();
  f0->SetLineColor(kBlue);
  f1->SetLineColor(kRed);
  f0->Draw();
  f1->Draw("SAME");

  c3->cd();
  f01->SetLineColor(kBlue);
  f2->SetLineColor(kRed);
  f01->Draw();
  f2->Draw("SAME");
  c4->cd();
  f02->SetLineColor(kBlue);
  f3->SetLineColor(kRed);
  f02->Draw();
  f3->Draw("SAME");

  for(int i=0;i<12;++i)
    std::cout << "MantisROOT::CreateScintillationDistribution -> Energy: " << energies[i] << " \t Eval: " << f1->Eval(energies[i]) << std::endl;

  for(int i=12;i<energies.size();++i)
    std::cout << "MantisROOT::CreateScintillationDistribution -> Energy: " << energies[i] << " \t Eval: " << f2->Eval(energies[i]) << std::endl;

  std::cout << std::endl << "MantisROOT::CreateScintillationDistribution -> Complete."
  << std::endl;
} // end of CreateScintillationDistribution Function 2




TGraph* MantisROOT::CreateScintillationDistribution(double scale=1.)
{
  std::cout << "MantisROOT::CreateScintillationDistribution -> Using Default values..." << std::endl;
  std::vector<double> energies = {1.90744, 1.9837, 2.0664, 2.156, 2.25425, 2.3615,
                                  2.4796, 2.6101, 2.75520, 2.9173, 3.0996, 3.306,
                                  3.44400, 3.542405, 3.64659, 3.8149, 4.132806, 4.95936};

  std::vector<double> crossX = {0.134451, 0.148294, 0.164921, 0.185046, 0.209947, 0.240969,
                                0.280459, 0.331664, 0.399644, 0.492194, 0.622117, 0.811069,
                                0.941421, 0.23927, 0.0561113, 0.00538955, 6.45194e-05, 6.49917e-10};

  for(int i=0;i<crossX.size();++i)
    crossX[i] = crossX[i]*scale*(1./0.941421);

  TGraph* gScint = CreateScintillationDistribution(energies, crossX);
  return gScint;
} // end of CreateScintillationDistribution Function 3




double MantisROOT::Energy2Wave(double energy, string unit="eV")
{
  if(!unit.compare("MeV"))
    energy = energy*1e6;
  else if(!unit.compare("keV"))
    energy = energy*1e3;
  else if(!unit.compare("eV"))
    energy = energy;
  else if(!unit.compare("J"))
    energy = energy/1.60218e-19;
  else
  {
    std::cout << "MantisROOT::Energy2Wave -> ERROR Unit not found." << std::endl;
    return -1;
  }

  energy = energy*1.60218e-19; // conversion to joule
  return hc/energy; // units m
} // end of Energy2Wave Function



void MantisROOT::GetCountIntegralAndError(const char* filename, bool weighted=false)
{
  CheckFile(filename);
  TFile* f = new TFile(filename);
  f->cd();
  TTree* tree;
  f->GetObject("DetInfo",tree);
  tree->SetEstimate(-1);
  TH1D* h = new TH1D("h","h",100,0.,tree->GetMaximum("Energy"));
  if(weighted)
    tree->Draw("Energy>>h","Weight","goff");
  else
    tree->Draw("Energy>>h","","goff");

  double error;
  double hIntegral = h->IntegralAndError(0,100,error);

  std::cout << "MantisROOT::GetCountIntegralAndError -> Counts: " << hIntegral << " +- " << error << std::endl;

} // end of GetCountIntegralAndError Public Function




double MantisROOT::GetCounts(const char* filename, bool weighted=false)
{

  CheckFile(filename);
  TFile* f = new TFile(filename);
  f->cd();

  TTree* tree;
  f->GetObject("DetInfo",tree);
  tree->SetEstimate(-1);

  double weights;
  //double profile_counts;
  double histo_counts;
  //double total_profile_counts = 0.;
  double total_histo_counts = 0.;
  double sd_counts = 0.;

  //tree->SetBranchAddress("NumPE", &profile_counts);
  tree->SetBranchAddress("NumPE2", &histo_counts);

  if(weighted)
    tree->SetBranchAddress("Weight",&weights);
  else
    weights = 1.;

  for(int i=0;i<tree->GetEntries();++i)
  {
    tree->GetEntry(i);
    //total_profile_counts += profile_counts*weights;
    total_histo_counts += histo_counts*weights;
    sd_counts += pow(histo_counts*weights,2);
  }

  sd_counts = sqrt(sd_counts);
  //std::cout << "MantisROOT::GetCounts -> Profile Counts: " << total_profile_counts << " +- " << sd_profile << std::endl
  //          << "MantisROOT::GetCounts -> Histo Counts:   " << total_histo_counts   << " +- " << sd_histo   << std::endl;

  std::cout << "MantisROOT::GetCounts -> Histo Counts: " << total_histo_counts << " +- " << sd_counts << std::endl;

  f->Close();
  //std::cout << "MantisROOT::GetCounts -> COMPLETE." << std::endl;
  return total_histo_counts;
} // end of GetCounts Function

/*
void MantisROOT::GetCounts(string filebase, int filestart=0, int filenum=1, bool weighted=false)
{
  std::vector<double> countsv;
  std::vector<int> photonsv;
  int found_files = 0;
  for(int i=filestart;i<filenum;++i)
  {
    string filename = filebase + "-" + std::to_string(i) + ".root";
    bool filefound = true;
    if(gSystem->AccessPathName(filename.c_str()))
    {
      std::cout << "File " << filename << " Not Found." << std::endl << "Skipping..." << std::endl;
      filefound = false;
    }
    if(filefound)
    {
      found_files++;
      countsv.push_back(GetCounts(filename.c_str(),weighted));
      TFile* f = TFile::Open(filename.c_str());
      TTree* tree=0;
      f->GetObject("DetInfo",tree);
      photonsv.push_back(tree->GetEntries());
      delete tree;
      f->Close();
    }
  }
  // determine variance
  double variance = 0.;
  long int t_counts = 0;
  long int t_photons = 0;
  for(int i=0;i<countsv.size();++i)
  {
    t_counts += countsv[i];
    variance += pow(countsv[i],2);
    t_photons += photonsv[i];
  }
  variance /= (countsv.size() - 1);

  int sd_optical_photons = sqrt(variance);
  int sd_photons = sqrt(t_photons);

  std::cout << "MantisROOT::GetCounts Summary" << std::endl
  << "Total Files Searched:                " << filenum - filestart << std::endl
  << "Files Found:                         " << found_files << std::endl
  << "Total Optical Photons:               " << t_counts << std::endl
  << "Optical Photons Variance:            " << variance << std::endl
  << "Optical Photons Standard Deviation:  " << sd_optical_photons << std::endl
  << "Incident Photons:                    " << t_photons << std::endl
  << "Incident Photons Standard Deviation: " << sd_photons << std::endl;

  std::cout << "MantisROOT::GetCounts -> COMPLETE." << std::endl;
}

*/
void MantisROOT::GetScintillationDistribution(const char* filename, bool Corrected=true)
{
  CheckFile(filename);
  TFile* f = new TFile(filename);
  f->cd();
  TTree* tdet;

  if(Corrected)
    f->GetObject("Corrected_DetInfo", tdet);
  else
    f->GetObject("DetInfo", tdet);

  double xmin = tdet->GetMinimum("Energy");
  TH1D* h1 = new TH1D("h1","Detected Scintillation Distribution",25,2.,4.);
  tdet->Draw("Energy*1e6>>h1","CreatorProcess == \"Scintillation\"","goff");
  h1->SetLineColor(kBlue);
  h1->GetXaxis()->SetTitle("Energy [eV]");
  h1->Sumw2();
  //h1->Smooth(2);
  TGraph* t1 = new TGraph(h1);
  t1->SetLineColor(kBlue);

  double ymax_scale = h1->GetMaximum();
  TGraph* gScint = CreateScintillationDistribution(ymax_scale);
  gScint->SetLineColor(kRed);
  TCanvas* get1 = new TCanvas("get1","Simulated Distribution",600,400);
  get1->cd();
  h1->Draw("h");
  TCanvas* get2 = new TCanvas("get2","Combined Distributions",600,400);
  get2->cd();
  t1->Draw("AC");
  gScint->Draw("C,SAME");

  auto legend = new TLegend();
  legend->SetHeader("Distributions","C");
  legend->AddEntry(h1, "Detector Scintillation Response");
  legend->AddEntry(gScint, "Simulation Input Scintillation Distribution");
  legend->Draw();

  std::cout << "MantisROOT::GetScintillationDistribution -> Complete." << std::endl;

} // end of GetScintillationDistribution Function




void MantisROOT::Integral(TTree* tree)
{
  tree->SetEstimate(-1);
  double Emax = tree->GetMaximum("Energy");
  TH1D *e1 = new TH1D("e1",tree->GetName(),100,0.,Emax);

  tree->Draw("Energy>>e1","","goff");

  Double_t *energies = tree->GetVal(0);
  int nentries = tree->GetEntries();
  double intSum = 0;

  for(unsigned int i=0;i<nentries;++i)
    intSum +=energies[i];

  std::cout << tree->GetName() << " TTree Sum: " << intSum << std::endl;

  hIntegral(e1);

  if(debug)
    std::cout << "MantisROOT::Integral -> Deallocating Memory." << std::endl;

  delete e1; // avoids potential memory leak
  std::cout << "MantisROOT::Integral -> Complete." << std::endl;
} // end of Integral Function 1

void MantisROOT::Integral(std::vector<TTree*> trees)
{
  for(int i=0;i<trees.size();++i)
    Integral(trees[i]);

  std::cout << "MantisROOT::Integral -> Complete." << std::endl;
} // end of Integral Function 2

void MantisROOT::Integral(std::vector<TTree*> trees, TCut cut1)
{
  for(int i=0;i<trees.size();++i)
    hIntegral(trees[i], cut1);

  std::cout << "MantisROOT::Integral -> Complete." << std::endl;
} // end of Integral Function 3



TFile* MantisROOT::OpenFile(const char* filename)
{
  return (new TFile(filename));
} // end of OpenFile function



void MantisROOT::PredictThickness(std::vector<string> objects, bool write2file=false)
{
  for(int i=0;i<objects.size();++i)
    Rescale(objects[i].c_str(), write2file);

  std::cout << "Thickness Prediction Analysis Complete." << std::endl;
} // end of PredictThickness Function 1

void MantisROOT::PredictThickness(std::vector<string> objects, double resonance_energy, bool write2file=false)
{
  for(int i=0;i<objects.size();++i)
    Rescale(objects[i].c_str(),resonance_energy, write2file);

  std::cout << "Thickness Prediction Analysis Complete." << std::endl;
} // end of PredictThickness Function 2




void MantisROOT::PrepInputSpectrum(const char* filename, bool drawPlots=false, bool smooth=false, const char* obj="ChopIn", bool Weighted=false, double deltaE=0.000005, double minimum_energy=0.0)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  f->cd();
  TTree* tin;
  f->GetObject(obj, tin);
  double minE = 0.0;

  if(minimum_energy == 0.0)
    minE = tin->GetMinimum("Energy");
  else
    minE = minimum_energy;

  double maxE = tin->GetMaximum("Energy");

  int nbins = (maxE - minE)/10e-3;
  int nbins2 = (maxE - minE)/deltaE;

  TH1D* dNdE_histogram = new TH1D("dNdE_histogram","dNdE Histogram Spectrum", nbins, minE, maxE);

  if(Weighted)
    tin->Draw("Energy>>dNdE_histogram","Weight","goff");
  else
    tin->Draw("Energy>>dNdE_histogram","","goff");

  if(smooth)
    dNdE_histogram->Smooth(1000);

  //dNdE_histogram->Scale(1./dNdE_histogram->Integral());
  dNdE_histogram->GetXaxis()->SetTitle("Energy [MeV]");
  int titleEValue = deltaE*1e6;
  string yTitle = "Probability per " + std::to_string(titleEValue) + " eV";
  dNdE_histogram->GetYaxis()->SetTitle("Probability per 10000 eV");
  TGraph* dNdE_graph1 = new TGraph(dNdE_histogram);

  // Here perform rebinning
  TH1D* dNdE_histogram_rebinned = new TH1D("dNdE_histogram_rebinned","dNdE Histogram Spectrum",nbins2, 0., maxE);
  dNdE_histogram_rebinned->GetYaxis()->SetTitle(yTitle.c_str());
  for(int i=0;i<nbins2;++i)
  {
    double this_energy = dNdE_histogram_rebinned->GetXaxis()->GetBinCenter(i);
    double new_dNdE_value = dNdE_graph1->Eval(this_energy);
    dNdE_histogram_rebinned->SetBinContent(i,new_dNdE_value);
  }

  dNdE_histogram_rebinned->Scale(1./dNdE_histogram_rebinned->Integral());
  TGraph* dNdE_graph = new TGraph(dNdE_histogram_rebinned);

  WriteSampling(dNdE_histogram_rebinned);
  WriteSampling(dNdE_graph, deltaE);

  if(drawPlots)
  {
    TCanvas* c0 = new TCanvas("dNdE_histogram_canvas","dNdE Histogram",600,400);
    c0->cd();
    dNdE_histogram->Draw("h");
    TCanvas* c1 = new TCanvas("dNdE_histogram_rebinned_canvas","dNdE Histogram Rebinned",600,400);
    c1->cd();
    dNdE_histogram_rebinned->Draw("h");
    TCanvas* c2 = new TCanvas("dNdE_graph_canvas2","dNdE TGraph 2",600,400);
    c2->cd();
    dNdE_graph1->Draw();
    TCanvas* c3 = new TCanvas("dNdE_graph_canvas","dNdE TGraph",600,400);
    c3->cd();
    dNdE_graph->Draw();
  }
  std::cout << "MantisROOT::PrepInputSpectrum -> COMPLETE." << std::endl;
} // end of PrepInputSpectrum Function





void MantisROOT::PrepIntObjInputSpectrum(const char* filename, const char* ObjName, std::vector<double> energy_regions, std::vector<double> bin_widths, bool Weighted=false, bool normalize=true, bool drawWeights=false)
{
  CheckFile(filename);
  TFile* f = new TFile(filename);
  f->cd();

  TTree* obj;

  obj = (TTree*) f->Get(ObjName);
  obj->SetEstimate(-1);
  double energy, weight;
  obj->SetBranchAddress("Energy",&energy);

  if(Weighted)
    obj->SetBranchAddress("Weight",&weight);

  int energy_end = energy_regions.size()-1;

  if(debug)
    std::cout << "MantisROOT::PrepIntObjInputSpectrum -> End of Energy Region: " << energy_regions[energy_end] << std::endl;

  int nbins = (energy_regions[energy_end] - energy_regions[0])/10e-3;
  if(debug)
    std::cout << "MantisROOT::PrepIntObjInputSpectrum -> Sampling Number of Bins: " << nbins << std::endl;

  TH1D* sampling_histogram = new TH1D("sampling_histogram","Sampling Distribution Histogram", nbins, energy_regions[0], energy_regions[energy_end]);
  for(int i=0;i<obj->GetEntries();++i)
  {
    obj->GetEntry(i);

    if(Weighted)
      sampling_histogram->Fill(energy,weight);
    else
      sampling_histogram->Fill(energy);
  }

  if(normalize)
    sampling_histogram->Scale(1./sampling_histogram->Integral());

  TGraph* sampling_graph = new TGraph(sampling_histogram);
  Double_t* sample = sampling_graph->GetX();
  std::vector<double> samplev;
  for(int i=0;i<nbins;++i)
  {
    if(sample[i] > energy_regions[energy_end-1])
    {
      if(debug)
        std::cout << "Sample Index: " << i << " Value set: " << sample[i] << std::endl;

      samplev.push_back(sample[i]);
    }
  }
  std::cout << "MantisROOT::PrepIntObjInputSpectrum -> Sampling created." << std::endl;


  TGraph* dNdE_graph = VariableBinWidthRebin(filename, ObjName, energy_regions, bin_widths, samplev, Weighted, normalize, true);

  if(dNdE_graph == 0)
  {
    std::cout << "MantisROOT::PrepIntObjInputSpectrum -> VariableBinWidthRebin Returned NULL Exiting..." << std::endl;
    return;
  }

  if(drawWeights)
  {
    DrawWeights(dNdE_graph, sampling_graph);
    TCanvas* c_input_short = new TCanvas("c_input_short","dNdE Distribution",600,400);
    c_input_short->cd();
    dNdE_graph->Draw();
    TCanvas* c_sample_short = new TCanvas("c_sample_short","Sampling Distribution",600,400);
    c_sample_short->cd();
    sampling_graph->Draw();
  }
  std::cout << "MantisROOT::PrepIntObjInputSpectrum -> COMPLETE." << std::endl;
  WriteSampling(dNdE_graph, sampling_graph, sampling_histogram, 5e-6);
} // end of PrepIntObjInputSpectrum Function



void MantisROOT::RunSummary(const char* onFile, const char* offFile, bool IntObjIn=true, bool weighted=false, bool drawPlots=false, bool drawBeamEnergyPlots=false)
{
  CheckFile(onFile);
  CheckFile(offFile);
  TFile* fon = new TFile(onFile);
  fon->cd();
  TTree *nrf, *objIn, *objOut, *shield, *plexi, *cher1, *cher2, *detInfo, *e_tree1, *e_tree2;
  fon->GetObject("NRF",nrf);

  if(IntObjIn)
    fon->GetObject("IntObjIn",objIn);

  fon->GetObject("IntObjOut",objOut);
  fon->GetObject("Shielding",shield);
  fon->GetObject("Plexiglass",plexi);
  fon->GetObject("Cherenkov",cher1);
  fon->GetObject("Cherenkov2",cher2);
  fon->GetObject("DetInfo",detInfo);
  fon->GetObject("event_tree",e_tree1);
  fon->GetObject("event_tree2",e_tree2);

  nrf->SetEstimate(-1);
  std::cout << "MantisROOT::RunSummary -> " << onFile << " Summary:" << std::endl << std::endl;
  TH1D* hnrf = new TH1D("hnrf","NRF",100,0.,nrf->GetMaximum("Energy"));

  if(weighted)
    nrf->Draw("Energy>>hnrf","Weight","goff");
  else
    nrf->Draw("Energy>>hnrf","","goff");

  double errorNRF;
  double integralNRF = hnrf->IntegralAndError(0,100,errorNRF);
  std::cout << "MantisROOT::RunSummary -> " << "* NRF Entries:                            " << integralNRF << " +- " << errorNRF << std::endl;
  TH1D *hin = new TH1D();
  TH1D *hin2 = new TH1D();

  if(IntObjIn)
  {
    objIn->SetEstimate(-1);
    hin->SetNameTitle("hin","Incident Interrogation Object");
    //hin->GetXaxis()->SetNbinsX(100);
    hin->SetMinimum(0.);
    hin->SetMaximum(objIn->GetMaximum("Energy"));
    hin2->SetNameTitle("hin2","Beam Energy of Photons Incident Interrogation Object");
    //hin2->GetXaxis()->SetNbinsX(100);
    hin2->SetMinimum(0.);
    hin2->SetMaximum(objIn->GetMaximum("BeamEnergy"));

    if(weighted)
    {
      objIn->Draw("Energy>>hin","Weight","goff");
      objIn->Draw("BeamEnergy>>hin2","Weight","goff");
    }
    else
    {
      objIn->Draw("Energy>>hin","","goff");
      objIn->Draw("BeamEnergy>>hin2","","goff");
      hin->Sumw2();
    }
    hin->SetStats(0);
    double errorIntObjIn;
    double intObjInIntegral = hin->IntegralAndError(0,100,errorIntObjIn);
    std::cout << "MantisROOT::RunSummary -> " << "* IntObjIn Entries:                       " << intObjInIntegral << " +- " << errorIntObjIn << std::endl;
    std::cout << "MantisROOT::RunSummary -> " << "* IntObjIn Mean:                          " << hin->GetMean() << std::endl;
    std::cout << "MantisROOT::RunSummary -> " << "* IntObjIn Beam Energy Mean:              " << hin2->GetMean() << std::endl;
  }

  objOut->SetEstimate(-1);
  TH1D* hout = new TH1D("hout","Interrogation Object Emission Spectrum",100,0.,objOut->GetMaximum("Energy"));
  TH1D* hout2 = new TH1D("hout2","Beam Energy of Interrogation Object Emission",100,0.,objOut->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    objOut->Draw("Energy>>hout","Weight","goff");
    objOut->Draw("BeamEnergy>>hout2","Weight","goff");
  }
  else
  {
    objOut->Draw("Energy>>hout","","goff");
    objOut->Draw("BeamEnergy>>hout2","","goff");
  }

  double errorhout;
  double integralhout = hout->IntegralAndError(0,100,errorhout);
  std::cout << "MantisROOT::RunSummary -> " << "* IntObjOut Entries:                      " << integralhout << " +- " << errorhout << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* IntObjOut Mean:                         " << hout->GetMean() << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* IntObjOut Beam Energy Mean:             " << hout2->GetMean() << std::endl;
  shield->SetEstimate(-1);
  TH1D* hshield = new TH1D("hshield","Incident Outer Shielding Layer", 100, 0.,shield->GetMaximum("Energy"));
  TH1D* hshield2 = new TH1D("hshield2","Beam Energy of Incident Outer Shielding Layer",100,0.,shield->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    shield->Draw("Energy>>hshield","Weight","goff");
    shield->Draw("BeamEnergy>>hshield2","Weight","goff");
  }
  else
  {
    shield->Draw("Energy>>hshield","","goff");
    shield->Draw("BeamEnergy>>hshield2","","goff");
    hshield2->Sumw2();
  }

  hshield2->SetStats(0);
  double errorhshield;
  double integralhshield = hshield->IntegralAndError(0,100,errorhshield);
  std::cout << "MantisROOT::RunSummary -> " << "* Shielding Entries:                      " << integralhshield << " +- " << errorhshield << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Shielding Mean:                         " << hshield->GetMean() << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Beam Energy of Incident Shielding Mean: " << hshield2->GetMean() << std::endl;
  plexi->SetEstimate(-1);
  TH1D* hplexi = new TH1D("hplexi","Incident Plexiglass",100,0.,plexi->GetMaximum("Energy"));
  TH1D* hplexi2 = new TH1D("hplexi2","Beam Energy of Incident Plexiglass",100,0,plexi->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    plexi->Draw("Energy>>hplexi","Weight","goff");
    plexi->Draw("BeamEnergy>>hplexi2","Weight","goff");
  }
  else
  {
    plexi->Draw("Energy>>hplexi","","goff");
    plexi->Draw("BeamEnergy>>hplexi2","","goff");
    hplexi->Sumw2();
  }

  hplexi->SetStats(0);
  double errorhplexi;
  double integralhplexi = hplexi->IntegralAndError(0,100,errorhplexi);
  std::cout << "MantisROOT::RunSummary -> " << "* Plexi Entries:                          " << integralhplexi << " +- " << errorhplexi << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Plexi Mean:                             " << hplexi->GetMean() << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Beam Energy of Plexiglass Mean:         " << hplexi2->GetMean() << std::endl;
  cher1->SetEstimate(-1);
  std::cout << "MantisROOT::RunSummary -> " << "* Optical Photon Entries:                 " << cher1->GetEntries() << std::endl;
  cher2->SetEstimate(-1);
  std::cout << "MantisROOT::RunSummary -> " << "* Cherenkov Photons Entries:              " << cher2->GetEntries() << std::endl;
  detInfo->SetEstimate(-1);
  TH1D* hdet = new TH1D("hdet","Detected",50,0.,8.0e-6);
  TH1D* hdet2 = new TH1D("hdet2","Beam Energy of Detected",100,0,detInfo->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    detInfo->Draw("Energy>>hdet","Weight","goff");
    detInfo->Draw("BeamEnergy>>hdet2","Weight","goff");
  }
  else
  {
    detInfo->Draw("Energy>>hdet","","goff");
    detInfo->Draw("BeamEnergy>>hdet2","","goff");
    hdet->Sumw2();
    hdet2->Sumw2();
  }

  hdet->SetStats(0);
  hdet2->SetStats(0);
  double errorhdet;
  double integralhdet = hdet->IntegralAndError(0,50,errorhdet);
  std::cout << "MantisROOT::RunSummary -> " << "* Detected Entries:                       " << integralhdet << " +- " << errorhdet << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Beam Energy of Detected Mean:           " << hdet2->GetMean() << std::endl;
  e_tree1->SetEstimate(-1);
  TH1D* he_tree1 = new TH1D("he_tree1","NRF Optical Photons Detected",100,0.,e_tree1->GetMaximum("Energy"));

  if(weighted)
    e_tree1->Draw("Energy>>he_tree1","Weight","goff");
  else
    e_tree1->Draw("Energy>>he_tree1","","goff");

  e_tree2->SetEstimate(-1);
  TH1D* he_tree2 = new TH1D("he_tree2","IntObj NRF Optical Photons Detected",100,0.,e_tree2->GetMaximum("Energy"));

  if(weighted)
    e_tree2->Draw("Energy>>he_tree2","Weight","goff");
  else
    e_tree2->Draw("Energy>>he_tree2","","goff");

  double errorhe_tree1, errorhe_tree2;
  double integralhe_tree1 = he_tree1->IntegralAndError(0,100, errorhe_tree1);
  double integralhe_tree2 = he_tree2->IntegralAndError(0,100, errorhe_tree2);
  std::cout << "MantisROOT::RunSummary -> " << "* NRF Optical Photons Detected:           " << integralhe_tree1 << " +- " << errorhe_tree1 << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* IntObj NRF Optical Photons Detected:    " << integralhe_tree2 << " +- " << errorhe_tree2 << std::endl;

  // OFF FILE ANALYSIS
  TFile* foff = new TFile(offFile);
  foff->cd();
  TTree *nrf_off, *objIn_off, *objOut_off, *shield_off, *plexi_off, *cher1_off, *cher2_off, *detInfo_off, *e_tree1_off, *e_tree2_off;
  foff->GetObject("NRF",nrf_off);

  if(IntObjIn)
    foff->GetObject("IntObjIn",objIn_off);

  foff->GetObject("IntObjOut",objOut_off);
  foff->GetObject("Shielding",shield_off);
  foff->GetObject("Plexiglass",plexi_off);
  foff->GetObject("Cherenkov",cher1_off);
  foff->GetObject("Cherenkov2",cher2_off);
  foff->GetObject("DetInfo",detInfo_off);
  foff->GetObject("event_tree",e_tree1_off);
  foff->GetObject("event_tree2",e_tree2_off);

  nrf_off->SetEstimate(-1);
  TH1D* hnrf_off = new TH1D("hnrf_off","NRF",100, 0., nrf_off->GetMaximum("Energy"));

  if(weighted)
    nrf_off->Draw("Energy>>hnrf_off","Weight","goff");
  else
    nrf_off->Draw("Energy>>hnrf_off","","goff");

  std::cout << std::endl << "MantisROOT::RunSummary -> " << offFile << " Summary:" << std::endl << std::endl;
  double errorNRF_off;
  double integralhnrf_off = hnrf_off->IntegralAndError(0,100,errorNRF_off);
  std::cout << "MantisROOT::RunSummary -> " << "* NRF Entries:                            " << integralhnrf_off << " +- " << errorNRF_off << std::endl;
  TH1D *hin_off = new TH1D();
  TH1D *hin2_off = new TH1D();

  if(IntObjIn)
  {
    objIn_off->SetEstimate(-1);
    hin_off->SetNameTitle("hin_off","Incident Interrogation Object");
    //hin_off->GetXaxis()->SetNbinsX(100);
    hin_off->SetMinimum(0.);
    hin_off->SetMaximum(objIn_off->GetMaximum("Energy"));
    hin2_off->SetNameTitle("hin2_off","Beam Energy of Photons Incident Interrogation Object");
    //hin2_off->GetXaxis()->SetNbinsX(100);
    hin2_off->SetMinimum(0.);
    hin2_off->SetMaximum(objIn_off->GetMaximum("BeamEnergy"));

    if(weighted)
    {
      objIn_off->Draw("Energy>>hin_off","Weight","goff");
      objIn_off->Draw("BeamEnergy>>hin2_off","Weight","goff");
    }
    else
    {
      objIn_off->Draw("Energy>>hin_off","","goff");
      objIn_off->Draw("BeamEnergy>>hin2_off","","goff");
      hin_off->Sumw2();
    }
    hin_off->SetStats(0);
    hin_off->SetLineColor(kRed);
    double errorhin_off;
    double integralhin_off = hin_off->IntegralAndError(0,100,errorhin_off);
    std::cout << "MantisROOT::RunSummary -> " << "* IntObjIn Entries:                       " << integralhin_off << " +- " << errorhin_off << std::endl;
    std::cout << "MantisROOT::RunSummary -> " << "* IntObjIn Mean:                          " << hin_off->GetMean() << std::endl;
    std::cout << "MantisROOT::RunSummary -> " << "* IntObjIn Beam Energy Mean:              " << hin2_off->GetMean() << std::endl;
  }

  objOut_off->SetEstimate(-1);
  TH1D* hout_off = new TH1D("hout_off","Interrogation Object Emission Spectrum",100,0.,objOut_off->GetMaximum("Energy"));
  TH1D* hout2_off = new TH1D("hout2_off","Beam Energy of Interrogation Object Emission",100,0.,objOut_off->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    objOut_off->Draw("Energy>>hout_off","Weight","goff");
    objOut_off->Draw("BeamEnergy>>hout2_off","Weight","goff");
  }
  else
  {
    objOut_off->Draw("Energy>>hout_off","","goff");
    objOut_off->Draw("BeamEnergy>>hout2_off","","goff");
  }

  double errorhout_off;
  double integralhout_off = hout_off->IntegralAndError(0,100,errorhout_off);
  std::cout << "MantisROOT::RunSummary -> " << "* IntObjOut Entries:                      " << integralhout_off << " +- " << errorhout_off << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* IntObjOut Mean:                         " << hout_off->GetMean() << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* IntObjOut Beam Energy Mean:             " << hout2_off->GetMean() << std::endl;
  shield_off->SetEstimate(-1);
  TH1D* hshield_off = new TH1D("hshield_off","Incident Outer Shielding Layer", 100, 0.,shield_off->GetMaximum("Energy"));
  TH1D* hshield2_off = new TH1D("hshield2_off","Beam Energy of Incident Outer Shielding Layer",100,0.,shield_off->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    shield_off->Draw("Energy>>hshield_off","Weight","goff");
    shield_off->Draw("BeamEnergy>>hshield2_off","Weight","goff");
  }
  else
  {
    shield_off->Draw("Energy>>hshield_off","","goff");
    shield_off->Draw("BeamEnergy>>hshield2_off","","goff");
    hshield2_off->Sumw2();
  }

  hshield2_off->SetStats(0);
  hshield2_off->SetLineColor(kRed);
  double errorhshield_off;
  double integralhshield_off = hshield_off->IntegralAndError(0,100, errorhshield_off);
  std::cout << "MantisROOT::RunSummary -> " << "* Shielding Entries:                      " << integralhshield_off << " +- " << errorhshield_off << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Shielding Mean:                         " << hshield_off->GetMean() << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Beam Energy of Incident Shielding Mean: " << hshield2_off->GetMean() << std::endl;
  plexi_off->SetEstimate(-1);
  TH1D* hplexi_off = new TH1D("hplexi_off","Incident Plexiglass",100,0.,plexi_off->GetMaximum("Energy"));
  TH1D* hplexi2_off = new TH1D("hplexi2_off","Beam Energy of Incident Plexiglass",100,0,plexi_off->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    plexi_off->Draw("Energy>>hplexi_off","Weight","goff");
    plexi_off->Draw("BeamEnergy>>hplexi2_off","Weight","goff");
  }
  else
  {
    plexi_off->Draw("Energy>>hplexi_off","","goff");
    plexi_off->Draw("BeamEnergy>>hplexi2_off","","goff");
    hplexi_off->Sumw2();
  }

  hplexi_off->SetStats(0);
  hplexi_off->SetLineColor(kRed);
  double errorhplexi_off;
  double integralhplexi_off = hplexi_off->IntegralAndError(0,100,errorhplexi_off);
  std::cout << "MantisROOT::RunSummary -> " << "* Plexi Entries:                          " << integralhplexi_off << " +- " << errorhplexi_off << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Plexi Mean:                             " << hplexi_off->GetMean() << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Beam Energy of Plexiglass Mean:         " << hplexi2_off->GetMean() << std::endl;
  cher1_off->SetEstimate(-1);
  std::cout << "MantisROOT::RunSummary -> " << "* Optical Photons Entries:                " << cher1_off->GetEntries() << std::endl;
  cher2_off->SetEstimate(-1);
  std::cout << "MantisROOT::RunSummary -> " << "* Cherenkov Photons Entries:              " << cher2_off->GetEntries() << std::endl;
  detInfo_off->SetEstimate(-1);
  TH1D* hdet_off = new TH1D("hdet_off","Detected",50,0.,8.0e-6);
  TH1D* hdet2_off = new TH1D("hdet2_off","Beam Energy of Detected",100,0.,detInfo_off->GetMaximum("BeamEnergy"));

  if(weighted)
  {
    detInfo_off->Draw("Energy>>hdet_off","Weight","goff");
    detInfo_off->Draw("BeamEnergy>>hdet2_off","Weight","goff");
  }
  else
  {
    detInfo_off->Draw("Energy>>hdet_off","","goff");
    detInfo_off->Draw("BeamEnergy>>hdet2_off","","goff");
    hdet_off->Sumw2();
    hdet2_off->Sumw2();
  }

  hdet_off->SetStats(0);
  hdet_off->SetLineColor(kRed);
  hdet2_off->SetStats(0);
  hdet2_off->SetLineColor(kRed);
  double errorhdet_off;
  double integralhdet_off = hdet_off->IntegralAndError(0,50,errorhdet_off);
  std::cout << "MantisROOT::RunSummary -> " << "* Detected Entries:                       " << integralhdet_off << " +- " << errorhdet_off << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* Beam Energy of Detected Mean:           " << hdet2_off->GetMean() << std::endl;
  e_tree1_off->SetEstimate(-1);
  TH1D* he_tree1_off = new TH1D("he_tree1_off","NRF Optical Photons Detected",100,0.,e_tree1_off->GetMaximum("Energy"));

  if(weighted)
    e_tree1_off->Draw("Energy>>he_tree1_off","Weight","goff");
  else
    e_tree1_off->Draw("Energy>>he_tree1_off","","goff");

  e_tree2_off->SetEstimate(-1);
  TH1D* he_tree2_off = new TH1D("he_tree2_off","IntObj NRF Optical Photons Detected",100,0.,e_tree2_off->GetMaximum("Energy"));

  if(weighted)
    e_tree2_off->Draw("Energy>>he_tree2_off","Weight","goff");
  else
    e_tree2_off->Draw("Energy>>he_tree2_off","","goff");


  double errorhe_tree1_off, errorhe_tree2_off;
  double integralhe_tree1_off = he_tree1_off->IntegralAndError(0,100, errorhe_tree1_off);
  double integralhe_tree2_off = he_tree2_off->IntegralAndError(0,100, errorhe_tree2_off);

  std::cout << "MantisROOT::RunSummary -> " << "* NRF Optical Photons Detected:           " << integralhe_tree1_off << " +- " << errorhe_tree1_off << std::endl;
  std::cout << "MantisROOT::RunSummary -> " << "* IntObj NRF Optical Photons Detected:    " << integralhe_tree2_off << " +- " << errorhe_tree2_off << std::endl;

  if(drawPlots)
  {

    if(IntObjIn)
    {
      TCanvas* c1 = new TCanvas("c1","Incident Interrogation Object",600,400);
      c1->cd();
      hin->Draw("h");
      hin_off->Draw("h,SAME");
      auto legend = new TLegend();
      legend->SetHeader("Chopper State","C");
      legend->AddEntry(hin, "Chopper On");
      legend->AddEntry(hin_off, "Chopper Off");
      legend->Draw();
    }

    TCanvas* c2 = new TCanvas("c2","Incident Plexiglass",600,400);
    c2->cd();
    hplexi->Draw("h");
    hplexi_off->Draw("h,SAME");
    auto legend2 = new TLegend();
    legend2->SetHeader("Chopper State","C");
    legend2->AddEntry(hplexi, "Chopper On");
    legend2->AddEntry(hplexi_off, "Chopper Off");
    legend2->Draw();

    TCanvas* c3 = new TCanvas("c3","Detected",600,400);
    c3->cd();
    hdet->Draw("h");
    hdet_off->Draw("h,SAME");
    auto legend3 = new TLegend();
    legend3->SetHeader("Chopper State","C");
    legend3->AddEntry(hdet, "Chopper On");
    legend3->AddEntry(hdet_off, "Chopper Off");
    legend3->Draw();
  }

  if(drawBeamEnergyPlots)
  {
    TCanvas* c4 = new TCanvas("c4","Beam Energy of Photons Incident Shielding",600,400);
    c4->cd();
    hshield2->Draw("h");
    hshield2_off->Draw("h,SAME");
    auto legend4 = new TLegend();
    legend4->SetHeader("Chopper State","C");
    legend4->AddEntry(hshield2, "Chopper On");
    legend4->AddEntry(hshield2_off, "Chopper Off");
    legend4->Draw();

    TCanvas* c5 = new TCanvas("c5","Beam Energy of Photons Detected",600,400);
    c5->cd();
    hdet2->Draw("h");
    hdet2_off->Draw("h,SAME");
    auto legend5 = new TLegend();
    legend5->SetHeader("Chopper State","C");
    legend5->AddEntry(hdet2, "Chopper On");
    legend5->AddEntry(hdet2_off, "Chopper Off");
    legend5->Draw();
  }

  std::cout << "MantisROOT::RunSummary -> COMPLETE." << std::endl;

} // end of RunSummary Function



void MantisROOT::Sampling(const char *filename, const char* object_to_sample, bool drawPlots=false, bool smooth=false, bool Weighted=false, string sample_element="U", double deltaE=0.000005, bool checkZero=false, double non_nrf_energy_cut=1.5, double weighting_factor=10000)
{
	CheckFile(filename);
  double deltaE_large_bin_width = 0.01;
  double Emax = ReturnMax(filename, object_to_sample);
	// resonance energies in MeV as calculated by G4NRF
	vector<double> Evec;
	vector<double> E_below_threshold;

	if(sample_element == "U")
	{
		std::cout << "MantisROOT::Sampling -> Uranium!" << std::endl;
		// U-238
		Evec.push_back(1.78200716196); // Vavrek
		Evec.push_back(1.84600768563); // Vavrek
		Evec.push_back(2.17601067909); // Vavrek
		Evec.push_back(2.20901100546); // Vavrek
		Evec.push_back(2.24501136709); // Vavrek

		// U-235
		Evec.push_back(1.65623622215); // Me
		Evec.push_back(1.73354686425); // Vavrek
		Evec.push_back(1.81525753275); // Vavrek
		Evec.push_back(1.86231786689); // Me
		//Evec.push_back(2.00336916735); // Vavrek
		Evec.push_back(2.00619912943); // Me
	}
	else if(sample_element == "Pu")
	{
		std::cout << "MantisROOT::Sampling -> Plutonium!" << std::endl;
		// Pu-239
		Evec.push_back(2.13501023737);
		Evec.push_back(2.14357031961);
		Evec.push_back(2.15101039142);
		Evec.push_back(2.43171328004);

		// Pu-240
		Evec.push_back(2.43321324158);
		Evec.push_back(2.57751485869);
		Evec.push_back(2.56641473101);
	}
	else
	{
		std::cout << "MantisROOT::Sampling -> Sample element not found. Exiting..." << std::endl;
		exit(100);
	}

	for(int i=0;i<Evec.size();i++)
	{
	  if(Evec[i] <= Emax)
	  {
	    E_below_threshold.push_back(Evec[i]);
	  }
	}

  // Build dNdE Graph with large bin widths

  if(debug)
  {
    std::cout << "MantisROOT::Sampling -> Prepping Input Spectrum..." << std::endl;
  }

  TGraph* dNdE_graph = PrepInputSpectrum(filename, object_to_sample, smooth, Weighted, deltaE, checkZero);

  if(debug)
    std::cout << "MantisROOT::Sampling -> Input Spectrum Prepped!" << std::endl;

  // Create small bin width Sampling Histogram
  TH1D* sampling_histogram = BuildBremSampling(E_below_threshold, non_nrf_energy_cut, deltaE, Emax, weighting_factor);

  sampling_histogram->SetTitle("Sampling Histogram");
  sampling_histogram->SetName("Sampling_Histogram");
  // Convert to TGraph
  TGraph* sampling_graph = new TGraph(sampling_histogram);
  sampling_graph->SetTitle("Sampling TGraph");

  // Write to Sampling file
	WriteSampling(dNdE_graph, sampling_graph, sampling_histogram, deltaE);

  if(debug || drawPlots)
  {
    std::cout << "MantisROOT::Sampling Displaying Graphs..." << std::endl;
    TCanvas* c_input_graph = new TCanvas("c_input_graph","dNdE Input Graph",600,400);
    c_input_graph->cd();
    dNdE_graph->Draw();
    TCanvas* c_sampling_graph = new TCanvas("c_sampling_graph","Sampling Graph",600,400);
    c_sampling_graph->cd();
    sampling_graph->Draw();
    //TCanvas* c_sampling_histogram = new TCanvas("c_sampling_histogram","Sampling Histogram",600,400);
    //c_sampling_histogram->cd();
    //sampling_histogram->Draw("h");

    DrawWeights(dNdE_graph, sampling_graph);
  }

  std::cout << "MantisROOT::Sampling -> COMPLETE!" << std::endl;

}// End of Sampling Function



void MantisROOT::Sig2Noise(std::vector<string> filenames, string object, bool Weighted=false, bool Corrected=false, bool place_cut=false, TCut cut1="NA")
{
  if(!object.compare("IntObj"))
  {
    for(int i=0;i<filenames.size();++i)
    {
      std::cout << std::endl << "Signal to Noise Calculation for " << filenames[i] << std::endl;
      SNR_IntObj(filenames[i].c_str(), Weighted);
    }
  }
  else if(!object.compare("Det"))
  {
    for(int i=0;i<filenames.size();++i)
    {
      std::cout << std::endl << "Signal to Noise Calculation for " << filenames[i] << std::endl;
      SNR_Det(filenames[i].c_str(), Weighted, Corrected, place_cut, cut1);
    }
  }
  else if(!object.compare("Both"))
    for(int i=0;i<filenames.size();++i)
    {
      std::cout << std::endl << "Signal to Noise Calculation for " << filenames[i] << std::endl;
      std::cout << filenames[i] << " Interrogation Object Signal to Noise Calculating..." << std::endl;
      SNR_IntObj(filenames[i].c_str(), Weighted);
      std::cout << filenames[i] << " Detected Signal to Noise Calculating..." << std::endl;
      SNR_Det(filenames[i].c_str(), Weighted, Corrected, place_cut, cut1);
    }
  else
  {
    std::cerr << "Error: Object Not Found Input Options: " << std::endl
    << "IntObj" << std::endl << "Det" << std::endl << "Both" << std::endl;
    return;
  }

  std::cout << "MantisROOT::Sig2Noise -> Signal to Noise Ratio Analysis Complete." << std::endl;
} // end of Sig2Noise Function



void MantisROOT::SimpleSampling(const char* filename, const char* object_to_sample, bool smooth=false, bool Weighted=false, double deltaE_large_bin_width=0.001, double deltaE_small_bin_width=0.000005, double cut_energy1=0.5, double cut_energy2=1.0, double weighting_factor=1000, double weighting_factor2=10, bool checkZero=false, bool drawWeights=false)
{
  TH1D* sampling_histogram = BuildSimpleSample(filename, object_to_sample, deltaE_small_bin_width, cut_energy1, cut_energy2, weighting_factor, weighting_factor2);
  TGraph *sampling_graph = new TGraph(sampling_histogram);
  TGraph *dNdE_graph = PrepInputSpectrum(filename, object_to_sample, smooth, Weighted, deltaE_large_bin_width, checkZero);

  WriteSampling(dNdE_graph, sampling_graph, sampling_histogram, deltaE_small_bin_width);

  if(drawWeights)
    DrawWeights(dNdE_graph, sampling_graph);

  std::cout << "MantisROOT::SimpleSampling -> Complete." << std::endl;

} // end of SimpleSampling Function



TGraph* MantisROOT::VariableBinWidthRebin(const char* filename, const char* ObjName, std::vector<double> energy_regions, std::vector<double> bin_widths, std::vector<double> samplev, bool Weighted=false, bool normalize=true, bool for_weighted_spectrum=false)
{
  // Check to make sure file exists
  CheckFile(filename);

  // Complete User Input Checks
  if(energy_regions.size() != bin_widths.size()+1)
  {
    std::cerr << "MantisROOT::VariableBinWidthRebin -> FATAL ERROR energy region vector size must be one index larger than bin width vector size. Exiting..." << std::endl;
    exit(1);
  }

  TFile *f = new TFile(filename);
  f->cd();
  TTree *inObj;
  // Grab the Users TTree
  inObj = (TTree*) f->Get(ObjName);
  inObj->SetEstimate(-1);
  double Emax = inObj->GetMaximum("Energy");
  // Grab TTree Values
  double energy, weight;
  inObj->SetBranchAddress("Energy", &energy);

  if(Weighted)
    inObj->SetBranchAddress("Weight", &weight);

  std::vector<double> energyv, weightv;

  if(debug)
    std::cout << "MantisROOT::VariableBinWidthRebin -> Grabbing Energies..." << std::endl;

  for(int i=0;i<inObj->GetEntries();++i)
  {
    inObj->GetEntry(i);
    energyv.push_back(energy);
    weightv.push_back(weight);
  }

  if(debug)
    std::cout << "MantisROOT::VariableBinWidthRebin -> Energies grabbed." << std::endl;

  int tbins = 0;
  std::vector<int> nbinsv;
  // Find total number of bins
  for(int i=0;i<energy_regions.size()-1;++i)
  {
    int nbins = (energy_regions[i+1] - energy_regions[i])/bin_widths[i];
    nbinsv.push_back(nbins);
    tbins += nbins;
  }

  if(debug)
  {
    for(int i=0;i<nbinsv.size();++i)
      std::cout << "Number of Bins: " << nbinsv[i] << std::endl;

    std::cout << "Total Number of Bins: " << tbins << std::endl;
  }
  // create edges (dynamically sized array)
  Double_t* edges = new Double_t[tbins+1];
  double edge_counter = bin_widths[0]+energy_regions[0];
  double last_edge_counter = bin_widths[0]+energy_regions[0];
  int energy_end = energy_regions.size()-1;

  if(debug)
    std::cout << "MantisROOT::VariableBinWidthRebin -> Filling Edges..." << std::endl;

  edges[0] = energy_regions[0];
  for(int i=0;i<nbinsv.size();++i)
  {
    edge_counter = last_edge_counter;
    int bins_completed = 0;

    if(i > 0)
    {
      int a = 0;
      while(a < i)
      {
        bins_completed += nbinsv[a];
        a++;
      }
    }

    bool bc_found = false;
    for(int j=bins_completed+1;j<nbinsv[i]+bins_completed+1;++j)
    {
      edges[j] = edge_counter;
      edge_counter += bin_widths[i];
      // do a check
      if(edge_counter > energy_regions[i+1])
      {
        if(debug)
        {
          std::cout << "Boundary Edge Condition met at index: " << j << std::endl
          << "Edge Counter: " << edge_counter << std::endl << "Next Energy Region: "
          << energy_regions[i+1] << std::endl;
        }

        edges[j+1] = energy_regions[i+1];
        edge_counter = energy_regions[i+1] + bin_widths[i+1];
        bc_found = true;
        bins_completed = bins_completed + 1;
      }
      last_edge_counter = edge_counter;
      if(bc_found)
        break;
    }
  }

  // Reset edges past NRF to end to ensure correctness
  for(int i=0;i<samplev.size();++i)
  {
    int loc = tbins - samplev.size() + i;
    edges[loc] = samplev[i];
  }
  int bin_width_end = bin_widths.size();
  edges[tbins] = Emax;
  // Check edges are increasing
  std::vector<double> edgesv;
  for(int i=0;i<tbins+1;++i)
    edgesv.push_back(edges[i]);

  if(!std::is_sorted(edgesv.begin(),edgesv.end()))
  {
    auto it = std::is_sorted_until(edgesv.begin(),edgesv.end());
    std::cout << "ERROR Edges not in ascending order." << std::endl
    << "Check Index: " << it - edgesv.begin() << std::endl;

    for(int i=0;i<edgesv.size();++i)
      std::cout << "Edge Index " << i << " Value: " << edgesv[i] << std::endl;

    return 0;
  }
  else
  {
    if(debug)
    {
      for(int i=0;i<edgesv.size();++i)
        std::cout << "Edge Index " << i << " Value: " << edgesv[i] << std::endl;
    }
  }

  // Create Histogram
  std::cout << "MantisROOT::VariableBinWidthRebin -> Creating Histogram..." << std::endl;
  TH1D* hObj = new TH1D("hObj",ObjName, tbins, edges);

  if(debug)
    std::cout << "MantisROOT::VariableBinWidthRebin -> Filling Histogram..." << std::endl;

  for(unsigned int i=0;i<inObj->GetEntries();++i)
  {
    if(Weighted)
      hObj->Fill(energyv[i], weightv[i]);
    else
      hObj->Fill(energyv[i]);
  }

  std::cout << "MantisROOT::VariableBinWidthRebin -> Histogram Filled." << std::endl;
  hObj->Print();
  // Prior to filling histogram set structure for storing bin errors
  hObj->Sumw2();

  if(normalize)
    hObj->Scale(1./hObj->Integral());

  //hObj->Smooth(10);

  TGraph* gObj = new TGraph(hObj);

  if(for_weighted_spectrum)
    hObj->SetName("h_sample_long");
  else
    hObj->SetName("h_input");

  gObj->SetName("Graph_from_h_input");

  return gObj;
} // end of VariableBinWidthRebin Function



double MantisROOT::Wave2Energy(double wavelength, string unit="m")
{
  if(!unit.compare("nm"))
    wavelength = wavelength/1e9;
  else if(!unit.compare("mm"))
    wavelength = wavelength/1e3;
  else if(!unit.compare("m"))
    wavelength = wavelength;
  else if(!unit.compare("km"))
    wavelength = wavelength*1e3;
  else
  {
    std::cout << "MantisROOT::Wave2Energy -> ERROR Unit not found." << std::endl;
    return -1;
  }
  double energy = hc/wavelength;
  return energy/1.60218e-19; // unit eV
} // end of Wave2Energy Function




void MantisROOT::ZScore(const char* filenameOn, bool weightedOn, const char* filenameOff, bool weightedOff)
{
  double counts_on, counts_off, error_on, error_off;

  GetCountIntegralAndError(filenameOn, weightedOn, counts_on, error_on);
  GetCountIntegralAndError(filenameOff, weightedOff, counts_off, error_off);
  double z_score = std::abs(counts_on - counts_off)/sqrt(pow(error_on,2) + pow(error_off,2));
  std::cout << "MantisROOT::ZScore: " << z_score << std::endl;
} // end of ZScore Function 1



void MantisROOT::ZScore(double countsOn, double errorOn, double countsOff, double errorOff)
{
  double zscore = std::abs(countsOn - countsOff)/sqrt(pow(errorOn,2) + pow(errorOff,2));
  std::cout << "MantisROOT::ZScore: " << zscore << std::endl;
} // end of ZScore Function 2



void MantisROOT::ZScore(double countsOn, double countsOff)
{
  double zscore = std::abs(countsOn - countsOff)/sqrt(pow(sqrt(countsOn),2) + pow(sqrt(countsOff),2));
  std::cout << "ZScore Result: " << zscore << std::endl;
  std::cout << std::endl << "MantisROOT::ZScore -> Complete." << std::endl;
} // end of ZScore Function 3

// END OF PUBLIC MEMBER FUNCTIONS
// *************************************************************************//
// *************************************************************************//
// *************************************************************************//


// START PRIVATE MEMBER FUNCTIONS
// *************************************************************************//
// *************************************************************************//
// *************************************************************************//

TH1D* MantisROOT::BuildBremSampling(const std::vector<double> E_below_threshold, double non_nrf_energy_cut, double deltaE, double Emax, double theweight)
{
  // create the sampling distribution
	// user can adjust relative scales in SetBinContent
  int nbins = Emax/deltaE;
  string hName;
  if(deltaE == 10.0e-3)
    hName = "h_sample_short";
  else
    hName = "h_sample_long";

  TH1D *h_sample = new TH1D(hName.c_str(), "h_sample", nbins, 0., Emax);
  double weight = 1./theweight;
	for (int i = 1; i <= nbins; ++i) {
		double e = h_sample->GetBinCenter(i);

		for (int j = 0; j < E_below_threshold.size(); ++j)
		{
			if (e < non_nrf_energy_cut)
			{
				h_sample->SetBinContent(i, weight);
			}
  		else if (e > E_below_threshold[j] - deltaE && e < E_below_threshold[j] + deltaE)
  		{
				h_sample->SetBinContent(i, 1);
				break;
  		}
  		else
  		{
				h_sample->SetBinContent(i, 0.1);
			}
		}
	}

	// normalize h_sample so that its integral is 1
	h_sample->Scale(1./h_sample->Integral());
  return h_sample;
} // end of BuildBremSampling Private Function




TH1D* MantisROOT::BuildSimpleSample(const char* filename, const char* obj, double deltaE, double cut_energy1, double cut_energy2, double weight1, double weight2)
{
  if(cut_energy1 > cut_energy2)
  {
    std::cerr << "MantisROOT::BuildSimpleSample -> FATAL ERROR Energy Cut 1 cannot be greater than Energy Cut 2!" << std::endl;
    exit(1);
  }

  double Emax = ReturnMax(filename, obj);
  double Emin = ReturnMin(filename, obj);

  int nbins = Emax/deltaE;
  string hName;

  if(deltaE == 10.0e-3)
    hName = "h_sample_short";
  else
    hName = "h_sample_long";

  TH1D *h_sample = new TH1D(hName.c_str(), "h_sample", nbins, Emin, Emax);
  double theWeight1 = 1./weight1;
  double theWeight2 = 1./weight2;
	// create the sampling distribution
	// user can adjust relative scales in SetBinContent
	for (int i = 1; i <= nbins; ++i)
  {
		double e = h_sample->GetBinCenter(i);

		if (e < cut_energy1)
			h_sample->SetBinContent(i, theWeight1);
    else if(e < cut_energy2 && e > cut_energy1)
      h_sample->SetBinContent(i, theWeight2);
		else
			h_sample->SetBinContent(i, 1);
	}

	// normalize h_sample so that its integral is 1
	h_sample->Scale(1.0/(h_sample->Integral()));
  std::cout << "MantisROOT::BuildSimpleSample -> Sampling Distribution Created." << std::endl;
  return h_sample;
} // end of BuildSimpleSample Private Function



void MantisROOT::CheckFile(const char* filename)
{
  if(gSystem->AccessPathName(filename))
  {
    std::cout << "File " << filename << " Not Found." << std::endl;
    exit(1);
  }
} // end of CheckFile Private Function



void MantisROOT::Compute(const char* fname, time_t time_start, bool Weighted, bool Corrected)
{
  int x =0;
  TFile *fMaincompute = new TFile(fname);
  fMaincompute->cd();
  string filename = fMaincompute->GetName();
  TTree *Cherenkov_in, *NRF_in, *DetInfo_in;
  fMaincompute->GetObject("Cherenkov",Cherenkov_in);
  fMaincompute->GetObject("NRF",NRF_in);

  if(Corrected)
    fMaincompute->GetObject("Corrected_DetInfo", DetInfo_in);
  else
    fMaincompute->GetObject("DetInfo",DetInfo_in);

  Cherenkov_in->SetEstimate(-1);
  NRF_in->SetEstimate(-1);
  DetInfo_in->SetEstimate(-1);

  if(debug)
    std::cout << "CheckEvents::Compute -> Objects Grabbed!" << std::endl;

  int nrf_entries = NRF_in->Draw("EventID","","goff");
  double *nrfEvent = NRF_in->GetVal(0);
  std::vector<int> nrfEventv;
  // Write NRF Events to Vector
  for(int i=0; i<nrf_entries; ++i)
  {
    nrfEventv.push_back((int)nrfEvent[i]);
  }

  int nrf_entries_intObj = NRF_in->Draw("EventID","Material == \"IntObj\"","goff");
  double *nrfEvent_intObj = NRF_in->GetVal(0);
  std::vector<int> nrfEventv_intObj;
  // Write NRF Events to Vector
  for(int i=0; i<nrf_entries_intObj; ++i)
  {
    nrfEventv_intObj.push_back((int)nrfEvent_intObj[i]);
  }

  std::cout << "CheckEvents::Compute -> NRF Entries:        " << nrf_entries << std::endl;
  std::cout << "CheckEvents::Compute -> NRF IntObj Entries: " << nrf_entries_intObj << std::endl;

  // Grab Cherenkov Events
  int cher_entries = Cherenkov_in->Draw("EventID","","goff");

  std::cout << "CheckEvents::Compute -> Cherenkov Entries:  " << cher_entries << std::endl;

  double *cherEvent = Cherenkov_in->GetVal(0);

  std::vector<int> cherEventv;
  // Write Cherenkov Events to vector
  for(int i=0; i<cher_entries; ++i)
  {
    cherEventv.push_back((int)cherEvent[i]);
  }

  // Grab DetInfo Events
  int det_entries =0;

  if(Weighted)
    det_entries = DetInfo_in->Draw("EventID:Energy:CreatorProcess:Time:Weight", "CreatorProcess == \"Scintillation\" || CreatorProcess == \"Cerenkov\"","goff");
  else
    det_entries = DetInfo_in->Draw("EventID:Energy:CreatorProcess:Time","CreatorProcess == \"Scintillation\" || CreatorProcess == \"Cerenkov\"","goff");

  std::cout << "CheckEvents::Compute -> Total Number of Detected Optical Photon entries: "
            << det_entries << std::endl << std::endl;

  double *detEvent = DetInfo_in->GetVal(0);
  double *detEnergy = DetInfo_in->GetVal(1);

  std::cout << "MantisROOT::Compute -> Setting CreatorProcess Branch Address..." << std::endl;

  Char_t creators[16];
  DetInfo_in->SetBranchAddress("CreatorProcess",&creators);

  double *detTime = DetInfo_in->GetVal(3);
  double *detWeight = new double[(int)det_entries];

  if(Weighted)
    detWeight = DetInfo_in->GetVal(4);

  std::vector<int> detEventv;
  std::vector<double> detEnergyv, detWeightv, detTimev;
  std::vector<string> detCreatorv;

  for(int i=0; i<det_entries; ++i)
  {
    detEventv.push_back((int)detEvent[i]);
    DetInfo_in->GetEntry(i);
    string creator_string = string(creators);
    detCreatorv.push_back(creator_string);
    detEnergyv.push_back(detEnergy[i]);
    detTimev.push_back(detTime[i]);

    if(Weighted)
      detWeightv.push_back(detWeight[i]);
  }

  std::vector<int> nrf_to_cherEvents, nrf_to_cherEvents_intObj, nrf_to_cher_to_det_event, nrf_to_cher_to_det_event_intObj;

  if(nrf_entries != 0 && cher_entries != 0 && det_entries != 0)
  {
    std::cout << "CheckEvents::Compute -> Finding NRF Events that Caused Optical Photons..." << std::endl;

    for(int i=0; i<nrf_entries; ++i)
    {
      // Grab nrf Event ID
      x = nrfEventv[i];
      // Check if NRF EventID is found in Cherenkov Vector
      auto exists = std::find(cherEventv.begin(),cherEventv.end(), x);

      if(exists != cherEventv.end())
        // if the eventID is found in cherenkov write to new vector
        nrf_to_cherEvents.push_back(x);
    }
    std::cout << "CheckEvents::Compute -> NRF to Optical Photon Number of Events Found: "
            << nrf_to_cherEvents.size() << std::endl;

    if(nrf_entries_intObj != 0)
    {
      std::cout << "CheckEvents::Compute -> Finding NRF Events from Interrogation Object that Caused Optical Photons..." << std::endl;

      for(int i=0;i<nrf_entries_intObj;++i)
      {
        x = nrfEventv_intObj[i];
        auto exists = std::find(cherEventv.begin(),cherEventv.end(),x);
        if(exists != cherEventv.end())
          nrf_to_cherEvents_intObj.push_back(x);
      }
    }
    std::cout << "CheckEvents::Compute -> Interrogation Object NRF to Optical Photon Number of Events Found: "
            << nrf_to_cherEvents_intObj.size() << std::endl;

    for(unsigned int i=0; i<nrf_to_cherEvents.size(); ++i)
    {
      // Check if nrf->cherenkov event ID is in detected
      x = nrf_to_cherEvents[i];
      auto exists = std::find(detEventv.begin(), detEventv.end(), x);
      if(exists != detEventv.end())
      {
        // if the eventID is found write to new vector
        nrf_to_cher_to_det_event.push_back(x);
      }
    }
    std::cout << "CheckEvents::Compute -> NRF to Optical Photons Detected Number of Events: "
            << nrf_to_cher_to_det_event.size() << std::endl;

    if(nrf_entries_intObj != 0)
    {
      for(unsigned int i=0;i<nrf_to_cherEvents_intObj.size();++i)
      {
        x = nrf_to_cherEvents_intObj[i];
        auto exists = std::find(detEventv.begin(),detEventv.end(),x);
        if(exists != detEventv.end())
          nrf_to_cher_to_det_event_intObj.push_back(x);
      }
      std::cout << "CheckEvents::Compute -> Interrogation Object NRF to Optical Photons Detected Number of Events: "
              << nrf_to_cher_to_det_event_intObj.size() << std::endl;
    }

  } // end if nrf_entries != 0 && cher_entries != 0

  std::cout << "CheckEvents::Compute -> Finding Total Number of NRF to Optical Photons Detected..." << std::endl;

  if(debug)
    std::cout << "CheckEvents::Compute -> Sorting DetInfo..." << std::endl;

  // Zipping Process for sorting
  std::vector<std::tuple<int, double, string, double>> zipped4; // No Weights
  std::vector<std::tuple<int, double, string, double, double>> zipped5; // weighted

  if(Weighted)
  {
    zip(detEventv, detEnergyv, detCreatorv, detTimev, detWeightv, zipped5);
    std::sort(zipped5.begin(),zipped5.end());
    unzip(zipped5, detEventv, detEnergyv, detCreatorv, detTimev, detWeightv);
  }
  else
  {
    zip(detEventv, detEnergyv, detCreatorv, detTimev, zipped4);
    std::sort(zipped4.begin(),zipped4.end());
    unzip(zipped4, detEventv, detEnergyv, detCreatorv, detTimev);
  }

  if(debug)
    std::cout << "MantisROOT::Compute -> DetInfo Sorted." << std::endl;

  int index = 0;
  int tmp_index = 0;
  std::vector<int> final_nrf_det_eventsv;
  std::vector<double> final_nrf_det_energiesv, final_nrf_det_timesv, final_nrf_det_weightsv;
  std::vector<string> final_nrf_det_creatorsv;
  std::vector<int> final_nrf_det_eventsv2;
  std::vector<double> final_nrf_det_energiesv2, final_nrf_det_timesv2, final_nrf_det_weightsv2;
  std::vector<string> final_nrf_det_creatorsv2;

  std::cout << "MantisROOT::Compute -> NRF to Det EventID Vector Size: " << nrf_to_cher_to_det_event.size() << std::endl;
  std::cout << "MantisROOT::Compute -> Interrogation Object NRF to Det EventID Vector Size: " << nrf_to_cher_to_det_event_intObj.size() << std::endl;
  std::cout << "MantisROOT::Compute -> DetInfo EventID Vector Size: " << detEventv.size() << std::endl;

  if(nrf_to_cher_to_det_event.size() > 0)
  {
    while(index < detEventv.size())
    {
      if(!debug)
        std::cout << "\r** Checking Entry: " << index << std::flush;
      else
        std::cout << "Checking Entry: " << index << std::endl;

      // Grab Det EventID
      x = detEventv[index];

      if(debug)
        std::cout << "X: " << x << std::endl;
      // Check if DetInfo EventID matches nrf_to_det_EventID
      auto exists = std::find(nrf_to_cher_to_det_event.begin(),nrf_to_cher_to_det_event.end(), x);

      // if found write event info to new vectors
      if(exists != nrf_to_cher_to_det_event.end())
      {
        final_nrf_det_eventsv.push_back(x);
        final_nrf_det_energiesv.push_back(detEnergyv[index]);
        final_nrf_det_creatorsv.push_back(detCreatorv[index]);
        final_nrf_det_timesv.push_back(detTimev[index]);

        if(Weighted)
          final_nrf_det_weightsv.push_back(detWeightv[index]);

        int counter = 0;
        while(counter >= 0)
        {
          counter++;
          tmp_index = index + counter;
          if(x == detEventv[index+counter])
          {
            final_nrf_det_eventsv.push_back(x);
            final_nrf_det_energiesv.push_back(detEnergyv[index+counter]);
            final_nrf_det_creatorsv.push_back(detCreatorv[index+counter]);
            final_nrf_det_timesv.push_back(detTimev[index+counter]);

            if(Weighted)
              final_nrf_det_weightsv.push_back(detWeightv[index+counter]);

          } // end of if(x == det_eventsv[index+counter])
          else
          {
            index = tmp_index;
            counter = -1;

            if(debug)
              std::cout << "While Else Index: " << index << std::endl;
          } // end of else
        } // end of while counter > 0
      } // end of if exists !=
      else
        index++;
    } // end of While index < detEvent.size()
  } // end of if nrf_to_cher_event > 0

  std::cout << std::endl << "MantisROOT::Compute -> Total Number of NRF Optical Photons Found: "
            << final_nrf_det_eventsv.size() << std::endl;

  if(nrf_to_cher_to_det_event_intObj.size() > 0)
  {
    index = 0;
    tmp_index = 0;
    while(index < detEventv.size())
    {
      if(!debug)
        std::cout << "\r** Checking Entry: " << index << std::flush;
      else
        std::cout << "Checking Entry: " << index << std::endl;

      // Grab Det EventID
      x = detEventv[index];
      // Check if DetInfo EventID matches nrf_to_det_EventID
      auto exists = std::find(nrf_to_cher_to_det_event_intObj.begin(),nrf_to_cher_to_det_event_intObj.end(), x);

      // if found write event info to new vectors
      if(exists != nrf_to_cher_to_det_event_intObj.end())
      {
        final_nrf_det_eventsv2.push_back(x);
        final_nrf_det_energiesv2.push_back(detEnergyv[index]);
        final_nrf_det_creatorsv2.push_back(detCreatorv[index]);
        final_nrf_det_timesv2.push_back(detTimev[index]);

        if(Weighted)
          final_nrf_det_weightsv2.push_back(detWeightv[index]);

        int counter = 0;
        while(counter >= 0)
        {
          counter++;
          tmp_index = index + counter;
          if(x == detEventv[index+counter])
          {
            final_nrf_det_eventsv2.push_back(x);
            final_nrf_det_energiesv2.push_back(detEnergyv[index+counter]);
            final_nrf_det_creatorsv2.push_back(detCreatorv[index+counter]);
            final_nrf_det_timesv2.push_back(detTimev[index+counter]);

            if(Weighted)
              final_nrf_det_weightsv2.push_back(detWeightv[index+counter]);

          } // end of if(x == det_eventsv[index+counter])
          else
          {
            index = tmp_index;
            counter = -1;
          } // end of else
        } // end of while counter > 0
      } // end of if exists !=
      else
        index++;
    } // end of While index < detEvent.size()
  } // end of if nrf_to_cher_event > 0

  std::cout << std::endl << "MantisROOT::Compute -> Total Number of Interrogation Object NRF Optical Photons Found: "
            << final_nrf_det_eventsv2.size() << std::endl;

  fMaincompute->Close();

  // Open New TFile to write to
  string event_output_name = "w_events_" + filename;
  TFile *fin = new TFile(event_output_name.c_str(),"recreate");
  fin->cd();

  // Set up NRF to Cher to Det Tree
  int event;
  double energy, weight, thetimes;
  string theCreator;

  TTree *nrf_to_cher_to_det_tree = new TTree("event_tree","NRF Events that Lead to Cherenkov that were Detected");
  nrf_to_cher_to_det_tree->Branch("EventID",&event);
  nrf_to_cher_to_det_tree->Branch("Energy",&energy);
  nrf_to_cher_to_det_tree->Branch("CreatorProcess",&theCreator);
  nrf_to_cher_to_det_tree->Branch("Time",&thetimes);

  if(Weighted)
    nrf_to_cher_to_det_tree->Branch("Weight",&weight);

  // Copy for Interrogation Object NRF
  int event2;
  double energy2, weight2, thetimes2;
  string theCreator2;

  TTree *nrf_to_cher_to_det_tree2 = new TTree("event_tree2","Interrogation Object NRF Events that Lead to Cherenkov that were Detected");
  nrf_to_cher_to_det_tree2->Branch("EventID",&event2);
  nrf_to_cher_to_det_tree2->Branch("Energy",&energy2);
  nrf_to_cher_to_det_tree2->Branch("CreatorProcess",&theCreator2);
  nrf_to_cher_to_det_tree2->Branch("Time",&thetimes2);

  if(Weighted)
    nrf_to_cher_to_det_tree2->Branch("Weight",&weight2);

  // Fill nrf_to_cher_to_det Tree
  if(nrf_to_cher_to_det_event.size() > 0)
  {
    // Fill tree
    for(unsigned int i=0; i<final_nrf_det_eventsv.size(); ++i)
    {
      event = final_nrf_det_eventsv[i];
      energy = final_nrf_det_energiesv[i];
      theCreator = final_nrf_det_creatorsv[i];
      thetimes = final_nrf_det_timesv[i];

      if(Weighted)
        weight = final_nrf_det_weightsv[i];

      nrf_to_cher_to_det_tree->Fill();
    }
  }

  if(nrf_to_cher_to_det_event_intObj.size() > 0)
  {
    for(unsigned int i=0;i<final_nrf_det_eventsv2.size();++i)
    {
      event2 = final_nrf_det_eventsv2[i];
      energy2 = final_nrf_det_energiesv2[i];
      theCreator2 = final_nrf_det_creatorsv2[i];
      thetimes2 = final_nrf_det_timesv2[i];

      if(Weighted)
        weight2 = final_nrf_det_weightsv2[i];

      nrf_to_cher_to_det_tree2->Fill();
    }
  }

  nrf_to_cher_to_det_tree->Write();
  nrf_to_cher_to_det_tree2->Write();

  std::cout << "CheckEvents::Compute -> TTrees Written to File: "
              << event_output_name << std::endl;

  fin->Close();

  time_t timer2;
  time_t time_end = std::time(&timer2);
  std::cout << "CheckEvents::Compute -> Event Check took: " << std::difftime(time_end, time_start)
          << " seconds!" << std::endl << std::endl;

} // end of Compute Private Function



void MantisROOT::CopyATree(const char* filename, const char* tObj, const char* outfilename)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  if(f == 0)
    exit(0);

  TTree *oldTree;
  f->GetObject(tObj, oldTree);
  oldTree->SetBranchStatus("*",1);

  TFile *newfile;
  if(gSystem->AccessPathName(outfilename))
    newfile = new TFile(outfilename, "recreate");
  else
    newfile = new TFile(outfilename,"update");

  auto newtree = oldTree->CloneTree();

  newtree->Print();
  // write to new file
  newfile->Write();
  newfile->Close();
}// end of CopyATree Private Function





void MantisROOT::CopyATreeNoWeight(const char* filename, const char* tObj, const char* outfilename)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  if(f == 0)
    exit(0);

  TTree *oldTree;
  f->GetObject(tObj, oldTree);

  oldTree->SetBranchStatus("*",0);

  if(!string(tObj).compare("ChopIn"))
  {
    for(auto activeBranchName : {"Energy","EventID"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("ChopOut"))
  {
    for(auto activeBranchName : {"Energy","EventID","isNRF","Theta","Phi"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("NRF"))
  {
    for(auto activeBranchName : {"EventID","Energy", "Material", "ZPos"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("AirIn") || !string(tObj).compare(0,6,"IntObj"))
  {
    for(auto activeBranchName : {"Energy", "CreatorProcess", "Theta", "Phi", "Time", "EventID"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("Water"))
  {
    for(auto activeBranchName : {"Energy","CreatorProcess","EventID", "TrackID"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("Cherenkov"))
  {
    for(auto activeBranchName : {"Energy","EventID", "NumSecondaries", "Time"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("DetInfo"))
  {
    for(auto activeBranchName : {"EventID", "Energy", "CreatorProcess", "Time", "X", "Y"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("IncDetInfo"))
  {
    for(auto activeBranchName : {"EventID", "Energy", "DetProcess"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("Corrected_DetInfo"))
  {
    for(auto activeBranchName :{"EventID", "Energy", "CreatorProcess", "Time"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("Erroneous_DetInfo"))
  {
    for(auto activeBranchName :{"EventID"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else if(!string(tObj).compare("event_tree") || !string(tObj).compare("event_tree2"))
  {
    for(auto activeBranchName :{"EventID","Energy","CreatorProcess","Time"})
    {
      oldTree->SetBranchStatus(activeBranchName,1);
    }
  }
  else
  {
    std::cerr << "ERROR: Object Name not found." << std::endl;
    exit(1);
  }

  TFile *newfile;
  if(gSystem->AccessPathName(outfilename))
    newfile = new TFile(outfilename, "recreate");
  else
    newfile = new TFile(outfilename,"update");

  auto newtree = oldTree->CloneTree();

  newtree->Print();
  // write to new file
  newfile->Write();
  newfile->Close();
} // end of CopyTreeNoWeight Function



void MantisROOT::DrawWeights(TGraph* input, TGraph* sample, string canvas_name="c1")
{
  std::cout << "MantisROOT::DrawWeights -> Drawing Weights..." << std::endl;
  TCanvas* c_Weighting_Spectra = new TCanvas(canvas_name.c_str(),"Weighting Spectra",600,400);
  c_Weighting_Spectra->cd();
  gPad->SetTicks(1,1);
  gPad->SetLogy();
  std::vector<double> energies, theweights;
  energies.push_back(0);
  theweights.push_back(0);
  double maxE = TMath::MaxElement(input->GetN(), input->GetX());
  for(double i=maxE/1000.;i<maxE;i += maxE/1000.)
  {
    energies.push_back(i);
  }
  for(int i=1;i<energies.size();++i)
  {
    double energy = energies[i];
    double w = input->Eval(energy)/sample->Eval(energy);
    if(w == 0)
    {
      std::cout << "MantisROOT::DrawWeights WARNING Zero Weight Detected!" << std::endl
      << "Energy: " << energy << " MeV" << std::endl
      << "dNdE: " << input->Eval(energy) << std::endl << "Sampling: " << sample->Eval(energy)
      << std::endl;
    }
    theweights.push_back(w);
  }

  TGraph* gWeights = new TGraph(energies.size(), &energies[0], &theweights[0]);
  gWeights->SetTitle("Weighting Spectrum");
  gWeights->GetXaxis()->SetTitle("Energy [MeV]");
  gWeights->GetYaxis()->SetTitle("Weight");
  gWeights->GetYaxis()->SetRangeUser(1e-4,1e5);
  gWeights->Draw("AC");

  std::cout << "MantisROOT::DrawWeights -> Weighting Drawn." << std::endl;
} // end of DrawWeights Private Function



string MantisROOT::EraseSubStr(string & mainStr, const string & toErase)
{
    // Search for the substring in string
    string newString = mainStr;
    size_t pos = newString.find(toErase);
    if (pos != std::string::npos)
    {
        // If found then erase it from string
        newString.erase(pos, toErase.length());
    }
    return newString;
} // end of EraseSubStr Private Function


void MantisROOT::GetCountIntegralAndError(const char* filename, bool weighted, double& counts, double& error)
{
  CheckFile(filename);
  TFile* f = new TFile(filename);
  f->cd();
  TTree* tree;
  f->GetObject("DetInfo",tree);
  tree->SetEstimate(-1);
  TH1D* h = new TH1D("h","h",100,0.,tree->GetMaximum("Energy"));
  if(weighted)
    tree->Draw("Energy>>h","Weight","goff");
  else
    tree->Draw("Energy>>h","","goff");

  counts = h->IntegralAndError(0,100, error);

  delete h;
  f->Close();
} // end of GetCountIntegralAndError Private Function



void MantisROOT::hIntegral(TH1 *h)
{
  int nentries = h->GetEntries();
  TAxis *xaxis = h->GetXaxis();
  double hMean = h->GetMean();
  int nbins = h->GetNbinsX();

  double intSum = 0;
  for(unsigned int i=0;i<nbins;++i)
  {
    double xVal = xaxis->GetBinCenter(i);
    double binVal = h->GetBinContent(i);
    double integralVal = xVal*binVal;
    intSum += integralVal;
  }
  std::cout << h->GetTitle() << " BinCenter Method Sum: " << intSum << std::endl;
  std::cout << h->GetTitle() << " Mean Method Sum: " << nentries*hMean << std::endl;
  std::cout << h->GetTitle() << " Integral Method: " << h->Integral() << std::endl << std::endl;
} // end of hIntegral Private Function 1



double MantisROOT::hIntegralReturn(TTree* inObj, bool cut, TCut cut1="NA")
{
  inObj->SetEstimate(-1);

  if(cut)
  {
    if(debug)
      std::cout << "Cut " << cut1 << " placed!" << std::endl;
    inObj->Draw("Energy",cut1,"goff");
  }
  else
    inObj->Draw("Energy","","goff");

  Double_t *energies = inObj->GetVal(0);
  int nentries = inObj->GetEntries();
  double intSum = 0;

  for(unsigned int i=0;i<nentries;++i)
  {
    intSum +=energies[i];
  }
  return intSum;
} // end of hIntegral Private Function 7




double MantisROOT::hIntegralReturnWeightedCounts(TTree* inObj, double cut_energy=5e-6)
{
  inObj->SetEstimate(-1);
  TH1D* h = new TH1D("h","Det Integral",100,0.,cut_energy);

  if(debug)
    std::cout << "Cut " << cut_energy << " MeV placed!" << std::endl;
  inObj->Draw("Energy>>h","Weight","goff");
  double intSum = h->Integral();

  std::cout << "MantisROOT::hIntegralReturnWeightedCounts -> Deallocating Memory..." << std::endl;

  delete h;
  return intSum;

} // end of hIntegral Private Function 8




double MantisROOT::hIntegralReturnWeightedEnergy(TTree* inObj, double cut_energy=5e-6)
{
  inObj->SetEstimate(-1);
  if(debug)
    std::cout << "Cut " << cut_energy << " MeV placed!" << std::endl;
  int nentries = inObj->Draw("Energy:Weight","","goff");
  double *Energies = inObj->GetVal(0);
  double *Weights = inObj->GetVal(1);

  double intSum = 0;
  for(int i=0;i<nentries;++i)
  {
    intSum += Energies[i]*Weights[i];
  }
  if(debug)
    std::cout << "MantisROOT::hIntegralReturnWeightedEnergy -> Deallocating Memory..." << std::endl;

  return intSum;
} // end of hIntegral Private Function 9



void MantisROOT::hIntegral(TTree *inObj,TCut cut1)
{
  inObj->SetEstimate(-1);
  double Emax = inObj->GetMaximum("Energy");
  TH1D *e1 = new TH1D("e1",inObj->GetName(),100,0.,Emax);

  if(cut1 == "NA")
    inObj->Draw("Energy>>e1","","goff");
  else
    inObj->Draw("Energy>>e1",cut1,"goff");

  Double_t *energies = inObj->GetVal(0);
  int nentries = inObj->GetEntries();
  double intSum = 0;

  for(unsigned int i=0;i<nentries;++i)
  {
    intSum +=energies[i];
  }

  std::cout << inObj->GetName() << " TTree Sum: " << intSum << std::endl;

  hIntegral(e1);
  if(debug)
    std::cout << "MantisROOT::hIntegral -> Deallocating Memory..." << std::endl;
  delete e1; // avoids potential memory leak
}




TGraph* MantisROOT::PrepInputSpectrum(const char* filename, const char* obj, bool smooth, bool Weighted, double deltaE, bool checkZero)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  f->cd();
  TTree* tin;
  f->GetObject(obj, tin);
  double maxE = tin->GetMaximum("Energy");
  int nbins = maxE/deltaE;
  int nbins2 = maxE/5e-6;
  TH1D* dNdE_histogram = new TH1D("dNdE_histogram","dNdE Histogram Spectrum", nbins, 0., maxE);
  if(Weighted)
    tin->Draw("Energy>>dNdE_histogram","Weight","goff");
  else
    tin->Draw("Energy>>dNdE_histogram","","goff");

  if(smooth)
    dNdE_histogram->Smooth(1000);

  if(debug)
    dNdE_histogram->Print();

  // check for zeros
  if(checkZero)
    CheckZeros(dNdE_histogram, nbins);

  dNdE_histogram->Scale(1./dNdE_histogram->Integral());
  dNdE_histogram->GetXaxis()->SetTitle("Energy [MeV]");
  int titleEValue = deltaE*1e6;
  string yTitle = "Probability per " + std::to_string(titleEValue) + " eV";
  dNdE_histogram->GetYaxis()->SetTitle(yTitle.c_str());
  TGraph* dNdE_graph = new TGraph(dNdE_histogram);

  // Here perform rebinning
  if(debug)
    std::cout << "MantisROOT::PrepInputSpectrum -> Rebinning..." << std::endl;

  TH1D* dNdE_histogram_rebinned = new TH1D("dNdE_histogram_rebinned","dNdE Histogram Spectrum",nbins2, 0., maxE);
  for(int i=0;i<nbins2;++i)
  {
    double this_energy = dNdE_histogram_rebinned->GetXaxis()->GetBinCenter(i);
    double new_dNdE_value = dNdE_graph->Eval(this_energy);
    dNdE_histogram_rebinned->SetBinContent(i,new_dNdE_value);
  }

  if(debug)
    std::cout << "MantisROOT::PrepInputSpectrum -> Rebinning Complete...Checking Zeros..." << std::endl;

  if(checkZero)
    CheckZeros(dNdE_histogram_rebinned,nbins2);

  //dNdE_histogram_rebinned->Scale(1./dNdE_histogram_rebinned->Integral());

  if(debug)
  {
    std::cout << "MantisROOT::PrepInputSpectrum -> Writing dNdE_histogram..." << std::endl;
    dNdE_histogram->Print();
  }
  WriteSampling(dNdE_histogram_rebinned);
  //TGraph* dNdE_graph1 = new TGraph(dNdE_histogram_rebinned);
  f->Close();
  return dNdE_graph;
} // end of PrepInputSpectrum Private Function



void MantisROOT::Rescale(const char* inObj, double Er, bool write2file=false)
{
  std::cout << "Input the Scale Base Filename:" << std::endl;
  string filename;
  std::cin >> filename;
  std::vector<std::string> user_files;
  std::vector<float> user_thick;
  std::vector<TFile*> tfilesv;

  // check to make sure file exists
  CheckFile(filename.c_str());

  // Handle the Base File
  user_files.push_back(filename);
  TFile *base = new TFile(filename.c_str());
  tfilesv.push_back(base);

  std::cout << "Input the Scale Base Thickness:" << std::endl;
  float b_thick;
  std::cin >> b_thick;
  user_thick.push_back(b_thick);

  string response = "Y";
  float thick;

  // Handle Files to be scaled
  while(!strcmp(response.c_str(),"Y"))
  {
    std::cout << "Input Filename to Scale: " << std::endl;
    std::cin >> filename;
    user_files.push_back(filename);

    CheckFile(filename.c_str());

    TFile *data_file = TFile::Open(filename.c_str());
    tfilesv.push_back(data_file);
    std::cout << "Input Thickness: " << std::endl;
    std::cin >> thick;
    user_thick.push_back(thick);
    std::cout << "Would you like to load another file?" << std::endl;
    std::cin >> response;
  }

  base->cd();
  double lowE = Er - 0.0001;
  double highE = Er + 0.0001;

  TH1D *hBase = new TH1D("hBase","Scale Base Histogram",60,lowE,highE);

  TTree *base_tInObj;
  base->GetObject(inObj,base_tInObj);
  base_tInObj->SetEstimate(-1);
  double Emax = base_tInObj->GetMaximum("Energy");
  TH1D *oghBase = new TH1D("theBase","Full Base Histogram",100,0.,Emax);
  base_tInObj->Draw("Energy>>theBase","Weight","goff");
  std::vector<TH1D*> ogOut;
  ogOut.push_back(oghBase);
  base_tInObj->Draw("Energy>>hBase","Weight","goff");
  std::vector<TH1D*> hOut;
  hOut.push_back(hBase);

  // based on 60 bins in histograms normalize to background
  std::vector<double> binValues;
  for(int i=0;i<60;++i)
  {
    binValues.push_back(hBase->GetBinContent(i));
  }

  std::cout << "Base set." << std::endl;

  std::cout << "Creating Histograms..." << std::endl;
  TTree *scale_tInObj;

  TH1D *hIn = new TH1D("hIn","Scaled Histogram",60,lowE,highE);
  for(int i=1;i<tfilesv.size();++i)
  {
    TFile *scaleFile = tfilesv[i];
    scaleFile->cd();
    //scaleFile->ls();
    scaleFile->GetObject(inObj,scale_tInObj);
    if(scale_tInObj !=0)
      std::cout << scaleFile->GetName() << " " << inObj << " grabbed."
                  << std::endl;
    else
    {
      std::cerr << "Error Object " << inObj << " not found in file: "
                  << scaleFile->GetName() << std::endl;
      exit(1);
    }

    TH1D *hIn = new TH1D("hIn","Scaled Histogram",60,lowE,highE);
    TH1D *oghIn = new TH1D("theH","Full Histogram to be Scaled",100,0.,Emax);
    scale_tInObj->SetEstimate(-1);
    scale_tInObj->Draw("Energy>>theH","Weight","goff");
    string fullhname = "full_" + std::to_string(i);
    ogOut.push_back(oghIn);
    ogOut[i]->SetName(fullhname.c_str());

    int nentries = scale_tInObj->Draw("Energy:Weight","","goff");
    Double_t* energies = scale_tInObj->GetVal(0);
    Double_t* weights = scale_tInObj->GetVal(1);

    for(unsigned int i=0;i<nentries;++i)
    {
      hIn->Fill(energies[i],weights[i]);
    }

    hOut.push_back(hIn);
    string hname = "Scaled_" + std::to_string(i);
    string htitle = "Scaled_" + user_files[i];
    hOut[i]->SetName(hname.c_str());
    hOut[i]->SetTitle(htitle.c_str());
    //scaleFile->Close();
  }

  std::cout << "Histograms created." << std::endl;
  for(int i=0;i<hOut.size();++i)
    hOut[i]->Print();

  std::cout << "Scaling Histograms." << std::endl;
  double newbinValue = 0;
  std::vector<TH1D*> outputHisto;
  for(int j=1;j<hOut.size();++j)
  {
    for(int i=0;i<60;++i)
    {
      if(binValues[i] == 0)
        newbinValue = 0;
      else
        newbinValue = binValues[i]*pow(hOut[j]->GetBinContent(i)/binValues[i],1./user_thick[j]);

      hOut[j]->SetBinContent(i, newbinValue);

    }
    std::cout << "Histogram Scaled: " <<std::endl;
    hOut[j]->Print();
  }

  // Draw Histograms to canvas
  TCanvas *c0 = new TCanvas();
  c0->cd();
  gPad->SetTicks(1,1);
  hOut[0]->SetLineColor(kBlack);
  std::cout << "Histogram from " << user_files[0]
              << " line color set to: Black" << std::endl;
  hOut[0]->Draw("h");

  std::vector<double> last_colors;
  last_colors.push_back(0);
  int histo_color = 0;
  string histo_color_label;

  for(int i=1;i<hOut.size();++i)
  {
    bool check = false;
    while(!check)
    {
        histo_color = rand() % 9 + 2;
        if(count(last_colors.begin(),last_colors.end(),histo_color) !=0)
        {
            check = false;
        }
        else
        {
            last_colors.push_back(histo_color);
            check = true;
        }
    }
    hOut[i]->SetLineColor(histo_color);
    switch(histo_color)
    {
        case 2:
            histo_color_label = "RED";
            break;
        case 3:
            histo_color_label = "LIGHT GREEN";
            break;
        case 4:
            histo_color_label = "DARK BLUE";
            break;
        case 5:
            histo_color_label = "YELLOW";
            break;
        case 6:
            histo_color_label = "PINK";
            break;
        case 7:
            histo_color_label = "LIGHT BLUE/CYAN";
            break;
        case 8:
            histo_color_label = "MEDIUM GREEN";
            break;
        case 9:
            histo_color_label = "PURPLE";
            break;
        default:
            histo_color_label = "BLACK";
    }
    cout << "Histogram from " << user_files[i] << " line color set to: " << histo_color_label << endl;

    hOut[i]->Draw("h,SAME");
  }

  std::cout << "All Histograms drawn." << std::endl;

  if(write2file)
  {
    // Save to file
    TFile *fout = new TFile("thick_rescale.root","recreate");
    fout->cd();

    for(int i=0;i<hOut.size();++i)
    {
      ogOut[i]->Write();
      hOut[i]->Write();
    }

    std::cout << "Histograms saved." << std::endl;
  }

} // end of Rescale Private Function 1



void MantisROOT::Rescale(const char* inObj, bool write2file=false)
{
  std::cout << "Input the Scale Base Filename:" << std::endl;
  string filename;
  std::cin >> filename;
  std::vector<std::string> user_files;
  std::vector<float> user_thick;
  std::vector<TFile*> tfilesv;

  // check to make sure file exists
  CheckFile(filename.c_str());

  // Handle the Base File
  user_files.push_back(filename);
  TFile *base = new TFile(filename.c_str());
  tfilesv.push_back(base);

  std::cout << "Input the Scale Base Thickness:" << std::endl;
  float b_thick;
  std::cin >> b_thick;
  user_thick.push_back(b_thick);

  string response = "Y";
  float thick;

  // Handle Files to be scaled
  while(!strcmp(response.c_str(),"Y"))
  {
    std::cout << "Input Filename to Scale: " << std::endl;
    std::cin >> filename;
    user_files.push_back(filename);

    CheckFile(filename.c_str());

    TFile *data_file = TFile::Open(filename.c_str());
    tfilesv.push_back(data_file);
    std::cout << "Input Thickness: " << std::endl;
    std::cin >> thick;
    user_thick.push_back(thick);
    std::cout << "Would you like to load another file?" << std::endl;
    std::cin >> response;
  }

  bool same_rescale = false;

  if(!user_files[0].compare(user_files[1]))
    same_rescale = true;

  if(same_rescale)
    std::cout << "Rescaling the same histogram." << std::endl;

  base->cd();

  // Create the base histogram to scale everything else to
  TTree *base_tInObj;
  base->GetObject(inObj,base_tInObj);
  base_tInObj->SetEstimate(-1);
  double Emax = base_tInObj->GetMaximum("Energy");
  TH1D *hBase = new TH1D("hBase","Scale Base Histogram",100,0.,Emax);
  base_tInObj->Draw("Energy>>hBase","Weight","goff");
  std::vector<TH1D*> hOut;
  hOut.push_back(hBase);

  // based on 100 bins in histograms normalize to background
  std::vector<double> binValues;

  for(int i=0;i<100;++i)
  {
    binValues.push_back(hBase->GetBinContent(i));
  }

  std::cout << "Base set." << std::endl;

  std::cout << "Creating Histograms..." << std::endl;
  TTree *scale_tInObj;

  TH1D *hIn = new TH1D("hIn","Scaled Histogram",100,0.,Emax);
  for(int i=1;i<tfilesv.size();++i)
  {
    TFile *scaleFile = tfilesv[i];
    scaleFile->cd();
    //scaleFile->ls();
    scaleFile->GetObject(inObj,scale_tInObj);
    if(scale_tInObj !=0)
      std::cout << scaleFile->GetName() << " " << inObj << " grabbed."
                  << std::endl;
    else
    {
      std::cerr << "Error Object " << inObj << " not found in file: "
                  << scaleFile->GetName() << std::endl;
      exit(1);
    }

    TH1D *hIn = new TH1D("theH","Full Histogram to be Scaled",100,0.,Emax);
    scale_tInObj->SetEstimate(-1);

    int nentries = scale_tInObj->Draw("Energy:Weight","","goff");
    Double_t* energies = scale_tInObj->GetVal(0);
    Double_t* weights = scale_tInObj->GetVal(1);

    for(unsigned int i=0;i<nentries;++i)
    {
      hIn->Fill(energies[i],weights[i]);
    }

    hOut.push_back(hIn);
    string hname = "Scaled_" + std::to_string(i);
    string htitle = "Scaled_" + user_files[i];
    hOut[i]->SetName(hname.c_str());
    hOut[i]->SetTitle(htitle.c_str());
  }

  std::cout << "Histograms created." << std::endl;
  for(int i=0;i<hOut.size();++i)
    hOut[i]->Print();

  std::cout << "Scaling Histograms." << std::endl;
  double newbinValue = 0;
  std::vector<TH1D*> outputHisto;
  for(int j=1;j<hOut.size();++j)
  {
    for(int i=0;i<100;++i)
    {
      if(binValues[i] == 0)
        newbinValue = 0;
      else
      {
        if(same_rescale)
          newbinValue = binValues[i]*user_thick[0]/user_thick[j];
        else
          newbinValue = binValues[i]*pow(hOut[j]->GetBinContent(i)/binValues[i],1./user_thick[j]);
      }
      hOut[j]->SetBinContent(i, newbinValue);

    }
    std::cout << "Histogram Scaled: " <<std::endl;
    hOut[j]->Print();
  }

  // Draw Histograms to canvas
  TCanvas *c0 = new TCanvas();
  c0->cd();
  gPad->SetTicks(1,1);
  hOut[0]->SetLineColor(kBlack);
  std::cout << "Histogram from " << user_files[0]
              << " line color set to: Black" << std::endl;
  hOut[0]->Draw("h");

  std::vector<double> last_colors;
  last_colors.push_back(0);
  int histo_color = 0;
  string histo_color_label;

  for(int i=1;i<hOut.size();++i)
  {
    bool check = false;
    while(!check)
    {
        histo_color = rand() % 9 + 2;
        if(count(last_colors.begin(),last_colors.end(),histo_color) !=0)
        {
            check = false;
        }
        else
        {
            last_colors.push_back(histo_color);
            check = true;
        }
    }
    hOut[i]->SetLineColor(histo_color);
    switch(histo_color)
    {
        case 2:
            histo_color_label = "RED";
            break;
        case 3:
            histo_color_label = "LIGHT GREEN";
            break;
        case 4:
            histo_color_label = "DARK BLUE";
            break;
        case 5:
            histo_color_label = "YELLOW";
            break;
        case 6:
            histo_color_label = "PINK";
            break;
        case 7:
            histo_color_label = "LIGHT BLUE/CYAN";
            break;
        case 8:
            histo_color_label = "MEDIUM GREEN";
            break;
        case 9:
            histo_color_label = "PURPLE";
            break;
        default:
            histo_color_label = "BLACK";
    }
    cout << "Histogram from " << user_files[i] << " line color set to: " << histo_color_label << endl;

    hOut[i]->Draw("h,SAME");
  }

  std::cout << "All Histograms drawn." << std::endl;
  // Save to file
  if(write2file)
  {
    TFile *fout = new TFile("thick_rescale.root","recreate");
    fout->cd();

    for(int i=0;i<hOut.size();++i)
      hOut[i]->Write();

    std::cout << "Histograms saved." << std::endl;
  }

}// end of ALL Rescale Private Functions




double MantisROOT::ReturnMax(const char* filename, const char* obj)
{
  std::cout << "MantisROOT::ReturnMax -> Searching Max Energy..." << std::endl;
  TFile *f = TFile::Open(filename);
  bool confirm = f->cd();
  if(!confirm)
    exit(10);
  TTree *tData;
  f->GetObject(obj, tData);

  double Emax = tData->GetMaximum("Energy");
  std::cout << "MantisROOT::ReturnMax -> Max Found: " << Emax << std::endl;
  return Emax;
} // end of ReturnMax Private Function



double MantisROOT::ReturnMin(const char* filename, const char* obj)
{
  std::cout << "MantisROOT::ReturnMin -> Searching Min Energy..." << std::endl;
  TFile* f = TFile::Open(filename);
  bool confirm = f->cd();

  if(!confirm)
    exit(1);

  TTree* tData;
  f->GetObject(obj, tData);
  double Emin = tData->GetMinimum("Energy");
  std::cout << "MantisROOT::ReturnMin -> Min Found: " << Emin << std::endl;
  return Emin;
} // end of ReturnMin Private Function



void MantisROOT::SNR_IntObj(const char* filename, bool Weighted)
{
  // Check to make sure file exists
  CheckFile(filename);

  TFile *f = new TFile(filename);
  f->cd();
  TTree *aIntObjIn;
  f->GetObject("IntObjIn", aIntObjIn);

  if(aIntObjIn !=0)
  {
    aIntObjIn->Print();
    double inMax = aIntObjIn->GetMaximum("Energy");
    aIntObjIn->SetEstimate(-1);

    TH1D* e11 = new TH1D("e11","IntObjIn NRF Histogram",100,1.73350, 1.73360);
    TH1D* e10 = new TH1D("e10","IntObjIn NRF Histogram",100,1.65620,1.65630);
    TH1D* e12 = new TH1D("e12","IntObjIn NRF Histogram",100,1.81520,1.81530);
    TH1D* e13 = new TH1D("e13","IntObjIn NRF Histogram",100,1.86230,1.86240);
    TH1D* e14 = new TH1D("e14","IntObjIn NRF Histogram",100,2.00615,2.00625);

    TH1D* eT = new TH1D("eT","IntObjIn Histogram",100,0.0,inMax);

    std::cout << "MantisROOT::SNR_IntObj -> Drawing IntObjIn NRF Histograms..." << std::endl;
    if(Weighted)
    {
      aIntObjIn->Draw("Energy>>e10","Weight","goff");
      aIntObjIn->Draw("Energy>>e11","Weight","goff");
      aIntObjIn->Draw("Energy>>e12","Weight","goff");
      aIntObjIn->Draw("Energy>>e13","Weight","goff");
      aIntObjIn->Draw("Energy>>e14","Weight","goff");
    }
    else
    {
      aIntObjIn->Draw("Energy>>e10","","goff");
      aIntObjIn->Draw("Energy>>e11","","goff");
      aIntObjIn->Draw("Energy>>e12","","goff");
      aIntObjIn->Draw("Energy>>e13","","goff");
      aIntObjIn->Draw("Energy>>e14","","goff");
    }

    std::cout << "Drawing IntObjIn and IntObjOut Histograms..." << std::endl;

    if(Weighted)
      aIntObjIn->Draw("Energy>>eT","Weight","goff");
    else
      aIntObjIn->Draw("Energy>>eT","","goff");

    // start integral 5eV prior to energy level peak
    double eStart[] = {1.6562312,1.7335419,1.8152525,1.8623129,2.0061941};
    double eEnd[5];

    for(int i=0;i<5;++i)
      eEnd[i] = eStart[i] + 0.00001; // add 10 eV or 5eV above energy level peak

    int binStart = e10->GetXaxis()->FindBin(eStart[0]);
    int binEnd = e10->GetXaxis()->FindBin(eEnd[0]);
    double inSignal[5];
    inSignal[0] = e10->Integral(binStart, binEnd);
    binStart = e11->GetXaxis()->FindBin(eStart[1]);
    binEnd = e11->GetXaxis()->FindBin(eEnd[1]);
    inSignal[1] = e11->Integral(binStart,binEnd);
    binStart = e12->GetXaxis()->FindBin(eStart[2]);
    binEnd = e12->GetXaxis()->FindBin(eEnd[2]);
    inSignal[2] = e12->Integral(binStart,binEnd);
    binStart = e13->GetXaxis()->FindBin(eStart[3]);
    binEnd = e13->GetXaxis()->FindBin(eEnd[3]);
    inSignal[3] = e13->Integral(binStart,binEnd);
    binStart = e14->GetXaxis()->FindBin(eStart[4]);
    binEnd = e14->GetXaxis()->FindBin(eEnd[4]);
    inSignal[4] = e14->Integral(binStart,binEnd);

    double tSignalin = 0;

    for(int i=0;i<5;++i)
    {
      std::cout << "MantisROOT::SNR_IntObj -> IntObjIn " << eStart[i] << " MeV Signals: \t" << inSignal[i] << std::endl;
      tSignalin += inSignal[i];
    }

    std::cout << "MantisROOT::SNR_IntObj -> Total IntObjIn Signal: \t" << tSignalin << std::endl;

    double inNoise = eT->Integral();
    std::cout << "MantisROOT::SNR_IntObj -> IntObjIn Noise: \t" << inNoise << std::endl;

    std::cout << "MantisROOT::SNR_IntObj -> The NRF photons are removed from the beam in the chopper wheel stage."
              << std::endl
              << "A lower SNR is better because you want the signal from NRF to be minimized."
              << std::endl;
    std::cout << "MantisROOT::SNR_IntObj -> IntObjIn SNR: \t" << tSignalin/sqrt(inNoise) << std::endl;
  }
  else
    std::cerr << "MantisROOT::SNR_IntObj -> ERROR IntObjIn Not Found in " << filename << std::endl;
}// end of SNR_IntObj Private Function




void MantisROOT::SNR_Det(const char* filename, bool Weighted, bool Corrected, bool cut, TCut cut1="NA")
{
  // Check to make sure file exists
  CheckFile(filename);

  // Open the file
  TFile *mainf = new TFile(filename);
  mainf->cd();

  TTree *eventT;
  mainf->GetObject("event_tree",eventT);
  double eventCounts, eventEnergy;
  if(!Weighted)
  {
    if(debug)
      std::cout << "MantisROOT::SNR_Det -> !Weighted hIntegralReturn" << std::endl;
    eventCounts = eventT->GetEntries();
    eventEnergy = hIntegralReturn(eventT,false);
  }
  else
  {
    if(debug)
      std::cout << "MantisROOT::SNR_Det-> Weighted hIntegralReturnWeighted" << std::endl;

    eventCounts = hIntegralReturnWeightedCounts(eventT);
    eventEnergy = hIntegralReturnWeightedEnergy(eventT);
  }

  std::cout << "MantisROOT::SNR_Det -> Detected Counts from NRF: " << eventCounts << std::endl;
  std::cout << "MantisROOT::SNR_Det -> Detected Energy from NRF: " << eventEnergy << " MeV" << std::endl;

  TTree* detT;

  if(Corrected)
    mainf->GetObject("Corrected_DetInfo",detT);
  else
    mainf->GetObject("DetInfo",detT);

  double counts, energy;
  if(!Weighted)
  {
    counts = detT->GetEntries();
    energy = hIntegralReturn(detT,cut,cut1);
  }
  else
  {
    counts = hIntegralReturnWeightedCounts(detT);
    energy = hIntegralReturnWeightedEnergy(detT);
  }

  std::cout << "MantisROOT::SNR_Det -> Total Detected Counts: " << counts << std::endl;
  std::cout << "MantisROOT::SNR_Det -> Total Detected Energy: " << energy << " MeV" << std::endl;

  std::cout << "MantisROOT::SNR_Det -> Counts SNR: " << eventCounts/sqrt(counts) << std::endl;

  if(debug)
    std::cout << "MantisROOT::SNR_Det -> Closing Main File..." << std::endl;

  mainf->Close();

  if(debug)
    std::cout << "MantisROOT::SNR_Det -> Main File Closed." << std::endl;

} // end of SNR_Det Private Function




void MantisROOT::WriteSampling(TGraph* dNdE, TGraph* sampling_graph, TH1D* sampling_histogram, double deltaE_small_bin_width)
{
  dNdE->SetNameTitle("dNdE_graph","dNdE TGraph Distribution");
  sampling_graph->SetNameTitle("sampling_graph","NRF Importance Sampling TGraph Distribution");
  sampling_histogram->SetNameTitle("sampling_histo","NRF Importance Sampling TH1D Distribution");

  string titleProb = "probability per " + std::to_string(deltaE_small_bin_width*1e6) + " eV";
  sampling_histogram->GetXaxis()->SetTitle("energy #it{E} [MeV]");
  sampling_histogram->GetYaxis()->SetTitle(titleProb.c_str());
  sampling_graph->GetXaxis()->SetTitle("Energy #it{E} [MeV]");
  sampling_graph->GetYaxis()->SetTitle(titleProb.c_str());

  // save everything to file
  TFile *fout = new TFile("importance_sampling_input.root","UPDATE");
  fout->cd();

  dNdE->Write();
  sampling_graph->Write();
  sampling_histogram->Write();
  std::cout << "MantisROOT::WriteSampling -> File Complete. Saved to importance_sampling_input.root" << std::endl;
  fout->Close();
} // end of WriteSampling Private Function




void MantisROOT::WriteSampling(TH1D* dNdE_histogram)
{
  if(debug)
  {
    std::cout << "MantisROOT::WriteSampling -> Writing dNdE_histogram..." << std::endl;
    dNdE_histogram->Print();
  }
  TFile* fout = new TFile("importance_sampling_input.root","RECREATE");
  fout->cd();
  dNdE_histogram->Write();
  std::cout << "MantisROOT::WriteSampling -> File Complete. dNdE_histogram saved to importance_sampling_input.root" << std::endl;
  if(debug)
    fout->ls();
  fout->Close();
}

void MantisROOT::WriteSampling(TGraph* dNdE, double delteE)
{
  dNdE->SetNameTitle("dNdE_graph","dNdE TGraph Distribution");
  // save everything to file
  TFile *fout = new TFile("importance_sampling_input.root","UPDATE");
  fout->cd();
  dNdE->Write();
  std::cout << "MantisROOT::WriteSampling -> File Complete. Saved to importance_sampling_input.root" << std::endl;
  fout->Close();
}

void MantisROOT::CheckZeros(TH1D* &hin, int nbins)
{
  if(debug)
  {
    std::cout << "MantisROOT::CheckZeros: " << std::endl;
    hin->Print();
  }

  for(int i=1; i < nbins - 1; ++i)
  {
    if(hin->GetBinContent(i) == 0)
    {
      double current_energy = hin->GetXaxis()->GetBinCenter(i);
      int j = 1;
      while(hin->GetBinContent(i - j) == 0)
      {
        ++j;
      }
      double prior_value = hin->GetBinContent(i - j);
      double prior_energy = hin->GetXaxis()->GetBinCenter(i - j);
      int k = 1;
      while(hin->GetBinContent(i + k) == 0)
      {
        ++k;
      }
      double next_value = hin->GetBinContent(i + k);
      double next_energy = hin->GetXaxis()->GetBinCenter(i + k);

      // linear interpolation
      double expected_value = (prior_value*(next_energy - current_energy) + next_value*(current_energy - prior_energy))/(next_energy - prior_energy);
      // set bin value
      hin->SetBinContent(i, expected_value);
      if(debug)
        std::cout << "Bin: " << i << " , Energy: " << current_energy << " Set to Value: " << expected_value << std::endl;
    } // end of if dNdE_histogram->GetBinContent(i) == 0
  } // end of for loop
}
// END OF PRIVATE FUNCTIONS

// COMMENTED FUNCTIONS

/*
void MantisROOT::Rebin(const char* filename,const char* ObjName,const char* OutObjName)
{
  // Check to make sure file exists
  CheckFile(filename);

  std::string OutFileName = "converted_" + (std::string)filename;
  if(!gSystem->AccessPathName(OutFileName.c_str()))
  {
    std::cout << "Rebinned File Already exists. Continue to rebin?" << std::endl;
    string response;
    std::cin >> response;

    if(!response.compare(0,1,"N"))
      exit(1);
    else
      std::cout << "Continuing rebinning..." << std::endl;

  }

  TFile *f = new TFile(filename);
  f->cd();
  TTree *inObj;
  // Grab the Users TTree
  inObj = (TTree*) f->Get(ObjName);
  inObj->SetEstimate(-1);
  double Emax = inObj->GetMaximum("Energy");
  // Write TTree to histogram
  TH1D *hObj = new TH1D(OutObjName, "Weighted Energy Spectrum",100,0.,Emax);
  std::string tCommand = "Energy>>" + (std::string)OutObjName;
  inObj->Draw(tCommand.c_str(), "Weight","goff");

  TFile *fout;

  if(!gSystem->AccessPathName(OutFileName.c_str()))
    fout = new TFile(OutFileName.c_str(),"update");
  else
    fout = new TFile(OutFileName.c_str(),"recreate");

  fout->cd();
  hObj->Write();
  fout->Close();
} // end of Rebin Functions

void MantisROOT::RebinHisto(std::vector<string> filename, std::vector<string> ObjName,
                 std::vector<string> OutObjName, int nbins, double Emin,
                 double Emax)
{
  if(OutObjName.size() != ObjName.size())
  {
    std::cout << "Error ObjName and OutObjName vector inputs must be same length! Check your inputs!" << std::endl;
    exit(1);
  }
  for(int i=0;i<filename.size();++i)
  {
    for(int j=0;j<ObjName.size();++j)
    {
      Rebin(false, filename[i].c_str(), ObjName[j].c_str(), OutObjName[j].c_str(),
            nbins, Emin, Emax);
    }
  }
}

void MantisROOT::RebinHisto(std::vector<string> filename, std::vector<string> ObjName,
                 std::vector<string> OutObjName, int nbins, double Emin,
                 double Emax, TCut cut1)
{
  if(OutObjName.size() != ObjName.size())
  {
    std::cout << "Error ObjName and OutObjName vector inputs must be same length! Check your inputs!" << std::endl;
    exit(1);
  }
  for(int i=0;i<filename.size();++i)
  {
    for(int j=0;j<ObjName.size();++j)
    {
      Rebin(false, filename[i].c_str(), ObjName[j].c_str(), OutObjName[j].c_str(),
            nbins, Emin, Emax, cut1);
    }
  }
}

void MantisROOT::VarRebin(std::vector<string> filename, std::vector<string> ObjName,
                           std::vector<string> OutObjName, int nbins,
                           double Ecut1, double Ecut2,
                           TCut cut1, double binwidth1, double binwidth2)
{
  if(OutObjName.size() != ObjName.size())
  {
    std::cout << "Error ObjName and OutObjName vector inputs must be same length! Check your inputs!" << std::endl;
    exit(1);
  }
  for(int i=0;i<filename.size();++i)
  {
    for(int j=0;j<ObjName.size();++j)
    {
      Rebin(false, filename[i].c_str(), ObjName[j].c_str(), OutObjName[j].c_str(),
            nbins, Ecut1, Ecut2, cut1, true, binwidth1, binwidth2);
    }
  }
}

TGraph* MantisROOT::CreateTKDE(const char* filename, int nentries=10000)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  f->cd();
  TTree* tBrem;

  f->GetObject("Brem",tBrem);
  tBrem->SetEstimate(nentries);

  double xmin = 0.;
  double xmax = tBrem->GetMaximum("Energy");
  double rho = 1.0;
  int nbins = xmax/5e-6;

  TH1D* h1 = new TH1D("h1","h1",nbins,xmin, xmax);

  tBrem->Draw("Energy","","goff");

  std::vector<double> energyv(nentries);
  Double_t* energies = tBrem->GetVal(0);
  std::cout << "MantisROOT::CreateTKDE -> Energies Grabbed." << std::endl;

  for(int i=0;i<nentries;++i)
  {
    energyv[i] = energies[i];
    h1->Fill(energyv[i]);
  }

  // Scale histogram
  h1->Scale(1./h1->Integral(),"width");
  h1->SetStats(0);
  h1->SetTitle("Bremsstrahlung Data");
  h1->Draw();

  std::cout << "MantisROOT::CreateTKDE -> Creating TKDE..." << std::endl;
  TKDE* kde = new TKDE(nentries, &energyv[0], xmin, xmax, "", rho);

  // Normalize kde
  //kde->ComputeKernelL2Norm();
  std::cout << "MantisROOT::CreateTKDE -> TKDE Created." << std::endl;

  kde->Draw("SAME");
  std::cout << "MantisROOT::CreateTKDE -> TKDE Drawn." << std::endl;

  TLegend* legend = new TLegend();
  legend->SetHeader("Bremsstrahlung Data","C");
  legend->AddEntry(h1,"Bremsstrahlung Histogram");
  legend->AddEntry(kde, "Bremsstrahlung kde");
  legend->Draw();
  std::cout << "MantisROOT::CreateTKDE -> Complete." << std::endl;

  TCanvas* c2 = new TCanvas();
  c2->cd();
  kde->Draw();

  TCanvas* c3 = new TCanvas();
  c3->cd();
  TF1* const hk = kde->GetFunction(nentries);
  TGraph* gBrems = new TGraph(hk);
  gBrems->Draw();

  return gBrems;

} // End of CreateTKDE Function


void MantisROOT::hIntegral(const char* filename, const char* objName)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  if(f == 0)
    exit(0);

  bool confirm = f->cd();
  if(!confirm)
    exit(0);

  TTree *inObj;
  f->GetObject(objName,inObj);
  if(inObj == 0)
    exit(0);

  hIntegral(inObj);
  if(debug)
    std::cout << "MantisROOT::hIntegral -> Deallocating Memory..." << std::endl;
  delete inObj; // avoids potential memory leak
}




void MantisROOT::hIntegral(const char* filename, const char* objName, TCut cut1)
{
  CheckFile(filename);
  TFile *f = new TFile(filename);
  if(f == 0)
    exit(0);

  bool confirm = f->cd();
  if(!confirm)
    exit(0);

  TTree *inObj;
  f->GetObject(objName,inObj);
  if(inObj == 0)
    exit(0);

  hIntegral(inObj, cut1);
  delete inObj; // avoids potential memory leak
} // end of hIntegral Function



void MantisROOT::hIntegral(const char* filename)
{
  // Doing the integral for chopOut, IntObjIn and DetInfo
  CheckFile(filename);
  TFile *f = new TFile(filename);
  if(f == 0)
    exit(0);

  TTree *inChopOut, *inIntObjIn, *inDetInfo;
  f->GetObject("ChopOut",inChopOut);
  f->GetObject("IntObjIn",inIntObjIn);
  f->GetObject("DetInfo",inDetInfo);
  hIntegral(inChopOut);
  hIntegral(inIntObjIn);
  inDetInfo->SetEstimate(-1);
  TH1D *e1 = new TH1D("e1","DetInfo Histogram",100,0.,10e-6);
  inDetInfo->Draw("Energy>>e1","Energy<10e-6","goff");
  std::cout << "DetInfo Integral: " << e1->Integral() << std::endl;
  if(debug)
    std::cout << "MantisROOT::hIntegral -> Deallocating Memory..." << std::endl;
  delete e1;
  f->Close();
} // end of ALL hIntegral Private Functions

double MantisROOT::hIntegral(TH1* h, int returnValue)
{
  int nentries = h->GetEntries();
  TAxis *xaxis = h->GetXaxis();
  double hMean = h->GetMean();
  int nbins = h->GetNbinsX();

  double intSum = 0;
  for(unsigned int i=0;i<nbins;++i)
  {
    double xVal = xaxis->GetBinCenter(i);
    double binVal = h->GetBinContent(i);
    double integralVal = xVal*binVal;
    intSum += integralVal;
  }

  if(returnValue == 1)
    return intSum;
  else if(returnValue == 2)
    return nentries*hMean;
  else if(returnValue == 3)
    return h->Integral();
  else
    return 0;

} // end of hIntegral Private Function 2


double MantisROOT::hIntegral(TTree *inObj, int returnValue)
{
  inObj->SetEstimate(-1);
  double Emax = inObj->GetMaximum("Energy");
  TH1D *e1 = new TH1D("e1",inObj->GetName(),100,0.,Emax);

  inObj->Draw("Energy>>e1","","goff");

  Double_t *energies = inObj->GetVal(0);
  int nentries = inObj->GetEntries();
  double intSum = 0;

  for(unsigned int i=0;i<nentries;++i)
  {
    intSum +=energies[i];
  }

  double theSum = hIntegral(e1, returnValue);
  delete e1;

  if(returnValue == 0)
    return intSum;
  else
    return theSum;

} // end of hIntegral Private Function 3



double MantisROOT::hIntegral(TTree *inObj, int returnValue, TCut cut1, double Emax)
{
  //std::cout << "MantisROOT::hIntegral -> Setting TCut to: " << cut1 << std::endl;
  inObj->SetEstimate(-1);
  TH1D *e1 = new TH1D("e1",inObj->GetName(),100,0.,Emax);

  if(cut1 == "NA")
    inObj->Draw("Energy>>e1","","goff");
  else
    inObj->Draw("Energy>>e1",cut1,"goff");

  Double_t *energies = inObj->GetVal(0);
  int nentries = inObj->GetEntries();
  double intSum = 0;

  for(unsigned int i=0;i<nentries;++i)
  {
    intSum +=energies[i];
  }

  double theSum = hIntegral(e1, returnValue);
  delete e1;

  if(returnValue == 0)
    return intSum;
  else
    return theSum;

} // end of hIntegral Private Function 5




void MantisROOT::hIntegral(TTree* inObj)
{
  inObj->SetEstimate(-1);
  double Emax = inObj->GetMaximum("Energy");
  TH1D *e1 = new TH1D("e1",inObj->GetName(),100,0.,Emax);

  inObj->Draw("Energy>>e1","","goff");

  Double_t *energies = inObj->GetVal(0);
  int nentries = inObj->GetEntries();
  double intSum = 0;

  for(unsigned int i=0;i<nentries;++i)
  {
    intSum +=energies[i];
  }

  std::cout << inObj->GetName() << " TTree Sum: " << intSum << std::endl;

  hIntegral(e1);
  if(debug)
    std::cout << "MantisROOT::hIntegral -> Deallocating Memory." << std::endl;
  delete e1; // avoids potential memory leak
} // end of hIntegral Private Function 6
*/

//
// end of file
