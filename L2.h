//
// Created by Omer on 4/23/2019.
//

#ifndef WET2_L2_H
#define WET2_L2_H


#include "CacheLine.h"



class L2 {
public:
    L2(unsigned int L2size, unsigned int L2Cyc,unsigned int L2Assoc, unsigned int BSize);
    CacheLine& getLine(int set, long int tag);
    void AddLine(int set,CacheLine& nwLine);
    void ReadLine();


private:
    static unsigned int L2Size_,L2Cyc_,L2Assoc_,BSize_;
    static int NumOfLines=L1Size_/BSize_;
    CacheLine* CacheArray_[NumOfLines];
    int AccessNum_;
    int MissNum_;
    //TODO: add victim cache


};

#endif //WET2_L2_H
