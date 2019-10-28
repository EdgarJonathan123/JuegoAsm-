;====================Fin Conversiones====================
    mtolineal macro fila,col
        push fila
        push col
        call tolineal
    endm

    mgetxy macro posicion

        ;PrintReg posicion
        push posicion
        call getxy
    endm
;====================Fin Conversiones====================

;====================Ini Pantalla====================

    mPintarMargen macro color
        push dx
        mov dl,color
        call pintarMargen
        pop dx
    endm


    mpintarPelota macro pos, color
        push di 
        push dx

        mov di,pos
        mov dl,color
        call pintarPelota

        pop dx
        pop di
    endm

    mPintarBarra macro pos,color
        push di 
        push dx
        push ax
        push bx

        mov di,pos
        mov dl,color
        mov ax,anchoBarra
        mov bx,alturaBarra
        call pintarBarra

        pop bx
        pop ax
        pop dx
        pop di
    endm


    mPintarObstaculo macro pos,color,alto,ancho
        push di 
        push dx
        push ax
        push bx

        mov di,pos
        mov dl,color
        mov ax,ancho
        mov bx,alto
        call pintarBarra

        pop bx
        pop ax
        pop dx
        pop di
    endm




    mavanzaPelota macro pos,state
        push offset state
        push offset pos
        call avanzaPelota
    endm


    mMovimiento macro 
        call movimiento
    endm 


    Print_VideoString macro cadena , pagina , fila  , columna

      push      dx
      push      ax
      push      cx
      
      mov       ah, 2                           ; modo de escritura con el puntero en modo video 
      mov       bh, pagina                      ; numero de pagina 
      mov       dh, fila                        ; numero de fila 
      mov       dl, columna                     ; numero columna 
      int       10h                             ; ejecucion de la interrupcion 

      mov       dx, offset cadena               ; tamañ de la cadena 
      mov       ax, dx
      mov       cl, 0ah
      mul       cl
      mov       ah, 00h
      add       ax, dx
      mov       dx, ax

      mov       ah, 09h
      int       21h

      pop       cx
      pop       ax
      pop       dx

    endm



    imprimir macro 
        mov dh, 1   ; posicion y en pantalla
        mov dl, 35   ; posicion x en pantalla
        mov ah, 02h
        int 10h
        mov     al, 'A' ;char a dibujar
        mov     ah, 09h
        mov     bl, 6 ; attribute color.
        mov     cx, 1   ; solo un char.
        int     10h
    endm
;====================Ini Pantalla====================

;====================Ini Juego====================
    mSetup macro
        call setup
    endm

    mGame macro
        call game
    endm

    mInstrucciones macro 
        call Instrucciones
    endm

    mMover macro pos,state
        push state
        push pos
        call mover
    endm

    mMoverBarra macro 
        call moverBarra
    endm

    mColisionBarra macro pos, state
        push offset state
        push offset pos 
        call ColisionBarra
    endm


    mGenerarObstaculo macro pos,color
        push pos
        push color
        call GenerarObstaculo
    endm

    mPintarNivel macro 
        call pintarNivel
    endm

    mDeleteBlock macro pos
        push pos
        call deleteBlock
    endm


    mDeleteDerecha macro pos
        push pos
        call DeleteDerecha
    endm


    mDeleteIzquierda macro pos
        push pos
        call DeleteIzquierda
    endm


    mgestionObstaculo macro pos,state
        push offset state
        push offset pos
        call gestionObstaculo
    endm
;====================Fin Juego====================