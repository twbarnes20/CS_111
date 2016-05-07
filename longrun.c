/*
 * longrun.c
 *
 *	This program runs for a very long time, and occasionally prints
 *	out messages that identify itself.
 *
 * Author: Ethan L. Miller (elm at cs.ucsc.edu)
 *
 * $Id: longrun.c,v 1.1 2006/05/02 17:23:29 elm Exp $
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define	LOOP_COUNT_MIN	100
#define	LOOP_COUNT_MAX	100000000
int
main (int argc, char *argv[])
{
    char *      id_str;
    uint32_t    v;
    int         i = 0;
    int         iteration = 0;
    int         loop_count;
    int         max_loops = -1;

    if (argc < 3 || argc > 4) {
        printf ("Usage: %s <id> <loop count> [max loops]\n", argv[0]);
        exit (-1);
    }
    /* Start with PID so result is unpredictable */
    v = getpid ();
    /* ID string is first argument */
    id_str = argv[1];
    /* loop count is second argument */
    loop_count = atoi (argv[2]);
    if ((loop_count < LOOP_COUNT_MIN) || (loop_count > LOOP_COUNT_MAX)) {
        printf ("%s: loop count must be between %d and %d (passed %s)\n",
                argv[0], LOOP_COUNT_MIN, LOOP_COUNT_MAX, argv[2]);
        exit (-1);
    }
    /* max loops is third argument (if present) */
    if (argc == 4) {
        max_loops = atoi (argv[3]);
    }

    /* Loop forever - use CTRL-C to exit the program */
    while (1) {
        for (i = 0; i < loop_count; ++i) {
            /* This calculation is done to keep the value of v unpredictable.  Since
             * the compiler can't calculate it in advance (even from the original
             *  value of v and the loop count), it has to do the loop.
             */
            v = (v << 4) ^ (v << 2) ^ (v >> 3);
        }
        printf ("%s: %06d\n", id_str, ++iteration);
        fflush (stdout);
        if (iteration == max_loops) {
            break;
        }
    }
    /* Print a value for v that's unpredictable so the compiler can't
       optimize the loop away.  Note that this works because the compiler
       can't tell in advance that it's not an infinite loop. */
    printf ("%s: final value of v is 0x%08x\n", id_str, v);
}
