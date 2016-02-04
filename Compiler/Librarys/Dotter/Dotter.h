//===============================================================================
//! @file    Dotter.h
//! @brief Библиотека для dot.
//!
//! $copyright: (C) Danila Baygushev$ <br>
//===============================================================================
#ifndef DOTTER__
#define DOTTER__

#include "stdio.h"
#include "windows.h"

//===============================================================================
//! @defgroup System Системная
//! @defgroup Main   Главная
//===============================================================================

//==============================================================================
#include "Dot\DotDef.h"  //Auto-gen file. Creates automatically.
//===============================================================================

//===============================================================================
//! @ingroup Main
//! @brief   Структура узла.
//===============================================================================
struct newDotNodeStyle
{
    char Shape     [30]; //!< Форма. Значения:<br>
                         //!1. box            - "коробка"(прямоугольник)<br>
                         //!2. ellipse        - эллипс<br>
                         //!3. point          - точка<br>
                         //!4. egg            - яйцо<br>
                         //!5. triangle       - треугольник<br>
                         //!6. diamond        - ромб<br>
                         //!7. trapezium      - трапеция<br>
                         //!8. parallelogram  - параллелограмм<br>
                         //!9. hexagon        - шестиугольник<br>
                         //!10.octagon        - восьмиугольник<br>
                         //!11.invtriangle    - перевёрнутый треугольник<br>
                         //!12.invtrapezium   - перевёрнутая трапеция<br>
                         //!13.folder         - папка<br>
                         //!14.tab            - закладка<br>
                         //!15.component      - деталь<br>
                         //!15.box3d          - 3D "коробка"(прямоугольник)<br>
                         //!15.house          - дом<br>

    char Color     [30]; //!< Цвет снаружи. Значения:<br>
                         //!1.английские названия цветов (см. Dotguide.pdf)<br>
                         //!2.# и за ней как в html<br>
                         //!3.три числа double = цвет / 256<br>

    char FillColor [30]; //!< Цвет внутри. Значения:<br>
                         //!1.английские названия цветов (см. Dotguide.pdf)<br>
                         //!2.# и за ней как в html<br>
                         //!3.три числа double = цвет / 256<br>

    char FontColor [30]; //!< Цвет букв. Значения:<br>
                         //!1.английские названия цветов (см. Dotguide.pdf)<br>
                         //!2.# и за ней как в html<br>
                         //!3.три числа double = цвет / 256<br>

    char Style     [30]; //!< Стиль. Значения: <br>
                         //!1.solid     - обычный<br>
                         //!2.dashed    - пунктирный<br>
                         //!3.dotted    - точками<br>
                         //!4.bold      - жирный<br>
                         //!5.invis     - не рисуется<br>
                         //!6.filled    - заполнен<br>
                         //!7.diagonals - диагонали<br>
                         //!8.round     - скруглённные углы<br>

    newDotNodeStyle ();

    newDotNodeStyle& shape     (const char Value[]);
    newDotNodeStyle& color     (const char Value[]);
    newDotNodeStyle& fillcolor (const char Value[]);
    newDotNodeStyle& fontcolor (const char Value[]);
    newDotNodeStyle& style     (const char Value[]);
};

//------------------------------------------------------------------------------

newDotNodeStyle::newDotNodeStyle ()
{
    strcpy (Shape,     "ellipse");
    strcpy (Color,     "black");
    strcpy (FillColor, "black");
    strcpy (FontColor, "black");
    strcpy (Style,     "solid");
}

newDotNodeStyle& newDotNodeStyle::shape     (const char Value[])
{
    strcpy (Shape, Value);

    return *this;
}
newDotNodeStyle& newDotNodeStyle::color     (const char Value[])
{
    strcpy (Color, Value);

    return *this;
}
newDotNodeStyle& newDotNodeStyle::fillcolor (const char Value[])
{
    strcpy (FillColor, Value);

    return *this;
}
newDotNodeStyle& newDotNodeStyle::fontcolor (const char Value[])
{
    strcpy (FontColor, Value);

    return *this;
}
newDotNodeStyle& newDotNodeStyle::style     (const char Value[])
{
    strcpy (Style, Value);

    return *this;
}

