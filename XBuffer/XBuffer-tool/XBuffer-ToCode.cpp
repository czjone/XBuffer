#include "XBuffer-ToCode.hpp"

using namespace XBF;

ToCodeHandler::ToCodeHandler(std::shared_ptr< Analyzer> _analyzer)
    : analyzerPtr(_analyzer)
{
}

ToCodeHandler::~ToCodeHandler()
{
}