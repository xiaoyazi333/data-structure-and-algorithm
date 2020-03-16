#include <bits/stdc++.h>

using namespace std;

#define DEBUG (1)

#define Len(x)              sizeof(x)/sizeof(x[0]) 

/**********************************************
    aho corasick
**********************************************/
#define ALPHABET   (26)

int cnt = 0;                // debug

typedef struct _NODE
{
    int name;               // debug
    vector<int> exist;
    _NODE *fail;
    _NODE *child[ALPHABET];
    _NODE()
    {
        name = 0;           // debug
        fail = NULL;
        memset(child, NULL, ALPHABET*sizeof(_NODE *));
    }
}NODE;

/**********************************************
    "he" "she" "hers" "his" 
    ahishers
     his
       she
        he
        hers
**********************************************/
void print_matching_result(const char *T, int start, int len)
{
    for(int i = 0; i < start; i++)
        printf(" ");
    for(int i = 0; i < len; i++)
        printf("%c",T[start+i]);
    printf("\n");
}

/**********************************************
    用于debug确认构造完成的状态机的[fail指针]和[exist信息]
    bfs遍历一遍trie,按顺序给节点命名,同时输出fail指向信息
**********************************************/
void print_automaton_info(NODE *tmp)
{
    printf("---------------------info----------------------\n");
    queue<NODE *> q;
    q.push(tmp);
    while(!q.empty())
    {
        NODE *tmp = q.front(); q.pop();
        tmp->name = cnt++;
        if(tmp->fail)
            printf("%d --fail--> %d, has %d word\n", tmp->name, tmp->fail->name, tmp->exist.size());
        for(int i = 0; i < ALPHABET; i++)
            if(tmp->child[i])
                q.push(tmp->child[i]);
    }
    printf("---------------------end----------------------\n");
}

void trie_insert(NODE *root, const char *word)
{
    NODE *tmp = root;

    for(int i = 0; i < strlen(word); i++)
    {
        int c = word[i]-'a';
        if(NULL == tmp->child[c])
            tmp->child[c] = new NODE();
        tmp = tmp->child[c];
    }
    tmp->exist.push_back(strlen(word));
}

void ac_build(NODE *root, const char *P[], int n)
{
    for(int i = 0; i < n; i++)
        trie_insert(root, P[i]);
    
    queue<NODE *> q;
    for(int i = 0; i < ALPHABET; i++)
    {
        if(root->child[i])
        {
            root->child[i]->fail = root;
            q.push(root->child[i]);
        }
    }

    while(!q.empty())
    {
        NODE *x = q.front(); q.pop();
        for(int i = 0; i < ALPHABET; i++)
        {
            if(x->child[i])
            {
                NODE *y = x->child[i], *fafail = x->fail;
                /*
                    x--fail-→fafail         x--fail-→fafail
                      ↘ⁱ             ==>     ↘ⁱ        ↘ⁱ      
                        y                      y--fail--→★
                */
                while(fafail && NULL == fafail->child[i])
                    fafail = fafail->fail;
                if(NULL == fafail)
                    y->fail = root;
                else
                    y->fail = fafail->child[i];

                if(y->fail->exist.size())
                    for(int j = 0; j < y->fail->exist.size(); j++)
                        y->exist.push_back(y->fail->exist[j]);
                q.push(y);
            }
        }
    }
}

void ac_query(NODE *root, const char *T)
{
    NODE *tmp = root;
    for(int i = 0; i < strlen(T); i++)
    {
        int c = T[i]-'a';
        while(NULL == tmp->child[c] && tmp->fail)
            tmp = tmp->fail;
        if(tmp->child[c])
            tmp = tmp->child[c];
        else
            continue;
        if(tmp->exist.size())
        {
            for(int j = 0; j < tmp->exist.size(); j++)
            {
                int len = tmp->exist[j];
                print_matching_result(T, i-len+1, len);
            }
        }
    }
}

void aho_corasick(const char *P[], int n, const char *T)
{
    printf("**********************************************\n");
    for(int i = 0; i < n; i++)
        printf("\"%s\" ", P[i]);
    printf("\n%s\n", T);

    NODE *root = new NODE();
    ac_build(root, P, n);
    ac_query(root, T);

    print_automaton_info(root);         // debug
}

int main()
{
    const char *P[] = {"he", "she", "hers", "his", "is"}; 
    const char *T = "ahishersheishiser";

    aho_corasick(P, Len(P), T);

    return 0;
}
