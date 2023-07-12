#pragma once

#ifdef CREATION_DEBUG
#define CREATION_ASSERT(x) if(!(x)) abort();
#define CREATION_ASSERT_MESSAGE(x, message) if(!(x)) abort();
#else
#define CREATION_ASSERT(x) (void)0;
#define CREATION_ASSERT_MESSAGE(x, message) (void)0;
#endif