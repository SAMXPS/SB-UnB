cd jvm
g++ -I"classfile/" -I"." -I"instructions/" -I"init/" -g classfile/*.c instructions/*.c init/*.c init/*.cpp *.c -o ../jvm.exe