#ifndef SQREFOFUNC_H
#define SQREFOFUNC_H

class sqre {
private:
    double m_A, m_B, m_C;

public:
    sqre(double a, double b, double c) : m_A(a), m_B(b), m_C(c) {};
    double operator()(double x) {
        return m_A*x*x + m_B*x + m_C;
    }
};

#endif
