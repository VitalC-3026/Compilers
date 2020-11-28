#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 2) {
        cout << argv[1] << endl;
    }
    if (argc == 3) {
        cout << argv[1] << " " << argv[2] << endl;
    }
}