
main proc
    Inicio:
        IniciarDs
    ;Fin etiqueta

    MenuPrincipal:
		;--------MOSTRANDO EL MENU PRINCIPAL--------------------------
		print enc0
		print enc1
		print salt
		;--------OBTENIENDO EL NUMERO ESCOGIDO------------------------
		getChar
		cmp al,'1'; COMPARO CON EL ASCII DEL NUMERO 1 QUE ES 49 Y EN HEXA 31H
		je Video1
		cmp al,'3'
		je Salir
		jmp MenuPrincipal
	;fin etiqueta

	Video1:
		ModoVideo
		mPintarMargen 5

		mtolineal posI[0],posI[1]
		mov bx,ax

		movmiento

		;getChar
        ;TES:
		    ModoTexto
		jmp MenuPrincipal

	;fin etiqueta


    salir:
            mov ah,4ch ; numero de funcion para finalizar el programa
            xor al,al
            int 21h
    ;fin etiqueta

main endp
