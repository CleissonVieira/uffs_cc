q = "aluno/page1.dat"
with open(q, "rb") as arquivo:
   arq = arquivo.read()
   print(arq)
   arquivo.close()