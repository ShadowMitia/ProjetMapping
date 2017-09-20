//
//  LightSystem2D.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//

#pragma once


#include "Light2D.h"
#include "Shape2D.h"
#include "ofTexture.h"
#include "ofShader.h"
#include "ofFbo.h"
#include "Constant.h"


namespace ofx {
    
    
    class LightSystem2D
    {
    public:
        LightSystem2D();
        virtual ~LightSystem2D();
        
        void setup();
        void update();
        void draw();
        
        void add(Light2D::SharedPtr light);
        void add(Shape2D::SharedPtr shape);
        
        void add(const Light2D::List& light);
        void add(const Shape2D::List& shape);
        
        void remove(Light2D::SharedPtr light);
        void remove(Shape2D::SharedPtr shape);
        
        void remove(const Light2D::List& lights);
        void remove(const Shape2D::List& shapes);
        
        void clearLights();
        void clearShapes();
        
        //void windowResized(ofResizeEventArgs& resize);
        
    protected:
        Light2D::List _lights;
        Shape2D::List _shapes;
        
        ofFbo _lightComp;
        ofFbo _sceneComp;
        
        static void makeMask(Light2D::SharedPtr light,
                             Shape2D::SharedPtr shape,
                             ofMesh& mask);
        
    };
    
    
} // namespace ofx
