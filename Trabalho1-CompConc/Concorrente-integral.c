#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
//numero de threads
#define NTHREADS 3
//variavel de lock
pthread_mutex_t mutex; 
//definição de 'e' para uso na math.h
#define e 2.71828
//Definição das funções presentes
double calculaArea(double pontoA, double pontoB);
double calculaPMedio(double pontoA, double pontoB);
double calculaIntegral(double pontoA, double pontoB,double erro);
double Modulo(double num);
double func(double x);
int funcNum = 0;
double resultadoFinal = 0.0;
//Pontos principais do intervalo e erro
double pontoInicio, pontoFim, erro;
//quantidade de subintervalos que divido a função
int partes=3;

// Calcula a área de um retângulo
double calculaArea(double pontoA, double pontoB){
    return ((pontoB - pontoA) * func(pontoB));
}

// Calcula o ponto médio 
double calculaPMedio(double pontoA, double pontoB){
    return (pontoB + pontoA)/2;
}

//Calcula a integral
double calculaIntegral(double pontoA, double pontoB, double erro){
    double pontoMedio = calculaPMedio(pontoA, pontoB);
    double retanguloEsq = calculaArea(pontoA, pontoMedio);
    double retanguloDir = calculaArea(pontoMedio, pontoB);
    double retanguloMaior = calculaArea(pontoA, pontoB);
    double errinho = retanguloMaior - (retanguloEsq + retanguloDir);
    if(Modulo(errinho) < erro ){
        return retanguloDir+retanguloEsq;
    }
    else{
        return calculaIntegral(pontoA, pontoMedio, erro) + calculaIntegral(pontoMedio, pontoB, erro);
    }
}

// Retorna a função f(x) 
double func(double x) {
    switch(funcNum){
        case 0:
            return (1 + x);
            break;
        case 1:
            return (sqrt(1 - pow(x,2)));
            break;
        case 2:
            return (sqrt(1 + pow(x,4)));
            break;
        case 3:
            return  sin(pow(x,2));
            break;
        case 4:
            return  cos(pow(e, -x));
            break;
        case 5:
            return  (cos(pow(e, -x)) * x);
            break;
        case 6:
            return (cos(pow(e, -x)) * (0.005 * pow(x,3)));
            break;
    }
}

//Função que substitui o abs() pois este nao suporta double.
double Modulo(double num){
    if(num < 0)
        num = num * (-1);
    return num;
}

//Função ExecutaTarefa => separa a tarefa entre as threads
double ExecutaTarefa(void *threadid){
	int i, tid = *(int*) threadid;
	//threads recebem o intervalo dividido em N partes
    //threads calculam integrais das partes (dividem as partes entre si)
    //caso nao seja suficiente, numero de partes aumenta, e threads repetem as ações até respeitar o erro máximo
}

//Função principal
int main(){
    double tempo_gasto = 0.0;
    printf("Digite a funcao desejada a ser integrada:\n(0) f(x) = 1 + x,\n(1) f(x) = sqrt(1 - pow(x, 2)), -1 < x < 1,\n(2) f(x) = sqrt(1 + pow(x, 4)),\n(3) f(x) = sin(pow(x, 2)),\n(4) f(x) = cos(pow(e, -x)),\n(5) f(x) = cos(pow(e, -x)) * x,\n(6) f(x) = cos(pow(e, -x)) * (0.005 * pow(x, 3) + 1).\n");
    scanf("%d", &funcNum);
    if(funcNum < 0 || funcNum > 6){
        printf("Opcao invalida.\n");
        return 0;
    }
    printf("Digite o limite de integração inicial:\n");
    scanf("%lf", &pontoInicio);
    printf("Digite o limite de integração final:\n");
    scanf("%lf", &pontoFim);
    printf("Digite o erro máximo aceitável:\n");
    scanf("%lf", &erro);
    // Pega o horário no momento
    clock_t begin = clock();
    pthread_t tid[NTHREADS];
	int t, id[NTHREADS];
	for(t=0; t<NTHREADS; t++) {
		id[t]=t;
		if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *) &id[t])) {
	  		printf("--ERRO: pthread_create()\n"); exit(-1);
		}
	}
	//--espera todas as threads terminarem
	for (t=0; t<NTHREADS; t++) {
		if (pthread_join(tid[t], NULL)) {
	  	printf("--ERRO: pthread_join() \n"); exit(-1); 
	  	} 
	}
	//Pega o horário no momento
	clock_t end = clock();
	// calculando o tempo a partir da diferenca entre o inicio e o fim do programa
	tempo_gasto += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %f segundos", tempo_gasto);
    return 0;
}