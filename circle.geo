//+
//Circle

Include "circle.dat";

// Create 5 points to define the circle
//          x   y  z  mesh
Point(1) = {cx, cy, cz, msh};	// This point defines the center of the circle
//+
Point(2) = {P2x, P2y, P2z, msh};
//+
Point(3) = {P3x, P3y, P3z, msh};
//+
Point(4) = {P4x, P4y, P4z, msh};
//+
Point(5) = {P5x, P5y, P5z, msh};
//+
// Create circumference by creating circle arcs connecting the points
//          {First, Center, Last}
Circle(1) = {2,     1,      3};
//+
Circle(2) = {3,     1,      4};
//+
Circle(3) = {4,     1,      5};
//+
Circle(4) = {5,     1,      2};
//+
// Create surface
Line Loop(1) = {1, 2, 3, 4};
//+
//Plane Surface(1) = {1};

// Name the boundaries
//Physical Surface("internal") = {1};
Physical Line("TopRight") 	= {1};
Physical Line("TopLeft") 	= {2};
Physical Line("BottomLeft") 	= {3};
Physical Line("BottomRight") 	= {4};
