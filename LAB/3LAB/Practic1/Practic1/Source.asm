; 15 �������
; �� ��������� ������ ��� �����, ������ �� ������� ������ �����
; ��������� (x, y). ���������� ������ �� ��� �����
; ������������� �����������. ���������� ����� -
; �������������� �����.

; ��� ��������, �������� �� ������ ������������� �������������, ����� ������������ ������� ��������
; 
; �������, ��� ���������� ������� ������ �������� ������������� �������������:
; x1^2+y1^2-x1x2+x2x3-x1x3-y1y2+y2y3-y1y3 = 0



.686
.model flat, stdcall
.stack 100h

.data
x1 dd 1
y1 dd 1

x2 dd 1
y2 dd 4

x3 dd 5
y3 dd 1

result dd 0 ; �������� ���������� �������
bufer dd 0  ; �������� �������� �������

otvet dw 1 ; ���� 0, �� �������������; ���� 1, �� ���

.code
ExitProcess PROTO STDCALL :DWORD

; ��������� �������: ���������� ������� ����� c���, � ���������� � ������� ����� ����� ��� ������������� ����, ����� ���� � � ������ ����������� ��������� ����� ����������� 



Start:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    finit ; ������������� ������������

    mov otvet, 1 ; ����������� ���� ���
    mov cx, 3 ; 3 ����� 

    



smeshenie:
    sub esp, 80
    call vichislenia
    add esp, 80
    ; ����� �������� �� ������� �������� ZF (���� ����)
    ; ���� ZF=1, ������ ������������� �����������
    ; ���� ���, ������ ���������� � ���������

    ; �������� ����� ZF ����� vichislenia
    ; vichislenia ������ ������������� ���� ZF ����� sahf

    ; �������� ���� ZF --> sahf ��������� ����� �� AH, ������� ���� ZF �������� ��������

    ; ���� ZF=1 --> ������� � obhod
    ;jz obhod

    ; ������������ ��������� ��� ��������� ��������
    mov edx, x2
    mov eax, x1
    mov x2, eax
    mov eax, x3
    mov x3, edx
    mov x1, eax

    mov edx, y2
    mov eax, y1
    mov y2, eax
    mov eax, y3
    mov y3, edx
    mov y1, eax

    loop smeshenie

    ; ���� ����� 3 ������� �� ����� ������������� �����������
    ; ������� � exit (�� �������� �������������)
    jmp exit

    



    mult PROC ; ������� ���������
      add esp, 4
      finit ; ������������ �������������
      fild dword ptr [esp]
      fild dword ptr [esp+4]
      fmul st(0), st(1) 
      fist dword ptr [esp]
      sub esp, 4

      ret

    mult ENDP

    sum PROC ; ������� �����
      add esp, 4
      finit ; ������������ �������������
      fild dword ptr [esp]
      fild dword ptr [esp+4]
      fadd st(0), st(1) 
      fist dword ptr [esp]
      sub esp, 4

      ret

    sum ENDP

    power PROC ; ������� �������
      add esp, 4
      finit ; ������������ �������������
      fild dword ptr [esp]
      fild dword ptr [esp]
      fmul st(0), st(1) 
      fist dword ptr [esp]
      sub esp, 4

      ret

    power ENDP
    ;                                                       *�������*

    minus PROC ; ������� ���������
     add esp, 4
     finit ; ������������ �������������
     fild dword ptr [esp]
     fild dword ptr [esp+4]
     fsub st(0), st(1) 
     fist dword ptr [esp]
     sub esp, 4

     ret

    minus ENDP

vichislenia PROC
    mov ebx, esp
    ; �������� x1^2
    ;fild word ptr [x1]
    ;fld st(0)
    ;fmulp st(1), st(0)
    push x1
    call power
    pop result
    
    
    ; ������� y1^2
    ;fild word ptr [y1]
    ;fld st(0)
    ;fmulp st(1), st(0)
    ;faddp st(1), st(0)
    push y1
    call power
    ;pop bufer
    push result
    ;push bufer
    call sum
    pop result


    ; ������ x1*x2
    ;fild word ptr [x1]
    ;fild word ptr [x2]
    ;fmulp st(1), st(0)
    ;fchs
    ;faddp st(1), st(0)
    push x1
    push x2
    call mult 
    push result
    call minus
    pop result
    

    ; ������� x2*x3
    ;fild word ptr [x2]
    ;fild word ptr [x3]
    ;fmulp st(1), st(0)
    ;faddp st(1), st(0)
    push x2
    push x3
    call mult
    push result
    call sum
    pop result
  

    ; ������ x1*x3
    ;fild word ptr [x1]
    ;fild word ptr [x3]
    ;fmulp st(1), st(0)
    ;fchs
    ;faddp st(1), st(0)
    push x1
    push x3
    call mult
    push result
    call minus
    pop result


    ; ������ y1*y2
    ;fild word ptr [y1]
    ;fild word ptr [y2]
    ;fmulp st(1), st(0)
    ;fchs
    ;faddp st(1), st(0)
    push y1
    push y2
    call mult
    push result
    call minus
    pop result


    ; ������� y2*y3
    ;fild word ptr [y2]
    ;fild word ptr [y3]
    ;fmulp st(1), st(0)
    ;faddp st(1), st(0)
    push y2
    push y3
    call mult
    push result
    call sum


    ; ������ y1*y3
    ;fild word ptr [y1]
    ;fild word ptr [y3]
    ;fmulp st(1), st(0)
    ;fchs
    ;faddp st(1), st(0)
    push y1
    push y3
    call mult
    push result
    call minus
    pop result
  

    ; ������� ��������� � 0
    cmp result, 0
    je pryamougolniy ; ������� � ����� pryamougolniy, ���� �������������
;    mov otvet, 0
    mov esp, ebx
    ret ; ���� �� �������., �� ����� �� �������
    ;fldz
    ;fcom st(1)
    ;fstsw ax
    ;sahf


    pryamougolniy:
        mov otvet, 0


    mov esp, ebx
    ret
vichislenia ENDP

;obhod:
;    ; ����������� �������������
;    invoke ExitProcess, otvet
;
exit:
;    ; ����������� �� �������������
    invoke ExitProcess, otvet

End Start


; otvet = 0 --> ��������������� �����������
; otvet = 1 -->  ������������� �����������