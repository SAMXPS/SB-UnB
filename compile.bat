cd jvm
g++ -Wfatal-errors -I"classfile/" -I"." -I"instructions/" -I"init/" -g classfile/*.c instructions/*.c init/*.c init/*.cpp *.c -w -o jvm.exe