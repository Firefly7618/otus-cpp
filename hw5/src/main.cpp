#include "Controller.h"
#include "EditorView.h"
#include "EditorModel.h"
#include "Line.h"
#include "Point.h"

#include <memory>

int main()
{
    std::shared_ptr<EditorModel> model;
    std::shared_ptr<Controller> controller(new Controller{model});

    std::shared_ptr<EditorView> view (new EditorView{model});
    view->add_controller(controller);

    model->add_observer(view);

    {
        std::shared_ptr<Point> p1 = std::make_shared<Point>(1,2);

        view->user_added_primitive(p1);
        view->user_deleted_primitive(p1);
    }

    {
        std::shared_ptr<Point> p1 = std::make_shared<Point>(1,2);
        std::shared_ptr<Point> p2 = std::make_shared<Point>(1,4);
        std::shared_ptr<Line> l1 = std::make_shared<Line>(*p1, *p2);

        view->user_added_primitive(l1);
    }

    return 0;
}