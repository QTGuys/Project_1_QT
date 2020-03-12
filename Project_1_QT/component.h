#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
    Component();
    Component(GameObject* go);
    GameObject* go;
};

#endif // COMPONENT_H
