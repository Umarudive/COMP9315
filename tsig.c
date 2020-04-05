// tsig.c ... functions on Tuple Signatures (tsig's)
// part of SIMC signature files
// Written by John Shepherd, March 2020

#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "tsig.h"
#include "reln.h"
#include "hash.h"
#include "bits.h"

Bits codeword(char *attr, int m, int k)
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

// make a tuple signature

Bits makeTupleSig(Reln r, Tuple t)
{
	assert(r != NULL && t != NULL);
	//TODO
//    Tsig = AllZeroBits
//    for each attribute A in tuple T {
//            CW = codeword for A
//            Tsig = Tsig OR CW
//    }

    Bits tsig = newBits(tsigBits(r));
    char **vals = tupleVals(r, t);

    for(int i = 0; i < nAttrs(r); i++)
    {
        if (vals[i][0] == '?') continue;
        Bits cw = codeword(vals[i], tsigBits(r),codeBits(r));
        orBits(tsig,cw);
    }
    return tsig;
}

// find "matching" pages using tuple signatures

void findPagesUsingTupSigs(Query q)
{
	assert(q != NULL);
	//TODO
//    QuerySig = makeTupleSig(Query)
//    Pages = AllZeroBits
//    foreach Tsig in tsigFile {
//            if (Tsig matches QuerySig) {
//                PID = data page for tuple corresponding to Tsig
//                include PID in Pages
//            }
//    }

    Reln r = q->rel;
    Tuple t = q->qstring;

    Bits query_sig = makeTupleSig(r,t);
    unsetAllBits(q->pages);
    File f = tsigFile(r);
    Bits tsig = newBits(tsigBits(r));

    int pid = 0;

    for(int i = 0; i < nTsigPages(r); i++)
    {
        q->nsigpages++;
        Page p = getPage(f, i);
        for(int pos = 0; pos < pageNitems(p); pos++)
        {
            pid++;
            getBits(p, pos, tsig);
            if(isSubset(query_sig, tsig))
                setBit(q->pages, pid/maxTupsPP(r));
            q->nsigs++;
        }
    }

	// The printf below is primarily for debugging
	// Remove it before submitting this function
//	printf("Matched Pages:"); showBits(q->pages); putchar('\n');
}
