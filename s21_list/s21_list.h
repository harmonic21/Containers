#ifndef S21_LIST_H
#define S21_LIST_H
#include <iostream>

namespace s21 {
    template<typename T>
    class list {
    private:
        class node;
        class ListIterator;
        class ListConstIterator;
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = ListIterator;
        using const_iterator = ListConstIterator;
        using size_type = std::size_t;
    private:
        node* first_;
        node* last_;
        size_type size_;
    public:
        list();
        explicit list(size_type n);
        list(std::initializer_list<value_type> const &items);
        list(const list &l);
        list(list&& other) noexcept;
        ~list();
        list<T>& operator=(const list &l);
        list<T>& operator=(list &&l) noexcept;

        const_reference front() const;
        const_reference back() const;

        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;

        void clear();
        iterator insert(iterator pos, const_reference value);
        iterator insert(const_iterator pos, const_reference value);
        void erase(iterator pos);
        void erase(const_iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(list& other);
        void merge(list& other);
        void splice(const_iterator pos, list& other);
        void reverse();
        void unique();
        void sort();  //  use merge sort
    private:
        node* s21_merge(node* a, node* b);
        void s21_split(node* head, node** b);
        void s21_merge_sort(node** current);
        void s21_remove_node(node* n);

    private:
        class node {
        public:
            node* prev_;
            node* next_;
            value_type value_;

            node() = delete;
            node(node* prev, node* next, value_type value) : prev_(prev), next_(next), value_(value) { };
            ~node() = default;
        };


        class ListIterator {
        public:
            // One of the @link iterator_tags tag types@endlink.
            typedef std::random_access_iterator_tag  iterator_category;
            // The type "pointed to" by the iterator.
            typedef T value_type;
            // Distance between iterators is represented as this type.
            typedef  std::ptrdiff_t  difference_type;
            // This type represents a pointer-to-value_type.
            typedef T*   pointer;
            // This type represents a reference-to-value_type.
            typedef T& reference;

        private:
            node* current_node_;
        public:
            ListIterator() = delete;
            explicit ListIterator(node* n) : current_node_(n) { };
            reference operator*() const noexcept { return current_node_->value_; }

            iterator& operator++() noexcept {
                current_node_ = current_node_->next_;
                return *this;
            }

            iterator operator++(int) noexcept {
                current_node_ = current_node_->next_;
                return *this;
            }

            iterator& operator--() noexcept {
                current_node_ = current_node_->prev_;
                return *this;
            }

            iterator operator--(int) noexcept {
                iterator current = iterator(current_node_);
                --*this;
                return current;
            }

            bool operator==(const iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator==(const const_iterator &other) const noexcept {
                node* temp = other.current_node_;
                return current_node_ == temp;
            }

            bool operator!=(const const_iterator &other) const noexcept {
                node* temp = other.current_node_;
                return current_node_ != temp;
            }

            bool operator!=(const iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }

            node *getCurrentNode() const noexcept {
                return current_node_;
            }

        };

        class ListConstIterator {
        public:
            typedef std::random_access_iterator_tag  iterator_category;
            typedef T value_type;
            typedef std::ptrdiff_t  difference_type;
            typedef T* pointer;
            typedef T& reference;
        private:
            const node* current_node_;
        public:
            ListConstIterator() = delete;
            explicit ListConstIterator(node* n) : current_node_(n) { };

            reference operator*() const noexcept {
                node* temp = (node*)current_node_;
                return temp->value_;
            }

            const_iterator& operator++() noexcept {
                current_node_ = current_node_->next_;
                return *this;
            }

            const_iterator operator++(int) noexcept {
                const_iterator current = const_iterator(current_node_);
                ++(*this);
                return current;
            }

            const_iterator& operator--() noexcept {
                current_node_ = current_node_->prev_;
                return *this;
            }

            const_iterator operator--(int) noexcept {
                const_iterator current = const_iterator(current_node_);
                --(*this);
                return current;
            }

            bool operator==(const const_iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator!=(const const_iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }

            node *getCurrentNode() const noexcept {
                return (node*)current_node_;
            }
        };
    };

    template<typename T>
    list<T>::list() : first_(new node(nullptr, nullptr, value_type{})), last_(first_), size_(0) {
        last_ = first_;
    };

    template<typename T>
    list<T>::list(size_type n) : list() {
        for (size_type i = 0; i < n; i++) {
            push_back(value_type{});
        }
    }

    template<typename T>
    list<T>::list(std::initializer_list<value_type> const &items) : list() {
        for(auto i : items) {
            push_back(i);
        }
    }

    template<typename T>
    list<T>::list(const list &l) : list() {
        for (auto i = l.cbegin(); i != l.cend(); ++i) {
          push_back(*i);
      }
    }

    template<typename T>
    list<T>::list(list&& other) noexcept : list() {
        splice(cbegin(), other);
    }

    template<typename T>
     list<T>::~list() {
         clear();
         delete last_;
         first_ = last_ = nullptr;
     }

     template<typename T>
     list<T>& list<T>::operator = (const list &l) {
         if (this != &l) {
            clear();
             for(auto i : l) {
                 push_back(i);
             }
         }
         return *this;
    }

    template<typename T>
    list<T>& list<T>::operator = (list &&l) noexcept {
       if (this != &l) {
           clear();
           splice(begin(), l);
       }
        return *this;
   }

/*
 * List Element access*
 */
    template<typename T>
    typename list<T>::const_reference list<T>::front() const {
        if (size_ == 0) {
            throw std::out_of_range("list is empty");
        }
        return first_->value_;
    }

    template<typename T>
    typename list<T>::const_reference list<T>::back() const {
        if (size_ == 0) {
            throw std::out_of_range("list is empty");
        }
        return last_->prev_->value_;
    }

    template<typename T>
    typename list<T>::iterator list<T>::begin() noexcept {
        return iterator(first_);
    }

    template<typename T>
    typename list<T>::iterator list<T>::end() noexcept {
        return iterator(last_);
    }

    template<typename T>
    typename list<T>::const_iterator list<T>::cbegin() const noexcept {
        return const_iterator(first_);
    }

    template<typename T>
    typename list<T>::const_iterator list<T>::cend() const noexcept {
        return const_iterator(last_);
    }

    template<typename T>
    bool list<T>::empty() const noexcept{
        return size_ == 0;
    }

    template<typename T>
    typename list<T>::size_type list<T>::size() const noexcept{
        return size_;
    }

    template<typename T>
    typename list<T>::size_type list<T>::max_size() const noexcept {
        return SIZE_MAX / sizeof(node) / 2;
    }

    template<typename T>
    void list<T>::clear() {
        while (size() > 0) {
            erase(begin());
        }
    }

    template<typename T>
    typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
        node* current;
        node* next = pos.getCurrentNode();
        if (size_ == 0) {
            push_back(value);
            current = first_;
        } else {
            node *before = next->prev_;
            if (before == nullptr) {
                push_front(value);
                current = first_;
            } else {
                node *new_node = new node(before, next, value);
                before->next_ = new_node;
                next->prev_ = new_node;
                current = new_node;
                size_++;
            }
        }
        return iterator(current);
    }

    template<typename T>
    typename list<T>::iterator list<T>::insert(const_iterator pos, const_reference value) {
        node* current;
        node* next = pos.getCurrentNode();
        if (size_ == 0) {
            push_back(value);
            current = first_;
        } else {
            node *before = next->prev_;
            if (before == nullptr) {
                push_front(value);
                current = first_;
            } else {
                node *new_node = new node(before, next, value);
                before->next_ = new_node;
                next->prev_ = new_node;
                current = new_node;
                size_++;
            }
        }
        return iterator(current);
    }


    template<typename T>
    void list<T>::erase(iterator pos) {
        if (pos != end()) {
            node* current = pos.getCurrentNode();
            s21_remove_node(current);
            delete current;
        }
    }

    template<typename T>
    void list<T>::erase(const_iterator pos) {
        if (pos != cend()) {
            node* current = pos.getCurrentNode();
            s21_remove_node(current);
            delete current;
        }
    }


    template<typename T>
    void list<T>::push_back(const_reference value) {
        node* current = new node(last_->prev_, last_, value);
        if (size_ > 0) {
            last_->prev_->next_ = current;
        } else {
            first_ = current;
        }
        last_->prev_ = current;
        size_++;
    }

    template<typename T>
    void list<T>::pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("size == 0");
        }
        iterator it = end();
        erase(it--);
    }

