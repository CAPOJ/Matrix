#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

Suite *test_create_matrix(void);
Suite *test_remove_matrix(void);
Suite *test_eq_matrix(void);
Suite *test_sum_matrix(void);
Suite *test_sub_matrix(void);
Suite *test_mult_matrix(void);
Suite *test_mult_number(void);
Suite *test_transpose(void);
Suite *test_determinant(void);
Suite *test_calc_complements(void);
Suite *test_inverse(void);

typedef struct {
  int fails;
} fail;

void run_tests(fail *fails);
void run_testcase(Suite *testcase, fail *fails);

#endif
