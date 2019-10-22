include mjuego.asm

.data
;====================Ini Var Globales=============================
	salidaJuego 	word 	0
	

	LimiteIzquierdo =	6d  				;margen Izquierdo
	LimiteDerecho	=	311d				;margen derecho
	LimiteSuperior	=	21d					;margen superior
	LimiteInferior	=	187d				;margen inferior

	estado 			word 	1d 				;estado de direccion de la pelota
	direccion 		word 	0d
	posicion 		word 	0d
	posBarra 		word	0d


	prueba 			db 'esto es una prueba',13,10,'$'
;====================Fin Var Globales=============================

.code
;====================Ini Conversiones=============================
	tolineal proc
        ;--------------------------------------------------------------------;
        ;   Recibe:      DS:[bp+4]  col                          		     ;
        ;                DS:[bp+6]  fila                                     ;
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
		;				 CX=Columna                      
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
				cmp di,61114d
				jne Segunda
			;fin


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
				cmp di,61114d
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
        ;   Comentarios: Cambia de posicion de la barra				                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo.
        	push bp                    	;almacenamos el puntero base
        	mov  bp,sp               	;ebp contiene la direccion de esp
        	sub  sp,4					;Guardamos espacio para dos variables locales
        	push ax
        	push bx
        ;fin Surutina prologo

        ;Ini Codigo--
        	mov word ptr[bp-2],30				;Numero de Columnas
        	mov word ptr[bp-4],4				;Numero de Filas
        	xor bx,bx
        	xor ax,ax

        	D1:
        		mov es:[di+bx],dl
        		cmp bx,word ptr[bp-2]			;[bp-2] Columnas
        		je D2
        		inc bx
        		jmp D1
        	D2:
        		cmp ax,word ptr[bp-4]		   	;[bp-4] Filas
        		je FIN
        		xor bx,bx
        		inc ax
        		add di,320d
        		jmp D1


        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
            	pop bx
            	pop ax
            	mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
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

	mover proc 
		;--------------------------------------------------------------------
        ;   Recibe:    	 AX = estado                                       
        ;   Devuelve:    Nada	                                              
        ;   Comentarios: Avanza una posicion	
        ;				 Dependiendo el valor del estado(Variable global)
        ;				 1 = NorEste
		; 				 2 = NorOeste
		;				 3 = SurOeste
		;				 4 = SurEste				                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
        ;fin Surutina prologo

        ;Ini Codigo--
        	cmp ax,1
        	je NorEste
        	cmp ax,2
        	je NorOeste
        	cmp ax,3
        	je SurOeste
        	cmp ax,4
        	je SurEste

        	NorEste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				sub bx,319
				mov posicion[0],bx
				mpintarPelota bx, 2
				jmp FIN
			;fin accion

			SurEste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				add bx,321
				mov posicion[0],bx
				mpintarPelota bx, 2
				jmp FIN
			;fin

			NorOeste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				sub bx,321
				mov posicion[0],bx
				mpintarPelota bx, 2
				jmp FIN
			;fin 

			SurOeste:
				mpintarPelota bx, 0 ;(i,j) = (110,160) = 110*320 + 160
				add bx,319
				mov posicion[0],bx
				mpintarPelota bx, 2
				jmp FIN
			;fin
        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo
	mover endp
;====================Fin Conversiones=============================

