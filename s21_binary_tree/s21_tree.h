#ifndef CPP2_S21_CONTAINERS_0_MASTER_S_21_TREE_H
#define CPP2_S21_CONTAINERS_0_MASTER_S_21_TREE_H

#include <iostream>

namespace s21 {
    template<typename Key>
    class BinaryTree {
    private:
        class Iterator;

        class ConstIterator;

        class Node;

    public:
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        using size_type = size_t;
    private:
        Node *before_root_;
        Node *nil_;
        size_type size_;
    public:
        BinaryTree() : before_root_(new Node()), nil_(new Node()), size_(0) {
            before_root_->parent_ = nil_;
        };

        BinaryTree(const BinaryTree<value_type> &binaryTree) : BinaryTree() {
            if (!binaryTree.empty()) {
                s21_copy_tree(binaryTree);
            }
        }

        BinaryTree(BinaryTree &&binaryTree) noexcept: BinaryTree() {
            if (!binaryTree.empty()) {
                s21_swap(binaryTree);
                binaryTree.clear();
            }
        }

        BinaryTree<value_type> &operator=(const BinaryTree<value_type> &binaryTree) {
            if (binaryTree != this && !binaryTree.empty()) {
                clear();
                s21_copy_tree(binaryTree);
            }
            return *this;
        }

        BinaryTree<value_type> &operator=(BinaryTree<value_type> &&binaryTree) noexcept {
            if (binaryTree != this) {
                clear();
                s21_swap(binaryTree);
                binaryTree.clear();
            }
            return *this;
        }

        ~BinaryTree() {
            clear();
            delete before_root_->parent_;
            delete before_root_;
            before_root_ = nil_ = nullptr;
        }

        iterator begin() noexcept {
            return iterator(s21_min_node(before_root_->parent_), this);
        }

        iterator end() noexcept {
            return iterator(nil_, this);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(s21_min_node(before_root_->parent_));
        }

        const_iterator cend() const noexcept {
            return iterator(nil_, this);
        }

        bool empty() const noexcept {
            return size_ == 0;
        }

        size_type size() const noexcept {
            return size_;
        }

        size_type max_size() const noexcept {
            return ((SIZE_MAX / 2) / sizeof(BinaryTree<value_type> *)) - sizeof(Node *) * 2;
        }

        void clear() {
            if (size_ != 0) {
                s21_delete_all(before_root_->parent_);
            }
            before_root_->parent_ = nil_;
            size_ = 0;
        }

        std::pair<iterator, bool> insert_not_unique(const value_type &value) {
            Node *current = new Node(value);
            return insert(current, false);
        }

        std::pair<iterator, bool> insert_unique(const value_type &value) {
            Node *current = new Node(value);
            std::pair<iterator, bool> res = insert(current, true);
            if (res.second == false) {
                delete current;
            }
            return res;
        }

        std::pair<iterator, bool> insert(Node *new_node, bool is_unique) {
            Node *current_node = before_root_->parent_;
            Node *parent_for_new_node = nullptr;
            while (current_node != nil_) {
                parent_for_new_node = current_node;
                if (new_node->key_ < current_node->key_) {
                    current_node = current_node->left_;
                } else {
                    if (is_unique && current_node->key_ == new_node->key_) {
                        return {iterator(current_node, this), false};
                    }
                    current_node = current_node->right_;
                }
            }
            s21_nil_init(new_node);
            if (parent_for_new_node == nullptr) {
                before_root_->parent_ = new_node;
                new_node->red_ = false;
                new_node->parent_ = nil_;
            } else {
                new_node->parent_ = parent_for_new_node;
                if (new_node->key_ < parent_for_new_node->key_) {
                    parent_for_new_node->left_ = new_node;
                } else {
                    parent_for_new_node->right_ = new_node;
                }
            }
            size_++;
            s21_balancing_tree_after_insert(new_node);
            return {iterator(new_node, this), true};
        }

        void erase(iterator pos) {
            Node *current_node = pos.get_node();
            if (current_node != nil_) {
                s21_delete_node(current_node);
            }
        }

        void merge(BinaryTree<value_type> &other) {
            iterator it = other.begin();
            while (it != end()) {
                Node *other_current = it.get_node();
                it++;

                if (other_current->right_ != nil_) {
                    other_current->right_->parent_ = other_current->parent_;
                }
                if (other_current->parent_->left_ == other_current) {
                    other_current->parent_->left_ = other->end();
                } else if (other_current->parent_->right_ == other_current) {
                    other_current->parent_->right_ = other->end();
                }
                other_current->red_ = true;
                insert(other_current, false);
            }
        }

