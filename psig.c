// psig.c ... functions on page signatures (psig's)
// part of SIMC signature files
// Written by John Shepherd, March 2020

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "psig.h"
#include "hash.h"

Bits pcodeword(char *attr, int m, int k)
{
    int hash_seed = hash_any(attr, strlen(attr));
    Count nbits = 0;
    Bits cw = newBits(m);
    srandom(hash_seed);

    while(nbits < k)
    {
        int i = random() % m;   // [0, m-1]
        if(!bitIsSet(cw,i))
        {
            setBit(cw,i);
            nbits++;
        }
    }
    return cw;
}

Bits makePageSig(Reln r, Tuple t)
{
	assert(r != NULL && t != NULL);
	//TODO
    Bits psig = newBits(psigBits(r));
    char **vals = tupleVals(r, t);

    for(int i = 0; i < nAttrs(r); i++)
    {
        if (vals[i][0] == '?') continue;
        Bits cw = pcodeword(vals[i], psigBits(r),codeBits(r));
        orBits(psig,cw);
        freeBits(cw);
    }
    freeVals(vals, nAttrs(r));
    return psig;
}

void findPagesUsingPageSigs(Query q)
{
	assert(q != NULL);
	//TODO
    Reln r = q->rel;
    Tuple t = q->qstring;
    Bits query_sig = makePageSig(r,t);
    unsetAllBits(q->pages);
    Bits psig = newBits(psigBits(r));
    int pid = -1;
    for(int i = 0; i < nPsigPages(r); i++)
    {
        q->nsigpages++;
        Page p = getPage(psigFile(r), i);
        for(int pos = 0; pos < pageNitems(p); pos++)
        {
            ++pid;
            getBits(p, pos, psig);
            if(isSubset(query_sig, psig))
                setBit(q->pages, pid);
            q->nsigs++;
        }
    }
    freeBits(psig);
}





