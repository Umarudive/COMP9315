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
            if(former!= pid) {visited++; former = pid;}

            int pos = i % maxBsigsPP(r);
            Page p = getPage(r->bsigf, pid);
            Bits bsig = newBits(bsigBits(r));
            getBits(p,pos,bsig);
            andBits(q->pages, bsig);
            freeBits(bsig);
        }
    }
    q->nsigpages = visited;
}