        void unique_merge(BinaryTree<value_type> &other) {
            iterator it = other.begin();
            while (it != end()) {
                Node *other_current = it.get_node();
                it++;
                if (!contains(const Key& key)) { // нет контейнс
                    s21_cut_node(other_current);
                    insert(other_current, false);
                }
            }
        }

        Node *s21_cut_node(Node *current) {
            if (current->left_ != nil_ && current->right_ != nil_ && current->red_) {
                Node *left_max = s21_max_node(current->left_);
                std::swap(left_max->key_, current->key_);
                s21_cut_node(left_max);
            } else if (current->left_ != nil_ && current->right_ != nil_ && !current->red_) {
                Node *left_max = s21_max_node(current->left_);
                std::swap(left_max->key_, current->key_);
                cut_node(left_max);
            } else if (!current->red_ && (current->left_ != nil_ || current->right_ != nil_)) {
                // у черного узла - если один ребенок, то точно красный без детей
                Node *son = current->left_ != nil_ ? current->left_ : current->right_;
                std::swap(son->key_, current->key_);
                s21_cut_node(son);
            } else if (current->red_ && current->right_ == nil_ && current->left_ == nil_) {
               s21_cut_son(current);
            } else if (!current->red_ && current->right_ == nil_ && current->left_ == nil_) {
                Node *parent = current->parent_;
                s21_cut_son(current);
                s21_balancing_tree_after_erase(parent);
            }
            size_--;
        }

        void s21_cut_son(Node *son) {
            if (son == son->parent_->left_) {
                son->parent_->left_ = nil_;
            } else {
                son->parent_->right_ = nil_;
            }
        }

        iterator find(const_reference value) {
            Node *current = before_root_->parent_;
            Node *result = end();
            while (current != nil_) {
                if (current->key_ < value) {
                    result = current;
                    current = current->left_;
                } else {
                    current = current->right_;
                }
            }
            return iterator(result);
        }

        bool contains(const Key &key) {
            iterator  it = find(key);
            return it != end();
        }

        iterator lower_bound(const Key &key) {

        }

        iterator upper_bound(const Key &key) {

        }

    private:
        void s21_nil_init(Node *current_node) {
            current_node->left_ = current_node->right_ = nil_;
        }

        void s21_delete_all(Node *current) {
            if (current != nil_) {
                s21_delete_all(current->left_);
                s21_delete_all(current->right_);
                delete current;
            }
        }


        void s21_copy_tree(BinaryTree<value_type> binaryTree) {
            for (auto it = binaryTree.begin(); it != binaryTree.end(); it++) {
                insert(*it);
            }
        }

        void s21_swap(BinaryTree<value_type> binaryTree) {
            std::swap(before_root_->parent_, binaryTree.before_root_->parent_);
            std::swap(size_, binaryTree.size_);
        }

        void s21_delete_node(Node *del) {
            if (del->left_ != nil_ && del->right_ != nil_ && del->red_) {
                Node *left_max = s21_max_node(del->left_);
                std::swap(left_max->key_, del->key_);
                s21_delete_node(left_max);
            } else if (del->left_ != nil_ && del->right_ != nil_ && !del->red_) {
                Node *left_max = s21_max_node(del->left_);
                std::swap(left_max->key_, del->key_);
                s21_delete_node(left_max);
            } else if (!del->red_ && (del->left_ != nil_ || del->right_ !=
                                                            nil_)) { // у черного узла - если один ребенок, то точно красный без детей
                Node *son = del->left_ != nil_ ? del->left_ : del->right_;
                std::swap(son->key_, del->key_);
                s21_delete_node(son);
            } else if (del->red_ && del->right_ == nil_ && del->left_ == nil_) {
                s21_delete_son(del);
            } else if (!del->red_ && del->right_ == nil_ && del->left_ == nil_) {
                Node *parent = del->parent_;
                s21_delete_son(del);
                s21_balancing_tree_after_erase(parent);
            }
            size_--;
        }

        void s21_delete_son(Node *son) {
            s21_cut_son(son);
            delete son;
        }

