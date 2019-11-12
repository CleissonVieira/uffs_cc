from Producao import Producao 
import re

class Automato(object):         #carga do automato finito

    FINAL = '$'     #identifica um estado final
    EPSILON = '#'   #identifica o símbolo épsilon
    Estados = dict()                #estados do autômato
    Alfabeto = set()                #símbolos do alfabeto
    Finais = set()                  #estados que são finais
    Texto = str()                   #string de entrada
    NovosEstados = dict()           #usada para identificar a origem das novas produções criadas na determinização
    TransicoesVisitadas = list()    #indicar quais transições já foram visitadas na busca em profundidade da remoção de inúteis
    AutomatoMinimizado = dict()     #guardar o automato ao final do processo de minimização

    def __init__(self):
        self.Estados = dict()       
        self.Alfabeto = set()       
        self.Finais = set()         
        self.NovosEstados = dict()
        self.AutomatoMinimizado = dict()

    def carregaToken(self, simbolo, new):       #inserção de Tokens da Linguagem
        self.Alfabeto.add(simbolo)              #adiciona os símbolos ao alfabeto

        if new:                                                                         #se novo token:
            if simbolo in self.Estados[0]:                                              #se já existir no estado:
                self.Estados[0][simbolo].append(len(self.Estados))                      #adiciona na lista de estados destinos daquele token
            else:                                                                       #se token não existir no estado:
                self.Estados[0].update({simbolo: [len(self.Estados)]})                  #adiciona nova entrada para o token
            self.Estados.update({len(self.Estados): {}})                                #cria um estado vazio para a próxima iteração
        if not new:                                                                      #se símbolo for de um token já existente:
            self.Estados[len(self.Estados) - 1].update({simbolo: [len(self.Estados)]})  #insere no último estado criado
            self.Estados.update({len(self.Estados): {}})                                #cria um estado vazio para a próxima iteração
    

    def carregaGramatica(self, textos):         #leitura das regras da Gramática Regular
        regras = dict()         #mapeamento das regras
        estados = dict()        #estados da gramática
        ignorar = [' ', ':']      

        def novaRegra(self, texto):     #insere uma nova regra no mapa de regras
            if texto == 'S':                #se identificador do estado for S:
                estados.update({0: {}})        #add no estado inicial                
                regras.update({'S': 0})        #mapeia

            else:                #senão
                numero = len(set(list(self.Estados) + list(estados)))           
                regras.update({texto: numero})           #insere a regra com o número                
                estados.update({regras[texto]: {}})      #mapeado para o número do último estado

        def novaTransicao(self, texto, regra):      #insere nova transição nas regras
            self.Alfabeto.add(texto)           #add símbolo no alfabeto

            if regra not in regras:            #se regra não foi mapeada cria nova
                novaRegra(self, regra)       

            if texto in estados[regraAtiva]:          #se símbolo já existe no estado:
                lista = list(set(estados[regraAtiva][texto] + [regras[regra]])) #add simbolo novo aos existentes
                estados[regraAtiva][texto] = lista                           

            else:               #senao add o símbolo no estado.
                estados[regraAtiva].update({texto: [regras[regra]]})   

        for linha in textos:        #percorre as linhas do texto de entrada
            word = ''               #zera a palavra
            for caractere in linha:         #percorre os caracteres da linha
                if caractere in ignorar:        #se estiver na lista de ignorados
                    continue                    #vai para o próximo caracter

                word = word + caractere       #concatena a palavra com o caractere válido

                if re.match('<\S>', word) is not None:    #se a palavra tem o formato de um nome de regra
                    if word[1] not in regras:         #se não existe regra com esse nome
                        novaRegra(self, word[1])          #add a nova regra com esse nome
                    regraAtiva = regras[word[1]]          #marca a flag de regra ativa para add uma transição nessa regra
                    word = ''                                                  

                elif (re.match('\|\S<\S>', word) is not None or re.match('=\S<\S>', word) is not None):     #se palavra tem formato de uma transição             
                    novaTransicao(self, word[1], word[3])           #add uma nova transição à regra ativa
                    word = ''                                                

                elif (re.match('\|<\S>', word) is not None or re.match('=<\S>', word) is not None):     #se palavra tem formato de um nome de regra e está no meio da regra 
                    novaTransicao(self, self.EPSILON, word[2])      #add uma nova épsilon transição à regra ativa
                    word = ''                                                  

                elif ((word == '|' + self.FINAL) or (word == '=' + self.FINAL)):     #se encontrado um caractere que indica estado final: 
                     self.Finais.add(regraAtiva)         #marca a regra ativa como final.

            self.insereEstadosGramatica(estados)         #insere os estados nos estados do automato


    def insereEstadosGramatica(self, estados):      #inserção das regras no automato   
        for nome, estado in estados.items():                   #percore o estado temporario
            self.setAlfabetoEstado(estado)                     #coloca todos os símbolos do alfabeto em estado, até os que tem transição vazia
            for simbolo, transicoes in estado.items():         #percorre todos os itens/transições de estado
                if nome not in self.Estados:                   #se nome/número do estado não existe no automato
                    self.Estados.update({nome: {}})            #add o estado ao automato

                if simbolo in self.Estados[nome]:                               #se símbolo já existe no estado
                    lista = list(set(self.Estados[nome][simbolo] + transicoes)) #add as transições do estado temporário
                    self.Estados[nome][simbolo] = lista                         #junto às transições do estado do automato

                else:     
                    self.Estados[nome].update({simbolo: transicoes})      #senão add as novas transições no estado.


    def imprimir(self, mensagem, First = False):        #imprime o automato no terminal e no arquivo.txt
        self.imprimirTela(mensagem)            
        self.analisador_lexico_sintatico()

    def imprimirTela(self, mensagem = ''):      #imprime automato deterministico
        # print(mensagem)                                             #mostra mensagem, para identificar o automato que se está imprimindo
        estados = self.pegarAutomato()                              #utiliza o estado minimiazdo se existir
        for nome, estado in sorted(estados.items()):                #PERCORRE CADA ESTADO(nome) com uma lista desse estado(estado)
            print(' *' if nome in self.Finais else '  ', end='')    #se NOME está em FINAIS, então *
            print(nome, end=' = ')                                  #imprime NOME/NUMERO do estado
            for simbolo, transicoes in estado.items():              #percorre cada estado    
                if len(transicoes) > 0:                             #se existir transições para símbolo
                    print(simbolo, transicoes, end=', ')            #imprime símbolo e lista de transições
            print('')
        
        
    def analisador_lexico_sintatico(self):
        tabela = self.pegarAutomato()
        fitaS = [] 
        Ts = []    
        codigoFonte = list(open('codigo.txt'))
        separador = [' ', '\n', '\t']
        palavra = ''
        count = 0
        estado = 0
        for linha in codigoFonte:
            count += 1
            for caracter in linha:
                if caracter in separador and palavra:
                    Ts.append({'Linha': str(count), 'Estado': str(estado), 'Rotulo': palavra.strip('\n')})
                    fitaS.append(estado)
                    estado = 0
                    palavra = ''
                else:    
                    try:
                        estado = tabela[estado][caracter][0]
                    except KeyError:
                        estado = -1
                    if caracter != ' ':
                        palavra += caracter

        print("\nFINAIS: ", self.Finais, "\n")

        print("\n Fita de saída:", fitaS, "\n")

        for x in Ts:
            print(x)
        print('\n')

        for erro in Ts:
            if erro['Estado'] == '-1':
                print('Erro Léxico: linha {}, erro {}' .format(erro['Linha'], erro['Rotulo']))
        
        


        


    def setAlfabetoEstado(self, estado):    #em um estado é inserido todos os símbolos do alfabeto
        for simbolo in sorted(self.Alfabeto):   #percorre os símbolos do alfabeto da linguagem
            if simbolo not in estado:           #se não existir no estado:
                estado.update({simbolo: []})    #add o símbolo associado à uma lista vazia.


    def setAlfabeto(self):          #relacioana os estados com os símbolos do alfabeto
        estados = self.pegarAutomato()          #utiliza o estado minimizado se existir
        for nome, estado in estados.items():    #percorre estados
            self.setAlfabetoEstado(estado)      #relacioana o estado com os símbolos do alfabeto

    def carrega(self, arquivo):     #Insere no automato
        arquivo = open(arquivo, 'r')
        entrada = arquivo.read()                        #converte o arquivo para string
        new = True                                      #verificar se tem duas quebras de linha, significa que não tem mais tokens pra ler
        self.Estados.update({len(self.Estados): {}})    #inicializa o estado inicial com: um inteiro para chave e um dicionário vazio para conteúdo

        for simbolo in entrada:                         #percorre caractere a caractere na string da estrada
            simbolo = simbolo.lower()                   #pega todas as letras minusculas

            if simbolo == '\n':                         #verifica onde tem quebra de linha
                if new:                                 #com duas quebras de linha termina a leitura dos tokens
                    break                               
                new = True                              #verificar se ainda tem simbolos a serem lidos
                self.Finais.add(len(self.Estados) - 1)  #adiciona o simbolo final do token em um estado

            else:
                self.carregaToken(simbolo, new)         #carrega o token para o autômato.
                new = False                             #reseta a variável para o próximo símbolo

        texto = entrada.partition('\n\n')[2]            #separa o texto após as duas quebras de linha para a leitura de gramática
        self.carregaGramatica(texto.splitlines())       #envia o texto em formato de lista com as linhas do texto
        self.setAlfabeto()                              # Relaciona os estados com o alfabeto da linguagem


    def pegarAutomato(self):           #retorna automato mais atualizado existente
        if len(self.AutomatoMinimizado) > 0:    #se tamanho do dicionário de estados maior que 0 já existe um autômato minimizado
            return self.AutomatoMinimizado   
        else:                 #senão retorna o da estrutura original
            return self.Estados             