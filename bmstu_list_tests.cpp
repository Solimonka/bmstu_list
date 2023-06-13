#include <gtest/gtest.h>
#include <string>
#include "bmstu_list.h"

TEST(ListTest, BasicConstructor) {
    bmstu::list<int> l_list;
    ASSERT_EQ(l_list.size(), 0);
    ASSERT_TRUE(l_list.begin() == l_list.end());
    ASSERT_TRUE(--l_list.begin() == --l_list.end());
}

TEST(ListTest, Pushback_) {
    bmstu::list<int> l_list;
    l_list.push_back(1);
    ASSERT_EQ(l_list.size(), 1);
    ASSERT_EQ(l_list[0], 1);
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
    ASSERT_EQ(l_list.size(), 3);
    ASSERT_TRUE(l_list[0] == "ya");
    ASSERT_TRUE(l_list[1] == "ne");
    ASSERT_TRUE(l_list[2] == "loh");
}

TEST(ListTest, Clear) {
    bmstu::list<std::string> l_list({"tut", "nichego", "net"});
    l_list.clear();
    ASSERT_EQ(l_list.size(), 0);
    ASSERT_TRUE(l_list.begin() == l_list.end());
}

TEST(ListTest, Swap) {
    bmstu::list<std::string> l_list({"ya", "hochu", "pyat'", "po", "proge"});
    bmstu::list<std::string> l_list_swap({"hotet", "ne", "vredno"});
    l_list.swap(l_list_swap);
    ASSERT_EQ(l_list.size(), 3);
    ASSERT_EQ(l_list_swap.size(), 5);
    ASSERT_TRUE(l_list[0] == "hotet");
    ASSERT_TRUE(l_list[1] == "ne");
    ASSERT_TRUE(l_list[2] == "vredno");
    ASSERT_TRUE(l_list_swap[0] == "ya");
    ASSERT_TRUE(l_list_swap[1] == "hochu");
    ASSERT_TRUE(l_list_swap[2] == "pyat'");
    ASSERT_TRUE(l_list_swap[3] == "po");
    ASSERT_TRUE(l_list_swap[4] == "proge");
}

TEST(ListTest, Compare) {
    bmstu::list<int> l_list({0, 1, 2, 3, 4, 5});
    bmstu::list<int> l_list_fail_1({0, 1, 2, 3, 4, 5, 6});
    bmstu::list<int> l_list_fail_2({0, 1, 2, 3, 4, 6});
    ASSERT_FALSE(l_list == l_list_fail_1);
    ASSERT_FALSE(l_list == l_list_fail_2);
    ASSERT_TRUE(l_list == l_list);
    ASSERT_TRUE(l_list != l_list_fail_2);
    ASSERT_TRUE(l_list < l_list_fail_2);
    ASSERT_TRUE(l_list_fail_2 > l_list);
    ASSERT_TRUE(l_list <= l_list_fail_2);
    ASSERT_TRUE(l_list_fail_2 >= l_list);
}

TEST(ListTest, Output) {
    bmstu::list<std::string> l_list({"very", "hardcode"});
    std::stringstream s;
    s << l_list;
    ASSERT_STREQ(s.str().c_str(), "{very, hardcode}");
}

TEST(ListTest, Insert) {
    bmstu::list<std::string> l_list({"hardcoding", "shitcoding", "schizocoding"});
    bmstu::list<std::string>::iterator pos = l_list.begin() + 1;
    ASSERT_THROW(l_list.insert(l_list.end(), "perfectcoding"), std::logic_error);
    l_list.insert(pos, "girlscoding");
    ASSERT_EQ(l_list.size(), 4);
    ASSERT_TRUE(l_list[0] == "hardcoding");
    ASSERT_TRUE(l_list[1] == "shitcoding");
    ASSERT_TRUE(l_list[2] == "girlscoding");
    ASSERT_TRUE(l_list[3] == "schizocoding");
}

TEST(ListTest, Reverse) {
    bmstu::list<int> l_list_0({1, 2, 3, 4, 5, 6, 7, 8, 9});
    l_list_0.reverse();
    bmstu::list<int> l_list_r({9, 8, 7, 6, 5, 4, 3, 2, 1});
    ASSERT_EQ(l_list_0, l_list_r);
    l_list_0.push_back(0);
    bmstu::list<int> l_list_1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    l_list_0.my_reverse();
    ASSERT_EQ(l_list_0, l_list_1);
}

