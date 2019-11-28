#include <string>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include "../Class/class.h"
using namespace std;
#define MAX 62

string encrypt(string s)
{
    for(int i=0;i<s.size();i++)
    {
        s[i]+=5;
    }
    return s;
}

void SetStdinEcho(bool enable = true)
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

string input_password()
{
    SetStdinEcho(false);
    string password;
    cin >> password;
    SetStdinEcho(true);
    return password;
}

bool check(string email_id)
{
    for(int i=0;i<email_id.size();i++)
    {
        if(email_id[i]=='@')
            return true;
    }
    return false;
}

bool is_valid_no(string num)
{
    if(num.size()!=10)
        return false;
    for(int i=0;i<num.size();i++)
    {
        if(num[i]<'0' || num[i]>'9')
            return false;
    }
    return true;
}

bool is_password_valid(string s)
{
    bool flag_num=false,flag_special_char=false;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]>='0' && s[i]<='9')
            flag_num=true;
        if((s[i]>=32 && s[i]<=47) || (s[i]>=58 && s[i]<=64) || (s[i]>=91 && s[i]<=96) || (s[i]>=123 && s[i]<=126))
            flag_special_char=true;
    }
    return flag_num && flag_special_char;
}

string alphaNum="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

string generate_otp()
{
    string s="";
    for(int i=0;i<6;i++)
    {
        s = s + alphaNum[rand()%MAX];
    }
    return s;
}


void generate_mail(string username,string email_id)
{
    string s=generate_otp();
    ofstream fout;
    fout.open("Data/mail.txt");
    fout << "From: \"BuyPal\" <buypaliitj@gmail.com>" << endl;
    fout << "To: \"" << username << "\" <" << email_id << ">" << endl;
    fout << "Subject: Reset Password" << endl;
    fout << endl;
    fout << "OTP: " << s << endl;
    fout.close();
    fout.open("Data/otp.txt");
    fout << s << endl;
}

bool email_otp(string username,string email_id)
{
    ifstream fin;
    fin.open("Data/authentication.txt");
    while(fin)
    {
        string check_username,check_email_id,password;
        fin >> check_username;
        fin >> check_email_id;
        fin >> password;
        if(check_username==username && check_email_id==email_id)
        {
            generate_mail(username,email_id);
            string s="curl --url 'smtps://smtp.gmail.com:465' --ssl-reqd \
            --mail-from 'buypaliitj@gmail.com' --mail-rcpt '" + email_id + "' \
            --upload-file 'Data/mail.txt' --user 'buypaliitj@gmail.com:buypalnsfw789' --insecure";
            const char *command=s.c_str();
            system(command);
            return true;
        }
    }
    return false;
}

bool is_already_exists(string username,string email_id)
{
    ifstream fin;
    fin.open("Data/authentication.txt");
    while(fin)
    {
        string existing_username,existing_email_id,existing_password;
        fin >> existing_username;
        fin >> existing_email_id;
        fin >> existing_password;
        if((existing_username==username || existing_email_id==email_id))
        {
            return 1;
        }
    }
    return 0;
}

bool is_user(string username,string password)
{
    ifstream fin;
    fin.open("Data/authentication.txt");
    while(fin)
    {
        string existing_username,existing_email_id,existing_password;
        fin >> existing_username;
        fin >> existing_email_id;
        fin >> existing_password;
        if((existing_username==username || existing_email_id==username) && existing_password==password)
        {
            return 1;
        }
    }
    return 0;
}

customer createid()
{
    string username,password="",check_password="0",email_id;
    bool verify=false;
    while(!verify)
    {
        cout << endl;
        bool flag=0;
        while(!flag)
        {
            cout << "Email_id : ";
            cin >> email_id;
            if(check(email_id))
                flag=1;
            else
            {
                cout << endl << "Enter valid Email_id : " << endl;
            }
        }
        cout << "Username : ";
        cin >> username;
        while(!is_password_valid(password) || password!=check_password)
        {
            cout << endl << "!!! Password should carry at least one special character and a number" << endl;
            cout << "Password : ";
            password=input_password();
            cout << endl << "Confirm Password : ";
            check_password=input_password();
            cout << endl;
            if(password!=check_password)
            {
                cout << "Please Enter same password :(" << endl;
            }
        }
        if(!is_already_exists(username,email_id))
        {
            cout << endl << "Enter Personal details" << endl << endl;
            verify=true;
        }
        else
        {
            cout << endl << "Username\\Email_id already exists :(" << endl;  
        }
    }
    customer new_user;
    new_user.username=username;
    new_user.password=encrypt(password);
    new_user.email_id=email_id;
    cout << "Name : ";
    cin >> new_user.name;
    while(1)
    {
        cout << "Mobile No. : ";
        cin >> new_user.mobile_no;
        if(!is_valid_no(new_user.mobile_no))
        {
            cout << "Enter Valid number \n";
        }
        else
        {
            break;
        }
    }
    cout << "Address\n";
    cout << "House\\Room No : ";
    cin >> new_user._address.house_no;
    cout << "Resident Area : ";
    cin >> new_user._address.res_area;
    cout << "Landmark : ";
    scanf("\n");
    getline(cin,new_user._address.landmark);
    ofstream fout;
    fout.open("Data/user_details.txt",ios::app);
    fout <<new_user.username  << endl;
    fout << new_user.name << endl;
    fout << new_user.email_id << endl;
    fout << new_user._address.res_area << " " << new_user._address.house_no << " " << new_user._address.landmark << endl;
    fout << new_user.mobile_no << endl;
    fout.close();
    fout.open("Data/authentication.txt",ios::app);
    fout << new_user.username << endl;
    fout << new_user.email_id << endl;
    fout << new_user.password << endl;
    return new_user;
}

void update(string username,string email_id,string password)
{
    ifstream fin;
    ofstream copout;
    fin.open("Data/authentication.txt");
    copout.open("Data/try.txt");
    while(fin)
    {
        string username_change,email_id_change,password_change;
        fin >> username_change >> email_id_change >> password_change;
        if(username==username_change && email_id==email_id_change)
        {
            copout << username_change << endl;
            copout << email_id_change << endl;
            copout << password << endl;
        }
        else
        {
            copout << username_change << endl;
            copout << email_id_change << endl;
            copout << password_change << endl;
        }
    }
    ifstream copin;
    copin.open("Data/try.txt");
    ofstream fout;
    fout.open("Data/authentication.txt");
    while(copin)
    {
        string s;
        copin >> s;
        fout << s << endl;
    }
}