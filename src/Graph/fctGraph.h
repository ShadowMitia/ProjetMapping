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

void triVector(vector<ofPoint>* tab)
{
    ofPoint tmp;
    for(int i = 0; i < tab->size(); i++)            //On veut remplir la case i du tableau
    {
        for(int j = i+1; j < tab->size(); j++)      //On vérifie s'il n'y a pas de nombre inférieur
        {                                           //Dans les cases suivantes
            if(tab->at(j).x < tab->at(i).x)
            {
                tmp = tab->at(i);                     //Si c'est le cas on intervertit les cases
                tab->at(i) = tab->at(j);
                tab->at(j) = tmp;
            }
        }
    }
}

void recursionPoint(vector<ofPoint>*  ps, ofPoint pt1, ofPoint pt2, float y )
{
    float rand;
    do{
        rand = y + ofRandom(-1,4.0);
        
    }while (abs(rand-y) < 0.3);
    ofPoint pt3;
    pt3.set((pt1.x+pt2.x)/2, rand);
    ps->push_back(pt3);
    if (pt1.x - pt2.x > ofRandom(17,28)) {
        recursionPoint(ps,pt1, pt3 ,y);
        recursionPoint(ps,pt3, pt2, y);
        
    }
}


vector<ofPolyline> mouse(ofPolyline poly, ofPoint decalPtOri, float coef)
{
    
    vector<ofPolyline> mouses;
    //cout << " >>>>mouse Start<<<<"<< endl;
    poly.getVertices().erase(poly.getVertices().end()-1);
    
    for (int i =0; i<poly.getVertices().size(); i++) {
        ofPoint point1 , point2;
        point1 = poly.getVertices()[i % poly.getVertices().size()];
        point2 = poly.getVertices()[(i+1) % poly.getVertices().size()];
        
        if (getNorm(point1,point2).x > 0 && point1.distance(point2)>2) {
            ofPolyline tempMouse;
            ofPoint next , previous ;
            ofPoint left, right, leftNorm, rightNorm;
            
            
            previous = poly.getVertices()[(poly.getVertices().size() + i -1)%poly.getVertices().size()];
            next = poly.getVertices()[(i+2) % poly.getVertices().size()];
            if (previous.y < point1.y) {
                previous.y = point1.y + previous.y;
            }
            if(next.y < point2.y){
                next.y = point2.y + next.y;
            }
            
            leftNorm = getNorm(point1, previous);
            left = point1 -  leftNorm * decalPtOri;
            
            rightNorm = getNorm(point1, point2);
            right = point1 - rightNorm * decalPtOri;
            
            tempMouse.addVertex(left);
            tempMouse.bezierTo(left + leftNorm*coef, right + rightNorm*coef, right);
            
            
            leftNorm = getNorm(point2, point1);
            left = point2 -  leftNorm * decalPtOri;
            
            rightNorm = getNorm(point2, next);
            right = point2 - rightNorm * decalPtOri;
            
            tempMouse.addVertex(left);
            tempMouse.bezierTo(left + leftNorm*coef, right + rightNorm*coef, right);
            
            ofPoint p1,p2;
            p1 = tempMouse[0];
            p2 = tempMouse[tempMouse.size()-1];
            
            vector<ofPoint> ps;
            ps.push_back(tempMouse[0]);
            ps.push_back(tempMouse[tempMouse.size()-1]);
            
            recursionPoint(&ps, ps[0], ps[1], tempMouse[tempMouse.size()-1].y);
            triVector(&ps);
            float b = ofRandom(2);
            if (b>1) {
                b=1;
            }else{
                b=-1;
                //cout << " t " <<endl;
            }
            float y;
            for (int i= 0; i<ps.size()-1; i++) {
                float t = ofRandom(-2,0);
                while (abs(t-y)<0.5) {
                    t = ofRandom(-2,0);
                }
                y=t;
                tempMouse.addVertex(ps[i].x,ps[ps.size()-1].y - y);
                //cout << ps[i] << endl;
                float d = ps[i].distance(ps[i+1]);
                tempMouse.bezierTo(ofPoint(ps[i].x,ps[0].y - y + (b*d/2)),
                                   ofPoint(ps[i+1].x,ps[0].y - y + (b*d/2)),
                                   ofPoint(ps[i+1].x,ps[0].y - y));
                if (b==1) {
                    b=-1;
                }else{
                    b=1;
                }
                
            }
            
            //cout << "sortie" << endl;
            
            //tempMouse.close();
            mouses.push_back(tempMouse);
            
            
        }
        
        
        
    }
    return mouses;
}
