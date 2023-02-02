#ifndef SRC_S21_SET_S21_SET_H
#define SRC_S21_SET_S21_SET_H
#include <iostream>
 #include "../s21_binary_tree/s21_tree.h"

namespace s21 {
    template<class Key>
    class set : private BinaryTree<Key> {
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = typename BinaryTree<key_type>::iterator;
        using const_iterator = typename BinaryTree<key_type>::const_iterator;
        using size_type = std::size_t;
        /*
         * Set Member functions
        */
        set();
        set(std::initializer_list<value_type> const &items);
        set(const set &s);
        set(set &&s);
        ~set();
        set<key_type>& operator=(const set &s);
        set<key_type>& operator=(set &&s) noexcept;
        /*
         * Set Iterators
         */
        iterator begin();
        iterator end();
        /*
         * Set Capacity
         */
        bool empty();
        size_type size();
        size_type max_size();
        /*
         * Set Modifiers
         */
        void clear();
        std::pair<iterator, bool> insert(const value_type& value);
        void erase(iterator pos);
        void swap(set& other);
        void merge(set& other);
        /*
         * Set Lookup
         */
        iterator find(const Key& key);
        bool contains(const Key& key);

    };
}

#endif  //  SRC_S21_SET_S21_SET_H