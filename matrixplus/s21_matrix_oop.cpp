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
}