// Copyright 2018

/**
 * @file   test.cpp
 * @brief  Arquivo para realização dos testes da Classe ABB
 *
 * @author Gleydvan
 * @author JohnVithor
 * @author JoMedeiros
 *
 * @since  20/05/2018
 * @date   20/05/2018
 */

#include <cassert>
#include <iostream>

#include "ABB.h"
int main(int argc, char const* argv[]) {
    std::cout << "Ola árvore binária de busca! Você gosta de Raça Negra?\n";
    std::cout << "Iniciando Testes:" << std::endl;

    ABB* plantinha = new ABB();
    Node* root = plantinha->getRoot();
    assert(root == nullptr);

    Node* node = new Node();

    return 0;
}
