### Trabalho da Unidade 2 da disciplina de Estruturas de Dados Básicas II

# Árvore de Busca Binária 


Esse repositório é correspondente ao trabalho da segunda unidade da disciplina de Estruturas de Dados Básicas do curso de Bacharelado em Tecnologia da Informação(BTI) do Instituto Metrópole Digital(IMD), Universidade Federal do Rio Grande do Norte(UFRN).
O trabalho é uma implementação de uma Árvore de Busca Binária com algumas funcionalidades adicionais.

## Intro

Uma árvore de busca binária é uma estrutura de dados en que a chave de cada nó da subárvore a esquerda é menor ou igual a chave do seu nó pai. 
A árvore de busca suporta várias operações como busca, mínimo, máximo, predecessor, sucessor, inserção e remoção.

#### Funcionalidades (lista TODO)

- [x] percurso simétrico
- [x] busca
- [x] inserir (Usa a ideia de busca)
- [x] remover (Usa a ideia de busca)
- [x] enésimo elemento
- [x] acessar posição
- [x] mediana
- [x] é cheia (booleano)
- [x] é completa (booleano)
- [x] toString por nível

#### Opcionais/Extras

- [x] mínimo
- [x] máximo

## Requisitos

* g++ version 5.4.0 ou mais recente

#### No Ubuntu

Atualize a lista do seu gerenciador de pacotes com a versão mais recente do g++ e depois instale o compilador:

`$ sudo apt-get update`

`$ sudo apt-get install g++`

## Intruções de Compilação

Para compilar o programa basta digitar `make` no terminal dentro do diretório do projeto.
Outros alvos do makefile:

#### `make run`:

Executa o programa caso ele já tenha sido compilado.

#### `make debug`:

Compila os arquivos com opção de depuração.

#### `make clean`:

Apaga os arquivos objetos gerados, o executável e a documentação.

#### `make test`:

Compila o arquivo com os casos de teste da classe.

## Instruções de Uso

A compilação irá gerar um arquivo executável na pasta `./bin` com o nome `ABB` (maiúsculo). A instrução de execução é (caso esteja na pasta principal do projeto):

`./bin/ABB -a <arquivo_arvore> -i <arquivo_instrucoes>`

Onde:

- `<arquivo_arvore>` deve conter uma sequência de valores inteiros separados por um espaço que serão armazenados na árvore.

- `<arquivo_instrucoes>` deve conter umq sequência de operações (uma operação por linha) a serem realizadas na árvore.

Na pasta `./data` existem dois arquivos de exemplo, um para a construção da árvore e outro com os exemplos de comandos.


## Autores
| [<img src="https://avatars1.githubusercontent.com/u/29136918?s=460&v=4" width="100" style="border-radius:50%"/>](https://github.com/gleydvan) | 
[<img src="https://avatars3.githubusercontent.com/u/28351214?s=460&v=4" width="100" style="border-radius:50%"/>](https://github.com/JohnVithor) | 
[<img src="https://scontent.fnat2-1.fna.fbcdn.net/v/t1.0-9/26196311_1726317707421220_3069236098433062740_n.jpg?_nc_cat=0&oh=68686ac8256abd16fd2c09ce0ba80b07&oe=5B9D0B5E" width="100" style="border-radius:50%"/>](https://github.com/JoMedeiros) |
|---|---|---|
| [Gleydvan](https://github.com/gleydvan) | [João Vítor](https://github.com/JohnVithor) | [Josivan Medeiros](http://lcc.ufrn.br/~josivanmedeiros/) |  
| [![Facebook][2]][1.2] [![GitHub][6]][1.6] | [![GitHub][6]][2.6] | [![twitter][1]][3.1] [![Facebook][2]][3.2] [![GitHub][6]][3.6] |

[1]: http://i.imgur.com/tXSoThF.png
[2]: http://i.imgur.com/P3YfQoD.png
[6]: http://i.imgur.com/0o48UoR.png

[1.2]: https://www.facebook.com/gleydvan
[1.6]: https://github.com/gleydvan

[2.3]: jv.venceslau.c@gmail.com 
[2.6]: https://github.com/JohnVithor

[3.1]: https://twitter.com/MedeirosJosivan
[3.2]: https://www.facebook.com/JosivanMedeiros
[3.6]: https://github.com/JoMedeiros

