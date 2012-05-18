#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
#include <iostream>
#include <windows.h>  //Contiene le API di Windows
using namespace std;

void progressBar()
{
    char buffer[256]={0};
    char percent[7]="0.0%%";
    short i, j;
    buffer[0]='[';
    for (i=0;i<40;i++)
    {
        buffer[i + 1]='=';
        j=i%4;
        if (j==0)
            buffer[i+2]='\\';
        else if (j==1)
            buffer[i+2]='|';
        else if (j==2)
            buffer[i+2]='/';
        else
            buffer[i+2]='-';

        for (short k=i+3;k<41;k++)
            buffer[k]=' ';
        buffer[41]=']';
        sprintf(percent,"%3.2f%%",i/40.0*100.0);
        cout<<"\t\t"<<buffer<<" "<<percent<<'\r';
        Sleep(35);     //Win32 API : delay di 55 ms
    }

    sprintf(percent,"%3.2f%%",i/40.0*100.0);
    cout<<"\t\t"<<buffer<<" "<<percent<<'\r';
}

#endif // PROGRESS_BAR_H
