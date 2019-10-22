;====================Fin Conversiones====================
    mtolineal macro fila,col
        push fila
        push col
        call tolineal
    endm

    mgetxy macro posicion
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

        mov di,pos
        mov dl,color
        call pintarBarra

        pop dx
        pop di
    endm



    mavanzaPelota macro 
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

    mMover macro 
        call mover
    endm

    mMoverBarra macro 
        call moverBarra
    endm

   ;mColisionBarra macro
   ;    call ColisionBarra
   ;endm
;====================Fin Juego====================