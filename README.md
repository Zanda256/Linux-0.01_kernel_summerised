* Prerequisites
*
* GCC, BINUTILS (main tool-chain) -- can be installed by: apt-get install build-essential 
* BIN86 (for the bootloader 16 bit assembly code) -- can be installed by: apt-get install bin86
* qemu-system-x86 (as Pc visualizing software) -- can be installed by: apt-get install qemu-system
* NOTE: installing build essentials also ships the GNU make tool, All installations assume 
* you are root and with a nice connection

* Compile
* Open terminal int the source directory
* make -- to compile everything
* make run -- to compile all the sources
* make dump -- objdum (default is intel but can be overriden by att from the makefile)

* Challenge_1
* src_dir/boot/boot.s is written in assembler. as86
* re-write the file int GNU GAS assembler and make sure it compiles

* Challenge_2
* (after Challenge_1) ...

* Challenge_3
* (after Challenge_2) ...

.
.
.
