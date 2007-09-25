/******************************************************************************
This file is part of a voxel plugin for OGRE
Copyright (C) 2006  David Williams

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
******************************************************************************/

#ifndef __SurfaceEdge_H__
#define __SurfaceEdge_H__

#include "OgrePrerequisites.h"

namespace Ogre
{
	class SurfaceVertex;
	typedef std::set<SurfaceVertex>::iterator SurfaceVertexIterator;
	class SurfaceTriangle;
	typedef std::set<SurfaceTriangle>::iterator SurfaceTriangleIterator;
	class SurfaceEdge;
	typedef std::set<SurfaceEdge>::iterator SurfaceEdgeIterator;

	class SurfaceEdge
	{
	public:
		SurfaceEdge(const SurfaceVertexIterator& targetToSet,const SurfaceVertexIterator& sourceToSet);

		friend bool operator == (const SurfaceEdge& lhs, const SurfaceEdge& rhs);
		friend bool operator < (const SurfaceEdge& lhs, const SurfaceEdge& rhs);

		//int crud;		

		SurfaceTriangleIterator triangle;

		

		//FIXME - could use boost::optional for this?

		std::string toString(void);

		bool isDegenerate(void);

		const SurfaceVertexIterator& getTarget(void);
		const SurfaceVertexIterator& getSource(void);
		const SurfaceEdgeIterator& getOtherHalfEdge(void);
		const SurfaceEdgeIterator& getPreviousHalfEdge(void);
		const SurfaceEdgeIterator& getNextHalfEdge(void);

		void setPreviousHalfEdge(const SurfaceEdgeIterator& previousHalfEdgeToSet);
		void setNextHalfEdge(const SurfaceEdgeIterator& nextHalfEdgeToSet);

		void pairWithOtherHalfEdge(const SurfaceEdgeIterator& otherHalfEdgeToPair);

	private:
		SurfaceVertexIterator target;
		SurfaceVertexIterator source;

		SurfaceEdgeIterator previousHalfEdge;
		SurfaceEdgeIterator nextHalfEdge;
		SurfaceEdgeIterator otherHalfEdge;
	};	
}

#endif
