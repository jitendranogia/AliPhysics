#ifndef AliClusterContainer_H
#define AliClusterContainer_H

class TLorentzVector;

class AliVEvent;

#include <AliVCluster.h>

#include "AliEmcalContainer.h"

class AliClusterContainer : public AliEmcalContainer {
 public:
  typedef enum AliVCluster::VCluUserDefEnergy_t VCluUserDefEnergy_t;
  
  AliClusterContainer();
  AliClusterContainer(const char *name); 
  virtual ~AliClusterContainer(){;}

  virtual Bool_t              AcceptObject(Int_t i)              { return AcceptCluster(i);}
  virtual Bool_t              AcceptObject(const TObject* obj)   { return AcceptCluster(dynamic_cast<const AliVCluster*>(obj));}
  virtual Bool_t              AcceptCluster(Int_t i)                      ;
  virtual Bool_t              AcceptCluster(const AliVCluster* vp)        ;
  virtual Bool_t              ApplyClusterCuts(const AliVCluster* clus)   ;
  AliVCluster                *GetAcceptCluster(Int_t i)                   ;
  AliVCluster                *GetAcceptClusterWithLabel(Int_t lab)        ;
  void                        SetClusECut(Double_t cut)                    { SetMinE(cut)     ; }
  void                        SetClusPtCut(Double_t cut)                   { SetMinPt(cut)    ; }
  Double_t                    GetClusPtCut()                         const { return GetMinPt(); }
  AliVCluster                *GetCluster(Int_t i)                    const;
  AliVCluster                *GetClusterWithLabel(Int_t lab)         const;
  AliVCluster                *GetLeadingCluster(const char* opt="")       ;
  Bool_t                      GetMomentum(TLorentzVector &mom, const AliVCluster* vc, Double_t mass);
  Bool_t                      GetMomentum(TLorentzVector &mom, const AliVCluster* clus);
  Bool_t                      GetMomentum(TLorentzVector &mom, Int_t i);
  Bool_t                      GetAcceptMomentum(TLorentzVector &mom, Int_t i);
  Bool_t                      GetNextMomentum(TLorentzVector &mom, Int_t i=-1);
  Bool_t                      GetNextAcceptMomentum(TLorentzVector &mom, Int_t i=-1);
  AliVCluster                *GetNextAcceptCluster(Int_t i=-1)            ;
  AliVCluster                *GetNextCluster(Int_t i=-1)                  ;
  Int_t                       GetNClusters()                         const { return GetNEntries();   }
  Int_t                       GetNAcceptedClusters()                      ;
  void                        SetClassName(const char* clname);
  void                        SetClusTimeCut(Double_t min, Double_t max)   { fClusTimeCutLow  = min ; fClusTimeCutUp = max ; }
  void                        SetMinMCLabel(Int_t s)                       { fMinMCLabel      = s   ; }
  void                        SetMaxMCLabel(Int_t s)                       { fMaxMCLabel      = s   ; }
  void                        SetMCLabelRange(Int_t min, Int_t max)        { SetMinMCLabel(min)     ; SetMaxMCLabel(max)    ; }
  void                        SetExoticCut(Bool_t e)                       { fExoticCut       = e   ; }

  void                        SetClusUserDefEnergyCut(Int_t t, Double_t cut);
  Double_t                    GetClusUserDefEnergyCut(Int_t t) const;

  void                        SetClusNonLinCorrEnergyCut(Double_t cut)                     { SetClusUserDefEnergyCut(AliVCluster::kNonLinCorr, cut); }
  void                        SetClusHadCorrEnergyCut(Double_t cut)                        { SetClusUserDefEnergyCut(AliVCluster::kHadCorr, cut)   ; }
  void                        SetDefaultClusterEnergy(Int_t d)                             { fDefaultClusterEnergy = d                             ; }

  Int_t                       GetDefaultClusterEnergy() const                              { return fDefaultClusterEnergy                          ; }

  const char*                 GetTitle() const;

 protected:
  
  Double_t         fClusTimeCutLow;             // low time cut for clusters
  Double_t         fClusTimeCutUp;              // up time cut for clusters
  Bool_t           fExoticCut;                  // reject clusters marked as "exotic"
  Double_t         fUserDefEnergyCut[AliVCluster::kLastUserDefEnergy+1]; // cut on the energy of the cluster after higher level corrections (see AliVCluster.h)
  Int_t            fDefaultClusterEnergy;       // default cluster energy: -1 for clus->E(); otherwise clus->GetUserDefEnergy(fDefaultClusterEnergy)

 private:
  AliClusterContainer(const AliClusterContainer& obj); // copy constructor
  AliClusterContainer& operator=(const AliClusterContainer& other); // assignment

  ClassDef(AliClusterContainer,5);
};

#endif
