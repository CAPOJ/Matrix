#include "s21_test.h"

START_TEST(test_remove_matrix_1) {
  matrix_t matrix;
  int rows = 3;
  int columns = 3;

  int res = s21_create_matrix(rows, columns, &matrix);
  if (res == 0) s21_remove_matrix(&matrix);
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(0, matrix.rows);
  ck_assert_int_eq(0, matrix.columns);
}
END_TEST

START_TEST(test_remove_matrix_2) {
  matrix_t matrix;
  int rows = 0;
  int columns = 5;

  s21_create_matrix(rows, columns, &matrix);
  s21_remove_matrix(&matrix);
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(0, matrix.rows);
  ck_assert_int_eq(0, matrix.columns);
}
END_TEST

START_TEST(test_remove_matrix_3) {
  matrix_t matrix;
  int rows = -2;
  int columns = 3;

  s21_create_matrix(rows, columns, &matrix);
  s21_remove_matrix(&matrix);
  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(0, matrix.rows);
  ck_assert_int_eq(0, matrix.columns);
}
END_TEST

Suite *test_remove_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_remove_matrix=-\033[0m");
  TCase *tc = tcase_create("case_remove_matrix");

  tcase_add_test(tc, test_remove_matrix_1);
  tcase_add_test(tc, test_remove_matrix_2);
  tcase_add_test(tc, test_remove_matrix_3);

  suite_add_tcase(s, tc);
  return s;
}