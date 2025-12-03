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
        // std::cout << "Skipping function global " << sym->getName() << "\n";
        continue;
      }
      out << opd->getMemoryLoc() << ": .quad 0" << "\n";
    }
    for (auto pair : strings)
    {
      LitOpd *opd = pair.first;
      std::string val = pair.second;
      out << opd->valString() << ": .asciz " << val << "\n";
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
    out << "movq $0, %rdi\n";
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
    for (auto form : formals)
    {
      offset += form->getWidth();
      std::string loc = "-" + std::to_string(offset) + "(%rbp)";
      form->setMemoryLoc(loc);
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

  void BinOpQuad::codegenX64(std::ostream &out)
  {

    switch (getOp())
    {
    case ADD64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "addq %rax, %rbx\n";
      dst->genStoreVal(out, B);
      break;
    case SUB64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "subq %rbx, %rax\n";
      dst->genStoreVal(out, A);
      break;
    case MULT64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "imulq %rbx, %rax\n";
      dst->genStoreVal(out, A);
      break;
    case DIV64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "cqto\n";
      out << "idivq %rbx\n";
      dst->genStoreVal(out, A);
      break;
    case EQ64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "cmpq %rbx, %rax\n";
      out << "movq $0, %rax\n";
      out << "sete %al\n";
      dst->genStoreVal(out, A);
      break;
    case NEQ64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "cmpq %rbx, %rax\n";
      out << "movq $0, %rax\n";
      out << "setne %al\n";
      dst->genStoreVal(out, A);
      break;
    case LT64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "cmpq %rbx, %rax\n";
      out << "movq $0, %rax\n";
      out << "setl %al\n";
      dst->genStoreVal(out, A);
      break;
    case GT64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "cmpq %rbx, %rax\n";
      out << "movq $0, %rax\n";
      out << "setg %al\n";
      dst->genStoreVal(out, A);
      break;
    case LTE64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "cmpq %rbx, %rax\n";
      out << "movq $0, %rax\n";
      out << "setle %al\n";
      dst->genStoreVal(out, A);
      break;
    case GTE64:
      src1->genLoadVal(out, A);
      src2->genLoadVal(out, B);
      out << "cmpq %rbx, %rax\n";
      out << "movq $0, %rax\n";
      out << "setge %al\n";
      dst->genStoreVal(out, A);
      break;

    default:
      break;
    }
  }

  void UnaryOpQuad::codegenX64(std::ostream &out)
  {
    switch (getOp())
    {
    case NEG64:
      src->genLoadVal(out, A);
      out << "negq %rax\n";
      dst->genStoreVal(out, A);
      break;
    case NOT64:
      src->genLoadVal(out, A);
      out << "cmpq $0, %rax\n";
      out << "movq $0, %rax\n";
      out << "sete %al\n";
      dst->genStoreVal(out, A);
      break;
    default:
      break;
    }
  }

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
          out << mySrc->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %rdi\n";
          out << "callq printInt\n";
        }
        if (srcType->isBool())
        {
          out << mySrc->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %rdi\n";
          out << "callq printBool\n";
        }
        if (srcType->isString())
        {
          out << mySrc->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %rdi\n";
          out << "callq printString\n";
        }
      }
      else if (getSrc()->isInt())
      {
        out << mySrc->getMovOp() << " $" << getSrc()->valString() << ", %rdi\n";
        out << "callq printInt\n";
      }
      else if (getSrc()->isString())
      {
        out << mySrc->getMovOp() << " $" << getSrc()->valString() << ", %rdi\n";
        out << "callq printString\n";
      }
      else if (getSrc()->isBool())
      {
        out << mySrc->getMovOp() << " $" << getSrc()->valString() << ", %rdi\n";
        out << "callq printBool\n";
      }
    }
  }

  void GotoQuad::codegenX64(std::ostream &out)
  {
    out << "jmp " << tgt->getName() << "\n";
  }

  void IfzQuad::codegenX64(std::ostream &out)
  {
    getCnd()->genLoadVal(out, C);
    out << "cmpq $0, %rcx\n";
    out << "je " << getTarget()->getName() << "\n";
  }

  void NopQuad::codegenX64(std::ostream &out) { out << "nop" << "\n"; }

  void CallQuad::codegenX64(std::ostream &out)
  {
    out << "callq fun_" << sym->getName() << "\n";
    int stackneeded = (numArgs > 6) ? (numArgs - 6) * 8 : 0;
    if (stackneeded > 0){
      out << "addq $" << stackneeded << ", %rsp\n";
    }
  }

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

  void SetArgQuad::codegenX64(std::ostream &out)
  {
    switch (getIndex())
    {
    case 1:
      if (getSrc()->isLiteral())
      {
        out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", %rdi\n";
        break;
      }
      out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %rdi\n";
      break;
    case 2:
      if (getSrc()->isLiteral())
      {
        out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", %rsi\n";
        break;
      }
      out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %rsi\n";
      break;
    case 3:
      if (getSrc()->isLiteral())
      {
        out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", %rdx\n";
        break;
      }
      out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %rdx\n";
      break;
    case 4:
      if (getSrc()->isLiteral())
      {
        out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", %rcx\n";
        break;
      }
      out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %rcx\n";
      break;
    case 5:
      if (getSrc()->isLiteral())
      {
        out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", %r8\n";
        break;
      }
      out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %r8\n";
      break;
    case 6:
      if (getSrc()->isLiteral())
      {
        out << getSrc()->getMovOp() << " $" << getSrc()->valString() << ", %r9\n";
        break;
      }
      out << getSrc()->getMovOp() << " " << getSrc()->getMemoryLoc() << ", %r9\n";
      break;

    default:
      getSrc()->genLoadVal(out, A);
      out << "pushq %rax\n";
      break;
    }
  }

  void GetArgQuad::codegenX64(std::ostream &out)
  {
    switch (getIndex())
    {
    case 1:
      out << opd->getMovOp() << " %rdi, " << opd->getMemoryLoc() << "\n";
      break;
    case 2:
      out << opd->getMovOp() << " %rsi, " << opd->getMemoryLoc() << "\n";
      break;
    case 3:
      out << opd->getMovOp() << " %rdx, " << opd->getMemoryLoc() << "\n";
      break;
    case 4:
      out << opd->getMovOp() << " %rcx, " << opd->getMemoryLoc() << "\n";
      break;
    case 5:
      out << opd->getMovOp() << " %r8, " << opd->getMemoryLoc() << "\n";
      break;
    case 6:
      out << opd->getMovOp() << " %r9, " << opd->getMemoryLoc() << "\n";
      break;

    default:
    out<<opd->getMovOp()<<" "<< (8 * (numArgs - getIndex())) << "(%rbp), %rbx\n"; 
    out<<opd->getMovOp()<<" %rbx, " << opd->getMemoryLoc() << "\n";

      break;
    }
  }

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

  void AuxOpd::genLoadVal(std::ostream &out, Register reg)
  {
    out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
  }

  void AuxOpd::genStoreVal(std::ostream &out, Register reg)
  {
    out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
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
