#pragma once

#include "PropertyPreprocessor.h"

#include "TimeSpanReference.h"
#include "DateTimeReference.h"

#ifdef USE_WIN32_INTEROP
#include "PointReference.h"
#include "RectReference.h"
#include "SizeReference.h"
#endif

#ifndef VECTOR_EXTENSION_USE
#define VECTOR_EXTENSION_USE 1
#endif

#ifdef VECTOR_EXTENSION_USE
#define VECTOR_EXTENSION 1
#include "Collections/Deque.h"
#endif