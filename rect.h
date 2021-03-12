#ifndef RECT_H
#define RECT_H

#include "vec2.h"
#include "shape.h"

/* simple data representation of a rectangle */
class Rect : public shape {
  public:
	Rect(double lX, double lY, double rX, double rY, color C, double deep) : shape{C, deep},
		upperL(lX, lY), lowerR(rX, rY) {}
	
	Rect(vec2(left), vec2(right), color C, double deep) : shape{C, deep},
		upperL(left), lowerR(right) {}
	Rect(vec2(left), double width, double height, color C, double deep) : shape{C, deep},
		upperL(left), lowerR(left.x()+width,left.y()+height) {}

	bool eval(double x, double y) override {
		if ((x >= upperL.x() && x <= lowerR.x()) && (y >= upperL.y() && y <= lowerR.y())) {
			return true;
		}
		return false;
	}

	//void setColor(color col) { inC = color{0, 0, col.b()}; }

	void translate(vec2 offset) {
		upperL += offset;
		lowerR += offset;
	}

	double getWidth() const {return lowerR.x() - upperL.x(); }
	double getHeight() const {return lowerR.y() - upperL.y(); }
	double getArea() const {return (lowerR.x() - upperL.x())*(lowerR.y() - upperL.y());}

	void setLCorner(vec2 inLCor) { upperL = inLCor; }
	void setRCorner(vec2 inRCor) {lowerR = inRCor;}

	void validate() override {
		try{
			std::string what_arg = "rect vert less zero";
			try{
				if( (upperL.x() < 0) || (upperL.y() < 0) || (lowerR.x() < 0) || (lowerR.y() < 0) ) {
					throw std::out_of_range(what_arg);
				}
			}
			catch(const std::out_of_range & e) {
				std::cout << e.what() << std::endl;
				this->setColor(color(0.0, 0.0, 0.0));
			}
			// not in correct order if upper left is less than lower right
			std::string what_arg_order = "rect order incorrect";
			if( ( upperL.y() > lowerR.y() )  ||   ( upperL.x() > lowerR.x() ) ) {
				throw std::out_of_range(what_arg_order); 
			}
		}
		catch(const std::out_of_range & e){
			std::cout << e.what() << std::endl;
			//this->setColor(color(255, 0.0 , 0.0));
			if( upperL.y() > lowerR.y() ) {
				//std::cout << "1st ULX " << upperL.x() << "ULY " << upperL.y() << "LRX " << lowerR.x() << "LRY " << lowerR.y() << std::endl;
				int temp = upperL.y();
				this->upperL.setY(lowerR.y());
				this->lowerR.setY(temp);
			//std::cout << "After 1st ULX " << upperL.x() << "ULY " << upperL.y() << "LRX " << lowerR.x() << "LRY " << lowerR.y() << std::endl;	
			}
			if (( upperL.x() > lowerR.x() ) ) {
			//std::cout << "2nd ULX " << upperL.x() << "ULY " << upperL.y() << "LRX " << lowerR.x() << "LRY " << lowerR.y() << std::endl;
				
				int temp = upperL.x();
				this->upperL.setX(lowerR.x());
				this->lowerR.setX(temp);
			}
			//std::cout << "After 2nd ULX " << upperL.x() << "ULY " << upperL.y() << "LRX " << lowerR.x() << "LRY " << lowerR.y() << std::endl;
			color red = color(255.0, 0.0, 0.0);
			this->setColor(red);
			//std::cout << this->getInC().r() << " " << this->getInC().g() << " " << this->getInC().b() << std::endl; 
		}
	}


  private:
	vec2 upperL;
	vec2 lowerR;

};

#endif
