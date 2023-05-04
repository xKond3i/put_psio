#pragma once

#include <vector>
#include <iostream>

template <typename T>
class Matrix { // stands for Custom Implementation of Vector
    double columns_;
    double rows_;
    std::vector<std::vector<T>> matrix_;

public:
    Matrix(int rows = 2, int cols = -1) {
        // could add some exception handling - e.g. dimensions can't be 0 or negative
        if (cols < 2) cols = rows;

        rows_ = rows;
        columns_ = cols;

        for (int r = 0; r < rows_; ++r) {
            std::vector<T> row(columns_);        
            matrix_.push_back(row);
        }
    };
    Matrix(const std::vector<std::vector<T>> & data) {
        rows_    = data.size();
        columns_ = data[0].size();
        matrix_  = data;
    };

    static Matrix eye(int rows = 2, int cols = -1) {
        // could add some exception handling - e.g. dimensions can't be 0 or negative
        if (cols < 2) cols = rows;

        Matrix<T> result(rows, cols);

        for (int r = 0; r < rows; ++r) {
            std::vector<T> row(cols, 0);
            row[r] = 1;
            result.matrix_[r] = row;
        }

        return result;
    };

    template <typename FUNC>
    static Matrix fill(int rows, int cols, FUNC func) {
        Matrix<T> result(rows, cols);

        for (int r = 0; r < rows; ++r) {
            std::vector<T> row;
            for (int c = 0; c < cols; ++c) {
                row.push_back(func());
            }
            result.matrix_[r] = row;
        }

        return result;
    }

    friend std::ostream & operator << (std::ostream & str, const Matrix & m) {
        for (int r = 0; r < m.rows_; ++r) {
            if (r == 0) str << "┌ ";
            else if (r == m.rows_ - 1) str << "└ ";
            else str << "│ ";
            for (int c = 0; c < m.columns_; ++c) {
                str << m.matrix_[r][c] << (c < (m.columns_ - 1) ? ", " : "");
            }
            if (r == 0) str << " ┐\n";
            else if (r == m.rows_ - 1) str << " ┘\n";
            else str << " │\n";
        }
        return str;
    }

    friend std::istream & operator >> (std::istream & str, Matrix & m) {
        std::cout << "# MATRIX INPUT #\n";
        std::cout << "- enter number of rows: ";
        str >> m.rows_; // we could handle all invalid input cases, but for sake of simplicity of the example I'll not
        std::cout << "- enter number of columns: ";
        str >> m.columns_; // we could handle all invalid input cases, but for sake of simplicity of the example I'll not

        m.matrix_.clear();
        for (int r = 0; r < m.rows_; ++r) {
            std::vector<T> row(m.columns_);        
            m.matrix_.push_back(row);
        }

        for (int r = 0; r < m.rows_; ++r) {
            std::cout << "> row " << (r+1) << "\n";
            for (int c = 0; c < m.columns_; ++c) {
                std::cout << "- enter value at [" << (r+1) << ", " << (c+1) << "]: ";
                str >> m.matrix_[r][c];
            }
        }

        return str;
    }

    friend Matrix operator * (const Matrix & a, const Matrix & b) {
        if (a.rows_ != b.columns_) throw std::out_of_range("matrices size do not match the operation");

        Matrix<T> result(a.rows_, a.columns_);

        for (int r = 0; r < a.rows_; ++r) {
            for (int c = 0; c < a.columns_; ++c) {
                for (int i = 0; i < a.rows_; ++i) {
                    result.matrix_[r][c] += a.matrix_[r][i] * b.matrix_[i][c];
                }
            }
        }

        return result;
    }

    friend Matrix operator * (const T scalar, const Matrix & m) {
        Matrix<T> result(m.matrix_);

        for (int r = 0; r < m.rows_; ++r) {
            for (int c = 0; c < m.columns_; ++c) {
                result.matrix_[r][c] = m.matrix_[r][c] * scalar;
            }
        }

        return result;
    }

    friend Matrix operator * (const Matrix & m, const T scalar) {
        Matrix<T> result(m.matrix_);

        for (int r = 0; r < m.rows_; ++r) {
            for (int c = 0; c < m.columns_; ++c) {
                result.matrix_[r][c] = m.matrix_[r][c] * scalar;
            }
        }

        return result;
    }

    friend Matrix operator + (const Matrix & m, const T num) {
        Matrix<T> result(m.matrix_);

        for (int r = 0; r < m.rows_; ++r) {
            for (int c = 0; c < m.columns_; ++c) {
                result.matrix_[r][c] = m.matrix_[r][c] + num;
            }
        }

        return result;
    }
};
