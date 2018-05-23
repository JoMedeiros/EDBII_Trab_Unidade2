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

Node::Node(DataType value, int n, Node* p, Node* l, Node* r)
    : parent(p), left(l), right(r), data(value), level(n) {
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

void ABB::atualizaCounts(Node* node, int value) {
    if (node != root) {
        if (node == node->parent->right) {
            node->parent->r_cnt += value;
        }
        if (node == node->parent->left) {
            node->parent->l_cnt += value;
        }
        atualizaCounts(node->parent, value);
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
                current->left = new Node(target, count, current);
                atualizaCounts(current->left, 1);
                ++size;
                if (count > height) {
                    ++height;
                    // Não sei porque mas trocando 1 por 0 funciona
                    levelCount.push_back(0);
                }
                // Atualiza o número de nós no nível inserido
                ++levelCount[count - 1];
                return true;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new Node(target, count, current);
                atualizaCounts(current->right, 1);
                ++size;
                if (count > height) {
                    ++height;
                    // Não sei porque mas trocando 1 por 0 funciona
                    levelCount.push_back(0);
                }
                // Atualiza o número de nós no nível inserido
                ++levelCount[count - 1];
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
    int data = first->data;
    first->data = second->data;
    second->data = data;
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
                atualizaCounts(current, -1);
                if (current->parent->left == current) {
                    current->parent->left = nullptr;
                } else if (current->parent->right == current) {
                    current->parent->right = nullptr;
                }
                --size;
                --levelCount[current->level - 1];
                if (levelCount[current->level - 1] == 0) {
                    levelCount.pop_back();
                }
                delete current;
                return true;
            }
            // Um único filho
            if (current->left == nullptr) {
                atualizaCounts(current, -1);
                if (current->parent->left == current) {
                    current->parent->left = current->right;
                } else if (current->parent->right == current) {
                    current->parent->right = current->right;
                }
                current->right->parent = current->parent;
                --size;
                --levelCount[current->right->level - 1];
                if (levelCount[current->right->level - 1] == 0) {
                    levelCount.pop_back();
                }
                delete current;
                return true;
            }
            if (current->right == nullptr) {
                atualizaCounts(current, -1);
                if (current->parent->left == current) {
                    current->parent->left = current->left;
                } else if (current->parent->right == current) {
                    current->parent->right = current->left;
                }
                current->left->parent = current->parent;
                --size;
                --levelCount[current->left->level - 1];
                if (levelCount[current->left->level - 1] == 0) {
                    levelCount.pop_back();
                }
                delete current;
                return true;
            }
            // Dois filhos
            Node* smallest = minimum(current->right);
            substituir(current, smallest);
            atualizaCounts(smallest, -1);
            if (smallest->parent->left == smallest) {
                smallest->parent->left = nullptr;
            } else if (smallest->parent->right == smallest) {
                smallest->parent->right = nullptr;
            }
            --size;
            --levelCount[smallest->level - 1];
            if (levelCount[smallest->level - 1] == 0) {
                levelCount.pop_back();
            }
            delete smallest;
            return true;
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

// Parece certo...
bool ABB::ehCompleta() {
    int n = levelCount.size();  // para acessar o vector
    if (n > 2) {
        // [... , x, y] se x = 2^level(x) -> é cheia
        int a = levelCount[n - 2];
        int b = std::pow(2, n - 2) - 1;
        return levelCount[n - 2] >= std::pow(2, n - 2) - 1;
    }
    return true;
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
