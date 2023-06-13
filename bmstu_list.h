#include <iostream>
#include <cassert>

namespace bmstu {
    template<typename T>
    class list {
        struct node {
            node() = default;

            node(node *prev, const T &value, node *next) : next_node(next), value_(value), prev_node(prev) {}

            ~node() = default;

            T value_ = {};
            node *next_node = nullptr;
            node *prev_node = nullptr;
        };

    public:

#pragma region Iterator

        template<typename value_t>
        struct list_iterator {
            friend class list;

            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = value_t;
            using pointer = value_t *;
            using reference = value_t &;

            list_iterator() = default;

            list_iterator(node *node) : node_(node) {}

            list_iterator(const list_iterator<T> &other) noexcept: node_(other.node_) {}

            reference operator*() const {
                assert(node_ != nullptr);
                return static_cast<T &> (node_->value_);
            }

            pointer operator->() {
                assert(node_ != nullptr);
                return static_cast<T *> (&(node_->value_));
            }

            list_iterator &operator++() {
                assert(node_ != nullptr);
                if (node_->next_node == nullptr) {
                    throw std::logic_error("lOsEr");
                }
                node_ = node_->next_node;
                return *this;
            }

            list_iterator &operator--() {
                assert(node_ != nullptr);
                if (node_->prev_node == nullptr) {
                    throw std::logic_error("lOsEr");
                }
                node_ = node_->prev_node;
                return *this;
            }

            list_iterator &operator=(const list_iterator &other) = default;

            list_iterator operator++(int) {
                list_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            list_iterator operator--(int) {
                list_iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const list_iterator &a, const list_iterator &b) {
                return a.node_ == b.node_;
            }

            friend bool operator!=(const list_iterator &a, const list_iterator &b) {
                return !(a == b);
            }

            explicit operator bool() {
                return node_ != nullptr;
            }

            list_iterator operator+(const difference_type value) noexcept {
                list_iterator copy(*this);
                for (auto i = 1; i <= value; ++i) {
                    ++(copy);
                }
                return copy;
            }

            template<typename Integer>
            list_iterator operator+(Integer value) noexcept {
                list_iterator copy(*this);
                for (auto i = 1; i <= value; ++i) {
                    ++(copy);
                }
                return copy;
            }

            list_iterator operator-(const difference_type value) noexcept {
                list_iterator copy(*this);
                for (auto i = 1; i <= value; ++i) {
                    --(copy);
                }
                return copy;
            }

            list_iterator operator+=(const difference_type value) noexcept {
                return ((*this) + value);
            }

            friend difference_type operator-(const list_iterator &end, const list_iterator &begin) {
                difference_type result{};
                list_iterator copy(begin);
                for (result = 0; copy != end; ++result) {
                    copy += 1;
                }
                return result;
            }

        private:
            node *node_ = nullptr;
        };

#pragma endregion

        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = list_iterator<T>;
        using const_iterator = list_iterator<const T>;

#pragma region Constructors

        list() : size_(0), tail_(std::make_unique<node>()), head_(std::make_unique<node>()) {
            head_->next_node = tail_.get();
            tail_->prev_node = head_.get();
        }

        template<typename it>
        list(it begin, it end) {
            list<T> tmp;
            it copy(begin);
            while (copy != end) {
                tmp.push_back(*copy);
                ++copy;
            }
            swap(tmp);
        }

        list(std::initializer_list<T> values) {
            list<T> tmp;
            for (const auto &val: values) {
                tmp.push_back(val);
            }
            swap(tmp);
        }

        list(const list &other) {
            if (this != &other) {
                list<T> tmp;
                for (const auto &item: other) {
                    tmp.push_back(item);
                }
                swap(tmp);
            }
        }

        list(list &&other) {
            swap(other);
        }

#pragma endregion

#pragma region pushs

        template<typename Type>
        void push_back(const Type &value) {
            node *last = tail_->prev_node;
            node *new_last = new node(tail_->prev_node, value, tail_.get());
            tail_->prev_node = new_last;
            last->next_node = new_last;
            ++size_;
        }

        template<typename Type>
        void push_front(const Type &value) {
            node *first = head_->next_node;
            node *new_first = new node(head_.get(), value, head_->next_node);
            head_->next_node = new_first;
            first->prev_node = new_first;
            ++size_;
        }

#pragma endregion

