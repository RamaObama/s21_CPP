#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument(
        "Invalid matrix dimensions. Rows and columns must be greater than 0.");
  } else {
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  // Allocate memory for the matrix
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    // Copy the elements from the other matrix
    std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  // Reset the other matrix
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  // Deallocate memory for the matrix
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

// Binary addition operator
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrix dimensions are incompatible for addition.");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      // Perform element-wise addition
      result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }

  return result;
}

// Assignment operator
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    // Deallocate current memory
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    // Copy dimensions
    rows_ = other.rows_;
    cols_ = other.cols_;

    if (rows_ <= 0 || cols_ <= 0) {
      throw std::invalid_argument(
          "Invalid matrix dimensions. Rows and columns must be greater than "
          "0.");
    }

    // Allocate memory for the new matrix
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      // Copy the elements from the other matrix
      std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
    }
  }
  return *this;
}
