#include "Basic/CommonInclude.h"
#include "Lexer/Token.h"
#include "Lexer/Parser.h"
#include "AST/AST.h"
#include "CodeGen/CodeGen.h"

using namespace llvm;
using namespace llvm::sys;

/*
 * ===----------------------------------------------------------------------===
 *  Top-Level parsing and JIT Driver
 * ===----------------------------------------------------------------------===
 */
static void InitializeModuleAndPassManager()
{
    /*  Open a new module. */
    TheModule = std::make_unique<Module>("my cool jit", TheContext);
}

static void HandleDefinition()
{
    if (auto FnAST = ParseDefinition())
    {
        if (auto *FnIR = FnAST->codegen())
        {
            fprintf(stderr, "Read function definition:");
            FnIR->print(errs());
            fprintf(stderr, "\n");
        }
    }
    else
    {
        /*  Skip token for error recovery. */
        getNextToken();
    }
}

static void HandleExtern()
{
    if (auto ProtoAST = ParseExtern())
    {
        if (auto *FnIR = ProtoAST->codegen())
        {
            fprintf(stderr, "Read extern: ");
            FnIR->print(errs());
            fprintf(stderr, "\n");
            FunctionProtos[ProtoAST->getName()] = std::move(ProtoAST);
        }
    }
    else
    {
        /*  Skip token for error recovery. */
        getNextToken();
    }
}

static void HandleTopLevelExpression()
{
    /*  Evaluate a top-level expression into an anonymous function. */
    if (auto FnAST = ParseTopLevelExpr())
    {
        FnAST->codegen();
    }
    else
    {
        /*  Skip token for error recovery. */
        getNextToken();
    }
}

/* / top ::= definition | external | expression | ';' */
static void MainLoop()
{
    while (true)
    {
        switch (CurTok)
        {
            case tok_eof:
                return;
            case ';': /*  ignore top-level semicolons. */
                getNextToken();
                break;
            case tok_def:
                HandleDefinition();
                break;
            case tok_extern:
                HandleExtern();
                break;
            default:
                HandleTopLevelExpression();
                break;
        }
    }
}

/*
 * ===----------------------------------------------------------------------===
 *  "Library" functions that can be "extern'd" from user code.
 * ===----------------------------------------------------------------------===
 */
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/* / putchard - putchar that takes a double and returns 0. */
extern "C" DLLEXPORT double putchard(double X)
{
    fputc((char)X, stderr);
    return 0;
}

/* / printd - printf that takes a double prints it as "%f\n", returning 0. */
extern "C" DLLEXPORT double printd(double X)
{
    fprintf(stderr, "%f\n", X);
    return 0;
}

/*
 *  ===----------------------------------------------------------------------===
 *  Main driver code.
 * ===----------------------------------------------------------------------===
 */
int main() {
    /*
     * Install standard binary operators.
     *  1 is lowest precedence.
     */
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40; /*  highest. */

    /*  Prime the first token. */
    fprintf(stderr, "ready> ");
    getNextToken();

    InitializeModuleAndPassManager();

    /*  Run the main "interpreter loop" now. */
    MainLoop();

    /*  Initialize the target registry etc. */
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    auto TargetTriple = sys::getDefaultTargetTriple();
    TheModule->setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    /*
     *  Print an error and exit if we couldn't find the requested target.
     *  This generally occurs if we've forgotten to initialise the
     *  TargetRegistry or we have a bogus target triple.
     */
    if (!Target)
    {
        errs() << Error;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TheTargetMachine =
        Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    TheModule->setDataLayout(TheTargetMachine->createDataLayout());

    auto Filename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OpenFlags::F_None);

    if (EC)
    {
        errs() << "Could not open file: " << EC.message();
        return 1;
    }

    legacy::PassManager pass;
    auto FileType = TargetMachine::CGFT_ObjectFile;

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
    {
        errs() << "TheTargetMachine can't emit a file of this type";
        return 1;
    }

    pass.run(*TheModule);
    dest.flush();

    outs() << "Wrote " << Filename << "\n";

    return 0;
}