TEST(ListTest, Popback) {
    bmstu::list<int> l_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(l_list.pop_back(0), 1);
    bmstu::list<int> l_list_r({2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(l_list.size(), 8);
    ASSERT_EQ(l_list, l_list_r);
    ASSERT_EQ(l_list.pop_back(4), 6);
    ASSERT_EQ(l_list.size(), 7);
    bmstu::list<int> l_list_r_({2, 3, 4, 5, 7, 8, 9});
    ASSERT_EQ(l_list, l_list_r_);
    ASSERT_THROW(l_list.pop_back(90), std::logic_error);
    ASSERT_EQ(l_list.pop_back(), 9);
    try {
        l_list.pop_back(100);
    }
    catch (const std::logic_error &err) {
        ASSERT_EQ(err.what(), std::string("lOsEr"));
    }
}

TEST(ListTest, Remove) {
    bmstu::list<int> l_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    bmstu::list<int> l_list_r({1, 8, 9});
    l_list.remove(1, 6);
    ASSERT_EQ(l_list, l_list_r);
    ASSERT_THROW(l_list.remove(0, 0), std::logic_error);
    ASSERT_THROW(l_list.remove(0, 10), std::logic_error);
    l_list.remove(1, 2);
    bmstu::list<int> l_list_({1});
    ASSERT_EQ(l_list, l_list_);
}

TEST(ListTest, OperatorEqual) {
    bmstu::list<int> l_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    bmstu::list<int> l_list_r({1, 8, 9});
    l_list = l_list_r;
    ASSERT_EQ(l_list, l_list_r);
    ASSERT_EQ(l_list.size(), 3);
    bmstu::list<int> l_list_;
    l_list_ = l_list_r;
    ASSERT_EQ(l_list_, l_list_r);
    ASSERT_EQ(l_list_.size(), 3);
    bmstu::list<int> l_list_2;
    l_list = l_list_2;
    ASSERT_EQ(l_list.size(), 0);
    ASSERT_TRUE(l_list.begin() == l_list.end());
    ASSERT_EQ(l_list, l_list_2);
}

TEST(ListTest, OperatorConcatenation) {
    bmstu::list<int> l_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    bmstu::list<int> l_list_({1, 8, 9});
    l_list += l_list_;
    bmstu::list<int> l_list_r({1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 8, 9});
    ASSERT_EQ(l_list, l_list_r);
    bmstu::list<int> l_list_2;
    l_list += l_list_2;
    ASSERT_EQ(l_list, l_list_r);
}

TEST(ListTest, OperatorPlus) {
    bmstu::list<int> l_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    bmstu::list<int> l_list_({1, 8, 9});
    bmstu::list<int> l_list_r = l_list + l_list_;
    bmstu::list<int> l_list_r_({1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 8, 9});
    ASSERT_EQ(l_list_r, l_list_r_);
    bmstu::list<int> l_list_2;
    bmstu::list<int> l_list_2_;
    bmstu::list<int> l_list_3 = l_list_2 + l_list_2_;
    ASSERT_EQ(l_list_3, l_list_2);
}

TEST(ListTest, Find) {
    bmstu::list<int> l_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(l_list.find(4), 3);
    bmstu::list<int> l_list_f;
    ASSERT_THROW(l_list_f.find(3), std::logic_error);
    bmstu::list<int> l_list_({0, 0, 0, 0, 0});
    ASSERT_EQ(l_list_.find(0), 0);
    bmstu::list<int> l_list__({1, 2});
    ASSERT_THROW(l_list__.find(0), std::logic_error);
    bmstu::list<int> l_list_2({0, 0, 1, 1, 1});
    ASSERT_EQ(l_list_2.find(1), 2);
}

TEST(ListTest, Sort) {
    bmstu::list<int> l_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(l_list.max(), 9);
    l_list.sort();
    bmstu::list<int> l_list_r = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT_EQ(l_list, l_list_r);
    bmstu::list<int> l_list_({8, 7, 6, 90, 123, 77777, 0});
    ASSERT_EQ(l_list_.max(), 77777);
    l_list_.sort();
    bmstu::list<int> l_list_r_ = {77777, 123, 90, 8, 7, 6, 0};
    ASSERT_EQ(l_list_, l_list_r_);
    bmstu::list<int> l_list_2;
    bmstu::list<int> l_list_2_;
    l_list_2.sort();
    ASSERT_EQ(l_list_2, l_list_2_);
    bmstu::list<int> l_list_3({9, 9, 9, 10, 9, 9});
    bmstu::list<int> l_list_3_({10, 9, 9, 9, 9, 9});
    l_list_3.sort();
    ASSERT_EQ(l_list_3, l_list_3_);
    bmstu::list<int> l_list_4({9, 9, 9, 9, 9});
    bmstu::list<int> l_list_4_({9, 9, 9, 9, 9});
    l_list_4.sort();
    ASSERT_EQ(l_list_4, l_list_4_);
}

TEST(ListTest, Count) {
    bmstu::list<int> l_list({1, 4, 4, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(l_list.count(4), 3);
    ASSERT_EQ(l_list.count(0), 0);
    bmstu::list<int> l_list_;
    ASSERT_EQ(l_list_.count(4), 0);
}

TEST(ListTest, Alignment) {
    bmstu::list<int> l_list({1, 4, 4, 4, 5, 6, 7, 8, 9});
    bmstu::list<int> l_list_r({4, 4, 4, 4, 4, 4, 4, 4, 4});
    l_list.alignment(4);
    ASSERT_EQ(l_list, l_list_r);
    bmstu::list<int> l_list_;
    l_list_.alignment(4);
    bmstu::list<int> l_list__;
    ASSERT_EQ(l_list_, l_list__);
    l_list.alignment_2(5);
    bmstu::list<int> l_list_r2({5, 5, 5, 5, 4, 4, 4, 4, 4});
    ASSERT_EQ(l_list, l_list_r2);
    bmstu::list<int> l_list_r3({5, 5, 5, 0, 0, 0, 4, 4, 4});
    l_list.alignment_3(3, 5, 0);
    ASSERT_EQ(l_list, l_list_r3);
}