#include <iostream>
#include <stdio.h>
#include<string.h>
#include<windows.h>
#include <bits/stdc++.h>

using namespace std;

#define nullptr 0
//#define CHAR_TO_POSITION(a) ((int)a - (int))  Shouldn't this be used ??

class trie{
    public:
                bool endx;
                trie *chr[256]; // Why 256???
                trie()
                {
                    for(int i=0;i<256;i++)
                    {
                        chr[i]=nullptr;
                    }
                    endx=false;
                }
                void insert_ele(char ch[],int n);
                int search_ele(char ch[],int n);
                char* get_ele(char ch[],int n);
};
void trie::insert_ele(char ch[],int n)
{
    trie *t=this;

    for (int i=0;i<n;i++)
    {
        if(t->chr[ch[i]]==nullptr)
        {
            t->chr[ch[i]]=new trie();
        }
        t=t->chr[ch[i]];
    }
    t->endx=true;
}
int trie::search_ele(char ch[],int n)
{
    if (this == nullptr)
		return 0;

    trie *t=this;

    for (int i=0;i<n;i++)
	{
		t=t->chr[ch[i]];
		if ( t== nullptr)
			return 0;
	}
    return int(t->endx);
}

bool is_last_node(trie *t)
{
    return t->endx;
}

char* trie::get_ele(char ch[], int n)
{
    cout<<"In get_ele : "<<ch<<endl;
    trie *t = this;
    int i, cnt=1;
    static char ret[50];
    for(i=0;i<n;i++)
    {
        if(t->chr[ch[i]]!=nullptr)
        {
            cout<<"In trie : "<<ch[i]<<endl;
            t = t->chr[ch[i]];
            cnt++;
        }
        else
        {
            cout<<"Not in trie : "<<ch[i]<<endl;
            if(is_last_node(t))
            {
                cout<<"In last node"<<endl;
                int k;
                for(k=0;k<cnt-1;k++)
                {
                    ret[k] = ch[k];
                }
                ret[k] = '\0';
                cout<<"Ret : "<<ret<<endl;
                if(!search_ele(ret,strlen(ret)))
                {
                    cout<<"Not in Dic!!!"<<endl;
                }
                return ret;
            }
            else
            {
                cout<<"Not in last node "<<endl;
                int k;
                for(k=0;k<cnt-1;k++)
                {
                    ret[k] = ch[k];
                }
                while(!is_last_node(t))
                {
                    char j = 'a';
                    while(j<='z')
                    {
                        if(t->chr[j]!=nullptr)
                        {
                            ret[k] = j;
                            k++;
                            t = t->chr[j];
                        }
                        else
                        {
                            j = (int)j +1;
                        }
                    }
                }
                ret[k] = '\0';
                cout<<"ret : "<<ret<<endl;
                return ret;
            }
        }

    }
    if(cnt==n+1) // If the given string isn't a word but a part of an actual word
    {
        cout<<"Sub-string : "<<ch<<endl;
        int k = n;
        strcpy(ret,ch);
        while(! is_last_node(t))
        {
            char j='a';
            while(j<='z')
            {
                if(t->chr[j]!=nullptr)
                {
                    ret[k] = j;
                    k++;
                    t = t->chr[j];
                    break;
                }
                else
                {
                    j = (int)j + 1;
                }
            }
        }
        ret[k] = '\0';
        cout<<"Ret in prefix : "<<ret<<endl;
        return ret;
    }
}

struct words {
                char x[50];
};

int main()
{
    words w;
    trie t;
    char ch[50];
    cout<<"Loading..."<<endl;
    fstream q;
    string input_file;
    input_file = "english3.txt";
    q.open(input_file.c_str());
    unsigned int j;
    while(q>>ch)
    {
        for(j=0;j<strlen(ch);j++)
        {
            ch[j] = tolower(ch[j]);
        }
        ch[0] -= 32;
        ch[strlen(ch)]='\0';
        t.insert_ele(ch,strlen(ch));
    }
    system("cls");
    cout<<"Enter a word : ";
    cin>>ch;
    for(j=0;j<strlen(ch);j++)
    {
        ch[j] = tolower(ch[j]);
    }
    ch[strlen(ch)]='\0';
    ch[0] -= 32;
    cout<<t.search_ele(ch,strlen(ch))<<endl;
    fstream p;
    string filename;
    filename = "text.txt";
    p.open(filename.c_str());
    ofstream outfile;
    outfile.open("out.txt");
    while(p>>ch)
    {
        for(j=0;j<strlen(ch);j++)
        {
            ch[j] = tolower(ch[j]);
        }
        ch[strlen(ch)]='\0';
        ch[0] -= 32;
        cout<<"input : "<<ch<<endl;
        if(!bool(t.search_ele(ch,strlen(ch))))
        {
            cout<<"Not_in_dic : "<<ch<<endl;
            char *st = t.get_ele(ch,strlen(ch));
            cout<<"Output : "<<st<<endl;
            strcpy(ch,st);
        }
        ch[0] +=32;
        outfile<<ch<<" ";
    }
    q.close();
    p.close();
    outfile.close();
    return 0;
}
