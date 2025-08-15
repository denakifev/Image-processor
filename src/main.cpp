#include "app/app.h"
#include "error_message/error_message.h"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    image_processor::App app(argc, argv);
    try {
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << error_message::UndefinedMessage() << std::endl;
    }
    return 0;
}
