/**
 * @file clientevocalesUDP.c
 *
 * Programa *clientevocalesUDP* que envía cadenas de texto a un servidor.
 *
 * Uso: clientevocalesUDP servidor puerto
 *
 * El programa crea un socket UDP y envía cadenas de caracteres al servidor y
 * puerto especificado hasta llegar a fin de fichero (Control+d para provocarlo
 * desde la entrada estándar). Como en UDP no hay conexión, el fin de los envíos
 * se marca enviando un único byte con el valor 4.
 * Finalmente, espera como respuesta el número total de vocales en las
 * cadenas enviadas e imprime dicho valor por pantalla.
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
 * Función que crea el socket.
 *
 * @param servinfo Estructura de dirección del servidor.
 * @param f_verbose Flag.
 * @return Descriptor de socket.
 */
int initsocket(struct addrinfo *servinfo, char f_verbose)
{
    int sock;

    // crea un extremo de la comunicación y devuelve un descriptor
    if (f_verbose)
    {
        printf("Creando el socket (socket)... ");
        fflush(stdout);
    }
    sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sock < 0)
    {
        perror("Error en la llamada socket: No se pudo crear el socket");
        // muestra por pantalla el valor de la cadena suministrada por el
        // programador, dos puntos y un mensaje de error que detalla la
        // causa del error cometido
        exit(1);
    }
    if (f_verbose) printf("hecho\n");

    return sock;
}

/**
 * Programa principal
 *
 * @param argc Número de argumentos usados en la línea de comandos.
 * @param argv Vector de punteros a cadenas de caracteres. argv[0]
 *             apunta al nombre del programa, argv[1] al primer
 *             argumento y así sucesivamente.
 * @return 0 si todo ha ido bien, distinto de 0 si hay error.
 */
int main(int argc, char * argv[])
{
    // declaración de variables propias del programa principal (locales a main)
    char f_verbose = 1;         // flag, 1: imprimir información extra
    struct addrinfo * servinfo; // puntero a estructura de dirección destino
    int sock;                   // descriptor del socket
    char msg[MAX_BUFF_SIZE];    // buffer donde almacenar datos para enviar
    ssize_t len,       // número de bytes leídos por la entrada estándar
            sentbytes, recvbytes;
                       // número de bytes enviados/recibidos por el socket
                       // (size_t con signo)
    uint32_t num;      // variable donde anotar el número de vocales
    struct sockaddr_storage servaddr;
    socklen_t servaddrlen;

    // verificación del número de parámetros:
    if (argc != 3)
    {
        printf("Número de parámetros incorrecto \n");
        printf("Uso: %s servidor puerto/servicio\n", argv[0]);
        exit(1); // finaliza el programa indicando salida incorrecta (1)
    }

    // obtiene estructura de dirección
    servinfo = obtener_struct_direccion(argv[1], argv[2], f_verbose);

    // crea un extremo de la comunicación con la primera de las
    // direcciones de servinfo. Devuelve el descriptor del socket
    sock = initsocket(servinfo, f_verbose);

    servaddrlen = servinfo->ai_addrlen;
    memcpy(&servaddr, servinfo->ai_addr, servinfo->ai_addrlen);

    // hay que liberar la memoria dinámica usada para la dirección
    // cuando ya no se necesite
    freeaddrinfo(servinfo);
    servinfo = NULL;
    // como ya se ha liberado ese bloque de memoria,
    // dejamos de apuntarlo para evitar acceder a ella por error.
    // Si referenciamos esta variable el programa abortará con
    // ERROR: SEGMENTATION FAULT

    // bucle que lee texto del teclado y lo envía al servidor
    printf("\nTeclea el texto a enviar y pulsa <Enter>, o termina con <Ctrl+d>\n");
    while ((len = read(0, msg, MAX_BUFF_SIZE)) > 0)
    {
        // read lee del descriptor 0 (entrada estándar, por defecto el teclado)
        // hasta que se pulsa INTRO,
        // almacena en msg la cadena leída y
        // devuelve la longitud de los datos leídos, en bytes
        if (f_verbose) printf("  Leídos %zd bytes\n", len);

        // envía datos al socket
        if ((sentbytes = sendto(sock, msg, len, 0, (struct sockaddr *)&servaddr, servaddrlen)) < 0)
        {
            perror("Error de escritura en el socket (sendto)");
            exit(1);
        }
        else
        {
            if (f_verbose) printf("  Enviados %zd bytes al servidor\n",sentbytes);
        }

        printf("Teclea el texto a enviar y pulsa <Enter>, o termina con <Ctrl+d>\n");
    }

    if (f_verbose)
    {
        printf("Enviando marca de fin de transmisión...");
        fflush(stdout);
    }
    if (sendto(sock, &fin, 1, 0, (struct sockaddr *)&servaddr, servaddrlen) < 0)
    {
        perror("Error al enviar la marca de fin de transmisión (sendto)");
        exit(1);
    }

    if (f_verbose)
    {
        printf("hecho\nEsperando respuesta del servidor...");
        fflush(stdout);
    }

    // recibe del servidor el número de vocales recibidas:
    recvbytes = recvfrom(sock, &num, sizeof num, 0, NULL, NULL);
    if (recvbytes != (ssize_t) sizeof num)
    {
        printf("Recibidos %zd bytes en lugar de los %zu esperados", recvbytes, sizeof num);
        exit(1);
    }
    printf(" %zu bytes\n", sizeof num);
    printf("Todo el texto enviado contenía en total %u vocales\n", ntohl(num));
    // convierte el entero largo sin signo de formato de red a formato de host

    // cierra la conexión del socket
    if (close(sock) < 0)
    {
        perror("Error al cerrar el socket (close)");
        exit(1);
    }
    else
    {
        if (f_verbose) printf("Socket cerrado\n");
    }

    exit(0); // finaliza el programa indicando salida correcta (0)
}
