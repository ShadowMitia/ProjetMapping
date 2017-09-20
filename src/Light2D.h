//
//  Light2D.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//

#pragma once


#include "ofVec2f.h"
#include "ofColor.h"
#include "ofMesh.h"
#include "ofShader.h"


namespace ofx {
    
    
    class Light2D
    {
    public:
        typedef std::shared_ptr<Light2D> SharedPtr;
        typedef std::vector<SharedPtr> List;
        
        Light2D();
        virtual ~Light2D();
        
        virtual void update();
        virtual void draw();
        
        void setPosition(const ofVec3f& position);
        const ofVec3f& getPosition() const;
        
        void setAngle(float angle);
        float getAngle() const;
        
        void setViewAngle(float viewAngle);
        float getViewAngle() const;
        
        void setRadius(float radius);
        float getRadius() const;
        
        void setColor(const ofFloatColor& color);
        ofFloatColor getColor() const;
        
        float getBleed() const;
        void setBleed(float bleed);
        
        float getLinearizeFactor() const;
        void setLinearizeFactor(float linearizeFactor);
        
        static const float DEFAULT_RADIUS;
        static const float DEFAULT_RANGE;
        static const std::string DEFAULT_LIGHT_SHADER_FRAGMENT_SRC;
        
        static ofShader DEFAULT_LIGHT_SHADER;
        
    protected:
        ofVec3f _position;
        float _angle;
        
        float _radius;
        
        float _viewAngle;
        ofFloatColor _color;
        float _bleed;
        float _linearizeFactor;
        
        void createMesh() const;
        mutable bool _isMeshDirty;
        mutable ofMesh _mesh;
    };
    
    
} // namespace ofx
