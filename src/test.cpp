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
 * @date   21/05/2018
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
    {
        abb->insert(8);
        int size = abb->getSize();
        assert(size == 1);
        std::cout << "Passou no inserir numa abb vazia!" << std::endl;
    }
    {
        abb->insert(4);
        int size = abb->getSize();
        assert(size == 2);
        std::cout << "Passou no inserir numa abb com um elemento!" << std::endl;
    }
    {
        abb->insert(2);
        int resultado = abb->enesimoElemento(1);
        assert(resultado == 2);
        std::cout << "Passou no enesimoElemento do primeiro elemento!"
                  << std::endl;
    }
    {
        abb->insert(12);
        int resultado = abb->enesimoElemento(4);
        assert(resultado == 12);
        std::cout << "Passou no enesimoElemento do ultimo elemento!"
                  << std::endl;
    }
    {
        int size = abb->getSize();
        Node* root = abb->getRoot();
        int childremSum = root->l_cnt + root->r_cnt + 1;
        assert(size == childremSum);
        std::cout << "Passou no size igual a soma dos filhos mais 1!"
                  << std::endl;
    }
    {
        std::string porNivel = abb->toString();
        assert(porNivel.compare("{ 8 4 12 2 }"));
        std::cout << "Passou no toString por nível!" << std::endl;
    }
    return 0;
}
