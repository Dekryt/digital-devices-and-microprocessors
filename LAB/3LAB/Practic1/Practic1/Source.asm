; 15 вариант
; На плоскости задано три точки, каждая из которых задана парой
; координат (x, y). Определить задают ли эти точки
; прямоугольный треугольник. Координаты точек -
; действительные числа.

; для проверки, является ли фигура прямоугольным треугольником, можно использовать теорему Пифагора
; 
; Формула, при истинности которой объект является прямоугольным треугольником:
; x1^2+y1^2-x1x2+x2x3-x1x3-y1y2+y2y3-y1y3 = 0



.686
.model flat, stdcall
.stack 100h

.data
x1 dd 1 ; задаем координаты точек
y1 dd 1

x2 dd 1
y2 dd 4

x3 dd 5
y3 dd 1

result sdword 0 ; хранение результата формулы
bufer dd 0  ; буферное хранение формулы
                ; sdword -- dd со знаком
otvet dw 1 ; если 0, то прямоугольный; если 1, то нет

.code
ExitProcess PROTO STDCALL :DWORD

; последняя догадка: передавать функции через cтек, и обращаться в нужноее место стека для инициализации того, какой блок и с какими переменными программа будет выполняться 



Start:
    xor eax, eax ; очистка регистров
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    finit ; инициализация сопроцессора

    mov otvet, 1 
    mov cx, 3 ; кол-во итераций цикла "smeshenie"

    
smeshenie:
    sub esp, 80 ; выделение 80 байт памяти (оптимально) для выполнения функции
    call vichislenia
    add esp, 80 ; смещаем указатель на вершину стека в сторону большего адреса, что даёт отстут на 80 байт
                ; от реальной вершины стека
                ; чем больше значение, тем ближе к концу стека

    cmp otvet, 0 ; если otvet == 0 --> ZF = 1
    je exit      ; идем на точку exit, если ZF == 1

    ; после возврата из функции проверим ZF (флаг нуля)
    ; если ZF=1, значит прямоугольный треугольник
    ; если нет, меняем координаты и повторяем

    ; проверка флага ZF после vichislenia
    ; vichislenia должна устанавливать флаг ZF через sahf

    ; Проверим флаг ZF
    ; sahf загружает флаги из AH, поэтому флаг ZF доступен напрямую

    ; если ZF=1, перейти к obhod
    ;jz obhod

    ; перестановка координат для следующей проверки
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

    ; если после 3 попыток не нашли прямоугольный треугольник
    ; перейти к exit (не является прямоугольным)
    jmp exit

    
    mult PROC ; функция умножения
      add esp, 4
      finit ; перезагрузка матпроцессора
      fild dword ptr [esp]
      fild dword ptr [esp+4]
      fmul st(0), st(1) 
      fist dword ptr [esp]
      sub esp, 4

      ret

    mult ENDP

    sum PROC ; функция суммы 
      add esp, 4
      finit ; перезагрузка матпроцессора
      fild dword ptr [esp+4]
      fild dword ptr [esp]
      fadd st(0), st(1) 
      fist dword ptr [esp]
      sub esp, 4

      ret

    sum ENDP

    power PROC ; функция степени
      add esp, 4
      finit ; перезагрузка матпроцессора
      fild dword ptr [esp]
      fild dword ptr [esp]
      fmul st(0), st(1) 
      fist dword ptr [esp]
      sub esp, 4

      ret

    power ENDP
    ;                                                       *выстрел*

    minus PROC ; функция вычитания (esp - (esp+4))
     add esp, 4
     finit ; перезагрузка матпроцессора
     fild dword ptr [esp+4]
     fild dword ptr [esp]
     fsub st(0), st(1) 
     fist dword ptr [esp]
     sub esp, 4

     ret

    minus ENDP

vichislenia PROC
    mov ebx, esp
    ; Вычислим x1^2
    ;fild word ptr [x1]
    ;fld st(0)
    ;fmulp st(1), st(0)
    push x1
    call power
    pop result
    
    
    ; Добавим y1^2
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


    ; Вычтем x1*x2
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
    

    ; Добавим x2*x3
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
  

    ; Вычтем x1*x3
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


    ; Вычтем y1*y2
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


    ; Добавим y2*y3
    ;fild word ptr [y2]
    ;fild word ptr [y3]
    ;fmulp st(1), st(0)
    ;faddp st(1), st(0)
    push y2
    push y3
    call mult
    push result
    call sum
    pop result

    ; Вычтем y1*y3
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
  

    ; Сравним результат с 0
    cmp result, 0
    je pryamougolniy ; переход к точке pryamougolniy, если прямоугольный
;    mov otvet, 0
    mov result, 0
    mov esp, ebx
    ret ; если не прямоуг., то выход из функции
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
;    ; Треугольник прямоугольный
;    invoke ExitProcess, otvet
;
exit:
;    ; Треугольник не прямоугольный
    invoke ExitProcess, otvet

            ;otvet = 0 --> является прямоугольным
            ;otvet = 1 --> неявляется прямоугольным

End Start
