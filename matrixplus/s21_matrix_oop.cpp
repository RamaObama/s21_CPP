#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(1) {
    this->CreateMatrix(rows_, cols_);
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

void S21Matrix::CreateMatrix(int rows, int cols) {
    this->rows_ = rows;
    this->cols_ = cols;
    this->matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
        this->matrix_[i] = new double[cols_]();
    }
}

void S21Matrix::DeleteMatrix() {
    for (int i = 0; i < rows_; ++i) {
        delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->rows_ = 0;
    this->cols_ = 0;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows < 1 || cols < 1) {
        throw std::invalid_argument("Invalid matrix size");
    } else {
        this->CreateMatrix(rows, cols);
    }
}

S21Matrix::S21Matrix(const S21Matrix &other)
        : rows_(other.rows_), cols_(other.cols_) {
    this->CreateMatrix(other.rows_, other.cols_);
    for (int i = 0; i < other.rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            this->matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
        return false;
    } else {
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < this->cols_; ++j) {
                if (std::abs(this->matrix_[i][j] - other.matrix_[i][j]) > EPSILON) {
                    return false;
                }
            }
        }
        return true;
    }
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
        throw std::invalid_argument("Invalid matrix size");
    } else {
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < this->cols_; ++j) {
                this->matrix_[i][j] += other.matrix_[i][j];
            }
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
        throw std::invalid_argument("Invalid matrix size");
    } else {
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < this->cols_; ++j) {
                this->matrix_[i][j] -= other.matrix_[i][j];
            }
        }
    }
}

/**
 * @brief Multiply matrix by number (A * number) = B (this * number = result)
 * @param number to multiply by this matrix (A)
 * @return result of multiplication (B)
 * @note This function is not a member of the class
 */
void S21Matrix::MulNumber(const double number) {
    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            this->matrix_[i][j] *= number;
        }
    }
}

/**
 * @brief Multiply matrix by matrix (matrix multiplication) (A * B) = C (this * other = result)
 * @param other matrix to multiply by this matrix (B)
 * @return result of multiplication (C)
 * @note This function is not a member of the class
 */
void S21Matrix::MulMatrix(const S21Matrix &other) {
    if (this->cols_ != other.rows_) {
        throw std::invalid_argument("Invalid matrix size");
    } else {
        S21Matrix result(this->rows_, other.cols_);
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                for (int k = 0; k < this->cols_; ++k) {
                    result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
                }
            }
        }
        this->DeleteMatrix();
        this->rows_ = result.rows_;
        this->cols_ = result.cols_;
        this->matrix_ = result.matrix_;
        result.rows_ = 0;
        result.cols_ = 0;
        result.matrix_ = nullptr;
    }
}