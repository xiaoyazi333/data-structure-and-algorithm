#include <bits/stdc++.h>

using namespace std;

/**********************************************
    horspool
**********************************************/
#define ALPHABET (256)

void print_matching_result(const char *p, int s)
{
    for(int i = 0; i < s; i++)
        printf(" ");
    printf("%s\n",p);
}

void calc_skip(int skip[], const char *p)
{
    int np = strlen(p);
    for(int i = 0; i < ALPHABET; i++)
        skip[i] = np;               
    for(int i = 0; i < np-1; i++)
        skip[p[i]] = np-i-1;
}

void horspool(const char *t, const char *p)
{
    printf("**********************************************\n");
    printf("%s\n",t);

    int s = 0, nt = strlen(t), np = strlen(p), skip[ALPHABET];

    calc_skip(skip, p);
    while(s <= nt-np)
    {
        int j = np-1;
        while(j >= 0 && p[j] == t[s+j])
            j--;
        if(j < 0)
            print_matching_result(p, s);
        s = s+skip[t[s+np-1]];
    }
}

int main()
{
    horspool("ABABABABC", "ABAB");
    horspool("ABABCABAB", "ABAB");
    horspool("AAAAAAA", "AAA");
    horspool("ABABABC", "ABABC");
    horspool("XYXZdeOXZZKWXYZ", "WXYZ");
    horspool("GCAATGCCTATGTGACCTATGTG", "TATGTG");
    horspool("AGATACGATATATAC", "ATATA");
    horspool("CATCGCGGAGAGTATAGCAGAGAG", "GCAGAGAG");
    return 0;
}