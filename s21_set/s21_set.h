#ifndef SRC_S21_SET_S21_SET_H
#define SRC_S21_SET_S21_SET_H

#include <iostream>
#include "../s21_binary_tree/s21_tree.h"

namespace s21 {
    template<class Key>
    class set {
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = typename BinaryTree<value_type>::iterator;
        using const_iterator = typename BinaryTree<value_type>::const_iterator;
        using size_type = std::size_t;
        using rb_tree = BinaryTree<value_type>;
    private:
        rb_tree *rbTree_;

        /*
         * Set Member functions
        */
        set() : rbTree_(new rb_tree{}) {}

        set(std::initializer_list<value_type> const &items) {
            for (auto it: items) {
                insert(it);
            }
        }

        set(const set &s) : rbTree_(new rb_tree(*s)) {}

        set(set &&s) noexcept: rbTree_(new rb_tree(std::move(s))) {}

        ~set() {
            delete rbTree_;
            rbTree_ = nullptr;
        }

        set<key_type> &operator=(const set &s) {
            rbTree_ = s;
            return *this;
        }

        set<key_type> &operator=(set &&s) noexcept {
            rbTree_ = std::move(s);
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
            return rbTree_->insert(value, true);

        }

        void erase(iterator pos) {
            rbTree_->erase(pos);
        }

        void swap(set &other) {
            rbTree_->s21_swap(other);
        }

        void merge(set &other) {
            rbTree_->unique_merge(other);
        }

        /*
         * Set Lookup
         */
        iterator find(const Key &key) {
            return rbTree_->find(key);
        }

        bool contains(const Key &key) {
            return rbTree_->contains(key);
        }

    };
}

#endif  //  SRC_S21_SET_S21_SET_H