        //  https://habr.com/ru/company/otus/blog/521034/
        void s21_balancing_tree_after_erase(Node *current) {
            if (s21_is_red(current)
                && s21_is_black(current->left_)
                && s21_is_black(current->left_->left_)
                && s21_is_black(current->left_->right_)) {
                current->left_->red_ = true;
                current->red_ = false;
                current = current->parent_;
            } else if (s21_is_red(current)
                       && s21_is_black(current->left_)
                       && s21_is_red(current->left_->left_)) {
                s21_rotate_right(current);
            } else if (s21_is_black(current)
                       && s21_is_red(current->left_)
                       && s21_is_black(current->left_->left_)
                       && s21_is_black(current->left_->right_)) {
                current->left_->right_->red_ = true;
                current->left_->red_ = false;
                s21_rotate_right(current);
            } else if (s21_is_black(current)
                       && s21_is_red(current->left_)
                       && s21_is_red(current->left_->right_->left_)) {
                current->left_->right_->left_->red_ = false;
                s21_rotate_left(current->left_);
                s21_rotate_left(current);
            } else if (s21_is_black(current)
                       && s21_is_black(current->left_)
                       && s21_is_red(current->left_->right_)) {
                current->left_->right_->red_ = false;
                s21_rotate_left(current->left_);
                s21_rotate_left(current);
            } else {
                current->left_->red_ = true;
                s21_balancing_tree_after_erase(current->parent_);
            }
        }

        bool s21_is_red(Node *current) {
            return current != nullptr && current->red_;
        }

        bool s21_is_black(Node *current) {
            return current != nullptr && !current->red_;
        }

        Node *s21_max_node(Node *node) {
            Node *result = node;
            if (result == nil_) {
                result = before_root_->parent_;
            }
            while (result != nil_ && result->right_ != nil_) {
                result = result->right_;
            }
            return result;
        }

        Node *s21_node_prev(Node *node) {
            Node *result = nil_;
            if (node != nil_) {
                if (node->left_ != nil_) {
                    result = s21_max_node(node->left_);
                } else if (node == node->parent_->right_) {
                    result = node->parent_;
                } else {
                    Node *temp = node->parent_;
                    while (temp->parent_ != nil_ && temp == temp->parent_->left_) {
                        temp = temp->parent_;
                        if (temp->parent_ != nil_) {
                            result = temp->parent_;
                            break;
                        } else if (temp == before_root_->parent_) {
                            result = temp;
                            break;
                        }
                    }
                }
            }
            return result;
        }

        Node *s21_min_node(Node *node) {
            Node *result = node;
            if (result == nil_) {
                result = before_root_->parent_;
            }
            while (result != nil_ && result->left_ != nil_) {
                result = result->left_;
            }
            return result;
        }

        Node *s21_node_next(Node *node) {
            Node *result = nil_;
            if (node != nil_) {
                if (node->right_ != nil_) {
                    result = s21_min_node(node->right_);
                } else if (node == node->parent_->left_) {
                    result = node->parent_;
                } else {
                    while (node == node->parent_->right_) {     // while x is a right son
                        node = node->parent_;
                    }
                    result = node->parent_;
                }
            }
            return result;
        }

        void s21_balancing_tree_after_insert(Node *current_node) {
            while (current_node != before_root_->parent_ && current_node->parent_->red_) {
                if (current_node->parent_ == current_node->parent_->parent_->left_) {  //  parent of cn - is left son
                    Node *node = current_node->parent_->parent_->right_;
                    if (node != nil_ && node->red_) {
                        current_node->parent_->red_ = false;
                        node->red_ = false;
                        current_node = current_node->parent_->parent_;
                        current_node->red_ = true;
                    } else {
                        if (current_node == current_node->parent_->right_) {
                            current_node = current_node->parent_;
                            s21_rotate_left(current_node);
                        }
                        current_node->parent_->red_ = false;
                        current_node->parent_->parent_->red_ = true;
                        s21_rotate_right(current_node->parent_->parent_);
                    }
                } else if (current_node->parent_ ==
                           current_node->parent_->parent_->right_) {  // parent of cn - is right son
                    Node *node = current_node->parent_->parent_->left_;
                    if (node != nil_ && node->red_) {
                        current_node->parent_->red_ = false;
                        node->red_ = false;
                        current_node = current_node->parent_->parent_;
                        if (before_root_->parent_ != current_node) {
                            current_node->red_ = true;
                        }
                    } else {
                        if (current_node == current_node->parent_->left_) {
                            s21_rotate_right(current_node);
                            current_node = current_node->parent_;
                        }
                        current_node->parent_->red_ = false;
                        current_node->parent_->parent_->red_ = true;
                        s21_rotate_left(current_node->parent_->parent_);
                    }
                }
            }
        }

