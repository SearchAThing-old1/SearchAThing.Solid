#include "stdafx.h"

#include <gp_Pnt.hxx>
#include <gp_Lin.hxx>

#include <STEPControl_Controller.hxx>
#include <STEPControl_Writer.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <GeomAPI_IntSS.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <Geom_Line.hxx>
#include <TopOpeBRep_ShapeIntersector.hxx>
#include <BRepFill_FaceAndOrder.hxx>
#include <BRepTools.hxx>
#include <BRepTools_Modifier.hxx>
#include <BRepBuilderAPI_NurbsConvert.hxx>
#include <BRepLib_FindSurface.hxx>
#include <BRepFill.hxx>
#include <BRep_TVertex.hxx>
#include <Geom_Curve.hxx>
#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <BRep_Tool.hxx>

int main()
{
	STEPControl_Controller::Init();
	STEPControl_Writer STW;

	IGESControl_Controller::Init();
	IGESControl_Writer ICW("MM", 0);

	TopoDS_Face face1;
	TopoDS_Face face2;

	{
		gp_Pnt p1(0, 0, 0);
		gp_Pnt p2(10, 0, 0);
		gp_Pnt p3(0, 10, 0);
		gp_Pnt p4(10, 10, 5);

		auto edge12 = BRepBuilderAPI_MakeEdge(p1, p2);
		auto edge23 = BRepBuilderAPI_MakeEdge(p2, p3);
		auto edge34 = BRepBuilderAPI_MakeEdge(p3, p4);
		auto edge41 = BRepBuilderAPI_MakeEdge(p4, p1);

		face1 = BRepFill::Face(edge12, edge34);

		ICW.AddShape(face1);
	}

	{
		gp_Pnt p1(7.5, -5, -5);
		gp_Pnt p2(7.5, 15, -5);
		gp_Pnt p3(7.5, -5, 15);
		gp_Pnt p4(7.5, 15, 15);

		auto edge12 = BRepBuilderAPI_MakeEdge(p1, p2);
		auto edge23 = BRepBuilderAPI_MakeEdge(p2, p3);
		auto edge34 = BRepBuilderAPI_MakeEdge(p3, p4);
		auto edge41 = BRepBuilderAPI_MakeEdge(p4, p1);

		face2 = BRepFill::Face(edge12, edge34);

		ICW.AddShape(face2);
	}

	auto s1 = BRepLib_FindSurface(face1);
	auto s2 = BRepLib_FindSurface(face2);

	auto a = GeomAPI_IntSS(s1.Surface(), s2.Surface(), 1e-1);

	printf("IsDone=%d\n", a.IsDone());
	printf("lines = %d\n", a.NbLines());

	Handle(Geom_Curve) C = a.Line(1);
	BRepBuilderAPI_MakeEdge edge(C, C->FirstParameter(), C->LastParameter());

	auto v1 = edge.Vertex1();
	auto v2 = edge.Vertex2();

	auto p1 = BRep_Tool::Pnt(v1);
	auto p2 = BRep_Tool::Pnt(v2);

	printf("Intersection line = (%f,%f,%f)-(%f,%f,%f)",
		p1.X(), p1.Y(), p1.Z(),
		p2.X(), p2.Y(), p2.Z());

	ICW.AddGeom(C);
	ICW.ComputeModel();

	auto OK = ICW.Write("MyFile.igs");

	return 0;
}

