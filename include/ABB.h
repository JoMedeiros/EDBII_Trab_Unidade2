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
 * @date   21/05/2018
 */

#ifndef INCLUDE_ABB_H_
#define INCLUDE_ABB_H_

#ifndef _GLIBCXX_STRING
#include <string>
#endif

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

typedef int DataType;

/**
 * @brief Estrutura Node para a Árvore Binária de Busca Extendida.
 */
struct Node {
   public:
    /**
     * Nó imediatamente acima deste.
     */
    Node* parent;
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
     * @param p Nó acima deste.
     * @param l Nó a esquerda deste.
     * @param r Nó a direita deste.
     */
    explicit Node(DataType value = DataType(), Node* p = nullptr,
                  Node* l = nullptr, Node* r = nullptr);
    /**
     * @brief Conta o numero de nós nas subárvores a esquerda e a direita do nó
     * indicado.
     *
     * @param n Nó indicado.
     * @return int numero de descendentes do nó indicado.
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
     * @brief Constrói uma árvore binária de busca a partir de um nó.
     *
     * @param r Nó que será usado como raiz.
     */
    explicit ABB(Node* r = nullptr);
    /**
     * @brief Destroi a árvore binária de busca
     */
    ~ABB();
    /**
     * @brief Elimina recursivamente os nós a partir do nó indicado,
     * incluindo-o.
     *
     * @param node Nó por onde a eliminação irá ter inicio.
     */
    void recursiveErase(Node* node);
    /**
     * @brief Recupera o Nó raiz da árvore.
     *
     * @return Node* O nó raiz.
     */
    Node* getRoot();
    /**
     * @brief Retorna o número de nós presentes nesta árvore.
     *
     * @return int Número de nós.
     */
    int getSize();
    /**
     * @brief Busca o Nó que contém o conteúdo indicado
     *
     * @param target Conteúdo a ser buscado.
     * @return Node* Nó que possui o conteúdo buscado.
     * @return nullptr Caso o nó não seja encontrado.
     */
    Node* search(const DataType target);

    /**
     * @brief Atualiza a contagem de filhos a esquerda e a direita de todos os
     *        nós entre o nó indicado e a raiz. Incrementando em 1.
     *
     * @param node Nó de inicio.
     */
    void atualizaCounts(Node* node);
    /**
     * @brief Insere um novo nó com o conteúdo indicado na árvore.
     *
     * @param target Conteúdo a ser inserido.
     * @return true Caso seja inserido com sucesso.
     * @return false Caso não seja possível inserir. (Elemento repetido)
     */
    bool insert(const DataType target);
    /**
     * @brief Substitui o segundo nó pelo primeiro.
     *
     * @param first Nó a ser substituido.
     * @param second Nó a substituir.
     */
    void substituir(Node* first, Node* second);
    /**
     * @brief Remove o nó com o conteúdo indicado desta árvore.
     *
     * @param target Conteúdo a ser removido.
     * @return true Caso seja removido com sucesso.
     * @return false Caso não seja possível remover.
     */
    bool remove(const DataType target);
    /**
     * @brief Retorna o n-ésimo elemento (contando a partir de 1) do percurso
     *        em ordem (ordem simétrica) da ABB.
     *
     * @param n Posição do elemento a ser retornado.
     * @return int Elemento da posição indicada.
     */
    int enesimoElemento(const int n);
    /**
     * @brief Retorna a posição ocupada pelo elemento x em um percurso em ordem
     *        simétrica na ABB (contando a partir de 1).
     *
     * @param x Elemento o qual a posição será retornada.
     * @return int Posição do elemento indicado.
     */
    int posicao(const int x);
    /**
     * @brief retorna o elemento que contém a mediana da ABB. Se a ABB possuir
     * um número par de elementos, retorne o menor dentre os dois elementos
     * medianos.
     *
     * @return int Elemento que ocupa a mediana da árvore.
     */
    int mediana();
    /**
     * @brief Indica se a árvore é uma árvore cheia.
     *
     * @return true
     * @return false
     */
    bool ehCheia();
    /**
     * @brief Indica se a árvore é uma árvore completa.
     *
     *
     * @return true
     * @return false
     */
    bool ehCompleta();
    /**
     * @brief retorna uma String que contém a sequência de visitação
     *        (percorrimento) da ABB por nível.
     *
     * @return std::string Resultado do percorrimento por nível.
     */
    std::string toString();
    /**
     * @brief
     *
     * @param node
     * @return Node*
     */
    Node* minimum(Node* node = nullptr);
    /**
     * @brief
     *
     * @param node
     * @return Node*
     */
    Node* maximum(Node* node = nullptr);
};

#endif  // INCLUDE_ABB_H_
