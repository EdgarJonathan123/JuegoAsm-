
   	iniciarDs macro 
        mov ax,@data        ;pasamos la direccion de data a ax
        mov ds,ax           ;Inicializa DS
    endm

    
    print macro cadena 
	 	push dx
	    mov dx, offset cadena 
        call WriteString
		pop dx
    endm

    mWrite macro texto
        ;Ejemplo llamada
        ;mWrite <13,10,'Esto es un texto alv',13,10>
        LOCAL cadena
        .data
            cadena byte texto,0
        .code
            push dx
            mov dx, offset cadena
            call WriteString
            pop dx
    endm


.data 
     var db 'probando el ensamblaje xd',0
.code

    Str_length proc
        ;--------------------------------------------------------------------;
        ;   Recibe:     DS:[bp+4] apunta al arreglo                          ;
        ;                                                                    ;
        ;   Devuelve:   AX= tamanio de la cadena de entrada.                 ;
        ;                                                                    ;
        ;   Comentarios:Se detiene cuando se encuentra (0dh)en el arreglo.   ;
        ;--------------------------------------------------------------------;

        ;Subrutina proglogo
        push bp                    ;almacenamos el puntero base
        mov  bp,sp                 ;ebp contiene la direccion de esp
        push di                    ;guarda edi para no perder el valor al salir

        ;Ini Codigo--
            mov di,[bp+4]    ;guarda Parametro1 en edi
            xor ax,ax                 ;eax=0

            L1:
                cmp byte PTR[di],0      ;¿final de cadena?
                je  L2                  ;si: termina
                inc di                  ;no: apunta al siguiente
                inc ax                  ;suma 1 a la cuenta
                jmp L1

        ;Fin Codigo--

        L2:
            ;Subrutina epilogo
            pop di                  ;obtenemos el valor devuelta
            mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
            pop bp                  ;restaura el valor del puntro base listo para el ret
            ret 2
    Str_length endp

    WriteString proc
        ;--------------------------------------------------------------------;
        ;   Recibe:      DS:DX apunta a la cadena                            ;
        ;                                                                    ;
        ;   Devuelve:    Nada.                                               ;
        ;                                                                    ;
        ;   Comentarios: Recibe una cadena con terminacion nula y            ;
        ;                lo imprime en la salida estandar                    ;
        ;--------------------------------------------------------------------;

        ;Subrutina proglogo
        pusha
        push ds                         ;ES=DS
        pop  es

        ;Ini Codigo--
            push dx                         ;Enviamos parameter1
            call Str_length                 ;EAX = longitud de la cadena
            mov cx,ax                       ;ECX = numero de bytes
            mov ah,40h                      ;Escribe al archivo o dispositivo
            mov bx,1                        ;manejador de salida estandar
            int 21h                         ;llamada a ms-dos
        ;Fin Codigo--

        ;Subrutina epilogo
        popa
        ret
    WriteString endp

