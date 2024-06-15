#include "s21_test.h"

START_TEST(test_transpose_1) {
  ck_assert_int_eq(s21_transpose(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_transpose_2) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(INCORRECT_MATRIX, s21_transpose(&A, &result));
}
END_TEST

START_TEST(test_transpose_3) {
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_transpose(&A, NULL));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transpose_4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 8.765;
  ck_assert_int_eq(OK, s21_transpose(&A, &result));
  ck_assert_ldouble_eq_tol(A.matrix[0][0], result.matrix[0][0], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_5) {
  int rows = 2;
  int cols = 3;
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(cols, rows, &check);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3.25;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = 3.25252525;
  A.matrix[1][2] = -75;

  check.matrix[0][0] = 1;
  check.matrix[0][1] = -4;
  check.matrix[1][0] = 2;
  check.matrix[1][1] = 3.25252525;
  check.matrix[2][0] = 3.25;
  check.matrix[2][1] = -75;

  int res = s21_transpose(&A, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

Suite *test_transpose(void) {
  Suite *s = suite_create("\033[45m-=s21_transpose=-\033[0m");
  TCase *tc = tcase_create("case_transpose");

  tcase_add_test(tc, test_transpose_1);
  tcase_add_test(tc, test_transpose_2);
  tcase_add_test(tc, test_transpose_3);
  tcase_add_test(tc, test_transpose_4);
  tcase_add_test(tc, test_transpose_5);

  suite_add_tcase(s, tc);
  return s;
}