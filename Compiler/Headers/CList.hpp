//DEER(id, name, word, fontcolor, color, fillcolor, shape, style)

DEER ( 0,        Digit, {           to_string (value.value); }, "darkgreen", "darkgreen",   "#98FF66", "box", "rounded, filled")
DEER ( 1,         Name, { "name_" + to_string (value.value); }, "darkgreen", "darkgreen",   "#98FF66", "box", "rounded, filled")
DEER ( 2,        Block,                                "block",      "grey",      "grey", "lightgrey", "box", "rounded, filled")
DEER ( 3,      DeclVar,                             "decl_var",      "grey",      "grey", "lightgrey", "box", "rounded, filled")
DEER ( 4,     DeclFunc,                            "decl_func",      "grey",      "grey", "lightgrey", "box", "rounded, filled")
DEER ( 5,        Equal,                                   "==",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER ( 6,     NotEqual,                                   "!=",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER ( 7,          And,                                   "&&",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER ( 8,           Or,                                   "||",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER ( 9,    LessEqual,                                   "<=",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (10,    MoreEqual,                                   ">=",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (11,           If,                                   "if",      "blue",      "blue", "lightblue", "box", "rounded, filled")
DEER (12,         Else,                                 "else",     "white",     "white",     "white", "box", "rounded, filled")
DEER (13,        While,                                "while",      "blue",      "blue", "lightblue", "box", "rounded, filled")
DEER (14,          Int,                                  "int",      "blue",      "blue", "lightblue", "box", "rounded, filled")
DEER (15,         Void,                                 "void",      "blue",      "blue", "lightblue", "box", "rounded, filled")
DEER (16,        Comma,                                    ",",     "white",     "white",     "white", "box", "rounded, filled")
DEER (17,      Include,                             "#include",    "purple",    "purple",    "purple", "box", "rounded, filled")
DEER (18,       Define,                              "#define",    "purple",    "purple",    "purple", "box", "rounded, filled")
DEER (19,  OpenBracket,                                    "(",     "white",     "white",     "white", "box", "rounded, filled")
DEER (20, CloseBracket,                                    ")",     "white",     "white",     "white", "box", "rounded, filled")
DEER (21,          Mul,                                    "*",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (22,          Div,                                    "/",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (23,          Mod,                                   "%%",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (24,          Add,                                    "+",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (25,          Sub,                                    "-",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (26,   Assingment,                                    "=",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (27,         Less,                                    "<",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (28,         More,                                    ">",       "red",       "red",   "#FFCCC9", "box", "rounded, filled")
DEER (29,        Begin,                                    "{",     "white",     "white",     "white", "box", "rounded, filled")
DEER (30,          End,                                    "}",     "white",     "white",     "white", "box", "rounded, filled")
DEER (31,   EndOfToken,                                    ";",     "white",     "white",     "white", "box", "rounded, filled")
DEER (32,         Call,                                 "call",      "grey",      "grey", "lightgrey", "box", "rounded, filled")
DEER (32,       Params,                               "params",      "grey",      "grey", "lightgrey", "box", "rounded, filled")
