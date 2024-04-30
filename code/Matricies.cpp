#include "Matrices.h"
using namespace std;
namespace Matrices
{
    Matrix::Matrix() : rows(0), cols(0) {}
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
    {
        a.resize(_rows, std::vector<double>(_cols, 0.0));
    }

    std::ostream& operator<<(std::ostream& os, const Matrices::Matrix& a)
    {
        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                os << std::setw(10) << a(i, j) << " ";
            }
            os << "\n" << "\n";
        }

        return os;
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix sums(a.getRows(), a.getCols());

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                sums(i, j) = a(i, j) + b(i, j);
            }
        }

        return sums;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (b.getRows() != a.getCols())
        {
            throw std::runtime_error("Error: dimensions must agree");
        }

        Matrix product(a.getRows(), b.getCols());

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int k = 0; k < b.getCols(); ++k)
            {
                double total = 0;
                for (int j = 0; j < a.getCols(); ++j)
                {
                    total += a(i, j) * b(j, k);
                }
                product(i, k) = total;
            }
        }

        return product;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if ((abs(a(i, j) - b(i, j)) > 0.001))
                {
                    return false;
                }
            }
        }

        return true;

    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            return true;
        }

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if ((abs(a(i, j) - b(i, j)) > 0.001))
                {
                    return true;
                }
            }
        }

        return false;

    }

    ////////////////////////////////////////////////////////////////////////

    ///2D rotation matrix
    ///usage:  A = R * A rotates A theta radians counter-clockwise
            ///Call the parent constructor to create a 2x2 matrix
            ///Then assign each element as follows:
            /*
            cos(theta)  -sin(theta)
            sin(theta)   cos(theta)
            */
            ///theta represents the angle of rotation in radians, counter-clockwise
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }

    ///2D scaling matrix
    ///usage:  A = S * A expands or contracts A by the specified scaling factor
            ///Call the parent constructor to create a 2x2 matrix
            ///Then assign each element as follows:
            /*
            scale   0
            0       scale
            */
            ///scale represents the size multiplier
 
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;
    }


    ///2D Translation matrix
    ///usage:  A = T + A will shift all coordinates of A by (xShift, yShift)
 
            ///Call the parent constructor to create a 2xn matrix
            ///Then assign each element as follows:
            /*
            xShift  xShift  xShift  ...
            yShift  yShift  yShift  ...
            */
            ///paramaters are xShift, yShift, and nCols
            ///nCols represents the number of columns in the matrix
            ///where each column contains one (x,y) coordinate pair
            
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int i = 0; i<nCols; i++)
        {
            a[0][i] = xShift;
            a[1][i] = yShift;
        }
    }
 
}

