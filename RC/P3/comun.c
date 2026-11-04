/**
 * @file comun.c
 *
 * Funciones comunes para trabajar con estructuras de direcciones.
 * Version UDP: se solicita un socket de datagramas (SOCK_DGRAM) y, dado que
 * la practica solo evalua IPv4, se pide la familia AF_INET para evitar que
 * cliente y servidor queden en familias distintas (IPv4/IPv6) y no puedan
 * intercambiar mensajes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include "comun.h"

/**
 * Imprime una estructura *sockaddr_in* o *sockaddr_in6* almacenada en
 * *sockaddr_storage*.
 *
 * @param saddr Estructura de dirección a imprimir.
 */
void printsockaddr(struct sockaddr_storage * saddr)
{
    struct sockaddr_in *saddr_ipv4;  // puntero a estructura de dirección IPv4
    struct sockaddr_in6 *saddr_ipv6; // puntero a estructura de dirección IPv6
    void *addr;                      // puntero a dirección (IPv4 o IPv6)
    char ipstr[INET6_ADDRSTRLEN];    // string para la dirección en texto
    int port;                        // número de puerto

    if (saddr == NULL)
    {
        printf("La dirección está vacía\n");
    }
    else
    {
        printf("\tFamilia de direcciones: ");
        fflush(stdout);
        if (saddr->ss_family == AF_INET6)
        {   // IPv6
            printf("IPv6\n");
            saddr_ipv6 = (struct sockaddr_in6 *)saddr;
            addr = &(saddr_ipv6->sin6_addr);
            port = ntohs(saddr_ipv6->sin6_port);
        }
        else if (saddr->ss_family == AF_INET)
        {   // IPv4
            printf("IPv4\n");
            saddr_ipv4 = (struct sockaddr_in *)saddr;
            addr = &(saddr_ipv4->sin_addr);
            port = ntohs(saddr_ipv4->sin_port);
        }
        else
        {
            fprintf(stderr, "familia desconocida\n");
            exit(1);
        }
        inet_ntop(saddr->ss_family, addr, ipstr, sizeof ipstr);
        printf("\tDirección (interpretada según familia): %s\n", ipstr);
        printf("\tPuerto (formato local): %d\n", port);
    }
}


/**
 * Devuelve un puntero a una estructura de direcciones rellenada con direcciones
 * que cumplan los parámetros especificados (UDP/IPv4).
 *
 * @param dir_servidor Nombre/IP del equipo destino. NULL si es el equipo local.
 * @param servicio     Servicio/puerto a solicitar.
 * @param f_verbose    Si es distinto de 0, se muestra información extra.
 * @return Puntero a la estructura de direcciones creada en memoria dinámica.
 */
struct addrinfo* obtener_struct_direccion(char *dir_servidor, char *servicio, char f_verbose)
{
    struct addrinfo hints,     // Variable para especificar la solicitud
                    *servinfo, // Puntero para respuesta de getaddrinfo()
                    *direccion;// Puntero para recorrer la lista de direcciones
    int status;     // Finalización correcta o no de la llamada getaddrinfo()
    int numdir = 1; // Contador de estructuras de direcciones

    // sobreescribimos con ceros la estructura
    memset(&hints, 0, sizeof hints);

    if (f_verbose)
    {
        printf("1 - Especificando detalles de la estructura de direcciones a solicitar... \n");
        fflush(stdout);
    }

    // IPv4 (la practica solo evalua IPv4)
    hints.ai_family = AF_INET;

    if (f_verbose)
    {
        printf("\tFamilia de direcciones/protocolos: ");
        switch (hints.ai_family)
        {
            case AF_UNSPEC: printf("IPv4 e IPv6\n"); break;
            case AF_INET:   printf("IPv4\n"); break;
            case AF_INET6:  printf("IPv6\n"); break;
            default:        printf("No IP (%d)\n", hints.ai_family); break;
        }
        fflush(stdout);
    }

    // UDP: socket de datagramas
    hints.ai_socktype = SOCK_DGRAM;

    if (f_verbose)
    {
        printf("\tTipo de comunicación: ");
        switch (hints.ai_socktype)
        {
            case SOCK_STREAM: printf("flujo (TCP)\n"); break;
            case SOCK_DGRAM:  printf("datagrama (UDP)\n"); break;
            default:          printf("no convencional (%d)\n", hints.ai_socktype); break;
        }
        fflush(stdout);
    }

    if (dir_servidor != NULL)
    {
        // somos el cliente: nos comunicaremos con dir_servidor
        if (f_verbose) printf("\tNombre/dirección del equipo: %s\n", dir_servidor);
    }
    else
    {
        // somos el servidor: la IP se rellena para hacer bind
        if (f_verbose) printf("\tNombre/dirección: equipo local\n");
        hints.ai_flags = AI_PASSIVE;
    }
    if (f_verbose) printf("\tServicio/puerto: %s\n", servicio);

    if (f_verbose)
    {
        printf("2 - Solicitando la estructura de direcciones con getaddrinfo()... ");
        fflush(stdout);
    }
    status = getaddrinfo(dir_servidor, servicio, &hints, &servinfo);
    if (status != 0)
    {
        fprintf(stderr,"Error en la llamada getaddrinfo(): %s\n", gai_strerror(status));
        exit(1);
    }
    if (f_verbose) printf("hecho\n");

    if (f_verbose)
    {
        printf("3 - Analizando estructura de direcciones devuelta... \n");
        direccion = servinfo;
        while (direccion != NULL)
        {
            printf("    Dirección %d:\n", numdir);
            printsockaddr((struct sockaddr_storage*) direccion->ai_addr);
            direccion = direccion->ai_next;
            numdir++;
        }
    }

    return servinfo;
}
