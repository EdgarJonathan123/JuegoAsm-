;================================================================================
;En la clase anterior pintamos pixeles usando la interrupción 10h servicio 0Ch; 
;podríamos pensar que estamos mandando la instrucción de pintar un pixel directamente 
;a la tarjeta de video. Sin embargo, lo que realmente estamos haciendo es escribir al 
;área de memoria de gráficos que inicia en A000:0000.
;
;Esta área consta de 320x200 bytes (64,000 bytes) y cada byte corresponde a un pixel. 
;Para cada byte del área de memoria de gráficos, la tarjeta de video lee el byte y usa 
;ese byte como índice en la paleta de colores para obtener el color del pixel.
;
;En la pantalla, el pixel superior-izquierdo (fila 0, columna 0) corresponde al byte en 
;la dirección A000:0000, el pixel superior-derecho (fila 0, columna 319) corresponde a A000:013F, 
;el primer pixel de la segunda fila (fila 1, columna 0) está mapeado a la dirección A000:0140. 
;En general, el pixel en la fila i, columna j corresponde a A000:(140h*i+j).
;
;La siguiente imagen muestra cómo interactuamos con el área de memoria y la paleta de colores; 
;la tarjeta de video usa esta información para desplegar el contenido de la pantalla.

;================================================================================
ModoVideo macro
mov ah,00h
mov al,13h
int 10h
mov ax, 0A000h
mov ds, ax  ; DS = A000h (memoria de graficos).
endm

ModoTexto macro
mov ah,00h
mov al,03h
int 10h
endm

;-------------DELAY 1 PARA QUE SEA VISIBLE
Delay macro constante
LOCAL D1,D2,Fin
push si
push di

mov si,constante
D1:
dec si
jz Fin
mov di,constante
D2:
dec di
jnz D2
jmp D1

Fin:
pop di
pop si
endm

;mov [di],30h

PintarMargen macro color,tx



mov dl, color
push tx

call paint

mov ax, 0A000h
mov ds, ax  ; DS = A000h (memoria de graficos).


endm

;------------------------
;
;
;
;
;
;------------------------

;--------------OBTENER CARACTER DE CONSOLA CON ECHO A PANTALLA----------------------
getChar macro
mov ah,0dh
int 21h
mov ah,01h
int 21h
endm

   	iniciarDs macro 
        mov ax,@data        ;pasamos la direccion de data a ax
        mov ds,ax           ;Inicializa DS
    endm

;--------------MACRO IMPRESION DE CADENA---------------------------
print macro cadena
push ax
push dx
mov ax,@data
mov ds,ax
mov ah,09
mov dx,offset cadena
int 21h
pop dx
pop ax
endm

pintarPelota macro pos, color
push dx
mov di,pos
mov dl,color

mov [di],dl
mov [di+1], dl
mov [di+2], dl

mov [di+320], dl
mov [di+321], dl
mov [di+322], dl

mov [di+640], dl
mov [di+641], dl
mov [di+643], dl

pop dx
endm



.model small
;-------------------SEGMENTO DE PILA--------------------------
.stack
;-------------------SEGMENTO DE DATO--------------------------
.data
	;----------------------------MENSAJES---------------------------------------------------
	salt db 0ah,0dh, '	','$'
	;ENCABEZADO
	enc0 db 0ah,0dh, '	UNIVERSIDAD DE SAN CARLOS DE GUATEMALA',0ah,0dh,'	FACULTAD DE INGENIERIA', 0ah,0dh, '	ESCUELA DE CIENCIAS Y SISTEMAS',0ah,0dh, '	ARQUITECTURA DE COMPUTADORES Y ENSAMBLADORES 1 A',0ah,0dh, '	SEGUNDO SEMESTRE 2019',0ah,0dh, '	OSCAR RENE CUELLAR MANCILLA',0ah,0dh, '	201503712',0ah,0dh, '	EJEMPLO MODO VIDEO','$'
	;MENU PRINCIPAL
	enc1 db 0ah,0dh, '	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%',0ah,0dh,'	%%%%%%% MENU PRINCIPAL %%%%%%%',0ah,0dh,'	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%',0ah,0dh,'	%%%% 1. VIDEO             %%%%',0ah,0dh,'	%%%% 2. IMPRIMIR          %%%%',0ah,0dh,'	%%%% 3. SALIR             %%%%',0ah,0dh,'	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%','$'

	topex word  61114d

	lol word 25d
;-------------------SEGMENTO DE CODIGO------------------------
.code
main proc

	MenuPrincipal:
		;--------MOSTRANDO EL MENU PRINCIPAL--------------------------
		print enc0
		print enc1
		print salt
		;--------OBTENIENDO EL NUMERO ESCOGIDO------------------------
		getChar
		cmp al,'1'; COMPARO CON EL ASCII DEL NUMERO 1 QUE ES 49 Y EN HEXA 31H
		je Video1
		cmp al,'3'
		je Salir
		jmp MenuPrincipal

	Video1:
		ModoVideo
		PintarMargen 5,topex[0]

		mov dx,35360

		Accion:
			pintarPelota dx, 0 ;(i,j) = (110,160) = 110*320 + 160
			sub dx,319
			pintarPelota dx, 2
			;Delay 200
			;getChar
			call escucha
			cmp al,'l'
			je TES
			jmp Accion

			;getChar
		 TES:
			ModoTexto
		jmp MenuPrincipal
;---------------------METODO PARA FINALIZAR EL PROGRAMA-----------------------------
	Salir:
		mov ah, 4ch
		mov al, 00h
		int 21h
main endp ;Termina proceso


	escucha proc
		mov ah,06h
		mov dl,0ffh
		int 21h
		;ZF=1 no hay entrada activa
		;AL guarda el caracter 
		ret
	escucha endp


	paint proc
	    ;--------------------------------------------------------------------;
        ;   Recibe:      DS:[bp+4]  Variable Global                          ;
        ;                                                                    ;
        ;   Devuelve:    Solo afecta las cadenas enviadas                    ;
        ;                                                                    ;
        ;   Comentarios: Se utiliza la variable global para prueba xd        ;
        ;--------------------------------------------------------------------;

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
        ;fin Surutina prologo

        ;Ini Codigo--
            
            mov ax,DS:[bp+4]              ;di = direccion inicio token1
            
;empieza en pixel (i,j) = (20,0) = 20*320+0 = 6400
;barra horizontal superior
mov di,6405
Primera:
mov [di],dl
inc di
cmp di,6714
jne Primera

;barra horizontal inferior
;empieza en pixel (i,j) = (190,0) = 190 * 320 + 0 = 60800
mov di,60805
Segunda:
mov [di],dl
inc di
cmp di, 61114
jne Segunda


mov ax,@data        ;pasamos la direccion de data a ax
mov ds,ax           ;Inicializa DS

mov ax,25d
cmp lol[0],ax
je FIN

;barra vertical izquierda
mov di, 6405
Tercera:
mov [di], dl
add di,320
cmp di,60805
jne Tercera

;barra vertical derecha
mov di,6714
Cuarta:
mov [di], dl
add di,320
cmp di,61114
jne Cuarta





        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 2
            ;fin etiqueta
        ;fin Subrutina epilogo

	paint endp
	
end main