#include <iostream>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *arg[])
{

    int fd1[2];
    int p1 = pipe(fd1);

    string array[1000];
    if (p1 == -1)
    {
        cout << "Pipe not created successfully!" << endl;
        exit(0);
    }

    int pid = fork();

    if (pid > 0)
    {
        close(fd1[0]);

        ifstream fin;
        fin.open(arg[1], ios::in);

        int c=0;
        if (fin.is_open())
        {
           string line;
           while(!fin.eof())
           {
            getline(fin,line);
            array[c]=line;
            c++;
           }
           array[c]='\0';
        }

        fin.close();
        write(fd1[1], &array, sizeof(array));
        wait(NULL);
    }
    else if (pid == 0)
    {
        close(fd1[1]);
        read(fd1[0], &array, sizeof(array));

        ofstream fout;
        fout.open(arg[2], ios::out);

        if (fout.is_open())
        {
           for(int i=0;i<100;i++)
           {
            if(array[i+1]=="\0")
            {
                break;
            }
            fout<<array[i];
            fout<<endl;
           }
        }
        fout.close();
        exit(0);
    }
    else
    {
        cout << "Error in child creation !" << endl;
    }

    return 0;
}