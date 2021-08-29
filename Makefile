build-main:
	g++ -g -Wall -Wextra -Wpedantic \
	exercise${exercise}/main.cpp \
	-o build/exercise${exercise}.out

build-comparison:
	g++ -g -Wall -Wextra -Wpedantic \
	exercise${exercise}/comparison.cpp \
	-o build/exercise${exercise}_comparison.out

run:
	build/exercise${exercise}.out
