
#include <iostream>
#include <math.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;

int main(int argc, char* argw[])
{
    //int n;
    int n = stoi(argw[1]);
    //
    //cin >> n;
    srand((unsigned int)time(NULL));

    std::ofstream out;          
    out.open("./answer.txt");
    
    if (out.is_open())
    {
        for (int i = 0; i < n; i++) {   
            for (int j = 0; j < 3; j++) {
                double randnum = rand()%628;
                double num = (randnum - 314)/100;
                cout << num << " ";
                out << num << " ";
            }
            out << '\n';
            cout << '\n';
        }
    }

    
}
