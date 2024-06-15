#include "s21_test.h"

START_TEST(test_create_1) {
  matrix_t my_matrix = {0};
  int result = s21_create_matrix(3, 3, &my_matrix);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&my_matrix);
}
END_TEST

START_TEST(test_create_2) {
  matrix_t my_matrix = {0};
  int result = s21_create_matrix(-3, 3, &my_matrix);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_3) {
  matrix_t my_matrix = {0};
  int result = s21_create_matrix(-5, 0, &my_matrix);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_4) {
  matrix_t my_matrix = {0};
  int result = s21_create_matrix(2, 0, &my_matrix);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_5) {
  matrix_t my_matrix = {0};
  int result = s21_create_matrix(0, 1, &my_matrix);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_6) {
  matrix_t my_matrix = {0};
  int result = s21_create_matrix(2, 5, &my_matrix);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&my_matrix);
}
END_TEST

Suite *test_create_matrix(void) {
  Suite *s = suite_create("\033[45m-=s21_create=-\033[0m");
  TCase *tc = tcase_create("case_create");

  tcase_add_test(tc, test_create_1);
  tcase_add_test(tc, test_create_2);
  tcase_add_test(tc, test_create_3);
  tcase_add_test(tc, test_create_4);
  tcase_add_test(tc, test_create_5);
  tcase_add_test(tc, test_create_6);

  suite_add_tcase(s, tc);
  return s;
}