#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <fstream>
using namespace std;

int main()
{

    int fd1[2];
    int fd2[2];

    int p1 = pipe(fd1);
    int p2 = pipe(fd2);

    if (p1 == -1 || p2 == -1)
    {
        cout << "Pipe not created successfully!" << endl;
        exit(0);
    }

    int pid = fork();
    string str1 = "Hi There";
    string str3;

    if (pid > 0)
    {
        close(fd1[0]);
        write(fd1[1], &str1, sizeof(str1));
        wait(NULL);

        close(fd2[1]);
        read(fd2[0], &str3, sizeof(str3));
        cout << "The converted string is : " << str3 << endl;
    }
    else if (pid == 0)
    {

        close(fd1[1]);

        string str2;
        read(fd1[0], &str2, sizeof(str2));

        cout << "The original string is : " << str2 << endl;

        for (int i = 0; i < str2.length(); i++)
        {
            if (str2[i] >= 65 && str2[i] <= 90)
            {
                str3 += (str2[i] + 32);
            }
            else if (str2[i] >= 97 && str2[i] <= 122)
            {
                str3 += (str2[i] - 32);
            }
            else if (str2[i] == 32)
            {
                str3 += 32;
            }
        }

        close(fd2[0]);
        write(fd2[1], &str3, sizeof(str3));

        exit(0);
    }
    else
    {
        cout << "Error in child creation !" << endl;
    }

    return 0;
}
