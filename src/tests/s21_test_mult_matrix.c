#include "s21_test.h"

START_TEST(test_mult_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(3, 1, &B);
  int res = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  matrix_t check = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &check);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.;
  A.matrix[1][1] = 4.53;

  B.matrix[0][0] = 5.;
  B.matrix[0][1] = 6.123456;
  B.matrix[1][0] = -7.;
  B.matrix[1][1] = 8.;

  check.matrix[0][0] = -9;
  check.matrix[0][1] = 22.123456;
  check.matrix[1][0] = -16.71;
  check.matrix[1][1] = 54.610368;
  int res = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_mult_matrix_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_matrix(&A, &B, &result));
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  matrix_t check = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &check);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -5.;
  A.matrix[1][2] = 6.35;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  B.matrix[0][0] = 1.;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.;
  B.matrix[1][1] = 4.;
  B.matrix[2][0] = 5.75;
  B.matrix[2][1] = -6.;

  check.matrix[0][0] = 24.25;
  check.matrix[0][1] = -8;
  check.matrix[1][0] = 25.5125;
  check.matrix[1][1] = -50.1;
  check.matrix[2][0] = 82.75;
  check.matrix[2][1] = -8;
  int res = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

Suite *test_mult_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_mult_matrix=-\033[0m");
  TCase *tc = tcase_create("case_mult_matrix");

  tcase_add_test(tc, test_mult_matrix_1);
  tcase_add_test(tc, test_mult_matrix_2);
  tcase_add_test(tc, test_mult_matrix_3);
  tcase_add_test(tc, test_mult_matrix_4);

  suite_add_tcase(s, tc);
  return s;
}