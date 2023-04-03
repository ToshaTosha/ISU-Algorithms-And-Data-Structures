#include <iostream>

template <typename T> class NDArray
{
private:
    T** arr;
    int size_x;
    int size_y;

public:
    NDArray(int i, int j);
    void display();

    void fill_zero();
    void fill_one();
    void fill_rand();

    NDArray<T> operator+(NDArray other);
    NDArray operator-(NDArray other);
    NDArray operator*(NDArray other);
    NDArray operator/(NDArray other);

    NDArray matmul(NDArray other);

    NDArray transposition();

    NDArray mean(int shape);
    T meanAll();

    NDArray min(int shape);
    NDArray max(int shape);

};


template <typename T >
NDArray<T>::NDArray(int i, int j) {

    size_x = i;
    size_y = j;

    arr = new T * [size_x];

    for (int i = 0; i < size_x; i++) {
        arr[i] = new T[size_y];
    }

}
template <typename T >
void NDArray<T>::display() {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
template <typename T >
void NDArray<T>::fill_zero() {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            arr[i][j] = 0;
        }
    }
}
template <typename T >
void NDArray<T>::fill_rand() {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            arr[i][j] = 1 + rand() % 10;
        }
    }
}
template <typename T >
void NDArray<T>::fill_one() {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            arr[i][j] = 1;
        }
    }
}

template <typename T >
NDArray<T> NDArray<T>::transposition() {
    NDArray <T> temp_arr(size_y, size_x);
    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            temp_arr.arr[i][j] = arr[j][i];
        }
    }
    return temp_arr;
}

template <typename T >
NDArray<T> NDArray<T>::operator+(NDArray other) {
    NDArray temp_arr(size_x, size_y);

    if (other.size_y == size_y && other.size_x == size_x)
    {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                temp_arr.arr[i][j] = arr[i][j] + other.arr[i][j];
            }
        }
        return temp_arr;
    }
    else
    {
        throw "size_y != rv.size_y or size_x != rv.size_x";
    }
}

template <typename T >
NDArray<T> NDArray<T>::operator-(NDArray other) {
    NDArray temp_arr(size_x, size_y);

    if (other.size_y == size_y && other.size_x == size_x)
    {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                temp_arr.arr[i][j] = arr[i][j] - other.arr[i][j];
            }
        }
        return temp_arr;
    }
    else
    {
        throw "size_y != rv.size_y or size_x != rv.size_x";
    }
}

template <typename T >
NDArray<T> NDArray<T>::operator*(NDArray other) {
    NDArray temp_arr(size_x, size_y);

    if (other.size_y == size_y && other.size_x == size_x)
    {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                temp_arr.arr[i][j] = arr[i][j] * other.arr[i][j];
            }
        }
        return temp_arr;
    }
    else
    {
        throw "size_y != rv.size_y or size_x != rv.size_x";
    }
}

template <typename T >
NDArray<T> NDArray<T>::operator/(NDArray other) {
    NDArray temp_arr(size_x, size_y);

    if (other.size_y == size_y && other.size_x == size_x)
    {
        for (int i = 0; i < size_x; i++) {
            for (int j = 0; j < size_y; j++) {
                temp_arr.arr[i][j] = arr[i][j] / other.arr[i][j];
            }
        }
        return temp_arr;
    }
    else
    {
        throw "size_y != rv.size_y or size_x != rv.size_x";
    }
}


template <typename T >
NDArray<T> NDArray<T>::matmul(NDArray other)
{
    if (size_y == other.size_x && size_x == other.size_y)
    {
        NDArray temp_arr(this->size_x, other.size_y);
        for (int i = 0; i < size_x; i++)
        {
            for (int j = 0; j < size_y; j++)
            {
                temp_arr.arr[i][j] = 0;
                for (int k = 0; k < size_y; k++)
                {
                    temp_arr.arr[i][j] += arr[i][k] * other.arr[k][j];
                }
            }
        }
        return temp_arr;
    }
    else
    {
        throw "size_y != rv.size_y or size_x != rv.size_x";
    }
}


template <typename T >
NDArray<T> NDArray<T>::mean(int shape)
{
    int value = 0;
    if (shape == 0)
    {
        NDArray temp_arr(1, size_y);
        for (int i = 0; i < size_x; i++)
        {
            value = 0;
            for (int j = 0; j < size_y; j++)
            {
                value += arr[j][i];
            }
            temp_arr.arr[0][i] = value / size_x;
        }
        return temp_arr;
    }
    else if (shape == 1)
    {
        NDArray temp_arr(1, size_x);
        for (int i = 0; i < size_x; i++)
        {
            value = 0;
            for (int j = 0; j < this->size_y; j++)
            {
                value += arr[i][j];
            }
            temp_arr.arr[0][i] = value / size_y;
        }
        return temp_arr;
    }
    else
    {
        NDArray temp_arr(1, size_x);
        temp_arr.fill_zero();
        return temp_arr;
    }

}

