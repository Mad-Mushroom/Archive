del %0\..\..\ovmfbin\* /F /Q
copy %0\..\OVMF_CODE-pure-efi.fd %0\..\..\ovmfbin
copy %0\..\OVMF_VARS-pure-efi.fd %0\..\..\ovmfbin

set OSNAME=MushroomOS
set BUILDDIR=%0/../bin
set OVMFDIR=%0/../../ovmfbin

:: qemu-system-x86_64 -machine q35 -drive file=%BUILDDIR%/%OSNAME%.img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="%OVMFDIR%/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="%OVMFDIR%/OVMF_VARS-pure-efi.fd" -net none
qemu-system-x86_64 -machine q35 -drive file=%BUILDDIR%/%OSNAME%.img -drive file=%BUILDDIR%/blank.img -m 1G -cpu qemu64 -drive if=pflash,format=raw,unit=0,file=%OVMFDIR%/OVMF_CODE-pure-efi.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=%OVMFDIR%/OVMF_VARS-pure-efi.fd -net none -soundhw pcspk
exit
