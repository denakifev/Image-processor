#include "../clparser/clparser.h"
#include "../filters_creator_factory/filters_creator_factory.h"

namespace image_processor {
class App {
protected:
    FiltersCreatorFactory factory_;
    CLParser parser_;
    int argc_;
    char** argv_;
    void InitFilters();

public:
    App(int argc, char* argv[]);
    void Run();
};

}  // namespace image_processor