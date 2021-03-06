/*
    StructUtil.hpp
    ==============
        Struct utils implementation.
*/

#ifndef __PDBTOOLS_STRUCT_UTIL_HPP
#define __PDBTOOLS_STRUCT_UTIL_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <regex>
#include "StructBase.h"
#include "Constants.hpp"

namespace PDBTools
{

////////////////////////////////////////////////////////////////////////////////
// Using
////////////////////////////////////////////////////////////////////////////////

using std::string;
using std::stoi;
using std::vector;
using std::ostream;
using std::regex_search;
using std::regex_match;
using std::smatch;


////////////////////////////////////////////////////////////////////////////////
// operator<<
////////////////////////////////////////////////////////////////////////////////

template <typename SelfType>
inline ostream &operator<<(ostream &os, const __StructBase<SelfType> &structObj)
{
    return os << static_cast<const SelfType &>(structObj).str();
}


////////////////////////////////////////////////////////////////////////////////
// If An Atom Name is H
////////////////////////////////////////////////////////////////////////////////

inline bool IsH(const string &atomName)
{
    return regex_search(atomName, __H_RE);
}


////////////////////////////////////////////////////////////////////////////////
// Split CompNum To ResNum + ResIns
////////////////////////////////////////////////////////////////////////////////

inline void SplitCompNum(const string &compNumStr, int &resNum, string &resIns)
{
    smatch smatchObj;

    regex_match(compNumStr, smatchObj, __COMP_NUM_RE);

    resNum = stoi(smatchObj[1]);
    resIns = smatchObj[2];
}


////////////////////////////////////////////////////////////////////////////////
// Get Dump String Of Struct Object List
////////////////////////////////////////////////////////////////////////////////

template <typename SelfType>
string Dumpls(const vector<SelfType *> &structPtrList)
{
    string dumpStr;

    for (auto structPtr: structPtrList)
    {
        dumpStr += structPtr->Dumps();
    }

    return dumpStr;
}


////////////////////////////////////////////////////////////////////////////////
// Dump Struct Object List To PDB File
////////////////////////////////////////////////////////////////////////////////

template <typename SelfType>
void Dumpl(const vector<SelfType *> &structPtrList, const string &dumpFilePath,
    const string &fileMode = "w")
{
    FILE *fo = fopen(dumpFilePath.c_str(), fileMode.c_str());

    for (auto structPtr: structPtrList)
    {
        fprintf(fo, "%s", structPtr->Dumps().c_str());
    }

    fclose(fo);
}


////////////////////////////////////////////////////////////////////////////////
// Get Fasta String Of Struct Object List
////////////////////////////////////////////////////////////////////////////////

template <typename SelfType>
string DumpFastals(const vector<SelfType *> &structPtrList)
{
    string dumpStr;

    for (auto structPtr: structPtrList)
    {
        dumpStr += structPtr->fasta();
    }

    return dumpStr;
}


////////////////////////////////////////////////////////////////////////////////
// Dump Struct Object List To Fasta File
////////////////////////////////////////////////////////////////////////////////

template <typename SelfType>
void DumpFastal(const vector<SelfType *> &structPtrList, const string &dumpFilePath,
    const string &fileMode = "w")
{
    FILE *fo = fopen(dumpFilePath.c_str(), fileMode.c_str());

    for (auto structPtr: structPtrList)
    {
        fprintf(fo, "%s", structPtr->fasta().c_str());
    }

    fclose(fo);
}


}  // End namespace PDBTools


#endif  // __PDBTOOLS_STRUCT_UTIL_HPP
