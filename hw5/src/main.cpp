#include "Controller.h"
#include "EditorView.h"

#include <memory>

int main()
{
    std::shared_ptr<EditorModel> model;
    Controller(model, std::unique_ptr<EditorView>(new EditorView(model)));

    return 0;
}