        bool empty() const noexcept {
            return (size_ == 0u);
        }

        ~list() {
            clear();
//            delete tail_;
//            delete head_;
        }

        void clear() {
            if (empty()) {
                return;
            } else {
                while (head_->next_node != tail_.get()) {
                    node *next = head_->next_node;
                    head_->next_node = next->next_node;
                    delete next;
                }
                tail_->prev_node = head_.get();
                size_ = 0;
            }
        }

        size_t size() {
            return size_;
        }

        void swap(list &other) noexcept {
            std::swap(head_, other.head_);
            std::swap(tail_, other.tail_);
            std::swap(size_, other.size_);
        }

        friend void swap(list &l, list &r) {
            l.swap(r);
        }

#pragma region iterators

        iterator begin() noexcept {
            return iterator{head_->next_node};
        }

        iterator end() noexcept {
            return iterator{tail_.get()};
        }

        const_iterator begin() const noexcept {
            return const_iterator{head_->next_node};
        }

        const_iterator end() const noexcept {
            return const_iterator{tail_.get()};
        }

        const_iterator cbegin() const noexcept {
            return const_iterator{head_->next_node};
        }

        const_iterator cend() const noexcept {
            return const_iterator{tail_.get()};
        }

#pragma endregion

        T operator[](size_t pos) const {
            return *(begin() + pos);
        }

        T &operator[](size_t pos) {
            return *(begin() + pos);
        }

        friend bool operator==(const list &l, const list &r) {
            if (l.size_ != r.size_) {
                return false;
            } else {
                auto l_b = l.begin();
                auto r_b = r.begin();
                while (l_b != l.end() && r_b != r.end()) {
                    if (*l_b != *r_b) {
                        return false;
                    }
                    ++l_b;
                    ++r_b;
                }
            }
            return true;
        }

        friend bool operator!=(const list<T> &left, const list<T> &right) {
            return !(left == right);
        }

        friend bool operator<(const list<T> &left, const list<T> &right) {
            return lexicographical_compare_(left, right);
        }

        friend bool operator>(const list<T> &left, const list<T> &right) {
            return (right < left);
        }

        friend bool operator<=(const list<T> &left, const list<T> &right) {
            return !(right < left);
        }

        friend bool operator>=(const list<T> &left, const list<T> &right) {
            return !(left < right);
        }

        friend std::ostream &operator<<(std::ostream &os, const list<T> &other) {
            os << "{";
            if (other.size_) {
                for (int i = 0; i < other.size_ - 1; ++i) {
                    os << other[i] << ", ";
                }
                os << other[other.size_ - 1];
            }
            os << "}";
            return os;
        }

        iterator insert(const_iterator pos, const T &value) {
            if (pos.node_->next_node == nullptr) {
                throw std::logic_error("lOsEr");
            }
            node *new_node = new node(pos.node_, value, pos.node_->next_node);
            pos.node_->next_node = new_node;
            ++size_;
            return iterator{new_node};
        }

#pragma region delo_bilo_vecherom_delat_bilo_nechego

        T pop_back(size_t pos) {
            if (pos > size_ || pos < 0) {
                throw std::logic_error("lOsEr");
            }
            iterator it = begin() + pos;
            T val = it.node_->value_;
            it.node_->next_node->prev_node = it.node_->prev_node;
            it.node_->prev_node->next_node = it.node_->next_node;
            delete it.node_;
            --size_;
            return val;
        }

        void pop(size_t pos) {
            if (pos > size_ || pos < 0) {
                throw std::logic_error("lOsEr");
            }
            iterator it = begin() + pos;
            it.node_->next_node->prev_node = it.node_->prev_node;
            it.node_->prev_node->next_node = it.node_->next_node;
            delete it.node_;
            --size_;
        }

        T pop_back() {
            node *dying_node = tail_->prev_node;
            T val = dying_node->value_;
            dying_node->prev_node->next_node = dying_node->next_node;
            dying_node->next_node->prev_node = dying_node->prev_node;
            delete dying_node;
            --size_;
            return val;
        }

