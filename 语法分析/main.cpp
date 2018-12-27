#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
void Print();
void Scanner();
bool Statement(int d);
bool Condition(int d);
bool While_Statement(int d);
bool Expression(int d);
bool Item_expression(int d);
bool Factor(int d);
bool Conditional_statements(int d);
bool Assignment_statement(int d);
bool Compound_statements(int d);
int syn;//��ŵ��ʵ�����
int p;
char ch;
int sum;//�����������ֵ�ֵ
char program[1010],token[10];
char *rwtab[9]={"begin","if","then", "else","while","do","Const","Var","end"};
int m;
void out(int len)
{
    for(int i=0;i<len;i++)
        cout<<"    ";
}
bool isDigital(char ch)
{
    if(ch<='9'&&ch>='0') return true;
    else return false;
}
bool isAlpha(char ch)
{
    if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') return true;
    else return false;
}
void Scanner()
{
    int num=0;
    for(m=0;m<10;m++) token[m]='\0';
    m=0;
    ch=program[p++];
    while(ch==' '||ch=='\n'||ch=='\t') ch=program[p++];
    if(isAlpha(ch))
    {
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
                    else
                    {
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
                    else
                    {
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
                    else
                    {
                        syn=16;
                        p--;
                    }
                    break;
            case '+':syn=12;
                    break;
            case '-':syn=13;
                    break;
            case '*':syn=14;
                    break;
            case '/':syn=15;
                    break;
            case ';':syn=23;
                    break;
            case '(':syn=24;
                    break;
            case ')':syn=25;
                    break;
            case ',':syn=26;
                    break;
            case '#':syn=0;
                    break;
            default:syn=-1;
                    break;
        }
        return;
    }
}
bool Constan_Defined(int d)
{
    if(syn==10)
    {
        out(d);
        cout<<"��������  "<<token<<endl;
        Scanner();
        if(syn==16)
        {
            out(d);
            cout<<"����  "<<token<<endl;
            Scanner();
            if(syn==11)
            {
                out(d);
                cout<<"�޷�������  "<<sum<<endl;
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}
bool Constan_Description(int d)
{
    Scanner();
    if(syn==7)
    {
        out(d);
        cout<<"����˵��  "<<token<<endl;
        Scanner();
        d++;
        while(Constan_Defined(d))
        {
            Scanner();
            if(syn==23)
            {
                out(d);
                cout<<"�ֺ�  "<<token<<endl;
                return true;
            }
            else if(syn==26)
            {
                out(d);
                cout<<"����"<<token<<endl;
                Scanner();
                continue;
            }
            cout<<"ERROR ����˵������"<<endl;
        }
    }
    return false;
}
bool Variable_Defined(int d)
{
    if(syn==10)
    {
        out(d);
        cout<<"��������  "<<token<<endl;
        return true;
    }
    return false;
}
bool Variable_Description(int d)
{
    if(syn==10||syn==2||syn==5||syn==1||syn==0)
    {
        return true;
    }
    Scanner();
    if(syn==8)
    {
        out(d);
        cout<<"����˵��  "<<token<<endl;
        Scanner();
        d++;
        while(Variable_Defined(d))
        {
            Scanner();
            if(syn==23)
            {
                out(d);
                cout<<"�ֺ�  "<<token<<endl;
                return true;
            }
            else if(syn==26)
            {
                out(d);
                cout<<"����"<<token<<endl;
                Scanner();
                continue;
            }
        }
    }
}
bool Condition(int d)
{
    Expression(++d);
    if(syn==17||syn==18||syn==19||syn==20||syn==21 ||syn==22)
    {
        out(d);
        cout<<"��ϵ�����"<<token<<endl;
        Scanner();
    }
    else
    {
        cout<<"��ϵ���������"<<endl;
        return false;
    }
    Expression(++d);
}
bool Expression(int d)
{
    out(d);
    cout<<"���ʽ"<<endl; //Scanner();
    d++;
    do{
        if(syn==12||syn==13)
        {
            out(d);
            cout<<"�ӷ������"<<token<<endl;
            Scanner();
            Item_expression(d);
        }
        else
        {
            Item_expression(d);
        }
    }while(syn==12||syn==13);
    d--;
    return true;
}
bool Item_expression(int d)
{
    out(d);
    cout<<"��"<<endl;
    d++;
    while(Factor(d))
    {
        //Scanner();
        if(syn==14||syn==15)
        {
            out(d);
            cout<<"�˷������"<<token<<endl;
            Scanner();
        }
        else
        {
            return true;
        }
    }
    return false;
}
bool Factor(int d)
{
    out(d);
    cout<<"����"<<endl;
    //Scanner();
    if(syn==10)
    {
        out(d);
        cout<<"��ʶ��"<<token<<endl;
        Scanner();//����
        return true;
    }
    else if(syn==11)
    {
        out(d);
        cout<<"�޷�������"<<sum<<endl;
        Scanner();
        return true;
    }
    else if(syn==24)
    {
        out(d);
        cout<<"������"<<token<<endl;
        Scanner();
        Expression(++d);
        if(syn==25)
        {
            out(d);
            cout<<"������"<<token<<endl;
            Scanner();
            return true;
        }
        else
        {
            cout<<"ERROR  û�У�"<<endl;
            return false;
        }
    }
    else
    {
        cout<<"ERROR  û�������Ż�ȱ����"<<endl;
        return false;
    }
    return false;
}
bool Assignment_statement(int d)
{
    out(d);
    cout<<"��ֵ���  "<<endl;
    out(d);
    cout<<"��ʶ��  "<<token<<endl;
    Scanner();
    if(syn==16)
    {
        out(d);
        cout<<"��ֵ���  ="<<endl;
        Scanner();
        Expression(++d);
        return true;
    }
    else
    {
        cout<<"ERROR  û��="<<endl;
    }
}
bool Compound_statements(int d)
{
    out(d);
    cout<<"�������"<<token<<endl;
    Scanner();
    while(Statement(d))
    {
        if(syn==23)
        {
            d++;
            out(d);
            cout<<"��������еķָ��"<<token<<endl;
            d--;
            Scanner();
            if(syn==9)
            {
                //out(d);
                //cout<<"�������"<<token<<endl;
                break;
            }
        }
    }
    if(syn==9)
    {
        out(d);
        cout<<"�������"<<token<<endl;
        Scanner();
        return true;
    }
    else
    {
        cout<<"ERROR  �������ȱ��"<<endl;
        return false;
    }
    if(syn==0)
    {
        out(d);
        cout<<"�������"<<token<<endl;
    }
}
bool Conditional_statements(int d)
{
    if(syn==2)
    {
        out(d);
        cout<<"�������if"<<endl;
        Scanner();
        Condition(d);
        if(syn==3)
        {
            out(d);
            cout<<"then"<<endl;
            Scanner();
            Statement(d);
            if(syn==4)
            {
                out(d);
                cout<<"�������else"<<endl;
                Scanner();
                Statement(d);
            }
            else return true;
        }
        else
        {
            cout<<"ERROR  ���������ȱ�� then"<<endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool While_Statement(int d)
{
    out(d);
    cout<<"ѭ�����"<<token<<endl;
    Scanner();
    Condition(++d);
    if(syn==6)
    {
        out(d);
        cout<<"whileѭ����do"<<endl;
        Scanner();
        Statement(++d);
        return true;
    }
    else return false;
}
bool Statement(int d)
{
    if(syn==10)
    {
        Assignment_statement(++d);
        return true;
    }
    else if(syn==5)
    {
        While_Statement(++d);
        return true;
    }
    else if(syn==1)
    {
        Compound_statements(++d);
        return true;
    }
    else if(syn==2)
    {
        Conditional_statements(++d);
        return true;
    }
    else return false;
}
int main()
{
    printf("�����﷨��������#��Ϊ����\n");
    do
    {
        ch=getchar();
        program[p++]=ch;
    }while(ch!='#');
    p=0;
    cout<<"����ʼ"<<endl;
    Constan_Description(1);
    Variable_Description(1);
    Scanner();
    do{
        Statement(0);
    }while(syn!=0);
    cout<<"�������"<<endl;
    return 0;
}
