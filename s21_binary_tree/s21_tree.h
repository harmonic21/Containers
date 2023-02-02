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
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        using size_type = std::size_t;
    private:
        Node* before_root_;
        Node* nil_;
        size_type size_;
    public:
        BinaryTree() : before_root_(new Node()), nil_(new Node()), size_(0) {
            before_root_->parent_ = nil_;
        };

        BinaryTree(const BinaryTree<value_type> &binaryTree) : BinaryTree() {

        }

        BinaryTree(BinaryTree&& other) noexcept : BinaryTree() {

        }

        BinaryTree<value_type>& operator=(const BinaryTree<value_type> &binaryTree) {

        }

        BinaryTree<value_type>& operator=(BinaryTree<value_type> &&binaryTree) noexcept {

        }
        ~BinaryTree() {

        }

        iterator begin() noexcept {
            return iterator(minNode(before_root_->parent_), this);
        }

        iterator end() noexcept {
            return iterator(nil_, this);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(minNode(before_root_->parent_));
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

        size_type max_size() const noexcept;

        void clear();

        std::pair<iterator, bool> insert(const value_type& value) {
            Node* new_node = new Node(value);
            s21_nil_init(new_node);
            Node* current_node = before_root_->parent_;
            Node* parent_for_new_node = nullptr;
            while (current_node != nil_) {
                parent_for_new_node = current_node;
                if (value < current_node->key_) {
                    current_node = current_node->left_;
                } else {
                    current_node = current_node->right_;
                }
            }
            if (parent_for_new_node == nullptr) {
                before_root_->parent_ = new_node;
                new_node->red_ = false;
            } else {
                new_node->parent_ = parent_for_new_node;
                if (value < parent_for_new_node->key_) {
                    parent_for_new_node->left_ = new_node;
                } else {
                    parent_for_new_node->right_ = new_node;
                }
            }
            size_++;
          //  s21_balancingTree();
            return {iterator(new_node, this), true};
        }

        void s21_nil_init(Node* current_node) {
            current_node->left_ = current_node->right_ = nil_;
        }

        void erase(iterator pos);

    private:

        Node* maxNode(Node* current) {
            Node* temp = current;
            if (temp == nil_) {
                temp = before_root_->parent_;
            }
            while(temp != nil_ && temp->right_ != nil_) {
                temp = temp->right_;
            }
            return temp;
        }

        Node* minNode(Node* current) {
            Node* temp = current;
            if (temp == nil_) {
                temp = before_root_->parent_;
            }
            while (temp != nil_ && temp->left_ != nil_) {
                temp = temp->left_;
            }
            return temp;
        }

        Node* nodeNext(const Node* node) {
            Node* result = nil_;
            if (node != nil_) {
                if (node->right_ != nil_) {
                    result = (Node*) minNode(node->right_);
                } else if (node == node->parent_->left_) {
                    result = node->parent_;
                }
            }
            return result;
        }

        Node* nodePrev(Node* node) {
           Node* result = node;
            if (node != nil_) {
                if (node->left_ != nil_) {
                    result = maxNode(node->left_);
                } else if (node == node->parent_->right_) {
                    result = node->parent_;
                } else {
                    Node* temp = node->parent_;
                    while(temp->parent_ != nil_ && temp == temp->parent_->left_) {
                        temp = temp->parent_;
                        if (temp->parent_ != nil_) {
                            result = temp->parent_;
                            break;
                        } else if (temp == *begin()) {
                            result = temp;
                            break;
                        }
                    }
                }
            }
            return result;
        }

       void s21_balancingTree();

       void s21_rotateLeft(Node* node) {
            Node* right_son = node->right_;
            if (right_son != nullptr) {
                Node *parent = node->parent_;
                right_son->parent_ = parent;
                before_root_->parent_ = right_son;
                if (node == parent->left_) {
                    parent->left_ = right_son;
                } else {
                    parent->right_ = right_son;
                }
                node->right_ = right_son->left_;
                if (right_son->left_ != nullptr) {
                    right_son->left_->parent_ = node;
                }
                right_son->left_ = node;
                node->parent_ = right_son;
            }
       }

       void rightRotation(Node* node) {
           Node*  left_son = node->left_;
           if (left_son != nullptr) {
               Node* parent = node->parent_;
               left_son->parent_ = parent;
               before_root_->parent_ = left_son;
               if (node == parent->left_) {
                   parent->left_ = left_son;
               } else {
                   parent->right_ = left_son;
               }
               node->left_ = left_son->right_;
               if (left_son->right_ != nullptr) {
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
            Node* parent_;
            Node* left_;
            Node* right_;
            value_type key_;
        public:
            Node()
                    : red_(false), parent_(nullptr), left_(nullptr), right_(nullptr), key_(value_type{}) {};
            explicit Node(Key key)
                    : red_(true), parent_(nullptr), left_(nullptr), right_(nullptr), key_(key) {};
        };


       class Iterator {
       private:
           Node* current_node_;
           BinaryTree<value_type>* binaryTree_;
       public:
           explicit Iterator(Node* n, BinaryTree<value_type>* binaryTree) : current_node_(n), binaryTree_(binaryTree) { };
           reference operator*() noexcept { return current_node_->key_; }

           iterator& operator++() noexcept {
               current_node_ = (Node*) binaryTree_->nodeNext(current_node_);
               return *this;
           }

            iterator operator++(int) noexcept {
                iterator current = iterator(current_node_, binaryTree_);
                ++(*this);
                return current;
            }

            iterator& operator--() noexcept {
                current_node_ = (Node*) binaryTree_->nodePrev(current_node_);
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

        };

    };

}  //  namespace s21


#endif //CPP2_S21_CONTAINERS_0_MASTER_S_21_TREE_H
