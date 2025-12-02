#include "3ac.hpp"
#include <iostream>
#include <ostream>

namespace leviathan
{

  void IRProgram::allocGlobals()
  {
    // Choose a label for each global
    for (auto pair : globals)
    {
      SemSymbol *sym = pair.first;
      SymOpd *opd = pair.second;
      std::string label = "global_" + sym->getName();
      opd->setMemoryLoc(label);
    }
  }

  void IRProgram::datagenX64(std::ostream &out)
  {
    out << ".data \n";
    // Output each global
    for (auto pair : globals)
    {

      SemSymbol *sym = pair.first;
      SymOpd *opd = pair.second;
      if (opd->isFunction() || !sym->getDataType()->asBasic() ||
          sym->getName() == "out" || sym->getName() == "in")
      {
        std::cout << "Skipping function global " << sym->getName() << "\n";
        continue;
      }
      out << opd->getMemoryLoc() << ": .quad 0" << "\n";
    }
    // Put this directive after you write out strings
    //  so that everything is aligned to a quadword value
    //  again
    out << ".align 8\n";
    out << ".section .note.GNU-stack,\"\",@progbits\n";
    out << ".globl main\n";
    out << ".text\n";
  }

  void IRProgram::toX64(std::ostream &out)
  {
    allocGlobals();
    datagenX64(out);
    
    getInitProc()->toX64(out);
    // Iterate over each procedure and codegen it
    for (Procedure *proc : *procs)
    {
      std::cout << "Generating x64 for proc " << proc->getName() << "\n";
      proc->toX64(out);
    }

    out << "movq $60, %rax\n";
    out << "movq $7, %rdi\n";
    out << "syscall\n";
    
    
  }

  void Procedure::allocLocals()
  {
    size_t offset = 16;
    for (auto pair : locals)
    {
      SemSymbol *sym = pair.first;
      SymOpd *opd = pair.second;
      offset += opd->getWidth();
      std::string loc = "-" + std::to_string(offset) + "(%rbp)";
      opd->setMemoryLoc(loc);
    }
    for (AuxOpd *tmp : temps)
    {
      offset += tmp->getWidth();
      std::string loc = "-" + std::to_string(offset) + "(%rbp)";
      tmp->setMemoryLoc(loc);
    }
  }

  void Procedure::toX64(std::ostream &out)
  {
    // Allocate all locals
    allocLocals();

    enter->codegenLabels(out);
    enter->codegenX64(out);
    out << "#Fn body " << myName << "\n";
    for (auto quad : *bodyQuads)
    {
      quad->codegenLabels(out);
      // out << "#" << quad->toString() << "\n";
      quad->codegenX64(out);
    }
    if (myName.compare("<init>") == 0)
    {
      out << "callq fun_main\n";
    }
    out << "#Fn epilogue " << myName << "\n";
    leave->codegenLabels(out);
    leave->codegenX64(out);
  }

  void Quad::codegenLabels(std::ostream &out)
  {
    if (labels.empty())
    {
      return;
    }

    size_t numLabels = labels.size();
    size_t labelIdx = 0;
    for (Label *label : labels)
    {
      out << label->getName() << ": ";
      if (labelIdx != numLabels - 1)
      {
        out << "\n";
      }
      labelIdx++;
    }
  }

  void BinOpQuad::codegenX64(std::ostream &out) { 
    
    switch (getOp())
    {
    case ADD64:
      src1->genLoadVal(out,A);
      src2->genLoadVal(out,B);
      out<<"addq %rax, %rbx\n";
      dst->genStoreVal(out,B);
      break;
    
    default:
      break;
    }
  
  }

  void UnaryOpQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void AssignQuad::codegenX64(std::ostream &out)
  {
    src->genLoadVal(out, A);
    dst->genStoreVal(out, A);
  }

  void ReadQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void WriteQuad::codegenX64(std::ostream &out)
  {
    // std::cout << mySrc->locString() << " and " << myDst->locString() << "\n";
    if ((getDst()->valString() == "[out]"))
    {
      if (getSrc()->isSymbol())
      {
        DataType const *srcType = getSrc()->getDataType();
        if (srcType->isInt())
        {
          out << mySrc->getMovOp()<< " " << getSrc()->getMemoryLoc() << ", %rdi\n";
          out << "callq printInt\n"; 
        }
        if(srcType->isBool())
        {
          out << mySrc->getMovOp()<< " " << getSrc()->getMemoryLoc() << ", %rdi\n";
          out << "callq printBool\n"; 
        }
        if(srcType->isString())
        {
          out << mySrc->getMovOp()<< " " << getSrc()->getMemoryLoc() << ", %rdi\n";
          out << "callq printString\n"; 
        }
      }
      else if (getSrc()->isInt())
      {
        out << mySrc->getMovOp()<< " $" << getSrc()->valString() << ", %rdi\n";
        out << "callq printInt\n";
      }
    }
  }

  void GotoQuad::codegenX64(std::ostream &out)
  {
    out << "jmp " << tgt->getName() << "\n";
  }

  void IfzQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void NopQuad::codegenX64(std::ostream &out) { out << "nop" << "\n"; }

  void CallQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void EnterQuad::codegenX64(std::ostream &out)
  {
    out << "pushq %rbp\n";
    out << "movq %rsp, %rbp\n";
    out << "addq $16,%rbp\n";
    size_t arSize = myProc->arSize();
    if (arSize > 0)
    {
      out << "subq $" << arSize << ", %rsp\n";
    }
  }

  void LeaveQuad::codegenX64(std::ostream &out)
  {
    out << "addq $" << myProc->arSize() << ", %rsp\n";
    out << "popq %rbp\n";
    out << "retq\n";
  }

  void SetArgQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void GetArgQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void SetRetQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void GetRetQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void LocQuad::codegenX64(std::ostream &out) { TODO(Implement me) }

  void SymOpd::genLoadVal(std::ostream &out, Register reg)
  {
    out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
  }

  void SymOpd::genStoreVal(std::ostream &out, Register reg)
  {
    out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
  }

  void SymOpd::genLoadAddr(std::ostream &out, Register reg)
  {
    TODO(Implement me if necessary)
  }

  void AuxOpd::genLoadVal(std::ostream &out, Register reg) { 
    out<< getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n"; 
  
  }

  void AuxOpd::genStoreVal(std::ostream &out, Register reg) { 
    out<< getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
  }
  void AuxOpd::genLoadAddr(std::ostream &out, Register reg) { TODO(Implement me) }

  void AddrOpd::genStoreVal(std::ostream &out, Register reg)
  {
    TODO(Implement me)
  }

  void AddrOpd::genLoadVal(std::ostream &out, Register reg) { TODO(Implement me) }

  void AddrOpd::genStoreAddr(std::ostream &out, Register reg)
  {
    TODO(Implement me)
  }

  void AddrOpd::genLoadAddr(std::ostream &out, Register reg)
  {
    TODO(Implement me)
  }

  void LitOpd::genLoadVal(std::ostream &out, Register reg)
  {
    out << getMovOp() << " $" << val << ", " << getReg(reg) << "\n";
  }

} // namespace leviathan
