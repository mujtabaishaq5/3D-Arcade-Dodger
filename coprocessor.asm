; @elpl-sig: void invert_colors(void* ptr, int bytes)
global _invert_colors

section .text
_invert_colors:
    ; RDI = Framebuffer RAM pointer
    ; RSI = Total byte count

    test rsi, rsi
    jz .done

.process_pixel:
    not byte [rdi]      ; Fast bitwise NOT (255 - val)
    inc rdi
    dec rsi
    jnz .process_pixel

.done:
    ret