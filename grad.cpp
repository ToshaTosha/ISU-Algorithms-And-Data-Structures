
#include <iostream>
#include <math.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    std::string line;
    int x, y, z;

    std::ifstream in("./answer.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            sscanf(line.c_str(), "%d %d %d", &x, &y, &z);
            float angle = 2 * sin(x) * sin(y) + cos(z);
            cout << angle << endl;
        }
    }
    in.close();

}
