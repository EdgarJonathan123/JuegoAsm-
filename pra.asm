;--------Ensamblador MASM arquitectura 80286
    include macro.asm
;================= DECLARACION TIPO DE EJECUTABLE ================
    .model small , stdcall
    .286
    .stack 100h

        include Juego.inc
        include proc.inc
        topex = 61114d
    .data
        include data.asm
;================= FIN TIPO DE EJECUTABLE ========================

.code
;================== SECCION DE CODIGO =============================
    include main.asm
;================ FIN DE SECCION DE CODIGO ========================
end main
