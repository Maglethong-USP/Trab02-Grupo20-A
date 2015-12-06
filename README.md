
Compilação
-----

mkdir bin
g++ -o ./bin/sequencial ./src/Image.cc ./src/Pixel.cc ./src/sequencial.cc 
mpiCC -o ./bin/parallel ./src/Image.cc ./src/Pixel.cc ./src/parallel.cc -fopenmp


Execução
---------
Sequencial:
./bin/sequencial arquivo_de_entrada arquivo_de_saida

Paralelo:
mpirun --host lista_de_nodos -np numero_de_processos ./bin/parallel arquivo_de_entrada arquivo_de_saida numero_de_cortes_verticais numero_de_cortes_horizontais


(V) numero_de_cortes_verticais 
(H) numero_de_cortes_horizontais 
(NP) numero_de_processos 
NP = V*H


exemplo:
mpirun --host node03,node04,node07,node11 -np 4 ./bin/parallel arquivo_de_entrada arquivo_de_saida 2 2


Imagens de entrada
-------------------

/home/grupo20a/Imagens/
