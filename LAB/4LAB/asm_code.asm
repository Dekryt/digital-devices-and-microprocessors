;.686
;.model flat, stdcall
;.stack 100h

PUBLIC func1 ; ������� asm ������ �������
EXTRN c_function:PROC   ; c_function - �������� ������� � c / cpp

.data


.code

; ������ �������� ������� � �������� RCX
; ������ �������� ������� � �������� RDX
func1 PROC  ;dword --> 4 byte , massive, n --> ���������� ��������
xor eax, eax
xor ebx, ebx

mov R12, rcx  ; � �������� R12 ����� �������
mov R9, rdx  ; � �������� R9 �������� n , ������ �������
mov R14, 0 ; ��� ��� ������� , �������
mov rcx, R9 ; ���������� �������� �����

loop_1:

  movss xmm0, dword ptr [R12 + R14 * 4] ; ��������� � xmm0 i-�� ������� �������, ��� R14 - �������� ��������� ��������
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