        list<T> remove(size_t pos1, size_t pos2) {
            if (pos2 < pos1 || pos2 - pos1 > size_ || pos1 < 0 || pos2 < 0 || pos2 - pos1 == 0) {
                throw std::logic_error("lOsEr");
            }
            for (int i = 0; i < pos2 - pos1 + 1; ++i) {
                pop(pos1);
            }
            return *this;
        }

        list<T> &operator=(const list<T> &other) {
            if (this != &other) {
                list<T> tmp;
                for (const auto &item: other) {
                    tmp.push_back(item);
                }
                swap(tmp);
            }
            return *this;
        }

        list<T> &operator+=(const list<T> &other) {
            if (this != &other) {
                for (const auto &item: other) {
                    push_back(item);
                }
            }
            return *this;
        }

        friend list<T> operator+(const list<T> &l, const list<T> &r) {
            list<T> tmp(l);
            tmp += r;
            return tmp;
        }

        size_t find(T value) {
            if (size_ == 0) {
                throw std::logic_error("lOsEr");
            } else {
                node *pos = head_->next_node;
                size_t num = 0;
                while (pos->next_node != nullptr) {
                    if (pos->value_ == value) {
                        return num;
                    }
                    num += 1;
                    pos = pos->next_node;
                }
                throw std::logic_error("lOsEr");
            }
        }

        T max() {
            T max_ = head_->next_node->value_;
            node *pos = head_->next_node;
            while (pos != nullptr) {
                max_ = std::max(pos->value_, max_);
                pos = pos->next_node;
            }
            return max_;
        }

        list<T> sort() {
            if constexpr (!std::is_arithmetic_v<T>) {
                throw std::logic_error("lOsEr");
            }
            list<T> result;
            while (head_->next_node != tail_.get()) {
                T tmp_ = max();
                result.push_back(tmp_);
                pop(find(tmp_));
            }
            swap(result);
            return *this;
        }

        size_t count(T value) {
            iterator it = begin();
            size_t num = 0;
            while (it != end()) {
                if (it.node_->value_ == value) {
                    num += 1;
                }
                ++it;
            }
            return num;
        }

        void alignment(T value) {
            node *pos = head_->next_node;
            while (pos != tail_.get()) {
                pos->value_ = value;
                pos = pos->next_node;
            }
        }

        void alignment_2(T value) {
            iterator it = begin();
            while (it != (begin() + size_ / 2)) {
                it.node_->value_ = value;
                ++it;
            }
        }

        void alignment_3(size_t pos1, size_t pos2, T value) {
            iterator it1 = begin() + pos1;
            iterator it2 = begin() + pos2 + 1;
            while (it1 != it2) {
                it1.node_->value_ = value;
                ++it1;
            }
        }

#pragma endregion

        void reverse() {
            node *prev = nullptr, *current = head_.get(), *next = nullptr;
            tail_.release();
            node *hed = head_.release();
            node *hvost = hed;
            while (current != nullptr) {
                next = current->next_node;
                current->next_node = prev;
                current->prev_node = next;
                prev = current;
                current = next;
            }
            hed = prev;
            tail_.reset(hvost);
            head_.reset(hed);
        }

        void my_reverse() {
            node *hed = head_.release();
            node *hvost = tail_.release();
            iterator begin_ = hed;
            iterator end_ = hvost;
            iterator current = hed->next_node;
            begin_.node_->next_node = end_.node_;
            (end_ - 1).node_->prev_node = current.node_;
            for (int i = 0; begin_ != end_; ++begin_, ++i) {
                begin_.node_->prev_node = (begin_ + 1).node_;
                (begin_ + 1).node_->next_node = begin_.node_;
            }
            tail_.reset(hvost);
            head_.reset(hed);
        }

    private:
        static bool lexicographical_compare_(const list<T> &l, const list<T> &r) {
            auto fl = l.begin(), fr = r.begin();
            for (; (fl != l.end()) && (fr != r.end()); ++fl, ++fr) {
                if (*fl < *fr) {
                    return true;
                }
                if (*fr < *fl) {
                    return false;
                }
            }
            return (fr == r.end()) && (fl == l.end());
        }

        size_t size_ = 0;
        std::unique_ptr<node> tail_;
        std::unique_ptr<node> head_;
//        node *tail_ = nullptr;
//        node *head_ = nullptr;
    };
}