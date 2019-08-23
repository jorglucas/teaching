#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) //função principal inicializada com os argumentos digitados
{
    int cont; //variável para contar quantas vezes será executado os comandos(bash_cmd)
    unsigned long long k; //variável utilizada para loop que simula o uso intenso de CPU
    int pid = fork(); //guarda o pid do precesso filho criado pela chamada de sistema fork()
    char id_process[500], bash_cmd[500]; //id_process é utilizada para guardar o valor do id do processo filho e que será convertida para string. bash_cmd será o comando passado para a função system(bash_cmd), que executa esse comando no terminal do linux.
    if(pid < 0) //se o pid for < 0, houve erro na criação do processo filho
    {
        perror("Falha ao criar o processo!\n");
        exit(-1);
    }
    else if(pid  > 0) //se o id for > 0, o processo filho foi executado e retornou o id do seu processo para o pai
    {
        sprintf(id_process, "%d", pid); //salva o id do processo filho e o converte para string
        if(strcmp(argv[1], "uso_cpu") == 0) //se o argumento 1 for uso_cpu, entra nessa condição e executa o código de uso intenso da CPU
        {
            printf("  PID | CPU(%%)\n");
              sprintf(bash_cmd,"ps -e -o pid,pcpu | grep %s",id_process); //Salva o comando "ps -e -o pid,pcpu | grep (id)" na string bash_cmd e vai para o for(), para ser executado 10 vezes, ou seja, 10 segundos.

        }
        else if(strcmp(argv[1], "cpu_e_memoria") == 0) //se o argumento 1 for cpu_e_memoria, entra nessa condição e executa o código de uso intenso de memória e uso da cpu
        {
            printf("  PID | CPU(%%) | MEMORIA(KB)\n");
            snprintf(bash_cmd,500, "ps -e -o pid,pcpu | grep %s ;pmap %s |grep -i total",id_process,id_process); //Salva o comando "pps -e -o pid,pcpu | grep (id) ;pmap (id) |grep -i total" na string bash_cmd e vai para o for(), para ser executado 10 vezes, ou seja, 10 segundos.
        }

        for(cont = 0;cont < 10; ++cont) //loop finito de execução do comando (bash_cmd)
        {
            system(bash_cmd); //função que escreve no terminal o comando bash_cmd
            sleep(1); //Pausa por 1 segundo e em seguida executa novamente o comando
        }

        sprintf(bash_cmd,"kill %s",id_process); //salva na string bash_cmd o comando ""kill (id)"
        system(bash_cmd); //matando o filho
    }

    else //Se o pid for == 0, entra nessa condição e o filho executa se "programa"
    {
        if(strcmp(argv[1], "uso_cpu") == 0) //verifica se o argumento 1 é uso_cpu
        {
            for(;;) //simula o uso intenso da cpu através de um loop infinito
            {

            }
        }
        else if(strcmp(argv[1], "cpu_e_memoria") == 0) //verifica se o argumento 1 é cpu_e_memoria
        {
            for(k = 0; k < 99999999; ++k) ///simula o uso intenso da cpu através de um loop finito, porém muito longo
            {
                malloc(sizeof(2)); //função usada para alocar 2 bytes consecutivos na memória RAM, que se repete por 99999999 vezes, alocando assim, muita memória para esse processo
            }
        }
    }
    exit(0) ; // encerra o processo
}
