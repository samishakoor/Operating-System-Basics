#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{

    ifstream in;
    in.open("readfile.txt", ios::in);

    ofstream out;
    out.open("hello.txt", ios::app);

    if (in.is_open() && out.is_open())
    {    
        int i=0;
        string line;
      
        while (!in.eof())
        {
            getline(in, line);

            int j=0;
            int k=0;
            string get_specific;

            while(line[j]!='\0')
            {
                 if(line[j]==' ' && line[j-1]==':')
                 {
                    k=j+1;
                    while(line[k]!='\0')
                    {
                       get_specific+=line[k];
                       k++;           
                    }
                    break;
                 }     
                j++;
            }
            out << get_specific << endl;
        }
    }

    in.close();
    out.close();
}
