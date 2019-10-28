include mjuego.asm

.data
;====================Ini Var Globales=============================

    gameText db 'User1             N1     0      00:00:03','$'
    punteo  word 0


    ;Variables Boolenas
        TRUE        =   1d
        FALSE       =   2D


    ;Ini Global Sensor

            ;---;   ;---;
            ; 8 ;   ; 7 ;
        ;---;---;---;---;---;
        ; 1 ;           ; 6 ;
        ;---;           ;---;
            ;           ;
        ;---;           ;---;
        ; 2 ;           ; 5 ;
        ;---;---;---;---;---;
            ; 3 ;   ; 4 ;
            ;---;   ;---;

        Sensor1     =   1d              ;Se Usa  Sub pos,Sensor1
        Sensor2     =   639d            ;Se Usa  Add pos,Sensor2   
        Sensor3     =   960d            ;Se Usa  Add pos,Sensor3
        Sensor4     =   962d            ;Se Usa  Add pos,Sensor4
        Sensor5     =   643d            ;Se Usa  Add pos,Sensor5    
        Sensor6     =   3d              ;Se Usa  Add pos,Sensor6
        Sensor7     =   318d            ;Se Usa  Sub pos,Sensor7
        Sensor8     =   320d            ;Se Usa  Sub pos,Sensor8   
    ;Fin Global Sensor

    ;tamano obstaculos
    colObstaculo    =  50d
    filObstaculo    =   8d

    Retardo         =  180d

    ;Colores
    Negro           =   0d
    Azul            =   1d
    Verde           =   2d
    Cyan            =   3d
    Rojo            =   4d
    Magenta         =   5d
    Cafe            =   6d
    GrisClaro       =   7d
    Gris            =   8d
    AzulClaro       =   9d
    VerdeClaro      =   10d
    CyanClaro       =   11d
    RojoClaro       =   12d
    MagentaClaro    =   13d
    Amarillo        =   14d
    Blanco          =   15d

    ;Direcciones
    DirNorEste      =   1d
    DirNorOeste     =   2d
    DirSurOeste     =   3d
    DirSurEste      =   4d



    ;ESTADO DEL JUEGO
	salidaJuego 	word 	0
    terminoJuego    word    0
    pausa           word    0

    moises          db  'moi$'


    anchoBarra      = 30
    alturaBarra     = 3	


    ;variables PARA EL margen
	LimiteIzquierdo =	7d  				;margen Izquierdo
	LimiteDerecho	=	311d				;margen derecho
	LimiteSuperior	=	22d					;margen superior
	LimiteInferior	=	186d				;margen inferior


    posicion2       word    0d
    estado2         word    0d

    posicion1       word    0d
    estado1         word    1d

    posicion        word    0d
	estado 			word 	1d 				;estado de direccion de la pelota
    ;                1 = NorEste
    ;                2 = NorOeste
    ;                3 = SurOeste
    ;                4 = SurEste    



    ;NIVELES DEL jUEGO
    Nivel           word    1d              ;Nivel Actual del Juego
    cambioNivel     word    1d              ;Se activa para decir que hubo un cambio d


    ;Posiciones de los objetos
    ;direccion 		word 	0d
	posBarra 		word	0d
;====================Fin Var Globales=============================

