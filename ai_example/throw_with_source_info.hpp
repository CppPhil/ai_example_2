#pragma once
#include <fmt/format.h>

#include <pl/except.hpp>

#define AIE_THROW_WITH_SOURCE_INFO(ExceptionType, FormatString, ...) \
  PL_THROW_WITH_SOURCE_INFO(                                         \
    ExceptionType, fmt::format(FormatString, __VA_ARGS__))
