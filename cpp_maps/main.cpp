#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// objeto de teste
class Objeto {
    private:
        
    public:
        double var1;
        double var2;
        double vec1[3];
        double vec2[10];
        
        Objeto(void);
};

Objeto::Objeto(void){
    memset(&this->var1, 0, sizeof(this->var1));
    memset(&this->var2, 0, sizeof(this->var2));
    memset(this->vec1, 0, sizeof(this->vec1));
    memset(this->vec2, 0, sizeof(this->vec2));
}

struct DataMap {
    int32_t idx;
    void* addr;
    std::string name;
    std::string type;
    int32_t size;
};

Objeto *obj;

struct DataMap get_map(std::string name) {
    
    // criando `mapa`
    struct DataMap Maps[] {
        {0, (void*) &obj->var1, "var1", "double", 1},
        {1, (void*) &obj->var2, "var2", "double", 1},
        {2, (void*) &obj->vec1[0], "vec1", "double", 3},
        {3, (void*) &obj->vec2[0], "vec2", "double", 10},
        {-1, NULL, "", "", 0}
    };

    // buscando `mapa`
    struct DataMap map = {-1, NULL, "", "", 0};
    for (auto mapi : Maps) {
        if (mapi.name.compare(name) == 0) {
            map = mapi;
            break;
        }
    }
    
    return map;
}

uint8_t set_value_double(std::string name, double value){
    // lendo mapa
    struct DataMap map = get_map(name);

    // caso de erro
    if ((map.size != 1)) {
        printf("nao eh um escalar: `%s`\n", map.name.c_str());
        return 0;
    }

    // escrevendo valor valor
    *((double*) map.addr) = value;   

    return 1;     
}

double get_value_double(std::string name){
    // lendo mapa
    struct DataMap map = get_map(name);

    // caso de erro
    if ((map.size != 1)) {
        printf("nao eh um escalar: `%s`\n",map.name.c_str());
        return -1.;
    }

    // retornando valor
    return *((double*) map.addr);        
}

int main(int argc, char const *argv[]) {
      
    // inicializando objeto
    obj = new Objeto();
    double bla;

    // lendo `var1`
    bla = get_value_double("var1");
    printf("bla: %f\n", bla);
    
    // escrevendo em `var1`
    set_value_double("var1", 64.);

    // lendo `var1`
    bla = get_value_double("var1");
    printf("bla: %f\n", bla);

    // deletando objeto
    delete obj;

    return 0;
}