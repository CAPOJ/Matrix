#include "s21_matrix.h"

int is_correct(matrix_t *matrix) {
  int res_code = 0;
  if ((matrix != NULL) && (matrix->matrix != NULL) && (matrix->rows >= 1) &&
      (matrix->columns >= 1)) {
    res_code = 1;
    for (int i = 0; i < matrix->rows; i++) {
      for (int j = 0; j < matrix->columns; j++) {
        if (isnan(matrix->matrix[i][j]) || isinf(matrix->matrix[i][j])) {
          res_code = 0;
        }
      }
    }
  }
  return res_code;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res_code = OK;

  if (rows < 1 || columns < 1) {
    res_code = INCORRECT_MATRIX;
    result->matrix = NULL;
  } else if (result == NULL) {
    res_code = INCORRECT_MATRIX;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          result->rows = i;
          s21_remove_matrix(result);
          fprintf(stderr, "not enough memory (calloc returned NULL)\n");
          res_code = CALLOC_ERROR;
          i = rows;
        }
      }
    } else {
      res_code = CALLOC_ERROR;
    }
  }

  if (res_code == OK) {
    result->rows = rows;
    result->columns = columns;
  }

  return res_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
  }
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res_code = SUCCESS;

  if (is_correct(A) && is_correct(B) && (A->rows == B->rows) &&
      (A->columns == B->columns)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-6) {
          res_code = FAILURE;
        }
      }
    }
  } else {
    res_code = FAILURE;
  }

  return res_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res_code = OK;

  if (!is_correct(A) || !is_correct(B)) {
    res_code = INCORRECT_MATRIX;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res_code = CALC_ERROR;
  } else {
    res_code = s21_create_matrix(A->rows, A->columns, result);
    if (res_code == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }

  return res_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res_code = OK;

  if (!is_correct(A) || !is_correct(B)) {
    res_code = INCORRECT_MATRIX;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res_code = CALC_ERROR;
  } else {
    res_code = s21_create_matrix(A->rows, A->columns, result);
    if (res_code == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }

  return res_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res_code = OK;

  if (is_correct(A)) {
    res_code = s21_create_matrix(A->rows, A->columns, result);
    if (res_code == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    res_code = INCORRECT_MATRIX;
  }

  return res_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res_code = OK;

  if (!is_correct(A) || !is_correct(B)) {
    res_code = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    res_code = CALC_ERROR;
  } else if ((res_code = s21_create_matrix(A->rows, B->columns, result)) ==
             OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }

  return res_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res_code = OK;

  if (is_correct(A)) {
    res_code = s21_create_matrix(A->columns, A->rows, result);
    if (res_code == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    res_code = INCORRECT_MATRIX;
  }

  return res_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res_code = OK;

  if (!is_correct(A)) {
    res_code = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res_code = CALC_ERROR;
  } else if (A->rows == 1) {
    res_code = s21_create_matrix(1, 1, result);
    if (res_code == OK) {
      result->matrix[0][0] = 1;
    }
  } else if ((res_code = s21_create_matrix(A->rows, A->columns, result)) ==
             OK) {
    matrix_t temp_matrix = {0};

    res_code = s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matrix);
    if (res_code == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_get_minor(A, i, j, &temp_matrix);
          double number = 0;
          s21_determinant(&temp_matrix, &number);
          result->matrix[i][j] = pow(-1, i + 1 + j + 1) * number;
        }
      }
      s21_remove_matrix(&temp_matrix);
    }
  }

  return res_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int res_code = OK;

  if (!is_correct(A)) {
    res_code = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res_code = CALC_ERROR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result = (A->matrix[0][0] * A->matrix[1][1]) -
                (A->matrix[0][1] * A->matrix[1][0]);
    } else {
      *result = 0;
      matrix_t temp_matrix = {0};

      res_code = s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matrix);
      if (res_code == OK) {
        for (int j = 0; j < A->columns; j++) {
          s21_get_minor(A, 0, j, &temp_matrix);
          double number = 0;
          s21_determinant(&temp_matrix, &number);
          *result += A->matrix[0][j] * pow(-1, 1 + j + 1) * number;
        }

        s21_remove_matrix(&temp_matrix);
      }
    }
  }

  return res_code;
}

void s21_get_minor(matrix_t *A, int row, int column, matrix_t *result) {
  for (int i = 0, m = 0; i < A->rows; i++) {
    if (i != row) {
      for (int j = 0, n = 0; j < A->columns; j++) {
        if (j != column) {
          result->matrix[m][n] = A->matrix[i][j];
          n++;
        }
      }
      m++;
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res_code = OK;
  double det = 0;

  if (!is_correct(A)) {
    res_code = INCORRECT_MATRIX;
  } else {
    s21_determinant(A, &det);
    if ((A->rows == A->columns) && (det != 0)) {
      if (A->rows == 1) {
        res_code = s21_create_matrix(1, 1, result);
        if (res_code == OK) {
          result->matrix[0][0] = 1.00 / A->matrix[0][0];
        }
      } else {
        matrix_t temp_calc_comp = {0};
        matrix_t temp_transpose = {0};

        s21_calc_complements(A, &temp_calc_comp);
        s21_transpose(&temp_calc_comp, &temp_transpose);
        s21_mult_number(&temp_transpose, 1.0 / det, result);

        s21_remove_matrix(&temp_calc_comp);
        s21_remove_matrix(&temp_transpose);
      }

    } else {
      res_code = CALC_ERROR;
    }
  }

  return res_code;
}