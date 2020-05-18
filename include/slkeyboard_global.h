#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SLKEYBOARD_LIB)
#  define SLKEYBOARD_EXPORT Q_DECL_EXPORT
# else
#  define SLKEYBOARD_EXPORT Q_DECL_IMPORT
# endif
#else
# define SLKEYBOARD_EXPORT
#endif
