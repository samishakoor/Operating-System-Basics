#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

int main(int arg, char *args[])
{

    int id = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);
    int pid = fork();
    int pid2;
    if (pid > 0)
    { 
        wait(NULL);
        cout << endl<< "Back into Parent !" << endl;
        char *shm_read_ptr = (char *)shmat(id, NULL, 0);

        // changing case of each character
        for (int i = 0; shm_read_ptr[i] != '\0'; i++)
        {
            if (islower(shm_read_ptr[i]))
            {
                shm_read_ptr[i] = char(toupper(shm_read_ptr[i]));
            }
            else if (isupper(shm_read_ptr[i]))
            {
                shm_read_ptr[i] = char(tolower(shm_read_ptr[i]));
            }
        }
        // removing integers
        int i, j;
        for (i = 0; shm_read_ptr[i] != '\0'; ++i)
        {
            while (shm_read_ptr[i] >= '0' && shm_read_ptr[i] <= '9')
            {
                for (j = i; shm_read_ptr[j] != '\0'; ++j)
                {
                    shm_read_ptr[j] = shm_read_ptr[j + 1];
                }
                shm_read_ptr[j] = '\0';
            }
        }
        
        cout << "File's Content updated Successfully by Parent !" << endl;
        pid2 = fork();
    }
    else if (pid == 0)
    {
        cout << endl << "Child created Successfully!" << endl;
        char *shm_write_ptr = (char *)shmat(id, NULL, 0);

        ifstream in;
        in.open(args[1], ios::in);
        if (in.is_open())
        {
            cout << "Reading data from " << args[1] << endl;
            cout << "Writing file contents to shared memory region." << endl;
            in >> shm_write_ptr;
        }
        in.close();
        shmdt(shm_write_ptr);
        exit(0);
    }
    else
    {
        cout << endl<< "Child Creation Unsuccessfull" << endl;
    }

    if (pid2 == 0)
    {
        char *shm_update_ptr = (char *)shmat(id, NULL, 0);
        ofstream out;
        out.open(args[1], ios::out);
        if (out.is_open())
        {
            out << shm_update_ptr;
            cout <<endl<< "Updated Data is write to " << args[1] << " successfully by child!" << endl;
        }
        out.close();
        shmdt(shm_update_ptr);
        exit(0);
    }
    shmctl(id, IPC_RMID, NULL);
    return 0;
}
