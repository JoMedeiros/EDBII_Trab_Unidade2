#include <iostream>
#include <cassert>
#include "ABB.h"

using namespace std;

int main(int argc, char const *argv[])
{
	cout << "Ola árvore binária de busca! Você gosta de Raça Negra?\n";

	ABB *plantinha = new ABB();

	assert(plantinha->getRaiz() == nullptr);

	return 0;
}