#include <stdio.h>
#include <winsock2.h>


int main(void)
{
    char buffClient[129];
    char buffServer[129] = "Mensagem recebida!";

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0),&wsa);

    struct sockaddr_in caddr;
    struct sockaddr_in saddr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port        = htons(5000)
    };

    int server = socket(AF_INET,SOCK_STREAM,0); // Cria um novo socket
    int client;
    int resultRecv;
    int csize = sizeof caddr;


    bind(server,(struct sockaddr *)&saddr,sizeof saddr); // Associa o socket a um endereço e porta
    listen(server,5); // Configura o socket para receber as conexões

    while(1)
    {
        client = accept(server,(struct sockaddr *)&caddr,&csize); // Configura o socket para esperar as conexões
        resultRecv = recv(client,buffClient,sizeof buffClient,0); // Permite receber os dados que o cliente envia

        puts(buffClient);
        send(client,buffServer,resultRecv,0); // Permite enviar dados para o cliente

        fflush(stdout);
        closesocket(client); // Permite fechar o socket
    }

    return 0;
}


