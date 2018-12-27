#include <bits/stdc++.h>
using namespace std;

#define MAX 100
int m=0,sum=0;//sum用于计算运算符的个数

char JG='W';
char str[MAX];//用于存输入表达式
int  token=0;//左括号的标志

/***********用于更改计算后数组中的值*************/
void change(int e)
{

	int f=e+2;
	char ch=str[f];
	if(ch>='A'&&ch<='Z')
	{
		for (int l=0; l<m+10; l++) {
			if(str[l]==ch)
				str[l]=JG;
		}
	}

	if(str[e]>='A'&&str[e]<='Z')
	{
		for(int i=0; i<m; i++)
		{
			if(str[i]==str[e])
				str[i]=JG;
		}
	}

}



void chengchuchuli(int i,int m)
{

	i++;
	for( ;i<=m-1;i++)//处理乘除运算
	{
		if(str[i]=='*'||str[i]=='/')
		{

			cout<<"("<<str[i]<<" "<<str[i-1]<<"  "<<str[i+1]<<"  "<<JG<<")"<<endl;
			change(i-1);
			str[i-1]=str[i]=str[i+1]=JG;
			sum--;
			JG++;
		}
	}
}

void jiajianchuli(int j,int m)
{
	j++;
	for( ;j<=m-1;j++)////处理加减运算
	{
		if(str[j]=='+'||str[j]=='-')
		{
			cout<<"("<<str[j]<<" "<<str[j-1]<<"  "<<str[j+1]<<"  "<<JG<<")"<<endl;
			change(j-1);
			str[j-1]=str[j]=str[j+1]=JG;
			sum--;
			JG++;
		}

	}
}

void scan(FILE *fin)
{
	//int p[MAX];
	char st[MAX];
	char ch='a';
	//int c=-1,q=0;
	while(ch!=EOF)
	{
		ch=getc(fin);

		while(ch==' '||ch=='\t') ch=getc(fin);

		str[m++]=ch;

		if(ch=='='||ch=='+'||ch=='-'||ch=='*'||ch=='/') sum++;


	}


	int mm = 0;
	for (int i = 0; i < m - 1; ++i){
		if (isdigit(str[i]) && isalpha(str[i + 1])){
			st[mm++] = str[i];
			st[mm++] = '*';
		}

		else{
			st[mm++] = str[i];
		}
	}

	m = mm;
	for (int i = 0; i < m; ++i) str[i] = st[i];
}

void sanyuanshi()
{
    int p[MAX];
    int c=0,q=0;
    int iii=0;
    for(int ii=0;ii<=m-1;ii++){
            if(str[ii]=='\n'){
    for(int w=iii;w<=ii-1;w++){
        if(str[w]=='(')
		{
			p[c]=w;

		}
		else if(str[w]==')')
		{
			q=w;
			chengchuchuli(p[c],q);//从左括号处理到右括号
			jiajianchuli(p[c],q);
			JG--;
			str[p[c]]=str[w]=JG;
			JG++;

		}
	}

	for(int i=iii;i<=ii-1;i++)//处理乘除运算
	{
		if(str[i]=='*'||str[i]=='/')
		{

			cout<<"("<<str[i]<<"  "<<str[i-1]<<"  "<<str[i+1]<<"  "<<JG<<")"<<endl;
			change(i-1);
			str[i-1]=str[i]=str[i+1]=JG;
			sum--;
			JG++;
		}

	}

	for(int j=iii;j<=ii-1;j++)//处理加减运算
	{
		if(str[j]=='+'||str[j]=='-')
		{

			cout<<"("<<str[j]<<"  "<<str[j-1]<<"  "<<str[j+1]<<"  "<<JG<<")"<<endl;
			change(j-1);
			str[j-1]=str[j]=str[j+1]=JG;
			sum--;
			JG++;
		}

	}

	for(int k=iii;k<=ii-1;k++)//处理赋值
	{
		if(str[k]=='=')
		{

			--JG;
			cout<<"("<<str[k]<<"  "<<str[k+1]<<"  "<<"  "<<" "<<str[k-1]<<")"<<endl;
			sum--;
			change(k+1);
			str[k-1]=JG;
		}
	}
    iii=ii;
    }
    }
}


int main(){
	char in[MAX];
	FILE *fin;
	fin=fopen("examplse2.txt","r");
	cout<<"四元式如下	"<<endl;

	scan(fin);
    sanyuanshi();
	cout<<"SUCCESS"<<endl;
	fclose(fin);

}

