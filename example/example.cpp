
#include <iostream>
#include "cppath.h"
#include <string>

using namespace std;

int main()
{
    string a = "../../include", b;
    cppath::abspath(b, a);
    cout << a << ' ' << b << endl;
    return 0;
}
