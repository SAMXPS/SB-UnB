cd jvm
g++ -D_DEBUG=1 -Wfatal-errors -I"classfile/" -I"." -I"instructions/" -I"init/" -g classfile/*.c instructions/*.c init/*.c init/*.cpp *.c -w -o ../jvm.exe