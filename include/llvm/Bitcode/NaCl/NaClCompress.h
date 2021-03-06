//===-- NaClCompress.h - Bitcode (abbrev) compression ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Defines API's to read in a PNaCl bitcode buffer, and write it out to
// a corresponding ostream.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_BITCODE_NACL_NACLCOMPRESS_H
#define LLVM_BITCODE_NACL_NACLCOMPRESS_H

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm {

/// Analyzes and (optionally) compresses a bitcode file.
class NaClBitcodeCompressor {
public:
  /// The flags to use when compressing.
  struct CompressFlags {
    CompressFlags()
        : TraceGeneratedAbbreviations(false),
          ShowValueDistributions(false),
          ShowAbbrevLookupTries(false),
          ShowAbbreviationFrequencies(false),
          RemoveAbbreviations(false) {}
    bool TraceGeneratedAbbreviations;
    bool ShowValueDistributions;
    bool ShowAbbrevLookupTries;
    bool ShowAbbreviationFrequencies;
    bool RemoveAbbreviations;
  };
  CompressFlags Flags;

  NaClBitcodeCompressor() {}

  /// Analyzes bitcode in MemBuf for applicable abbreviations for
  /// compression. Output is the stream to write data associated with
  /// "show" flags (ShowValueDistributions, ShowAbbrevLookupTries, //
  /// and ShowAbbreviationFrequencies).
  bool analyze(MemoryBuffer *MemBuf, raw_ostream &Output = outs());

  /// Reads bitcode in MemBuf, finds new applicable abbreviations for
  /// compression, and then rewrites out the bitcode out using these
  /// new abbreviations to BitcodeOutput. Returns true iff successful.
  /// ShowOutput captures analysis output generated by "show" flags
  /// (see method analyze).
  bool compress(MemoryBuffer *MemBuf, raw_ostream &BitcodeOutput,
                raw_ostream &ShowOutput = errs());
};

} // namespace llvm

#endif // LLVM_BITCODE_NACL_NACLCOMPRESS_H
