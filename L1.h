//
// Created by Omer on 4/23/2019.
//

#ifndef WET2_L1_H
#define WET2_L1_H

#include "CacheLine.h"
#include "L2.h"



class L1 {
public:
    L1(unsigned int L1size, unsigned int L1Cyc,unsigned int L1Assoc, unsigned int BSize);
    CacheLine& getLine(int set, long int tag);
    void ReadLine(uint32_t adrs);
    void AddLine(int set, CacheLine& nwLine);


private:
    static unsigned int L1Size_,L1Cyc_,L1Assoc_,BSize_;
    static int NumOfLines=L1Size_/BSize_;
    CacheLine* CacheArray_[NumOfLines];
    int AccessNum_;
    int MissNum_;
    L2& L2_; //TODO: add to c'tor


};


#endif //WET2_L1_H
