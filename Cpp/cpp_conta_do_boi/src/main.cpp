#include <stdio.h>
#include <math.h>
#include <memory>
#include <cassert>
#include <iostream>


#define PI 3.14159265358979323846
#define DR 360.0 
#define MILS 6400.0


struct Response 
{
    double dist;
    double azim;
    double head;
    double diff;
};


struct Coord 
{
    double e;
    double n;
    
    Coord() {}
    Coord(double e, double n) : e(e), n(n) {}

    void set(double e_, double n_) {
        e = e_;
        n = n_;
    }
};


double deg2rad(double deg)
{
    return (deg * PI / 180);
}

double rad2deg(double rad)
{
    return (rad * 180 / PI);
}

double distance(Coord lmu, Coord ref)
{
    double de = ref.e - lmu.e;
    double dn = ref.n - lmu.n;
    return sqrt(de * de + dn * dn);
}

double azimuth(Coord lmu, Coord ref)
{
    double de = ref.e - lmu.e;
    double dn = ref.n - lmu.n;
    double angle = rad2deg(atan2(de, dn));
    angle = fmod(angle + DR, 360.0);
    return angle * MILS / 360.0;
}


double calc_azimute(Coord ini, Coord end)
{
    const Coord vref(0.0, 1.0); 
    const Coord v(end.e - ini.e, end.n - ini.n);
    
    // calculando angulo por produto escalar
    double azi = acos((v.e*vref.e + v.n*vref.n)/sqrt(v.e*v.e + v.n*v.n));
    
    // calculando sinal angulo
    const bool sinal = vref.e*v.n - v.e*vref.n;
    
    if (sinal > 0.0) {
        printf("sinal: %d, azi: %f\n", sinal, azi);
        azi = 2.0*PI - azi;
    }

    return azi * 3200.0 / PI;
}

double heading(Coord lmu, Coord ref, double ao)
{
    double azim = azimuth(lmu, ref);
    double head = fmod(azim - ao * MILS / 360.0, MILS);
    return head;
}

std::shared_ptr<Response> computeBoi(Coord &lmu, Coord &ref, double ao, double heading_read)
{
    std::shared_ptr<Response> re = std::make_shared<Response>();
    
    re->dist = distance(lmu, ref);
    re->azim = azimuth(lmu, ref);
    re->head = heading(lmu, ref, (ao / 17.7778));
    
    double head_ = (re->head > 0.0) ? re->head : (6400 + re->head);
    re->diff = head_ - heading_read;

    return re;
}

int main()
{
    Coord lmu, ref;
    double ao;
    double heading_sensor;
    int op;
    do
    {
        // printf("Conta do Ze\n\n");
        // printf("Coordenadas LMU (Este):\n");
        // scanf("%lf", &x1);
        // printf("Coordenadas LMU (Norte):\n");
        // scanf("%lf", &y1);
        // printf("Coordenadas Ponto Ref. (Este):\n");
        // scanf("%lf", &x2);
        // printf("Coordenadas Ponto Ref. (Norte):\n");
        // scanf("%lf", &y2);
        // printf("Digite o AO em MILs:\n");
        // scanf("%lf", &ao);
        // printf("Digite o Azimute:\n");
        // scanf("%lf", &azimute);


        // preparando funcoes de assert
        auto assert_result = [] (std::shared_ptr<Response> re, const Response &re_ref) 
        {
            auto assert_double = [] (double d1, double d2) 
            {
                assert(fabs(d1 - d2) < 0.01);
            };

            assert_double(re->dist, re_ref.dist);
            assert_double(re->azim, re_ref.azim);
            assert_double(re->head, re_ref.head);
            assert_double(re->diff, re_ref.diff);
        };


        auto print_result = [] (std::shared_ptr<Response> re) 
            {
            printf("\n");
            printf("..> dist: %.2f metros\n", re->dist);
            printf("..> DR: %.2f mils\n", re->azim);
            printf("..> HEADING (DR-AO): %.2f mils\n", re->head);
            printf("..> Diff heading: %.2f mils\n\n", re->diff);
        };

        // criando ponteiro para resultado
        std::shared_ptr<Response> re;

        // rodando caso 1
        lmu.set(262'546, 8'277'039);
        ref.set(261'110, 8'277'879);
        ao = 2178;
        heading_sensor = 3159.9;

        re = computeBoi(lmu, ref, ao, heading_sensor);

        Response re_ref;
        re_ref.dist = 1663.64;
        re_ref.azim = 5339.13;
        re_ref.head = 3161.13;
        re_ref.diff = 1.23;

        assert_result(re, re_ref);

        print_result(re);


        // rodando caso 2
        lmu.set(260'852, 9'344'736);
        ref.set(258'818, 9'348'801);
        ao = 4154;
        heading_sensor = 1776.7;

        re = computeBoi(lmu, ref, ao, heading_sensor);

        re_ref.dist =  4545.48;
        re_ref.azim =  5927.43;
        re_ref.head =  1773.44;
        re_ref.diff = -3.26;

        assert_result(re, re_ref);

        print_result(re);

        printf("azimute_dan: %f\n", calc_azimute(lmu, ref));

        break;

        printf("Retornar ao início: 1- Sim / 2 - Nao\n");
        scanf("%d", &op);
    } while (op == 1);

    return 0;
}