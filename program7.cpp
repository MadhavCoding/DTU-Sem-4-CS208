#include <iostream>
#include <vector>
using namespace std;

class ipv4
{
    string s;
    vector<int> v;

public:
    void get1()
    {
        cout<<"Enter 32 bits sequence : ";
        cin.ignore();
        getline(cin, s);

        v.clear();

        for(int i = 0; i < 32; i += 9)
        {
            int num = 0;
            for(int j = i + 7; j >= i; j--)
            {
                if(s[j] == '1') num |= (1 << (i + 7 - j));
            }
            v.push_back(num);
        }
    }

    void get2()
    {
        cout<<"Enter Dotted Decimal sequence : ";
        cin>>s;

        v.clear();

        int i = 0;
        while(i < s.length())
        {
            int num = 0;
            while(i < s.length() && s[i] != '.')
            {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i++;
            v.push_back(num);
            num = 0;
        }
    }

    void show()
    {
        cout<<v[0];
        for(int i = 1; i < 4; i++)
        {
            cout<<"."<<v[i];
        }
        cout<<endl;
    }

    void find()
    {
        if(0 <= v[0] && v[0] <= 127)
        {
            cout<<"Network Class : A"<<endl;
            cout<<"Netword ID : ";
            cout<<v[0]<<".0.0.0"<<endl;
            cout<<"Host ID : ";
            cout<<v[0]<<"."<<v[1]<<"."<<v[2]<<"."<<v[3]<<endl;
        }

        else if(128 <= v[0] && v[0] <= 191)
        {
            cout<<"Network Class : B"<<endl;
            cout<<"Netword ID : ";
            cout<<v[0]<<"."<<v[1]<<".0.0"<<endl;
            cout<<"Host ID : ";
            cout<<v[0]<<"."<<v[1]<<"."<<v[2]<<"."<<v[3]<<endl;
        }

        else if(192 <= v[0] && v[0] <= 223)
        {
            cout<<"Network Class : C"<<endl;
            cout<<"Netword ID : ";
            cout<<v[0]<<"."<<v[1]<<"."<<v[2]<<".0"<<endl;
            cout<<"Host ID : ";
            cout<<v[0]<<"."<<v[1]<<"."<<v[2]<<"."<<v[3]<<endl;
        }

        else if(224 <= v[0] && v[0] <= 239)
        {
            cout<<"Network Class : D"<<endl;
        }

        else
        {
            cout<<"Network Class : E"<<endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    ipv4 ip;
    cout<<"1 : 32 Bit Sequence \n2 : Dotted Decimal \n3 : Exit"<<endl;
    while(true)
    {
        int op; cin>>op;
        cout<<endl;
        if(op == 1)
        {
            ip.get1();
            ip.show();
            ip.find();
        }
        else if(op == 2)
        {
            ip.get2();
            ip.show();
            ip.find();
        }
        else break;

        cout<<endl;
    }
    return 0;
}