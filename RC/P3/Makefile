# DEFINICIÓN DE VARIABLES Y CONSTANTES
# Compilador de c: gcc
CC=gcc
# -Wall, -Wextra, -Wshadow: activan avisos de compilación
# -g: información de depuración para GDB
CFLAGS = -Wall -Wextra -Wshadow -g

# OBJETIVOS
all: clientevocalesUDP servidorvocalesUDP

# $@: objetivo (clientevocalesUDP / servidorvocalesUDP)
# $^: dependencias (archivos .o)
clientevocalesUDP: clientevocalesUDP.o comun.o
	$(CC) $(CFLAGS) -o $@ $^

servidorvocalesUDP: servidorvocalesUDP.o comun.o
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar cualquier .c en un .o
# %: comodín para el nombre del archivo
# $<: primera dependencia (el archivo .c)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Objetivo para comprimir los fuentes y generar el fichero a entregar
tarea:
	tar cvzf "vocalesUDP_${LOGNAME}.tar.gz" *.c *.h ?akefile

# Objetivo para limpiar: borra objetos, binarios y el paquete de entrega
# El prefijo @ hace que no se imprima el comando, únicamente el resultado
clean:
	@echo "Limpiando ficheros objeto y binarios ..."
	-rm -f *.o clientevocalesUDP servidorvocalesUDP "vocalesUDP_${LOGNAME}.tar.gz"

# Objetivos que no son archivos físicos
.PHONY: all clean tarea