//==============================================================================

//===============================================================================
//! @ingroup Main
//! @brief   Структура связи.
//===============================================================================
struct newDotLinkStyle
{
    char Style [30]; //!< Стиль. Значения: <br>
                     //!1.solid     - обычный<br>
                     //!2.dashed    - пунктирный<br>
                     //!3.dotted    - точками<br>
                     //!4.bold      - жирный<br>
                     //!5.invis     - не рисуется<br>

    char Color [30]; //!< Цвет линии. Значения:<br>
                     //!1.английские названия цветов (см. Dotguide.pdf)<br>
                     //!2.# и за ней как в html<br>
                     //!3.три числа double = цвет / 256<br>

    newDotLinkStyle ();

    newDotLinkStyle& style (const char Value[]);
    newDotLinkStyle& color (const char Value[]);
};

//------------------------------------------------------------------------------

newDotLinkStyle::newDotLinkStyle ()
{
    strcpy (Color, "black");
    strcpy (Style, "solid");
}

newDotLinkStyle& newDotLinkStyle::style (const char Value[])
{
    strcpy (Style, Value);

    return *this;
}
newDotLinkStyle& newDotLinkStyle::color (const char Value[])
{
    strcpy (Color, Value);

    return *this;
}

//==============================================================================

//===============================================================================
//! @ingroup System
//! @brief   Здесь хранятся некоторые системные данные.
//===============================================================================
namespace DotterSystem
{
    FILE* CurrentFile = NULL; //!< Текущий файл
    bool CloseAtEnd = false; //!< Закрывать файл после конца, или нет

    newDotNodeStyle DefDotNode; //!< Стандартный стиль узла.
    newDotLinkStyle DefDotLink; //!< Стандартный стиль ссылки.

    newDotNodeStyle CurrentNodeStyle; //!< Текущий стиль узла.
    newDotLinkStyle CurrentLinkStyle; //!< Текущий стиль ссылки.

    int Ind = 4; //!< Отступ перед строкой в кол-ве пробелов.
};
using namespace DotterSystem;

//==============================================================================

//===============================================================================
//! @ingroup System
//! @brief   Функция вывода ошибки.
//!
//! @param Message - сообщение, поясняющее ошибку
//===============================================================================
void dtError (const char Message []);

//==============================================================================

//===============================================================================
//! @ingroup Main
//! @brief   Начать запись dot графа.
//!
//! @param To - Файл, куда писать. Все команды (см. @ref dtNode, @ref dtLink) до @ref dtEnd будут писаться в этот файл
//===============================================================================
void dtBegin (FILE* To);

//===============================================================================
//! @ingroup Main
//! @brief   Открыть файл и начать запись dot графа.
//!
//! @param Name - Имя файла, куда писать. Все команды (см. @ref dtNode, @ref dtLink) до @ref dtEnd будут писаться в этот файл
//===============================================================================
inline void dtBegin (const char Name []);

//===============================================================================
//! @ingroup Main
//! @brief   Закончить описание dot графа.
//===============================================================================
void dtEnd  ();

//===============================================================================
//! @ingroup Main
//! @brief   Вывести строку в пригодном для Dot формате.
//===============================================================================
void dtOut (const char Str []);

//==============================================================================

//===============================================================================
//! @ingroup Main
//! @brief   Устанавливает текущий стиль узла.
//!
//! @param NodeStyle - Структура, с описанным стилем узла. Не обязательно
//!
//! @return Ссылка на текущий стиль. Позволяет писать так:
//!
//! @usage
//! @code
//!
//!   dtNodeStyle ().shape ("diamond")
//!                 .color ("red");
//!
//! @endcode
//===============================================================================
newDotNodeStyle& dtNodeStyle  (const newDotNodeStyle NodeStyle = CurrentNodeStyle);

//===============================================================================
//! @ingroup Main
//! @brief   Устанавливает текущий стиль узла.
//!
//! @param LinkStyle - Структура, с описанным стилем узла. Не обязательно
//!
//! @return Ссылка на текущий стиль. Позволяет писать так:
//!
//! @usage
//! @code
//!
//!   dtLinkStyle ().style ("bold")
//!                 .color ("red");
//!
//! @endcode
//===============================================================================
newDotLinkStyle& dtLinkStyle  (const newDotLinkStyle LinkStyle = CurrentLinkStyle);

