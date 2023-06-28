#pragma once

#include "async/CommandContext.h"

#include <memory>

namespace async
{

std::unique_ptr<CommandContext> connect(std::size_t block_size);

void receive(std::unique_ptr<CommandContext> const& context, const char* data, std::size_t data_size);

void disconnect(std::unique_ptr<CommandContext>&& context);

} // ns async