#pragma region SearchAThing.Solid, Copyright(C) 2016 Lorenzo Delana, License under MIT
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
#pragma endregion

#pragma once

#include "Stdafx.h"

#include "BRepBuilderAPI_ModifyShape.h"
#include "TopoDS_Shape.h"
#include "gp_Trsf.h"

#include <TopoDS_Shape.hxx>
#include <BRepBuilderAPI_Transform.hxx>

using namespace System;

namespace SearchAThing::Solid::Wrapper {

	public ref class BRepBuilderAPI_Transform : BRepBuilderAPI_ModifyShape
	{

	public:
		BRepBuilderAPI_Transform(TopoDS_Shape^ shape, gp_Trsf^ tr, bool copy) : BRepBuilderAPI_ModifyShape()
		{
			m_Impl = new ::BRepBuilderAPI_Transform(*shape->ObjRef(), *tr->ObjRef(), copy);
		}

		~BRepBuilderAPI_Transform()
		{
			MyUtil::ReleaseInstance(this, &m_Impl);
		}

		TopoDS_Shape^ Shape()
		{
			::TopoDS_Shape *sh = new ::TopoDS_Shape();
			*sh = m_Impl->Shape();
			return gcnew TopoDS_Shape(sh);
		}

	protected:
		!BRepBuilderAPI_Transform()
		{
			MyUtil::ReleaseInstance(this, &m_Impl);
		}

	private:
		::BRepBuilderAPI_Transform *m_Impl;

	};

}
