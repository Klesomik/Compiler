<type,value,(<...>,<...>,...)>

-<опция> = <значение>;
@<файл> = <путь>;
# <комментарий>

-lexicial   = true;  // принимает @source, выдает @source
-syntax     = true;  // принимает @source, выдает @ast
-semantic   = false; // принимает @ast,    выдает @ast
-optimiser  = false; // принимает @ast,    выдает @ast
-disast     = false; // принимает @ast,    выдает @disast 
-generator  = true;  // принимает @ast,    выдает @asm
-disasm     = false; // принимает @asm,    выдает @disasm
-translator = true;  // принимает @asm,    выдает @byte
-disbyte    = false; // принимает @byte,   выдает @disbyte
-jit        = false; // принимает @byte,   выдает @jit
-disjit     = false; // принимает @jit,    выдает @disjit


@source  = "..//Materials//Source.txt";
@ast     = "..//Materials//AST.txt";
@disast  = "..//Materials//DisAST.txt";
@asm     = "..//Materials//Asm.txt";
@disasm  = "..//Materials//DisAsm.txt";
@byte    = "..//Materials//Byte.txt";
@disbyte = "..//Materials//DisByte.txt";
@jit     = "..//Materials//Jit.txt";
@disjit  = "..//Materials//DisJit.txt";
@log     = "..//Materials//Log.html";
@config  = "..//Materials//Config.txt";