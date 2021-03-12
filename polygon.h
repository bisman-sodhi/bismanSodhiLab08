#ifndef POLY_H
#define POLY_H
#include <vector>
#include "vec2.h"
#include "color.h"
#include "shape.h"
#include <algorithm>

/* simple data representation of an implicit ellipse */
class Polygon : public shape {
  public:

	Polygon(vec2 v1, double d, color C) : shape{C,d} {
		theVerts.push_back(v1);
	}

	bool eval(double x, double y) override;
	void addVert(vec2 inV) { theVerts.push_back(inV); }
	bool concave();

	double getMinX() {
		return min_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.x() < r.x();
      				}
      			)->x();
	}

	double getMinY() {
		vec2 min 
      		= *min_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.y() < r.y();
      				}
      			);
      	return min.y();
	}

	double getMaxX() {
		vec2 max 
      		= *max_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.x() < r.x();
      				}
      			);
      	return max.x();
	}

	double getMaxY(){
		vec2 max 
      		= *max_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.y() < r.y();
      				}
      			);
      	return max.y();
	}

	void validate() override {
		try{
			try{
				std::string what_arg = "polygon vert less zero"; 
				for(auto a : theVerts){
					if( (a.x() < 0) || (a.y() < 0) ){
						throw std::out_of_range(what_arg) ;
					}
				}
			}
			catch(const std::out_of_range & e){
				std::cout << e.what() << std::endl;
				this->setColor(color(0.0, 0.0, 0.0));
			}
			if (this->concave()){
				std::string what_arg_concave = "polygon concave";
				throw std::out_of_range(what_arg_concave);

			}
		}
		catch(const std::out_of_range & e) {
			std::cout << e.what() << std::endl;

			vec2 lastone = vec2(theVerts.back().x(), theVerts.back().y());
			while (theVerts.size() != 2){
				theVerts.pop_back(); 
			}
			theVerts.push_back(lastone);
			this->setColor(color(255, 0.0, 0.0));
		}	
	}

  private:
	std::vector<vec2> theVerts;

};

#endif
