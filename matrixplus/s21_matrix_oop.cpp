#include "s21_matrix_oop.h"

/**
 * @brief Default constructor and initialize matrix with zeros (0) by default
 * @note This function is not a member of the class
 */
S21Matrix::S21Matrix() : rows_(1), cols_(1) {
    this->CreateMatrix(rows_, cols_);
}

/**
 * @brief Destructor and delete matrix from memory (free memory)
 * @note This function is not a member of the class
 */
S21Matrix::~S21Matrix() { this->DeleteMatrix(); }

/**
 * @brief Allocate memory for matrix (allocate memory for rows and columns) and initialize matrix with zeros (0) by default
 * @param rows number of rows (default = 1)
 * @param cols number of columns (default = 1)
 * @note This function is not a member of the class
 */
void S21Matrix::CreateMatrix(int rows, int cols) {
    this->rows_ = rows;
    this->cols_ = cols;
    this->matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
        this->matrix_[i] = new double[cols_]();
    }
}

/**
 * @brief Delete matrix from memory (free memory) and set rows and columns to zero (0)
 * @note This function is not a member of the class
 */
void S21Matrix::DeleteMatrix() {
    for (int i = 0; i < rows_; ++i) {
        delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->rows_ = 0;
    this->cols_ = 0;
}

/**
 * @brief Constructor with parameters (rows, cols) and initialize matrix with zeros (0) by default
 * @param rows number of rows (default = 1)
 * @param cols number of columns (default = 1)
 * @throws std::invalid_argument if matrix size is invalid (rows < 1 or cols < 1)
 * @note This function is not a member of the class
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows < 1 || cols < 1) {
        throw std::invalid_argument("Invalid matrix size");
    } else {
        this->CreateMatrix(rows, cols);
    }
}

/**
 * @brief Copy constructor and copy matrix from other matrix (copy rows, cols and matrix)
 * @param other matrix to copy
 * @note This function is not a member of the class
 */
S21Matrix::S21Matrix(const S21Matrix &other)
        : rows_(other.rows_), cols_(other.cols_) {
    this->CreateMatrix(other.rows_, other.cols_);
    for (int i = 0; i < other.rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            this->matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

/**
 * @brief Move constructor and move matrix from other matrix (move rows, cols and matrix)
 * @param other matrix to move
 * @note This function is not a member of the class
 */
S21Matrix::S21Matrix(S21Matrix &&other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

/**
 * @brief Compare matrix with matrix (A == B) = true (this == other) = true
 * @param other matrix to compare
 * @return true if matrix are equal, false otherwise
 * @note This function is not a member of the class
 */
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

/**
 * @brief Sum matrix with matrix (A + B) = C (this + other = result)
 * @param other matrix to sum with this matrix (B)
 * @return result of summation (C)
 * @throws std::invalid_argument if matrix sizes are not equal
 * @note This function is not a member of the class
 */
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

/**
 * @brief Subtract matrix from matrix (A - B) = C (this - other = result)
 * @param other matrix to subtract from this matrix (B)
 * @return result of subtraction (C)
 * @throws std::invalid_argument if matrix sizes are not equal
 * @note This function is not a member of the class
 */
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
 * @throw std::invalid_argument if matrix sizes are not equal
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

/**
* @brief Transpose matrix (A^T) = B (this^T = result)
* @return result of transposition (B)
* @note This function is not a member of the class
*/
S21Matrix S21Matrix::Transpose() {
    S21Matrix result(this->cols_, this->rows_);
    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            result.matrix_[j][i] = this->matrix_[i][j];
        }
    }
    return result;
}

/**
 * @brief Calculate determinant of matrix (|A|) = det(A) (this = A) (this = result)
 * @return determinant of matrix (det(A))
 * @throw std::invalid_argument if matrix is not square (rows != cols) or matrix is empty (rows = 0 or cols = 0)
 * @note This function is not a member of the class
 */
double S21Matrix::Determinant() {
    if (this->rows_ != this->cols_ || this->rows_ <= 0 && this->cols_ <= 0) {
        throw std::invalid_argument("Invalid matrix size");
    } else {
        double det = 0;
        if (this->rows_ == 1) {
            det = this->matrix_[0][0];
        } else if (this->rows_ == 2) {
            det = this->matrix_[0][0] * this->matrix_[1][1] - this->matrix_[0][1] * this->matrix_[1][0];
        } else {
            for (int i = 0; i < this->rows_; ++i) {
                S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
                for (int j = 1; j < this->rows_; ++j) {
                    for (int k = 0; k < this->cols_; ++k) {
                        if (k < i) {
                            minor.matrix_[j - 1][k] = this->matrix_[j][k];
                        } else if (k > i) {
                            minor.matrix_[j - 1][k - 1] = this->matrix_[j][k];
                        }
                    }
                }
                det += pow(-1, i) * this->matrix_[0][i] * minor.Determinant();
            }
        }
        return det;
    }
}