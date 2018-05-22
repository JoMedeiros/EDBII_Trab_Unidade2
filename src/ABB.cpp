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
 * @date   22/05/2018
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

ABB::ABB(Node* r) : root(r), size(0), height(0) { levelCount.reserve(10); }

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

int ABB::getHeight() { return height; }

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
        ++height;
        levelCount.push_back(1);
        return true;
    }
    int count = 1;
    while (current != nullptr) {
        data = current->data;
        if (data == target) {
            return false;
        }
        ++count;
        if (data > target) {
            if (current->left == nullptr) {
                current->left = new Node(target, current);
                atualizaCounts(current->left);
                ++size;
                if (count > height) {
                    ++height;
                    levelCount.push_back(1);
                }
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new Node(target, current);
                atualizaCounts(current->right);
                ++size;
                if (count > height) {
                    ++height;
                    levelCount.push_back(1);
                }
                return true;
            }
            current = current->right;
        }
    }
    return false;
}

/**
 * Me pergunto se é realmente necessário realizar tantas verificações...
 */
void ABB::substituir(Node* first, Node* second) {
    if (first->parent != nullptr) {
        if (first == first->parent->left) {
            first->parent->left = second;
        } else {
            first->parent->right = second;
        }
    }
    if (second == second->parent->left) {
        second->parent->left = first;
    } else {
        second->parent->right = first;
    }

    Node temp = *second;
    // Provavelmente é melhor realizar uma sobrecarga ou criar um método que
    // faça essas atribuições e as verificações
    second->parent = first->parent;
    second->left = first->left;
    second->right = first->right;
    second->l_cnt = first->l_cnt;
    second->r_cnt = first->r_cnt;

    first->parent = temp.parent;
    first->left = temp.left;
    first->right = temp.right;
    first->l_cnt = temp.l_cnt;
    first->r_cnt = temp.r_cnt;

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
/**
 * Preciso setar os ponteiros do nó a ser removido para nullptr antes de chamar
 * o delete? Ou só o delete já é o suficiente?
 */

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
                if (current->parent->left == current) {
                    current->parent->left = nullptr;
                } else if (current->parent->right == current) {
                    current->parent->right = nullptr;
                }
                current->parent = nullptr;
                current->left = nullptr;
                current->right = nullptr;
                delete current;
                return true;
            }
            if (current->right == nullptr) {
                substituir(current, current->left);
                if (current->parent->left == current) {
                    current->parent->left = nullptr;
                } else if (current->parent->right == current) {
                    current->parent->right = nullptr;
                }
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
        } else if (data < target) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return false;
}

/**
 * Ainda utilizo a estratégia de busca
 */
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
    throw std::out_of_range("Não existe a posição: " + n);
}

/**
 * Ainda utilizo a estratégia de busca
 */
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
    throw std::invalid_argument("Não existe o elemento: " + x);
}
/**
 * Parece simples demais... deve estar errado...
 */
int ABB::mediana() {
    if (size % 2 == 0) {
        return enesimoElemento(size / 2);
    } else {
        return enesimoElemento((size / 2) + 1);
    }
}

// Parece certo...
bool ABB::ehCheia() { return size == std::pow(2, height) - 1; }

// Falta atualizar esse método, está errado.
bool ABB::ehCompleta() {
    size <= std::pow(2, height) - 1 && size >= std::pow(2, height - 1);
    return size == std::pow(2, height) - 1;
}

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
            nodes.push(node->left);
        }
        if (node->right != nullptr) {
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
