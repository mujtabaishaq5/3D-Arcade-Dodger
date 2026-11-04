global _get_assembly_signature

section .data
    hardware_badge db " [x86-64 NASM Coprocessor Active via ELPL]", 0

section .text
_get_assembly_signature:
    lea rax, [rel hardware_badge]
    ret