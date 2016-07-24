#region SearchAThing.Solid, Copyright(C) 2016 Lorenzo Delana, License under MIT
/*
* Thirdy Part Components
* ======================
* SearchAThing.Solid project uses libraries from the following projects:
*
* - OpenCascade [LGPL-2.1](LICENSE.Thirdy/OpenCascade)
* - FreeImage [FreeImage Public License - Version 1.0](LICENSE.Thirdy/FreeImage/license-fi.txt)
* - FreeType [The FreeType Project LICENSE](LICENSE.Thirdy/Freetype/FTL.TXT)
* - GL2PS [GL2PS LICENSE - Version 2, November 2003](LICENSE.Thirdy/gl2ps/COPYING.GL2PS.txt)
* - Qt486 [LGPL 2.1](LICENSE.Thirdy/Qt486/LICENSE.LGPL.txt)
* - tbb [GPL](LICENSE.Thirdy/tbb/COPYING.txt) with [exceptions](https://www.threadingbuildingblocks.org/licensing)
* - tcltk [ActiveTcl Community License Agreement](LICENSE.Thirdy/tcltk/license-at8.6-thread.terms.txt)
* - vtk [Copyright (c) 1993-2008 Ken Martin, Will Schroeder, Bill Lorensen](LICENSE.Thirdy/vtk/Copyright.txt)
*
* SearchAThing.Solid
* ==================
* The MIT License(MIT)
* Copyright(c) 2016 Lorenzo Delana, https://searchathing.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/
#endregion

using SearchAThing.Solid.Wrapper;
using System;
using System.Text;

namespace SearchAThing.Solid.Example01
{

    class Program
    {

        static void Main(string[] args)
        {
            Console.WriteLine(Environment.CurrentDirectory);

            IGESControl_Controller.Init();
            var writer = new IGESControl_Writer("MM", 0);

            TopoDS_Face face1;
            {
                var p1 = new gp_Pnt(-10, 0, 0);
                var p2 = new gp_Pnt(20, 0, 0);
                var p3 = new gp_Pnt(-10, 10, 0);
                var p4 = new gp_Pnt(20, 10, 15);

                var edge12 = new BRepBuilderAPI_MakeEdge(p1, p2);
                var edge34 = new BRepBuilderAPI_MakeEdge(p3, p4);

                face1 = BRepFill.Face(edge12.Edge(), edge34.Edge());

                writer.AddShape(face1);
            }

            TopoDS_Face face2;
            {
                var p1 = new gp_Pnt(7.5, -5, -5);
                var p2 = new gp_Pnt(7.5, 15, -5);
                var p3 = new gp_Pnt(7.5, -5, 15);
                var p4 = new gp_Pnt(7.5, 15, 15);

                var edge12 = new BRepBuilderAPI_MakeEdge(p1, p2);
                var edge34 = new BRepBuilderAPI_MakeEdge(p3, p4);

                face2 = BRepFill.Face(edge12.Edge(), edge34.Edge());

                writer.AddShape(face2);
            }

            var s1 = new BRepLib_FindSurface(face1);
            var s2 = new BRepLib_FindSurface(face2);

            var a = new GeomAPI_IntSS(s1.Surface(), s2.Surface(), 1e-1);

            var C = a.Line(1);

            var edge = new BRepBuilderAPI_MakeEdge(C, C.FirstParameter(), C.LastParameter());

            var v1 = edge.Vertex1();
            var v2 = edge.Vertex2();

            var i1 = BRep_Tool.Pnt(v1);
            var i2 = BRep_Tool.Pnt(v2);
            
            Console.WriteLine($"Intersection line = {i1}-{i2}");

            writer.AddGeom(C.This());
            writer.ComputeModel();
            
            writer.Write("MyFile.igs");                        
        }

    }

}
