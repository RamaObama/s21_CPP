#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() :
        rows_(1),
        cols_(1) {
    this->CreateMatrix(rows_, cols_);
}

S21Matrix::~S21Matrix() {
    DeleteMatrix();
}

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

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
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