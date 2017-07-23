//
//  Shape2D.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//


#include "Shape2D.h"
#include "ofGraphics.h"
#include "ofAppRunner.h"


namespace ofx {
    
    
    Shape2D::Shape2D():
    _color(.5, 1),
    _isMeshDirty(true)
    {
    }
    
    
    Shape2D::~Shape2D()
    {
    }
    
    
    void Shape2D::update()
    {
        if (_isMeshDirty)
        {
            createMesh();
        }
    }
    
    
    void Shape2D::draw()
    {
        _mesh.draw();
    }
    
    
    void Shape2D::setShape(const ofPolyline& shape)
    {
        _shape = shape;
        _position = _shape.getCentroid2D();
    }
    
    
    const ofPolyline& Shape2D::getShape() const
    {
        return _shape;
    }
    
    
    ofVec3f Shape2D::getCenter() const
    {
        return _position;
    }
    
    
    void Shape2D::setColor(const ofFloatColor& color)
    {
        _color = color;
        _isMeshDirty = true;
    }
    
    
    ofFloatColor Shape2D::getColor() const
    {
        return _color;
    }
    
    
    void Shape2D::createMesh() const
    {
        _mesh.clear();
        _mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
        ofVec3f position(_position);
        
        _mesh.addVertex(position);
        
        ofFloatColor color(_color);
        color = color * .8;
        
        _mesh.addColor(_color);
        
        for (std::size_t i = 0; i < _shape.size(); ++i)
        {
            _mesh.addVertex(_shape[i]);
            _mesh.addColor(color);
        }
        
        _mesh.addVertex(_shape[0]);
        _mesh.addColor(color);
        
        _isMeshDirty = false;
    }
    
    
} // namespace ofx
