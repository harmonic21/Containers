#ifndef SRC_S21_SET_S21_SET_H
#define SRC_S21_SET_S21_SET_H

#include <iostream>
#include "../s21_binary_tree/s21_tree.h"

namespace s21 {
    template<class Key>
    class set {
    public:
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = typename BinaryTree<value_type>::iterator;
        using const_iterator = typename BinaryTree<value_type>::const_iterator;
        using size_type = std::size_t;
        using rb_tree = BinaryTree<value_type>;

        /*
         * Set Member functions
        */
        set() : rbTree_(new rb_tree{}) {}

        set(std::initializer_list<value_type> const &items) : set() {
            for (auto it: items) {
                insert(it);
            }
        }

        set(const set &s) : rbTree_(new rb_tree(*s.rbTree_)) {}

        set(set &&s) noexcept: rbTree_(new rb_tree(std::move(*s.rbTree_))) {}

        ~set() {
            delete rbTree_;
            rbTree_ = nullptr;
        }

        set<value_type> &operator=(const set &s) {
            *rbTree_ = *s.rbTree_;
            return *this;
        }

        set<value_type> &operator=(set &&s) noexcept {
            *rbTree_ = std::move(*s.rbTree_);
            return *this;
        }

        /*
         * Set Iterators
         */
        iterator begin() noexcept {
            return rbTree_->begin();
        }

        iterator end() noexcept {
            return rbTree_->end();
        }

        const_iterator cbegin() const noexcept {
            return rbTree_->cbegin();
        }

        const_iterator cend() const noexcept {
            return rbTree_->cend();
        }

        /*
         * Set Capacity
         */
        bool empty() const noexcept {
            return rbTree_->empty();
        }

        size_type size() const noexcept {
            return rbTree_->size();
        }

        size_type max_size() const noexcept {
            return rbTree_->max_size();
        }

        /*
         * Set Modifiers
         */
        void clear() {
            return rbTree_->clear();
        }

        std::pair<iterator, bool> insert(const value_type &value) {
            return rbTree_->insert_unique(value);

        }

        void erase(iterator pos) {
            rbTree_->erase(pos);
        }

        void swap(set &other) {
            rbTree_->s21_swap(*other.rbTree_);
        }

        void merge(set &other) {
            rbTree_->unique_merge(*other.rbTree_);
        }

        /*
         * Set Lookup
         */
        iterator find(const Key &key) {
            auto result = rbTree_->find(key);
            return result == end() ? end() : result;
        }

        bool contains(const Key &key) {
            return rbTree_->contains(key);
        }
    private:
        rb_tree *rbTree_;
    };
}

#endif  //  SRC_S21_SET_S21_SET_H