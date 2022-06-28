#pragma 

#include "KEnyin/SceneManagement/Entity.hpp"
#include "KEnyin/Core/Timestep.hpp"

namespace KEnyin
{
    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() {};

        template<typename T>
        T& GetComponent()
        {
            return _entity.GetComponent<T>();
        }
    protected:
        virtual void onCreate(){}
        virtual void onUpdate(Timestep ts){}
        virtual void onDestroy(){}
    private:
        Entity _entity;
        friend class Scene;
    };
}
