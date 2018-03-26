//
//  fctGraph.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 26/03/2018.
//
//

#pragma once
#include "ofMain.h"
#include "objGraph.h"

template <typename T>
void Append(std::vector<T>& a, const std::vector<T>& b)
{
    a.reserve(a.size() + b.size());
    a.insert(a.end(), b.begin(), b.end());
}

int aleatoir( vector<float> loi){
    int i = 0;
    float x = ofRandom(0, 1);
    float somme = 0;
    do{
        somme +=loi[i];
        i++;
    }while(somme < x && i < loi.size());
    return i;
}

ofPoint getNorm(ofPoint pOri,ofPoint p){
    ofPoint temp;
    temp = pOri - p;
    temp.normalize();
    return temp;
    
}

ofPolyline fctBezier(ofPolyline poly, ofPoint decalPtOri, float coef){
    ofPolyline polyBezier;
    
    poly.getVertices().erase(poly.getVertices().end()-1);
    
    for (int i =0; i<poly.getVertices().size(); i++) {
        ofPoint next , point , previous ;
        ofPoint left, right, leftNorm, rightNorm;
        
        previous = poly.getVertices()[(poly.getVertices().size() + i -1)%poly.getVertices().size()];
        point = poly.getVertices()[i % poly.getVertices().size()];
        next = poly.getVertices()[(i+1) % poly.getVertices().size()];
        if (point.distance(next) < 7 &&  getNorm(point, next).x == 1 ) {
            cout  << " mort " << getNorm(point, next).x<<  endl;
        }
        
        leftNorm = getNorm(point, previous);
        left = point -  leftNorm * decalPtOri;
        
        rightNorm = getNorm(point, next);
        right = point - rightNorm * decalPtOri;
        
        polyBezier.addVertex(left);
        polyBezier.bezierTo(left + leftNorm*coef, right + rightNorm*coef, right);
    }
    
    polyBezier.close();
    return polyBezier;
};

