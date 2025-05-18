; X = 9			Вычислить M=(Z' or X' and Y)+(X' / Z)
; Y = 44		, где Z', X' - получены в результате инверсии 4
; Z = 12		старших бит Z и X соответственно 

.686
.model flat, stdcall
.stack 100h

.data
x dw 9 ; задание переменных
y dw 44
z dw 12
.code

ExitProcess PROTO STDCALL :DWORD
Start:
xor eax,eax
xor ebx,ebx
xor edx,edx ; очищение памяти для исключения перегрузки
mov bx, z ;  ввод в регистр BX значение числа z == Ch == 12 (10)
xor x,11110000b ;X` == 11111001 == F9
xor bx,11110000b ;Z` == 11111100 == FC

; скобка (X' / z)
mov ax, x ;  ввод в регистр AX значение числа х
div z ; деление на переменную z  == 14h == 20 (10)

; скобка (Z' or X' and Y)
or bx, x ; операция z or x, так как в регистре BX уже находится значение z
and bx, y ; операция полученного значения в регистре BX and y

; сумма результатов скобок, находящихся в регистрах BX и AX
ADD bx, ax

exit:
Invoke ExitProcess,1
End Start