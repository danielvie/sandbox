CXX      = g++
CC       = gcc

# CONFIGURACOES
pwd      = C:\ProgramData\Anaconda3
pyd      = hello.pyd


# declare  = -D_hypot = hypot
DECLARE  = -DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION

INCLUDE  = -I${pwd}\include \
		   -I${pwd}\Lib\site-packages\numpy\core\include

cflags   = -O0 ${DECLARE}
CXXFLAGS = -O0 ${INCLUDE} ${DECLARE}
LDFLAGS  = -L${pwd} -shared -lpython37


src      = $(wildcard src/*.c*)

obj      = $(addsuffix .o, $(basename $(src:src/%=obj/%)))

all: r

p:
	@echo ${src}
	@echo ----------------------
	@echo ${obj}
	@echo ----------------------

r: lib
r: test

t: test

lib: ${pyd}
	
${pyd} : $(obj) 
	$(CXX) ${LDFLAGS} ${obj} -o ${pyd}

obj/%.o : src/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

test: lib
	@echo -----------------------------
	python test_mod.py

clean: 
	rm obj/*