.code
;====================Ini Conversiones=============================


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
        ;                 ax = anchoBarra
        ;                 bx = alturaBarra                                 
        ;                                                                    
        ;   Devuelve:    nada	                               
        ;                                                                    
        ;   Comentarios: Cambia de posicion de la barra				                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo.
        	push bp                    	;almacenamos el puntero base
        	mov  bp,sp               	;ebp contiene la direccion de esp
        	sub  sp,4					;Guardamos espacio para dos variables locales
        ;fin Surutina prologo

        ;Ini Codigo--
        	mov word ptr[bp-2],ax			;Numero de Columnas
        	mov word ptr[bp-4],bx			;Numero de Filas
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
        ;   Recibe:    	 [bp+4] = posicion 
        ;                [bp+6] = estado
        ;                                   
        ;   Devuelve:    Nada	                                              
        ;   Comentarios: Avanza una posicion	
        ;				 Dependiendo el valor del estado(Variable global)
        ;				 1 = NorEste
		; 				 2 = NorOeste
		;				 3 = SurOeste
		;				 4 = SurEste				                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp 
            mov bp,sp
            push ax
            push bx
            push di
        ;fin Surutina prologo

        ;Ini Codigo--
            mov bx,word ptr[bp+4]
            mov di,word ptr[bp+6]
        	cmp word ptr[di],1
        	je NorEste
        	cmp word ptr[di],2
        	je NorOeste
        	cmp word ptr[di],3
        	je SurOeste
        	cmp word ptr[di],4
        	je SurEste

        	NorEste:
				mpintarPelota [bx], 0 ;(i,j) = (110,160) = 110*320 + 160
                mov ax,[bx]
				sub ax,319
				mov word ptr[bx],ax
				mpintarPelota [bx], 2
				jmp FIN
			;fin accion

			SurEste:
				mpintarPelota [bx], 0 ;(i,j) = (110,160) = 110*320 + 160
                mov ax,[bx]
				add ax,321
				mov word ptr[bx],ax
				mpintarPelota [bx], 2
				jmp FIN
			;fin

			NorOeste:
				mpintarPelota [bx], 0 ;(i,j) = (110,160) = 110*320 + 160
                mov ax,[bx]
				sub ax,321
				mov word ptr[bx],ax
				mpintarPelota [bx], 2
				jmp FIN
			;fin 

			SurOeste:
				mpintarPelota [bx], 0 ;(i,j) = (110,160) = 110*320 + 160
                mov ax,[bx]
				add ax,319
				mov word ptr[bx],ax
				mpintarPelota [bx], 2
				jmp FIN
			;fin
        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop di
                pop bx
                pop ax
                mov sp,bp
                pop bp
                ret 4
            ;fin etiqueta
        ;fin Subrutina epilogo
	mover endp
;====================Fin Conversiones=============================

