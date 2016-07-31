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

using SearchAThing.Sci;
using SearchAThing.Solid.Wrapper;

namespace SearchAThing.Solid
{

    public static partial class Toolkit
    {

        public static TopoDS_Face FromEdges(Line3D line1, Line3D line2)
        {
            return BRepFill.Face(
                new BRepBuilderAPI_MakeEdge(line1.From.gp_Pnt(), line1.To.gp_Pnt()).Edge(),
                new BRepBuilderAPI_MakeEdge(line2.From.gp_Pnt(), line2.To.gp_Pnt()).Edge());
        }

    }

    public static partial class Extensions
    {

        public static UVBounds UVBounds(this TopoDS_Face face)
        {
            var umin = 0.0;
            var umax = 0.0;
            var vmin = 0.0;
            var vmax = 0.0;

            BRepTools.UVBounds(face, ref umin, ref umax, ref vmin, ref vmax);

            return new UVBounds(umin, umax, vmin, vmax);
        }

        public static TopoDS_Face Offset(this TopoDS_Face face, double off, Vector3D sideRefPt = null)
        {
            var surface = face.Surface();
            var props = surface.LProp_SLProps(face.UVBounds());
            var normal = props.Normal();

            var offFact = 1.0;

            if (sideRefPt != null)
            {
                if (!sideRefPt.Normalized().Concordant(Constants.NormalizedLengthTolerance, normal.ToVector3D()))
                    offFact *= -1;
            }

            return new BRepOffset_Offset(face, off * offFact).Face();
        }

        public static gp_Dir ComputeNormal(this TopoDS_Face face)
        {
            double umin = 0, umax = 0, vmin = 0, vmax = 0;
            BRepTools.UVBounds(face, ref umin, ref umax, ref vmin, ref vmax);
            var surface = BRep_Tool.Surface(face);
            var props = new GeomLProp_SLProps(surface, umin, vmin, 1.0, 1e-1);
            return props.Normal();
        }

        public static Geom_Surface Surface(this TopoDS_Face face)
        {
            return new BRepLib_FindSurface(face).Surface();
        }

        public static FaceIntersectionLineResult IntersectLine(this TopoDS_Face face, TopoDS_Face other, double tol)
        {
            var s1 = face.Surface();
            var s2 = other.Surface();
            var a = new GeomAPI_IntSS(s1, s2, tol);
            var C = a.Line(1);
            var edge = new BRepBuilderAPI_MakeEdge(C, C.FirstParameter(), C.LastParameter());
            var v1 = edge.Vertex1();
            var v2 = edge.Vertex2();
            var i1 = BRep_Tool.Pnt(v1);
            var i2 = BRep_Tool.Pnt(v2);
            return new FaceIntersectionLineResult(C, new Line3D(i1.ToVector3D(), i2.ToVector3D()));
        }

    }

    public class FaceIntersectionLineResult
    {
        public Geom_Curve Curve { get; private set; }
        public Line3D IntersectionLine { get; private set; }

        public FaceIntersectionLineResult(Geom_Curve curve, Line3D intersectionLine)
        {
            Curve = curve;
            IntersectionLine = intersectionLine;
        }
    }

}
