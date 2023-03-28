#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string>
using namespace std;

class Calculator
{
public:
  float operand1;
  float operand2;
  char op;
  int wait;
  float result;
};

int main()
{

  int key = shmget(12321, 1024, IPC_CREAT | IPC_EXCL | 0666);
  cout << "Shared Memory is created with id: " << key << endl<<endl;

  Calculator *server_ptr = (Calculator *)shmat(key, NULL, 0);

  cout << "Enter Operand 1: ";
  cin >> server_ptr->operand1;

  cout << "Enter Operand 2: ";
  cin >> server_ptr->operand2;

  cout << "Enter Operator: ";
  cin >> server_ptr->op;

  if (server_ptr->op != '+' || server_ptr->op != '-' || server_ptr->op != '/' || server_ptr->op != '*')
  {

    server_ptr->wait = -1;

    cout <<endl<< "Waiting for the client process to send data.!" << endl;
    while (server_ptr->wait == -1)
      ; // busy wait

    cout << endl<< "The client process returned data to server successfully ! " << endl;
    cout<<"The result is :";
    cout << endl<< server_ptr->operand1<< server_ptr->op<< server_ptr->operand2 << " = " << server_ptr->result << endl;
  }
  else
  {
    cout << "Invalid Operand !" << endl;
  }
  // detach
  shmdt(server_ptr);

  shmctl(key, IPC_RMID, NULL); // mark the shared region for deletion
}