;====================Ini Loop======================================
	
	game proc

		BUCLE:

            EstadoJuego:
                cmp pausa[0],1
                je accionesPausa
                cmp terminoJuego[0],1
                je FIN
                jmp instruction
            ;Fin etiqueta

            accionesPausa:
                call listening
                cmp al,01bh                         ;se presiono esc
                je despausar
                cmp al,'1'
                je level1
                cmp al,'2'
                je level2
                cmp al,'3'
                je level3
                jmp Bucle
            ;Fin etiqueta

            level1:
                mov Nivel[0],1
                mov cambioNivel[0],1
                jmp despausar
            ;fin etiqueta

            level2:
                mov Nivel[0],2
                mov cambioNivel[0],1
                jmp despausar
            ;fin etiqueta

            level3: 
                mov Nivel[0],3
                mov cambioNivel[0],1
                jmp despausar
            ;fin etiqueta

            despausar:
                mov pausa[0],0                      ;Se quito la pausa
                jmp Bucle
            ;fin etiqueta


            instruction:
				mInstrucciones
            ;Fin etiqueta 


			jmp Bucle
        ;fin etiqueta


		FIN:
            ;printReg terminoJuego[0]
			ret
	game endp

	avanzaPelota proc
	    ;--------------------------------------------------------------------
        ;   Recibe:      [bp+4] = posicion    
        ;                [bp+6] = estado                  		                                  
        ;   Devuelve:    Nada				                                 
        ;                                                                    
        ;   Comentarios: Cambia la posicion de la pelotita 		                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp 
            mov bp,sp
        	push ax
        	push bx
            push di
        
        ;ini Subrutina prologo

        ;Ini Codigo--

            ;mov bx,terminoJuego[0]
            ;cmp bx,1                                    ;¿terminoJuego = true?
            ;je FIN

        	mov bx,word ptr[bp+4]
        	mov di,word ptr[bp+6]
            
        	cmp word ptr[di],1
        	je NorEste
        	cmp word ptr[di],2
        	je NorOeste
        	cmp word ptr[di],3
        	je SurOeste
        	cmp word ptr[di],4
        	je SurEste


			NorEste:
				mMover bx,di
				mgetxy [bx]
				cmp ax,LimiteSuperior					;¿fila = limite Superior?
				je EstadoSurEste

           
				cmp cx,LimiteDerecho					;Columna = limite Derecho?
				je EstadoNorOeste
				jmp FIN
			;fin accion

			SurEste:
				mMover bx,di
				mgetxy [bx]
				cmp ax,LimiteInferior					;¿fila = limite inferior?
				je perder				
				cmp cx,LimiteDerecho					;Columna = limite Derecho?	
				je EstadoSurOeste

				jmp FIN
			;fin

			NorOeste:
				mMover bx,di
				mgetxy [bx]
				cmp ax,LimiteSuperior					;¿fila = limite Superior?
				je EstadoSurOeste
				cmp cx,LimiteIzquierdo					;¿Columna = limite Izquierdo?
				je EstadoNorEste
				jmp FIN
			;fin 

			SurOeste:
				mMover bx,di
				mgetxy [bx]
				cmp ax,LimiteInferior					;¿fila = limite inferior?
				je perder
				cmp cx,LimiteIzquierdo					;¿columna = limite izquierdo?
				je EstadoSurEste
				jmp FIN
			;fin

			EstadoSurEste:
				mov word ptr[di],4						;4=SurEste
				jmp FIN
			;fin
			EstadoNorEste:
				mov word ptr[di],1						;1=NorEste
				jmp FIN
			;fin
			EstadoNorOeste:
				mov word ptr[di],2						;2=NorOeste
				jmp FIN
			;fin
			EstadoSurOeste:
				mov word ptr[di],3						;3=SurOeste	
				jmp FIN
			;fin


            perder:
                mpintarPelota word ptr[bp+4],0
                mov terminoJuego[0],1

                jmp FIN
            ;fin
        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop di
            	pop bx
            	pop ax
                mov sp,bp
                pop bp
                ret 4
            ;fin etiqueta
        ;fin Subrutina epilogo
	avanzaPelota endp

    moverBarra proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                                  
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Se lee si se presiono una tecla
        ;                si se presiono se mueve la barrita                       
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
            cmp al,01bh
            je pausar
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


            pausar:
                mov pausa[0],1                          ;1=pausa del juego
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

    colisionBarra proc 
        ;--------------------------------------------------------------------
        ;   Recibe:      [bp+4] = pos
        ;                [bp+6] = estado
        ;                                                                  
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: se varifica una colision con la barrita
        ;                si colisiona se cambia la direccion                   
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp
            mov  bp,sp
            pusha
        ;ini Subrutina prologo

        ;Ini Codigo--
            mov si,word ptr[bp+4]               ;si=direccion de posicion
            mov di,word ptr[bp+6]               ;di=direccion de estado

            verficaPosicion:
                mov bx,[si]                     ;bx= posicion Pelotita
                add bx,960
                mov ax,posBarra[0]              ;posicion inicial Barra
                mov cx,anchoBarra               ;25 columnas
                add cx,ax                       ;cx=cx+ax= posicion final barra

                cmp bx,ax                       ;¿posicion pelotita es menor que posicion inicial barra?
                jb FIN            ;si: no hace nada 
                cmp bx,cx                       ;¿posicion pelotita es mayor que posicion Final barra?
                ja FIN            ;si: no hace nada


                mov ax,[di]                     ;ax= estado
                cmp ax,3                        ;estado=SurOeste
                je EstadoNorOeste
                cmp ax,4                        ;estado=SurEste
                je EstadoNorEste

                jmp FIN
           ;Fin de etiqueta

           EstadoNorEste:
                mov ax,DirNorEste
                mov word ptr[di],ax                 
                jmp FIN
           ;fin etiqueta

           EstadoNorOeste:
                mov ax,DirNorOeste
                mov word ptr[di],ax                 
                jmp FIN
           ;fin etiqueta

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                popa
                mov sp,bp
                pop bp
                ret 4
            ;fin etiqueta
        ;fin Subrutina epilogo
    colisionBarra endp


    gestionObstaculo proc
        ;--------------------------------------------------------------------
        ;   Recibe:      [bp+4] = pos
        ;                [bp+6] = estado
        ;                                                                  
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Gestiona si la pelotita choca con los Obstaculos              
        ;--------------------------------------------------------------------
        ;ini Subrutina proglogo
            push bp
            mov  bp,sp
            pusha
        ;ini Subrutina prologo

        ;Ini Codigo--
            mov si,word ptr[bp+4]               ;si=direccion de posicion
            mov di,word ptr[bp+6]               ;di=direccion de estado


            VerificaEstado:
                mov ax,DirNorEste
                cmp [di],ax
                je VerificaNorESTE

                mov ax,DirNorOeste
                cmp [di],ax
                je VerificaNorOeste

                mov ax,DirSurOeste
                cmp [di],ax
                je VerificaSurOeste

                mov ax,DirSurEste
                cmp [di],ax
                je VerificaSurEste
            ;Fin Etiqueta

            VerificaNorEste:
                ;---;   ;---;
                ; 8 ;   ; 7 ;
                ;---;---;---;---;
                ;   ____    ; 6 ;
                ;      /|   ;---;
                ;     / |   ;
                ;    /      ;---;
                ;   /       ; 5 ;
                ;-----------;---;


                ;Para la etiqueta 8 de la figura
                mov bx,[si]
                mov ax,Sensor8
                sub bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoSurEste

                ;Para la etiqueta 7 de la figura
                mov bx,[si]   
                mov ax,Sensor7
                sub bx,ax                  
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoSurEste

                ;Para la etiqueta 6 de la figura
                mov bx,[si]
                mov ax,Sensor6
                add bx,ax                        
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoNorOeste

                ;Para la etiqueta 5 de la figura
                mov bx,[si]
                mov ax,Sensor5
                add bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoNorOeste

                jmp FIN
            ;fIN etiqueta

            VerificaNorOeste:
                    ;---;   ;---;
                    ; 8 ;   ; 7 ;
                ;---;---;---;---;
                ; 1 ;           ;
                ;---;           ;
                    ;           ;
                ;---;           ;
                ; 2 ;           ; 
                ;---;-----------;

                ;Para la etiqueta 7 de la figura
                mov bx,[si]
                mov ax,Sensor7
                sub bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoSurOeste

                ;Para la etiqueta 8 de la figura
                mov bx,[si]   
                mov ax,Sensor8
                sub bx,ax                  
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoSurOeste

                ;Para la etiqueta 1 de la figura
                mov bx,[si]
                mov ax,Sensor1
                sub bx,ax                        
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoNorEste

                ;Para la etiqueta 2 de la figura
                mov bx,[si]
                mov ax,Sensor2
                add bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoNorEste

                jmp FIN
            ;fin etiqueta

            VerificaSurEste:
                ;-----------;---;
                ;           ; 6 ;
                ;           ;---;
                ;           ;
                ;           ;---;
                ;           ; 5 ;
                ;---;---;---;---;
                ; 3 ;   ; 4 ;
                ;---;   ;---;

                ;Para la etiqueta 3 de la figura
                mov bx,[si]
                mov ax,Sensor3
                add bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoNorEste

                ;Para la etiqueta 4 de la figura
                mov bx,[si]   
                mov ax,Sensor4
                add bx,ax                  
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoNorEste

                ;Para la etiqueta 5 de la figura
                mov bx,[si]
                mov ax,Sensor5
                add bx,ax                        
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoSurOeste

                ;Para la etiqueta 6 de la figura
                mov bx,[si]
                mov ax,Sensor6
                add bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoSurOeste

                jmp FIN
            ;fin etiqueta

            VerificaSurOeste:
                ;---;-----------;
                ; 1 ;           ;
                ;---;      /    ;
                    ;     /     ;
                ;---;  | /      ;
                ; 2 ;  |/___    ;
                ;---;---;---;---;
                    ; 3 ;   ; 4 ;
                    ;---;   ;---;


                ;Para la etiqueta 1 de la figura
                mov bx,[si]
                mov ax,Sensor1
                sub bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoSurEste

                ;Para la etiqueta 2 de la figura
                mov bx,[si]   
                mov ax,Sensor2
                add bx,ax                  
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoSurEste

                ;Para la etiqueta 3 de la figura
                mov bx,[si]
                mov ax,Sensor3
                add bx,ax                        
                mov al,es:[bx]
                cmp al,Cyan                    
                je EstadoNorOeste

                ;Para la etiqueta 4 de la figura
                mov bx,[si]
                mov ax,Sensor4
                add bx,ax                      
                mov al,es:[bx]
                cmp al,Cyan                     
                je EstadoNorOeste

                jmp FIN
            ;fin etiqueta
   

            EstadoNorEste:
                call aumentaPunto
                mDeleteBlock bx
                mov ax,DirNorEste
                mov word ptr[di],ax                 
                jmp FIN
           ;fin etiqueta

           EstadoNorOeste:
                call aumentaPunto
                mDeleteBlock bx
                mov ax,DirNorOeste
                mov word ptr[di],ax                 
                jmp FIN
           ;fin etiqueta

           EstadoSurEste:
                call aumentaPunto
                mDeleteBlock bx
                mov ax,DirSurEste
                mov word ptr[di],ax                 
                jmp FIN
           ;Fin Etiqueta

           EstadoSurOeste:
                call aumentaPunto
                mDeleteBlock bx
                mov ax,DirSurOeste
                mov word ptr[di],ax                 
                jmp FIN
           ;Fin Etiqueta
          

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                popa
                mov sp,bp
                pop bp
                ret 4
            ;fin etiqueta
        ;fin Subrutina epilogo

    gestionObstaculo endp

    deleteBlock proc
        ;--------------------------------------------------------------------
        ;   Recibe:      [bp+4] = posicion actual 
        ;                                                                  
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Elimina el blocke dado un Color                 
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp
            mov  bp,sp
            pusha
        ;ini Subrutina prologo

        ;Ini Codigo--
           xor ax,ax
           mov si,word ptr[bp+4]               ;si=Posicion absoluta Actual
           mov di,word ptr[bp+6]               ;di=Posicion Color A Eliminar
       
           mov bx,si                           ;bx=iterador,si=valor fijo
           ;mov cx,9

           C1: 
                mov al,es:[bx]
                cmp al,Negro
                je reiniciar

                mDeleteDerecha bx
                mDeleteIzquierda bx

                sub bx,320
                jmp C1
                ;loop C1
           ;Fin etiqueta 

            reiniciar:;
                mov bx,si                           ;bx=iterador,si=valor fijo

           C2: 
                add bx,320

                mov al,es:[bx]
                cmp al,Negro
                je FIN

                mDeleteDerecha bx
                mDeleteIzquierda bx

                
                jmp C2
                ;loop C2
           ;Fin etiqueta 

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                popa
                mov sp,bp
                pop bp
                ret 2
            ;fin etiqueta
        ;fin Subrutina epilogo
    deleteBlock endp


    aumentaPunto proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                       
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Aumenta el punteo de jugador               
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
        ;ini Subrutina prologo

        ;Ini Codigo--
            inc punteo
            Ascii punteo 
            mSetCursor 0,25
            print Num
        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                ret 
            ;fin etiqueta
        ;fin Subrutina epilogo 
    aumentaPunto endp

    deleteDerecha proc
        ;--------------------------------------------------------------------
        ;   Recibe:      [bp+4] = Posicion Actual
        ;                                                                  
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Elimina hacia la derecha                  
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp
            mov  bp,sp
            pusha
        ;ini Subrutina prologo

        ;Ini Codigo--
                mov si,word ptr[bp+4]               ;si=Posicion absoluta Actual
                mov di,word ptr[bp+6]               ;di=Posicion Color A Eliminar
            
                mov bx,si                           ;bx=iterador,si=valor fijo

            C1:                
                mov al,es:[bx]
                cmp al,Negro
                je FIN

                mov al,Negro
                mov es:[bx],al

                inc bx                
                jmp C1
            ;fin
        ;Fin Codigo--


        ;ini Subrutina epilogo
            FIN:
                popa
                mov sp,bp
                pop bp
                ret 2
            ;fin etiqueta
        ;fin Subrutina epilogo
    deleteDerecha endp

    deleteIzquierda proc
        ;--------------------------------------------------------------------
        ;   Recibe:      [bp+4] = Posicion Actual
        ;                                                                  
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Elimina hacia la izquierda                  
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp
            mov  bp,sp
            pusha
        ;ini Subrutina prologo

        ;Ini Codigo--
                mov si,word ptr[bp+4]               ;si=Posicion absoluta Actual
                mov di,word ptr[bp+6]               ;di=Posicion Color A Eliminar
            
                mov bx,si                           ;bx=iterador,si=valor fijo
                dec bx 

            C1:
                mov al,es:[bx]
                cmp al,Negro
                je FIN

                mov al,Negro
                mov es:[bx],al

                dec bx                 
                jmp C1
            ;fin
        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                popa
                mov sp,bp
                pop bp
                ret 2
            ;fin etiqueta
        ;fin Subrutina epilogo
    deleteIzquierda endp



    GenerarObstaculo proc
        ;--------------------------------------------------------------------
        ;   Recibe:      [bp+4] Color                                                                  
        ;   Devuelve:    [bp+6] Posicion Incial                                        
        ;                                                                    
        ;   Comentarios: Se pintan los obstaculos del primer Nivel             
        ;--------------------------------------------------------------------

        ;ini Subrutina proglogo
            push bp                    ;almacenamos el puntero base
            mov  bp,sp                 ;ebp contiene la direccion de esp
            push ax
            push dx
            push bx
            push cx
        ;ini Subrutina prologo

        ;Ini Codigo--
            mov dx,4                              ;Numero de Rectanculos
            mov cx,0

            mov bx,25                           ;posicion Incial
            Bucle:
                mtolineal [bp+6],bx
                mPintarObstaculo ax,[bp+4],filObstaculo,colObstaculo

                cmp cx,dx                            ;dx=Numero De bloques para hacer
                je FIN

                inc cx

                add bx,colObstaculo
                add bx,4
                jmp Bucle
            ;fin etiqueta

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop cx
                pop bx
                pop dx
                pop ax
                mov sp,bp               ;esp vuelve apuntar al inicio y elimina las variables locales
                pop bp                  ;restaura el valor del puntro base listo para el ret
                ret 4
            ;fin etiqueta
        ;fin Subrutina epilogo
    GenerarObstaculo endp
