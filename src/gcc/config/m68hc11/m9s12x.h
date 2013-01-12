/* Definitions of target machine for GNU compiler, for m68hc12.
   Copyright (C) 1999, 2000, 2001, 2003 Free Software Foundation, Inc.
   Contributed by Stephane Carrez (stcarrez@nerim.fr).

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* Default to compile and assemble for a m9s12x */
#define ASM_SPEC                                                \
"%{m68hc11:-m68hc11}"                                           \
"%{m6812:-m68hc12}"                                         \
"%{m9s12x:-mm9s12x}"                                         \
"%{m68hcs12:-m68hcs12}"                                         \
"%{!m68hc11:%{!m68hcs12:%{!m68hc12: -mm9s12x}}}"
/* last line was "%{!m68hc11:%{!m68hcs12:%{!m68hc12:%{!m9s12x:-mm9s12x}}}}" */
#define LIB_SPEC       ""
#define CC1_SPEC       ""

/* We need to tell the linker the target elf format.  Just pass an
   emulation option.  This can be overriden by -Wl option of gcc.  */
#define LINK_SPEC                                               \
"%{m68hc11:-m m68hc11elf}"                                      \
"%{m9s12x:-m m68hc12elf}"                                     \
"%{m68hcs12:-m m68hc12elf}"                                     \
"%{!m68hc11:%{!m68hcs12:%{!m9s12x:-m m68hc11elf}}} %{mrelax:-relax}"

#define CPP_SPEC  \
"%{mshort:-D__HAVE_SHORT_INT__ -D__INT__=16}\
 %{!mshort:-D__INT__=32}\
 %{m68hc11:-Dmc68hc11}\
 %{m68hc12:-Dmc68hc12 -Dm68hc12}\
 %{m9s12x:-Dmc68hc12 -Dmc68hcs12 -Dm9s12x -m9s12x}\
 %{m68hcs12:-Dmc6812 -DMC6812 -Dmc68hc12 -Dmc68hcs12}\
 %{!m68hc11:%{!m68hc12:%{!m68hcs12:-Dmc68hc12 -Dmc68hcs12 -Dm9s12x -m9s12x}}}\
 %{fshort-double:-D__HAVE_SHORT_DOUBLE__}"
/* penultimate was %{!m68hc11:%{!m68hc12:%{!m68hcs12:%{!m9s12x:-Dmc6812 -DMC6812 -Dmc68hc12 -Dmc68hcs12 -Dm9s12x -m9s12x}}}} */

/* Default target_flags if no switches specified. Just causes problems if defaulting to S12X */
#define TARGET_DEFAULT		(MASK_M6812)

#define TARGET_M68HC12

#define MULTILIB_DEFAULTS { "m9s12x" }

#define CPP_PREDEFINES		"-Dmc68hc1x -Dtargets12x"
