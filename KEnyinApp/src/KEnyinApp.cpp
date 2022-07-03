#include <KEnyin.hpp>
#include <KEnyin/Core/EntryPoint.hpp>

class KEnyinApp : public KEnyin::Application
{
public: 
    KEnyinApp() : Application("KEnyin App")
    {

    }

    ~KEnyinApp()
    {

    }
};

KEnyin::Application* KEnyin::CreateApplication()
{
    return new KEnyinApp();
}
