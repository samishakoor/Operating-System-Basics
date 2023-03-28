#include <iostream>
#include <sys/shm.h>
#include <string>
#include <stdio.h>
#include <cstring>
#include <sys/ipc.h>
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

    int key = shmget(12321, 1024, 0);

    Calculator *client_ptr = (Calculator *)shmat(key, NULL, 0);


    float op1 = client_ptr->operand1;
    float op2 = client_ptr->operand2;
    
    //computing the operator on operators given by the server
    if (client_ptr->op == '+')
    {
        client_ptr->result = op1 + op2;
    }
    else if (client_ptr->op == '-')
    {
        client_ptr->result = op1 - op2;
    }
    else if (client_ptr->op == '/')
    {
        client_ptr->result = op1 / op2;
    }
    else if (client_ptr->op == '*')
    {
        client_ptr->result = op1 * op2;
    }
    else
    {
        cout << "Invalid Operator !" << endl;
    }

    client_ptr->wait=1;   //wait is over for server


    // detach
    shmdt(client_ptr);

    return 0;
}