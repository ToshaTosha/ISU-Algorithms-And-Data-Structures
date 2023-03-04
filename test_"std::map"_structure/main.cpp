#include <iostream>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <time.h>

int main()
{
    srand((unsigned)time(0));

    int n = 1;
    std::ofstream out("out.txt");
    for (int i = 0; i < 7; i++) {
        double start = clock();
        n *= 10;
        std::map<int, int> counter{};
        for (int j = 0; j < n; j++) {
            counter[j] = rand() % n;
        }

        int time = (clock() - start)*1000;
        out << time << " " << sizeof(counter) + 2 * n * sizeof(int) << std::endl;
        //std::cout "Time: " << time << " Memory: " << sizeof(counter) + 2 * n * sizeof(int) << << std::endl;
    }

    return 0;
}



//with open('file.txt', 'a', encoding='UTF-8') as file:
//    file.write(str(n) + ' ' + str(elapsed))