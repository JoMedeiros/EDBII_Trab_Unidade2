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
    // insert(int target)
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
    // enesimoElemento(int n)
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
    // getSize() e atualizaCounts(Node* node)
    {
        int size = abb->getSize();
        Node* root = abb->getRoot();
        int childremSum = root->l_cnt + root->r_cnt + 1;
        assert(size == childremSum);
        std::cout << "Passou no size igual a soma dos filhos mais 1!"
                  << std::endl;
    }
    // tostring()
    {
        std::string porNivel = abb->toString();
        std::cout << "Resultado: " << porNivel << std::endl;
        std::cout << "Esperado: "
                  << "{ 8 4 12 2 }" << std::endl;
        assert(porNivel.compare("{ 8 4 12 2 }") == 0);
        std::cout << "Passou no toString por nível!" << std::endl;
    }
    // remove(int n)
    {
        bool resultado = abb->remove(8);
        assert(resultado == true);
        std::string porNivel = abb->toString();
        std::cout << "Resultado: " << porNivel << std::endl;
        std::cout << "Esperado: "
                  << "{ 12 4 2 }" << std::endl;
        assert(porNivel.compare("{ 12 4 2 }") == 0);
        std::cout << "Passou no remove da raiz!" << std::endl;
    }
    return 0;
}
