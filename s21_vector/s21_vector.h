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
        vector();
        explicit vector(size_type count);
        vector(std::initializer_list<value_type> const &items);
        vector(const vector &v);
        vector(vector &&v) noexcept;
        ~vector() noexcept;
        vector<T>& operator=(const vector &v);
        vector<T>& operator=(vector &&v) noexcept;

        reference at(size_type pos) const;
        reference operator[](size_type pos) noexcept;
        reference operator[](size_type pos) const noexcept;
        const_reference front() const;
        const_reference back() const;
        T* data() const;

        iterator begin() const noexcept;
        iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        void reserve(size_type new_cap);
        void resize(size_type count, const T& value);
        size_type capacity() const noexcept;
        void shrink_to_fit();

        void clear() noexcept;
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos) noexcept;
        void push_back(const_reference value);
        void pop_back();
        void swap(vector& other);

        template<class... Args >
        iterator emplace(const_iterator pos, Args&&... args);
        template<class... Args >
        void emplace_back(Args&&... args);
    private:
        void s21_remove_vector();
        void s21_change_capacity(size_type new_capacity);

    };


    /*
    * Vector Member functions
    */
    template<typename T>
    s21::vector<T>::vector() : capacity_(0), size_(0), values_(nullptr) { }

    template<typename T>
    s21::vector<T>::vector(size_type count) : capacity_(count), size_(count) {
        values_ = reinterpret_cast<T*>(new char[count * sizeof(T)]);
    }

    template<typename T>
    s21::vector<T>::vector(std::initializer_list<value_type> const &items) : capacity_(items.size()),
                                                                             size_(items.size()) {
        values_ = reinterpret_cast<T*>(new char[items.size() * sizeof(T)]);
        int j = 0;
        for(auto i : items) {
            new (values_ + j) T(i);
            j++;
        }
    }

    template<typename T>
    s21::vector<T>::vector(const vector &v) : capacity_(v.capacity_), size_(v.size_), values_(new T[v.capacity_]){
        memcpy(values_, v.values_, v.size_);
    }

    template<typename T>
    s21::vector<T>::vector(vector &&v) noexcept : capacity_(v.capacity_), size_(v.size_) {
        *this = std::move(v);
    }

    template<typename T>
    s21::vector<T>::~vector() noexcept {
        s21_remove_vector();
        values_ = nullptr;
        capacity_ = size_ = 0;
    }

