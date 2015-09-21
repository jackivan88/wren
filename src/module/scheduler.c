#include <stdlib.h>
#include <string.h>

#include "uv.h"

#include "scheduler.h"
#include "wren.h"
#include "vm.h"

// This method resumes a fiber that is suspended waiting on an asynchronous
// operation. The first resumes it with zero arguments, and the second passes
// one.
static WrenValue* resume;
static WrenValue* resumeWithArg;

void schedulerCaptureMethods(WrenVM* vm)
{
  resume = wrenGetMethod(vm, "scheduler", "Scheduler", "resume_(_)");
  resumeWithArg = wrenGetMethod(vm, "scheduler", "Scheduler", "resume_(_,_)");
}

void schedulerResume(WrenValue* fiber)
{
  wrenCall(getVM(), resume, NULL, "v", fiber);
  wrenReleaseValue(getVM(), fiber);
}

void schedulerResumeDouble(WrenValue* fiber, double value)
{
  wrenCall(getVM(), resumeWithArg, NULL, "vd", fiber, value);
  wrenReleaseValue(getVM(), fiber);
}

void schedulerResumeString(WrenValue* fiber, const char* text)
{
  wrenCall(getVM(), resumeWithArg, NULL, "vs", fiber, text);
  wrenReleaseValue(getVM(), fiber);
}

void schedulerReleaseMethods()
{
  if (resume != NULL) wrenReleaseValue(getVM(), resume);
  if (resumeWithArg != NULL) wrenReleaseValue(getVM(), resumeWithArg);
}