//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012-2013, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of Image Engine Design nor the names of any
//       other contributors to this software may be used to endorse or
//       promote products derived from this software without specific prior
//       written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#ifndef IECOREHOUDINI_SOPSCENECACHESOURCE_H
#define IECOREHOUDINI_SOPSCENECACHESOURCE_H

#include "SOP/SOP_Node.h"

#include "IECore/SceneCache.h"
#include "IECore/MatrixTransform.h"

#include "IECoreHoudini/SceneCacheNode.h"

namespace IECoreHoudini
{

/// SOP for loading an IECore::SceneCache from disk
class SOP_SceneCacheSource : public SceneCacheNode<SOP_Node>
{
	public :

		SOP_SceneCacheSource( OP_Network *net, const char *name, OP_Operator *op );
		virtual ~SOP_SceneCacheSource();
		
		static const char *typeName;
		
		static OP_Node *create( OP_Network *net, const char *name, OP_Operator *op );
		static OP_TemplatePair *buildParameters();
		
		static PRM_Name pShapeFilter;
		static PRM_Name pAttributeFilter;
		
		static PRM_Default shapeFilterDefault;
		static PRM_Default attributeFilterDefault;
		
		static PRM_ChoiceList shapeFilterMenu;
		
		static void buildShapeFilterMenu( void *data, PRM_Name *menu, int maxSize, const PRM_SpareData *, const PRM_Parm * );
		
	protected :
	
		virtual OP_ERROR cookMySop( OP_Context &context );
		virtual IECore::ObjectPtr modifyObject( IECore::Object *object, std::string &name, const UT_StringMMPattern &attributeFilter );
		virtual IECore::ObjectPtr transformObject( IECore::Object *object, Imath::M44d transform );
	
	private :
		
		void loadObjects( const IECore::SceneCache *cache, Imath::M44d transform, Space space, const UT_StringMMPattern &shapeFilter, const UT_StringMMPattern &attributeFilter );
		IECore::MatrixTransformPtr matrixTransform( Imath::M44d t );

};

} // namespace IECoreHoudini

#endif // IECOREHOUDINI_SOPSCENECACHESOURCE_H