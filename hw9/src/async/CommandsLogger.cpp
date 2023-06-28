#include "async/CommandsLogger.h"

namespace async
{

void CommandsLogger::log_commands(std::vector<std::string> const& commands)
{
    m_file_logger.log(commands);
    m_stdout_logger.log(commands);
}

} // namespace async