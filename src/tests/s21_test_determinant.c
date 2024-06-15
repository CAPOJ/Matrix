#include "s21_test.h"

START_TEST(test_determinant_1) {
  double result = 0;
  matrix_t A = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 3;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 6;
  A.matrix[1][2] = 7;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 4;
  A.matrix[2][2] = 0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 31, 1e-06);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(-1, 3, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 835.38562563;
  ck_assert_int_eq(OK, s21_determinant(&A, &result));
  ck_assert_double_eq_tol(result, A.matrix[0][0], 1e-06);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5) {
  double result = 0;
  matrix_t A = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 0, 1e-06);
  s21_remove_matrix(&A);
}
END_TEST

Suite *test_determinant(void) {
  Suite *s = suite_create("\033[45m-=s21_determinant=-\033[0m");
  TCase *tc = tcase_create("case_determinant");

  tcase_add_test(tc, test_determinant_1);
  tcase_add_test(tc, test_determinant_2);
  tcase_add_test(tc, test_determinant_3);
  tcase_add_test(tc, test_determinant_4);
  tcase_add_test(tc, test_determinant_5);

  suite_add_tcase(s, tc);
  return s;
}