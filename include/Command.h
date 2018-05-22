// Copyright 2018

/**
 * @file   Command.h
 * @brief  Declaração da Classe Command e de seu enum, métodos e atributos.
 *
 * @author Gleydvan
 * @author JohnVithor
 * @author JoMedeiros
 *
 * @since  22/05/2018
 * @date   22/05/2018
 */

#ifndef INCLUDE_COMMAND_H_
#define INCLUDE_COMMAND_H_

#ifndef _GLIBCXX_STRING
#include <string>
#endif

#ifndef _GLIBCXX_SSTREAM
#include <sstream>
#endif

#ifndef _TYPEINFO
#include <typeinfo>
#endif

class Command {
   public:
    enum class CommandType {
        ENESIMO,
        POSICAO,
        MEDIANA,
        CHEIA,
        COMPLETA,
        IMPRIMA,
        REMOVA,
        INVALIDO
    };

    Command();

    explicit Command(std::string command, std::string arg = "");

    ~Command() = default;

    CommandType getType();

    int getArg();

    std::string getCommand();

   private:
    CommandType type;
    std::string str;
    int argument;
};
#endif  // INCLUDE_COMMAND_H_
