#include "server.h"

uint8_t* varCompartilhada;


void* criaServidor(void *arg){
    int socketServidor, socketClient;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    unsigned int clienteLength;

	// Abrir Socket
    if(( socketServidor = socket(AF_INET, SOCK_STREAM, 0)) <0)
        printf("Erro ao abrir o socket\n");

   	// Montar a estrutura sockaddr_in
	memset(&serverAddr, 0, sizeof(serverAddr)); // Zerando a estrutura de dados
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//qualquer endereço
	serverAddr.sin_port = htons(SERVER_PORT);

    //Bind
    if (bind(socketServidor, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        printf("erro binding\n");
    
    //Listen
    if (listen(socketServidor, 10) < 0)
        printf("listen error\n");
    
    // while (1) 

	while(1) {
		clienteLength = sizeof(clientAddr);
		if((socketClient = accept(socketServidor, 
			                      (struct sockaddr *) &clientAddr, 
			                      &clienteLength)) < 0)
			printf("Falha no Accept\n");
		comunicacaoClienteTCP(socketClient);
		close(socketClient);
	}
    close(socketServidor);
    return NULL;
}


void comunicacaoClienteTCP(int socketClient) {
	int tamanhoRecebido;

    if((tamanhoRecebido = recv(socketClient, varCompartilhada, 14, 0)) < 0)
		printf("Erro no recv()\n");
	while (tamanhoRecebido > 0) {
		if(send(socketClient, varCompartilhada, tamanhoRecebido, 0) != tamanhoRecebido)
			printf("Erro no envio - send()\n");
		
		if((tamanhoRecebido = recv(socketClient, varCompartilhada, 14, 0)) < 0)
			printf("Erro no recv2()\n");

        sleep(0.5);
	}

}

int main(int argc, char **argv)
{
    pthread_t menu_tid;
    pthread_t server_tid; 
    varCompartilhada = new uint8_t[14];

    int r = pthread_create(&menu_tid, NULL, menu, varCompartilhada);
    int r2 = pthread_create(&server_tid, NULL, criaServidor, NULL);
    pthread_join(server_tid, NULL);
    pthread_join(menu_tid, NULL);

    return 0;
}
