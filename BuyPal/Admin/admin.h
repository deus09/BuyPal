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
		break;
	}
	if(n==name&&p==password)
  {
      cout<<"\nwelcome!!!!!"<<endl;
      return 1;
  }
	else
  {
      cout<<"\nRe-enter Name and Password\n";
      return 0;
  }
}

void update_shopping_list()
{
  cout<<"[1] Create list....(only for New Admin) ------> warning : you will lose all your data :)\n";
  cout<<"[2] View & edit list.....\n";
  int ch;
  cin>>ch;
  if(ch==1)
  {
    ofstream fout;
    int i=0;
    fout.open("Data/list.txt");
    while(fout)
    {
      i++;
      string itemname;
      float price;
      int quantity;
      cout<<"\nItem-Name:";
      cin>>itemname;
      cout<<"\nPrice:";
      cin>>price;
      cout<<"\nQuantity:";
      cin>>quantity;
      if(price==-1||quantity==-1)
        break;
      fout <<i<<" "<<itemname<<" "<<price<<" "<<quantity<< endl;
    }
    fout.close();
  }
  else
  {
    ifstream fin;
    string l;
    fin.open("Data/list.txt");
    while(fin)
    {
      getline(fin,l);
      cout<<l<<endl;
      if(fin.eof())break;
    }
    fin.close();
    int f;
    cout << endl;
    cout<<"[1] Update List\n";
    cout<<"[2] Add more Items\n";
    cout<<"[3] Leave as it is\n";
    cout<<"\nChoice : ";
    cin>>f;
    if(f==1)
    {
      ifstream fin;
      string l;
      fin.open("Data/list.txt");
      while(fin)
      {
        getline(fin,l);
        cout<<l<<endl;
        if(fin.eof())break;
      }
      fin.close();
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
          cout<<"Enter new name :\n";
          cin>>itemname;
          cout<<"Enter the price :\n";
          cin>>price;
          cout<<"Enter new quantity :\n";
          cin>>quantity;
          file1<<itno<<" "<< itemname<<" "<<price<<" "<<quantity<<endl;
        }
        else
        {
          file1<<l<<endl;
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
    else if(f==2)
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
      fout<<endl;
      while(true)
      {
        sn++;
        string itemname;
        float price;
        int quantity;
        cout<<"\nItemname:";
        cin>>itemname;
        cout<<"\nPrice:";
        cin>>price;
        cout<<"\nQuantity:";
        cin>>quantity;
        if(price==-1||quantity==-1)
        {
          cout<<"\nyou entered wrong price or quantity......\n";
          cout<<"\ndo you wanna edit or quit....\n";
          cout<<"\n [1] Edit again and [2] Quit....\n";
          int p;
          cin>>p;
          if(p==1)
          {
            cout<<"itemname:";
            cin>>itemname;
            cout<<"price:";
            cin>>price;
            cout<<"quantity:";
          }
          else
          {
            break;
          }
        }
        fout <<sn<<" "<<itemname<<" "<<price<<" "<<quantity<< endl;
        cout<<"Do you wanna Exit (y/n)....";
        char w;
        cin>>w;
        if(w=='y')
          break;
      }
    }
  }
}

void view_carts()
{
    ifstream fin;
    string l;
    fin.open("Data/cart.txt");
    while(fin)
    {
      getline(fin,l);
      cout<<l<<endl;
    }
}


void admin() {
	string name, password;
	int flag;
	do{
    cout << "Name : ";
    cin >> name;
    cout << "Password : ";
    password=input_password();
    flag = verifyadmin(name, password);
	}while(!flag);
	int choice;
  flag=1;
  while(flag)
  {
	  cout<<"\n[1]view & update list.....\n ";
	  cout<<"[2]view carts.....\n";
	  cout<<"[3]delivery part.....\n";
	  cout<<"\nChoice:";
    cin>>choice;
    if(choice==1)
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
    else if(choice==2)
    {
      view_carts();
    }
    else
    {
      delivery();
    }
    cout << "\n[1]Continue \n";
    cout << "Press another Key to exit\n";
    cin >> flag;
    if(flag!=1)
      flag=0;
  }
}