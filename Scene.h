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

    ~Scene() = default;

    void setup() {
        // create some figures with certain parameters
        _actors.push_back(std::make_unique<Box>(0.0f, -750.0f, 3000.0f, 1500.0f));
        _actors[0]->setAngle(0.0f);

        _actors.push_back(std::make_unique<Circle>(-100.0f, 1500.0f, 50.0f));
        _actors[1]->setVel(0.0f, -0.1f);
        _actors[1]->setMass(5.0f);

        _actors.push_back(std::make_unique<Box>(100.0f, 300.0f, 500.0f, 400.0f));
        _actors[2]->setAngle(PI / 19);
    }

    void draw() {
        _actors[0]->collision(_actors[1].get());

        for (int i = 0; i < 1; i++) {
            //_actors[i]->lineReflection(glm::vec2(-1500.0f, -1500 * tanf(TEST_ANGLE)), glm::vec2(1500.0f, 1500 * tanf(TEST_ANGLE)));
            _actors[i]->applyForce(glm::vec2(0.0f, -Figure::grav) * _actors[i]->mass());
            _actors[i]->move();
            _actors[i]->rotate();
        }

        for (const auto& a : _actors)
            a->draw(*_objectsGroup);
    }


private:
    std::vector<std::unique_ptr<Figure>> _actors;
    ObjectsGroup* _objectsGroup;
    // todo: const ObjectsGroup & ?
};

#endif //MYPHYSICS_SCENE_H