    template<typename T>
    void list<T>::push_front(const_reference value) {
       node* current = new node(nullptr, first_, value);
       if (size_ > 0) {
           first_->prev_ = current;
       } else {
           last_->prev_ = current;
       }
       first_ = current;
       size_++;
    }

    template<typename T>
    void list<T>::pop_front() {
        if (size_ == 0) {
            throw std::out_of_range("size == 0");
        }
        erase(begin());
    }

    template<typename T>
    void list<T>::swap(list& other) {
        if (this != &other) {
            std::swap(size_, other.size_);
            std::swap(first_, other.first_);
            std::swap(last_, other.last_);
        }
    }

    template<typename T>
    void list<T>::merge(list& other) {
        iterator it = begin();
        iterator oth_it1 = other.begin();
        while (oth_it1 != other.end() && it != end()) {
            if (*it > *oth_it1) {
                insert(it, *oth_it1);
                oth_it1++;
            } else {
                it++;
            }
        }
        while(oth_it1 != other.end()) {
            push_back(*oth_it1);
            oth_it1++;
        }
        other.clear();
    }

    template<typename T>
    void list<T>::splice(const_iterator pos, list& other) {
        if (!other.empty() && other.begin() != begin()) {
            node *current = pos.getCurrentNode();
            node *prev = current->prev_;
            other.last_->prev_->next_ = current;
            current->prev_ = other.last_->prev_;
            other.first_->prev_ = prev;

            if (prev != nullptr) {
                prev->next_ = other.first_;
            } else {
                first_ = other.first_;
            }
            size_ += other.size_;
            other.size_ = 0;
            delete other.last_;
            other.first_ = other.last_ = nullptr;
        }
    }

