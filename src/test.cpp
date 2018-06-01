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
 * @date   23/05/2018
 */

#include <cassert>
#include <iostream>

#include "ABB.h"
int main(int argc, char const* argv[]) {
    std::cout << "Iniciando Testes:" << std::endl;

    ABB* abb = new ABB();
    Node* root = abb->getRoot();
    assert(root == nullptr);
    std::cout << "Passou no do construtor vazio!" << std::endl;
    // insere(int target)
    {
        abb->insere(8);
        int size = abb->getSize();
        assert(size == 1);
        std::cout << "Passou no inserir numa abb vazia!" << std::endl;
    }
    {
        abb->insere(4);
        int size = abb->getSize();
        assert(size == 2);
        std::cout << "Passou no inserir numa abb com um elemento!" << std::endl;
    }
    // enesimoElemento(int n)
    {
        abb->insere(2);
        int resultado = abb->enesimoElemento(1);
        assert(resultado == 2);
        std::cout << "Passou no enesimoElemento do primeiro elemento!"
                  << std::endl;
    }
    {
        abb->insere(12);
        int resultado = abb->enesimoElemento(4);
        assert(resultado == 12);
        std::cout << "Passou no enesimoElemento do ultimo elemento!"
                  << std::endl;
    }
    // posicao
    {
        int resultado = abb->enesimoElemento(4);
        int indice = abb->posicao(resultado);
        assert(indice == 4);
        std::cout << "Passou no posicao!" << std::endl;
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
            abb->insere(array[i]);
        }
        std::cout << abb->toString() << std::endl;
        // { 8 4 12 2 6 10 14 1 3 5 7 9 11 13 15 }
    }
    {
        int resultado = abb->getHeight();
        assert(resultado == 4);
        std::cout << "Passou no getHeight árvore cheia!" << std::endl;
    }

    // enesimoElemento(int n)
    {
        int resultado = abb->enesimoElemento(14);
        assert(resultado == 14);
        std::cout << "Passou no enesimoElemento com um numero no meio!"
                  << std::endl;
    }
    // mediana()
    {
        int resultado = abb->mediana();
        assert(resultado == 8);
        std::cout << "Passou no mediana!"
                  << std::endl;
    }
    // ehCheia()
    {
        bool resultado = abb->ehCheia();
        assert(resultado == true);
        std::cout << "Passou no ehCheia!" << std::endl;
    }
    // ehCompleta()
    {
        ABB* abb2 = new ABB();
        abb2->insere(2);
        abb2->insere(3);
        abb2->insere(4);  // Arvore ziguezague
        bool resultado = abb2->ehCompleta();
        assert(resultado == false);  // Teste negativo
        resultado = abb->ehCompleta();
        assert(resultado == true);  // Teste positivo
        std::cout << "Passou no não ehCompleta!" << std::endl;
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
    // mediana()
    {
        int resultado = abb->mediana();
        assert(resultado == 7);
        std::cout << "Passou no mediana!"
                  << std::endl;
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
    {
        ABB tree;
        std::cout << "Apenas a Raiz:" << std::endl;
        tree.insere(8);
        std::cout << tree.toString() << std::endl;
        std::cout << "Raiz com todos os filhos:" << std::endl;
        tree.insere(4);
        tree.insere(16);
        std::cout << tree.toString() << std::endl;
        std::cout << "Raiz com alguns netos e um bisneto:" << std::endl;
        tree.insere(2);
        tree.insere(6);
        tree.insere(10);
        tree.insere(12);
        std::cout << tree.toString() << std::endl;
        std::cout << "Apagar a raiz:" << std::endl;
        tree.remove(8);
        std::cout << tree.toString() << std::endl;
    }
    return 0;
}
