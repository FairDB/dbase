#ifndef FAIRDBVALIDITYRECBUILDER_H
#define FAIRDBVALIDITYRECBUILDER_H

#include "FairDb.h"                     // for Version
#include "FairDbValidityRec.h"          // for FairDbValidityRec

#include "Rtypes.h"                     // for Int_t, UInt_t, Bool_t, etc

#include <map>                          // for map
#include <string>                       // for string
#include <vector>                       // for vector

class FairDbProxy;
class ValContext;


class FairDbValidityRecBuilder
{


  public:
    enum { kMAX_AGGREGATE_NO = 1000 };

    FairDbValidityRecBuilder(const FairDbProxy& proxy,
                             const ValContext& vc,
                             const FairDb::Version& task,
                             Int_t selectDbNo = -1,
                             Bool_t findFullTimeWindow = true);
    FairDbValidityRecBuilder(const FairDbProxy& proxy,
                             const std::string& context,
                             const FairDb::Version& task);
    FairDbValidityRecBuilder(const FairDbValidityRec& vr,
                             const std::string tableName);

    virtual ~FairDbValidityRecBuilder();

    std::string GetL2CacheName() const;
    FairDb::Version GetVersion() const { return fVersion; }
    UInt_t GetNumValidityRec() const {
      return fVRecs.size();
    }

    Int_t IndexOfAggno(Int_t aggNo) const;
    Bool_t IsExtendedContext() const {
      return fIsExtendedContext;
    }
    const FairDbValidityRec& GetValidityRec(Int_t rowNo) const;
    const FairDbValidityRec& GetValidityRecFromAggNo(Int_t aggNo) const {
      return this->GetValidityRec(this->IndexOfAggno(aggNo));
    }
    const FairDbValidityRec& GetValidityRecFromSeqNo(UInt_t SeqNo) const;
    Bool_t NonAggregated() const {
      return  ! this->IsExtendedContext()
              && this->GetNumValidityRec() == 1;
    }


  private:

    UInt_t AddNewAgg(const FairDbValidityRec& vrec,Int_t aggNo);
    UInt_t AddNewGap(Int_t aggNo);

    void MakeGapRec(const ValContext& vc,
                    const std::string& tableName,
                    Bool_t findFullTimeWindow = true);


    FairDbValidityRec fGap;
    Bool_t fIsExtendedContext;
    FairDb::Version fVersion;

    std::vector<FairDbValidityRec> fVRecs;
    std::map<Int_t,UInt_t>  fAggNoToIndex;


    ClassDef(FairDbValidityRecBuilder,0) // Builder for eff. ValidityRecs

};


#endif  // FAIRDBVALIDITYRECBUILDER_H
