/*
Iranian National Code Generator
Copyright (C) 2025  Ghorban M. Tavakoly <gmt3141@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP "[-h] [--help] [-v] [--verbose] [prefix1 [prefix2 ...]]"
#define ARG_IS(v, shrt, lng) (!strcmp (v, shrt) || !strcmp (v, lng))

void
next (int n, int len, int checksum)
{
  int i, reminder;

  if (len == 9)
    {
      reminder = checksum % 11;
      printf ("%09d%d\n", n, reminder < 2 ? reminder : 11 - reminder);
    }
  else
    for (i = 0; i < 10; ++i)
      next (10 * n + i, len + 1, checksum + i * (10 - len));
}

int
main (int argc, char **argv)
{
  int prefix, len, checksum, tmp, iarg, iprefix, valid, i, digit;
  int nprefixes = 0, verbose = 0;
  const char *arg;

  for (iarg = 1; arg = argv[iarg], iarg < argc; ++iarg)
    if (ARG_IS (arg, "-h", "--help"))
      {
        printf ("USAGE: %s %s\n", argv[0], HELP);
        return EXIT_SUCCESS;
      }
    else if (ARG_IS (arg, "-v", "--verbose"))
      verbose = 1;
    else
      nprefixes += 1;

  if (nprefixes == 0)
    {
      if (verbose)
        fprintf (stderr, "generating all possible codes...\n");
      next (0, 0, 0);
      return EXIT_SUCCESS;
    }

  for (iarg = 1, iprefix = 0; iarg < argc; ++iarg)
    {
      arg = argv[iarg];

      if (ARG_IS (arg, "-v", "--verbose"))
        continue;

      if (verbose)
        fprintf (stderr, "prefix %d: %s\n", ++iprefix, arg);

      len = strlen (arg);

      valid = 1;
      for (i = 0; i < len; ++i)
        if (arg[i] < '0' || arg[i] > '9')
          valid = 0;
      if (!valid)
        {
          fprintf (stderr, "ERROR: invalid integer number: %s\n", arg);
          continue;
        }

      prefix = atoi (arg);
      if (len > 9 || prefix < 0)
        {
          fprintf (stderr, "ERROR: out of 0..999999999 range: %s\n", arg);
          continue;
        }

      checksum = 0;
      for (tmp = prefix, digit = len; digit; --digit, tmp /= 10)
        checksum += (11 - digit) * (tmp % 10);

      next (prefix, len, checksum);
    }

  return EXIT_SUCCESS;
}
