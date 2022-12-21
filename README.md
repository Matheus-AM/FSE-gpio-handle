# FSE-gpio-handle
## Trabalho 1 de FSE : sistema central-distribuido para ler gpio
Este trabalho tem por objetivo a criação de um sistema distribuído de automação predial para monitoramento e acionamento de sensores e dispositivos de um prédio com múltiplas salas. O sistema deve ser desenvolvido para funcionar em um conjunto de placas Raspberry Pi com um servidor central responsável pelo controle e interface com o usuário e servidores distribuídos para leitura e acionamento dos dispositivos. Dentre os dispositivos envolvidos estão o monitoramento de temperatura e umidade, sensores de presença, sensores de fumaça, sensores de contagem de pessoas, sensores de abertura e fechamento de portas e janelas, acionamento de lâmpadas, aparelhos de ar-condicionado, alarme e aspersores de água em caso de incêndio.

## Build

Para executar o projeto, primeiro faça o clone do projeto em uma placa raspberry pi 4:

```
  $ git clone https://github.com/Matheus-AM/FSE-gpio-handle.git
```

em seguida, vá para a pasta do client ou do server, dependendo de qual voce quiser executar:

``` 
  $ cd FSE-gpio-handle/client
```

ou

```
  $ cd FSE-gpio-handle/server
```

em seguida, basta dar um make para buildar e um make run para executar:

```
  $ make
  $ make run
```

## Observações
- o arquivo de configuração a ser lido está com o path fixo, caso precise mudar, acesse a gpio.cpp
- o ip está fixo no server.h e no client.h
