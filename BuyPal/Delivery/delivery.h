#include <cstring>
#include <fstream>
using namespace std;

void AssignCart()
{
    ifstream fileCart;
    fileCart.open("Data/ShoppingCart.txt");
    while(fileCart)
    {
        string UserName_Customer_ToDeliver;
        string CartSearchString;
        getline(fileCart,CartSearchString);
        for(int lv1=5;;lv1++)
        {
            if(CartSearchString[lv1]!=' ')
            {
                UserName_Customer_ToDeliver+=CartSearchString[lv1];
            }
            else
            {
                break;
            }
        }
        int reqTimeSlot;
        reqTimeSlot=(CartSearchString[0]-'0')*1000+(CartSearchString[1]-'0')*100+(CartSearchString[2]-'0')*10+(CartSearchString[3]-'0');
        ifstream file_AddressSearch;
        string AddressSearchString;
        file_AddressSearch.open("Data/user_details.txt",ios::in);
        while(file_AddressSearch)
        {
            getline(file_AddressSearch,AddressSearchString);
            if(AddressSearchString==UserName_Customer_ToDeliver)
            {
                getline(file_AddressSearch,AddressSearchString);
                getline(file_AddressSearch,AddressSearchString);
                break;
            }
        }
        file_AddressSearch.close();
        ofstream file1;
        if(reqTimeSlot>=800 && reqTimeSlot<1100)
            file1.open("Data/DeliveryBoy0.txt",ios::app);
        else if(reqTimeSlot>=1100 && reqTimeSlot<1400)
            file1.open("Data/DeliveryBoy1.txt",ios::app);
        else if(reqTimeSlot>=1400 && reqTimeSlot<1700)
            file1.open("Data/DeliveryBoy2.txt",ios::app);
        else if(reqTimeSlot>=1700 && reqTimeSlot<2000)
            file1.open("Data/DeliveryBoy3.txt",ios::app);
        else if(reqTimeSlot>=2000 && reqTimeSlot<=2300)
            file1.open("Data/DeliveryBoy4.txt",ios::app);
        file1 << AddressSearchString << endl << CartSearchString << endl;
        file1.close();
        fileCart.close();
    }
}

void completeDelivery()
{
    ofstream file1;
    file1.open("Data/DeliveryBoy0.txt",ios::out);
    file1.open("Data/DeliveryBoy1.txt",ios::out);
    file1.open("Data/DeliveryBoy2.txt",ios::out);
    file1.open("Data/DeliveryBoy3.txt",ios::out);
    file1.open("Data/DeliveryBoy4.txt",ios::out);
    file1.close();
}

void DisplayDeliverySlot()
{
    string s;
    ifstream file1;
    cout << endl << "Slot 8AM to 11AM:-" << endl;
    file1.open("Data/DeliveryBoy0.txt",ios::in);
    if(file1.peek()==ifstream::traits_type::eof())
    {
        cout << "No deliveries are pending in this slot :)" << endl;
    }
    else
    {    
        while(file1)
        {
            getline(file1,s);
            cout<<s<<endl;
        }
    file1.close();
    }
    cout << endl << "Slot 11AM to 2PM:-" << endl;
    file1.open("Data/DeliveryBoy1.txt",ios::in);
    if(file1.peek()==ifstream::traits_type::eof())
    {
        cout << "No deliveries are pending in this slot :)" << endl;
    }
    else
    {
        while(file1)
        {
            getline(file1,s);
            cout<<s<<endl;
        }
        file1.close();
    }
    cout << endl << "Slot 2PM to 5PM:-" << endl;
    file1.open("Data/DeliveryBoy2.txt",ios::in);
    if(file1.peek()==ifstream::traits_type::eof())
    {
        cout << "No deliveries are pending in this slot :)" << endl;
    }
    else
    {
        while(file1)
        {
            getline(file1,s);
            cout<<s<<endl;
        }
        file1.close();
    }
    cout << endl << "Slot 5PM to 8PM:-" << endl;
    file1.open("Data/DeliveryBoy3.txt",ios::in);
    if(file1.peek()==ifstream::traits_type::eof())
    {
        cout << "No deliveries are pending in this slot :)" << endl;
    }
    else
    {
        while(file1)
        {
            getline(file1,s);
            cout<<s<<endl;
        }
        file1.close();
    }
    cout << endl << "Slot 8PM to 11PM:-" << endl;
    file1.open("Data/DeliveryBoy4.txt",ios::in);
    if(file1.peek()==ifstream::traits_type::eof())
    {
        cout << "No deliveries are pending in this slot :)" << endl;
    }
    else
    {
        while(file1)
        {
            getline(file1,s);
            cout<<s<<endl;
        }
        file1.close();
    }
}

void delivery()
{
while(true)
{
  string flag;
  cout << endl;
  cout << "[1]View Pending deliveries\n";
  cout << "[2]complete all delivery\n";
  cout << "[3]Assign DeliveryBoys\n";
  cout << endl;
  cout << "Choice : ";
  cin >> flag;
  if(flag=="1")
  {
    DisplayDeliverySlot();
  }
  else if(flag=="2")
  {
    completeDelivery();
  }
  else if(flag=="3")
  {
    AssignCart();
  }
  else
  {
    cout << "Wrong Input :( \n";
  }
  cout << "[1] Continue\n";
  cout << "Press another key to exit :)\n";
  cin >> flag;
  if(flag!="1")
    break;  
}
}