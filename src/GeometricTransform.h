/*
 <Mix-mesher: region type. This program generates a mixed-elements 2D mesh>

 Copyright (C) <2013,2018>  <Claudio Lobos> All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/lgpl.txt>
 */
/**
* @file GeometricTransform.h
* @author Claudio Lobos, Fabrice Jaillet
* @version 0.1
* @brief
**/

#ifndef GeometricTransform_h
#define GeometricTransform_h 1

#include <iostream>
#include <math.h>
#include "Point3D.h"
#include "Polyline.h"
#include <vector>
#include <list>

using Clobscode::Point3D;
using std::list;
using std::vector;
using Clobscode::Polyline;

namespace Clobscode
{	
    double toDegrees(double rad);
    double toRadians(double deg);

	class GeometricTransform{
		
	public:
		
		GeometricTransform();
		
		GeometricTransform(Point3D &centroid, double &xAxisRotationAngle,
                           double &yAxisRotationAngle, double &zAxisRotationAngle);
				
		virtual ~GeometricTransform();
        
        //to implement
        virtual void rotatePolyline(Polyline &ply);
        
        virtual void rotatePolylineInverse(Polyline &ply);
        
        virtual void calculateAnglesAndCentroid(Polyline &tm);
        
        virtual void apply(Point3D &p);
        
        virtual void applyInverse(Point3D &p);
		
		virtual void setCentroid(Point3D &p);
        
        virtual void setXAxis(double x);
        
        virtual void setYAxis(double y);
        
        virtual void setZAxis(double z);
        
        virtual Point3D &getCentroid();
        
        virtual double &getXAxis();
        
        virtual double &getYAxis();
        
        virtual double &getZAxis();
        
        virtual bool Default();

	protected:
		
		Point3D centroid;
        double x,y,z;
		
	};
	
    inline void GeometricTransform::setCentroid(Point3D &p) {
        centroid = p;
    }
    
    inline void GeometricTransform::setXAxis(double x) {
        this->x = x;
    }

    inline void GeometricTransform::setYAxis(double y) {
        this->y = y;
    }
    
    inline void GeometricTransform::setZAxis(double z) {
        this->z = z;
    }
    
    inline Point3D &GeometricTransform::getCentroid() {
        return centroid;
    }
    
    inline double &GeometricTransform::getXAxis() {
        return x;
    }
    
    inline double &GeometricTransform::getYAxis() {
        return y;
    }
    
    inline double &GeometricTransform::getZAxis() {
        return z;
    }
    
    inline bool largestNormal (Point3D n1, Point3D n2){
		 return (n1.Norm() > n2.Norm()); 
	}

    inline bool GeometricTransform::Default() {
        return x==0 && y==0 && z==0;
    }

}
#endif
