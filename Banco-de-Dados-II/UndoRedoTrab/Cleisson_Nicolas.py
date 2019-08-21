import re;
arquivo = open('teste03.txt', 'r')
arquivolist = list(arquivo)     #cria uma lista com o .txt
UNDO = []                       #salva quem vai ser feito UNDO
UNDOcheck = []
REDO = []                       #salva quem vai ser feito REDO
REDOcheck = []

    #Variaveis p/ identificar se existe no .txt
commit = re.compile(r'commit', re.IGNORECASE) #re.IGNORECASE -> ignorar se maiuscula ou minuscula
start = re.compile(r'start', re.IGNORECASE)
startckpt = re.compile(r'start ckpt', re.IGNORECASE)
endckpt = re.compile(r'end ckpt', re.IGNORECASE)
extracT = re.compile(r'(?!commit\b)(?!CKPT\b)(?!Start\b)\b\w+', re.IGNORECASE) #Ignora as palavras descritas e coloca as demais em uma lista com .findall
words = re.compile(r'\w+', re.IGNORECASE)   #Utilizado p/ pegar o valor das variaveis

valores = words.findall(arquivolist[0])
variaveis = {}

for i in range(0,len(valores),2): #Iniciar primeiros valores das variáveis (A B C...)
    variaveis[valores[i]]= valores[i+1]
del valores
print("", variaveis)
end = 0

for linha in reversed(arquivolist): #Verificar os casos e criar as listas de UNDO e REDO
    if startckpt.search(linha): #Caso nao tenha sido encontrado o end ele ignora o checkpoint
        if end:
            print("Start Checkpoint")
            Tx = extracT.findall(linha)
            for i in range(0, len(Tx)):
                if Tx[i] not in REDO:
                    UNDO.append(Tx[i])
            break
    elif start.search(linha):   #Procura start
        Tx = extracT.findall(linha)[0]
        if Tx not in REDO:
            UNDO.append(Tx)
    elif commit.search(linha):  #Procura commit
        REDO.append(extracT.findall(linha)[0])
    elif endckpt.search(linha):
        print(" End  Checkpoint")
        end = 1

print("\nAplicar UNDO:", UNDO)
print("Aplicar REDO:", REDO, "\n")

for i in range(len(arquivolist)-1, 0, -1): #Aplicar UNDO e REDO
    linha = arquivolist[i]
    if start.search(linha) and not startckpt.search(linha):
        Tx = extracT.findall(linha)[0]
        if Tx in UNDO:
            UNDO.remove(Tx)
            UNDOcheck.append(Tx)
        if Tx in REDO:
            REDO.remove(Tx)
            REDOcheck.append(Tx)
        if not len(UNDO) and not len(REDO):
            break
    elif words.findall(linha)[0] in UNDO:
        variaveis[words.findall(linha)[1]] = words.findall(linha)[2]

for j in range(i,len(arquivolist)-1,1):
    linha = arquivolist[j]
    if words.findall(linha)[0] in REDOcheck:
        variaveis[words.findall(linha)[1]] = words.findall(linha)[3]

print("Aplicado UNDO:", UNDOcheck)
print("Aplicado REDO:", REDOcheck, "\n")
print("Resultado:", variaveis)
arquivo.close()