/*
* Copyright (c) 2008-2009 Apple Inc. All rights reserved.
* Copyright (c) 2011 MLBA. All rights reserved.
*
* @MLBA_OPEN_LICENSE_HEADER_START@
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* @MLBA_OPEN_LICENSE_HEADER_END@
*/

#ifndef __DISPATCH_BASE__
#define __DISPATCH_BASE__

#ifndef __DISPATCH_INDIRECT__
#error "Please #include <xdispatch/dispatch.h> instead of this file directly."
#endif

typedef void (*dispatch_function_t)(void *);

#ifndef ATOMIC_INT

#ifdef __GNUC__
# define ATOMIC_INT unsigned int
#endif
#ifdef _MSC_VER
# if _MSC_VER >= 1600
#	define ATOMIC_INT unsigned int
# else
#	define ATOMIC_INT long
# endif
#endif

#endif

#ifdef __cplusplus
/*
 * Dispatch objects are NOT C++ objects. Nevertheless, we can at least keep C++
 * aware of type compatibility.
 */
typedef struct dispatch_object_s {
public:
	void* context;
	int type;
	unsigned int count;
	ATOMIC_INT lock;
	dispatch_function_t finalizer;
	void* target;
	char suspended;
    void* obj;
private:
	dispatch_object_s();
	dispatch_object_s(const dispatch_object_s &);
	void operator=(const dispatch_object_s &);
} *dispatch_object_t;
#else
typedef struct dispatch_object_s {
	void* context;
	int type;
	unsigned int count;
	ATOMIC_INT lock;
	dispatch_function_t finalizer;
	void* target;
	char suspended;
    void* obj;
} *dispatch_object_t;
#endif

#ifdef __cplusplus
#	define DISPATCH_DECL(name) typedef struct name##_s : public dispatch_object_s {} *name##_t
#else
#	define DISPATCH_DECL(name) typedef struct dispatch_object_s *name##_t
#endif


#endif