;====================Fin Loop======================================

;====================Ini Niveles===================================

    pintarNivel1 proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                 
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Pinta los bloques del primer Nivel                                 
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo
        ;Fin Subrutina prologo

        ;Ini Codigo--
            mov bx,25
            mGenerarObstaculo bx,Cyan  
            add bx,13   
            mGenerarObstaculo bx,Cyan      
            add bx,13   
            mGenerarObstaculo bx,Cyan  

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                ret 
        ;fin Subrutina epilogo
    pintarNivel1 endp

    pintarNivel2 proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                 
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Pinta los bloques del Segundo Nivel                                 
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo
            push bx
        ;Fin Subrutina prologo

        ;Ini Codigo--

            mov bx,25
            mGenerarObstaculo bx,Cyan   
            add bx,13   
            mGenerarObstaculo bx,Cyan 
            add bx,13   
            mGenerarObstaculo bx,Cyan   
            add bx,13   
            mGenerarObstaculo bx,Cyan  
            add bx,13   
            mGenerarObstaculo bx,Cyan      

        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop bx
                ret 
        ;fin Subrutina epilogo
    pintarNivel2 endp

    pintarNivel3 proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                 
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Pinta los bloques del Segundo Nivel                                 
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo
            push bx
        ;Fin Subrutina prologo

        ;Ini Codigo--

            mov bx,25
            mGenerarObstaculo bx,Cyan  
            add bx,13   
            mGenerarObstaculo bx,Cyan
            add bx,13   
            mGenerarObstaculo bx,Cyan
            add bx,13   
            mGenerarObstaculo bx,Cyan     
            add bx,13   
            mGenerarObstaculo bx,Cyan
        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                pop bx
                ret 
        ;fin Subrutina epilogo
    pintarNivel3 endp

    pintarNivel proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                 
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Pinta el Nivel Segun la variable Global (Nivel)                                 
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo

        ;Fin Subrutina prologo


        ;Ini Codigo

            cmp cambioNivel[0],1
            je  CambiarNivel
            jmp FIN


            CambiarNivel:
                cmp Nivel[0],1
                je level1
                cmp Nivel[0],2
                je level2
                cmp Nivel[0],3
                je level3
                jmp FIN
            ;fin etiqueta

            level1:
                call pintarNivel1
                mov cambioNivel[0],0
                jmp FIN
            ;Fin Juego

            level2:
                mWrite<'Level2'>
                call pintarNivel2
                mov cambioNivel[0],0
                jmp FIN
            ;fin etiqueta

            level3:
                call pintarNivel3
                mov cambioNivel[0],0
                jmp FIN
            ;fin etiqueta
        ;Fin Codigo


        ;ini Subrutina epilogo
            FIN:
                ret 
        ;fin Subrutina epilogo
    pintarNivel endp

    controlNiveles proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                 
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Pinta el Nivel Segun la variable Global (Nivel)                                 
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo

        ;Fin Subrutina prologo


        ;Ini Codigo
            level:
                cmp Nivel[0],1
                je level1
                cmp Nivel[0],2
                je level2
                cmp Nivel[0],3
                je level3
                jmp FIN
            ;fin etiqueta

            level1:
                mDelay 180 
                mAvanzaPelota posicion,estado
                mColisionBarra posicion,estado
                mgestionObstaculo posicion,estado
                jmp FIN
            ;Fin Juego

            level2:
                mDelay 150
                mAvanzaPelota posicion,estado
                mColisionBarra posicion,estado
                mgestionObstaculo posicion,estado
                

                mAvanzaPelota posicion1,estado1
                mColisionBarra posicion1,estado1
                mgestionObstaculo posicion1,estado1
                jmp FIN
            ;fin etiqueta

            level3:
                mDelay 108
                mAvanzaPelota posicion,estado
                mColisionBarra posicion,estado
                mgestionObstaculo posicion,estado
                

                mAvanzaPelota posicion1,estado1
                mColisionBarra posicion1,estado1
                mgestionObstaculo posicion1,estado1
               
                mAvanzaPelota posicion2,estado2
                mColisionBarra posicion2,estado2
                mgestionObstaculo posicion2,estado2
                jmp FIN
            ;fin etiqueta
        ;Fin Codigo


        ;ini Subrutina epilogo
            FIN:
                ret 
        ;fin Subrutina epilogo
    controlNiveles endp
;====================Fin Niveles===================================

;====================Ini Instrucciones=============================
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
			mPintarMargen MagentaClaro

            print gameText

			mov Nivel[0],1
            mov cambioNivel[0],1
            mPintarNivel

    


            mtolineal 180,12
            mov posBarra[0],ax
            mPintarBarra ax,Rojo


            mov estado[0],1                 ;Se inicia en NorEste
			mtolineal 150,60
			mov posicion[0],ax              ;define la posicion inical de la pelotita


            mov estado1[0],2                 ;Se inicia en NorEste
            mtolineal 150,60
            mov posicion1[0],ax              ;define la posicion inical de la pelotita
           
            mov estado2[0],2                 ;Se inicia en NorEste
            mtolineal 120,100
            mov posicion2[0],ax              ;define la posicion inical de la pelotita

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
        ;Fin Subrutina prologo

        ;Ini Codigo--

    
                mPintarNivel 
                call controlNiveles
                mMoverBarra
                
                jmp FIN
        ;Fin Codigo--

        ;ini Subrutina epilogo
            FIN:
                ret 
        ;fin Subrutina epilogo
	instrucciones endp
;====================Fin Instrucciones=============================