#include <iostream>
using namespace std;

int modpower(int a, int b, int m)
{
    if(b == 0) return 1;
    else if (b % 2 == 0)
    {
        int t = modpower(a, b/2, m);
        return (1LL * t * t % m);
    }
    else
    {
        int t = modpower(a, b/2, m);
        t = 1LL * t * t % m;
        return (1LL * a * t % m);
    }
}

int main(int argc, char const *argv[])
{
    int p, g, a, b;
    cout<<"Enter a prime number : ";
    cin>>p;
    cout<<"Enter a primitive key : ";
    cin>>g;
    cout<<"Enter the private key for the first party : ";
    cin>>a;
    cout<<"Enter the private key for the second party : ";
    cin>>b;

    int A = modpower(g, a, p);
    cout<<"Public key shared by the first party : "<<A<<endl;
    int B = modpower(g, b, p);
    cout<<"Public key shared by the second party : "<<B<<endl;
    
    int AA = modpower(B, a, p);
    int BB = modpower(A, b, p);

    cout<<"Shared secret key for the first party : "<<AA<<endl;
    cout<<"Shared secret key for the second party : "<<BB<<endl;
    return 0;
}