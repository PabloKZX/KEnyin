#pragma once

#define ADD_SERVICE(__CLASS__, __MEMBER__) ADD_SERVICE_NAME(__CLASS__, __MEMBER__, __CLASS__)

#define ADD_SERVICE_NAME(__CLASS__, __MEMBER__, __NAME__)               \
private:                                                                \
    __CLASS__* __MEMBER__ = nullptr;                                    \
                                                                        \
public:                                                                 \
    bool has##__NAME__() const                                          \
    {                                                                   \
        return __MEMBER__ != nullptr;                                   \
    }                                                                   \
                                                                        \
    __CLASS__& get##__NAME__()                                          \
    {                                                                   \
        KECheck(has##__NAME__(), "Service {0} not found", #__NAME__);   \
        return *__MEMBER__;                                             \
    }                                                                   \
                                                                        \
    const __CLASS__& get##__NAME__() const                              \
    {                                                                   \
        KECheck(has##__NAME__(), "Service {0} not found", #__NAME__);   \
        return *__MEMBER__;                                             \
    }

namespace KEnyin
{
    class Application;

    namespace Editor
    {
        class Editor;
    }
}

namespace KEnyin
{
    class ServiceLocator final
    {
    private:
        ADD_SERVICE(Application, _application)
        ADD_SERVICE_NAME(Editor::Editor, _editor, Editor)

    public:
        ~ServiceLocator() = default;

        ServiceLocator(const ServiceLocator&) = delete;
        ServiceLocator(ServiceLocator&&) = delete;
        ServiceLocator& operator=(const ServiceLocator&) = delete;
        ServiceLocator& operator=(ServiceLocator&&) = delete;

        static ServiceLocator& get();

        void loadServices(Application* application);
        void clearServices();

    private:
        ServiceLocator();
    };
}


