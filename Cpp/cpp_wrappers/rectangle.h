#ifndef RECTANGLE_H
#define RECTANGLE_H
class Rectangle{
public:				//interface functions:
	Rectangle(int ay1, int ax1, int ay2, int ax2);
	int  surf();
	int  getheight();
	int  getwidth();

private:			 //data:
	int y1, x1;
	int y2, x2;
};

//The constructor function:
inline Rectangle::Rectangle(int ay1, int ax1, int ay2, int ax2) : 
                                   y1(ay1), x1(ax1), y2(ay2), x2(ax2)
{
}

inline int Rectangle::getheight(){ return y2 - y1; }

inline int Rectangle::getwidth(){ return x2 - x1; }

inline int Rectangle::surf(){ return getheight() * getwidth(); }
#endif
