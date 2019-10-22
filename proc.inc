
.code 
	listening proc
		mov ah,06h
		mov dl,0ffh
		int 21h
		;ZF=1 no hay entrada activa
		;AL guarda el caracter 
		ret
	listening endp

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

	
