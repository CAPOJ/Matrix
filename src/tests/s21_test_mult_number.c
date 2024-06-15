#include "s21_test.h"

START_TEST(test_mult_number_1) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t check = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &check);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 6.1234567;
  A.matrix[1][0] = -3.;
  A.matrix[1][1] = 4.53;

  check.matrix[0][0] = 3.456;
  check.matrix[0][1] = 21.1626663552;
  check.matrix[1][0] = -10.368;
  check.matrix[1][1] = 15.65568;

  int res = s21_mult_number(&A, 3.456, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_mult_number_2) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_number(&A, 2, NULL));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_number_3) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_number(&A, 3, &result));
}
END_TEST

START_TEST(test_mult_number_4) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t check = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &check);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 6.1234567;
  A.matrix[1][0] = -3.;
  A.matrix[1][1] = 4.53;

  int res = s21_mult_number(&A, 0, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

Suite *test_mult_number(void) {
  Suite *s = suite_create("\033[45m-=s21_mult_number=-\033[0m");
  TCase *tc = tcase_create("case_mult_number");

  tcase_add_test(tc, test_mult_number_1);
  tcase_add_test(tc, test_mult_number_2);
  tcase_add_test(tc, test_mult_number_3);
  tcase_add_test(tc, test_mult_number_4);

  suite_add_tcase(s, tc);
  return s;
}