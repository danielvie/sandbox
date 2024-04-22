CXX = g++
CC = gcc

DEFINE = -DMODEL=mod_foggui \
		 -DNUMST=2 \
		 -DNCSTATES=0 \
		 -DHAVESTDIO \
		 -DRT \
		 -DUSE_RTMODEL \
		 -DCLASSIC_INTERFACE=0 \
		 -DALLOCATIONFCN=0 \
		 -DTID01EQ=0 \
		 -DMAT_FILE=0 \
		 -DONESTEPFCN=1 \
		 -DTERMFCN=1 \
		 -DMULTI_INSTANCE_CODE=1 \
		 -DINTEGER_CODE=0 \
		 -DMT=0

INCLUDE = -Ilib

CXXFLAGS = ${DEFINE} ${INCLUDE} -Wall -pedantic -std=c++17 -o2
CFLAGS = ${DEFINE} ${INCLUDE} -Wall -pedantic -o2
LDFLAGS = 



src_ = $(wildcard src/*.c*)
src  = ${src_} $(wildcard lib/*.c*)

obj_ = $(addsuffix .o,$(basename $(src:src/%=obj/%)))
obj  = $(obj_:lib/%=obj/%)
app  = main.exe

all: run
# all: p

p: 
	@echo ${obj}
	@echo ${app}

$(app): $(obj)
	$(CXX) $(LDFLAGS) -o $@ $(obj) $(LBLIBS)

obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/%.o : lib/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

obj/%.o : lib/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

run: ${app}
	 @echo --------------------------------
	 ./${app}

r:
	 ./${app}


clean:
	rm -rf $(obj) $(app)