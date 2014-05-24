#pragma once

#include "TimeSpanReference.h"
#include "DateTimeReference.h"

#ifdef USE_WIN32_INTEROP
#include "PointReference.h"
#include "RectReference.h"
#include "SizeReference.h"
#endif

#ifndef NOT_USE_VECTOR_EXTENSION
#define VECTOR_EXTENSION 1
#include "Collections/Deque.h"
#endif