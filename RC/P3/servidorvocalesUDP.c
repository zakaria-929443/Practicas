/**
 * @file servidorvocalesUDP.c
 *
 * Programa *servidorvocalesUDP* que cuenta vocales usando UDP.
 *
 * Uso: servidorvocalesUDP puerto
 *
 * Crea un socket UDP asociado al puerto indicado y atiende a los clientes uno
 * tras otro. Para cada cliente va recibiendo datagramas con cadenas de texto y
 * contando sus vocales, hasta recibir un datagrama con el byte de fin de
 * transmisión (EOT = 4); en ese momento envía al cliente el número total de
 * vocales contadas.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include "comun.h"

// definición de constantes
#define BUFF_SIZE 1000 ///< Tamaño del buffer para las cadenas de texto.

const char fin = 4; // carácter ASCII end of transmission (EOT)

/**
 * Función que crea el socket UDP y lo asocia al puerto local.
 *
 * @param servinfo Estructura de dirección local.
 * @param f_verbose Flag.
 * @return Descriptor de socket.
 */
int establecer_servicio(struct addrinfo *servinfo, char f_verbose)
{
    int sock;

    // crea un extremo de la comunicación (socket de datagramas)
    if (f_verbose) { printf("Creando el socket (socket)... "); fflush(stdout); }
    sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sock < 0)
    {
        perror("Error en la llamada socket: No se pudo crear el socket");
        exit(1);
    }
    if (f_verbose) printf("hecho\n");

    // asocia el socket con el puerto local
    if (f_verbose) { printf("Asociando socket a puerto (bind)... "); fflush(stdout); }
    if (bind(sock, servinfo->ai_addr, servinfo->ai_addrlen) < 0)
    {
        perror("Error asociando el socket");
        exit(1);
    }
    if (f_verbose) printf("hecho\n");

    // en UDP NO hay listen() ni accept(): no hay conexión
    return sock;
}

/**
 * Función que cuenta las vocales en una cadena de texto.
 *
 * @param msg Cadena con el mensaje al que contar vocales.
 * @param s   Longitud del mensaje.
 * @return Número de vocales en msg[0..s].
 */
uint32_t countVowels(char msg[], size_t s)
{
    uint32_t result = 0;
    size_t i;
    for (i = 0; i < s; i++)
    {
        if (msg[i] == 'a' || msg[i] == 'A' ||
            msg[i] == 'e' || msg[i] == 'E' ||
            msg[i] == 'i' || msg[i] == 'I' ||
            msg[i] == 'o' || msg[i] == 'O' ||
            msg[i] == 'u' || msg[i] == 'U') result++;
    }
    return result;
}

/**
 * Programa principal
 *
 * @param argc Número de argumentos usados en la línea de comandos.
 * @param argv Vector de punteros a cadenas de caracteres.
 * @return 0 si todo ha ido bien, distinto de 0 si hay error.
 */
int main(int argc, char * argv[])
{
    char f_verbose = 1;          // flag, 1: imprimir información extra
    struct addrinfo * servinfo;  // dirección propia (servidor)
    int sock;                    // descriptor del socket
    char msg[BUFF_SIZE];         // espacio para los datos recibidos
    ssize_t readbytes;           // número de bytes recibidos
    uint32_t num, netNum;        // vocales en formato local y de red
    struct sockaddr_storage caddr; // dirección del cliente (remitente)
    socklen_t clen;              // longitud de la dirección del cliente

    // verificación del número de parámetros:
    if (argc != 2)
    {
        printf("Número de parámetros incorrecto \n");
        printf("Uso: %s puerto\n", argv[0]);
        exit(1);
    }

    // obtiene estructura de dirección y crea el socket
    servinfo = obtener_struct_direccion(NULL, argv[1], f_verbose);
    sock = establecer_servicio(servinfo, f_verbose);

    freeaddrinfo(servinfo);
    servinfo = NULL;

    // bucle infinito para atender clientes uno tras otro
    while (1)
    {
        printf("\nEsperando datagramas (pulsa <Ctrl+c> para finalizar la ejecución)...\n");

        // recibe datagramas de un cliente hasta la marca de fin de transmisión
        num = 0;
        int activa = 1;
        while (activa)
        {
            clen = sizeof caddr;
            readbytes = recvfrom(sock, msg, BUFF_SIZE, 0,
                                 (struct sockaddr *)&caddr, &clen);
            if (readbytes < 0)
            {
                perror("Error de lectura en el socket (recvfrom)");
                exit(1);
            }

            // ¿es la marca de fin (un único byte con valor 4)?
            if (readbytes == 1 && msg[0] == fin)
            {
                activa = 0;
            }
            else
            {
                printf("Mensaje recibido del cliente: "); fflush(stdout);
                write(1, msg, readbytes);
                // evitamos printf por si lo recibido no es texto acabado en \0
                num += countVowels(msg, readbytes);
                printf("Vocales contadas hasta el momento: %u\n", num);
            }
        }

        // el remitente del datagrama de fin es el cliente: le respondemos
        printf("\nFin de transmisión. Cliente:\n");
        printsockaddr(&caddr);
        printf("Contadas %u vocales\n", num);

        netNum = htonl(num); // formato de red
        if (sendto(sock, &netNum, sizeof netNum, 0,
                   (struct sockaddr *)&caddr, clen) < 0)
        {
            perror("Error de escritura en el socket (sendto)");
            exit(1);
        }
        if (f_verbose) printf("Enviado número de vocales contadas al cliente\n");
    }

    // código inalcanzable
    close(sock);
    exit(0);
}
