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

    ABB* abb = new ABB();
    Node* root = abb->getRoot();
    assert(root == nullptr);
    std::cout << "Passou no do construtor vazio!" << std::endl;
    abb->insert(8);
    assert(abb->getSize() == 1);
    std::cout << "Passou no inserir numa abb vazia!" << std::endl;
    abb->insert(4);
    assert(abb->getSize() == 2);
    std::cout << "Passou no inserir numa abb com um elemento!" << std::endl;
    std::cout << abb->toString() << std::endl;
    return 0;
}