    template<typename T>
    void list<T>::reverse() {
        if (size_ > 1) {
            iterator it_begin = begin();
            iterator it_end = end();
            it_end--;
            for (size_type i = 0; i < size_ / 2; i++) {
                std::swap(*it_begin, *it_end);
                it_begin++;
                it_end--;
            }
        }
    }

    template<typename T>
    void list<T>::unique() {
        if (size_ > 1) {
            iterator temp = begin();
            temp++;
            for (iterator i = begin(); i != end(); i++) {
                if (*temp == *i) {
                    iterator del = iterator(temp.getCurrentNode());
                    temp = i;
                    erase(del);
                } else {
                    temp++;
                }
            }
        }
    }

    template<typename T>
    void list<T>::sort() {
        if (size_ > 1) {
            last_->prev_->next_ = nullptr;
            node* temp = last_;
            this->s21_merge_sort(&first_);
            last_->next_ = temp;
            temp->prev_ = last_;
            last_ = temp;
        }
   }

    template<typename T>
    void list<T>::s21_split(node* head, node** b) {
        node* slow = head;
        node* fast = head->next_;

        while (fast != nullptr) {
            fast = fast->next_;
            if (fast != nullptr) {
                slow = slow->next_;
                fast = fast->next_;
            }
        }
            *b = slow->next_;
            slow->next_ = nullptr;
    }

    template<typename T>
    typename list<T>::node* list<T>::s21_merge(node* a, node* b) {
        if (a == nullptr) {
            return b;
        }

        if (b == nullptr) {
            return a;
        }
        if (a->value_ <= b->value_) {
            a->next_ = s21_merge(a->next_, b);
            a->next_->prev_ = a;
            a->prev_ = nullptr;
            if (a->next_->next_ == nullptr) {
                last_ = a->next_;
            }
            return a;
        } else {
            b->next_ = s21_merge(a, b->next_);
            b->next_->prev_ = b;
            b->prev_ = nullptr;
            if (b->next_->next_ == nullptr) {
                last_ = b->next_;
            }
            return b;
        }
    }


    template<typename T>
    void list<T>::s21_merge_sort(node** current) {
        if (*current == nullptr || (*current)->next_ == nullptr) {
            return;
        }
        node* a = *current;
        node* b = nullptr;
        s21_split(*current, &b);

        s21_merge_sort(&a);
        s21_merge_sort(&b);

         *current = s21_merge(a, b);
    }

    template<typename T>
    void list<T>::s21_remove_node(node* current) {
            node *prev = current->prev_;
            node *next = current->next_;
            if (prev != nullptr && next != nullptr) {
                prev->next_ = next;
                next->prev_ = prev;
            } else if (prev == nullptr && next != nullptr) {
                first_ = next;
                next->prev_ = nullptr;
            } else if (prev != nullptr) {
                last_->next_ = prev;
                prev->next_ = nullptr;
            }
            size_--;
    }

}  //  namespace s21

#endif  //  S21_LIST_H