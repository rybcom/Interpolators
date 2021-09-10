#pragma once

#define cmp_floating(x,y)  static_cast<bool>(abs(x - y) > 0.0001 ? false : true)

#define pure_virtual virtual

#ifdef _DEBUG

#define assert(expression,msg ) \
if (expression == false)	\
{							\
		__debugbreak();		\
}							\

#else

#define assert(expression ) 

#endif // _DEBUG

