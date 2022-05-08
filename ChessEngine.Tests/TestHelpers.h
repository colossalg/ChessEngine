#pragma once

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
    using namespace ChessEngine;

    template<> static std::wstring ToString<TranspositionTableEntry>(const class TranspositionTableEntry& entry)
    {
        std::wostringstream wss;
        wss << "TranspositionTableEntry { "
            << entry.GetHash() << ", "
            << (entry.IsInitialized() ? "true, " : "false, ")
            << entry.GetDepth() << ", "
            << entry.GetEval()
            << " }";

        return wss.str();
    }
}