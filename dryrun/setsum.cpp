#include <cstdio>
#include <iostream>

using namespace std;

int data[]={43,73,25,85,65,45,79,21,87,63,99,94,90,22,39,52,48,69,17,86,21,23,32,16,92,38,21,94,24,77,40,55,51,41,97,32,93,22,40,30,19,36,17,51,21,95,36,40,55,51};
int kong[100],yuansugeshu,biaoganshu;
int j=0;

void shuchu()
{
    int i;
    for (i=0;i<yuansugeshu;i++)
    {
        printf("%d ",kong[i]);
    }
    printf("\n");
}

void biaoganshuyunsuan(int xianzaihe,int qishiyuansu)
{
    int i;
    if ((biaoganshu-1<=xianzaihe)&&(xianzaihe<=biaoganshu+1))
    {j++;
        shuchu();
        return ;
    }
    for (i=qishiyuansu;i<50;i++)
    {
        if (xianzaihe+data[i]<=biaoganshu)
        {
            kong[yuansugeshu++]=data[i];
            biaoganshuyunsuan(xianzaihe+data[i],i+1);
            yuansugeshu--;
        }
    }
    return ;
}



int main()
{   
    while (scanf("%d",&biaoganshu))
    {
        yuansugeshu=0;
        biaoganshuyunsuan(0,0);
        cout<<"total"<<j<<"sets"<<endl;j=0;
    }   

}
