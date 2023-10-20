global _start
[bits 32]

_start:
    ; TODO: pass a bunch of information to the kernel main
    ;       function, like the filesystem, etc.

    

    ; call kmain
    [extern kmain]
    call kmain
    ; jmp $