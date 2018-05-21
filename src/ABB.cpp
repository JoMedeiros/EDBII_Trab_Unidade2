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
 * @date   21/05/2018
 */

#include "ABB.h"

Node::Node(DataType value, Node* p, Node* l, Node* r)
    : parent(p), left(l), right(r), data(value) {
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
        node->parent = nullptr;
        delete node;
    }
}

Node* ABB::getRoot() { return root; }

int ABB::getSize() { return size; }

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

void ABB::atualizaCounts(Node* node) {
    if (node != root) {
        if (node == node->parent->right) {
            ++node->parent->r_cnt;
        }
        if (node == node->parent->left) {
            ++node->parent->l_cnt;
        }
        atualizaCounts(node->parent);
    }
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
                current->left = new Node(target, current);
                atualizaCounts(current->left);
                ++size;
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new Node(target, current);
                atualizaCounts(current->right);
                ++size;
                return true;
            }
            current = current->right;
        }
    }
    return false;
}

void ABB::substituir(Node* first, Node* second) {
    if (first->parent != nullptr) {
        if (first == first->parent->left) {
            first->parent->left = second;
        } else {
            first->parent->right = second;
        }
        if (second != nullptr) {
            second->parent = first->parent;
        }
    }

    Node temp = *second;
    second->left = first->left;
    second->right = first->right;

    first->parent = temp.parent;
    first->left = temp.left;
    first->right = temp.right;

    if (first->parent == first) {
        first->parent = second;
    }
    if (second->parent == second) {
        second->parent = first;
    }
    if (second->left == second) {
        second->left = first;
    }
    if (second->right == second) {
        second->right = first;
    }
    if (root == first) {
        second->parent = nullptr;
        root = second;
    }
}

bool ABB::remove(const DataType target) {
    Node* current = this->root;
    DataType data = DataType();
    while (current != nullptr) {
        data = current->data;
        if (data == target) {
            // Nenhum filho
            if (current->left == nullptr && current->right == nullptr) {
                if (current->parent->left == current) {
                    current->parent->left = nullptr;
                } else if (current->parent->right == current) {
                    current->parent->right = nullptr;
                }
                delete current;
                --size;
                return true;
            }
            // Um único filho
            if (current->left == nullptr) {
                substituir(current, current->right);
                current->parent = nullptr;
                current->left = nullptr;
                current->right = nullptr;
                delete current;
                return true;
            }
            if (current->right == nullptr) {
                substituir(current, current->left);
                current->parent = nullptr;
                current->left = nullptr;
                current->right = nullptr;
                delete current;
                return true;
            }
            // Dois filhos
            Node* smallest = minimum(current->right);
            substituir(current, smallest);
            continue;
        }
    }
    return false;
}

/**
 * Ainda utilizo a estratégia de busca
 */
int ABB::enesimoElemento(const int n) {
    int nodes = 0;
    Node* current = root;
    while (current != nullptr) {
        nodes += current->l_cnt + 1;
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

/**
 * Ainda utilizo a estratégia de busca
 */
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

/**
 * Utiliza uma std::queue, talvez seja possivel fazer esse método sem
 * utiliza-la.
 */
std::string ABB::toString() {
    std::string result;
    std::queue<Node*> nodes;
    Node* node = root;
    nodes.push(node);
    while (!nodes.empty()) {
        node = nodes.front();
        nodes.pop();
        result += std::to_string(node->data) + " ";
        if (node->left != nullptr) {
            // result += "left:" + std::to_string(node->left->data) + " ";
            nodes.push(node->left);
        }
        if (node->right != nullptr) {
            // result += "right:" + std::to_string(node->right->data) + " ";
            nodes.push(node->right);
        }
    }
    return "{ " + result + "}";
}

Node* ABB::minimum(Node* node) {
    Node* step = node;
    if (node == nullptr) {
        step = root;
    }
    Node* smallest = step;
    while (step != nullptr) {
        smallest = step;
        step = step->left;
    }
    return smallest;
}

Node* ABB::maximum(Node* node) {
    Node* step = node;
    if (node == nullptr) {
        step = root;
    }
    Node* biggest = step;
    while (step != nullptr) {
        biggest = step;
        step = step->right;
    }
    return biggest;
}
