#include <iostream>
#include "./Admin/admin.h"
#include "./Customer/customer.h"
using namespace std;

void centerstring(string s)
{
  int l=s.size();
  int pos=(int)((80-l)/2);
  for(int i=0;i<pos;i++)
    cout << " ";
  cout << s << endl;
}

int main()
{
  cout << endl;
  centerstring("Welcome to BuyPal :)");
  cout << endl;
  bool flag=true;
  int count=0;
  while(flag)
  {
    string choice;
    cout << "Log_in as" << endl;
    cout << "   [1]Admin" << endl;
    cout << "   [2]Customer" << endl;
    cout << endl << "Choice : ";
    cin >> choice;
    if(choice=="1")
    {
      flag=admin();
    }
    else if(choice=="2")
    {
      flag=_customer();
    }
    else
    {
      cout << endl << "Wrong Input" << endl;
    }
    count++;
    if(count==3 && flag)
    {
      cout << endl << "Try again after sometime :)" << endl;
      flag=0;
    }
  }
  return 0;
}