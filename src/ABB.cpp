// Copyright 2018

/**
 * @file   ABB.cpp
 * @brief  Implementação da Classe ABB e da Estrutura Node juntamente de seus
 * respectivos atributos e métodos.
 *
 * @author Gleydvan
 * @author JohnVithor
 * @author JoMedeiros
 *
 * @since  20/05/2018
 * @date   20/05/2018
 */

#include "ABB.h"

Node::Node(DataType value, Node* l, Node* r) : left(l), right(r), data(value) {
    if (l == nullptr) {
        l_cnt = countChildren(l) + 1;
    } else {
        l_cnt = 0;
    }
    if (r == nullptr) {
        r_cnt = countChildren(r) + 1;
    } else {
        r_cnt = 0;
    }
}

int Node::countChildren(Node* n) {
    if (n == nullptr) {
        return -1;
    }
    return n->r_cnt + n->l_cnt;
}

ABB::ABB(Node* r) : root(r), size(0) {}

ABB::~ABB() { recursiveErase(root); }

void ABB::recursiveErase(Node* node) {
    if (node != nullptr) {
        Node* left = node->left;
        node->left = nullptr;
        Node* right = node->right;
        node->right = nullptr;
        recursiveErase(left);
        recursiveErase(right);
        delete node;
    }
}

Node* ABB::getRoot() { return root; }

/**
 * Search normal.
 */
Node* ABB::search(const DataType target) {
    Node* current = this->root;
    DataType data = DataType();
    while (current != nullptr) {
        data = current->data;
        if (data == target) {
            return current;
        }
        if (data < target) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return nullptr;
}
/**
 * Insert Padrão... Segundo o PDF eu acho que não é possivel usar ele.
 */
bool ABB::insert(const DataType target) {
    Node* current = this->root;
    DataType data = DataType();
    if (this->root == nullptr) {
        this->root = new Node(target);
        ++size;
        return true;
    }
    while (current != nullptr) {
        data = current->data;
        if (data == target) {
            return false;
        }
        if (data > target) {
            if (current->left == nullptr) {
                current->left = new Node(target);
                ++size;
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new Node(target);
                ++size;
                return true;
            }
            current = current->right;
        }
    }
    return false;
}

bool ABB::remove(const DataType target) {
    Node* current = this->root;
    Node* before = current;
    DataType data = DataType();
    while (current != nullptr) {
        data = current->data;
        if (data == target) {
            // Nenhum filho
            if (current->left == nullptr && current->right == nullptr) {
                if (before->left == current) {
                    before->left = nullptr;
                } else if (before->right == current) {
                    before->right = nullptr;
                }
                delete current;
                --size;
                return true;
            }
            // Um único filho
            if (false) {
                return false;
            }
            // Dois filhos
            if (false) {
                return false;
            }
        }
    }
    return false;
}

int ABB::enesimoElemento(const int n) {
    int nodes = 0;
    Node* current = root;
    while (current == nullptr) {
        nodes = current->l_cnt + 1;
        if (nodes == n) {
            return current->data;
        }
        if (nodes < n) {
            current = current->right;
        } else {
            nodes = 0;
            current = current->left;
        }
    }
    return 0;
}

int ABB::posicao(const int x) {
    int nodes = 0;
    Node* current = this->root;
    DataType data = DataType();
    while (current != nullptr) {
        nodes += current->l_cnt + 1;
        data = current->data;
        if (data == x) {
            return nodes;
        }
        if (data < x) {
            current = current->right;
        } else {
            nodes = 0;
            current = current->left;
        }
    }
    return 0;
}

int ABB::mediana() { return 0; }

bool ABB::ehCheia() { return false; }

bool ABB::ehCompleta() { return false; }

std::string ABB::toString() { return ""; }
