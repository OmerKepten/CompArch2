//
// Created by Omer on 4/23/2019.
//

#include <stdint-gcc.h>
#include "L1.h"

L1::L1(unsigned int L1size, unsigned int L1Cyc,unsigned int L1Assoc, unsigned int BSize){
    L1Size_=L1size;
    L1Cyc_=L1Cyc;
    L1Assoc_=L1Assoc;
    BSize_=BSize;
    AccessNum_=0;
    MissNum_=0;

}

//ReadLine: searches for line according to address, if not found seeks from L2
void L1::ReadLine(uint32_t adrs) {
    int set = (adrs >> 5)% 4; //get bits [5,6]
    long int tag = (adrs >> 7);
    CacheLine& CurrLine = getLine(set,tag);
    if (CurrLine==NULL){ //there was a miss in L1 cache
        MissNum_++;
        CurrLine= L2_.getLine(set,tag);
        AddLine(set,CurrLine);
    }
    AccessNum_++;
}

//getLine: searches for the given tag in the current cache
CacheLine& L1::getLine(int set, long int tag) {
    CacheLine* currLine;
    for (int i=0;i<=L1Assoc_;i++){
        currLine=CacheArray_[i*set];
        if ((currLine->isValid()) && (tag==(currLine->getTag()))){
            currLine->UpdateTime();//accessed line- update time
            return *currLine;
        }
    }

    return NULL;
}

//adds a new line to the cache. If needed, evicts from cache according to LRU policy
void L1::AddLine(int set, CacheLine& nwLine) {
    //note: since cache is inclusive, new lines in L1 are always existing ones- no need to create object
    CacheLine* currLine;
    for (int i=0;i<=L1Assoc_;i++){
        currLine=&CacheArray_[i*set];
        if (!(currLine->isValid())){ //line not valid- can delete instantly
            currLine=&nwLine;
            return;
        }
    }

    //could not find an available line- need to evict to L2:

    //first, go over relevant set+ways and choose LRU:
    CacheLine* LatestLine = &CacheArray_[set];//get from first way
    double timeDiff;
    for(int i=1;i<=L1Assoc_;i++){
        currLine=&CacheArray_[set*i];
        timeDiff= difftime(LatestLine->getTime(),currLine->getTime());
        if (timeDiff<0){
            LatestLine=currLine;
        }
    }

    //TODO: question: before we evict, do we need to update the evicted line's time in L2 to its time here?
    // TODO: cont: if not then its time in L2 would be the last time asked for by L1, even if it was accessed again here

    //write new line to evicted' place
    LatestLine=&nwLine;
}
