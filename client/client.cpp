#include "client.h"

uint8_t* varCompartilhada;

// #define DEV

void comunicacaoServidorTCP(int socketClient)
{
    uint8_t buffer[14];
    int bytesRecebidos;
    int aux;

    while(1) {
        int aux;
        aux = send(socketClient, buffer, 14, 0);
        if(aux != 14){
	    	printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
            break;
        }
        aux = recv(socketClient, buffer, 14, 0);
    	if(aux < 0){
            printf("Não recebeu o total de bytes enviados\n");
            break;
        }
        memcpy(varCompartilhada, buffer, 14);
        sleep(1);
        memcpy(buffer, varCompartilhada, 14);
    }
    return;

}

void *criaCliente(void* args){
    int socketClient;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    // Criar Socket
    if((socketClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

    // Construir struct sockaddr_in
    memset(&serverAddr, 0, sizeof(serverAddr)); // Zerando a estrutura de dados
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(IP_SERVER);
	serverAddr.sin_port = htons(SERVER_PORT);

    // Connect
	if(connect(socketClient, (struct sockaddr *) &serverAddr, 
							sizeof(serverAddr)) < 0)
		printf("Erro no connect()\n");
    
    comunicacaoServidorTCP(socketClient);
    close(socketClient);
    return NULL; 
}

void quit_handler(int sig){
    exit(0);
}

int main(int argc, char **argv)
{
#ifndef DEV
    if (!bcm2835_init())
	return 1;
#endif

    varCompartilhada = new uint8_t[14];

    signal(SIGINT, quit_handler);

    pthread_t client_tid, gpio_tid;
    pthread_create(&gpio_tid, NULL, gpio_handler, varCompartilhada);
    pthread_create(&client_tid, NULL, criaCliente, NULL);
    pthread_join(gpio_tid, NULL);
    pthread_join(client_tid, NULL);

    return 0;
}
