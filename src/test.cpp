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
    // Adiciona alguns elementos.
    {
        int array[] = {6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
        for (int i = 0; i < 11; ++i) {
            abb->insert(array[i]);
        }
        // { 8 4 12 2 6 10 14 1 3 5 7 9 11 13 15 }
    }
    // remove(int n)
    {
        bool resultado = abb->remove(15);
        assert(resultado == true);
        std::string porNivel = abb->toString();
        std::cout << "Resultado: " << porNivel << std::endl;
        std::cout << "Esperado: "
                  << "{ 8 4 12 2 6 10 14 1 3 5 7 9 11 13 }" << std::endl;
        assert(porNivel.compare("{ 8 4 12 2 6 10 14 1 3 5 7 9 11 13 }") == 0);
        std::cout << "Passou no remove da folha!" << std::endl;
    }
    {
        bool resultado = abb->remove(14);
        assert(resultado == true);
        std::string porNivel = abb->toString();
        std::cout << "Resultado: " << porNivel << std::endl;
        std::cout << "Esperado: "
                  << "{ 8 4 12 2 6 10 13 1 3 5 7 9 11 }" << std::endl;
        assert(porNivel.compare("{ 8 4 12 2 6 10 13 1 3 5 7 9 11 }") == 0);
        std::cout << "Passou no remove com um filho!" << std::endl;
    }
    {
        bool resultado = abb->remove(4);
        assert(resultado == true);
        std::string porNivel = abb->toString();
        std::cout << "Resultado: " << porNivel << std::endl;
        std::cout << "Esperado: "
                  << "{ 8 5 12 2 6 10 13 1 3 7 9 11 }" << std::endl;
        assert(porNivel.compare("{ 8 5 12 2 6 10 13 1 3 7 9 11 }") == 0);
        std::cout << "Passou no remove com dois filhos!" << std::endl;
    }
    {
        bool resultado = abb->remove(8);
        assert(resultado == true);
        std::string porNivel = abb->toString();
        std::cout << "Resultado: " << porNivel << std::endl;
        std::cout << "Esperado: "
                  << "{ 9 5 12 2 6 10 13 1 3 7 11 }" << std::endl;
        assert(porNivel.compare("{ 9 5 12 2 6 10 13 1 3 7 11 }") == 0);
        int rootData = abb->getRoot()->data;
        assert(rootData == 9);
        std::cout << "Passou no remove da raiz!" << std::endl;
    }

    return 0;
}
