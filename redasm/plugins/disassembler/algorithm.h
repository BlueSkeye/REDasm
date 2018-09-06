#ifndef DISASSEMBLERALGORITHM_H
#define DISASSEMBLERALGORITHM_H

#include <stack>
#include <set>
#include "../../redasm.h"
#include "../assembler/assembler.h"

namespace REDasm {

class DisassemblerAlgorithm
{
    public:
        enum: u32 { OK, SKIP, FAIL };

    protected:
        DisassemblerAlgorithm(DisassemblerAPI* disassembler, AssemblerPlugin* assembler);

    public:
        u32 disassemble(const Buffer &buffer, InstructionPtr& instruction);
        void push(address_t address);
        bool hasNext() const;
        address_t next();

    protected:
        virtual void onDisassembled(const InstructionPtr& instruction, u32 result);
        virtual void checkOperands(const InstructionPtr& instruction);

    private:
        bool isDisassembled(address_t address) const;

    protected:
        DisassemblerAPI* m_disassembler;
        AssemblerPlugin* m_assembler;

    private:
        std::set<address_t> m_disassembled;
        std::stack<address_t> m_pending;
};

} // namespace REDasm

#endif // DISASSEMBLERALGORITHM_H