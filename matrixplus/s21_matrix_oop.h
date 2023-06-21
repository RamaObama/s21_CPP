/**
 * @file s21_matrix_oop.h
 * @author Ramin Rasuli (S21: deltajed) (deltajed@student.21-school.ru)
 * @brief Definition of the S21Matrix class and matrix operations.
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef S21_CPP_S21_MATRIX_OOP_H
#define S21_CPP_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>

#define EPSILON 1e-6

/**
 * @class S21Matrix
 * @brief A matrix class that supports various matrix operations.
 */
class S21Matrix {
 private:
  int rows_;         ///< Number of rows in the matrix
  int cols_;         ///< Number of cols in the matrix
  double **matrix_;  ///< Pointer to the memory where the matrix is allocated

  void AllocateMemory();

  void CreateMatrix(int rows, int cols);

  void DeleteMatrix();

 public:
  /**
   * @brief Defualt constructor.
   * Create an empty matrix.
   *
   */
  S21Matrix();

  /**
   * @brief Parametrized constructor.
   * Creates a matrix with the specified dimensions.
   *
   * @param rows Number of rows in the matrix
   * @param cols Number of cols in the matrix
   */
  S21Matrix(int rows, int cols);

  /**
   * @brief Copy constructor.
   * Creates a copy of the given matrix.
   *
   * @param other The matrix to be copied
   */
  S21Matrix(const S21Matrix &other);

  /**
   * @brief Move constructor.
   * Moves the data from the given matrix to construct a new matrix.
   *
   * @param other The matrix to be moved
   */
  S21Matrix(S21Matrix &&other) noexcept;

  /**
   * @brief Destructor.
   * Deallocates the memory occupied by the matrix.
   *
   */
  ~S21Matrix();

  // Operators
  /**
   * @brief Assignment operator.
   * Asssigns the values from one matrix to another.
   *
   * @param other The matrix to be assigned
   * @return Reference to the updated matrix
   */
  S21Matrix &operator=(const S21Matrix &other);

  /**
   * @brief
   *
   * @param other
   * @return S21Matrix&
   */
  S21Matrix &operator=(S21Matrix &&other);  // Move assignment operator

  /**
   * @brief Binary additions operator. Adds two matrices.
   *
   * @param other The matrix to be added
   * @return The sum of the two matrices
   * @throws std::invalid_argument if the matrix dimensions are incompatible for
   * addition
   */
  S21Matrix operator+(const S21Matrix &other) const;

  /**
   * @brief Binary subtraction operator.
   * Substracts one matrix from another.
   *
   * @param other The matrix to be substracted
   * @return The difference of the two matrices
   * @throws std::invalid_argumengt if the matrix dimensions are incompatible
   * for subtraction
   */
  S21Matrix operator-(const S21Matrix &other) const;

  /**
   * @brief Binary multiplication operator.
   * Multiplies two matrices.
   *
   * @param other The matrix to be multiplied
   * @return The product of the two matrices
   * @throws std::invalid_argument if the matrix dimensions are incompatible for
   * multiplication
   */
  S21Matrix operator*(const S21Matrix &other) const;

  /**
   * @brief Unary multiplication operator.
   * Multiplies the matrix by a scalar.
   *
   * @param num The scalar to be multiplied
   * @return The matrix multiplied by the scalar
   */
  S21Matrix operator*(double num) const;

  /**
   * @brief Equality operator.
   * Checks if two matrices are equal.
   *
   * @param other The matrix to be compared
   * @return True if the matrices are equal, false otherwise
   */
  bool operator==(const S21Matrix &other) const;

  /**
   * @brief Indexing operator.
   * Accesses the element at the specified row and column.
   *
   * @param i The row inedex
   * @param j The column index
   * @return Reference to the element at the specified position
   * @throws std::out_of_range if the indeces are out of ragne
   */
  double &operator()(int i, int j);

  /**
   * @brief Constand indexing operator.
   * Accesses the element at the specified row and column (read-only).
   *
   * @param i The row index
   * @param j The column index
   * @return The element at the specified position
   * @throws std::out_of_range if thje indices are out of range
   */
  const double &operator()(int i, int j) const;

  bool EqMatrix(const S21Matrix &other);  // Check if two matrices are equal

  /**
   * @brief Adds the elements of another matrix to the current matrix.
   *
   * @param other The matrix to be added
   * @throws std::invalid_argument if the matrix dimensions are incompatible for
   * subraction
   */
  void SumMatrix(const S21Matrix &other);

  /**
   * @brief Subtracts the elemetns of another matrix frim the current matrix.
   *
   * @param other The matrix to be subtracted
   * @throws std::invalid_argument if the matrix dimensions are incompatible for
   * subtraction
   */
  void SubMatrix(const S21Matrix &other);

  /**
   * @brief Multiplies the current matrix by a scalar.
   *
   * @param number The scalar to be multiplied
   */
  void MulNumber(const double number);

  /**
   * @brief Multiplies the current matrix by another matrix.
   *
   * @param other The matrix to be multiplied
   * @throws std::invalid_argument if the matrix dimensions are incompatible for
   * multiplication
   */
  void MulMatrix(const S21Matrix &other);

  /**
   * @brief Creates a new matrix that is the transpose of the current matrix.
   *
   * @return The transposed matrix
   */
  S21Matrix Transpose() const;

  /**
   * @brief Calculates the algebraic addition matrix of the current matrix.
   *
   * @return The algebraic addition matrix
   * @throws std::invalid_argument if the matrix is not square
   */
  S21Matrix CalcComplements() const;

  /**
   * @brief Calculates the determinant of the current matrix.
   *
   * @return The determinant of the matrix
   * @throws std::invalid_argument if the matrix is not square
   */
  double Determinant() const;

  /**
   * @brief Calculates the inverse matrix of the current matrix.
   *
   * @return The inverse matrix
   * @throws std::invalid_argument if the matrix determinant is zero
   */
  S21Matrix InverseMatrix() const;

  void SetRows(const int &rows);  // Set number of rows

  void SetCols(const int &cols);  // Set number of columns
};

#endif  // S21_CPP_S21_MATRIX_OOP_H