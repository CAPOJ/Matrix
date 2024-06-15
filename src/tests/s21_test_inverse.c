#include "s21_test.h"

START_TEST(test_inverse_1) {
  matrix_t A = {0}, result = {0};
  int res;

  s21_create_matrix(0, 3, &A);
  res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_2) {
  matrix_t A = {0}, result = {0};
  int res;

  s21_create_matrix(-1, 3, &A);
  res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_3) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_4) {
  matrix_t A = {0}, result = {0};
  int res;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  double check[2][2] = {{-2, 1}, {3.0 / 2.0, -1.0 / 2.0}};

  res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(res, OK);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], check[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_5) {
  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_6) {
  ck_assert_int_eq(s21_inverse_matrix((void *)0, (void *)0), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_7) {
  matrix_t A = {0}, check = {0}, result = {0};
  int res;

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &check);
  A.matrix[0][0] = 1;
  check.matrix[0][0] = 1 / 1;

  res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

Suite *test_inverse(void) {
  Suite *s = suite_create("\033[45m-=s21_inverse=-\033[0m");
  TCase *tc = tcase_create("case_inverse");

  tcase_add_test(tc, test_inverse_1);
  tcase_add_test(tc, test_inverse_2);
  tcase_add_test(tc, test_inverse_3);
  tcase_add_test(tc, test_inverse_4);
  tcase_add_test(tc, test_inverse_5);
  tcase_add_test(tc, test_inverse_6);
  tcase_add_test(tc, test_inverse_7);

  suite_add_tcase(s, tc);
  return s;
}