        void s21_rotate_left(Node *node) {
            Node *right_son = node->right_;
            if (right_son != nil_) {
                Node *parent = node->parent_;
                right_son->parent_ = parent;
                if (parent != nil_) {
                    if (node == parent->left_) {
                        parent->left_ = right_son;
                    } else {
                        parent->right_ = right_son;
                    }
                } else {
                    before_root_->parent_ = right_son;
                    right_son->parent_ = nil_;
                }
                node->right_ = right_son->left_;
                if (right_son->left_ != nil_) {
                    right_son->left_->parent_ = node;
                }
                right_son->left_ = node;
                node->parent_ = right_son;
            }
        }

        void s21_rotate_right(Node *node) {
            Node *left_son = node->left_;
            if (left_son != nil_) {
                Node *parent = node->parent_;
                left_son->parent_ = parent;
                if (parent != nil_) {
                    if (node == parent->left_) {
                        parent->left_ = left_son;
                    } else {
                        parent->right_ = left_son;
                    }
                } else {
                    before_root_->parent_ = left_son;
                    left_son->parent_ = nil_;
                }
                node->left_ = left_son->right_;
                if (left_son->right_ != nil_) {
                    left_son->right_->parent_ = node;
                }
                left_son->right_ = node;
                node->parent_ = left_son;
            }
        }

    private:
        class Node {
        public:
            bool red_;
            Node *parent_;
            Node *left_;
            Node *right_;
            value_type key_;
        public:
            Node()
                    : red_(false), parent_(nullptr), left_(nullptr), right_(nullptr), key_(value_type{}) {};

            explicit Node(Key key)
                    : red_(true), parent_(nullptr), left_(nullptr), right_(nullptr), key_(key) {};
        };


        class Iterator {
        private:
            Node *current_node_;
            BinaryTree<value_type> *binaryTree_;
        public:
            explicit Iterator(Node *n, BinaryTree<value_type> *binaryTree) : current_node_(n),
                                                                             binaryTree_(binaryTree) {};

            reference operator*() noexcept { return current_node_->key_; }

            iterator &operator++() noexcept {
                current_node_ = binaryTree_->s21_node_next(current_node_);
                return *this;
            }

            Node *get_node() { return current_node_; }

            iterator operator++(int) noexcept {
                iterator current = iterator(current_node_, binaryTree_);
                ++(*this);
                return current;
            }

            iterator &operator--() noexcept {
                current_node_ = binaryTree_->s21_node_prev(current_node_);
                return *this;
            }

            iterator operator--(int) noexcept {
                iterator current = iterator(current_node_, binaryTree_);
                --(*this);
                return current;
            }

            bool operator==(const iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator==(const const_iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator!=(const const_iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }

            bool operator!=(const iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }
        };

        class ConstIterator {
        private:
            const Node *current_node_;
            const BinaryTree<value_type> *binaryTree_;
        public:
            ConstIterator(const Node *n, const BinaryTree<value_type> *binaryTree)
                    : current_node_(n), binaryTree_(binaryTree) {};

            reference operator*() const noexcept { return current_node_->key_; }

            const_iterator &operator++() noexcept {
                current_node_ = binaryTree_->s21_node_next(current_node_);
                return *this;
            }

            const Node *get_node() { return current_node_; }

            const_iterator operator++(int) noexcept {
                const_iterator current = const_iterator(current_node_, binaryTree_);
                ++(*this);
                return current;
            }

            const_iterator &operator--() noexcept {
                current_node_ = binaryTree_->s21_node_prev(current_node_);
                return *this;
            }

            const_iterator operator--(int) noexcept {
                const_iterator current = const_iterator(current_node_, binaryTree_);
                --(*this);
                return current;
            }

            bool operator==(const const_iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator==(const iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator!=(const const_iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }

            bool operator!=(const iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }

        };
    };

}  //  namespace s21


#endif //CPP2_S21_CONTAINERS_0_MASTER_S_21_TREE_H
