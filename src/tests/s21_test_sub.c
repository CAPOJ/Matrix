#include "s21_test.h"

START_TEST(test_sub_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(3, 1, &B);
  int res = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_2) {
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
  B.matrix[0][1] = 6.1234567;
  B.matrix[1][0] = -7.;
  B.matrix[1][1] = 8.;

  check.matrix[0][0] = -4;
  check.matrix[0][1] = -4.1234567;
  check.matrix[1][0] = 10;
  check.matrix[1][1] = -3.47;
  int res = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_sub_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(&A, &B, &result));
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_4) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(&A, &B, NULL));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = INFINITY;
  B.matrix[0][0] = INFINITY;
  int res = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *test_sub_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_sub_matrix=-\033[0m");
  TCase *tc = tcase_create("case_sub_matrix");

  tcase_add_test(tc, test_sub_1);
  tcase_add_test(tc, test_sub_2);
  tcase_add_test(tc, test_sub_3);
  tcase_add_test(tc, test_sub_4);
  tcase_add_test(tc, test_sub_5);

  suite_add_tcase(s, tc);
  return s;
}