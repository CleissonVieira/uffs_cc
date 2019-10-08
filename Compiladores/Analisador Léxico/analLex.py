
codigoFonte = open('codigo.txt', 'r')
automato = open('automato.txt', 'r')
ts = open('ts.txt', 'a')


for linha in codigoFonte: # Percorre todas as linhas  
    for caracter in linha: # Percore todos os caracteres da linha
        print(caracter)
    break 