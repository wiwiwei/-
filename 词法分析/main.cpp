
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

int syn;//存放单词的类型
int p,m;
char ch;
int sum;//用来保存数字的值
char program[1010],token[10];
char *rwtab[9]={"Const","Var","if","then","else","while","do","begin","end"};

bool isDigital(char ch)
{
    if(ch<='9'&&ch>='0')
        return true;
    return false;
}

bool isAlpha(char ch)
{
    if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
        return true;
    return false;
}

void Scanner()
{
    int num=0;
    for(m=0;m<10;m++)
    {
        token[m]=NULL;
    }
    m=0;
    ch=program[p++];
    while(ch==' '||ch=='\n'||ch=='\t')
    {
        ch=program[p++];
    }
    if(isAlpha(ch)){
        do{
            token[m++]=ch;
            ch=program[p++];
        }while(isAlpha(ch)||isDigital(ch));
        p--;
        syn=10;
        token[m++]='\0';
        for(int n=0;n<=8;n++)
        {
            if(strcmp(token,rwtab[n])==0)
            {
                syn=n+1;
                break;
            }
        }
        return;
    }
    else if(isDigital(ch))
    {
        sum=0;
        while(isDigital(ch))
        {
            sum=sum*10+ch-'0';
            ch=program[p++];
        }
        p--;
        syn=11;
        if(isAlpha(ch))
            syn=-1;
        return;
    }
    else
    {
        token[0]=ch;
        switch(ch)
        {
            case '<':ch=program[p++];
                    if(ch=='>')
                    {
                        syn=22;
                        token[1]=ch;
                    }
                    else if(ch=='=')
                        {
                            syn=18;
                            token[1]=ch;
                        }
                    else{
                        syn=19;
                        p--;
                    }
                    break;
            case '>':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=21;
                        token[1]=ch;
                    }
                    else{
                        syn=20;
                        p--;
                    }
                    break;
            case '=':ch=program[p++];
                    if(ch=='=')
                    {
                        syn=17;
                        token[1]=ch;
                    }
                    else{
                        syn=17;
                        p--;
                    }
                    break;
            case '+':syn=12;break;
            case '-':syn=13;break;
            case '*':syn=14;break;
            case '/':syn=15;break;
            case ';':syn=23;break;
            case '(':syn=24;break;
            case ')':syn=25;break;
            case ',':syn=26;break;
            case '#':syn=0;break;
            default:syn=-1;break;
        }
        return;
    }
}

void Print()
{
    if(syn==11)
        printf("<%d,%d>\n",syn,sum);
    else
        printf("<%d,%s>\n",syn,token);
}


int main()
{
    printf("输入词法分析串以#作为结束\n");
    do
    {
        ch=getchar();
        program[p++]=ch;
    }while(ch!='#');
    p=0;
    //printf("%s\n",program);
    do{
        Scanner();
        //cout<<syn<<endl;
        switch(syn)
        {
            case -1:printf("wrong\n",token);break;
            default:Print();break;
        }
    }while(syn!=0&&syn!=-1);
    if(syn==0)printf("success");
    return 0;
}
