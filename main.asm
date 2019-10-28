
main proc
    Inicio:
        IniciarDs
        print msm0
    ;Fin etiqueta

    MenuPrincipal:
		;--------MOSTRANDO EL MENU PRINCIPAL--------------------------
		print msm8

		print salt
		;--------OBTENIENDO EL NUMERO ESCOGIDO------------------------
		getChar
		cmp al,'1'; COMPARO CON EL ASCII DEL NUMERO 1 QUE ES 49 Y EN HEXA `31H
		je juego
		cmp al,'2'
		je regUsuario
		cmp al,'3'
		je IngresoAdmin
		cmp al,'4'
		je Salir
		jmp MenuPrincipal
	;fin etiqueta



	IngresoUsuario:
		jmp salir
	;fin etiqueta
	regUsuario:
		mRegistrarUsuario
		jmp salir
	;fin etiqueta
	IngresoAdmin:
		jmp salir
	;fin etiqueta


	juego:
		mSetup
		mGame

		;--Esto se Ejecuta despues de terminar el juegos
		mov terminoJuego[0],0				;se puede inicial el juego de nuevo
		ModoTexto
		jmp MenuPrincipal
	;fin etiqueta


    salir:
            mov ah,4ch ; numero de funcion para finalizar el programa
            xor al,al
            int 21h
    ;fin etiqueta

main endp
