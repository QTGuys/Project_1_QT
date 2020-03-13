#include "gameobject.h"
#include "component.h"
#include "componentshape.h"
#include "componenttransform.h"


GameObject::GameObject()
{
    shape = new ComponentShape(this);
    transform = new ComponentTransform(this);

}
