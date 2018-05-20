// Copyright 2018

/**
 * @file   ABB.h
 * @brief  Declaração da Classe ABB e da Estrutura Node juntamente de seus
 * respectivos atributos e métodos.
 *
 * @author Gleydvan
 * @author JohnVithor
 * @author JoMedeiros
 *
 * @since  20/05/2018
 * @date   20/05/2018
 */

#ifndef INCLUDE_ABB_H_
#define INCLUDE_ABB_H_

#ifndef _GLIBCXX_STRING
#include <string>
#endif

#ifndef _GLIBCXX_STACK
#include <stack>
#endif

typedef int DataType;
/**
 * @brief Estrutura Node para a Árvore Binária de Busca Extendida.
 */
struct Node {
 public:
    /**
     * Nó imediatamente a esquerda deste.
     */
    Node* left;
    /**
     * Nó imediatamente a direita deste.
     */
    Node* right;
    /**
     * Número de nós a esquerda.
     */
    int l_cnt;
    /**
     * Número de nós a direita.
     */
    int r_cnt;
    /**
     * Conteúdo armazenado neste nó.
     */
    DataType data;

 public:
    /**
     * @brief Constroi um novo objeto Node.
     *
     * @param value Valor a ser guardado pelo Node.
     * @param l
     * @param r
     */
    explicit Node(DataType value = DataType(), Node* l = nullptr,
                  Node* r = nullptr);
    /**
     * @brief
     *
     * @param n
     * @return int
     */
    int countChildren(Node* n);
};

/**
 * @brief Classe Árvore Binária de Busca Extendida.
 */
class ABB {
 private:
    /**
     * Nó raiz da árvore.
     */
    Node* root;
    /**
     * Número de nós na árvore.
     */
    int size;

 public:
    /**
     * @brief Constrói uma árvore binária de busca vazia (com nó raiz nulo).
     *
     * @param r
     */
    explicit ABB(Node* r = nullptr);
    ~ABB();

    void recursiveErase(Node* node);
    Node* getRoot();

    Node* search(const DataType target);
    bool insert(const DataType target);
    bool remove(const DataType target);

    int enesimoElemento(const int n);
    int posicao(const int x);
    int mediana();
    bool ehCheia();
    bool ehCompleta();
    std::string toString();
};

#endif  // INCLUDE_ABB_H_
