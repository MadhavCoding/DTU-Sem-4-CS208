#include <iostream>
using namespace std;

string mod2remainder(string s1, string s2)
{
    string result = "";
    for(int i = 1; i < s2.length(); i++)
    {
        if(s1[i] == s2[i]) result += '0';
        else result += '1';
    }

    return result;
}

string mod2division(string dataword, string key)
{
    int ptr = key.length();
    string temp = dataword.substr(0, key.length());

    while (ptr < dataword.length())
    {
        string remainder = "";
        if(temp[0] == '1')
        {
            remainder = mod2remainder(temp, key);
        }
        else
        {
            remainder = mod2remainder(temp, string(key.length(), '0'));
        }
        temp = remainder + dataword[ptr];
        ptr++;
    }
    
    if(temp[0] == '1')
    {
        return mod2remainder(temp, key);
    }
    else
    {
        return mod2remainder(temp, string(key.length(), '0'));
    }
}

string encodeData(string dataword, string key)
{
    dataword.append(key.length() - 1, '0');
    string remainder = mod2division(dataword, key);
    int i = (int)(remainder.length()) - 1, j = (int)(dataword.length()) - 1;

    while(i >= 0 && j >= 0)
    {
        if(remainder[i] == dataword[j])
        {
            dataword[j] = '0';
        }
        else
        {
            dataword[j] = '1';
        }
        i--; j--;
    }

    return dataword;
}

bool decodeData(string encoded, string key)
{
    string remainder = mod2division(encoded, key);
    for(int i = 0; i < remainder.length(); i++)
    {
        if(remainder[i] == '1') return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    cout<<"Sender side..."<<endl;

    string dataword;
    cout<<"Enter Dataword : ";
    cin>>dataword;
    string key;
    cout<<"Enter Key : ";
    cin>>key;

    cout<<"The encoded string is : ";
    string encoded = encodeData(dataword, key);
    cout<<encoded<<endl;

    cout<<"Reciever side..."<<endl;

    bool decoding = decodeData(encoded, key);
    if(decoding)
    {
        cout<<"Dataword"<<endl;
        cout<<"Data recieved successfully"<<endl;
    }
    else
    {
        cout<<"Invalid"<<endl;
        cout<<"Error in data"<<endl;
    }

    cout<<"Taking encoded data from user..."<<endl;

    string encodedUser;
    cout<<"Enter encoded string : ";
    cin>>encodedUser;
    string key2;
    cout<<"Enter key : ";
    cin>>key2;

    decoding = decodeData(encodedUser, key2);
    if(decoding)
    {
        cout<<"Dataword"<<endl;
        cout<<"Data recieved successfully"<<endl;
    }
    else
    {
        cout<<"Invalid"<<endl;
        cout<<"Error in data"<<endl;
    }
    return 0;
}