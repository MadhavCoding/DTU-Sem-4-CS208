#include <iostream>
using namespace std;

string reverse(string s)
{
    string result = s;
    int i = 0, j = s.length() - 1;
    while (i < j)
    {
        swap(result[i], result[j]);
        i++; j--;
    }
    return result;
}

string encode(string dataword)
{
    string dataword1 = reverse(dataword);

    int n = dataword.length();
    int r = 0;
    while ((1 << r) < n + r + 1)
    {
        r++;
    }
    
    string result(n+r, '0');

    int j = 0;
    for (int i = 1; i <= n + r; i++)
    {
        if((i & (i - 1)) == 0)
        {
            result[i-1] = '0';
        }
        else
        {
            result[i-1] = dataword1[j++];
        }
    }
    // return result;
    int ptr = 1;
    while (ptr <= n + r)
    {
        int parity = 0;
        for(int i = 1; i <= n + r; i++) if((i & ptr) == (ptr))
        {
            if(result[i - 1] == '1') parity++;
        }

        if(parity % 2) result[ptr - 1] = '1';

        ptr <<= 1;
    }

    result = reverse(result);
    return result;
}

bool decode(string encoded)
{
    int n = encoded.length();
    string encoded1 = reverse(encoded);

    int ptr = 1;
    while(ptr <= n)
    {
        int parity = 0;
        for(int i = 1; i <= n; i++) if((i & ptr) == (ptr))
        {
            if(encoded1[i - 1] == '1') parity++;
        }

        if(parity % 2) return false;
        ptr <<= 1;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    string dataword;
    cout<<"Enter dataword : ";
    cin>>dataword;

    string encodedData = encode(dataword);
    cout<<"Encoded Data : ";
    cout<<encodedData<<endl;

    bool decoded = decode(encodedData);
    if(decoded)
    {
        cout<<"Correct Data Recieved"<<endl;
    }
    else
    {
        cout<<"Error in Data"<<endl;
    }

    string encodedUser;
    cout<<"Enter Encoded Data : ";
    cin>>encodedUser;

    decoded = decode(encodedUser);
    if(decoded)
    {
        cout<<"Correct Data Recieved"<<endl;
    }
    else
    {
        cout<<"Error in Data"<<endl;
    }
    return 0;
}