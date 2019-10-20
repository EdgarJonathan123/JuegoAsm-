;====================Fin Conversiones====================
    mtolineal macro posx,posy
        push posx
        push posy
        call tolineal
    endm


    mgetxy macro posicion
        push posicion
        call getxy
    endm
;====================Fin Conversiones====================

;====================Ini Pantalla====================

    mPintarMargen macro color
        mov dl, color
        call pintarMargen
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


    mAvanzaPelota macro 
        call avanzaPelota
    endm

    mMover macro 
        call mover
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
;====================Fin Juego====================