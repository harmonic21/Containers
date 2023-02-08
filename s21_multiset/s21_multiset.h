#ifndef SRC_S21_MULTISET_S21_MULTISET_H
#define SRC_S21_MULTISET_S21_MULTISET_H

#include <iostream>
#include "../s21_binary_tree/s21_tree.h"

namespace s21 {
    template<class Key>
    class multiset {
    public:
        /*
         * Multiset Member type
         */
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = typename BinaryTree<value_type>::iterator;
        using const_iterator = typename BinaryTree<value_type>::const_iterator;
        using size_type = std::size_t;
        using rb_tree = BinaryTree<value_type>;

        /*
         *  Multiset Member functions
         */
        multiset() : rbTree_(new rb_tree{}) {}

        multiset(std::initializer_list<value_type> const &items) {
            for (auto it: items) {
                insert(it);
            }
        }

        multiset(const multiset &ms) : rbTree_(new rb_tree(*ms.rbTree_)) {}

        multiset(multiset &&ms) noexcept : rbTree_(new rb_tree(std::move(ms.rbTree_))) {}

        ~multiset() {
            delete rbTree_;
            rbTree_ = nullptr;
        }

        multiset<value_type> &operator=(const multiset &ms) {
            rbTree_ = ms.rbTree_;
            return *this;
        }

        multiset<value_type> &operator=(multiset &&ms) noexcept {
            rbTree_ = std::move(ms.rbTree_);
            return *this;
        }

        /*
         * Multiset Iterators
         */

        iterator begin() noexcept {
            return  rbTree_->begin();
        }

        iterator end() noexcept {
            return rbTree_->begin();
        }

        const_iterator cbegin() const noexcept {
            return  rbTree_->cbegin();
        }

        const_iterator cend() const noexcept {
            return rbTree_->cend();
        }


        /*
         * Multiset Capacity
         */
        bool empty() const noexcept {
            rbTree_->empty();
        }

        size_type size() const noexcept {
            rbTree_->size();
        }

        size_type max_size() const noexcept {
            rbTree_->max_size();
        }

        /*
         * Multiset Modifiers
         */
        void clear() noexcept {
            rbTree_->clear();
        }

        iterator insert(const value_type& value) {
            rbTree_->insert_not_unique(value);
        }

        void erase(iterator pos) {
            rbTree_->erase(pos);
        }

        void swap(multiset& other) {
            rbTree_->swap(other);

        }
        void merge(multiset& other) {
            rbTree_->merge(other);
        }

        /*
         * Multiset Lookup
         */

        size_type count(const Key& key) {
        }

        iterator find(const Key& key) {
            rbTree_->find(key);
        }

        bool contains(const Key& key) {
            rbTree_->contains(key);
        }

        std::pair<iterator,iterator> equal_range(const Key& key) {

        }

        iterator lower_bound(const Key& key) {

        }
        iterator upper_bound(const Key& key) {

        }
    private:
        rb_tree *rbTree_;
    };
}  // namespace s21

#endif  //  SRC_S21_MULTISET_S21_MULTISET_H