#ifndef Cell_header
#define Cell_header 
using namespace std;
namespace BrnSlmz{
	class Cell
	{
		public:
			char getX()const{ return x;};
			void setX(char _x_){ x=_x_;};
			int getY()const{ return y;};
			void setY(char _y_){ y=_y_;};
			char getState()const{ return type;};
			void setState(char _type_){ type=_type_;}
		private:
			int y;
			char x,type;
	};
}
#endif