//===============================================================================
//! @ingroup Main
//! @brief   Функция рисования узла в dot.
//!
//! @param NodeN       - Номер узла
//! @param Label       - Текст, который надо разместить внутри
//! @param NodeStyle   - Структура, с описанным стилем узла. Если не указано, используется текущая(см. @ref dtNodeStyle)
//! @param ExtraParams - Дополнительные параметры(см. dotguide)
//===============================================================================
void dtNode  (const int NodeN, const char Label [] = "", const newDotNodeStyle NodeStyle = CurrentNodeStyle, const char ExtraParams [] = "");

//===============================================================================
//! @ingroup Main
//! @brief   Функция рисования соединения узлов в dot.
//!
//! @param FromNode    - Номер узла откуда
//! @param ToNode      - Номер узла куда
//! @param Label       - Текст, который надо разместить рядом.
//! @param LinkStyle   - Структура, со стилем связи. Если не указано, используется текущий (см. @ref dtLinkStyle)
//! @param ExtraParams - Дополнительные параметры(см. dotguide)
//===============================================================================
void dtLink (const int FromNode, const int ToNode, const char Label [] = "", const newDotLinkStyle LinkStyle = CurrentLinkStyle, const char ExtraParams [] = "");

//==============================================================================

//===============================================================================
//! @ingroup Main
//! @brief   Функция генерирования изображения в dot.
//!
//! @param From - Имя dot файла
//! @param To   - Имя выходного файла
//! @param Type - Тип (jpg, bmp, ...)
//! @param Show - Показывать файл после создания, или нет
//===============================================================================
void dtRender (const char From [], const char To [] = "Graph.jpg", const char Type [] = "jpg", const bool Show = true);

//==============================================================================

void dtError (const char Message [])
{
    throw Message;

    printf ("==Dotter error!==\n");
    printf ("Message = %s\n", Message);

    throw "Dotter error!!!"; //Вдруг кто-то ловит. )

    system ("pause");

    exit (0);
}

//==============================================================================

void dtBegin (FILE* To)
{
    if (!To) dtError ("No output file");
    if (CurrentFile) dtError ("Close previous file first");
    CurrentFile = To;

    fprintf (CurrentFile, "digraph DotGraph\n");
    fprintf (CurrentFile, "{\n");
}

inline void dtBegin (const char Name [])
{
    FILE* To = NULL;
    To = fopen (Name, "w");

    CloseAtEnd = true;

    dtBegin (To);
}

void dtEnd  ()
{
    if (!CurrentFile) dtError ("No output file");

    fprintf (CurrentFile, "}\n");

    if (CloseAtEnd)
    {
        CloseAtEnd = false;

        fclose (CurrentFile);
    }

    CurrentFile = NULL;
}

void dtOut (const char Str [])
{
    if (!CurrentFile) dtError ("No output file");

    for (int i = 0; Str [i] != 0; i ++)
    {
        switch (Str [i])
        {
            case '\n':
            {
                fprintf (CurrentFile, "\\n");
                break;
            }
            case '\r':
            {
                fprintf (CurrentFile, "\\r");
                break;
            }
            case '\\':
            {
                fprintf (CurrentFile, "\\\\");
                break;
            }
            case '"':
            {
                fprintf (CurrentFile, "\\\"");
                break;
            }

            default:
            {
                fprintf (CurrentFile, "%c", Str [i]);
                break;
            }

        }
    }
}

//==============================================================================

newDotNodeStyle& dtNodeStyle  (const newDotNodeStyle NodeStyle)
{
    if (!CurrentFile) dtError ("No output file");

    CurrentNodeStyle = NodeStyle;

    return CurrentNodeStyle;
}
newDotLinkStyle& dtLinkStyle  (const newDotLinkStyle LinkStyle)
{
    if (!CurrentFile) dtError ("No output file");

    CurrentLinkStyle = LinkStyle;

    return CurrentLinkStyle;
}

