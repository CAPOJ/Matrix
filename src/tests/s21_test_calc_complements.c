#include "s21_test.h"

START_TEST(test_calc_complements_1) {
  matrix_t A = {0}, result = {0}, check = {0};
  int rows = 3;
  int columns = 3;
  int res_2 = 1;
  int res_1 = s21_create_matrix(rows, columns, &A);
  if (res_1 == OK) {
    res_2 = s21_create_matrix(rows, columns, &check);
  }

  if (!res_1 && !res_2) {
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 2;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = 2;
    A.matrix[2][2] = 1;
    check.matrix[0][0] = 0;
    check.matrix[0][1] = 10;
    check.matrix[0][2] = -20;
    check.matrix[1][0] = 4;
    check.matrix[1][1] = -14;
    check.matrix[1][2] = 8;
    check.matrix[2][0] = -8;
    check.matrix[2][1] = -2;
    check.matrix[2][2] = 4;
    s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &check), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&check);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t A = {0};
  matrix_t check = {0};
  int res = s21_calc_complements(&A, &check);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_calc_complements_3) {
  matrix_t m = {0};
  matrix_t check = {0};
  int res = s21_create_matrix(3, 4, &m);
  if (res == OK) {
    int code = s21_calc_complements(&m, &check);
    ck_assert_int_eq(code, CALC_ERROR);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_calc_complements_4) {
  matrix_t A = {0}, B = {0};

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = -5;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = -4;

  double check[2][2] = {{-4, -3}, {5, 1}};

  ck_assert_int_eq(s21_calc_complements(&A, &B), OK);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(B.matrix[i][j], check[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_5) {
  matrix_t A = {0}, result = {0}, check = {0};
  int rows = 1;
  int columns = 1;
  int res_2 = 1;
  int res_1 = s21_create_matrix(rows, columns, &A);
  if (res_1 == OK) {
    res_2 = s21_create_matrix(rows, columns, &check);
  }

  if (!res_1 && !res_2) {
    A.matrix[0][0] = 1;

    check.matrix[0][0] = 1;

    s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &check), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&check);
    s21_remove_matrix(&result);
  }
}
END_TEST

Suite *test_calc_complements(void) {
  Suite *s = suite_create("\033[45m-=s21_calc_complements=-\033[0m");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, test_calc_complements_1);
  tcase_add_test(tc, test_calc_complements_2);
  tcase_add_test(tc, test_calc_complements_3);
  tcase_add_test(tc, test_calc_complements_4);
  tcase_add_test(tc, test_calc_complements_5);

  suite_add_tcase(s, tc);
  return s;
}