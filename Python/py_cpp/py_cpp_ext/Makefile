CXX      = g++
CC       = gcc

pwd      = C:\ProgramData\Anaconda3

# declare  = -D_hypot = hypot

DECLARE  = -DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION

INCLUDE  = -I${pwd}\include \
		   -I${pwd}\Lib\site-packages\numpy\core\include

cflags   = -O0 ${DECLARE}
CXXFLAGS = -O0 ${INCLUDE} ${DECLARE}
LDFLAGS  = -L${pwd} -shared -lpython37


src      = $(wildcard src/*.c*)

obj      = $(addsuffix .o, $(basename $(src:src/%=obj/%)))

pyd      =  hello.pyd
			
all: r

p:
	@echo ${src}
	@echo ----------------------
	@echo ${obj}
	@echo ----------------------

# all: build

r: lib
r: test

t: test

lib: ${pyd}
	
${pyd} : $(obj) 
	$(CXX) ${LDFLAGS} ${obj} -o ${pyd}

obj/%.o : src/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

# all: hello.c setup.py
# 	python3 setup.py build_ext --inplace

test: all
	python test_mod.py

cl: clean
cl: ${pyd}

clean: 
	rm obj/*