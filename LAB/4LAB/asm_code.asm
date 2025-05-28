;.686
;.model flat, stdcall
;.stack 100h

PUBLIC func1 ; функция asm делаем внешней
EXTRN c_function:PROC   ; c_function - название функции в c / cpp

.data


.code

; первый параметр функции в регистре RCX
; второй параметр функции в регистре RDX
func1 PROC  ;dword --> 4 byte , massive, n --> передающий параметр
xor eax, eax
xor ebx, ebx

mov R12, rcx  ; в регистре R12 адрес массива
mov R9, rdx  ; в регистре R9 значение n , размер массива
mov R14, 0 ; шаг для массива , счетчик
mov rcx, R9 ; количество итераций цикла

loop_1:

  movss xmm0, dword ptr [R12 + R14 * 4] ; загружаем в xmm0 i-ый элемент массива, где R14 - является счетчиком элемента
  mov R13, rcx ; 
  sub rsp, 72 ; 
  call c_function
  add rsp, 72
  movss dword ptr [R12 + R14 * 4], xmm0 ; 
  mov rcx, R13
  inc R14 ; R14 + 1

loop loop_1

ret
func1 ENDP 

End 
