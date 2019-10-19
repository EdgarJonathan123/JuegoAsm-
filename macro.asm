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
iniciarDs macro 
        mov ax,@data        ;pasamos la direccion de data a ax
        mov ds,ax           ;Inicializa DS
endm


ModoVideo macro
    mov ah,00h
    mov al,13h
    int 10h
    mov ax, 0A000h
    mov es, ax  ; es = A000h (memoria de graficos).
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

mPintarMargen macro color
    mov dl, color
    call pintarMargen
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

mpintarPelota macro pos, color
    mov di,pos
    mov dl,color
    call pintarPelota
endm

mtolineal macro posx,posy
    push posx
    push posy
    call tolineal
endm


mgetxy macro posicion
    push posicion
    call getxy
endm




movmiento macro 
    call avanzaPelota
endm