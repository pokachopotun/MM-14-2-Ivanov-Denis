#ifndef MATHADDITIONALS_H
#define MATHADDITIONALS_H
#include <vector>
#include <iostream>


class Matrix : public std::vector< std::vector<double> >
{

public:

    Matrix(int height = 0, int width = 0, double val = 0.0, bool diagonal = false);
    Matrix(const Matrix&) = default;
    Matrix& operator = (const Matrix&) = default;
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix getInverse();
    int rows() const {return rows_;}
    int cols() const {return cols_;}
private:
    int rows_, cols_;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);

std::istream& operator>>(std::istream& is, Matrix& mat);
std::ostream& operator<<(std::ostream& os, const Matrix& mat);


class Polynom : public std::vector<double>
{
public:
    Polynom(int length = 0, double value = 0.0);
    Polynom(const Polynom&) = default;
    Polynom& operator =(const Polynom&) = default;
    Polynom& operator+=(const Polynom& rhs);
    Polynom& operator-=(const Polynom& rhs);
    double getValue(double x);

};

Polynom operator+(const Polynom& lhs, const Polynom& rhs);
Polynom operator-(const Polynom& lhs, const Polynom& rhs);
Polynom operator*(const Polynom& lhs, const Polynom& rhs);
Polynom operator*(const double& lhs, const Polynom& rhs);
Polynom operator*(const Polynom& lhs, const double& rhs);

std::istream& operator>>(std::istream& is, Polynom& mat);
std::ostream& operator<<(std::ostream& os, const Polynom& mat);


#endif // MATHADDITIONALS_H
