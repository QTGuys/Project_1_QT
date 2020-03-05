#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class ComponentTransform;
class ComponentShape;


class GameObject
{
public:

    GameObject();

    void Render();

public:

    std::string name="";

    ComponentTransform* transform;
    ComponentShape* shape;

};

#endif // GAMEOBJECT_H
