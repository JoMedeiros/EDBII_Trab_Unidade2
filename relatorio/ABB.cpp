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
 * @date   25/05/2018
 */

#include "ABB.h"

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
Node::Node(DataType value, int n, Node* p, Node* l, Node* r)
    : parent(p), left(l), right(r), l_cnt(0), r_cnt(0), data(value), level(n) {}

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
ABB::ABB(Node* r) : root(r), size(0), height(0) { levelCount.reserve(10); }

// Depende da complexidade do recursiveErase e do numero de nós da árvore
// Uma chamada a função recursiva
ABB::~ABB() { recursiveErase(root); }

// Percorre todos os nós a partir do nó indicado, logo: Theta(n)
// Função recursiva
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

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
Node* ABB::getRoot() { return root; }

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
int ABB::getSize() { return size; }

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
int ABB::getHeight() { return height; }

// Pior caso é uma árvore zig-zag, logo O(n)
// Utiliza um laço while
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

// O pior caso depende da complexidade do outro insere
// Dois casos, no primeiro temos tempo constante e no segundo uma chamada
// recursiva
bool ABB::insere(const DataType target) {
    if (root == nullptr) {
        root = new Node(target, 1, nullptr);
        levelCount.push_back(0);
        height = 1;
        size = 1;
        return true;
    }
    return insere(root, target);
}

// O pior caso é uma sub-árvore zig-zag, logo O(n)
// Função recursiva
bool ABB::insere(Node* node, const DataType target) {
    int data = node->data;
    if (data != target) {
        if (data < target) {
            if (node->right == nullptr) {
                node->right = new Node(target, node->level + 1, node);
                if (node->right->level > height) {
                    ++height;
                    levelCount.push_back(1u << (height - 1));
                }
                ++size;
                --levelCount[node->right->level - 1];
                ++node->r_cnt;
                return true;
            }
            if (insere(node->right, target)) {
                ++node->r_cnt;
                return true;
            }
        } else {
            if (node->left == nullptr) {
                node->left = new Node(target, node->level + 1, node);
                if (node->left->level > height) {
                    ++height;
                    levelCount.push_back(1u << (height - 1));
                }
                ++size;
                --levelCount[node->left->level - 1];
                ++node->l_cnt;
                return true;
            }
            if (insere(node->left, target)) {
                ++node->l_cnt;
                return true;
            }
        }
    }
    return false;
}

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
void ABB::substituir(Node* first, Node* second) {
    int data = first->data;
    first->data = second->data;
    second->data = data;
}

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
void ABB::atualizaParent(Node* node1, Node* node2) {
    if (node1 == root) {
        root = node2;
        return;
    }
    if (node1->parent->left == node1) {
        node1->parent->left = node2;
    } else {
        node1->parent->right = node2;
    }
}

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
void ABB::atualizaNivelENodes(Node* node) {
    --size;
    ++levelCount[node->level - 1];
    if (levelCount[node->level - 1] == (1u << (node->level - 1))) {
        levelCount.pop_back();
    }
}
// O pior caso depende da complexidade do outro remove
// Função recursiva
bool ABB::remove(const DataType target) { return remove(root, target); }

// O pior caso é uma sub-árvore zig-zag, onde o nó a ser removido é 
// a folha, logo O(n)
// Função recursiva e funções com Theta(1), função com laço while
bool ABB::remove(Node* node, const DataType target) {
    if (node != nullptr) {
        int data = node->data;
        if (data == target) {
            if (node->left == nullptr && node->right == nullptr) {
                atualizaParent(node, nullptr);
                atualizaNivelENodes(node);
                delete node;
                return true;
            }
            if (node->left == nullptr) {
                atualizaParent(node, node->right);
                atualizaNivelENodes(node->right);
                node->right->parent = node->parent;
                delete node;
                return true;
            }
            if (node->right == nullptr) {
                atualizaParent(node, node->left);
                atualizaNivelENodes(node->left);
                node->left->parent = node->parent;
                delete node;
                return true;
            }
            Node* smallest = minimum(node->right);
            substituir(node, smallest);
            atualizaParent(smallest, nullptr);
            atualizaNivelENodes(smallest);
            delete smallest;
            return true;
        }
        if (data < target) {
            if (remove(node->right, target)) {
                --node->r_cnt;
                return true;
            }
        } else {
            if (remove(node->left, target)) {
                --node->l_cnt;
                return true;
            }
        }
    }
    return false;
}
// O no pior caso o elemento com esse indice não está na árvore, e o laço while
// terá se repetido lg(n), logo O(lgn)
// Laço while
int ABB::enesimoElemento(const int n) {
    int increment = 0;
    int nodes = 0;
    Node* current = root;
    while (current != nullptr) {
        increment = current->l_cnt + 1;
        if (nodes + increment == n) {
            return current->data;
        }
        if (nodes + increment < n) {
            nodes += increment;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    throw std::out_of_range("Não existe a posição: " + std::to_string(n));
}

// O no pior caso esse elemento não está na árvore, e o laço while
// terá se repetido lg(n), logo O(lgn)
// Laço while
int ABB::posicao(const int x) {
    int increment = 0;
    int nodes = 0;
    Node* current = this->root;
    DataType data = DataType();
    while (current != nullptr) {
        increment = current->l_cnt + 1;
        data = current->data;
        if (data == x) {
            return nodes + increment;
        }
        if (data < x) {
            nodes += increment;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    throw std::invalid_argument("Não existe o elemento: " + std::to_string(x));
}
// Depende da complexidade do enesimoElemento
// Função recursiva
int ABB::mediana() {
    if (size % 2 == 0) {
        return enesimoElemento(size / 2);
    } else {
        return enesimoElemento((size / 2) + 1);
    }
}

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
bool ABB::ehCheia() { return size == (1u << height) - 1u; }

// Tempo constante, logo Theta(1)
// Nenhum laço ou chamada de função
bool ABB::ehCompleta() {
    int n = levelCount.size();
    if (n > 2) {
        return levelCount[n - 2] == 0;
    }
    return true;
}

// Utiliza um percusso por nível, logo Theta(n)
// Laço while
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
            nodes.push(node->left);
        }
        if (node->right != nullptr) {
            nodes.push(node->right);
        }
    }
    return "{ " + result + "}";
}

// No pior caso temos uma árvore zig-zag, logo O(n)
// Laço while
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

// No pior caso temos uma árvore zig-zag, logo O(n)
// Laço while
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
