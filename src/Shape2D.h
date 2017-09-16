//
//  Shape2D.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//


#pragma once


#include "ofVec2f.h"
#include "ofColor.h"
#include "ofMesh.h"
#include "ofPolyline.h"


namespace ofx {
    
    
    class Shape2D
    {
    public:
        typedef std::shared_ptr<Shape2D> SharedPtr;
        typedef std::vector<SharedPtr> List;
        
        bool   bVisible;
        
        Shape2D();
        virtual ~Shape2D();
        
        void update();
        void draw();
        
        void setShape(const ofPolyline& shape);
        const ofPolyline& getShape() const;
        
        ofVec3f getCenter() const;
        
        void setColor(const ofFloatColor& color);
        ofFloatColor getColor() const;
        
    protected:
        ofVec3f _position;
        ofFloatColor _color;
        ofPolyline _shape;
        
        void createMesh() const;
        mutable bool _isMeshDirty;
        
        mutable ofMesh _mesh;
        
    };
    
    
} // namespace ofx
