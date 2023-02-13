#ifndef S21_VECTOR_S21_VECTOR_H
#define S21_VECTOR_S21_VECTOR_H
#include <iostream>

namespace s21 {
    template <typename T>
    class vector {
    public:
        using value_type = T;
        using size_type = size_t;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
    private:
        size_type capacity_;
        size_type size_;
        value_type* values_;
    public:
        /*
        * Vector Member functions
        */
        vector() : capacity_(0), size_(0), values_(nullptr) { }

        vector(size_type count) : capacity_(count), size_(count) {
            values_ = reinterpret_cast<T*>(new char[count * sizeof(T)]);
            memset(values_, 0, sizeof(T) * count);
        }

       vector(std::initializer_list<value_type> const &items) : capacity_(items.size()),
                                                                                 size_(items.size()) {
            values_ = reinterpret_cast<T*>(new char[items.size() * sizeof(T)]);
            int j = 0;
            for(auto i : items) {
                new (values_ + j) T(i);
                j++;
            }
        }

       vector(const vector &v) : capacity_(v.capacity_), size_(v.size_) {
            values_ = reinterpret_cast<T*>(new char[v.capacity_ * sizeof(T)]);
            memcpy(values_, v.values_, v.size_ * sizeof(T));
        }

        vector(vector &&v) noexcept : capacity_(v.capacity_), size_(v.size_), values_(nullptr) {
            std::swap(values_, v.values_);
            v.size_ = v.capacity_ = 0;
        }

       ~vector() noexcept {
            s21_remove_vector();
            values_ = nullptr;
            capacity_ = size_ = 0;
        }

/*
 * constructors overload
 */
        vector<T>& operator = (const vector &v) {
            if (this != &v) {
                this->s21_remove_vector();
                capacity_ = v.capacity_;
                size_ = v.size_;
                values_ = new T[capacity_];
                memcpy(values_, v.values_, size_);
            }
            return *this;
        }

       vector<T>& operator = (vector &&v) noexcept {
            if (this != &v) {
                this->s21_remove_vector();
                capacity_ = v.capacity_;
                size_ = v.size_;
                values_ = v.values_;

                v.capacity_ = v.size_ = 0;
                v.values_ = nullptr;
            }
            return *this;
        }

/*
 * Vector Element access
 */

       reference at(size_type pos) const {
            if (pos >= size_) {
                throw std::out_of_range("out of range");
            }
            return values_[pos];
        }

        reference operator[](size_type pos) noexcept{
            return values_[pos];
        }

        reference operator[](size_type pos) const noexcept{
            return values_[pos];
        }

       const_reference front() const {
            if (size_ == 0) {
                throw std::out_of_range("out of range");
            }
            return values_[0];
        }

       const_reference back() const {
            if (size_ == 0) {
                throw std::out_of_range("out of range");
            }
            return values_[size_ - 1];
        }

       iterator data() const {
            if (values_ == nullptr) {
                throw std::out_of_range("mass not exist");
            }
            return values_;
        }

        /*
         * Vector Iterators
         */
        iterator begin() const noexcept{
            return &values_[0];
        }

        iterator end() const noexcept {
            return &values_[size_];
        }

        const_iterator cbegin() const noexcept {
            return &values_[0];
        }

        const_iterator cend() const noexcept {
            return &values_[size_];
        }

        /*
         * Vector Capacity
         */
        bool empty() const noexcept {
            return size_ == 0;
        }

        size_type size() const noexcept {
            return size_;
        }

        size_type max_size() const noexcept {
            return SIZE_MAX / sizeof(T) / 2;
        }

        void reserve(size_type new_cap) {
            if (new_cap > max_size()) {
                throw std::length_error("new capacity greater then max size");
            }
            if (new_cap > capacity_) {
                s21_change_capacity(new_cap);
            }
        }

        void resize(size_type count, const T& value ) {
            if (count < capacity_) {
                s21_change_capacity(count);
            }
            for(size_type i = 0; i < size_; i++) {
                new (values_ + i) T(value);
            }
            if (count < size_) {
                size_ = count;
            }
        }

        size_type capacity() const noexcept {
            return capacity_;
        }

        void shrink_to_fit() {
            if (capacity_ > size_) {
                s21_change_capacity(size_);
            }
        }

        /*
         * Vector Modifiers
         */
        void clear() noexcept{
            size_ = 0;
        }

      iterator insert(iterator pos, const_reference value) {
            iterator return_pos = pos;
            if (size_ == capacity_) {
                capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
            }
            T *new_arr = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);
            if (pos != nullptr) {
                for (size_type i = 0, j = 0; i < size_ + 1; i++, j++) {
                    if (&values_[j] == pos) {
                        new(new_arr + i) T(value);
                        return_pos = &new_arr[i];
                        i++;
                    }
                    if ( j < size_) {
                        new(new_arr + i) T(values_[j]);
                    }
                }
                s21_remove_vector();
            } else {
                new(new_arr) T(value);
                return_pos = new_arr;
            }
            values_ = new_arr;
            size_++;
            return return_pos;
        }

        void erase(iterator pos) noexcept {
            T *new_arr = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);
            size_--;
            for(size_type i = 0, j = 0; i <= size_; i++) {
                if (&values_[i] == pos) {
                    continue;
                }
                new (new_arr + j) T(values_[i]);
                j++;
            }
            s21_remove_vector();
            values_ = new_arr;
        }

        void push_back(const_reference value) {
            if (capacity_ == size_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            new (values_ + size_) T(value);
            size_++;
        }

        void pop_back() {
            if (size_ != 0) {
                size_--;
                (values_ + size_)->~T();
            }
        }


        void swap(vector& other) {
            auto *temp_arr = other.values_;
            size_type temp_capacity = other.capacity_;
            size_type temp_size = other.size_;
            other.values_ = values_;
            other.capacity_ = capacity_;
            other.size_ = size_;
            values_ = temp_arr;
            size_ = temp_size;
            capacity_ = temp_capacity;
        }

        template<class... Args>
        void emplace_back(Args &&... args) {
            if (capacity_ == size_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            new(values_ + size_) T(args...);
            size_++;
        }

        template<class... Args>
      iterator emplace(vector<T>::const_iterator pos, Args &&... args) {
            if (capacity_ == size_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            iterator it = insert(pos,new T(args...));
            return it;
        }

    private:
        void s21_remove_vector() {
            if (values_) {
                for (size_type k = 0; k < size_; k++) {
                    (values_ + k)->~T();
                }
               delete[] reinterpret_cast<char*>(values_);
            }
        }

        void s21_change_capacity(size_type new_cap) {
            T *temp_arr = reinterpret_cast<T*>(new char[new_cap * sizeof(T)]);
            size_type i = 0;
            try {
                for (; i < size_; i++) {
                    new(temp_arr + i) T(values_[i]);
                }
            } catch (...) {
                for (size_type j = 0; j < i; j++) {
                    (temp_arr + i)->~T();
                }
                delete[] reinterpret_cast<int8_t*>(temp_arr);
                throw;
            }
            s21_remove_vector();
            values_ = temp_arr;
            capacity_ = new_cap;
        }

    };


} // namespace s21
#endif  //  S21_VECTOR_S21_VECTOR_H