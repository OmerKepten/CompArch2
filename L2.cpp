//
// Created by Omer on 4/23/2019.
//

#include "L2.h"

L2::L2(unsigned int L2size, unsigned int L2Cyc,unsigned int L2Assoc, unsigned int BSize){
    L2Size_=L2size;
    L2Cyc_=L2Cyc;
    L2Assoc_=L2Assoc;
    BSize_=BSize;
    AccessNum_=0;
    MissNum_=0;

}

void L2::ReadLine() {
 //TODO: complete
}

CacheLine& L2::getLine(int set, long int tag) {
    CacheLine* currLine;
    for (int i=0;i<=L2Assoc_;i++){
        currLine=CacheArray_[i*set];
        if ((currLine->isValid()) && (tag==(currLine->getTag()))){
            currLine->UpdateTime(); //accessed line- update time
            return *currLine;
        }
    }
    return NULL;
}

void L2::AddLine(int set, CacheLine& nwLine) {
    CacheLine* currLine;
    for (int i=0;i<=L2Assoc_;i++){
        currLine=CacheArray_[i*set];
        if (!(currLine->isValid())){ //line not valid- can delete instantly
            currLine=&nwLine;
            return;
        }
    }

    //could not find an available line- need to evict to Victim:
    //TODO: complete
}