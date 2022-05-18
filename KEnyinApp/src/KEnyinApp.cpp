#include <KEnyin.hpp>

class KEnyinApp : public KEnyin::Application
{
public: 
    KEnyinApp()
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