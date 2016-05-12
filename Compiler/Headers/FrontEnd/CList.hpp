//DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code)
//DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code)
//DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code)

#define TO_STRING(prefix) { prefix + std::to_string (value.value) }

DEER_0 ( 0,        Digit, TO_STRING      (""), "darkgreen", "darkgreen",   "#98FF66",     "box", "rounded, filled", { give_Digit    (current, write); })
DEER_0 ( 1,         Name, TO_STRING ("name_"), "darkgreen", "darkgreen",   "#98FF66",     "box", "rounded, filled", { give_Name     (current, write); })
DEER_1 ( 2,        Block,             "block",     "black",     "black", "lightgrey", "ellipse", "rounded, filled", { give_Block    (current, write); })
DEER_1 ( 3,      DeclVar,          "decl_var",     "black",     "black", "lightgrey", "ellipse", "rounded, filled", { give_DeclVar  (current, write); })
DEER_1 ( 4,     DeclFunc,         "decl_func",     "black",     "black", "lightgrey", "ellipse", "rounded, filled", { give_DeclFunc (current, write); })
DEER_1 ( 5,         Call,              "call",     "black",     "black", "lightgrey", "ellipse", "rounded, filled", { give_Call     (current, write); })
DEER_1 ( 6,       Params,            "params",     "black",     "black", "lightgrey", "ellipse", "rounded, filled", {})
DEER_1 ( 7,        Equal,                "==",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 ( 8,     NotEqual,                "!=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "jne", "jn"); })
DEER_1 ( 9,          And,                "&&",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_And (current, write); })
DEER_1 (10,           Or,                "||",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Or  (current, write); })
DEER_1 (11,    LessEqual,                "<=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (12,    MoreEqual,                ">=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (13,          Mul,                 "*",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Add_Sub_Mul_Div_Mod (current, write, "mul"); })
DEER_1 (14,          Div,                 "/",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Add_Sub_Mul_Div_Mod (current, write, "div"); })
DEER_1 (15,          Mod,                "%%",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Add_Sub_Mul_Div_Mod (current, write, "mod"); })
DEER_1 (16,          Add,                 "+",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Add_Sub_Mul_Div_Mod (current, write, "add"); })
DEER_1 (17,          Sub,                 "-",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Add_Sub_Mul_Div_Mod (current, write, "sub"); })
DEER_1 (18,   Assingment,                 "=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Assignment (current, write); })
DEER_1 (19,         Less,                 "<",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (20,         More,                 ">",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
/*DEER_1 (21,         More,                 "&",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (22,         More,                 "|",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (23,          Xor,                 "^",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (23,          Xor,                 "!",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (23,          Xor,                 "~",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (23,          Xor,                "<<",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (23,          Xor,                ">>",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (24,     AddEqual,                "+=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (25,     SubEqual,                "-=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (26,     MulEqual,                "*=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (27,     DivEqual,                "/=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (28,     ModEqual,                "%=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (29,         More,                "&=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (30,         More,                "|=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (31,         More,                "^=",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (32,         More,                "++",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (33,         More,                "--",       "red",       "red",   "#FFCCC9",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })*/
DEER_1 (34,           If,                "if",      "blue",      "blue", "lightblue",     "box", "rounded, filled", { give_If (current, write); })
DEER_1 (35,        While,             "while",      "blue",      "blue", "lightblue",     "box", "rounded, filled", { give_While (current, write); })
DEER_1 (36,          Int,               "int",      "blue",      "blue", "lightblue",     "box", "rounded, filled", {})
DEER_1 (37,         Void,              "void",      "blue",      "blue", "lightblue",     "box", "rounded, filled", {})
DEER_1 (38,       Return,            "return",      "blue",      "blue", "lightblue",     "box", "rounded, filled", { give_Return (current, write); })
DEER_1 (39,        Break,             "break",      "blue",      "blue", "lightblue",     "box", "rounded, filled", {})
//DEER_1 (40,         More,          "continue",      "blue",      "blue", "lightblue",     "box", "rounded, filled", { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current, write, "je", "jne"); })
DEER_1 (40,        Begin,                 "{",     "white",     "white",     "white",     "box", "rounded, filled", {})
DEER_1 (41,          End,                 "}",     "white",     "white",     "white",     "box", "rounded, filled", {})
DEER_1 (42,   EndOfToken,                 ";",     "white",     "white",     "white",     "box", "rounded, filled", {})
DEER_1 (43,  OpenBracket,                 "(",     "white",     "white",     "white",     "box", "rounded, filled", {})
DEER_1 (44, CloseBracket,                 ")",     "white",     "white",     "white",     "box", "rounded, filled", {})
DEER_1 (45,         Else,              "else",     "white",     "white",     "white",     "box", "rounded, filled", {})
DEER_1 (46,        Comma,                 ",",     "white",     "white",     "white",     "box", "rounded, filled", {})
DEER_2 (47,      Include,           "include",    "purple",    "purple",    "purple",     "box", "rounded, filled", {})
DEER_2 (48,       Define,            "define",    "purple",    "purple",    "purple",     "box", "rounded, filled", {})
DEER_2 (49,        Undef,             "undef",    "purple",    "purple",    "purple",     "box", "rounded, filled", {})

#undef TO_STRING
