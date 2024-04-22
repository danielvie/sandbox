# CONFIGURANDO FLAGS COMPILADOR
CXX           = clang++
CC            = clang

python_path   = /Users/danielvieira/.pyenv/versions/3.11.2/
numpy_path    = ${python_path}/lib/python3.11/site-packages/numpy/core/include/

INCLUDE       = -I${python_path}/include/python3.11 \
				-I${numpy_path} 

OPTIM         = -O0

DECLARE       = -D_hypot=hypot -DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION
CFLAGS        = ${OPTIM} ${DECLARE}
CXXFLAGS      = ${OPTIM} ${INCLUDE} ${DECLARE}
LDFLAGS_PY    = -L${python_path}/lib -shared -lpython3.11

# DEFININDO NOME LIB 'python' E 'exe'
app           = main.exe
pyd           = engine.so

# EXPLICITANDO ARQUIVOS PARA COMPILAR
src           = $(wildcard src/*.c*)

# AJUSTANDO 'src' E 'obj'
obj           = $(addsuffix .o,$(basename $(src:src/%=obj/%)))

# LEIS DE COMPILACAO
all: test

# AJUSTANDO FLAGS 'python'
lib: ${pyd}
	
# COMPILACAO 'python'
${pyd} : $(obj) 
	$(CXX) ${LDFLAGS_PY} ${obj} -o ${pyd}

# ESCREVENDO '*.o' EM 'obj'
obj/%.o : src/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

obj/%.o : src/%.c
	$(CC) ${CFLAGS} -o $@ -c $<

# EXECURANDO 'exe'
run: ${app}
	 ${app}

# EXECURANDO 'python'
test: lib
	python mod_test.py

test_arquivo: lib
		@echo ------------------------------
	  	python py/mod_test_bittar.py

# LIMPANDO OBJETOS
clean: 
	rm obj/*.o ${pyd}