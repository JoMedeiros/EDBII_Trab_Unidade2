// Copyright 2018

/**
 * @file   main.cpp
 * @brief  Arquivo main para leitura dos arquivos e utilização da Árvore Binária
 * 		   de Busca Extendida a partir de comandos de um arquivo
 *
 * @author Gleydvan
 * @author JohnVithor
 * @author JoMedeiros
 *
 * @since  20/05/2018
 * @date   20/05/2018
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "ABB.h"

std::pair<std::string, std::string> validateArgs(int argc, char const *argv[]) {
    if (argc != 5) {
        std::cout << "Modo de usar: "
                  << "./bin/ABB -a <arquivo_arvore> -i <arquivo_instrucoes>"
                  << std::endl;
        std::exit(-1);
    }
    bool iFlag = false;
    bool aFlag = false;
    std::string arquivo_arvore;
    std::string arquivo_instrucoes;

    for (int i = 1; i < argc; ++i) {
        if (!aFlag && std::string(argv[i]) == "-a") {
            arquivo_arvore = argv[i + 1];
            aFlag = true;
        }
        if (!iFlag && std::string(argv[i]) == "-i") {
            arquivo_instrucoes = argv[i + 1];
            iFlag = true;
        }
    }
    if (!aFlag && !iFlag) {
        std::cout << "Modo de usar: "
                  << "./bin/ABB -a <arquivo_arvore> -i <arquivo_instrucoes>"
                  << std::endl;
        std::exit(-1);
    }
    return std::make_pair(arquivo_arvore, arquivo_instrucoes);
}

std::vector<int> readValues(const std::string &path) {
    std::string line;
    int value;
    std::vector<int> values;
    std::ifstream data;

    data.open(path);
    if (!data.is_open()) {
        std::cout << "O arquivo '" << path << "' não pode ser aberto."
                  << std::endl;
        std::exit(-1);
    }
    while (std::getline(data, line)) {
        std::istringstream(line) >> value;
        values.push_back(value);
    }
    data.close();
    return values;
}

std::vector<std::string> readCommands(const std::string &path) {
    std::string line;
    std::vector<std::string> commands;
    std::ifstream data;

    data.open(path);
    if (!data.is_open()) {
        std::cout << "O arquivo '" << path << "' não pode ser aberto."
                  << std::endl;
        std::exit(-1);
    }
    while (std::getline(data, line)) {
        commands.push_back(line);
    }
    data.close();
    return commands;
}

int main(int argc, char const *argv[]) {
    auto archives = validateArgs(argc, argv);
    std::vector<int> values = readValues(archives.first);
    std::vector<std::string> commands = readCommands(archives.second);

    std::cout << "Valores: ";
    for (auto var : values) {
        std::cout << var << " ";
    }
    std::cout << std::endl;

    std::cout << "Comandos: ";
    for (auto var : commands) {
        std::cout << "'" << var << "'" << " ";
    }
    std::cout << std::endl;

    return 0;
}
