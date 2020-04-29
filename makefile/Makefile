# CONFIGURANDO FLAGS COMPILADOR
CXX           = g++
CC            = gcc

INCLUDE       = -Isrc/lib
DECLARE       = 

CFLAGS	      = -O0 -Wall ${INCLUDE} ${DECLARE}
CXXFLAGS	  = -O0 -Wall ${INCLUDE} ${DECLARE}
LDFLAGS 	  = 

# DEFININDO NOME LIB 'python' E 'exe'
app           = main.exe

# LENDO ARQUIVOS
src           = $(wildcard src/main/*.c*) \
				$(wildcard src/lib/*.c*) 

# AJUSTANDO 'src' E 'obj'
obj_1         = $(addsuffix .o,$(basename $(src:src/main/%=obj/%)))
obj           = $(addsuffix .o,$(basename $(obj_1:src/lib/%=obj/%)))


# LEIS DE COMPILACAO
all: r

r: run

p: 
	@echo -----------------------------
	@echo ${src}
	@echo -----------------------------
	@echo ${obj}
	@echo -----------------------------
	
# AJUSTANDO FLAGS 'python'
lib: ${pyd}
	
# COMPILACAO 'app {exe}'
${app}: ${obj}
	$(CXX) -o ${app} ${obj}

# ESCREVENDO '*.o' EM 'obj'
obj/%.o : src/main/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

obj/%.o : src/lib/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

# MONITORANDO ALTERACOES '.h' IMPORTANTES
# obj/teste.o : src/teste.h

# EXECURANDO 'exe'
run: ${app}
	 ${app}

# LIMPANDO OBJETOS
clean: 
	rm obj/*