#ifndef _ABB_H_
#define _ABB_H_

#ifndef _GLIBCXX_STRING
	#include <string>
#endif

typedef int DataType;

struct Node
{
	Node(DataType value);
	Node *left;
	Node *right;
	int l_cnt; // Número de nós a esquerda
	int r_cnt; // Número de nós a direita
	DataType data;
};

class ABB
{
private:
	Node* raiz;
	int tamanho;
public:
	/**
	 * @brief      Constrói uma árvore binária de busca vazia (com nó raiz nulo).
	 */
	ABB();
	Node* getRaiz();
	int enesimoElemento (int n);
	int posicao (int x);
	int mediana ();
	bool ehCheia ();
	bool ehCompleta ();
	std::string toString ();
};

#endif