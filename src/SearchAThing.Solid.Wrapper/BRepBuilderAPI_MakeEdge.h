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

#pragma once

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>

using namespace System;

#include "gp_pnt.h"
#include "BRepBuilderAPI_MakeShape.h"
#include "TopoDS_Vertex.h"
#include "TopoDS_Edge.h"
#include "Geom_Curve.h"

namespace SearchAThing::Solid::Wrapper {

	public ref class BRepBuilderAPI_MakeEdge : BRepBuilderAPI_MakeShape
	{

	public:
		BRepBuilderAPI_MakeEdge(gp_Pnt ^p1, gp_Pnt ^p2) : BRepBuilderAPI_MakeShape(NULL)
		{
			m_Impl = new ::BRepBuilderAPI_MakeEdge(*p1->ObjRef(), *p2->ObjRef());
		}

		BRepBuilderAPI_MakeEdge(Geom_Curve^ c, double p1, double p2) : BRepBuilderAPI_MakeShape(NULL)
		{
			m_Impl = new ::BRepBuilderAPI_MakeEdge(c->ObjRef(), p1, p2);
		}

		~BRepBuilderAPI_MakeEdge()
		{
			delete m_Impl;
		}

		TopoDS_Edge^ Edge()
		{
			auto tmp = new ::TopoDS_Edge();
			*tmp = m_Impl->Edge();
			return gcnew TopoDS_Edge(tmp);
		}

		TopoDS_Vertex^ Vertex1()
		{
			auto tmp = new ::TopoDS_Vertex();
			*tmp = m_Impl->Vertex1();
			return gcnew TopoDS_Vertex(tmp);
		}

		TopoDS_Vertex^ Vertex2()
		{
			auto tmp = new ::TopoDS_Vertex();
			*tmp = m_Impl->Vertex2();
			return gcnew TopoDS_Vertex(tmp);
		}

	protected:
		!BRepBuilderAPI_MakeEdge()
		{
			delete m_Impl;
		}

	private:
		::BRepBuilderAPI_MakeEdge *m_Impl;

	};

}
