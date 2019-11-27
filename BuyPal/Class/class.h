#include<vector>
using namespace std;

struct item{
    string name;
    int price;
    int quantity;
};

typedef struct address
{
    public:
        string house_no;
        string res_area;
        string landmark;
}address;

class shopping_cart{
  public :
    int bill;
    int i;
    struct item items[100];
    shopping_cart(){
        bill=0;
        i=0;
    }
};

class customer
{
    public:
        shopping_cart cart;
        string name;
        string username;
        string email_id;
        string password;
        address _address;
        string mobile_no;
        friend customer createid();
};