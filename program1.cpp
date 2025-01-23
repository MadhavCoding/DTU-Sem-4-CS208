#include <iostream>
using namespace std;

string BitStuffing(string inputString)
{
    // Add a 0 on encountering 5 consecutive 1s
    string bitStuffing;
    int k = 0;

    for (int i = 0; i < inputString.size(); i++)
    {
        bitStuffing += inputString[i];
        if(inputString[i] == '1') k++;
        else k = 0;
        
        if(k == 5) bitStuffing += '0';
    }

    return bitStuffing;
}

string ByteStuffing(string inputString)
{
    string byteStuffing = "";
    string escape = "10010100";
    string flag = "00001000";
    byteStuffing += flag;

    for(int i = 0; i < inputString.size(); i++)
    {
        int j = i;
        if(inputString.substr(i, 8) == flag || inputString.substr(i, 8) == escape)
        {
            byteStuffing += escape;
            byteStuffing += inputString.substr(i, 8);
            i += 7;
        }
        else
        {
            byteStuffing += inputString[i];
        }
    }

    byteStuffing += flag;

    return byteStuffing;
}

string CharacterStuffing(string inputString)
{
    string characterStuffing = "";
    string escape = "10010100";
    string flag = "00001000";
    characterStuffing += 'F';

    for(int i = 0; i < inputString.size(); i++)
    {
        int j = i;
        if(inputString.substr(i, 8) == flag || inputString.substr(i, 8) == escape)
        {
            characterStuffing += 'E';
            characterStuffing += inputString.substr(i, 8);
            i += 7;
        }
        else
        {
            characterStuffing += inputString[i];
        }
    }

    characterStuffing += 'F';

    return characterStuffing;
}

int main(int argc, char const *argv[])
{
    string inputString;
    cout<<"Enter a string : ";
    cin>>inputString;

    string bitStuffing = BitStuffing(inputString);
    string byteStuffing = ByteStuffing(inputString);
    string characterStuffing = CharacterStuffing(inputString);

    cout<<"Bit Stuffing : "<<bitStuffing<<endl;
    cout<<"Byte Stuffing : "<<byteStuffing<<endl;
    cout<<"Character Stuffing : "<<characterStuffing<<endl;
    
    return 0;
}