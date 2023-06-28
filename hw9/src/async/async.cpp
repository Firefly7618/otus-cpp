#include "async/async.h"
#include "async/CommandContext.h"

#include <memory>
#include <string>

//TODO: remove
#include <iostream>

namespace async
{

std::unique_ptr<CommandContext> connect(std::size_t)
{
    return std::make_unique<CommandContext>();
}

void receive(std::unique_ptr<CommandContext> const& context, const char* data, std::size_t data_size)
{
    context->receive(data, data_size);
}

//TODO: remove
void disconnect(std::unique_ptr<CommandContext>&& )
{
    std::cout << "disconnect!!" << std::endl;
}

} // ns async