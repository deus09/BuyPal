#include "shopping.h"

void _customer()
{
    bool flag_log_in=false;
    customer new_user;
    string choice;
    while(!flag_log_in)
    {
        cout << "[1] Exsiting User\n";
        cout << "[2] New User\n";
        cout << "\nChoice : ";
        cin >> choice;
        if(choice == "1")
        {
            string username,password;
            cout << "Username/email_id : ";
            cin >> username;
            cout << "Password : ";
            password=input_password();
            if(is_user(username,password))
            {
                cout << "\nSuccessfully Logged In :)\n";
                new_user=create_user_obj(username);
                flag_log_in=true;
            }
            else
            {
                string flag;
                cout << "\nUsername/Password is Incorect\n";
                cout << "\nforgot password ? (y/n) : ";
                cin >> flag;
                if(flag=="y")
                {
                    string forgot_username,forgot_email_id;
                    cout << "\nUsername : ";
                    cin >> forgot_username;
                    cout << "\nEmail_id : ";
                    cin >> forgot_email_id;
                    srand(time(NULL));
                    int is_sent = email_otp(forgot_username,forgot_email_id);
                    if(is_sent)
                    {
                        string otp;
                        cout << "\nOTP is sent to your Email_id :)\n";
                        cout << "\nEnter OTP : ";
                        cin >> otp;
                        ifstream fin;
                        fin.open("Data/otp.txt");
                        string right_otp;
                        fin >> right_otp;
                        if(otp==right_otp)
                        {
                            cout << "\nOTP is correct :)\n";
                            string changed_password,check_password;
                            cout << "\nNew Password : ";
                            changed_password=input_password();
                            cout << "\nconfirm Password : ";
                            check_password=input_password();
                            if(check_password==changed_password)
                            {
                                update(forgot_username,forgot_email_id,changed_password);
                                cout << "\nPassword reset successfully !\n";
                            }
                            else
                            {
                                cout << "\nPlease Enter same Password :(\n";
                            }
                        }
                        else
                        {
                            cout << "\nIncorrect OTP :( \n";
                        }                              
                    }
                }
                else if(flag=="n")
                {
                    cout << "\nUsername/Email_id is incorrect :( try again\n";
                }
                else
                {
                    cout << "\nWrong Input :(\n";
                }
            }
        }
        else if(choice=="2")
        {
            new_user=createid();
            cout << "\nAccount successfully created !\n\n";
        }
        else
        {
            cout << "\nWrong Input :( \n";
        }
    }
    cout << endl;
    cout<<"\n[1] Shopping...\n";
    cout<<"[2] View your cart...\n";
    string sch;
    cout << "\nEnter your choice : ";
    cin >> sch;
    if(sch=="1")
    {
        int flag=1;
        while(flag)
        {
            ifstream fin;
            string l;
            fin.open("Data/list.txt");
            while(fin)
            {
                getline(fin,l);
                cout<<l<<endl;
            }
            fin.close();
            cout<<"\nEnter the Details of item \n ";
            int itmno,qntno;
            cout<<"\nserial no: ";
            cin>>itmno;
            cout<<"\nQuantity: ";
            cin>>qntno;
            new_user=addtocart(itmno,qntno,new_user);
            cout<<new_user.cart.items[new_user.cart.i-1].name<<endl;
            cout<<new_user.cart.items[new_user.cart.i-1].price<<endl;
            cout<<new_user.cart.items[new_user.cart.i-1].quantity<<endl;
            new_user=cartfile(new_user);
            cout<<"\n[1]Continue shopping:";
            cin>>flag;
            if(flag!=1)
                break;
        }
        cout<<" [1] MAKE PAYMENT...\n";
        cout<<"press another key for exit..\n";
        int mp;
        cin>>mp;
        if(mp==1)
        {
            //makepayment(new_user);
        }
    }
    else
        new_user=viewcart(new_user);
}