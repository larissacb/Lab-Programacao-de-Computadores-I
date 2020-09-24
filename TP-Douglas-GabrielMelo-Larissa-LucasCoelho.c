/* Nome: Douglas Fernandes da Costa
Matricula: 20183013697
Nome: Gabriel Melo Sette Ataide Arantes
Matricula: 20183015771
Nome: Larissa de Castro Braga
Matricula: 20183000581
Nome: Lucas Coelho de Lima
Matricula: 20183001542

Descrição: Código que realiza a contagem do numero de atomos e identifica o seu tipo e os aminoácidos presentes em um arquivo de entrada. Além disso, conta a quantidade de átomos e aminoácidos de cada tipo, além de imprimir em um arquivo de saida as linhas do arquivo de entrada que contém o inicio da linha a palavra ATOM*/

//*****************************Bibliotecas e defines****************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 3000
//******************************************************************************

int main(int argc, char *argv[]){
	//***********************Variaveis locais da int main*************************************************
    int i=0, j=0, k=0, l=0, m=0;									     
	char nome_atom[DIM][10],nome_amino[DIM][10],aux[DIM],nome_atom_aux[DIM][10],nome_amino_aux[DIM][10],linha[DIM][500],string[1000],primeira[100];
	int indent_amino[DIM],indent_amino_aux[DIM], cont_rep=0, indent_aux=0, cont_atom_aux=0,cont_atom=0,total_atom=0,cont_amino_aux=0,cont_amino=0,total_amino=0;
	float x[DIM],y[DIM],z[DIM],**p;
	//*****************************************************************************************************

	//***********************Testes para aberturas dos arquivos********************************************
    	if(argc!=3)
        	printf("Erro de parametrizacao\nEscreva o arquivo de entrada e saida\n");
    	else {
        	FILE *entrada=NULL;
        	FILE *saida=NULL;
        	entrada=fopen(argv[1],"r"); //abertura do arquivo de entrada digitado pelo terminal
        	if(entrada==NULL){
            		printf("O arquivo %s nao pode ser aberto\n",argv[1]);
            	return 1;
			}
        	saida=fopen(argv[2],"w"); //abertura do arquivo de saida digitado pelo terminal
        	if(saida==NULL){
            	printf("O arquivo %s nao pode ser aberto\n",argv[2]);
            	return 1;
			}
	//*****************************************************************************************************

        while(!feof(entrada)){ //enquanto nao retornar EOF do arquivo, as linhas são lidas 
            fgets(string,DIM,entrada);
            sscanf(string, "%s", primeira); //leio a primeira palavra de uma linha que é uma string
            if(strcmp(primeira,"ATOM")==0){ //caso a linha seja iniciada pela palavra ATOM, é salva em uma matriz de strings chamada linha
                strcpy(linha[j], string);//salvo uma linha em uma linha da string por inteiro
                j++;}} //j representa o numero de atomos do arquivo

        for(m=0;m<j;m++) //as linhas que contem a palavra atom são lidas usando o sscanf para que os dados desejados sejam alocados em seus vetores correspondetes
            sscanf(linha[m], "%*s %*d %s %s %*s %d %f %f %f %*f %*f %*s", nome_atom[m], nome_amino[m],&indent_amino[m],&x[m],&y[m],&z[m]);

        //*************Alocação dinamica da matriz e posterior armazenamento das coordenadas****************
        p=(float**)malloc(j*sizeof(float*)); //Reserva espaço para as linhas da matriz
        for(m=0;m<j;++m)
            p[m]=(float*)malloc(3*sizeof(float)); //Reserva espaço para as colunas
        for(m=0;m<j;++m){
            for(l=0;l<3;++l){ //Atribui os valores das coordenadas salvas anteriormente em vetores na matriz
                if(l==0)
                    p[m][l]=x[m];
                if(l==1)
                    p[m][l]=y[m];
                if(l==2)
                    p[m][l]=z[m];}}
         //***************************************************************************************************
        //Escrita no arquivo de saída o número do átomo, o nome do átomo, o nome do aminoácido e suas coordenadas atômicas no arquivo de saida
        for(i=0,l=1;i<j;++i,++l)
            fprintf(saida,"%d %s %s %.3f %.3f %.3f\n",l,nome_atom[i],nome_amino[i],x[i],y[i],z[i]);

        //Estatísticas gerais que são impressas na tela do terminal
        printf("Estatisticas:\n");
        printf("Atomos de cada tipo presentes no arquivo:\n");
        //Imprime a quantidade de átomos de cada tipo
        for(m=0;m<j;++m){
            strcpy(aux,nome_atom[m]);
            strcpy(nome_atom_aux[m],aux);
            for(l=0,cont_atom_aux=0;l<m;++l) {
                if(strcmp(nome_atom_aux[l],aux)==0)
                    cont_atom_aux++; }
            if(cont_atom_aux==0){ //para ver se nao tem repetido 
                for(k=0,cont_atom=0;k<j;++k){
                    if(strcmp(nome_atom[k],aux)==0) //quando encontra um nome igual soma a qtde de vezes que ele aparece
                        cont_atom++;} //conta a quantidade de cada tipo de atomo
                printf("%s:%d\n",aux,cont_atom);
                total_atom+=cont_atom;}}
        printf("Aminoacidos de cada tipo presentes no arquivo:\n");
        //Imprime a quantidade de aminoácidos de cada tipo
        for(m=0;m<j;++m){
            strcpy(aux,nome_amino[m]);
            strcpy(nome_amino_aux[m],aux);
            for(l=0,cont_amino_aux=0;l<m;++l) {
                if(strcmp(nome_amino_aux[l],aux)==0)
                    cont_amino_aux++; }
            if(cont_amino_aux==0){ //para ver se nao tem repetido
                for(k=0,cont_amino=0;k<j;++k){
                    if(strcmp(nome_amino[k],aux)==0) //quando encontra um nome igual soma a qtde de vezes que ele aparece
                        cont_amino++;} //conta a quantidade de cada tipo de atomo
                printf("%s:%d\n",aux,cont_amino);}}
        //Imprime a quantidade total de átomos
        printf("Quantidade total de atomos presentes no arquivo: %d\n",total_atom);
		//Conta a quantidade de aminoacidos diferentes no arquivo
        for(m=0,l=0;m<j;++m){
            indent_aux=indent_amino[m];
            for(k=0,cont_rep=0;k<j;++k)
                if(indent_amino_aux[k]==indent_aux)
                    cont_rep++;
            if(cont_rep==0){
            indent_amino_aux[l]=indent_aux;
            l++;
            total_amino=l;}}
        //Imprime a quantidade total de aminoácidos na tela do terminal
        printf("Quantidade total de aminoacidos presentes no arquivo: %d\n",total_amino);

        //******************Fecha os arquivos abertos anteriormente******************
        fclose(entrada);
        fclose(saida);
        //***************************************************************************
    }
    return 0;
}