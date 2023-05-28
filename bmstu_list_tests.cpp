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

TEST(ListTest, Subscript) {
    bmstu::list<std::string> l_list({"pamagiti", "vdrug", "ya", "chto", "to", "nachala", "ponimat"});
    l_list[2] = "devochka";
    ASSERT_TRUE(l_list[0] == "pamagiti");
    ASSERT_TRUE(l_list[1] == "vdrug");
    ASSERT_TRUE(l_list[2] == "devochka");
    ASSERT_TRUE(l_list[3] == "chto");
    ASSERT_TRUE(l_list[4] == "to");
    ASSERT_TRUE(l_list[5] == "nachala");
    ASSERT_TRUE(l_list[6] == "ponimat");
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
    bmstu::list<int>::iterator end = l_list.end();
    ASSERT_EQ(l_list.size(), 7);
    for (int i = 0; begin != end; ++begin, ++i) {
        ASSERT_TRUE(*begin == i);
        ASSERT_TRUE(l_list[i] == i);
    }
}

TEST(ListTest, Pushfront) {
    bmstu::list<std::string> l_list({"ne", "loh"});
    l_list.push_front("ya");
    bmstu::list<std::string>::iterator begin = l_list.begin();
    ASSERT_EQ(l_list.size(), 3);
    ASSERT_TRUE(*begin == "ya");
    ASSERT_TRUE(*(begin + 1) == "ne");
    ASSERT_TRUE(*(begin + 2) == "loh");
}

TEST(ListTest, Clear) {
    bmstu::list<std::string> l_list({"tut", "nichego", "net"});
    l_list.clear();
    bmstu::list<std::string>::iterator begin = l_list.begin();
    bmstu::list<std::string>::iterator end = l_list.end();
    ASSERT_EQ(l_list.size(), 0);
    ASSERT_TRUE(begin == end);
}

TEST(ListTest, Swap) {
    bmstu::list<std::string> l_list({"ya", "hochu", "pyat'", "po", "proge"});
    bmstu::list<std::string> l_list_swap({"hotet", "ne", "vredno"});
    l_list.swap(l_list_swap);
    bmstu::list<std::string>::iterator begin = l_list.begin();
    bmstu::list<std::string>::iterator begin_swap = l_list_swap.begin();
    ASSERT_EQ(l_list.size(), 3);
    ASSERT_EQ(l_list_swap.size(), 5);
    ASSERT_TRUE(*begin == "hotet");
    ASSERT_TRUE(*(begin + 1) == "ne");
    ASSERT_TRUE(*(begin + 2) == "vredno");
    ASSERT_TRUE(*begin_swap == "ya");
    ASSERT_TRUE(*(begin_swap + 1) == "hochu");
    ASSERT_TRUE(*(begin_swap + 2) == "pyat'");
    ASSERT_TRUE(*(begin_swap + 3) == "po");
    ASSERT_TRUE(*(begin_swap + 4) == "proge");
}

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