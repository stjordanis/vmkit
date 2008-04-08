//===------ N3ModuleProvider.cpp - LLVM Module Provider for N3 ------------===//
//
//                              N3
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <llvm/Module.h>
#include <llvm/ModuleProvider.h>

#include "mvm/JIT.h"

#include "Assembly.h"
#include "CLIJit.h"
#include "CLIString.h"
#include "N3ModuleProvider.h"

#include "VMClass.h"

using namespace llvm;
using namespace n3;


bool N3ModuleProvider::materializeFunction(Function *F, std::string *ErrInfo) {
  if (!F->empty()) return false;
  VMMethod* meth = functions->lookup(F);
  if (!meth) {
    // VT methods
    return false;
  } else {
    void* res = 
      mvm::jit::executionEngine->getPointerToGlobalIfAvailable(meth->methPtr);
    if (res == 0) {
      meth->classDef->aquire();
      res = 
        mvm::jit::executionEngine->getPointerToGlobalIfAvailable(meth->methPtr);
      if (res == 0) {
        CLIJit::compile(meth->classDef, meth);
        void* res = mvm::jit::executionEngine->getPointerToGlobal(meth->methPtr);
        meth->code = (mvm::Code*)((intptr_t)res - sizeof(intptr_t));
        meth->code->method()->definition(meth);
      }
      meth->classDef->release();
      meth->classDef->resolveStatic(true);
    }
    return false;
  }
}
