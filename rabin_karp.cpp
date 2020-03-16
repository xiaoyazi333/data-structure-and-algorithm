#include <bits/stdc++.h>

using namespace std;

/**********************************************
    rabin_karp
**********************************************/
#define RADIX   (256)
#define PRIME   (101)

void print_matching_result(const char *pval, int s)
{
    for(int i = 0; i < s; i++)
        printf(" ");
    printf("%s\n",pval);
}

void rabin_karp(const char *t, const char *p)
{
    printf("**********************************************\n");
    printf("%s\n",t);

    int nt = strlen(t), np = strlen(p);
    int pval = 0, tval = 0, h = 1;

    for(int i = 0; i < np-1; i++)
        h = (h*RADIX)%PRIME;

    for(int i = 0; i < np; i++)
    {
        pval = (RADIX*pval+p[i]) % PRIME;
        tval = (RADIX*tval+t[i]) % PRIME;
    }

    for(int i = 0; i <= nt-np; i++)
    {
        if(pval == tval)
        {
            int j;
            for(j = 0; j < np; j++)
                if(t[i+j] != p[j])
                    break;
            if(j == np)
                print_matching_result(p, i);
        }

        if(i == nt-np)    
            return; 

        tval = ((tval-t[i]*h)*RADIX + t[i+np])%PRIME;
        if(tval < 0)
            tval = tval + PRIME;
    }
}

int main()
{
    rabin_karp("ABABABABC", "ABAB");
    rabin_karp("ABABCABAB", "ABAB");
    rabin_karp("AAAAAAA", "AAA");
    rabin_karp("ABABABC", "ABABC");
    rabin_karp("XYXZdeOXZZKWXYZ", "WXYZ");
    rabin_karp("GCAATGCCTATGTGACCTATGTG", "TATGTG");
    rabin_karp("AGATACGATATATAC", "ATATA");
    rabin_karp("CATCGCGGAGAGTATAGCAGAGAG", "GCAGAGAG");
    return 0;
}