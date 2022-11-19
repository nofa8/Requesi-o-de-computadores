workzão!

-Pretende-se elaborar um programa em linguagem C que auxilie na gestão da requisição
de computadores portáteis pelos membros da comunidade académica do Politécnico. 

-Registar: computadores portáteis, às
requisições efetuadas e respetivas devoluções, bem como às avarias e reparações
ocorridas

-No registo de requisição de um portátil deverá ser identificado o computador (disponível)
selecionado pelo utente, bem como o prazo de requisição (máximo de 30 dias).

-Posteriormente poderão ser efetuadas renovações, por 7 dias, dessa requisição. Caso a
devolução ocorra após o prazo de requisição, será cobrada uma multa de 10€ por cada
dia de atraso.

-Caso ocorra uma avaria num portátil requisitado, este deverá ser devolvido.
Após o registo da reparação de um portátil (avariado), ele voltará a estar disponível para
ser requisitado.

___1st Structures
-Portátil: Cada computador portátil é caracterizado por um (int)número de identificação
(único), (str?)pela designação,  (string) pelo processador (i3, i5, i7), (int) memória RAM, pelo
(string) estado (disponível, requisitado, avariado), (string)localização (Residências, Campus1,
Campus2 ou Campus5), (struct int) data de aquisição e (float?) valor do equipamento.
Considera-se que, no máximo, existirão (MAX = 30 computadores portáteis)

__2nd Structures
-Requisição: Cada requisição é caracterizada por um código (string única), pelo número
de identificação do portátil(int), pelo nome do utente(string) , pelo tipo de utente(char!?string!?) (estudante,
docente ou técnico administrativo) pela data de requisição(struct ints), pelo prazo de requisição
e pelo estado da requisição (struct int, string)    (ativa, concluída).
Para cada requisição será também necessário registar a data da devolução(anotha struct), local
de devolução(string?!char?!) (Residências, Campus1, Campus2 ou Campus5) e o (if com cenas ...)valor da multa
paga.





1---- Menu
2---Inserir e listar informação referente a todos os portáteis, listar para cada portátil a quantidade de avarias, a quantidade de requesições, prazo de requisição e tipo de utente.
3---Registar as alterações de localização de um computador. e a aquisiçáo do computador
4---Listar dados de todas as requisições, mostrar duração da requisição, o campus onde foi devolvido e o valor da multa
5---Registar devolução do computador, previamente requisitado, toda a informação da tal requisição(processador, memória, num log)
6---Renovar requisições
7---Registar avarias e reparações
8---Informação referente a computadores e requisições em ficheiros binários, armanezar e ler
9---Apresentar a informação de uma requisição, selecionada pelo utilizador, incluindo designação, estado e quantidade total de dias requisitados
10--Apresentar dados estatísticos:percentagem de portateis com cada tipo de processador, custo médio de cada multa paga, tipos de utente com a menor quantia de requisições, e devoluções recentes
11--Apresentar lista de todas as avarias ocurridas, com dados do portátil, tipo de avaria (temporária, permanente), data da avaria e tempo de duração.


/\
Relatório contendo obrigatoriamente a descrição e representação gráfica das
estruturas de dados utilizadas, e a identificação das funcionalidades não
desenvolvidas ou parcialmente/incorretamente desenvolvidas.
Poderá também conter a justificação de algumas opções de implementação tomadas
/\






O Projeto deverá estar dividido em várias funções e dividido por vários ficheiros, de
forma a facilitar a sua correta estruturação, implementação e entendimento, e para
evitar a repetição de código.
• Deverão ser efetuadas todas as validações e proteções necessárias ao correto
funcionamento do programa.
• O programa deverá apresentar mensagens de aviso/erro sempre que necessário.
• Deverá ser dada prioridade à implementação das funcionalidades requeridas, em
detrimento da implementação de funcionalidades adicionais.
• A funcionalidade do programa é mais relevante do que a apresentação da informação.
