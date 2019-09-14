/*
 * Copyright (C) 2019 Jonathan D. Belanger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * File:   Keyword.h
 * Author: Jonathan D. Belanger
 *
 * Created on September 2, 2019, 1:04 PM
 */
#ifndef LLVM_BLISS_KEYWORD_H
#define LLVM_BLISS_KEYWORD_H

#include "Basic/CommonInclude.h"

using namespace std;

namespace bliss
{
    class KWD
    {
        public:
        enum Keyword
        {
            _ALLOCATION,        _ASCIC,             _ASCID,             _ASCII,             _ASCIZ,
            _ASSIGN,            _B,                 _BLISS,             _BLISS32,           _BLISS64,
            _BPADDR,            _BPUNIT,            _BPVAL,             _C,                 _CHAR,
            _CHARCOUNT,         _COUNT,             _CTCE,              _DECIMAL,           _DECLARED,
            _ELSE,              _ERROR,             _ERRORMACRO,        _EXACTSTRING,       _EXITITERATION,
            _EXITMACRO,         _EXPAND,            _EXPLODE,           _FI,                _FIELDEXPAND,
            _IDENTICAL,         _IF,                _INFORM,            _ISSTRING,          _LENGTH,
            _LTCE,              _MESSAGE,           _NAME,              _NBITS,             _NBITSU,
            _NULL,              _NUMBER,            _O,                 _P,                 _PRINT,
            _QUOTE,             _QUOTENAME,         _REF,               _REMAINING,         _REMOVE,
            _REQUIRE,           _S,                 _SBTTL,             _SIZE,              _STRING,
            _SWITCHES,          _T,                 _THEN,              _TITLE,             _UNQUOTE,
            _UPVAL,             _VARIANT,           _WARN,              _X,                 ABS,
            ABSOLUTE,           ACTUALCOUNT,        ACTUALPARAMETER,    ADDRESSING_MODE,    ALIGN,
            ALWAYS,             AND,                ARGPTR,             ASSEMBLY,           BEGIN,
            BINARY,             BIND,               BIT,                BITVECTOR,          BLISS,
            BLISS32,            BLISS64,            BLOCK,              BLOCKVECTOR,        BUILTIN,
            BY,                 BYTE,               CALL,               CASE,               CH$A_RCHAR,
            CH$A_WCHAR,         CH$ALLOCATION,      CH$COMPARE,         CH$COPY,            CH$DIFF,
            CH$EQL,             CH$FAIL,            CH$FILL,            CH$FIND_CH,         CH$FIND_NOT_CH,
            CH$FIND_SUB,        CH$GEQ,             CH$GTR,             CH$LEQ,             CH$LSS,
            CH$MOVE,            CH$NEQ,             CH$PLUS,            CH$PTR,             CH$RCHAR,
            CH$RCHAR_A,         CH$SIZE,            CH$TRANSLATE,       CH$TRANSTABLE,      CH$WCHAR,
            CH$WCHAR_A,         CODE,               CODECOMMENT,        COMMENTARY,         COMPILETIME,
            CONCATENATE,        DEBUG,              DECR,               DECRA,              DECRU,
            DO,                 ELSE,               ELUDOM,             ENABLE,             END,
            EQL,                EQLA,               EQLU,               EQV,                ERRS,
            EXECUTE,            EXITLOOP,           EXPAND,             EXTERNAL,           FIELD,
            FORWARD,            FROM,               GENERAL,            GEQ,                GEQA,
            GEQU,               GLOBAL,             GTR,                GTRA,               GTRU,
            IDENT,              IF,                 INCR,               INCRA,              INCRU,
            INITIAL,            INRANGE,            INTERRUPT,          IOPAGE,             IOT,
            JSB,                KEYWORDMACRO,       LABEL,              LANGUAGE,           LEAVE,
            LEQ,                LEQA,               LEQU,               LIBRARY,            LINKAGE,
            LIST,               LITERAL,            LOCAL,              LONG,               LONG_RELATIVE,
            LSS,                LSSA,               LSSU,               MACRO,              MAIN,
            MAP,                MAX,                MAXA,               MAXU,               MIN,
            MINA,               MINU,               MOD,                MODULE,             NEQ,
            NEQA,               NEQU,               NOASSEMBLY,         NOBINARY,           NOCODE,
            NOCOMMENTARY,       NODEBUG,            NODEFAULT,          NOERRS,             NOEXECUTE,
            NOEXPAND,           NOLIBRARY,          NONEXTERNAL,        NOOBJECT,           NOOPTIMIZE,
            NOPIC,              NOPRESERVE,         NOREAD,             NOREQUIRE,          NOSAFE,
            NOSHARE,            NOSOURCE,           NOSYMBOLIC,         NOT,                NOTRACE,
            NOTUSED,            NOUNAMES,           NOVALUE,            NOWRITE,            NOZIP,
            NULLPARAMETER,      OBJECT,             OF,                 OPTIMIZE,           OPTLEVEL,
            OR,                 OTHERWISE,          OUTRANGE,           OVERLAY,            OWN,
            PIC,                PLIT,               PRESERVE,           PRESET,             PSECT,
            READ,               RECORD,             REF,                REP,                REQUIRE,
            RETURN,             ROUTINE,            SAFE,               SELECT,             SELECTA,
            SELECTONE,          SELECTONEA,         SELECTONEU,         SELECTU,            SET,
            SETUNWIND,          SHARE,              SHOW,               SIGN,               SIGNAL,
            SIGNAL_STOP,        SIGNED,             SOURCE,             STACKLOCAL,         STANDARD,
            STRUCTURE,          SWITCHES,           SYMBOLIC,           TES,                THEN,
            TO,                 TRACE,              UNAMES,             UNDECLARE,          UNSIGNED,
            UNTIL,              UPLIT,              VECTOR,             VERSION,            VOLATILE,
            WEAK,               WHILE,              WITH,               WORD,               WORD_RELATIVE,
            XOR,                ZIP,                __MAX_ITEMS         // Must be last one.
        };
    };
#define KWD_MAX KWD::__MAX_ITEMS
}

#endif /* LLVM_BLISS_KEYWORD_H */
