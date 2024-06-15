#include "s21_test.h"

START_TEST(test_sum_1) {
  int rows = 4;
  int cols = 4;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_2) {
  int rows = 2;
  int cols = 2;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &A);
  s21_create_matrix(rows, cols, &B);
  s21_create_matrix(rows, cols, &check);
  A.matrix[0][0] = 1.;
  A.matrix[1][0] = 2;
  A.matrix[0][1] = 3.25;
  A.matrix[1][1] = -4;

  B.matrix[0][0] = 1;
  B.matrix[1][0] = 2.12345678;
  B.matrix[0][1] = 3;
  B.matrix[1][1] = 4;

  check.matrix[0][0] = 2;
  check.matrix[1][0] = 4.12345678;
  check.matrix[0][1] = 6.25;
  check.matrix[1][1] = 0;

  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_sum_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sum_matrix(&A, &B, &result));
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_4) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sum_matrix(&A, &B, NULL));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = INFINITY;
  B.matrix[0][0] = INFINITY;
  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_6) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 4, &B);
  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *test_sum_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_sum_matrix=-\033[0m");
  TCase *tc = tcase_create("case_sum_matrix");

  tcase_add_test(tc, test_sum_1);
  tcase_add_test(tc, test_sum_2);
  tcase_add_test(tc, test_sum_3);
  tcase_add_test(tc, test_sum_4);
  tcase_add_test(tc, test_sum_5);
  tcase_add_test(tc, test_sum_6);

  suite_add_tcase(s, tc);
  return s;
}