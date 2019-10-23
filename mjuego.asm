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
;====================Fin Juego====================