// Copyright 2018

/**
 * @file   Command.cpp
 * @brief  Implementação da Classe Command.
 *
 * @author Gleydvan
 * @author JohnVithor
 * @author JoMedeiros
 *
 * @since  22/05/2018
 * @date   23/05/2018
 */

#include "Command.h"

Command::Command() : type(CommandType::INVALIDO), argument(-1) {}

Command::Command(std::string command, std::string arg) {
    type = CommandType::INVALIDO;
    str = command;
    if (command.compare("CHEIA") == 0) {
        type = CommandType::CHEIA;
    }
    if (command.compare("COMPLETA") == 0) {
        type = CommandType::COMPLETA;
    }
    if (command.compare("MEDIANA") == 0) {
        type = CommandType::MEDIANA;
    }
    if (command.compare("IMPRIMA") == 0) {
        type = CommandType::IMPRIMA;
    }
    if (command.compare("ENESIMO") == 0) {
        type = CommandType::ENESIMO;
    }
    if (command.compare("POSICAO") == 0) {
        type = CommandType::POSICAO;
    }
    if (command.compare("REMOVA") == 0) {
        type = CommandType::REMOVA;
    }
    if (arg.compare("") == 0) {
        argument = -1;
        return;
    }
    std::istringstream convert(arg);
    if ((convert >> argument).fail() || !(convert >> std::ws).eof()) {
        argument = -1;
    }
}

Command::CommandType Command::getType() { return type; }

int Command::getArg() { return argument; }

std::string Command::getCommand() { return str; }
