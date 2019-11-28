#include "shopping.h"

int _customer()
{
    bool flag_log_in=false;
    customer new_user;
    string choice;
    while(!flag_log_in)
    {
        cout << endl << "[1] Exsiting User" << endl;
        cout << "[2] New User" << endl;
        cout << endl << "Choice : ";
        cin >> choice;
        if(choice == "1")
        {
            int count=0;
            while(1)
            {
                string username,password;
                cout << endl << "Username/Email_id : ";
                cin >> username;
                cout << "Password : ";
                password=encrypt(input_password());
                cout << endl;
                if(is_user(username,password))
                {
                    cout << endl << "Successfully Logged In :)" << endl;
                    new_user=create_user_obj(username);
                    flag_log_in=true;
                    break;
                }
                else
                {
                    string flag;
                    cout << endl << "Username/Password is Incorect" << endl;
                    cout << endl << "forgot password ? (y/n) : ";
                    cin >> flag;
                    if(flag=="y")
                    {
                        string forgot_username,forgot_email_id;
                        cout << endl << "Username : ";
                        cin >> forgot_username;
                        cout << endl << "Email_id : ";
                        cin >> forgot_email_id;
                        srand(time(NULL));
                        int is_sent = email_otp(forgot_username,forgot_email_id);
                        if(is_sent)
                        {
                            string otp;
                            cout << endl << "OTP is sent to your Email_id :)" << endl;
                            cout << endl << "Enter OTP : ";
                            cin >> otp;
                            ifstream fin;
                            fin.open("Data/otp.txt");
                            string right_otp;
                            fin >> right_otp;
                            if(otp==right_otp)
                            {
                                cout << endl << "OTP is correct :)" << endl;
                                string changed_password="",check_password;
                                cout << endl << "!!! Password should carry at least one special character and a number" << endl;
                                cout << endl << "New Password : ";
                                changed_password=input_password();
                                cout << endl << "confirm Password : ";
                                check_password=input_password();
                                if(is_password_valid(changed_password))
                                {
                                    if(check_password==changed_password)
                                    {
                                        update(forgot_username,forgot_email_id,encrypt(changed_password));
                                        cout << endl << "Password reset successfully !" << endl;
                                    }
                                    else
                                    {
                                        cout << endl << "Please Enter same Password :(" << endl;
                                    }
                                }
                                else
                                {
                                    cout << "Try again :( \n";
                                }
                                
                            }
                            else
                            {
                                cout << endl << "Incorrect OTP :( " << endl;
                            }                              
                        }
                    }
                    else if(flag=="n")
                    {
                        cout << endl << "Username/Email_id is incorrect :( try again" << endl;
                    }
                    else
                    {
                        cout << endl << "Wrong Input :(" << endl;
                    }
                }
                count++;
                if(count==3 && !flag_log_in)
                {
                    cout << endl << "Try again :(" << endl << endl;
                    return 1;
                }
            }
        }
        else if(choice=="2")
        {
            new_user=createid();
            cout << endl << "Account successfully created !" << endl << endl;
        }
        else
        {
            cout << endl << "Wrong Input :( " << endl;
        }
    }
    while(1)
    {
        cout << endl << "[1] Shopping..." << endl;
        cout << "[2] View your cart..." << endl;
        string sch;
        cout << endl << "Enter your choice : ";
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
                    cout << l << endl;
                }
                fin.close();
                cout << endl << "Enter the Details of item" << endl;
                int itmno,qntno;
                cout << endl << "Serial no: ";
                cin >> itmno;
                cout << endl << "Quantity: ";
                cin >> qntno;
                new_user=addtocart(itmno,qntno,new_user);
                new_user=cartfile(new_user);
                cout << "[1] Continue shopping:";
                cin >> flag;
                if(flag!=1)
                {
                    break;
                }
            }
            cout << endl << "[1] MAKE PAYMENT..." << endl;
            cout << "Press another key for exit.." << endl;
            cout << endl << "Choice : ";
            int mp;
            cin >> mp;
            if(mp==1)
            {
                //makepayment(new_user);
            }
        }
        else
            new_user=viewcart(new_user);
        cout << endl << "[1] Continue" << endl;
        cout << "Press another key to exit" << endl;
        cin >> sch;
        if(sch!="1")
            break;
    }
    return 0;
}