#include "s21_test.h"

START_TEST(test_eq_1) {
  int rows = 4;
  int cols = 4;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  int result = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_eq_2) {
  int rows = 4;
  int cols = 4;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  matrix_1.matrix[0][0] = 1;
  matrix_2.matrix[0][0] = 1;
  int result = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_eq_3) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[1][0] = 2;
  matrix_1.matrix[0][1] = 3;
  matrix_1.matrix[1][1] = 4;

  matrix_2.matrix[0][0] = 1;
  matrix_2.matrix[1][0] = 2;
  matrix_2.matrix[0][1] = 3;
  matrix_2.matrix[1][1] = 4;
  int result = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_eq_4) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  matrix_1.matrix[0][0] = 1.01;
  matrix_1.matrix[1][0] = 2;
  matrix_1.matrix[0][1] = 3.05;
  matrix_1.matrix[1][1] = 4;

  matrix_2.matrix[0][0] = 1.01;
  matrix_2.matrix[1][0] = 2;
  matrix_2.matrix[0][1] = 3.05;
  matrix_2.matrix[1][1] = 4;
  int result = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_eq_5) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  matrix_1.matrix[0][0] = 1.0100006;
  matrix_1.matrix[1][0] = -2;
  matrix_1.matrix[0][1] = 3.05;
  matrix_1.matrix[1][1] = -4;

  matrix_2.matrix[0][0] = 1.01;
  matrix_2.matrix[1][0] = -2;
  matrix_2.matrix[0][1] = 3.05;
  matrix_2.matrix[1][1] = -4;
  int result = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_not_eq_1) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[1][0] = 2;
  matrix_1.matrix[0][1] = 3;
  matrix_1.matrix[1][1] = 4;

  matrix_2.matrix[0][0] = -1;
  matrix_2.matrix[1][0] = 2;
  matrix_2.matrix[0][1] = 3;
  matrix_2.matrix[1][1] = 4;
  int result = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_not_eq_2) {
  int rows = 2;
  int cols = 2;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  matrix_1.matrix[0][0] = 1.010002;
  matrix_1.matrix[1][0] = -2;
  matrix_1.matrix[0][1] = 3.05;
  matrix_1.matrix[1][1] = -4;

  matrix_2.matrix[0][0] = 1.01;
  matrix_2.matrix[1][0] = -2;
  matrix_2.matrix[0][1] = 3.05;
  matrix_2.matrix[1][1] = -4;
  int result = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_not_eq_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 1, &B);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

Suite *test_eq_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_eq=-\033[0m");
  TCase *tc = tcase_create("case_eq");

  tcase_add_test(tc, test_eq_1);
  tcase_add_test(tc, test_eq_2);
  tcase_add_test(tc, test_eq_3);
  tcase_add_test(tc, test_eq_4);
  tcase_add_test(tc, test_eq_5);

  tcase_add_test(tc, test_not_eq_1);
  tcase_add_test(tc, test_not_eq_2);
  tcase_add_test(tc, test_not_eq_3);

  suite_add_tcase(s, tc);
  return s;
}