from Automatos import Automato
from Producao import Producao

class Inuteis(Automato):

    def __init__(self, automato):
        super(Inuteis, self).__init__()
        self.Estados = automato.Estados
        self.Alfabeto = automato.Alfabeto
        self.Finais = automato.Finais
        self.TransicoesVisitadas = automato.TransicoesVisitadas
        self.AutomatoMinimizado = automato.AutomatoMinimizado

    def gerarEstadosParaMinimizacao(self):
        estadosTemp = dict()
        AutomatoValido = self.pegarAutomato()

        for transicao in AutomatoValido:
            if (transicao in self.Finais) and (AutomatoValido[transicao] == {}):
                estadosTemp.update({transicao: {}})
                continue

            for producao in list(AutomatoValido[transicao]):
                if len(AutomatoValido[transicao][producao]) > 0:
                    if transicao not in estadosTemp: 
                        estadosTemp.update({transicao: {producao: Producao(AutomatoValido[transicao][producao][0])}})
                    else:
                        if producao not in estadosTemp[transicao]:
                            estadosTemp[transicao].update({producao: Producao(AutomatoValido[transicao][producao][0])})
                else:                    
                    if ((transicao in estadosTemp) and (producao not in estadosTemp[transicao])):
                        estadosTemp[transicao].update({producao: Producao(-1)})
                    elif transicao in self.Finais:
                        estadosTemp.update({transicao: {producao: Producao(-1)}})

        return estadosTemp

    def adicionaAutomatoMinimizado(self,transicao,producaoAtual,producaoInserir):
        if producaoAtual == -1:
            if transicao not in self.AutomatoMinimizado:
                self.AutomatoMinimizado.update({transicao: {}})
        else:
            if transicao not in self.AutomatoMinimizado:
                self.AutomatoMinimizado.update({transicao: {producaoAtual: [producaoInserir]}})
            else:
                if producaoAtual not in self.AutomatoMinimizado[transicao]:
                    self.AutomatoMinimizado[transicao].update({producaoAtual: [producaoInserir]})