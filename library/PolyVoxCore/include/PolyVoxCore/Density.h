/*******************************************************************************
Copyright (c) 2005-2009 David Williams

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution. 	
*******************************************************************************/

#ifndef __PolyVox_Density_H__
#define __PolyVox_Density_H__

#include "PolyVoxCore/DefaultMarchingCubesController.h" //We'll specialise the controller contained in here

#include "PolyVoxImpl/TypeDef.h"

#include <cassert>
#include <limits>

#undef min
#undef max

namespace PolyVox
{
	/// This class represents a voxel storing only a density.
	////////////////////////////////////////////////////////////////////////////////
	/// Detailed description...
	////////////////////////////////////////////////////////////////////////////////

	// int32_t template parameter is a dummy, required as the compiler expects to be able to declare an
	// instance of VoxelType::MaterialType without knowing that VoxelType doesn't actually have a material.
	template <typename Type>
	class Density
	{
	public:
		//We expose DensityType and MaterialType in this way so that, when code is
		//templatised on voxel type, it can determine the underlying storage type
		//using code such as 'VoxelType::DensityType value = voxel.getDensity()'
		//or 'VoxelType::MaterialType value = voxel.getMaterial()'.
		typedef Type DensityType;
		typedef int32_t MaterialType; //Shouldn't define this one...

		/// Constructor
		Density() : m_uDensity(0) {}

		/// Copy constructor
		Density(DensityType uDensity) : m_uDensity(uDensity) {}

		/// Copy constructor with cast
		template <typename CastType> explicit Density(const Density<CastType>& density) throw()
		{
			m_uDensity = static_cast<Type>(density.getDensity());
		}

		bool operator==(const Density& rhs) const throw()
		{
			return (m_uDensity == rhs.m_uDensity);
		};

		bool operator!=(const Density& rhs) const throw()
		{
			return !(*this == rhs);
		}

		// For densities we can supply mathematical operators which behave in an intuitive way.
		// In particular the ability to add and subtract densities is important in order to
		// apply an averaging filter. The ability to divide by an integer is also needed for
		// this same purpose.
		Density<Type>& operator+=(const Density<Type>& rhs)
		{
			m_uDensity += rhs.m_uDensity;
			return *this;
		}

		Density<Type>& operator-=(const Density<Type>& rhs)
		{
			m_uDensity -= rhs.m_uDensity;
			return *this;
		}

		Density<Type>& operator/=(uint32_t rhs)
		{
			m_uDensity /= rhs;
			return *this;
		}

		DensityType getDensity() const throw() { return m_uDensity; }
		void setDensity(DensityType uDensity) { m_uDensity = uDensity; }

		static DensityType getMaxDensity() throw() { return (std::numeric_limits<DensityType>::max)(); } 
		static DensityType getMinDensity() throw() { return (std::numeric_limits<DensityType>::min)(); }

	private:
		DensityType m_uDensity;
	};

	template <typename Type>
	Density<Type> operator+(const Density<Type>& lhs, const Density<Type>& rhs) throw()
	{
		Density<Type> result = lhs;
		result += rhs;
		return result;
	}

	template <typename Type>
	Density<Type> operator-(const Density<Type>& lhs, const Density<Type>& rhs) throw()
	{
		Density<Type> result = lhs;
		result -= rhs;
		return result;
	}

	template <typename Type>
	Density<Type> operator/(const Density<Type>& lhs, uint32_t rhs) throw()
	{
		Density<Type> result = lhs;
		result /= rhs;
		return result;
	}

	// These are the predefined density types. The 8-bit types are sufficient for many purposes (including
	// most games) but 16-bit and float types do have uses particularly in medical/scientific visualisation.
	typedef Density<uint8_t> Density8;
	typedef Density<uint16_t> Density16;
	typedef Density<uint32_t> Density32;
	typedef Density<float> DensityFloat;

	/**
	 * This is a specialisation of DefaultMarchingCubesController for the Density voxel type
	 */
	template <typename Type>
	class DefaultMarchingCubesController< Density<Type> >
	{
	public:
		typedef Type DensityType;
		typedef float MaterialType;

		DefaultMarchingCubesController(void)
		{
			// Default to a threshold value halfway between the min and max possible values.
			m_tThreshold = (Density<Type>::getMinDensity() + Density<Type>::getMaxDensity()) / 2;
		}

		DefaultMarchingCubesController(DensityType tThreshold)
		{
			m_tThreshold = tThreshold;
		}

		DensityType convertToDensity(Density<Type> voxel)
		{
			return voxel.getDensity();
		}

		MaterialType convertToMaterial(Density<Type> voxel)
		{
			return 1;
		}

		DensityType getThreshold(void)
		{			
			return m_tThreshold;
		}

	private:
		DensityType m_tThreshold;
	};
}

#endif //__PolyVox_Density_H__
