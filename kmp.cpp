#include <bits/stdc++.h>

using namespace std;

#define SIZE (100)
#define PRINT_ARRAY(a,n) do {for(int i = 0; i < n; i++) cout<<a[i]<<"|"; cout<<endl;} while(0)

/**********************************************
    KMP
**********************************************/
void print_matching_result(const char *p, int s)
{
    for(int i = 0; i < s; i++)
        printf(" ");
    printf("%s\n",p);
}

/**********************************************
    d[i]:p[0]~p[i]共计i+1个字符的最大公共前后缀
**********************************************/
void calc_lps(int d[], const char *p)
{
    int i = 1, j = 0, np = strlen(p);
    bzero(d, sizeof(int)*np);
    while(i < np)
    {
        if(p[j] == p[i])
            d[i++] = ++j;
        else
        {
            if(j > 0)   j = d[j-1];
            else        i++;
        }
    }
}

void kmp(const char *t, const char *p)
{
    printf("**********************************************\n");
    printf("%s\n",t);

    int d[SIZE];
    calc_lps(d, p);
    int i = 0, j = 0, nt = strlen(t), np = strlen(p);
    while(i < nt)
    {
        if(p[j] == t[i])
        {
            i++,j++;
            if(j == np)
            {
                print_matching_result(p, i-j);
                j = d[np-1];
            }
        }
        else
        {
            if(j > 0)   j = d[j-1];
            else        i++;
        }
    }
}

int main()
{
    kmp("ABABABABC", "ABAB");
    kmp("ABABCABAB", "ABAB");
    kmp("AAAAAAA", "AAA");
    kmp("ABABABC", "ABABC");
    kmp("XYXZdeOXZZKWXYZ", "WXYZ");
    kmp("GCAATGCCTATGTGACCTATGTG", "TATGTG");
    kmp("AGATACGATATATAC", "ATATA");
    kmp("CATCGCGGAGAGTATAGCAGAGAG", "GCAGAGAG");
    return 0;
}
