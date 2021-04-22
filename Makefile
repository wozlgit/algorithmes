build:
	g++ -Wall -Wextra -Wpedantic \
	./${program}.cpp \
	-o ${program}.out

run:
	./${program}.out