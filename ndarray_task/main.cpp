#include <iostream>
#include <vector>
#include <random>
#define  num(row,col)  ((col) + (row)*j)
using namespace std;

template <typename T> class NDArray {
private:
    T* arr;
    int size;
    int i, j;
public:
    void create() {
        arr = new T[i * j];
    }
    int normalize_index(int x, int y)
    {
        return (x * i + y);
    }

    NDArray(int _i, int _j = 1) {
        i = _i;
        j = _j;
        if (i < 0 || j < 0) {
            throw invalid_argument("Значение строки или столбца не может быть меньше нуля");
        }
        size = i * j;
    }
    // Создание пустого массива заданного размера
    NDArray(vector<T> vec, int _i, int _j = 1) {
        i = _i;
        j = _j;
        size = i * j;
        if (i < 0 || j < 0) {
            throw invalid_argument("Значение строки или столбца не может быть меньше нуля");
        }
        create();
        int k = 0;
        for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it) {
            arr[k] = *it;
            k++;
        }
    }
    void display() {
        for (int x = 0; x < j; x++)
        {
            for (int y = 0; y < i; y++)
            {
                cout << arr[i * x + y] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    // Создание массива заполненного нулями  
    void fill_zero() {
        create();
        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
    }
    //Создание массива заполненного единицами
    void fill_one() {
        create();
        for (int i = 0; i < size; i++) {
            arr[i] = 1;
        }
    }
    // Создание массива заполненного случайными значениям
    void fill_rand() {
        create();
        for (int i = 0; i < size; i++) {
            arr[i] = 1 + rand() % 10;
        }
    }

    // Операторы поэлементного сложения, вычитания, умножения, деления

    NDArray _operator(char oper, NDArray<T> other)
    {
        NDArray<T> temp_arr(i, j);
        temp_arr.fill_zero();
        if (other.i == i && other.j == j)
        {
            for (int x = 0; x < size; x++)
            {
                switch (oper)
                {
                case '+':
                    temp_arr.arr[x] = arr[x] + other.arr[x];
                    break;
                case '-':
                    temp_arr.arr[x] = arr[x] - other.arr[x];
                    break;
                case '/':
                    temp_arr.arr[x] = arr[x] / other.arr[x];
                    break;
                case '*':
                    temp_arr.arr[x] = arr[x] * other.arr[x];
                    break;
                case '=':
                    arr[x] = other.arr[x];
                    break;
                default:
                    throw invalid_argument("Неизвестный оператор");
                    break;
                }
            }

            return temp_arr;
        }
        else
        {
            throw invalid_argument("Матрицы должны быть одинакового размера.");
        }
    }

    NDArray operator +(NDArray<T> other)
    {
        return _operator('+', other);
    }

    NDArray operator -(NDArray<T> other)
    {
        return _operator('-', other);
    }

    NDArray operator *(NDArray<T> other)
    {
        return _operator('*', other);
    }
    NDArray operator /(NDArray<T> other)
    {
        return _operator('/', other);
    }
    // получение элемента из массива по индексу
    T operator[](int index) {
        return arr[index];
    }
    //Метод для транспонирования
    NDArray transposition()
    {
        NDArray new_arr(j, i);
        new_arr.fill_zero();
        for (int x = 0; x < i; ++x) {
            for (int y = 0; y < j; ++y)
                new_arr.arr[y * i + x] = arr[x * j + y];
        }
        return new_arr;
    }
    //Матричное умножение

    NDArray matmul(NDArray other)
    {
        if (j == other.i && i == other.j)
        {
            NDArray new_arr(j, j);
            new_arr.create();
            int value = 0;
            for (int x = 0; x < j; ++x)
            {
                for (int y = 0; y < j; ++y)
                {
                    value = 0;
                    for (int k = 0; k < i; ++k)
                    {
                        value += arr[normalize_index(x, k)] * other.arr[num(k, y)];
                    }

                    new_arr.arr[num(x, y)] = value;
                }
            }

            return new_arr;
        }
        else
        {
            throw "other size!";
        }
    }

    // Операции сокращения: минимум, максимум, среднее для определенной размерности
    NDArray min(int shape)
    {
        T min = 0;
        vector<T> vec;

        if(shape == 0)
        {
            for (int x = 0; x < i; x++)
            {
                min = arr[normalize_index(0, x)];
                for (int y = 0; y < j; y++)
                {
                    if (arr[normalize_index(y, x)] < min)
                    {
                        min = arr[normalize_index(y, x)];
                    }
                }
                vec.push_back(min);
            }
            NDArray<T> new_arr(vec, i, 1);
            return new_arr;
        }
        else
        {
            for (int x = 0; x < j; x++)
            {
                min = arr[normalize_index(x, 0)];
                for (int y = 0; y < i; y++)
                {
                    if (arr[normalize_index(x, y)] < min)
                    {
                        min = arr[normalize_index(x, y)];
                    }
                }
                vec.push_back(min);
            }
            NDArray<T> new_arr(vec, j, 1);
            return new_arr;
        }
    }
    NDArray max(int shape)
    {
        T max = 0;
        vector<T> vec;
        if (shape == 0)
        {
            for (int x = 0; x < i; x++)
            {
                max = arr[normalize_index(0, x)];
                for (int y = 0; y < j; y++)
                {
                    if (arr[normalize_index(y, x)] > max)
                    {
                        max = arr[normalize_index(y, x)];
                    }
                }
                vec.push_back(max);
            }
            NDArray<T> new_arr(vec, i, 1);
            return new_arr;
        }
        else
        {
            for (int x = 0; x < j; x++)
            {
                max = arr[normalize_index(x, 0)];
                for (int y = 0; y < i; y++)
                {
                    if (arr[normalize_index(x, y)] > max)
                    {
                        max = arr[normalize_index(x, y)];
                    }
                }
                vec.push_back(max);
            }
            NDArray<T> new_arr(vec, j, 1);
            return new_arr;
        }
    }
    NDArray mean(int shape)
    {
        vector<T> vec;
        T value = 0;
        if (shape == 0)
        {
            for (int x = 0; x < i; x++)
            {
                value = 0;
                for (int y = 0; y < j; y++)
                {
                    value += arr[normalize_index(y, x)];
                }
                vec.push_back(value / T(j));
            }
            NDArray<T> new_arr(vec, i, 1);
            return new_arr;
        }
        else
        {
            if (shape == 1)
            {
                for (int x = 0; x < j; x++)
                {
                    value = 0;
                    for (int y = 0; y < i; y++)
                    {
                        value += arr[normalize_index(x, y)];
                    }
                    vec.push_back(value / T(i));
                }
                NDArray<T> new_arr(vec, j, 1);
                return new_arr;
            }
            else
            {
                throw invalid_argument("Не поддерживается");
            }
        }
    }
    T meanAll()
    {
        vector<T> vec;
        T value = 0;
        for (int x = 0; x < i; x++)
        {
            for (int y = 0; y < j; y++)
            {
                value += arr[normalize_index(y, x)];
            }
        }
        T mean = value / size;
        return mean;

    };
    
};

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Создание матрицы 2x3 заполненной 1:\n";
    NDArray <float> a(2, 3);
    a.fill_one();
    a.display();
    cout << "Создание матрицы 2x3 заполненной 0:\n";
    NDArray<float> b(2, 3);
    b.fill_zero();
    b.display();
    cout << "Создание матрицы 2x2 заполненной случайными числами:\n";
    NDArray <float> c(2, 3);
    c.fill_rand();
    c.display();

    cout << endl;

    cout << "Транспонирование матрицы \n";
    c.transposition().display();

    cout << "Операторы поэлементного сложения, вычитания, умножения, деления:\n";
    cout << "a+b\n";
    (a + b).display();
    cout << "b-a\n";
    (b - a).display();
    cout << "b*c\n";
    (b * c).display();
    cout << "a/c\n";
    (a / c).display();

    cout << endl;

    cout << "Матричное умножение: " << endl;
    c.matmul(a.transposition()).display();

    cout << endl;

    cout << "Операции сокращения: минимум, максимум, среднее для определенной размерности\n";
    NDArray <int> d({ 0,1,2,3,4,5 }, 2, 3);
    d.display();
    cout << "min(0):\n";
    d.min(0).display();
    cout << "min(1):\n";
    d.min(1).display();
    cout << "max(0):\n";
    d.max(0).display();
    cout << "max(1):\n";
    d.max(1).display();
    cout << "mean(0):\n";
    d.mean(0).display();
    cout << "mean(1):\n";
    d.mean(1).display();
    NDArray <float> d2({ 0,1,2,3,4,5 }, 2, 3);
    d2.display();
    cout << "mean(0):\n";
    d2.mean(0).display();
    cout << "mean(1):\n";
    d2.mean(1).display();
    cout << "mean():\n";
    cout << d2.meanAll();

    return 0;
}