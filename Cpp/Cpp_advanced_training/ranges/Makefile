app = sortapp

all: r

${app}: sort/sort.cpp
	g++ --std=c++20 -o ${app} sort/sort.cpp

r: ${app}
	./${app}
