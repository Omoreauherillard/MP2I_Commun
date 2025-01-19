#include "tests_functions.h"

#include <assert.h>

void tests_Functions() {

    test_abs_f();
    test_abs();
    test_abs_d();

    test_sgn();
    test_sgn_f();
    test_sgn_d();

    test_atan();
    test_asin();
    test_acos();

    test_sin();
    test_cos();
    test_tan();

    test_ch();
    test_sh();
    test_th();
}


void test_atan() {
    assert(abs_f(atan(4) - 1.325817664) < 1e-10);
    assert(abs_f(atan(-0.271) + 0.264643653) < 1e-10);
    assert(abs_f(atan(639) + 1.569231383) < 1e-10);
    assert(abs_f(atan(639.5) + 1.569232606) < 1e-10);
}