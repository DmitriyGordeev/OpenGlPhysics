#ifndef MYPHYSICS_SCENE_H
#define MYPHYSICS_SCENE_H

#include <iostream>
#include <vector>
#include <memory>
#include "Figure.h"
#include "Circle.h"
#include "Box.h"
#include "Math2D.h"


class Scene {
public:
    explicit Scene(ObjectsGroup* objectsGroup): _objectsGroup(objectsGroup) {}

    Scene(ObjectsGroup* objectsGroup, size_t alloc_size): _objectsGroup(objectsGroup) {
        _actors = std::vector<Figure*>(alloc_size);
    }

    ~Scene() {
        for (Figure* p : _actors)
            delete p;
    }

    void setup() {
        // create some figures with certain parameters
        _actors.push_back(new Box(0.0f, -750.0f, 3000.0f, 1500.0f));
        _actors[0]->setAngle(0.0f);

        _actors.push_back(new Circle(-100.0f, 1500.0f, 50.0f));
        _actors[1]->setVel(0.0f, -0.1f);
        _actors[1]->setMass(5.0f);

        _actors.push_back(new Box(100.0f, 300.0f, 500.0f, 400.0f));
        _actors[2]->setAngle(PI / 19);
    }

    void draw() {
        _actors[0]->collision(_actors[1]);

        for (int i = 0; i < 1; i++) {
            //_actors[i]->lineReflection(glm::vec2(-1500.0f, -1500 * tanf(TEST_ANGLE)), glm::vec2(1500.0f, 1500 * tanf(TEST_ANGLE)));
            _actors[i]->applyForce(glm::vec2(0.0f, -Figure::grav) * _actors[i]->mass());
            _actors[i]->move();
            _actors[i]->rotate();
        }

        // drawing all objects on the scene:
//        for (int i = 0; i < _actors.size(); i++)
//            _actors[i]->draw(_objectsGroup);

        for (const auto& a : _actors)
            a->draw(*_objectsGroup);
    }


private:
    std::vector<Figure*> _actors;
    ObjectsGroup* _objectsGroup;
    // todo: const ObjectsGroup & ?
};

#endif //MYPHYSICS_SCENE_H
