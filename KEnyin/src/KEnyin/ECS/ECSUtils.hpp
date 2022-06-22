#include "KEnyin/ECS/EntityManager.fwd.hpp"

namespace KEnyin
{
   namespace ECSUtils
   {
       int _componentCounter = 0;

       template <class T>
       ComponentTypeID GetComponentTypeID()
       {
           static int _componentId = _componentCounter++;
           return _componentId;
       }
   }
}
