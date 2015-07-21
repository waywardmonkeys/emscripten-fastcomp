//===- X86MCNaClExpander.h --------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the X86MCNaClExpander class, the X86 specific
// subclass of MCNaClExpander.
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_MC_X86MCNACLEXPANDER_H
#define LLVM_MC_X86MCNACLEXPANDER_H
#include "llvm/ADT/SmallVector.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCNaClExpander.h"

namespace llvm {
class MCStreamer;
class MCSubtargetInfo;
namespace X86 {

class X86MCNaClExpander : public MCNaClExpander {
public:
  X86MCNaClExpander() {}

  bool expandInst(const MCInst &Inst, MCStreamer &Out,
                  const MCSubtargetInfo &STI) override;

private:
  bool Guard = false; // recursion guard
  SmallVector<MCInst, 4> Prefixes;
  void emitReturn(const MCInst &Inst, MCStreamer &Out,
                  const MCSubtargetInfo &STI);
  void doExpandInst(const MCInst &Inst, MCStreamer &Out,
                    const MCSubtargetInfo &STI);
};
}
}
#endif
