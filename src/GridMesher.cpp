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
* @file GridMesher.cpp
* @author Claudio Lobos, Fabrice Jaillet
* @version 0.1
* @brief
**/

#include "GridMesher.h"

namespace Clobscode
{
	
	/***********************************************
	 This class will compute the starting grid elements
	 that will be split following the octree technique.
	 The Octree works fine over domains that present a 
	 bounding box that is close to a cube, but it produces
	 several unnecessary elements in stick like domains or
	 3D domains that are close to be in 2D.
	 In order to do so, it will find the smallest edge
	 of the bounding box and will use it in other axis
	 to build cubes.
	***********************************************/
	GridMesher::GridMesher(){

	}
	
	GridMesher::~GridMesher(){
		
	}
	
    void GridMesher::generatePoints(vector<double> &bounds,
                                    vector<double> &all_x,
                                    vector<double> &all_y){
		
        /*for (unsigned int i=0; i<bounds.size(); i++) {
            cout << "bounds " << i+1 << ": " << bounds[i] << endl;
        }*/
        
		list<double> deltas;
		deltas.push_back(bounds[3]-bounds[0]);
        deltas.push_back(bounds[4]-bounds[1]);
		deltas.sort();
		
		double step = *(deltas.begin());
		step*=1.01;
        
        //cout << "delta: " << bounds[3]-bounds[0] << endl;
		
		generateVector(all_x,bounds[0],bounds[3],step);
		generateVector(all_y,bounds[1],bounds[4],step);
	}
	
    void GridMesher::generateMesh(vector<double> &all_x,
                                  vector<double> &all_y,
                                  vector<MeshPoint> &points,
                                  vector<vector<unsigned int> > &elements){

        unsigned int nx = all_x.size();
        unsigned int ny = all_y.size();

        points.reserve(nx*ny);
        points.clear();
        std::cerr << "points.size()=" << points.size() << " points.capacity()=" << points.capacity() << std::endl;
        elements.reserve((nx-1)*(ny-1));
        elements.clear();
        std::cerr << "elements.size()=" << points.size() << " elements.capacity()=" << points.capacity() << std::endl;

        for (unsigned int j=0; j<ny; j++) {
            for (unsigned int k=0; k<nx; k++) {

                //create the point
                Point3D p3d (all_x[k],all_y[j],0.0);
                MeshPoint mp (p3d);
                points.push_back(mp);

                //create the element
                if ((k+2)>nx || (j+2)>ny) {
                    continue;
                }

                vector<unsigned int> epts (4,0);
                epts[0] = k+j*nx;  // lower left
                epts[1] = epts[0]+1; // lower right
                epts[2] = epts[1]+nx; // upper right
                epts[3] = epts[0]+nx; // uppper left

                elements.push_back(epts);
            }
        }
    }

	void GridMesher::generateVector(vector<double> &coords, double min,
									double max, double step){
		
		list<double> tmp_pos_coords, tmp_neg_coords;
        
		double delta = max-min;
		double middle = min+delta/2;
		
		int exp;
		double mantissa = frexp(delta/step,&exp);
		
		double pos_start, neg_start;
		
		if (mantissa<0.55 || mantissa>0.97) {
			pos_start=middle+step/2;
			neg_start=middle-step/2;
			tmp_pos_coords.push_back(pos_start);
			tmp_neg_coords.push_back(neg_start);
		}
		else {
			pos_start = neg_start = middle;
			tmp_pos_coords.push_back(pos_start);
		}
		
		while (pos_start<max) {
			pos_start+=step;
			tmp_pos_coords.push_back(pos_start);
			neg_start-=step;
			tmp_neg_coords.push_back(neg_start);
		} 
		
		coords.reserve(tmp_pos_coords.size()+tmp_neg_coords.size());
		coords.clear();
		
		list<double>::reverse_iterator riter;
		for (riter=tmp_neg_coords.rbegin(); riter!=tmp_neg_coords.rend(); ++riter) {
			coords.push_back(*riter);
		}
		list<double>::iterator iter;
		for (iter=tmp_pos_coords.begin(); iter!=tmp_pos_coords.end(); iter++) {
			coords.push_back(*iter);
		}
	}
}
