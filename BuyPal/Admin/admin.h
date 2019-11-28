#include <fstream> 
#include "../Authentication/authentication.h"
#include "../Delivery/delivery.h"
int verifyadmin(string name, string password) 
{
	ifstream fin;
	string n, p;
	fin.open("Data/data.txt");
	while(fin) 
  {
		fin >> n;
		fin >> p;
		if(n==name&&p==password)
    {
      cout << endl << endl << "Log-in Successful :)" << endl << endl;
      return 1;
    }
    break;
	}
  cout << endl << endl << "Incorrect Name or Password" << endl;
  return 0;
}

void update_shopping_list()
{
  cout << endl;
  cout << "[1] Create list....(only for New Admin) ------> warning : you will lose all your data :)" << endl;
  cout << "[2] View & edit list....." << endl;
  cout << endl;
  cout << "Choice : ";
  string ch;
  cin >> ch;
  if(ch=="1")
  {
    ofstream fout;
    int i=0;
    fout.open("Data/list.txt");
    while(fout)
    {
      i++;
      string choice;
      string itemname;
      float price;
      int quantity;
      cout << endl << "Item-Name:";
      cin >> itemname;
      cout << endl << "Price:";
      cin >> price;
      cout << endl << "Quantity:";
      cin >> quantity;
      fout << i << " " << itemname << " " << price << " " << quantity << endl;
      while(true)
      {
        cout << "Wanna Add more items (y/n) : ";
        cin >> choice;
        if(choice!="y" && choice!="n")
        {
          cout << endl << "Wrong Input" << endl;
        }
        else
        {
          break;
        }
      }
      if(choice=="n")
        break;
    }
    fout.close();
  }
  else if(ch=="2")
  {
    ifstream fin;
    string l;
    fin.open("Data/list.txt");
    if(fin.peek() == ifstream::traits_type::eof())
    {
      cout << endl;
      cout << "List is Empty :( " << endl;
    }
    else
    {
      while(fin)
      {
        getline(fin,l);
        cout << l << endl;
        if(fin.eof())break;
      }
      fin.close();
    }
    string flag;
    cout << endl;
    cout << "[1] Update List" << endl;
    cout << "[2] Add more Items" << endl;
    cout << "[3] Leave as it is" << endl;
    cout << endl << "Choice : ";
    cin >> flag;
    if(flag=="1")
    {
      ifstream fin;
      string l;
      fin.open("Data/list.txt");
      if(fin.peek() == ifstream::traits_type::eof())
      {
          cout << "List is Empty :(" << endl;
      }
      else
      {
        while(fin)
        {
          getline(fin,l);
          cout << l << endl;
          if(fin.eof())break;
        }
        fin.close();
      }
      int itno;
      cout<<"Enter the Item no. which you want to update:";
      cin>>itno;
      string itemname;
      float price;
      int quantity;
      fstream file;
      file.open("Data/list.txt",ios::app |ios::in| ios::out);
      fstream file1;
      file1.open("Data/temp.txt",ios::out);
      while(file)
      {
        getline(file,l);
        if(l[0]-'0'==itno)
        {
          cout << "Enter new name: " << endl;
          cin >> itemname;
          cout << "Enter the price: " << endl;
          cin >> price;
          cout << "Enter new quantity: " << endl;
          cin >> quantity;
          file1 << itno << " " << itemname << " " << price << " " << quantity << endl;
        }
        else
        {
          file1 << l << endl;
        }
      }
      file.close();
      file1.close();
      file.open("Data/list.txt",ios::out);
      file1.open("Data/temp.txt",ios::in);
      while(file1)
      {
        getline(file1,l);
        file << l << endl;
      }
    }
    else if(flag=="2")
    {
      ifstream fin;
      string l;
      int sn=0;
      fin.open("Data/list.txt");
      while(fin)
      {
        getline(fin,l);
        if(fin.eof())break;
          sn=l[0]-'0';
      }
      fin.close();
      ofstream fout;
      fout.open("Data/list.txt",ios::out|ios::app);
      string lol;
      fout << endl;
      while(true)
      {
        sn++;
        string itemname;
        float price;
        int quantity;
        cout << endl << "Item-Name:";
        cin >> itemname;
        cout << endl << "Price:";
        cin >> price;
        cout << endl << "Quantity:";
        cin >> quantity;
        if(price==-1||quantity==-1)
        {
          cout << endl << "you entered wrong price or quantity......" << endl;
          cout << endl << "do you wanna edit or quit...." << endl;
          cout << endl << "[1] Edit again and [2] Quit...." << endl;
          int p;
          cin >> p;
          if(p==1)
          {
            cout << "Item-Name:";
            cin >> itemname;
            cout << "Price:";
            cin >> price;
            cout << "Quantity:";
          }
          else
          {
            break;
          }
        }
        fout << sn << " " << itemname << " " << price << " " << quantity << endl;
        cout << "Do you wanna Exit (y/n)....";
        char w;
        cin >> w;
        if(w=='y')
          break;
      }
    }
  }
  else
  {
    cout << endl;
    cout << "Wrong Input :(" << endl; 
  }
}

void view_carts()
{
    ifstream fin;
    string l;
    fin.open("Data/cart.txt");
    if(fin.peek() == ifstream::traits_type::eof())
    {
      cout << endl << "Cart is Empty :) " << endl;
      return;
    }
    while(fin)
    {
      getline(fin,l);
      cout << l << endl;
    }
}

int admin() {
  int count=0;
	string name, password;
	int flag=0;
	do{
    cout << endl << "Name : ";
    cin >> name;
    cout << "Password : ";
    password=input_password();
    password=encrypt(password);
    flag = verifyadmin(name, password);
    count++;
    if(count==3 && !flag)
    {
      cout << endl << "Try again :( " << endl << endl;
      return 1;
    }
  }while(!flag);
	string choice;
  flag=1;
  while(flag)
  {
	  cout << "[1] View & Update list...." << endl;
	  cout << "[2] View carts....." << endl;
	  cout << "[3] Delivery part....." << endl;
    cout << endl << "Choice : ";
    cin >> choice;
    if(choice=="1")
    {
      update_shopping_list();
      ifstream fin;
      fin.open("Data/list.txt");
      string l;
      while(fin)
      {
        getline(fin,l);
        cout << l << endl;
        if(fin.eof())break;
      }
    }
    else if(choice=="2")
    {
      view_carts();
    }
    else if(choice=="3")
    {
      delivery();
    }
    else
    {
      cout << "Wrong Input :( \n";
    }
    cout << endl << endl << "[1] Continue" << endl;
    cout << "Press another Key to exit" << endl;
    cin >> flag;
    if(flag!=1)
      flag=0;
  }
  return 0;
}