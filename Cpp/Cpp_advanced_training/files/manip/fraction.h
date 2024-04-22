#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <iomanip>
#include <stdexcept>


class Fraction {
public:
	Fraction(int nm=0, int dnm=1) : nominator(nm), denominator(dnm) {
          if (denominator==0) throw std::domain_error("fraction with denominator 0!");
	  normalize();
        }

	std::ostream& printfloat(std::ostream& os) const {
		
		return os << double(nominator)/denominator;
	}

	std::ostream& printfraction(std::ostream& os) const {
		int w=os.width(0);           // total width
		int nomwdth=(w-1)/2;         // width nominator part
		int denomwdth=(w-1)/2 + (w-1)%2; // width denominator part
		
        using std::setw;
		return os << setw(nomwdth) << nominator 
			<< '/' << setw(denomwdth) << denominator;
	}

	std::ostream& printentirefraction(std::ostream& os) const {
		int w=os.width(0);           // total width
		int entwdth=(w-2)/3;         // width entire part
		int nomwdth=(w-2)/3;         // width nominator part
		int denomwdth=(w-2)/3 + (w-2)%2; // width denominator part

                using std::setw;
		return os << setw(entwdth) << nominator/denominator 
                        << ':' << setw(nomwdth) << nominator % denominator
			<< '/' << setw(denomwdth) << denominator;
	}
private:
	int nominator, denominator;

	void normalize() {
		int g=gcd(nominator, denominator);
		nominator/=g;
		denominator/=g;
	}

	static int gcd(int a, int b) {
		if (b == 0) return a;
		return gcd(b, a%b);
	}

};
#endif
