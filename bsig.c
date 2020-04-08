// bsig.c ... functions on Tuple Signatures (bsig's)
// part of SIMC signature files
// Written by John Shepherd, March 2020

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "bsig.h"
#include "psig.h"

void findPagesUsingBitSlices(Query q)
{
	assert(q != NULL);

	//TODO
//    Qsig = makePageSig(Query)
//    Pages = AllOneBits
//    for each i in 0..pm-1 {
//        if (Psig bit[i] is 1) {
//            Slice = get i'th bit slice from bsigFile
//            zero bits in Pages which are zero in Slice
//        }
//    }

    Reln r = q->rel;
    Tuple t = q->qstring;

    Bits Qsig = makePageSig(r, t);
    setAllBits(q->pages);
    int visited = 0;
    int former = -1;

    for(int i = 0; i < psigBits(r); i++)
    {
        if(bitIsSet(Qsig, i))
        {
            q->nsigs++;
            PageID pid = i / maxBsigsPP(r);
            if(former!= pid) visited++; former = pid;

            int pos = i % maxBsigsPP(r);
            Page p = getPage(r->bsigf, pid);
            Bits bsig = newBits(bsigBits(r));
            getBits(p,pos,bsig);
            for(int j = 0; j < nPages(r);j++)
                if(!bitIsSet(bsig,j))
                    unsetBit(q->pages, j);
        }
    }
    q->nsigpages = visited;
}

