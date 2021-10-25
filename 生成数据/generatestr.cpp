#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
char getChar(int type)
{
//	srand(time(NULL));
    switch(type)
    {
    	case 1:return (rand()&1)+'0';
    	case 2:return rand()%10+'0';
    	default:
    		char temp = rand()%95+32;
    		if(temp != ' ')
			return temp;
			return '$';
			
		
    }
}
void write(ofstream &out, int strlen, int sub_strlen, int point, int type)
{
    string sub_str;
    for (int i=0;i<sub_strlen;i++) sub_str+=getChar(type);
    if (point<0||point+sub_strlen>strlen)
    {
        for (int i=0;i<strlen;i++) out<<getChar(type);
        out<<endl<<sub_str<<endl;
        return;
    }
    for (int i=0;i<point;i++) out<<getChar(type);
    out<<sub_str;
    for (int i=0;i<strlen-point-sub_strlen;i++) out<<getChar(type);
    out<<endl<<sub_str<<endl;
}
int main()
{
    srand(time(NULL));
    const int len=100000000;
    for (int k=1;k<=3;k++)
    {
        char s[20]={0};
        sprintf(s,"strings%d.txt",k);
        ofstream out(s);
        for (int i=0;i<5;i++)
        { 
            int temp=len/5*2;
            write(out,len,1000,temp*i+rand()%temp,k);
        }
        out.close();
    }
    return 0;
}
