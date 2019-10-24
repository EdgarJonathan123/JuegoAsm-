
.code 
	listening proc
		mov ah,06h
		mov dl,0ffh
		int 21h
		;ZF=1 no hay entrada activa
		;AL guarda el caracter 
		ret
	listening endp

    tolineal proc
        ;--------------------------------------------------------------------;
        ;   Recibe:      DS:[bp+4]  col                                      ;
        ;                DS:[bp+6]  fila                                     ;
        ;                                                                    ;
        ;   Devuelve:    AX=coordenada mapeada                               ;
        ;                                                                    ;
        ;   Comentarios: mapea coordenadas                                   ;
        ;--------------------------------------------------------------------;

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
            push bx
            push dx
            push cx
        ;fin Surutina prologo

        ;Ini Codigo--
            
            mov bx,[bp+4]              ;bx = col
            mov ax,[bp+6]              ;ax = fila
            mov cx,320d
            mul cx
            add ax,bx

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop cx
                pop dx
                pop bx
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 4
            ;fin etiqueta
        ;fin Subrutina epilogo
    tolineal endp

    getxy proc  
        ;--------------------------------------------------------------------
        ;   Recibe:      DS:[bp+4]  posicion absoluta                                
        ;                                                                    
        ;   Devuelve:    AX=Fila     
        ;                CX=Columna                      
        ;                                                                    
        ;   Comentarios: Dada una posicion absoluta se determina 
        ;                la fila y columna                               
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
            push dx
            push bx
        ;fin Surutina prologo

        ;Ini Codigo--
            mov dx,0                    ;limpiamos dividendo, superior
            mov ax,word ptr[bp+4]       ;ax = posicion absoluta, divendo inferior
            mov bx,320d                 ;divisor

            div bx
            mov cx,dx

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop bx
                pop dx
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 2
            ;fin etiqueta
        ;fin Subrutina epilogo
    getxy endp

	delay proc 
		;--------------------------------------------------------------------
        ;   Recibe:      AX = constante                          		     
        ;                                                                    
        ;   Devuelve:    Nada			                                     
        ;                                                                    
        ;   Comentarios: provoca un retardo hipergemetrico por software				 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
    		push si
    		push di
        ;fin Surutina prologo

        ;Ini Codigo--
            
            mov si,ax					;constante
    		D1:
        		dec si
       	 		jz Fin
        		mov di,ax				;constante
    		D2:
        		dec di
        		jnz D2
        		jmp D1
        ;Fin Codigo--

        ;ini Subrutina epilogo
            Fin:
        		pop di
        		pop si
				ret
            ;fin etiqueta
        ;fin Subrutina epilogo
	delay endp

	Str_length proc
        ;--------------------------------------------------------------------;
        ;   Recibe:     DS:[bp+4] apunta al arreglo                          ;
        ;                                                                    ;
        ;   Devuelve:   AX= tamanio de la cadena de entrada.                 ;
        ;                                                                    ;
        ;   Comentarios:Se detiene cuando se encuentra ('$')en el arreglo.   ;
        ;--------------------------------------------------------------------;

        ;Subrutina proglogo
        push bp                    ;almacenamos el puntero base
        mov  bp,sp                 ;ebp contiene la direccion de esp
        push di                    ;guarda edi para no perder el valor al salir

        ;Ini Codigo--
            mov di,[bp+4]    ;guarda Parametro1 en edi
            xor ax,ax                 ;eax=0

            L1:
                cmp byte PTR[di],'$'    ;¿final de cadena?
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
        ;   Recibe:      [bp+4] apunta a la cadena                           ;
        ;                                                                    ;
        ;   Devuelve:    Nada.                                               ;
        ;                                                                    ;
        ;   Comentarios: Recibe una cadena con terminacion nula y            ;
        ;                lo imprime en la salida estandar                    ;
        ;--------------------------------------------------------------------;

        ;Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
            pusha
        ;Ini Codigo--
            mov ah,09
            mov dx,word ptr[bp+4]
            int 21h
        ;Fin Codigo--

        ;Subrutina epilogo
            popa
            mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
            pop bp                  ;restaura el valor del puntro base listo para el ret
        ret 2
    WriteString endp

    toAscii proc
        ;--------------------------------------------------------------------
        ;   Recibe:      AX = Numero decimal                                                
        ;                                                                    
        ;   Devuelve:    Num = llena a num con el numero     
        ;                                                                    
        ;   Comentarios: Separa el numero en digitos y pone  lso digitos en un arreglo                    
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
            sub  sp,2                  ;se guarda espacio para dos variables
            mov word ptr[bp-2],0       ;var local =0 
            pusha
        ;fin Subrutina prologo

        ;Ini Codigo--
            push offset Num                    ;enviando un parametro
            call Clear_String                  ;limpiamos el arreglo
            xor si,si                          ;si=0

            cmp ax,0                           ;si ax, ya viene con un cero
            je casoMinimo
            
            mov  bx,0                          ;denota el fin de la cadena
            push bx                            ;se pone en la pila el fin de cadena

            Bucle:  
                mov dx,0
                cmp ax,0                    ;¿AX= 0?
                je toNum                    ;si:enviar numero al arreglo
                
                mov bx,10                   ;divisor  = 10
                div bx                      ;ax =cociente ,dx= residuo

                add dx,48d                   ;residuo +48 para  poner el numero en ascii

                push dx                     ;lo metemos en la pila 

                jmp Bucle
            ;fin etiqueta

            toNum:
                pop bx                      ;obtenemos elemento de la pila

                mov word ptr[bp-2],bx       ; pasamos de 16 bits a 8 bits 
                mov al, byte ptr[bp-2]


                cmp al,0                    ;¿Fin de Numero?
                je FIN                      ;si: enviar al fin de l procedimiento

                mov num[si],al              ;ponemos el numero en ascii en la cadena
                inc si                      ;incrementamos los valores               
                jmp toNum                   ;iteramos de nuevo 

            ;fin etiqueta

            
            casoMinimo:
                add al,48d                         ;convertimos 0 ascii
                mov Num[si],al                     ;Lo pasamos a num

                jmp FIN
            ;fin


        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                popa
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 
            ;fin etiqueta
        ;fin Subrutna epilogo
    toAscii endp

    Clear_String proc
        ;--------------------------------------------------------------------;
        ;   Recibe:      DS:[bp+4] cadena                                    ;
        ;                                                                    ;
        ;   Devuelve:    nada                                                ;
        ;                                                                    ;
        ;   Comentarios: Limpia la cadena dada.                              ;
        ;--------------------------------------------------------------------;

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
            push di                    ;guardamos di porque se utilizara
            push ax                    ;guardamos ax porque se utilizara
        ;fin Subrutina prologo

        ;Ini Codigo--
            mov di,[bp+4]             ;guarda Parametro1 en di
            xor ax,ax                 ;ax=0

            L1:
                cmp byte PTR[di],'$'      ;¿final de cadena?
                je  FIN                 ;si: termina
  
                mov byte ptr[di],'$'      ;suma 1 a la cuenta
                inc di                  ;no: apunta al siguiente
                jmp L1
            ;fin etiqueta

        ;Fin Codigo--


        ;ini Subrutina epilogo
            FIN:
                pop ax                  ;obtenemos ax despues de su uso
                pop di                  ;obtenemos di despues de su uso
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 2
            ;fin etiqueta
        ;fin Subrutna epilogo
    Clear_String endp

    ResetCursor proc
        push ax
        push bx
        push dx

        mov ah , 02H        ;MOVE CURSOR TO CENTER OF SCREEN
        mov bh , 0          ;pagina 
        mov dh , 1          ;ROW
        mov dl , 1          ;COL
        int 10h

        FIN:
            pop dx
            pop bx
            pop ax
            ret
    ResetCursor endp