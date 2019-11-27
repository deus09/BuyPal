#include <iostream>
#include "./Admin/admin.h"
#include "./Customer/customer.h"
using namespace std;

int main()
{
  string choice;
  cout << "Welcome to BuyPal :) \n\n";
  cout << "Log_in as\n";
  cout << "[1]Admin\n";
  cout << "[2]Customer\n";
  cout << "\nChoice : ";
  cin >> choice;
  if(choice=="1")
  {
    admin();
  }
  else
  {
    _customer();
  }
  return 0;
}