/*
 * constructors overload
 */
    template<typename T>
    s21::vector<T>& s21::vector<T>::operator = (const vector &v) {
        if (this != &v) {
            this->s21_remove_vector();
            capacity_ = v.capacity_;
            size_ = v.size_;
            values_ = new T[capacity_];
            memcpy(values_, v.values_, size_);
        }
        return *this;
    }

    template<typename T>
    s21::vector<T>& s21::vector<T>::operator = (vector &&v) noexcept {
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
    template<typename T>
    typename s21::vector<T>::reference s21::vector<T>::at(size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("out of range");
        }
        return values_[pos];
    }

    template<typename T>
    typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) noexcept{
        return values_[pos];
    }

    template<typename T>
    typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) const noexcept{
        return values_[pos];
    }

    template<typename T>
    typename s21::vector<T>::const_reference s21::vector<T>::front() const {
        if (size_ == 0) {
            throw std::out_of_range("out of range");
        }
        return values_[0];
    }

    template<typename T>
    typename s21::vector<T>::const_reference s21::vector<T>::back() const {
        if (size_ == 0) {
            throw std::out_of_range("out of range");
        }
        return values_[size_ - 1];
    }

    template<typename T>
    typename s21::vector<T>::iterator s21::vector<T>::data() const {
        if (values_ == nullptr) {
            throw std::out_of_range("mass not exist");
        }
        return values_;
    }

    /*
     * Vector Iterators
     */
    template<typename T>
    typename s21::vector<T>::iterator s21::vector<T>::begin() const noexcept{
        return &values_[0];
    }

    template<typename T>
    typename s21::vector<T>::iterator s21::vector<T>::end() const noexcept {
        return &values_[size_];
    }

    template<typename T>
    typename s21::vector<T>::const_iterator s21::vector<T>::cbegin() const noexcept {
        return &values_[0];
    }

    template<typename T>
    typename s21::vector<T>::const_iterator s21::vector<T>::cend() const noexcept {
        return &values_[size_];
    }

    /*
     * Vector Capacity
     */
    template<typename T>
    bool s21::vector<T>::empty() const noexcept {
        return size_ == 0;
    }

    template<typename T>
    typename s21::vector<T>::size_type s21::vector<T>::size() const noexcept {
        return size_;
    }

    template<typename T>
    typename s21::vector<T>::size_type s21::vector<T>::max_size() const noexcept {
        return SIZE_MAX / sizeof(T) / 2;
    }

    template<typename T>
    void s21::vector<T>::reserve(size_type new_cap) {
        if (new_cap > max_size()) {
            throw std::length_error("new capacity greater then max size");
        }
        if (new_cap > capacity_) {
            s21_change_capacity(new_cap);
        }
    }

    template<typename T>
    void s21::vector<T>::resize(size_type count, const T& value ) {
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

    template<typename T>
    typename s21::vector<T>::size_type s21::vector<T>::capacity() const noexcept {
        return capacity_;
    }

    template<typename T>
    void s21::vector<T>::shrink_to_fit() {
        if (capacity_ > size_) {
            s21_change_capacity(size_);
        }
    }

    /*
     * Vector Modifiers
     */
    template<typename T>
    void s21::vector<T>::clear() noexcept{
        size_ = 0;
    }

    template<typename T>
    typename s21::vector<T>::iterator s21::vector<T>::insert(iterator pos, const_reference value) {
        iterator return_pos = pos;
        if (size_ == capacity_) {
            capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
        }
        T *new_arr = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);
            for (size_type i = 0, j = 0; i < size_ + 1; i++, j++) {
                if (&values_[j] == pos) {
                    new(new_arr + i) T(value);
                    return_pos = &new_arr[i];
                    i++;
                }
                new (new_arr + i) T(values_[j]);
            }
            s21_remove_vector();
            values_ = new_arr;
            size_++;
        return return_pos;
    }

    template<typename T>
    void s21::vector<T>::erase(iterator pos) noexcept {
        T *new_arr = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);
        size_--;
        for(size_type i = 0, j = 0; i <= size_; i++, j++) {
            if (&values_[i] == pos) {
                i++;
            }
            new (new_arr + j) T(values_[i]);
        }
        s21_remove_vector();
        values_ = new_arr;
    }

    template<typename T>
    void s21::vector<T>::push_back(const_reference value) {
        if (capacity_ == size_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (values_ + size_) T(value);
        size_++;
    }

    template<typename T>
    void s21::vector<T>::pop_back() {
        if (size_ != 0) {
            size_--;
            (values_ + size_)->~T();
        }
    }

    template<typename T>
    void s21::vector<T>::swap(vector& other) {
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


    template<typename T>
    void s21::vector<T>::s21_remove_vector() {
        if (values_) {
            for (size_type k = 0; k < size_; k++) {
                (values_ + k)->~T();
            }
            delete[] reinterpret_cast<char*>(values_);
        }
    }

    template<typename T>
    void s21::vector<T>::s21_change_capacity(size_type new_cap) {
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

    template<typename T>
    template<class... Args>
    void vector<T>::emplace_back(Args &&... args) {
        if (capacity_ == size_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new(values_ + size_) T(args...);
        size_++;
    }

    template<typename T>
    template<class... Args>
    typename vector<T>::iterator vector<T>::emplace(vector<T>::const_iterator pos, Args &&... args) {
        if (capacity_ == size_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        iterator it = insert(pos,new T(args...));
        return it;
    }

} // namespace s21
#endif  //  S21_VECTOR_S21_VECTOR_H