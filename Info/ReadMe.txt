<type,value,(<...>,<...>,...)>

-<�����> = <��������>;
@<����> = <����>;
@<����> = <���>;
# <�����������>

-preprocessor  = false; # ��������� @source, ������ @source
-lexicial      = true;  # ��������� @source, ������ @source
-syntax        = true;  # ��������� @source, ������ @ast
-semantic      = false; # ��������� @ast,    ������ @ast
-optimiser     = false; # ��������� @ast,    ������ @ast
-dissyntax     = false; # ��������� @ast,    ������ @disast
-generator     = true;  # ��������� @ast,    ������ @asm
-disgenerator  = false; # ��������� @asm,    ������ @disasm
-translator    = true;  # ��������� @asm,    ������ @byte
-distranslator = false; # ��������� @byte,   ������ @disbyte
-jit           = false; # ��������� @byte,   ������ @jit
-disjit        = false; # ��������� @jit,    ������ @disjit


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

@source = <int main ()
           {
               int x = 5;

               out x;

               return 0;
           }>
