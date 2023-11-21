; OpenOS Binaries
;
; Made by MadMushroom
;
; Copyright (c) 2023 MadMushroom

%macro IncBin 2
  SECTION .rodata
  GLOBAL %1
%1:
  incbin %2
  db 0
  %1_size: dq %1_size - %1
%endmacro

IncBin Logo, "src/extern/logo.txt"
IncBin License, "src/extern/license.txt"
IncBin Alpha, "src/extern/alpha.txt"
IncBin BetaFish, "src/extern/beta.txt"