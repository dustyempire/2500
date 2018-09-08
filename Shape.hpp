
#ifndef MTRN3500_SHAPE_H
#define MTRN3500_SHAPE_H

#define RECT_PRISM 0
#define TRI_PRISM 1
#define TRAP_PRISM 2
#define CYL 3 


// Abstract class
class Shape {

public:
	Shape();
	Shape(double x_, double y_, double z_);
	Shape(double x_, double y_, double z_, double rotation_);
	virtual ~Shape();

	virtual void draw() = 0;

	double getX();
	double getY();
	double getZ();
	double getRotation();

	void setX(double x_);
	void setY(double y_);
	void setZ(double z_);
	void setRotation(double rotation_);

	void setPosition(double x_, double y_, double z_);

	void positionInGL();
	void setColorInGL();

	double getRed();
	double getGreen();
	double getBlue();
	void setColor(float red_, float green_, float blue_);
	int getShapeType();

protected:
	double x, y, z;               // position
	double rotation;              // heading of the object in the horizontal plane (degrees)
	float red, green, blue;       // colour of object
	int shapeType;
};

#endif // for MTRN3500_SHAPE_H
