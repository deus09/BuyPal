#include <fstream>
#include <sstream>

struct validity
{
  string month,year;
};

int verifycard(int cardno,int cvv,struct validity val,string cardname){
  return 1;
}

void shopping(int itemno,int quantity){
    ofstream cput;
    cput.open("Data/try.txt");
    ifstream fout;
    string nl;
    string l;
    fout.open("Data/list.txt");
    while(fout){
     getline(fout,l);
     if((l[0]-'0')==itemno)
    {
        int count=0,num=0;
       
        for(int i=0;i<l.size();i++){
            if(l[i]==' ')
            {
                count++;
            }
            if(count==3 && l[i]!=' ')
            {
                num=num*10+(l[i]-'0');
            }
            else
            {
                nl+=l[i];
            }
        }
        num=num-quantity;
        nl+=" ";
        nl+=to_string(num);
        l=nl;
    }
        cput << l << endl;
    }
    cput.close();
    fout.close();
    fout.open("Data/try.txt");
    cput.open("Data/list.txt");
    while(fout){
        getline(fout,l);
        cput << l << endl;
    }  
}
customer makepayment(customer u1)
{
  ifstream fin;
  fin.open("Data/cart.txt");
  string l;
  while(fin)
  {
    getline(fin,l);
    if(l==u1.username)
      break;
  }
  cout << "Username: " << l << endl;
  getline(fin,l);
  cout << "Total Amount: " << l << endl;
  getline(fin,l);
  cout << "No. of items: " << l << endl;
  fin.close();
  cout << endl << "[1] online payment..." << endl;
  cout << endl << "[2] cash on delivery...." << endl;
  cout << endl << "Choice : ";
  string a;
  cin >> a;
  if(a=="1")
  {
    cout << endl << "Enter card details..." << endl;
    string cardname;
    int cardno,cvv;
    struct validity val;
    cout << "Card number: ";
    cin >> cardno;
    cout << "CVV: ";
    cin >> cvv;
    cout << "Expiration Date..." << endl;
    cout << "Month:";
    cin >> val.month;
    cout << "Year:";
    cin >> val.year;
    cout << "Name on the card : ";
    scanf("\n");
    getline(cin,cardname);
    if(verifycard(cardno,cvv,val,cardname)){
      cout << "Your payment done successfully..:)" << endl;
      ofstream cop;
      ofstream pop;
      pop.open("Data/try.txt");
      fin.open("Data/cart.txt");
      cop.open("Data/ShoppingCart.txt");
      string name,bill,qty;
      while(fin)
      {
        int flag=0;
        getline(fin,l);
        if(l==u1.username)
        {
          name=l;
          getline(fin,l);
          bill=l;
          getline(fin,l);
          qty=l;
          cop << "1020 " << name << " " << bill << " " << qty << endl;
        }
        else
        {
            pop << l << endl;
        }
      }
      fin.close();
      pop.close();
      cop.close();
      fin.open("Data/try.txt");
      pop.open("Data/cart.txt");
      while(fin)
      {
        getline(fin,l);
        pop << l << endl;
      }
      fin.close();
      pop.close();
    }
  }
  else
  {
      cout << "Thank you...visit again :)" << endl;
  }
  return u1;
}
customer create_user_obj(string username){
  customer obj;
  ifstream fin;
  string l;
  fin.open("Data/user_details.txt");
  while(fin){
    getline(fin,l);
      if(l==username){
          obj.username=username;
        break;
      }
  }
  getline(fin,l);
  obj.name=l;
  getline(fin,l);
  obj.email_id=l;
  return obj;
}
class customer addtocart(int itmno,int qty,customer new_user){
  ifstream fin;
  string l,nam,mul,vim;
  fin.open("Data/list.txt");
  while(fin){
    getline(fin,l);
    if((l[0]-'0')==itmno)
    {
      int count=0;
      for(int i=0;i<l.size();i++){
        if(l[i]==' ')
          count++;
        if(count==1)
          nam+=l[i];
        if(count==2)
          mul+=l[i];
        if(count==3)
          vim+=l[i];
      }
      break;
    }
  }
  new_user.cart.items[new_user.cart.i].name=nam;
  stringstream geek(mul);
  new_user.cart.items[new_user.cart.i].price=0;
  geek >> new_user.cart.items[new_user.cart.i].price;
  new_user.cart.items[new_user.cart.i].quantity=qty;
    new_user.cart.i++;
  return new_user; 
}

customer cartfile(customer u1)
{
  ifstream fin;
  ofstream fout;
  cout << u1.cart.items[u1.cart.i-1].name << endl;
  fout.open("Data/try.txt");
  string l;
  int flag=1;
  fin.open("Data/cart.txt");
  while(fin)
  {
    getline(fin,l);
    if(l==u1.username)
    {
      flag=0;
      fout << l << endl;
      getline(fin,l);
      int x=0;
      stringstream geek(l);
      geek >> x;
      fout << ((u1.cart.items[u1.cart.i-1].price)*(u1.cart.items[u1.cart.i-1].quantity)+x) << endl;
      getline(fin,l);
      stringstream peek(l);
      peek >> x;
      fout << ((u1.cart.items[u1.cart.i-1].quantity)+x) << endl;
    }
    else
    {
      fout << l << endl;
    }
  }
  if(flag)
  {
    fout << u1.username << endl;
    fout << (u1.cart.items[u1.cart.i-1].price)*(u1.cart.items[u1.cart.i-1].quantity) << endl;
    fout << u1.cart.items[u1.cart.i-1].quantity << endl;
  }
  fin.close();
  fout.close();
  fin.open("Data/try.txt");
  fout.open("Data/cart.txt");
  while(fin)
  {
    fin >> l;
    if(fin.eof())break;
    fout << l << endl;
  }
  fin.close();
  fout.close();
  return u1;
}

customer viewcart(customer u1){
  ifstream fin;
  string l;
  int flag=1;
  fin.open("Data/cart.txt");
  while(fin){
    getline(fin,l);
    if(l==u1.username){
      flag=0;
      cout << l << endl;
      getline(fin,l);
      cout << l << endl;
      getline(fin,l);
      cout << l << endl;
      getline(fin,l);
      cout << l << endl;
      getline(fin,l);
      return u1;
    }
  }
  if(flag)
    cout << "sorry no data found..." << endl;
  return u1;
}