#include "ABB.h"

Node::Node(TipoDado value) left(nullptr), right(nullptr), l_cnt(0), r_cnt(0), data(value)
{}

ABB::ABB() : raiz(nullptr), tamanho(0)
{/* vazio */}

Node* ABB::getRaiz(){
	return raiz;
}