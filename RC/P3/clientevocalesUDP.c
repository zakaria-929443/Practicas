/**
 * @file clientevocalesUDP.c
 *
 * Programa *clientevocalesUDP* que envía cadenas de texto a un servidor por UDP.
 *
 * Uso: clientevocalesUDP servidor puerto
 *
 * Crea un socket UDP y envía al servidor cadenas leídas de la entrada estándar
 * hasta llegar a fin de fichero (Ctrl+d). Como en UDP no hay conexión, el fin
 * de los envíos se marca enviando un único byte con el valor 4 (EOT). Después
 * espera como respuesta el número total de vocales y lo imprime por pantalla.
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
#define MAX_BUFF_SIZE 1000 ///< Tamaño del buffer para las cadenas de texto.

const char fin = 4; // carácter ASCII end of transmission (EOT)

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
    struct addrinfo * servinfo;  // puntero a estructura de dirección destino
    int sock;                    // descriptor del socket
    char msg[MAX_BUFF_SIZE];     // buffer donde almacenar datos para enviar
    ssize_t len, sentbytes, recvbytes;
    uint32_t num;                // número de vocales recibido

    // dirección del servidor: en UDP la necesitamos en cada sendto()
    struct sockaddr_storage servaddr;
    socklen_t servaddrlen;

    // verificación del número de parámetros:
    if (argc != 3)
    {
        printf("Número de parámetros incorrecto \n");
        printf("Uso: %s servidor puerto/servicio\n", argv[0]);
        exit(1);
    }

    // obtiene estructura de dirección (UDP / IPv4)
    servinfo = obtener_struct_direccion(argv[1], argv[2], f_verbose);

    // En UDP no hay conexión: elegimos la primera dirección devuelta para el
    // servidor y creamos un socket de datagramas.
    if (f_verbose) { printf("Creando el socket (socket)... "); fflush(stdout); }
    sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sock < 0)
    {
        perror("Error en la llamada socket: No se pudo crear el socket");
        exit(1);
    }
    if (f_verbose) printf("hecho\n");

    // guardamos la dirección del servidor para usarla en cada sendto()
    servaddrlen = servinfo->ai_addrlen;
    memcpy(&servaddr, servinfo->ai_addr, servinfo->ai_addrlen);

    // ya podemos liberar la estructura de direcciones
    freeaddrinfo(servinfo);
    servinfo = NULL;

    // bucle que lee texto del teclado y lo envía al servidor
    printf("\nTeclea el texto a enviar y pulsa <Enter>, o termina con <Ctrl+d>\n");
    while ((len = read(0, msg, MAX_BUFF_SIZE)) > 0)
    {
        if (f_verbose) printf("  Leídos %zd bytes\n", len);

        // envía el datagrama al servidor
        sentbytes = sendto(sock, msg, len, 0,
                           (struct sockaddr *)&servaddr, servaddrlen);
        if (sentbytes < 0)
        {
            perror("Error de escritura en el socket (sendto)");
            exit(1);
        }
        if (f_verbose) printf("  Enviados %zd bytes al servidor\n", sentbytes);

        printf("Teclea el texto a enviar y pulsa <Enter>, o termina con <Ctrl+d>\n");
    }

    // fin de la entrada: enviamos la marca de fin de transmisión (byte EOT = 4)
    if (f_verbose) { printf("Enviando marca de fin de transmisión..."); fflush(stdout); }
    if (sendto(sock, &fin, 1, 0, (struct sockaddr *)&servaddr, servaddrlen) < 0)
    {
        perror("Error al enviar la marca de fin (sendto)");
        exit(1);
    }

    if (f_verbose) { printf("hecho\nEsperando respuesta del servidor..."); fflush(stdout); }

    // recibimos el número de vocales (no nos interesa el remitente: NULL, NULL)
    recvbytes = recvfrom(sock, &num, sizeof num, 0, NULL, NULL);
    if (recvbytes != (ssize_t) sizeof num)
    {
        printf("Recibidos %zd bytes en lugar de los %zu esperados\n",
               recvbytes, sizeof num);
        exit(1);
    }
    printf(" %zu bytes\n", sizeof num);
    printf("Todo el texto enviado contenía en total %u vocales\n", ntohl(num));

    // cierra el socket
    if (close(sock) < 0)
    {
        perror("Error al cerrar el socket (close)");
        exit(1);
    }
    if (f_verbose) printf("Socket cerrado\n");

    exit(0);
}
