#include <cassert>
#include <iostream>

using namespace std;

class matr;

class vect {
private:
    int dim;   // Размерность вектора
    double* b; // Динамический массив для хранения элементов вектора
    int num;   // Номер объекта
    static int count; // Количество объектов класса

public:
    // Конструкторы
    // Конструктор по умолчанию
    vect() : dim(0), b(nullptr), num(++count) {}

    // Конструктор заданной размерности с нулевыми элементами
    vect(int dimension) : dim(dimension), b(new double[dimension]), num(++count) {
        for (int i = 0; i < dimension; ++i) {
            b[i] = 0.0;
        }
    }
    // Конструктор из динамического массива
    vect(double* array, int dimension)
        : dim(dimension), b(new double[dimension]), num(++count) {
        for (int i = 0; i < dimension; ++i) {
            b[i] = array[i];
        }
    }

    // Конструктор копирования
    vect(const vect& other)
        : dim(other.dim), b(new double[other.dim]), num(++count) {
        for (int i = 0; i < other.dim; ++i) {
            b[i] = other.b[i];
        }
    }

    // Деструктор
    ~vect() { delete[] b; }

    // Методы
    // Вывод информации о векторе
    void print() const {
        std::cout << "Vector " << num << " (dim=" << dim << "): [";
        for (int i = 0; i < dim; ++i) {
            std::cout << b[i];
            if (i < dim - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    // Операторы
    vect& operator=(const vect& other) {
        if (this != &other) {
            delete[] b;
            dim = other.dim;
            b = new double[dim];
            for (int i = 0; i < dim; ++i) {
                b[i] = other.b[i];
            }
        }
        return *this;
    }

    friend vect operator+(const vect& lhs, const vect& rhs);
    friend vect operator-(const vect& lhs, const vect& rhs);
    friend vect operator-(const vect& v);
    friend double operator*(const vect& lhs,
        const vect& rhs); // Скалярное умножение
    friend vect operator*(const vect& v, double k);
    friend vect operator*(double k, const vect& v);
    friend vect operator*(const matr& m,
        const vect& v); // Умножение матрицы на вектор
};

vect operator+(const vect& lhs, const vect& rhs) {
    assert(lhs.dim == rhs.dim);
    vect result(lhs.dim);
    for (int i = 0; i < lhs.dim; ++i) {
        result.b[i] = lhs.b[i] + rhs.b[i];
    }
    return result;
}

vect operator-(const vect& lhs, const vect& rhs) {
    assert(lhs.dim == rhs.dim);
    vect result(lhs.dim);
    for (int i = 0; i < lhs.dim; ++i) {
        result.b[i] = lhs.b[i] - rhs.b[i];
    }
    return result;
}

vect operator-(const vect& v) {
    vect result(v.dim);
    for (int i = 0; i < v.dim; ++i) {
        result.b[i] = -v.b[i];
    }
    return result;
}

double operator*(const vect& lhs, const vect& rhs) {
    assert(lhs.dim == rhs.dim);
    double sum = 0.0;
    for (int i = 0; i < lhs.dim; ++i) {
        sum += lhs.b[i] * rhs.b[i];
    }
    return sum;
}

vect operator*(const vect& v, double k) {
    vect result(v.dim);
    for (int i = 0; i < v.dim; ++i) {
        result.b[i] = v.b[i] * k;
    }
    return result;
}

vect operator*(double k, const vect& v) { return v * k; }

int vect::count = 0;

class matr {
private:
    int dim1, dim2; // Размерности матрицы
    double** b; // Динамический массив для хранения элементов матрицы
    int num;    // Номер объекта
    static int count; // Количество объектов класса

public:
    // Конструктор по умолчанию
    matr() : dim1(0), dim2(0), b(nullptr), num(++count) {}

    // Конструктор заданных размерностей с нулевыми элементами
    matr(int dimension1, int dimension2)
        : dim1(dimension1), dim2(dimension2), num(++count) {
        b = new double* [dim1];
        for (int i = 0; i < dim1; ++i) {
            b[i] = new double[dim2]();
        }
    }

    // Конструктор из динамического массива
    matr(double** array, int dimension1, int dimension2)
        : dim1(dimension1), dim2(dimension2), num(++count) {
        b = new double* [dim1];
        for (int i = 0; i < dim1; ++i) {
            b[i] = new double[dim2];
            for (int j = 0; j < dim2; ++j) {
                b[i][j] = array[i][j];
            }
        }
    }

    // Конструктор копирования
    matr(const matr& other) : dim1(other.dim1), dim2(other.dim2), num(++count) {
        b = new double* [dim1];
        for (int i = 0; i < dim1; ++i) {
            b[i] = new double[dim2];
            for (int j = 0; j < dim2; ++j) {
                b[i][j] = other.b[i][j];
            }
        }
    }

    // Деструктор
    ~matr() {
        for (int i = 0; i < dim1; ++i) {
            delete[] b[i];
        }
        delete[] b;
    }

    // Методы
    void print() const {
        for (int i = 0; i < dim1; ++i) {
            for (int j = 0; j < dim2; ++j) {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }
    }
    // Операторы
    matr& operator=(const matr& other) {
        if (this != &other) {
            for (int i = 0; i < dim1; ++i) {
                delete[] b[i];
            }
            delete[] b;

            dim1 = other.dim1;
            dim2 = other.dim2;
            b = new double* [dim1];
            for (int i = 0; i < dim1; ++i) {
                b[i] = new double[dim2];
                for (int j = 0; j < dim2; ++j) {
                    b[i][j] = other.b[i][j];
                }
            }
        }
        return *this;
    }

    friend matr operator+(const matr& lhs, const matr& rhs);
    friend matr operator-(const matr& lhs, const matr& rhs);
    friend matr operator-(const matr& m);
    friend matr operator*(const matr& lhs, const matr& rhs); // Умножение матриц
    friend matr operator*(const matr& m, double k);
    friend matr operator*(double k, const matr& m);
    friend vect operator*(const matr& m,
        const vect& v); // Умножение матрицы на вектор
};

matr operator+(const matr& lhs, const matr& rhs) {
    assert(lhs.dim1 == rhs.dim1 && lhs.dim2 == rhs.dim2);
    matr result(lhs.dim1, lhs.dim2);
    for (int i = 0; i < lhs.dim1; ++i) {
        for (int j = 0; j < lhs.dim2; ++j) {
            result.b[i][j] = lhs.b[i][j] + rhs.b[i][j];
        }
    }
    return result;
}

matr operator-(const matr& lhs, const matr& rhs) {
    assert(lhs.dim1 == rhs.dim1 && lhs.dim2 == rhs.dim2);
    matr result(lhs.dim1, lhs.dim2);
    for (int i = 0; i < lhs.dim1; ++i) {
        for (int j = 0; j < lhs.dim2; ++j) {
            result.b[i][j] = lhs.b[i][j] - rhs.b[i][j];
        }
    }
    return result;
}

matr operator-(const matr& m) {
    matr result(m.dim1, m.dim2);
    for (int i = 0; i < m.dim1; ++i) {
        for (int j = 0; j < m.dim2; ++j) {
            result.b[i][j] = -m.b[i][j];
        }
    }
    return result;
}

matr operator*(const matr& lhs, const matr& rhs) {
    assert(lhs.dim2 == rhs.dim1);
    matr result(lhs.dim1, rhs.dim2);
    for (int i = 0; i < lhs.dim1; ++i) {
        for (int j = 0; j < rhs.dim2; ++j) {
            result.b[i][j] = 0;
            for (int k = 0; k < lhs.dim2; ++k) {
                result.b[i][j] += lhs.b[i][k] * rhs.b[k][j];
            }
        }
    }
    return result;
}

matr operator*(const matr& m, double k) {
    matr result(m.dim1, m.dim2);
    for (int i = 0; i < m.dim1; ++i) {
        for (int j = 0; j < m.dim2; ++j) {
            result.b[i][j] = m.b[i][j] * k;
        }
    }
    return result;
}

matr operator*(double k, const matr& m) { return m * k; }

vect operator*(const matr& m, const vect& v) {
    if (v.dim == 0) {
        cerr << "Error: Cannot multiply matrix by zero-dimensional vector." << endl;
        return vect(); // Возвращаем пустой вектор или выбрасываем исключение
    }
    assert(m.dim2 == v.dim);
    vect result;
    result.dim = m.dim1;
    result.b = new double[result.dim];
    for (int i = 0; i < m.dim1; ++i) {
        result.b[i] = 0;
        for (int j = 0; j < m.dim2; ++j) {
            result.b[i] += m.b[i][j] * v.b[j];
        }
    }
    return result;
}

int matr::count = 0;

int main() {
    vect v1;
    v1.print();

    vect v2(3);
    v2.print();

    double arr[] = { 1.0, 2.0, 3.0 };
    vect v3(arr, 3);
    v3.print();

    vect v4 = v3;
    v4.print();

    vect v5;
    v5 = v4;
    v5.print();

    vect v6 = v2 + v3;
    v6.print();

    vect v7 = v3 - v2;
    v7.print();

    vect v8 = -v3;
    v8.print();

    double dot_product = v3 * v4;
    cout << "Dot product of Vector 3 and Vector 4: " << dot_product << endl;

    vect v9 = v3 * 2.0;
    v9.print();

    vect v10 = 0.5 * v3;
    v10.print();

    matr mat1(3, 3);

    double** array = new double* [3];
    for (int i = 0; i < 3; ++i) {
        array[i] = new double[3];
        for (int j = 0; j < 3; ++j) {
            array[i][j] = i * 3 + j + 1;
        }
    }

    matr mat2(array, 3, 3);

    for (int i = 0; i < 3; ++i) {
        delete[] array[i];
    }
    delete[] array;

    matr mat3 = mat2;

    cout << "Matrix 1:" << endl;
    mat1.print();
    cout << "Matrix 2:" << endl;
    mat2.print();
    cout << "Matrix 3:" << endl;
    mat3.print();

    matr sum = mat2 + mat3;
    cout << "Sum of Matrix 2 and Matrix 3:" << endl;
    sum.print();

    matr diff = mat3 - mat2;
    cout << "Difference of Matrix 3 and Matrix 2:" << endl;
    diff.print();

    matr prod = mat2 * 2.0;
    cout << "Matrix 2 multiplied by 2:" << endl;
    prod.print();

    prod = 2.0 * mat2;
    cout << "2 multiplied by Matrix 2:" << endl;
    prod.print();

    matr mult = mat2 * mat3;
    cout << "Product of Matrix 2 and Matrix 3:" << endl;
    mult.print();

    vect result = mat2 * v3;
    cout << "Product of Matrix 2 and vector v:" << endl;
    result.print();

    result = mat2 * v1; //специально на пустой чтоб показать assert fail
    cout << "Product of Matrix 2 and vector v:" << endl;
    result.print();

    return 0;
}

