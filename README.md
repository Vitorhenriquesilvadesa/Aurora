# Aurora Lang

### Bem-vindo ao repositório oficial da linguagem de programação Aurora!

Aurora é uma linguagem de programação emergente, ainda em desenvolvimento,
e visa tornar acessível e simples aproveitar os recursos da GPU.
A sintaxe da Aurora é moderna, mas incorpora elementos de linguagens como
Java e C++, buscando manter a curva de aprendizado em um nível médio.

## Visão geral do projeto:

O projeto da linguagem Aurora possui até o momento quatro módulos, cada
um listado a seguir:

Aurora Core: Onde reside tudo o que é usado em várias partes da aplicação,
como tokens, o conjunto de instruções da Aurora Virtual Machine (AVM)
denominado Gear, macros de exportação e importação de símbolos de vínculo
dinâmico (DLL).

- Aurora Compiler: É aonde parte do trabalho pesado acontece, este módulo inclui
em seu escopo o Scanner, responsável por transformar o código-fonte em tokens,
o AurParser, que é o Parser da linguagem Aurora, ele é responsável por executar
algumas etapas do pipeline de compilação, e o AurCompiler, que é o responsável
por processar todos os dados gerados em etapas anteriores e converter tudo no
formato Aurora Byte Code (ABC).

- Aurora VM: É o módulo de Runtime, a implementação da AVM se encontra neste escopo,
ela carrega e executa arquivos gerados pelo AurCompiler, no arquivo estão alguns
dados de segurança para garantir que o bytecode é seguro para execução, e alguns
metadados que checam alguns códigos hashes para garantir a compatibilidade entre
o bytecode e a versão da AVM.

- Aurora: É a aplicação cliente que utiliza todos os módulos do pipeline de
compilação para executar as funcionalidades de cada um. Além disso, este
módulo conta com execução dos comandos disponíveis na linguagem, como
"--help", "--version", "-c", "-e", entre outros.
  em seu escopo o Scanner, responsável por transformar o código-fonte em tokens,
  o AurParser, que é o Parser da linguagem Aurora, ele é responsável por executar
  algumas etapas do pipeline de compilação, e o AurCompiler, que é o responsável
  por processar todos os dados gerados em etapas anteriores e converter tudo no
  formato Aurora Byte Code (ABC).

- Aurora VM: É o módulo de Runtime, a implementação da AVM se encontra neste escopo,
  ela carrega e executa arquivos gerados pelo AurCompiler, no arquivo estão alguns
  dados de segurança para garantir que o bytecode é seguro para execução, e alguns
  metadados que checam alguns códigos hashes para garantir a compatibilidade entre
  o bytecode e a versão da AVM.

- Aurora: É a aplicação cliente que utiliza todos os módulos do pipeline de
  compilação para executar as funcionalidades de cada um. Além disso, este
  módulo conta com execução dos comandos disponíveis na linguagem, como
  "--help", "--version", "-c", "-e", entre outros.
