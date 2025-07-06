;; NASM AT&T Style
section .data
    msg db      "hello, world!"

section .text
    global _start

_start:
    mov     rax, 1   ;; sys_write
    mov     rdi, 1   ;; arg[1] stdout
    mov     rsi, msg ;; arg[2] msg
    mov     rdx, 13  ;; arg[3] len(msg)

    syscall
    mov    rax, 60 ;; sys_exit
    mov    rdi, 0  ;; sys_exit code = 0 (success)
    syscall