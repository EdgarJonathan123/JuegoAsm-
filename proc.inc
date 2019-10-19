
.code 
	escucha proc
		mov ah,06h
		mov dl,0ffh
		int 21h
		;ZF=1 no hay entrada activa
		;AL guarda el caracter 
		ret
	escucha endp

	tolineal proc
        ;--------------------------------------------------------------------;
        ;   Recibe:      DS:[bp+4]  posy                          		     ;
        ;                DS:[bp+6]  posx                                     ;
        ;                                                                    ;
        ;   Devuelve:    AX=coordenada mapeada                               ;
        ;                                                                    ;
        ;   Comentarios: mapea coordenadas					                 ;
        ;--------------------------------------------------------------------;

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
			push bx
			push dx
			push cx
        ;fin Surutina prologo

        ;Ini Codigo--
            
            mov bx,[bp+4]              ;bx = posy
            mov ax,[bp+6]              ;ax = posx
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
		;				 BX=Columna                      
        ;                                                                    
        ;   Comentarios: Dada una posicion absoluta se determina 
		;				 la fila y columna				                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
			push dx
			push bx
        ;fin Surutina prologo

        ;Ini Codigo--
            mov dx,0				   	;limpiamos dividendo, superior
            mov ax,word ptr[bp+4]       ;ax = posicion absoluta, divendo inferior
            mov bx,320d					;divisor

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

	pintarMargen proc 
	    ;--------------------------------------------------------------------
        ;   Recibe:      dl = color                         		     
        ;                                                                    
        ;   Devuelve:    Nada                               
        ;                                                                    
        ;   Comentarios: Pinta un maren en modo grafico					                 
        ;--------------------------------------------------------------------


        ;Ini Codigo--
            
         	;empieza en pixel (i,j) = (20,0) = 20*320+0 = 6400
			;barra horizontal superior
			mov di,6405
			Primera:
				mov es:[di],dl
				inc di
				cmp di,6714 
				jne Primera
			;fin etiqueta

			;barra horizontal inferior
			;empieza en pixel (i,j) = (190,0) = 190 * 320 + 0 = 60800
			mov di,60805
			Segunda:
				mov es:[di],dl
				inc di
				cmp di, topex
				jne Segunda
			;fin

			mov ax,estado[0]
			cmp ax,5d
			je FIN

			;barra vertical izquierda
			mov di, 6405
			Tercera:
				mov es:[di], dl
				add di,320
				cmp di,60805
				jne Tercera
			;fin

			;barra vertical derecha
			mov di,6714
			Cuarta:
				mov es:[di], dl
				add di,320
				cmp di,topex
				jne Cuarta
			;fin

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo

	pintarMargen endp

	pintarBarra proc
		;--------------------------------------------------------------------
        ;   Recibe:       di  pos   
		;				  DL = color                                    
        ;                                                                    
        ;   Devuelve:    nada	                               
        ;                                                                    
        ;   Comentarios: Cambia de posicion la pelotita					                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
        ;fin Surutina prologo

        ;Ini Codigo--

			mov dl,9
			mtolineal 48,179
			mov di,ax
			mov bx,0

			bucle:
				cmp bx,7
				jmp Bucle1
				mov es:[di+bx],dl
				inc bx
				jmp bucle
			;fin 
			
			mtolineal 48,180
			mov di,ax
			mov bx,0

			bucle1:
				cmp bx,7
				jmp FIN
				mov es:[di+bx],dl
				inc bx
				jmp bucle1
			;fin bucle

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo
	pintarBarra endp

	pintarPelota proc
		;--------------------------------------------------------------------
        ;   Recibe:       di  pos   
		;				  DL = color                                    
        ;                                                                    
        ;   Devuelve:    nada	                               
        ;                                                                    
        ;   Comentarios: Cambia de posicion la pelotita					                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
        ;fin Surutina prologo

        ;Ini Codigo--
    		mov es:[di],dl
    		mov es:[di+1], dl
    		mov es:[di+2], dl

    		mov es:[di+320], dl
    		mov es:[di+321], dl
    		mov es:[di+322], dl

    		mov es:[di+640], dl
    		mov es:[di+641], dl
    		mov es:[di+642], dl

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo
	pintarPelota endp


	avanzaPelota proc
	    ;--------------------------------------------------------------------
        ;   Recibe:      DX = posicion                          		     
        ;                                                                    
        ;   Devuelve:    Nada				                                 
        ;                                                                    
        ;   Comentarios: Mueve la Pelotita por la pantalla					                 
        ;--------------------------------------------------------------------

        ;Ini Codigo--

			NorEste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				sub bx,319
				mpintarPelota bx, 2
					
					mgetxy bx

					cmp ax,21d					;¿fila = limite superior?
					je SurEste

					cmp cx,311					;columa = limite derecho?
					je NorOeste


				Delay 200
				jmp NorEste
			;fin accion

			SurEste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				add bx,321
				mpintarPelota bx, 2

					mgetxy bx

					cmp ax,187					;¿fila = limite infierior?
					je NorEste

					cmp cx,311					;columna = limite derecho?
					je SurOeste
		
				Delay 200
				jmp SurEste
			;fin

			NorOeste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				sub bx,321
				mpintarPelota bx, 2

					mgetxy bx

					cmp ax,21d					;¿fila = limite superior?
					je SurOeste

					cmp cx,6d					;¿columna = limite izquierdo?
					je NorEste

				Delay 200
				jmp NorOeste
			;fin 

			SurOeste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				add bx,319
				mpintarPelota bx, 2

					mgetxy bx

					cmp ax,187					;¿fila = limite inferior?
					je NorOeste

					cmp cx,6d					;¿columna = limite izquierdo?
					je SurEste

				Delay 200
				jmp SurOeste
			
			;fin

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
				ModoTexto
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo
	avanzaPelota endp