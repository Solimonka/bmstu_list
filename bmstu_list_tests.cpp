#include <gtest/gtest.h>
#include <string>
#include "bmstu_list.h"

TEST(ListTest, BasicConstructor) {
    bmstu::list<int> l_list;
    bmstu::list<int>::iterator begin = l_list.begin();
    bmstu::list<int>::iterator end = l_list.end();
    ASSERT_EQ(l_list.size(), 0);
    ASSERT_TRUE(begin == end);
    --begin;
    --end;
    ASSERT_TRUE(begin == end);
}

TEST(ListTest, InitializerList) {
    bmstu::list<int> l_list({0, 1, 2, 3, 4, 5});
    bmstu::list<int>::iterator begin = l_list.begin();
    bmstu::list<int>::iterator end = l_list.end();
    ASSERT_EQ(l_list.size(), 6);
    for (int i = 0; begin != end; ++begin, ++i) {
        ASSERT_TRUE(*begin == i);
        ASSERT_TRUE(l_list[i] == i);
    }
}

TEST(ListTest, CopyConstructor) {
    bmstu::list<int> l_list({0, 1, 2, 3, 4, 5});
    bmstu::list<int>::iterator begin = l_list.begin();
    bmstu::list<int>::iterator end = l_list.end();
    bmstu::list<int> l_list_copy(l_list);
    bmstu::list<int>::iterator begin_copy = l_list_copy.begin();
    bmstu::list<int>::iterator end_copy = l_list_copy.end();
    ASSERT_EQ(l_list.size(), 6);
    ASSERT_EQ(l_list_copy.size(), 6);
    for (int i = 0; begin_copy != end_copy; ++begin, ++begin_copy, ++i) {
        ASSERT_TRUE(*begin == i);
        ASSERT_TRUE(*begin_copy == i);
        ASSERT_TRUE(l_list[i] == l_list_copy[i]);
    }
}

TEST(ListTest, MoveConstructor) {
    bmstu::list<int> l_list({0, 1, 2, 3, 4, 5});
    bmstu::list<int> l_list_move(std::move(l_list));
    bmstu::list<int>::iterator begin_move = l_list_move.begin();
    bmstu::list<int>::iterator end_move = l_list_move.end();
    ASSERT_EQ(l_list.size(), 0);
    ASSERT_EQ(l_list_move.size(), 6);
    for (int i = 0; begin_move != end_move; ++begin_move, ++i) {
        ASSERT_TRUE(*begin_move == i);
        ASSERT_TRUE(l_list_move[i] == i);
    }
}

TEST(ListTest, Pushback) {
    bmstu::list<int> l_list({0, 1, 2, 3, 4, 5});
    l_list.push_back(6);
    bmstu::list<int>::iterator begin = l_list.begin();
    bmstu::list<int>::iterator it_e = l_list.end();

    ASSERT_EQ(l_list.size(), 6);
    for (int a = 0; begin != it_e; ++begin, ++a) {
        ASSERT_TRUE(*begin == a);
        ASSERT_TRUE(l_list[a] == a);
    }

    --it_e;
    begin = l_list.begin() - 1;
    for (int a = 5; begin != it_e; --it_e, --a) {
        ASSERT_TRUE(*it_e == a);
        ASSERT_TRUE(l_list[a] == a);
    }
}
//
//TEST(ListTest, Subscript) {
//    bmstu::list<int> arr2d({1, 2, 3, 11, 22, 33}, 2, 3);
//    std::vector a = arr2d[1];
//    std::vector b({11, 22, 33});
//    for (int i = 0; i < 3; ++i) {
//        ASSERT_EQ(*a[i], b[i]);
//    }
//}
//
//TEST(ListTest, Determinant) {
//    bmstu::list arr2d({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    bmstu::list matritsa({1, 2, 3, 11, 22, 33}, 3, 2);
//    ASSERT_THROW(matritsa.det(), std::logic_error);
//    ASSERT_EQ(arr2d.det(), 0);
//}
//
//TEST(ListTest, Multiplication) {
//    bmstu::list arr2d({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    bmstu::list matritsa({1, 2, 3, 11, 22, 33}, 3, 2);
//    bmstu::matrix rezult_mult_matrix = arr2d * matritsa;
//    bmstu::list solution_mult_matrix({73, 123, 803, 1353, 8103, 13653}, 3, 2);
//    bmstu::list rezult_mult_number = arr2d * 2;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 2; ++j) {
//            ASSERT_EQ(rezult_mult_matrix(i, j), solution_mult_matrix(i, j));
//            ASSERT_EQ(rezult_mult_number(i, j), arr2d(i, j) * 2);
//        }
//    }
//    ASSERT_THROW(matritsa * arr2d, std::logic_error);
//}
//
//TEST(ListTest, Addition) {
//    bmstu::list arr2d({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    bmstu::list matritsa({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    bmstu::matrix rezult_add = arr2d + matritsa;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            ASSERT_EQ(rezult_add(i, j), arr2d(i, j) * 2);
//        }
//    }
//    bmstu::list fail({1, 2, 3}, 1, 3);
//    ASSERT_THROW(arr2d + fail, std::logic_error);
//}
//
//TEST(ListTest, Substraction) {
//    bmstu::list arr2d({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    bmstu::list matritsa({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    bmstu::matrix rezult_substr = arr2d - matritsa;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            ASSERT_EQ(rezult_substr(i, j), 0);
//        }
//    }
//    bmstu::list fail({1, 2, 3}, 1, 3);
//    ASSERT_THROW(arr2d - fail, std::logic_error);
//}
//
//TEST(ListTest, GetMinor) {
//    bmstu::list arr2d({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    bmstu::matrix rezult_minor = arr2d.get_minor(2, 1);
//    bmstu::list solution({1, 3, 11, 33}, 2, 2);
//    for (int i = 0; i < 2; ++i) {
//        for (int j = 0; j < 2; ++j) {
//            ASSERT_EQ(rezult_minor(i, j), solution(i, j));
//        }
//    }
//    ASSERT_THROW(arr2d.get_minor(-1, 7), std::logic_error);
//    ASSERT_THROW(arr2d.get_minor(6, 1), std::logic_error);
//}
//
//
//TEST(ListTest, Transpose) {
//    bmstu::list arr2d({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    arr2d.transpose();
//    bmstu::list rezult_trans({1, 11, 111, 2, 22, 222, 3, 33, 333}, 3, 3);
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            ASSERT_EQ(arr2d(i, j), rezult_trans(i, j));
//        }
//    }
//}
//
//TEST(ListTest, Reverse) {
//    bmstu::list arr2d({2, 5, 7, 6, 3, 4, 5, -2, -3}, 3, 3);
//    bmstu::matrix rezult_reverse = arr2d.reverse();
//    bmstu::list solution({1, -1, 1, -38, 41, -34, 27, -29, 24}, 3, 3);
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            ASSERT_EQ(rezult_reverse(i, j), solution(i, j));
//        }
//    }
//    bmstu::list fail({1, 2, 3, 11, 22, 33, 111, 222, 333}, 3, 3);
//    ASSERT_THROW(fail.reverse(), std::logic_error);
//}