;====================Ini Loop======================================
	
	game proc
		BUCLE:
			mov ax,salidaJuego[0]
			cmp ax,1
			je FIN
				mInstrucciones
			jmp Bucle
		FIN:
			ret
	game endp

	avanzaPelota proc
	    ;--------------------------------------------------------------------
        ;   Recibe:      bx = posicion                          		                                  
        ;   Devuelve:    Nada				                                 
        ;                                                                    
        ;   Comentarios: Cambia el 		                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
        	push ax
        	push bx
        
        ;ini Subrutina prologo

        ;Ini Codigo--
        	mov bx,posicion[0]
        	mov ax,estado[0]

        	cmp ax,1
        	je NorEste
        	cmp ax,2
        	je NorOeste
        	cmp ax,3
        	je SurOeste
        	cmp ax,4
        	je SurEste


			NorEste:
				mMover
				mgetxy bx
				cmp ax,LimiteSuperior					;¿fila = limite Superior?
				je EstadoSurEste
				cmp cx,LimiteDerecho					;Columna = limite Derecho?
				je EstadoNorOeste
				jmp FIN
			;fin accion

			SurEste:
				mMover
				mgetxy bx
				cmp ax,LimiteInferior					;¿fila = limite inferior?
				je EstadoNoreste				
				cmp cx,LimiteDerecho					;Columna = limite Derecho?	
				je EstadoSurOeste

				jmp FIN
			;fin

			NorOeste:
				mMover
				mgetxy bx
				cmp ax,LimiteSuperior					;¿fila = limite Superior?
				je EstadoSurOeste
				cmp cx,LimiteIzquierdo					;¿Columna = limite Izquierdo?
				je EstadoNorEste
				jmp FIN
			;fin 

			SurOeste:
				mMover
				mgetxy bx
				cmp ax,LimiteInferior					;¿fila = limite inferior?
				je EstadoNorOeste
				cmp cx,LimiteIzquierdo					;¿columna = limite izquierdo?
				je EstadoSurEste
				jmp FIN
			;fin


			EstadoSurEste:
				mov estado[0],4						;4=SurEste
				jmp FIN
			;fin
			EstadoNorEste:
				mov estado[0],1						;1=NorEste
				jmp FIN
			;fin
			EstadoNorOeste:
				mov estado[0],2						;2=NorOeste
				jmp FIN
			;fin
			EstadoSurOeste:
				mov estado[0],3						;3=SurOeste	
				jmp FIN
			;fin

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
            	pop bx
            	pop ax
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo
	avanzaPelota endp

    moverBarra proc
        ;--------------------------------------------------------------------
        ;   Recibe:      bx = posicion                                                                    
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Cambia el                       
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push ax
            push bx
        
        ;ini Subrutina prologo

        ;Ini Codigo--
            call listening
            cmp al,04dh                 ;derehcha
            je moverDerecha
            cmp al,04bh                 ;izquierda
            je moverIzquierda
            jmp FIN


           

            moverDerecha:
                mov bx,posBarra[0]
                mgetxy bx 
                add cx,29
                cmp cx,LimiteDerecho
                je FIN

                mPintarBarra bx,0
                add bx,6
                mPintarBarra bx,6
                mov posBarra[0],bx
                jmp FIN
            ;fin
            moverIzquierda:
                mov bx,posBarra[0]
                mgetxy bx
                cmp cx, 6
                je FIN


                mPintarBarra bx,0
                sub bx,6
                mPintarBarra bx,6
                mov posBarra[0],bx
                jmp FIN
            ;fin



        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop bx
                pop ax
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo
    moverBarra endp
;====================Fin Loop======================================

;====================Ini Instrucciones======================================
	setup proc
	 	;--------------------------------------------------------------------
        ;   Recibe:      Nada                         		     
        ;                                                                    
        ;   Devuelve:    Nada				                                 
        ;                                                                    
        ;   Comentarios: Inicia el modo video y los valores inicales del juego					                 
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo
       		push bp                    ;almacenamos el puntero base
        	mov  bp,sp                 ;ebp contiene la direccion de esp
        ;Fin Subrutina prologo

        ;Ini Codigo--
        	ModoVideo
			mPintarMargen 5

			mtolineal 180,12
			mov posBarra[0],ax
			mPintarBarra ax,6

			mtolineal 175,48
			mov posicion[0],ax

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 
        ;fin Subrutina epilogo
	setup endp

	instrucciones proc
	    ;--------------------------------------------------------------------
        ;   Recibe:      Nada                         	                           
        ;   Devuelve:    Nada				                                   
        ;   Comentarios: Realiza instrucciones del juego					                 
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo
        	push bp                    ;almacenamos el puntero base
        	mov  bp,sp                 ;ebp contiene la direccion de esp
        ;Fin Subrutina prologo

        ;Ini Codigo--

        	mDelay 150
        	mAvanzaPelota
            mMoverBarra
        	


        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 
        ;fin Subrutina epilogo
	instrucciones endp
;====================Fin Instrucciones======================================

