#include "KEditor/EditorLayer.hpp"
#include <KEnyin.hpp>
#include <KEnyin/Core/EntryPoint.hpp>

namespace KEnyin
{
    namespace KEditor
    {
        class KEditor : public Application
        {
        public:
            KEditor() : Application("KEnyin")
            {
                pushLayer(new EditorLayer());
            }

            ~KEditor()
            {

            }
        };
    }

    Application* CreateApplication()
    {
        return new KEditor::KEditor();
    }
}