void dtNode (const int NodeN, const char Label [], const newDotNodeStyle NodeStyle, const char ExtraParams [])
{
    if (!CurrentFile) dtError ("No output file");

    for (int i = 0; i < DotterSystem::Ind; i ++)
    {
        fprintf (CurrentFile, " ");
    }

    fprintf (CurrentFile, "Node%d ", NodeN);
    fprintf (CurrentFile, "[");

#ifndef BeautifulDot
    fprintf (CurrentFile, "shape=\"%s\", ",     NodeStyle.Shape);
    fprintf (CurrentFile, "color=\"%s\", ",     NodeStyle.Color);
    fprintf (CurrentFile, "fontcolor=\"%s\", ", NodeStyle.FontColor);
    fprintf (CurrentFile, "fillcolor=\"%s\", ", NodeStyle.FillColor);
    fprintf (CurrentFile, "style=\"%s\", ",     NodeStyle.Style);
    fprintf (CurrentFile, "weight=\"1\", ");
#else
    if (strcmp (NodeStyle.Shape,     DefDotNode.Shape)     != 0) fprintf (CurrentFile, "shape=\"%s\", ",     NodeStyle.Shape);
    if (strcmp (NodeStyle.Color,     DefDotNode.Color)     != 0) fprintf (CurrentFile, "color=\"%s\", ",     NodeStyle.Color);
    if (strcmp (NodeStyle.FontColor, DefDotNode.FontColor) != 0) fprintf (CurrentFile, "fontcolor=\"%s\", ", NodeStyle.FontColor);
    if (strcmp (NodeStyle.FillColor, DefDotNode.FillColor) != 0) fprintf (CurrentFile, "fillcolor=\"%s\", ", NodeStyle.FillColor);
    if (strcmp (NodeStyle.Style,     DefDotNode.Style)     != 0) fprintf (CurrentFile, "style=\"%s\", ",     NodeStyle.Style);
#endif

    fprintf (CurrentFile, "label=\"");
    dtOut (Label);
    fprintf (CurrentFile, "\"");

    if (strcmp (ExtraParams, "") != 0) fprintf (CurrentFile, ", %s", ExtraParams);

    fprintf (CurrentFile, "];\n");
}

void dtLink (const int FromNode, const int ToNode, const char Label [], const newDotLinkStyle LinkStyle, const char ExtraParams [])
{
    if (!CurrentFile) dtError ("No output file");

    for (int i = 0; i < DotterSystem::Ind; i ++)
    {
        fprintf (CurrentFile, " ");
    }

    fprintf (CurrentFile, "Node%d -> Node%d ", FromNode, ToNode);
    fprintf (CurrentFile, "[");

#ifndef BeautifulDot
    fprintf (CurrentFile, "color=\"%s\", ", LinkStyle.Color);
    fprintf (CurrentFile, "style=\"%s\", ", LinkStyle.Style);
    fprintf (CurrentFile, "weight=\"1\", ");
#else
    if (strcmp (LinkStyle.Color, DefDotLink.Color) != 0) fprintf (CurrentFile, "color=\"%s\", ", LinkStyle.Color);
    if (strcmp (LinkStyle.Style, DefDotLink.Style) != 0) fprintf (CurrentFile, "style=\"%s\", ", LinkStyle.Style);
#endif

    fprintf (CurrentFile, "label=\"");
    dtOut (Label);
    fprintf (CurrentFile, "\"");

    if (strcmp (ExtraParams, "") != 0) fprintf (CurrentFile, ", %s", ExtraParams);

    fprintf (CurrentFile, "];\n");
}

//==============================================================================

void dtRender (const char From [], const char To [], const char Type [], const bool Show)
{
    const int ComandSize = 100;

    char Comand [ComandSize] = "";

    const int OtherSymbols = 14;

    if (strlen (__DOT__) + strlen (From) + strlen (To) + strlen (Type) + OtherSymbols >= ComandSize) dtError ("Names too long!");

    sprintf (Comand, "%s -T%s %s -o %s", __DOT__, Type, From, To);

    system (Comand);

    if (Show)
    {
        strcpy (Comand, "");

        sprintf (Comand, "start %s", To);

        system (Comand);
    }
}

//==============================================================================

#endif
