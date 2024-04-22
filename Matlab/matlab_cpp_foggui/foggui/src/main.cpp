
#include <cstdio>
#include <ctime>
#include "mod_foggui.h"

void linha(void);

int main(int argc, char const *argv[]) {

    mod_fogguiModelClass foggui;
    float deg = 180.0/3.14159265358;
    time_T ini = clock();
    time_T fim;
    

    foggui.initialize();
    
    
    foggui.mod_foggui_P.state.config.flags.controle_on = 1;

    foggui.mod_foggui_U.tiro = 1;
    
    
    int cont = 0;

    FILE *f;
    f = fopen("saida.txt","w");

    printf("estou aqui!\n");

    while(foggui.mod_foggui_Y.fim == 0) {
        cont++;
                
        foggui.step();
        
        if ((cont % 1) == 0){
            fprintf(f,"%.1f\t%10.4f\t%6.4f\n", foggui.mod_foggui_Y.tempo, -foggui.mod_foggui_Y.pos[2], foggui.mod_foggui_Y.canard_u[0]*deg);
        }
        
    }

    fclose(f);
    foggui.terminate();

    fim = clock();

    printf("\n");
    linha();
    printf("  tempo de simulacao: %.2fs\n",(float)((fim - ini)/CLOCKS_PER_SEC));
    linha();
    return 0;
}

void linha(void) {
    printf("=============================\n");
}
