Total Hours Spent: 1.5/1.5
		   Actual/Expect

4357 Embedded Firmware Essentials
- Program Assignment #2

1. Login to mbed web site, export the "Hello World" program to all of the following targets. 
   How many text files and how many lines of text code in the exported offline code package?
   	By "text files", I took that to mean any .cpp or .h files:
   	Number of text files: 
   		http://stackoverflow.com/questions/4767396/linux-command-how-to-find-only-text-files
   		find -type f -exec grep -Il . {} \;
   		Excluding the hidden .hg files, this yields 58 files for the uvision export, 57 files for the gcc export
   	Number of code files:
   		http://www.linuxquestions.org/questions/programming-9/linux-find-to-find-files-with-multiple-patterns-261595/
   		find . -type f \( -name "*.h" -o -name "*.cpp" \)| wc -l
   		54 files, for both the uvision export and the gcc export
   	Number of lines of code (I assumed just .h and .cpp files):
   		http://stackoverflow.com/questions/1358540/how-to-count-all-the-lines-of-code-in-a-directory-recursively
   		find . -type f \( -name "*.h" -o -name "*.cpp" \)| xargs wc -l
   		(find . -type f \( -name "*.h" -o -name "*.cpp" \) -print0 | xargs -0 cat) | wc -l
   		9706 lines of code, for both the uvision export and the gcc export
   	
   How many binary (library or object) files? 
   	I just browsed the output of find ./mbed -type f -print0 | xargs -0 file
   	gcc: looks like 6 files (four .o, two .a files)
   	uvision: looks like 7 files (five .0, two .ar files)
   How many files are different between (a) and (b)? (Use linux commands: find, wc, diff) (10 points)
   	which files are unique, top directory: just 3 files, 2 directories differ
   	diff -r HelloWorld\ gcc/ HelloWorld\ uvision/
   		Only in HelloWorld uvision/: HelloWorld.uvopt
		Only in HelloWorld uvision/: HelloWorld.uvproj
		Only in HelloWorld gcc/: Makefile
		Only in HelloWorld uvision/mbed/LPC1768: ARM
		Only in HelloWorld gcc/mbed/LPC1768: GCC_ARM
	comparing the 2 ARM directories: 4 pairs of binary files differ; 7 files are unique
	diff -r HelloWorld\ uvision/mbed/LPC1768/ARM/ HelloWorld\ gcc/mbed/LPC1768/GCC_ARM/
		Only in HelloWorld gcc/mbed/LPC1768/GCC_ARM/: LPC1768.ld
		Only in HelloWorld uvision/mbed/LPC1768/ARM/: LPC1768.sct
		Only in HelloWorld uvision/mbed/LPC1768/ARM/: capi.ar
		Binary files HelloWorld uvision/mbed/LPC1768/ARM/cmsis_nvic.o and HelloWorld gcc/mbed/LPC1768/GCC_ARM/cmsis_nvic.o differ
		Binary files HelloWorld uvision/mbed/LPC1768/ARM/core_cm3.o and HelloWorld gcc/mbed/LPC1768/GCC_ARM/core_cm3.o differ
		Only in HelloWorld gcc/mbed/LPC1768/GCC_ARM/: libcapi.a
		Only in HelloWorld gcc/mbed/LPC1768/GCC_ARM/: libmbed.a
		Only in HelloWorld uvision/mbed/LPC1768/ARM/: mbed.ar
		Binary files HelloWorld uvision/mbed/LPC1768/ARM/startup_LPC17xx.o and HelloWorld gcc/mbed/LPC1768/GCC_ARM/startup_LPC17xx.o differ
		Only in HelloWorld uvision/mbed/LPC1768/ARM/: sys.o
		Binary files HelloWorld uvision/mbed/LPC1768/ARM/system_LPC17xx.o and HelloWorld gcc/mbed/LPC1768/GCC_ARM/system_LPC17xx.o differ

   What is the "Entry point address:" of your program?  (hint: using readelf)
   	go into the uvision directory, execute: (find . -type f -print0 | xargs -0 file) | grep "ELF"
		./mbed/LPC1768/ARM/cmsis_nvic.o:      ELF 32-bit LSB relocatable, ARM, version 1 (SYSV), not stripped
		./mbed/LPC1768/ARM/core_cm3.o:        ELF 32-bit LSB relocatable, ARM, version 1 (SYSV), not stripped
		./mbed/LPC1768/ARM/startup_LPC17xx.o: ELF 32-bit LSB relocatable, ARM, version 1 (SYSV), not stripped
		./mbed/LPC1768/ARM/sys.o:             ELF 32-bit LSB relocatable, ARM, version 1 (SYSV), not stripped
		./mbed/LPC1768/ARM/system_LPC17xx.o:  ELF 32-bit LSB relocatable, ARM, version 1 (SYSV), not stripped
	Note that this command yields the same results: find . -type f -name "*.o"
	Get the entry point address for all these files: (find . -type f -name "*.o" -print0 | xargs -0 greadelf -a ) | grep "Entry point addr"
		  Entry point address:               0x0
		  Entry point address:               0x0
		  Entry point address:               0x0
		  Entry point address:               0x0
		  Entry point address:               0x0
   
   a.	Exporting to uVision 
   b.	Exporting to GCC ARM Embedded 

   Note: Right Click your program, then select "export ..."

2. binwalk, objdump, nm to Analysis binaries files
   http://binwalk.org/

3. Optional: git clone https://github.com/mbedmicro/mbed
   
