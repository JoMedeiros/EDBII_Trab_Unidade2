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
 * @date   25/05/2018
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "ABB.h"
#include "Command.h"

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

std::vector<std::string> parse(std::string target, std::string delimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    size_t delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> result;
    while ((pos_end = target.find(delimiter, pos_start)) != std::string::npos) {
        token = target.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }
    result.push_back(target.substr(pos_start));
    return result;
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
    std::getline(data, line);
    std::vector<std::string> numbers = parse(line, " ");
    for (auto number : numbers) {
        std::istringstream(number) >> value;
        values.push_back(value);
    }
    data.close();
    return values;
}

std::vector<Command> readCommands(const std::string &path) {
    std::string line;
    std::vector<Command> commands;
    std::ifstream data;
    data.open(path);
    if (!data.is_open()) {
        std::cout << "O arquivo '" << path << "' não pode ser aberto."
                  << std::endl;
        std::exit(-1);
    }
    std::vector<std::string> parsed;
    Command *command;
    while (std::getline(data, line)) {
        parsed = parse(line, " ");
        if (parsed.size() == 2) {
            command = new Command(parsed[0], parsed[1]);
        } else {
            command = new Command(parsed[0]);
        }

        commands.push_back(*command);
    }
    data.close();
    return commands;
}

int main(int argc, char const *argv[]) {
    auto archives = validateArgs(argc, argv);
    std::vector<int> values = readValues(archives.first);
    std::vector<Command> commands = readCommands(archives.second);
    ABB abb;
    for (auto value : values) {
        bool ok = abb.insere(value);
        if (!ok) {
            std::cout << "Não foi possível inserir o elemento '" << value
                      << "' elemento já presente na árvore.\n";
        }
    }
    int resultado;
    bool sucesso;
    for (auto command : commands) {
        std::cout << command.getCommand() << " ";
        switch (command.getType()) {
            case (Command::CommandType::CHEIA):
                std::cout << ": ";
                if (abb.ehCheia()) {
                    std::cout << "Sim é Cheia!" << std::endl;
                } else {
                    std::cout << "Não é Cheia!" << std::endl;
                }
                break;
            case (Command::CommandType::COMPLETA):
                std::cout << ": ";
                if (abb.ehCompleta()) {
                    std::cout << "Sim é Completa!" << std::endl;
                } else {
                    std::cout << "Não é Completa!" << std::endl;
                }
                break;
            case (Command::CommandType::ENESIMO):
                std::cout << command.getArg() << ": ";
                try {
                    resultado = abb.enesimoElemento(command.getArg());
                    std::cout << resultado << std::endl;
                } catch (std::out_of_range bd) {
                    std::cout << bd.what() << std::endl;
                }
                break;
            case (Command::CommandType::IMPRIMA):
                std::cout << ": ";
                std::cout << abb.toString() << std::endl;
                break;
            case (Command::CommandType::MEDIANA):
                std::cout << ": ";
                std::cout << abb.mediana() << std::endl;
                break;
            case (Command::CommandType::POSICAO):
                std::cout << command.getArg() << ": ";
                try {
                    resultado = abb.posicao(command.getArg());
                    std::cout << resultado << std::endl;
                } catch (std::invalid_argument bd) {
                    std::cout << bd.what() << std::endl;
                }
                break;
            case (Command::CommandType::REMOVA):
                std::cout << command.getArg() << ": ";
                sucesso = abb.remove(command.getArg());
                if (sucesso) {
                    std::cout << "Elemento " << command.getArg() << " removido!"
                              << std::endl;
                } else {
                    std::cout << "Não foi possível remover o elemento "
                              << command.getArg() << std::endl;
                }
                break;
            default:
                std::cout << "O comando '" << command.getCommand()
                          << " não foi reconhecido!" << std::endl;
                break;
        }
    }
    return 0;
}
