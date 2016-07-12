#include "stdafx.h"

#include <gp_Pnt.hxx>

#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>

int main()
{
	IGESControl_Controller::Init();
	IGESControl_Writer ICW("MM", 0);

	gp_Pnt p1(0, 0, 0);
	gp_Pnt p2(10, 0, 0);
	gp_Pnt p3(10, 10, 0);
	gp_Pnt p4(0, 10, 0);

	auto edge12 = BRepBuilderAPI_MakeEdge(p1, p2);
	auto edge23 = BRepBuilderAPI_MakeEdge(p2, p3);
	auto edge34 = BRepBuilderAPI_MakeEdge(p3, p4);
	auto edge41 = BRepBuilderAPI_MakeEdge(p4, p1);

	auto aWire = BRepBuilderAPI_MakeWire(edge12, edge23, edge34, edge41);

	auto face = BRepBuilderAPI_MakeFace(aWire);
	ICW.AddShape(face);
	

	ICW.ComputeModel();
	
	auto OK = ICW.Write("MyFile.igs");

	return 0;
}

