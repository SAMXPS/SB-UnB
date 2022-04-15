cd jvm
g++ -D_DEBUG=1 -Wfatal-errors -I"classfile/" -I"." -I"instructions/" -I"init/" -g classfile/*.cpp instructions/*.c init/*.cpp *.cpp -w -o ../jvm.exe
cd ..