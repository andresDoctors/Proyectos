# XV6 Grupo N°24
## Integrantes
 - Ariel Agustin Alvaro `ariel.alvaro@mi.unc.edu.ar`
 - Andres David Doctors `andresdaviddoctors@mi.unc.edu.ar`
 - Nicolas Alejandro Greiff `alejandro.greiff@mi.unc.edu.ar`
## Introduccion
En este laboratorio el objetivo fue familiarizarse con la programación en codigo de xv6, conectar el "espacio de usuario" y "espacio kernel" a través de syscalls para que interactuen y nos permitan hacer cosas como cambiar del modo texto al modo grafico y pintar en este ultimo. Para realizar el trabajo utilizamos numeracion en decimal, binaria y hexadecimal. Además de la manipulación de registros, accesos a la memoria y entender sobre puertos I/O. Las partes mas visibles del trabajo son la leyenda de "SO2021" abajo a la derecha cuando debugueamos y el programa de usuario que genera el dibujo de un personaje del juego "among us".

## Modularizacion 
Seguimos una modularizacion que donde tenemos por un lado el modeswitch en console como debe, y plotpixel como procedimiento nuevo en proc.c 
## Tecnicas de programacion
> Librerias Destacables
En este caso XV6 trae un par de funciones implementadas pero que no son poco importantes y sirvieron para el desarrollo de nuestros programas 
>>defs.h <-- Nos proporciona una suficiente cantidad de funciones que ayudaron pero la mas importante argint, la cual toma los argumentos de la syscall como enteros
>>user.h <-- Para la creacion de programas de usuario y toma de argumentos sirvió mucho la funcion atoi, la cual sirve para pasar de un argumento de string a integer.

El estilo de código que proporcionamos consta de nombre de variables simples y concretos según el caso, las funciones están escritas en minusculas para distinguirlas de macros y constantes si es que hubiese y separadas por guiones bajo en el caso que lo necesite, líneas con longitudes cortas que permite leer con facilidad el código y comentarios no triviales que ayudan a la compresión del mismo. Para la memoria dinámica usamos la variable Calloc que nos permite tener un buen manejo del tamaño de la memoria. El código es robusto, por lo tanto al mínimo error obtenemos una respuesta clara sobre el error

## Herramientas de programación
Como siempre usamos editores de texto para el desarrollo del código (Visual Studio, Notepad++,etc), para la compilación de estos la cátedra nos proporciona MakeFiles para compilar atraves de gcc (GNU Compiler Collection). Para el debugging utilizamos impresiones por pantalla de las variables y GDB(GNU debugger), como emulabamos en QEMU debimos debugear kernel y llamarlo de manera remota en otra terminal para debugearlo de manera exitosa.

## Desarrollo 
- Parte 1: 
La parte 1 fue la mas sencilla de este laboratorio ya que era solo mapear la dirección virtual de 4 coordenadas exactamente en el modo texto ->S02021
- parte 2:  
Esta parte llevo un poco de investigación para encontrar los registros que permitían cambiar a modo texto y modo grafico, pero una vez encontrados lo único que hacia falta eran setear los registros, en esta parte al no ser una syscall, la pudimos testear llamandola al inicio de la consola y comprobando que efectivamente cambiaba de modo
- parte 3:  
Syscall -> Al principio nos costo ver como definir una syscall, ya que había que definir nuestra syscall en diversos archivos, no fue tan simple pero gracias a que xv6 tiene sus syscalls la cual logramos ver llamando al comando ls en la consola y de a poco analizando como estaban declaradas en los distintos archivos (por ejemplo kill) logramos ver como crear ese programa de usuario que llama a nuestra syscall y con la funcion argint obtener sus argumentos (en este caso enteros). el modeswitch recibe un argumento entero ( 0(modo grafico)/1(modo texto) ) y plotpixel recibe 3 (x/y/color),la implementación de plotpixel era bastante sencilla, pero en un momento no nos percatamos de que estabamos queriendo mapear la memoria fisica en vez de la virtual, por lo que teniamos que usar P2V (como dice el enunciado), luego de eso funciono correctamente.
-parte 4:
En la parte 4, a la hora de pensar como hacer el dibujo pensamos en la estrategia de dividirlo en 2 bloques y de ahí agregarle mas bloques que cumplan la función del contorno que definen la forma del cuerpo, el visor y la mochila.



