GDT_Start:

  null_descriptor:

    dd 0
    dd 0

  code_descriptor:

    dw 0xFFFF ;first 16 bytes of the limit.
    dw 0      ;24 bits of the base
    dw 0      ; "
    db 10011010 ; pres,priv,type | TypeFlags
    db 11001111 ; otherFlags | last4bits of limit
    db 0        ; last 8 bits of the base.

  data_descriptor:

    dw 0xFFFF
    dw 0
    dw 0
    db 10010010
    db 11001111
    db 0

GDT_End:

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG egu data_descriptor - GDT_Start 


;tpe flags:  code seg? | conforming | readable | Accesed
;other flags : granularity 1 implies limit *= 0x1000 | is seg use 32bit mem | meh | meh

GDT_Descriptor:
  
  dw GDT_End - GDT_Start - 1
  dw GDT_Start