template <typename T >
NDArray<T> NDArray<T>::min(int shape)
{
    T min = 0;
    if (shape == 1)
    {
        NDArray temp_arr(1, size_x);
        for (int i = 0; i < size_x; i++)
        {
            min = arr[i][0];
            for (int j = 0; j < size_y; j++)
            {
                if (arr[i][j] <= min) {
                    min = arr[i][j];
                }
            }
            temp_arr.arr[0][i] = min;
        }
        return temp_arr;
    }
    else if (shape == 0)
    {
        NDArray temp_arr(1, size_y);
        for (int i = 0; i < size_y; i++)
        {
            min = arr[0][i];
            for (int j = 0; j < size_x; j++)
            {
                if (arr[j][i] <= min) {
                    min = arr[j][i];
                }
            }
            temp_arr.arr[0][i] = min;
        }
        return temp_arr;
    }
    else
    {
        NDArray temp_arr(1, size_x);
        temp_arr.fill_zero();
        return temp_arr;
    }

}


template <typename T >
NDArray<T> NDArray<T>::max(int shape)
{
    T max = 0;
    if (shape == 1)
    {
        NDArray temp_arr(1, size_x);
        for (int i = 0; i < size_x; i++)
        {
            max = arr[i][0];
            for (int j = 0; j < size_y; j++)
            {
                if (arr[i][j] >= max) {
                    max = arr[i][j];
                }
            }
            temp_arr.arr[0][i] = max;
        }
        return temp_arr;
    }
    else if (shape == 0)
    {
        NDArray temp_arr(1, size_y);
        for (int i = 0; i < size_y; i++)
        {
            max = arr[0][i];
            for (int j = 0; j < size_x; j++)
            {
                if (arr[j][i] >= max) {
                    max = arr[j][i];
                }
            }
            temp_arr.arr[0][i] = max;
        }
        return temp_arr;
    }
    else
    {
        NDArray temp_arr(1, size_x);
        temp_arr.fill_zero();
        return temp_arr;
    }

}

template <typename T >
T NDArray<T>::meanAll()
{
    int value = 0;
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            value += arr[i][j];
        }
    }
    value = value / (size_x + size_y);
    return value;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Создание матрицы 2x3 заполненной 1:\n";
    NDArray <float> a(2, 3);
    a.fill_one();
    a.display();

    std::cout << "Создание матрицы 2x3 заполненной 0:\n";
    NDArray<float> b(2, 3);
    b.fill_zero();
    b.display();
    std::cout << "Создание матрицы 2x2 заполненной случайными числами:\n";
    NDArray <float> c(2, 3);
    c.fill_rand();
    c.display();

    std::cout << std::endl;

    std::cout << "Транспонирование матрицы \n";
    c.transposition().display();

    std::cout << "Операторы поэлементного сложения, вычитания, умножения, деления:\n";
    std::cout << "a+b\n";
    (a + b).display();
    std::cout << "b-a\n";
    (b - a).display();
    std::cout << "b*c\n";
    (b * c).display();
    std::cout << "a/c\n";
    (a / c).display();

    std::cout << std::endl;

    std::cout << "Матричное умножение: " << std::endl;
    NDArray <float> d(2, 3);
    d.fill_rand();
    d.display();
    std::cout << std::endl;
    NDArray <float> e(3, 2);
    e.fill_rand();
    e.display();
    std::cout << std::endl;
    d.matmul(e).display();

    std::cout << std::endl;

    std::cout << "Операции сокращения: минимум, максимум, среднее для определенной размерности\n";
    NDArray <float> g(3, 2);
    g.fill_rand();
    g.display();
    std::cout << std::endl;
    std::cout << "min(0):\n";
    g.min(0).display();
    std::cout << std::endl;
    std::cout << "min(1):\n";
    g.min(1).display();
    std::cout << std::endl;
    std::cout << "max(0):\n";
    g.max(0).display();
    std::cout << std::endl;
    std::cout << "max(1):\n";
    g.max(1).display();
    std::cout << std::endl;
    std::cout << "mean(0):\n";
    g.mean(0).display();
    std::cout << std::endl;
    std::cout << "mean(1):\n";
    g.mean(1).display();
    std::cout << std::endl;
    std::cout << "mean():\n";
    std::cout << g.meanAll();

    return 0;
}
