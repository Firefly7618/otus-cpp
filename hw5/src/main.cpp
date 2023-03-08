#include "Controller.h"
#include "EditorView.h"
#include "EditorModel.h"
#include "Line.h"
#include "Point.h"

#include <memory>

int main()
{
    std::shared_ptr<EditorModel> model = std::make_shared<EditorModel>();
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(model);
    std::shared_ptr<EditorView> view = std::make_shared<EditorView>(model);

    model->add_observer(view);
    view->add_controller(controller);

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