compile:
	gcc -o main *.c auxiliars/*.c built-ins/*.c operators/*.c REPL/*.c
run:
	./main
