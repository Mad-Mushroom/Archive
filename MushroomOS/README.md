# MushroomOS

MushroomOS is a UEFI Operating System based of <a href="https://github.com/marceldobehere/MaslOS">MaslOS</a> and <a href="https://www.youtube.com/watch?v=mpPbKEeWIHU&list=PLxN4E629pPnJxCQCLy7E0SQY_zuumOVyZ">Poncho OS Dev Series</a>.

*The OS is still in development.*

Features
-------------------------------------------------------------------
* Display
  - VGA Output with GOP
* Desktop
  - Background Image
  - Taskbar
* Window Manager
  - Working Window Manager with dynamic windows
  - Start Menu Window
* Apps
  - Terminal using a scrollable Text Window
  - Connect Four Game
  - Task Manager
* Keyboard
  - PS/2 Keyboard support
* Mouse
  - PS/2 Mouse support
* IO
  + Disk
    + Disk Interfaces
      - SATA / SATAPI
      - RAM Disk
      - File Disk
    + Partitioning Interfaces
      - MRAPS (Marcels really awesome partitioning system)
    + Filesystem Interfaces
      - MRAFS (Marcels really awesome filesystem)
* Memory
  - Dynamic Memory Management
  - (In planning) Paging
* OTHER IO
  - PIT
  - AHCI
  - ACPI
  - PCI
* Other Features
  - Stack Trace
  + Crash handling
    - Crash Window showing non fatal kernel panic / crash
    - Advanced Fatal General Protection Fault Handler and recoverer
    - Emergency Kernel Panic
  - BF Interpreter
  - KernelFiles

Images
-------------------------------------------------------------------
Boot:
![Screenshot-Boot](https://user-images.githubusercontent.com/100442757/221419984-8d994db4-aea7-4661-93d9-f12996beab79.png)

Desktop:
![Screenshot-Desktop](https://user-images.githubusercontent.com/100442757/221419994-e4108f15-88bd-4c8c-941e-ac5915dbe0b6.png)

Multiple Windows:
![Screenshot-WindowManager](https://user-images.githubusercontent.com/100442757/221419025-76363573-1424-4ad4-bad8-c0cae24f528e.png)

ToDo before Release 1.0
-------------------------------------------------------------------
- [X] Program Menu
- [ ] File Manager (GUI)
- [ ] Settings
- [ ] Installer
