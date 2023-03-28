#include <iostream>
#include<bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    string *str = new string[1000];
    
    char filename[100];
    cout<<"Enter name of file in which you want to enter the readed data: ";
    cin.getline(filename,100);

    strcat(filename,".txt");
    
    ifstream in;
    in.open("readfile.txt", ios::in);

    ofstream out;
    out.open(filename, ios::app);

    if (in.is_open() && out.is_open())
    {
        int i=0;
        string line;
        while (!in.eof())
        {
            getline(in, line);
            str[i] = line;
            out << str[i] << endl;
            i++;
        }
        str[i] = "\0";
    }

    in.close();
    out.close();
}