#ifndef SRC_S21_MULTISET_S21_MULTISET_H
#define SRC_S21_MULTISET_S21_MULTISET_H

#include <iostream>
#include "s21_tree.h"

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

        multiset(std::initializer_list<value_type> const &items) : multiset() {
            for (auto it: items) {
                insert(it);
            }
        }

        multiset(const multiset &ms) : rbTree_(new rb_tree(*ms.rbTree_)) {}

        multiset(multiset &&ms) noexcept : rbTree_(new rb_tree(std::move(*ms.rbTree_))) {}

        ~multiset() {
            delete rbTree_;
            rbTree_ = nullptr;
        }

        multiset<value_type> &operator=(const multiset &ms) {
           *rbTree_ = *ms.rbTree_;
            return *this;
        }

        multiset<value_type> &operator=(multiset &&ms) noexcept {
            *rbTree_ = *std::move(ms.rbTree_);
            return *this;
        }

        /*
         * Multiset Iterators
         */

        iterator begin() noexcept {
            return  rbTree_->begin();
        }

        iterator end() noexcept {
            return rbTree_->end();
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
            return rbTree_->empty();
        }

        size_type size() const noexcept {
            return rbTree_->size();
        }

        size_type max_size() const noexcept {
            return rbTree_->max_size();
        }

        /*
         * Multiset Modifiers
         */
        void clear() noexcept {
            rbTree_->clear();
        }

        iterator insert(const value_type& value) noexcept {
            return rbTree_->insert_not_unique(value);
        }

        void erase(iterator pos) noexcept {
            rbTree_->erase(pos);
        }

        void swap(multiset& other) noexcept {
            rbTree_->s21_swap(*other.rbTree_);

        }

        void merge(multiset& other) noexcept {
            rbTree_->merge(*other.rbTree_);
        }

        /*
         * Multiset Lookup
         */

        size_type count(const Key& key) noexcept {
            std::pair<iterator, iterator> res = equal_range(key);
            int count = 0;
            while (res.first != res.second && *res.first == key) {
                count++;
                res.first++;
            }
            return count;
        }

        size_type count(const Key& key) const noexcept{
            std::pair<iterator, iterator> res = equal_range(key);
            int count = 0;
            while (res.first != res.second && *res.first == key) {
                count++;
                res.first++;

            }
            return count;
        }


        iterator find(const Key& key) const noexcept{
            return rbTree_->find(key);
        }

        bool contains(const Key& key) const noexcept{
            return rbTree_->contains(key);
        }

        std::pair<iterator,iterator> equal_range(const Key& key) noexcept {
            return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        std::pair<iterator,iterator> equal_range(const Key& key) const noexcept {
            return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
        }

        iterator lower_bound(const Key& key) {
           return rbTree_->lower_bound(key);
        }

        iterator upper_bound(const Key& key) {
            return rbTree_->upper_bound(key);
        }

        template<class... Args>
        std::vector<std::pair<iterator,bool>> emplace(Args&&... args) {
            return rbTree_->emplace(args...);
        }

    private:
        rb_tree *rbTree_;
    };
}  // namespace s21

#endif  //  SRC_S21_MULTISET_S21_MULTISET_H