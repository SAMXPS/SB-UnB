cd jvm
gcc -I"classfile/" -I"." -I"instructions/" -g classfile/*.c instructions/*.c init/*.c *.c -o ../jvm.exe