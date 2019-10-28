include musers.asm

.data
;====================Ini Var Globales=============================
usuarios STRUCT
        nombre BYTE 15 dup('$')
        contra BYTE 15 dup('$')
        punteo WORD 0
usuarios ENDS  

problem  db 'holiii', '$'

tamanioUsers = 3

arrayuser            usuarios   tamanioUsers dup(<>)
;====================Fin Var Globales=============================

.code
;====================Gestion Usuarios=============================



RegistrarUsuario proc
        ;--------------------------------------------------------------------
        ;   Recibe:      Nada                                                 
        ;   Devuelve:    Nada                                                
        ;                                                                    
        ;   Comentarios: Registra Usuarios                                  
        ;--------------------------------------------------------------------

        ;Ini Subrutina prologo

        ;Fin Subrutina prologo


        ;Ini Codigo

            ;println space
            ;mWrite <'****Ingrese***',13,10>
            ;mWrite <9,'Nombre Usuario:'>
            ;read Usuario
            ;mWrite <9,'Contrasena:'>
            ;read Contra
            ;print Usuario
            ;print Contra

        ;llenaArreglos
         mov si, offset arrayuser
         lea bx,(usuarios ptr[si]).nombre

         mov byte ptr[bx],'h'
         inc bx
         mov byte ptr[bx],'o'
         inc bx
         mov byte ptr[bx],'l'
         inc bx
         mov byte ptr[bx],'a'
         inc bx 
         mov byte ptr[bx],'d'

         lea bx,(usuarios ptr[si]).nombre
         printDir bx

        ;Fin Codigo


        ;ini Subrutina epilogo
            FIN:
                ret 
        ;fin Subrutina epilogo
RegistrarUsuario endp





;====================Gestion Usuarios=============================

