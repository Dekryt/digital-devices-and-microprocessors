; X = 9			��������� M=(Z' or X' and Y)+(X' / Z)
; Y = 44		, ��� Z', X' - �������� � ���������� �������� 4
; Z = 12		������� ��� Z � X �������������� 

.686
.model flat, stdcall
.stack 100h

.data
x dw 9 ; ������� ����������
y dw 44
z dw 12
.code

ExitProcess PROTO STDCALL :DWORD
Start:
xor eax,eax
xor ebx,ebx
xor edx,edx ; �������� ������ ��� ���������� ����������
mov bx, z ;  ���� � ������� BX �������� ����� z == Ch == 12 (10)
xor x,11110000b ;X` == 11111001 == F9
xor bx,11110000b ;Z` == 11111100 == FC

; ������ (X' / z)
mov ax, x ;  ���� � ������� AX �������� ����� �
div z ; ������� �� ���������� z  == 14h == 20 (10)

; ������ (Z' or X' and Y)
or bx, x ; �������� z or x, ��� ��� � �������� BX ��� ��������� �������� z
and bx, y ; �������� ����������� �������� � �������� BX and y

; ����� ����������� ������, ����������� � ��������� BX � AX
ADD bx, ax

exit:
Invoke ExitProcess,1
End Start