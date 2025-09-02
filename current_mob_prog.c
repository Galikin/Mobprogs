/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/***************************************************************************
 *  The MOBprograms have been contributed by N'Atas-ha.  Any support for   *
 *  these routines should not be expected from Merc Industries.  However,  *
 *  under no circumstances should the blame for bugs, etc be placed on     *
 *  Merc Industries.  They are not guaranteed to work on all systems due   *
 *  to their frequent use of strxxx functions.  They are also not the most *
 *  efficient way to perform their tasks, but hopefully should be in the   *
 *  easiest possible way to install and begin using. Documentation for     *
 *  such installation can be found in INSTALL.  Enjoy...         N'Atas-Ha *
 ***************************************************************************/

/*
 * $Log: mob_prog.c,v $
 * Revision 1.24  2003/05/17 04:46:32  mull
 * Mull: Added exit/exall trigger type for mobprogs
 *
 * Revision 1.23  2003/05/15 07:46:36  mull
 * Mull: Added new if check for mobprogs: mobhere()
 *
 * Revision 1.22  2001/12/13 22:53:01  coyotilo
 * Coy: Fixed death_prog so it now allows if checks
 * that use $* variables.
 *
 * Revision 1.21  2001/09/24 08:39:25  coyotilo
 * Coy: More fixes from code mixup.
 *
 * Revision 1.19  2001/09/12 05:13:18  coyotilo
 * Coy: Mostly bard stuff, got rid of some compile time warnings, fix
 * to calm, and some misc. special projects.
 *
 * Revision 1.18  2001/08/04 23:44:26  coyotilo
 * Coy: Added isaff mobprog.
 *
 * Revision 1.17  2001/05/03 02:05:55  icnec
 * Icnec: changed the objextract mob prog to search inventory and
 * what the pc is currently wearing
 *
 * Revision 1.16  2001/05/03 01:54:19  icnec
 * Icnec:  I added the objextract mob prog and fixed it so that you can now
 * delete a character.
 *
 * Revision 1.15  2001/04/22 18:53:39  icnec
 * Icnec:  I added some functions for mob_progs, as well as some functions for
 * searching inventory.  Also made some modifications to messages for auctioning.
 *
 * Revision 1.14  2000/03/30 17:26:35  lorn
 * Lorn: animate dead and bored_prog
 *
 * Revision 1.13  2000/03/05 09:41:44  mythos
 * Mythos: minor bug fixes etc
 *
 * Revision 1.12  1999/11/06 21:53:35  cvsuser
 * Lorn: clanpoints ifcheck
 *
 * Revision 1.10  1999/09/27 23:01:12  cvsuser
 * fixes to reduce/prevent bug reporting
 *
 * Revision 1.9  1999/09/22 22:40:35  cvsuser
 * Lorn: improved (created) nested ifs within else statemetns, I think
 *
 * Revision 1.8  1999/09/21 18:15:11  cvsuser
 * Lorn: give_word_prog check name instead of short
 *
 * Revision 1.7  1999/09/10 14:54:22  cvsuser
 * Lorn: put give_word_prog in correct order
 *
 * Revision 1.6  1999/09/07 21:57:02  cvsuser
 * Lorn: fix meditate, give_word_prog, create table skill slot
 *
 * Revision 1.5  1999/09/06 07:31:51  cvsuser
 * give_word_prog created and motorball repairs
 *
 * Revision 1.4  1999/08/19 00:18:27  cvsuser
 * mprog slotnum check, fix to deadly aura
 *
 * Revision 1.3  1999/07/11 19:56:08  cvsuser
 * Ivan: Fix to HITPRCNT, should work now.
 *
 * Revision 1.2  1999/04/01 03:13:12  cvsuser
 * Ivan: Minor mods. Clan only eq can't be used by recruits. Only aggro mobs
 *       are extracted after a nofollow. Removed case sensitivity and other
 *       bugs in table command, stripped all the ^Ms out of all files.
 *
 * Revision 1.1.1.1  1999/03/19 19:10:17  sjofn
 * Importing Ivan's tree as aesir-0.1
 *
 * Use: cvs checkout aesir-0.1
 *
 * Revision 1.1.1.1  1999/03/10 21:21:58  viviano
 * Inital Checkin
 *
 */

/* Debugging revisions:
   Fourth Revision: (1/15/99)
      wordlist_check phrase now accepts end of line as termination
   First revision:
	if has
	start of wordlist_check
	start of percent check
	percent check calling mprog_driver
   Second revision:
	after first call to  mprog_do_ifchck  in mprog_process_if
	two messages within mprog_driver
   Third revision:
	printing of comlists in mprog_driver
      failure variable in mprog_driver to print cmnd if nothing
*/

/*
 * Revision 1.2  1997/02/26 19:04:41  root
 * Fix in mprog_speech_trigger to prevent infinite loop.
 *
 */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "merc.h"
/*#define DEBUG */

/* externs */
extern void death_cry(CHAR_DATA * ch);
extern bool get_mob_vnum_room( CHAR_DATA *ch, OBJ_DATA *obj, ROOM_INDEX_DATA *room, sh_int vnum );

/*
 * Local function prototypes
 */

char *mprog_next_command args((char *clist));
bool mprog_seval args((char *lhs, char *opr, char *rhs));
bool mprog_veval args((int lhs, char *opr, int rhs));
bool mprog_do_ifchck args((char *ifchck, CHAR_DATA * mob,
                           CHAR_DATA * actor, OBJ_DATA * obj,
                           void *vo, CHAR_DATA * rndm));
char *mprog_process_if args((char *ifchck, char *com_list,
                             CHAR_DATA * mob, CHAR_DATA * actor,
                             OBJ_DATA * obj, void *vo,
                             CHAR_DATA * rndm));
void mprog_translate args((char ch, char *t, CHAR_DATA * mob,
                           CHAR_DATA * actor, OBJ_DATA * obj,
                           void *vo, CHAR_DATA * rndm));
void mprog_process_cmnd args((char *cmnd, CHAR_DATA * mob,
                              CHAR_DATA * actor, OBJ_DATA * obj,
                              void *vo, CHAR_DATA * rndm));
void mprog_driver args((char *com_list, CHAR_DATA * mob,
                        CHAR_DATA * actor, OBJ_DATA * obj,
                        void *vo));
int mp_aff_translate(int aff);

OBJ_DATA *check_inventory(CHAR_DATA *ch, int vnum, int chkOption);

static char null[1] = "0";

/***************************************************************************
 * Local function code and brief comments.
 */

/* if you dont have these functions, you damn well should... */

#ifdef DUNNO_STRSTR
char *strstr(s1, s2)
    const char *s1;
    const char *s2;
{
    char *cp;
    int i, j = strlen(s1) - strlen(s2), k = strlen(s2);

    if (j < 0)
        return NULL;
    for (i = 0; i <= j && strncmp(s1++, s2, k) != 0; i++) ;
    return (i > j) ? NULL : (s1 - 1);
}
#endif

/* Used to get sequential lines of a multi line string (separated by "\n\r")
 * Thus its like one_argument(), but a trifle different. It is destructive
 * to the multi line string argument, and thus clist must not be shared.
 */
char *mprog_next_command(char *clist)
{

    char *pointer = clist;

    while (*pointer != '\n' && *pointer != '\0')
        pointer++;
    if (*pointer == '\n')
        *pointer++ = '\0';
    if (*pointer == '\r')
        *pointer++ = '\0';

    return (pointer);

}

/* These two functions do the basic evaluation of ifcheck operators.
 *  It is important to note that the string operations are not what
 *  you probably expect.  Equality is exact and division is substring.
 *  remember that lhs has been stripped of leading space, but can
 *  still have trailing spaces so be careful when editing since:
 *  "guard" and "guard " are not equal.
 */
bool mprog_seval(char *lhs, char *opr, char *rhs)
{

    if (!str_cmp(opr, "=="))
        return (bool) (!str_cmp(lhs, rhs));
    if (!str_cmp(opr, "!="))
        return (bool) (str_cmp(lhs, rhs));
    if (!str_cmp(opr, "/"))
        return (bool) (!str_infix(rhs, lhs));
    if (!str_cmp(opr, "!/"))
        return (bool) (str_infix(rhs, lhs));

    bug("Improper MOBprog operator\n\r", 0);
    return 0;

}

bool mprog_veval(int lhs, char *opr, int rhs)
{

    if (!str_cmp(opr, "=="))
        return (lhs == rhs);
    if (!str_cmp(opr, "!="))
        return (lhs != rhs);
    if (!str_cmp(opr, ">"))
        return (lhs > rhs);
    if (!str_cmp(opr, "<"))
        return (lhs < rhs);
    if (!str_cmp(opr, "<="))
        return (lhs <= rhs);
    if (!str_cmp(opr, ">="))
        return (lhs >= rhs);
    if (!str_cmp(opr, "&"))
        return (lhs & rhs);
    if (!str_cmp(opr, "|"))
        return (lhs | rhs);

    bug("Improper MOBprog operator\n\r", 0);
    return 0;

}

/* This function performs the evaluation of the if checks.  It is
 * here that you can add any ifchecks which you so desire. Hopefully
 * it is clear from what follows how one would go about adding your
 * own. The syntax for an if check is: ifchck ( arg ) [opr val]
 * where the parenthesis are required and the opr and val fields are
 * optional but if one is there then both must be. The spaces are all
 * optional. The evaluation of the opr expressions is farmed out
 * to reduce the redundancy of the mammoth if statement list.
 * If there are errors, then return -1 otherwise return boolean 1,0
 */
bool mprog_do_ifchck(char *ifchck, CHAR_DATA * mob, CHAR_DATA * actor,
                     OBJ_DATA * obj, void *vo, CHAR_DATA * rndm)
{

    char buf[MAX_INPUT_LENGTH];
    char bugbuf[MAX_INPUT_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    char opr[MAX_INPUT_LENGTH];
    char val[MAX_INPUT_LENGTH];
    CHAR_DATA *vict = (CHAR_DATA *) vo;
    OBJ_DATA *v_obj = (OBJ_DATA *) vo;
    CHAR_DATA *target;
    char *bufpt = buf;
    char *argpt = arg;
    char *oprpt = opr;
    char *valpt = val;
    char *point = ifchck;
    int lhsvl;
    int rhsvl;
    bool not = FALSE;

    if (!IS_NPC(mob))
      bug("mprog_do_ifcheck called on player!!",0);

    if (*point == '\0')
    {
        sprintf(bugbuf, "Mob: %d null ifchck", mob->pIndexData->vnum);
        bug(bugbuf, mob->pIndexData->vnum);
        return -1;
    }
    /* skip leading spaces */
    while (*point == ' ')
        point++;

    /* get whatever comes before the left paren.. ignore spaces */
    while (*point != '(')
        if (*point == '\0')
        {
            bug("Mob: %d ifchck syntax error", mob->pIndexData->vnum);
            return -1;
        }
        else if (*point == ' ')
            point++;
        else
            *bufpt++ = *point++;

    *bufpt = '\0';
    point++;

    /* get whatever is in between the parens.. ignore spaces */
    while (*point != ')')
        if (*point == '\0')
        {
            bug("Mob: %d ifchck syntax error", mob->pIndexData->vnum);
            return -1;
        }
        else if (*point == ' ')
            point++;
        else
            *argpt++ = *point++;

    *argpt = '\0';
    point++;

    /* check to see if there is an operator */
    while (*point == ' ')
        point++;
    if (*point == '\0')
    {
        *opr = '\0';
        *val = '\0';
    }
    else
        /* there should be an operator and value, so get them */
    {
        while ((*point != ' ') && (!isalnum(*point)))
            if (*point == '\0')
            {
                bug("Mob: %d ifchck operator without value",
                    mob->pIndexData->vnum);
                return -1;
            }
            else
                *oprpt++ = *point++;

        *oprpt = '\0';

        /* finished with operator, skip spaces and then get the value */
        while (*point == ' ')
            point++;
        for (;;)
        {
            if ((*point != ' ') && (*point == '\0'))
                break;
            else
                *valpt++ = *point++;
        }

        *valpt = '\0';
    }
    bufpt = buf;
    argpt = arg;
    oprpt = opr;
    valpt = val;

    /* Ok... now buf contains the ifchck, arg contains the inside of the
     *  parentheses, opr contains an operator if one is present, and val
     *  has the value if an operator was present.
     *  So.. basically use if statements and run over all known ifchecks
     *  Once inside, use the argument and expand the lhs. Then if need be
     *  send the lhs,opr,rhs off to be evaluated.
     */

    if (buf[0] == '!')
    {
        not = TRUE;
        while (*bufpt != '\0')
            *bufpt = *(++bufpt);
        *bufpt = '\0';
    }

    if (!str_cmp(buf, "rand"))
    {
        return (not ? number_percent() > atoi(arg) : number_percent() <= atoi(arg));
    }
    if (!str_cmp(buf, "has"))
    {
        /* arg should be variable,vnum */
        char *p;
        OBJ_INDEX_DATA *pObjIndex;
        OBJ_DATA *qObj;
        int v;

        /* find the comma */
        for (p = arg; *p; p++)
            if (*p == ',')
                break;
        if (!*p)
        {
            bug("Mob: %d must have two arguments for 'has'", mob->pIndexData->vnum);
            return -1;
        }
        p++;                    /* p now points to vnum */
        /* check valid first argument - only allow mob, actor, victim */
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                target = mob;
                break;
            case 'n':
                target = actor;
                break;
            case 't':
                target = mob;  /* there was no assignment of target here
                                  but since this could lead to dereferencing
                                  NULL, I added this line.  Lorn, 9/98 */
                break;
            default:
                bug("Mob: %d bad argument to 'ifhas'", mob->pIndexData->vnum);
                return -1;
        }
        /* check second argument */
        v = atoi(p);

        sprintf(bugbuf, "Mob %d: ifhas searching for object %d.", mob->pIndexData->vnum,v);
        wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

        pObjIndex = get_obj_index(v);
        if (pObjIndex == NULL)
          {
            sprintf(bugbuf, "Mob %d: ifhas searching for invalid object %d.", mob->pIndexData->vnum,v);
            bug(bugbuf,0);
            return FALSE;
          }
        else
          for (qObj = target->carrying; qObj != NULL; qObj = qObj->next_content)
            {
              if ( qObj->pIndexData->vnum == v )
                {
                  return TRUE;
                }
            }
          return FALSE;
    }                           /* end of 'has' */
	/* Coy - 8/01 */
    if (!str_cmp(buf, "isaff")) {
        /* For integer value input by user (the affect being looked for. */
		int aff;
		int vector;
		
		/* arg should be variable,affect */
        char *p;                
        
        /* find the comma */
        for (p = arg; *p; p++)
            if (*p == ',')
                break;
        if (!*p)
        {
            bug("Mob: %d must have two arguments for 'isaff'", mob->pIndexData->vnum);
            return -1;
        }

        p++;                    /* p now points to vnum */
        /* check valid first argument - only allow mob, actor, victim */
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                target = mob;
                break;
            case 'n':
                target = actor;
                break;
            case 't':
                target = mob;  
                break;
            default:
                bug("Mob: %d bad argument to 'ifhas'", mob->pIndexData->vnum);
                return -1;
        }
        /* check second argument */
        aff = atoi(p);
		
		/* set the vector to look on */
		if (aff < MP_VECT2_START) {
			vector = AFF1_VECTOR;
		}
		else {
			vector = AFF2_VECTOR;
		}

		/* Get the actual affect number being looked for. */
		aff = mp_aff_translate(aff);
		
		/* Make sure it is one of the specified numbers */
		if (aff == 0) {
			bug("Mob: %d bad argument to 'ifaff'", mob->pIndexData->vnum);
		}
		
		/* Check if the apply is there. */
		if (vector == AFF1_VECTOR) {
			if (IS_AFFECTED(target, aff)) {
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
		else  {
			if (IS_AFFECTED2(target, aff)) {
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
		bug("ifaff reached end of prog, shouldn't happen, have someone look at isaff", 0);
		return FALSE;
    }
    if (!str_cmp(buf, "ispc"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return 0;
            case 'n':
                if (actor)
                    return (not ? IS_NPC(actor) : !IS_NPC(actor));
                else
                    return -1;
            case 't':
                if (vict)
                    return (not ? IS_NPC(vict) : !IS_NPC(vict));
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (not ? IS_NPC(rndm) : !IS_NPC(rndm));
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'ispc'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "isnpc"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return 1;
            case 'n':
                if (actor)
                    return (not ? !IS_NPC(actor) : IS_NPC(actor));
                else
                    return -1;
            case 't':
                if (vict)
                    return (not ? !IS_NPC(vict) : IS_NPC(vict));
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (not ? !IS_NPC(rndm) : IS_NPC(rndm));
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isnpc'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "isgood"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return IS_GOOD(mob);
            case 'n':
                if (actor)
                    return not ? !IS_GOOD(actor) : IS_GOOD(actor);
                else
                    return -1;
            case 't':
                if (vict)
                    return not ? !IS_GOOD(vict) : IS_GOOD(vict);
                else
                    return -1;
            case 'r':
                if (rndm)
                    return not ? !IS_GOOD(rndm) : IS_GOOD(rndm);
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isgood'", mob->pIndexData->vnum);
                return -1;
        }
    }

	if (!str_cmp(buf, "isneutral"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return IS_NEUTRAL(mob);
            case 'n':
                if (actor)
                    return not ? !IS_NEUTRAL(actor) : IS_NEUTRAL(actor);
                else
                    return -1;
            case 't':
                if (vict)
                    return not ? !IS_NEUTRAL(vict) : IS_NEUTRAL(vict);
                else
                    return -1;
            case 'r':
                if (rndm)
                    return not ? !IS_NEUTRAL(rndm) : IS_NEUTRAL(rndm);
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isgood'", mob->pIndexData->vnum);
                return -1;
        }
    }

	if (!str_cmp(buf, "isevil"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return IS_EVIL(mob);
            case 'n':
                if (actor)
                    return not ? !IS_EVIL(actor) : IS_EVIL(actor);
                else
                    return -1;
            case 't':
                if (vict)
                    return not ? !IS_EVIL(vict) : IS_EVIL(vict);
                else
                    return -1;
            case 'r':
                if (rndm)
                    return not ? !IS_EVIL(rndm) : IS_EVIL(rndm);
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isgood'", mob->pIndexData->vnum);
                return -1;
        }
    }

	if (!str_cmp(buf, "objextract"))
	{		
		OBJ_DATA *myobj;
		OBJ_INDEX_DATA *pObjIndex;
		
		/* arg should be variable,vnum */
        char *p;                
        int v;

        /* find the comma */
        for (p = arg; *p; p++)
            if (*p == ',')
                break;
        if (!*p)
        {
            bug("Mob: %d must have two arguments for 'objextract'", mob->pIndexData->vnum);
            return -1;
        }

        p++;                    /* p now points to vnum */
        /* check valid first argument - only allow mob, actor, victim */
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                target = mob;
                break;
            case 'n':
                target = actor;
                break;
            case 't':
                target = mob;  
                break;
            default:
                bug("Mob: %d bad argument to 'ifobjextract'", mob->pIndexData->vnum);
                return -1;
        }

        /* check second argument */
        v = atoi(p);

        pObjIndex = get_obj_index(v);

        if (pObjIndex == NULL)
        {
			sprintf(bugbuf, "Mob %d: objextract searching for invalid object %d.", mob->pIndexData->vnum,v);
            bug(bugbuf,0);
            return FALSE;
        }
        
        myobj = check_inventory(actor, v, 3);
				
		if (myobj == NULL)
			return FALSE;
				
		extract_obj(myobj); // it must exist at this point so lets extract it
				
		return TRUE;
	}

    if (!str_cmp(buf, "isfight"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return (not ? (mob->fighting == NULL) : !(mob->fighting == NULL));
            case 'n':
                if (actor)
                    return (not ? (actor->fighting == NULL) : !(actor->fighting == NULL));
                else
                    return -1;
            case 't':
                if (vict)
                    return (not ? (vict->fighting == NULL) : !(vict->fighting == NULL));
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (not ? (rndm->fighting == NULL) : !(rndm->fighting == NULL));
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isfight'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "isimmort"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return (not ? (get_trust(mob) < LEVEL_IMMORTAL) : (get_trust(mob) >= LEVEL_IMMORTAL));
            case 'n':
                if (actor)
                    return (not ? (get_trust(actor) < LEVEL_IMMORTAL) : (get_trust(actor) >= LEVEL_IMMORTAL));
                else
                    return -1;
            case 't':
                if (vict)
                    return (not ? (get_trust(vict) < LEVEL_IMMORTAL) : (get_trust(vict) >= LEVEL_IMMORTAL));
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (not ? (get_trust(rndm) < LEVEL_IMMORTAL) : (get_trust(rndm) >= LEVEL_IMMORTAL));
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isimmort'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "ischarmed"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return (not ? (char)!IS_AFFECTED(mob, AFF_CHARM) : (char)IS_AFFECTED(mob, AFF_CHARM));
            case 'n':
                if (actor)
                    return (not ? (char)!IS_AFFECTED(actor, AFF_CHARM) : (char)IS_AFFECTED(actor, AFF_CHARM));
                else
                    return -1;
            case 't':
                if (vict)
                    return (not ? (char)!IS_AFFECTED(vict, AFF_CHARM) : (char)IS_AFFECTED(vict, AFF_CHARM));
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (not ? (char)!IS_AFFECTED(rndm, AFF_CHARM) : (char)IS_AFFECTED(rndm, AFF_CHARM));
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'ischarmed'",
                    mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "isfollow"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return (mob->master != NULL
                        && mob->master->in_room == mob->in_room);
            case 'n':
                if (actor)
                    return (actor->master != NULL
                       && actor->master->in_room == actor->in_room);
                else
                    return -1;
            case 't':
                if (vict)
                    return (vict->master != NULL
                         && vict->master->in_room == vict->in_room);
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (rndm->master != NULL
                         && rndm->master->in_room == rndm->in_room);
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isfollow'", mob->pIndexData->vnum);
                return -1;
        }

    }

    if (!str_cmp(buf, "iskiller"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return (!IS_NPC(mob) && IS_SET(mob->act, PLR_KILLER));
            case 'n':
                if (actor)
                    return (!IS_NPC(actor) && IS_SET(actor->act, PLR_KILLER));
                else
                    return -1;
            case 't':
                if (vict)
                    return (!IS_NPC(mob) && IS_SET(mob->act, PLR_KILLER));
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (!IS_NPC(rndm) && IS_SET(rndm->act, PLR_KILLER));
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isKiller'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "isthief"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return (!IS_NPC(mob) && IS_SET(mob->act, PLR_THIEF));
            case 'n':
                if (actor)
                    return (!IS_NPC(actor) && IS_SET(actor->act, PLR_THIEF));
                else
                    return -1;
            case 't':
                if (vict)
                    return (!IS_NPC(mob) && IS_SET(mob->act, PLR_THIEF));
                else
                    return -1;
            case 'r':
                if (rndm)
                    return (!IS_NPC(rndm) && IS_SET(rndm->act, PLR_THIEF));
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'isThief'", mob->pIndexData->vnum);
                return -1;
        }
    }
    if (!str_cmp(buf, "hitprcnt"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = 100 * mob->hit / mob->max_hit;
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    lhsvl = 100 * actor->hit / actor->max_hit;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    lhsvl = 100 * vict->hit / vict->max_hit;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    lhsvl = 100 * rndm->hit / rndm->max_hit;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'hitprcnt'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "inroom"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = mob->in_room->vnum;
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    lhsvl = actor->in_room->vnum;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    lhsvl = vict->in_room->vnum;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    lhsvl = rndm->in_room->vnum;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'inroom'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "sex"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = mob->sex;
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    lhsvl = actor->sex;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    lhsvl = vict->sex;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    lhsvl = rndm->sex;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'sex'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "position"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = mob->position;
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    lhsvl = actor->position;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    lhsvl = vict->position;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    lhsvl = rndm->position;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'position'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "level"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = get_trust(mob);
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    lhsvl = get_trust(actor);
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    lhsvl = get_trust(vict);
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    lhsvl = get_trust(rndm);
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'level'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "class"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = mob->class;
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    lhsvl = actor->class;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    lhsvl = vict->class;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    lhsvl = rndm->class;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'class'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "goldamt"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = mob->gold;
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    lhsvl = actor->gold;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    lhsvl = vict->gold;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    lhsvl = rndm->gold;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'goldamt'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "objtype"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'o':
                if (obj)
                {
                    lhsvl = obj->item_type;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'p':
                if (v_obj)
                {
                    lhsvl = v_obj->item_type;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'objtype'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "objval0"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'o':
                if (obj)
                {
                    lhsvl = obj->value[0];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'p':
                if (v_obj)
                {
                    lhsvl = v_obj->value[0];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'objval0'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "objval1"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'o':
                if (obj)
                {
                    lhsvl = obj->value[1];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'p':
                if (v_obj)
                {
                    lhsvl = v_obj->value[1];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'objval1'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "objval2"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'o':
                if (obj)
                {
                    lhsvl = obj->value[2];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'p':
                if (v_obj)
                {
                    lhsvl = v_obj->value[2];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'objval2'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "objval3"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'o':
                if (obj)
                {
                    lhsvl = obj->value[3];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'p':
                if (v_obj)
                {
                    lhsvl = v_obj->value[3];
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'objval3'", mob->pIndexData->vnum);
                return -1;
        }
    }

    /* checks locations 1,2,3 for a slot number match */
    /* mostly copied from objval conditions */
    /* added August 1999 by Lorn  */
    if (!str_cmp(buf, "slotnum"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'o':
                if (obj)
                {
                    int sn, lhsvl1, lhsvl2, lhsvl3;

                    sn = obj->value[1];
                    if ( (sn <= MAX_SKILL) && (sn > 0) )
                        lhsvl1 = skill_table[sn].slot;
                    else
                        lhsvl1 = 0;

                    sn = obj->value[2];
                    if ( (sn <= MAX_SKILL) && (sn > 0) )
                        lhsvl2 = skill_table[sn].slot;
                    else
                        lhsvl2 = 0;

                    sn = obj->value[3];
                    if ( (sn <= MAX_SKILL) && (sn > 0) )
                        lhsvl3 = skill_table[sn].slot;
                    else
                        lhsvl3 = 0;

                    rhsvl = atoi(val);

                    sprintf(bugbuf, "Mob %d: slotnum checking skills %d, %d, %d.", mob->pIndexData->vnum, lhsvl1, lhsvl2, lhsvl3);
                    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

                    return mprog_veval(lhsvl1, opr, rhsvl) 
                           || mprog_veval(lhsvl2, opr, rhsvl) 
                           || mprog_veval(lhsvl3, opr, rhsvl);
                }
                else
                    return -1;
            case 'p':
                if (v_obj)
                {
                    int sn, lhsvl1, lhsvl2, lhsvl3;

                    sn = v_obj->value[1];
                    if (sn <= MAX_SKILL)
                        lhsvl1 = skill_table[sn].slot;
                    else
                        lhsvl1 = 0;

                    sn = v_obj->value[2];
                    if (sn <= MAX_SKILL)
                        lhsvl2 = skill_table[sn].slot;
                    else
                        lhsvl2 = 0;

                    sn = v_obj->value[3];
                    if (sn <= MAX_SKILL)
                        lhsvl3 = skill_table[sn].slot;
                    else
                        lhsvl3 = 0;

                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl1, opr, rhsvl) 
                           || mprog_veval(lhsvl2, opr, rhsvl) 
                           || mprog_veval(lhsvl3, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'slotnum'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "number"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                lhsvl = mob->gold;
                rhsvl = atoi(val);
                return mprog_veval(lhsvl, opr, rhsvl);
            case 'n':
                if (actor)
                {
                    if IS_NPC
                        (actor)
                    {
                        lhsvl = actor->pIndexData->vnum;
                        rhsvl = atoi(val);
                        return mprog_veval(lhsvl, opr, rhsvl);
                    }
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    if IS_NPC
                        (actor)
                    {
                        lhsvl = vict->pIndexData->vnum;
                        rhsvl = atoi(val);
                        return mprog_veval(lhsvl, opr, rhsvl);
                    }
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    if IS_NPC
                        (actor)
                    {
                        lhsvl = rndm->pIndexData->vnum;
                        rhsvl = atoi(val);
                        return mprog_veval(lhsvl, opr, rhsvl);
                    }
                }
                else
                    return -1;
            case 'o':
                if (obj)
                {
                    lhsvl = obj->pIndexData->vnum;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            case 'p':
                if (v_obj)
                {
                    lhsvl = v_obj->pIndexData->vnum;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'number'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "race"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return mprog_seval(race_table[mob->race].name, opr, val);
            case 'n':
                if (actor)
                {
                    return mprog_seval(race_table[actor->race].name, opr, val);
                }
                else
                    return -1;
            case 't':
                if (vict)
                {
                    return mprog_seval(race_table[vict->race].name, opr, val);
                }
                else
                    return -1;
            case 'r':
                if (rndm)
                {
                    return mprog_seval(race_table[rndm->race].name, opr, val);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'race'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "clan"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'n':
                if (actor && !IS_NPC(actor))
                {
                    if (actor->pcdata->clan)
                        return mprog_seval(actor->pcdata->clan->name, opr, val);
                    else
                        return mprog_seval("NONE", opr, val);
                }
                else
                    return -1;

            default:
                bug("Mob: %d bad argument to 'clan'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "clanpoints"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'n':
                if (actor && !IS_NPC(actor))
                {
                    lhsvl = actor->pcdata->clan_points;
                    rhsvl = atoi(val);
                    return mprog_veval(lhsvl, opr, rhsvl);
                }
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'clanpoints'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "name"))
    {
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                return mprog_seval(mob->name, opr, val);
            case 'n':
                if (actor)
                    return mprog_seval(actor->name, opr, val);
                else
                    return -1;
            case 't':
                if (vict)
                    return mprog_seval(vict->name, opr, val);
                else
                    return -1;
            case 'r':
                if (rndm)
                    return mprog_seval(rndm->name, opr, val);
                else
                    return -1;
            case 'o':
                if (obj)
                    return mprog_seval(obj->name, opr, val);
                else
                    return -1;
            case 'p':
                if (v_obj)
                    return mprog_seval(v_obj->name, opr, val);
                else
                    return -1;
            default:
                bug("Mob: %d bad argument to 'name'", mob->pIndexData->vnum);
                return -1;
        }
    }

    if (!str_cmp(buf, "worn"))
    {   /* copied from 'has' */
        /* arg should be variable,vnum */
        char *p;
        OBJ_INDEX_DATA *pObjIndex;
        OBJ_DATA *qObj;
        int v;

        /* find the comma */
        for (p = arg; *p; p++)
            if (*p == ',')
                break;
        if (!*p)
        {
            bug("Mob: %d must have two arguments for 'worn'", mob->pIndexData->vnum);
            return -1;
        }
        p++;                    /* p now points to vnum */
        /* check valid first argument - only allow mob, actor, victim */
        switch (arg[1])         /* arg should be "$*" so just get the letter */
        {
            case 'i':
                target = mob;
                break;
            case 'n':
                target = actor;
                break;
            case 't':
                target = mob;  /* there was no assignment of target here
                                  but since this could lead to dereferencing
                                  NULL, I added this line.  Lorn, 9/98 */
                break;
            default:
                bug("Mob: %d bad argument to 'ifhas'", mob->pIndexData->vnum);
                return -1;
        }
        /* check second argument */
        v = atoi(p);

        sprintf(bugbuf, "Mob %d: ifworn searching for object %d.", mob->pIndexData->vnum,v);
        wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

        pObjIndex = get_obj_index(v);
        if (pObjIndex == NULL)
          {
            sprintf(bugbuf, "Mob %d: ifworn searching for invalid object %d.", mob->pIndexData->vnum,v);
            bug(bugbuf,0);
            return FALSE;
          }
        else
          for (qObj = target->carrying; qObj != NULL; qObj = qObj->next_content)
            {
              if ( (qObj->pIndexData->vnum == v) && (qObj->wear_loc != WEAR_NONE ) )

                {
                  return TRUE;
                }
            }
          return FALSE;
    }                           /* end of 'worn' */

    /* to see if a mob of given vnum (or name) is in room with mob */
    if (!str_cmp(buf, "mobhere"))
    {
        if ( is_number(arg) )
            return (get_mob_vnum_room(mob,NULL,NULL,atoi(arg)));
        else
            return ((bool) (get_char_room(mob,NULL,arg) != NULL));
    }

    /* Ok... all the ifchcks are done, so if we didnt find ours then something
     * odd happened.  So report the bug and abort the MOBprogram (return error)
     */
    bug("Mob: %d unknown ifchck", mob->pIndexData->vnum);
    return -1;

}
/* Quite a long and arduous function, this guy handles the control
 * flow part of MOBprograms.  Basicially once the driver sees an
 * 'if' attention shifts to here.  While many syntax errors are
 * caught, some will still get through due to the handling of break
 * and errors in the same fashion.  The desire to break out of the
 * recursion without catastrophe in the event of a mis-parse was
 * believed to be high. Thus, if an error is found, it is bugged and
 * the parser acts as though a break were issued and just bails out
 * at that point. I havent tested all the possibilites, so I'm speaking
 * in theory, but it is 'guaranteed' to work on syntactically correct
 * MOBprograms, so if the mud crashes here, check the mob carefully!
 */
char *mprog_process_if(char *ifchck, char *com_list, CHAR_DATA * mob,
                       CHAR_DATA * actor, OBJ_DATA * obj, void *vo,
                       CHAR_DATA * rndm)
{
    char buf[MAX_INPUT_LENGTH];
    char bugbuf[MAX_STRING_LENGTH];
    char *morebuf = '\0';
    char *cmnd = '\0';
    bool loopdone = FALSE;
    bool flag = FALSE;
    int legal;
    int nesting;

#ifdef DEBUG
    fprintf(stdout, "Evaluating <if %s> as ", ifchck);
#endif
    /* check for trueness of the ifcheck */
    if ((legal = mprog_do_ifchck(ifchck, mob, actor, obj, vo, rndm))) {
			if (legal == 1) {
				flag = TRUE;
			}
			else  {
            return null; 
						}
		}
						

    if (legal)
      sprintf(bugbuf, "Mob %d, 1 do_ifchck returns True.", mob->pIndexData->vnum);
    else
      sprintf(bugbuf, "Mob %d, 1 do_ifchck returns False.", mob->pIndexData->vnum);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

#ifdef DEBUG
    fprintf(stdout, "%c\n", flag ? 'T' : 'F');
#endif

    while (loopdone == FALSE)
    {                           /*scan over any existing or statements */
        cmnd = com_list;
        com_list = mprog_next_command(com_list);
        while (*cmnd == ' ')
            cmnd++;
        if (*cmnd == '\0')
        {
            bug("Mob: %d no commands after IF/OR", mob->pIndexData->vnum);
            return null;
        }
        morebuf = one_argument(cmnd, buf);
        if (!str_cmp(buf, "or"))
        {
					if ((legal = mprog_do_ifchck(morebuf, mob, actor, obj, vo, rndm))) {
						if (legal == 1) {
                    flag = TRUE;
						}
						else {
                    return null;
						}
					}
        }
        else
            loopdone = TRUE;
    }                           /* searching for OR */
// Lorn: buf now holds first argument (of first line after after initial if)
//       cmnd holds the entire first line after the initial if
//       morebuf holds everything in cmnd after buf
//       com_list holds everything after cmnd

    /* Lorn - this is confusing, print the damn stuff */
    sprintf(bugbuf, "mprog_proccess_if processing comlist after if of:\n\r%s\n\r",com_list);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

    if (flag)
        for (;;)
        {                       /*ifcheck was true, do commands but ignore else to endif */

    /* Lorn - this is confusing, print the damn stuff */
    sprintf(bugbuf, "mprog_proccess_if loop processing comlist:\n\r%s\n\r",com_list);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

            if (!str_cmp(buf, "if"))
            {
                com_list = mprog_process_if(morebuf, com_list, mob, actor, obj, vo, rndm);
                while (*cmnd == ' ')
                    cmnd++;
                if (*com_list == '\0')
                    return null;
                cmnd = com_list;
                com_list = mprog_next_command(com_list);
                morebuf = one_argument(cmnd, buf);
                continue;
            }                   /* found an if */

            if (!str_cmp(buf, "break"))
                return null;
            if (!str_cmp(buf, "endif"))
                return com_list;
            if (!str_cmp(buf, "else"))
            {

                /* Once the else statement is found, all the commands
                   and processess within the else clause must be skipped until
                   the endif is found.  The problem with the original
                   version is that it was not designed to handle additional
                   if statements included inside the original else clause.
                   --Lorn 9/99 */
                int extra_if_count = 0;
                if (!str_cmp(buf, "endif"))
                  {
                    sprintf(bugbuf, "Mob: %d possible bug: endif immediately following else", 
                            mob->pIndexData->vnum);
                    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
                  }
                else
                  {
                    while (extra_if_count >= 0)
                      {
                        if (!str_cmp(buf, "if"))
                          {
                            extra_if_count++;
                            sprintf(bugbuf, "extra_if_count now = %d.\n\r",extra_if_count);
                            wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
                          }
                        else if (!str_cmp(buf, "endif"))
                          {
                            extra_if_count--;
                            sprintf(bugbuf, "extra_if_count now = %d.\n\r",extra_if_count);
                            wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
                          }
                        cmnd = com_list;
                        com_list = mprog_next_command(com_list);
                        while (*cmnd == ' ')
                            cmnd++;
                        if (*cmnd == '\0')
                        {
                            bug("Mob: %d missing endif after else",
                                mob->pIndexData->vnum);
                            return null;
                        }
                        morebuf = one_argument(cmnd, buf);
                      }  /* end while counting if/endif pairs */
                  }  /* end not immediate endif */

/*
                while (str_cmp(buf, "endif"))
                {
                    cmnd = com_list;
                    com_list = mprog_next_command(com_list);
                    while (*cmnd == ' ')
                        cmnd++;
                    if (*cmnd == '\0')
                    {
                        bug("Mob: %d missing endif after else",
                            mob->pIndexData->vnum);
                        return null;
                    }
                    morebuf = one_argument(cmnd, buf);
                }           */    /* found endif */


                /* Lorn - this is confusing, print the damn stuff */
                sprintf(bugbuf, "mprog_proccess_if loop else end returns comlist: \n\r%s\n\r",com_list);
                wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

                return com_list;
            }                   /* found an else */

            mprog_process_cmnd(cmnd, mob, actor, obj, vo, rndm);
            cmnd = com_list;
            com_list = mprog_next_command(com_list);
            while (*cmnd == ' ')
                cmnd++;
            if (*cmnd == '\0')
            {
                bug("Mob: %d missing else or endif", mob->pIndexData->vnum);
                return null;
            }
            morebuf = one_argument(cmnd, buf);
        }                       /* for (;;) */
    else
    {
        /*false ifcheck, find else and do existing commands or quit at endif */
#ifdef DEBUG
        fprintf(stdout, "Skipping...\n%s %s\n", buf, morebuf);
#endif
        nesting = 1;

        while (nesting)
        {
            if (!str_cmp(buf, "if"))
              {
                nesting++;
                sprintf(bugbuf, "nesting now = %d.\n\r",nesting);
                wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
              }
            else if ((!str_cmp(buf, "endif")) || (!str_cmp(buf, "else")))
              {
                nesting--;
                sprintf(bugbuf, "nesting now = %d.\n\r",nesting);
                wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
              }
            if (nesting)
            {
                /* get next command line */
                cmnd = com_list;
                com_list = mprog_next_command(com_list);
#ifdef DEBUG
                fprintf(stdout, "%s\n", cmnd);
#endif
                while (*cmnd == ' ')
                    cmnd++;
                if (*cmnd == '\0')
                {
                    bug("Mob: %d missing an else or endif",
                        mob->pIndexData->vnum);
                    return null;
                }
                morebuf = one_argument(cmnd, buf);
            }                   /* still nesting */
        }                       /* while nesting */
#ifdef DEBUG
        fprintf(stdout, "End skip\n");
#endif
        /* found either an else or an endif.. act accordingly */
        if (!str_cmp(buf, "endif"))
            return com_list;

        /* must be an else */
        cmnd = com_list;
        com_list = mprog_next_command(com_list);
        while (*cmnd == ' ')
            cmnd++;
        if (*cmnd == '\0')
        {
            bug("Mob: %d missing endif", mob->pIndexData->vnum);
            return null;
        }

        morebuf = one_argument(cmnd, buf);

        for (;;)
        {                       /*process the post-else commands until an endif is found. */
            if (!str_cmp(buf, "if"))
            {
                com_list = mprog_process_if(morebuf, com_list, mob, actor,
                                            obj, vo, rndm);
                while (*cmnd == ' ')
                    cmnd++;
                if (*com_list == '\0')
                    return null;
                cmnd = com_list;
                com_list = mprog_next_command(com_list);
                morebuf = one_argument(cmnd, buf);
                continue;
            }                   /* found if */
            if (!str_cmp(buf, "else"))
            {
                bug("Mob: %d found else in an else section",
                    mob->pIndexData->vnum);
                return null;
            }                   /* found else */
            if (!str_cmp(buf, "break"))
                return null;
            if (!str_cmp(buf, "endif"))
                return com_list;
            mprog_process_cmnd(cmnd, mob, actor, obj, vo, rndm);
            cmnd = com_list;
            com_list = mprog_next_command(com_list);
            while (*cmnd == ' ')
                cmnd++;
            if (*cmnd == '\0')
            {
                bug("Mob:%d missing endif in else section",
                    mob->pIndexData->vnum);
                return null;
            }
            morebuf = one_argument(cmnd, buf);
        }                       /* for (;;) */
    }                           /* else if check was false */
}

/* This routine handles the variables for command expansion.
 * If you want to add any go right ahead, it should be fairly
 * clear how it is done and they are quite easy to do, so you
 * can be as creative as you want. The only catch is to check
 * that your variables exist before you use them. At the moment,
 * using $t when the secondary target refers to an object 
 * i.e. >prog_act drops~<nl>if ispc($t)<nl>sigh<nl>endif<nl>~<nl>
 * probably makes the mud crash (vice versa as well) The cure
 * would be to change act() so that vo becomes vict & v_obj.
 * but this would require a lot of small changes all over the code.
 */
void mprog_translate(char ch, char *t, CHAR_DATA * mob, CHAR_DATA * actor,
                     OBJ_DATA * obj, void *vo, CHAR_DATA * rndm)
{
    static char *he_she[] =
    {"it", "he", "she"};
    static char *him_her[] =
    {"it", "him", "her"};
    static char *his_her[] =
    {"its", "his", "her"};
    CHAR_DATA *vict = (CHAR_DATA *) vo;
    OBJ_DATA *v_obj = (OBJ_DATA *) vo;

    *t = '\0';
    switch (ch)
    {
        case 'i':
            one_argument(mob->name, t);
            break;

        case 'I':
            strcpy(t, mob->short_descr);
            break;

        case 'c':              /* clan */
					if (actor && !IS_NPC(actor)) {
						if (can_see(mob, actor)) {
							if (actor->pcdata->clan) {
                        one_argument(actor->pcdata->clan->name, t);
							}
							else {
                        one_argument("None", t);
							}
						}
					}
            *t = UPPER(*t);
            break;

        case 'n':
            if (actor)
                if (can_see(mob, actor))
                    one_argument(actor->name, t);
            if (!IS_NPC(actor))
                *t = UPPER(*t);
            break;

        case 'N':
					if (actor) {
						if (can_see(mob, actor)) {
							if (IS_NPC(actor)) {
                        strcpy(t, actor->short_descr);
							}
              else {
                strcpy(t, actor->name);
                strcat(t, " ");
                strcat(t, actor->pcdata->title);
              }
						}
            else {
							strcpy(t, "someone");
						}
					}
            break;

        case 't':
            if (vict)
                if (can_see(mob, vict))
                    one_argument(vict->name, t);
            if (!IS_NPC(vict))
                *t = UPPER(*t);
            break;

        case 'T':
					if (vict) {
						if (can_see(mob, vict)) {
							if (IS_NPC(vict)) {
                        strcpy(t, vict->short_descr);
							}
              else {
								strcpy(t, vict->name);
                strcat(t, " ");
                strcat(t, vict->pcdata->title);
              }
						}
						else {
                    strcpy(t, "someone");
						}
					}
            break;

        case 'r':
            if (rndm)
            {
                if (can_see(mob, rndm))
                    one_argument(rndm->name, t);
                if (!IS_NPC(rndm))
                    *t = UPPER(*t);
            }
            break;

        case 'R':
            if (rndm)
            {
                if (can_see(mob, rndm))
                    if (IS_NPC(rndm))
                        strcpy(t, rndm->short_descr);
                    else
                    {
                        strcpy(t, rndm->name);
                        strcat(t, " ");
                        strcat(t, rndm->pcdata->title);
                    }
                else
                    strcpy(t, "someone");
            }
            else
                strcpy(t, "someone");
            break;

        case 'e':
            if (actor)
                can_see(mob, actor) ? strcpy(t, he_she[actor->sex])
                    : strcpy(t, "someone");
            break;

        case 'm':
            if (actor)
                can_see(mob, actor) ? strcpy(t, him_her[actor->sex])
                    : strcpy(t, "someone");
            break;

        case 's':
            if (actor)
                can_see(mob, actor) ? strcpy(t, his_her[actor->sex])
                    : strcpy(t, "someone's");
            break;

        case 'E':
            if (vict)
                can_see(mob, vict) ? strcpy(t, he_she[vict->sex])
                    : strcpy(t, "someone");
            break;

        case 'M':
            if (vict)
                can_see(mob, vict) ? strcpy(t, him_her[vict->sex])
                    : strcpy(t, "someone");
            break;

        case 'S':
            if (vict)
                can_see(mob, vict) ? strcpy(t, his_her[vict->sex])
                    : strcpy(t, "someone's");
            break;

        case 'j':
            strcpy(t, he_she[mob->sex]);
            break;

        case 'k':
            strcpy(t, him_her[mob->sex]);
            break;

        case 'l':
            strcpy(t, his_her[mob->sex]);
            break;

        case 'J':
            if (rndm)
                can_see(mob, rndm) ? strcpy(t, he_she[rndm->sex])
                    : strcpy(t, "someone");
            break;

        case 'K':
            if (rndm)
                can_see(mob, rndm) ? strcpy(t, him_her[rndm->sex])
                    : strcpy(t, "someone");
            break;

        case 'L':
            if (rndm)
                can_see(mob, rndm) ? strcpy(t, his_her[rndm->sex])
                    : strcpy(t, "someone's");
            break;

        case 'o':
            if (obj)
                can_see_obj(mob, obj) ? one_argument(obj->name, t)
                    : strcpy(t, "something");
            break;

        case 'O':
            if (obj)
                can_see_obj(mob, obj) ? strcpy(t, obj->short_descr)
                    : strcpy(t, "something");
            break;

        case 'p':
            if (v_obj)
                can_see_obj(mob, v_obj) ? one_argument(v_obj->name, t)
                    : strcpy(t, "something");
            break;

        case 'P':
            if (v_obj)
                can_see_obj(mob, v_obj) ? strcpy(t, v_obj->short_descr)
                    : strcpy(t, "something");
            break;

        case 'a':
            if (obj)
                switch (*(obj->name))
                {
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        strcpy(t, "an");
                        break;
                    default:
                        strcpy(t, "a");
                }
            break;

        case 'A':
            if (v_obj)
                switch (*(v_obj->name))
                {
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        strcpy(t, "an");
                        break;
                    default:
                        strcpy(t, "a");
                }
            break;

        case '$':
            strcpy(t, "$");
            break;

        default:
            bug("Mob: %d bad $var", mob->pIndexData->vnum);
            break;
    }

    return;

}

/* This procedure simply copies the cmnd to a buffer while expanding
 * any variables by calling the translate procedure.  The observant
 * code scrutinizer will notice that this is taken from act()
 */
void mprog_process_cmnd(char *cmnd, CHAR_DATA * mob, CHAR_DATA * actor,
                        OBJ_DATA * obj, void *vo, CHAR_DATA * rndm)
{
    char buf[MAX_INPUT_LENGTH];
    char tmp[MAX_INPUT_LENGTH];
    char *str;
    char *i;
    char *point;
    char bugbuf[MAX_STRING_LENGTH];

    point = buf;
    str = cmnd;

    while (*str != '\0')
    {
        if (*str != '$')
        {
            *point++ = *str++;
            continue;
        }
        str++;
        mprog_translate(*str, tmp, mob, actor, obj, vo, rndm);
        i = tmp;
        ++str;
        while ((*point = *i) != '\0')
            ++point, ++i;
    }
    *point = '\0';

    sprintf(bugbuf, "Mob %d: process_cmnd calling interpret", mob->pIndexData->vnum);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

    interpret(mob, buf, 2);

    return;

}

/* The main focus of the MOBprograms.  This routine is called 
 *  whenever a trigger is successful.  It is responsible for parsing
 *  the command list and figuring out what to do. However, like all
 *  complex procedures, everything is farmed out to the other guys.
 */
void mprog_driver(char *com_list, CHAR_DATA * mob, CHAR_DATA * actor,
                  OBJ_DATA * obj, void *vo)
{

    char tmpcmndlst[MAX_STRING_LENGTH];
    char buf[MAX_INPUT_LENGTH];
    char *morebuf;
    char *command_list;
    char *cmnd;
    CHAR_DATA *rndm = NULL;
    CHAR_DATA *vch = NULL;
    int count = 0;
    char bugbuf[MAX_STRING_LENGTH];
    bool failure = TRUE;    /* added in revision 3 */

    if IS_AFFECTED
        (mob, AFF_CHARM)
            return;

    /* get a random visable mortal player who is in the room with the mob */
    for (vch = mob->in_room->people; vch; vch = vch->next_in_room)
        if (!IS_NPC(vch)
            && vch->level < MAX_LEVEL - 3
            && can_see(mob, vch))
        {
            if (number_range(0, count) == 0)
                rndm = vch;
            count++;
        }

    /* added in revision 3 */
/*    sprintf(bugbuf, "mprog_driver received comlist:\n\r%s\n\r",com_list);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
*/
    strcpy(tmpcmndlst, com_list);
    command_list = tmpcmndlst;
    cmnd = command_list;

    /* added in revision 3 */
/*    sprintf(bugbuf, "mprog_driver: processing command_list:\n\r%s\n\r",command_list);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
*/
    command_list = mprog_next_command(command_list);
    while (*cmnd != '\0')
    {
        failure = FALSE;  /* added in revision 3 */
        morebuf = one_argument(cmnd, buf);
        if (!str_cmp(buf, "if"))
          {            
            sprintf(bugbuf, "Mob %d: mprog_driver calls process_if", mob->pIndexData->vnum);
            wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
          
            command_list = mprog_process_if(morebuf, command_list, mob,
                                            actor, obj, vo, rndm);
          }
        else
          {            
            sprintf(bugbuf, "Mob %d: mprog_driver calls process_cmnd", mob->pIndexData->vnum);
            wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
          
            mprog_process_cmnd(cmnd, mob, actor, obj, vo, rndm);
          }
        cmnd = command_list;
        command_list = mprog_next_command(command_list);
    }

    /* added in revision 3 */
    if (failure)
      {
        sprintf(bugbuf, "mprog_driver: failure, cmnd = %s <<<>>>",cmnd);
        wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
      }

    return;

}

/***************************************************************************
 * Global function code and brief comments.
 */

/* The next two routines are the basic trigger types. Either trigger
 *  on a certain percent, or trigger on a keyword or word phrase.
 *  To see how this works, look at the various trigger routines..
 */
void mprog_wordlist_check(char *arg, CHAR_DATA * mob, CHAR_DATA * actor,
                          OBJ_DATA * obj, void *vo, int type)
{

    char temp1[MAX_STRING_LENGTH];
    char temp2[MAX_INPUT_LENGTH];
    char word[MAX_INPUT_LENGTH];
    MPROG_DATA *mprg;
    char *list;
    char *start;
    char *dupl;
    char *end;
    int i;
    char bugbuf[MAX_STRING_LENGTH];

    if (!IS_NPC(mob))
      {
        bug("mprog_wordlist_check called on player!",0);
        return;
      }
    sprintf(bugbuf, "Mob %d: wordlist check of type %d.", mob->pIndexData->vnum, type);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);

    for (mprg = mob->pIndexData->mobprogs; mprg != NULL; mprg = mprg->next)
        if (mprg->type & type)
        {
            strcpy(temp1, mprg->arglist);
            list = temp1;
            for (i = 0; i < strlen(list); i++)
                list[i] = LOWER(list[i]);
            strcpy(temp2, arg);
            dupl = temp2;
            for (i = 0; i < strlen(dupl); i++)
                dupl[i] = LOWER(dupl[i]);
            if ((list[0] == 'p') && (list[1] == ' '))
            {
                list += 2;
                while ((start = strstr(dupl, list)))
                    if ((start == dupl || *(start - 1) == ' ')
                        && ((*(end = start + strlen(list)) == ' ')
                            || (*end == '\n')
                            || (*end == '\r')
                            || (*end == '\0') ))
                    {
    sprintf(bugbuf, "Mob %d: wordlist_check p calls driver.", mob->pIndexData->vnum);
    wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
                        mprog_driver(mprg->comlist, mob, actor, obj, vo);
                        break;
                    }
                    else
                        dupl = start + 1;
            }
            else
            {
                list = one_argument(list, word);
                for (; word[0] != '\0'; list = one_argument(list, word))
                    while ((start = strstr(dupl, word)))
                        if ((start == dupl || *(start - 1) == ' ')
			    /*  Changed following line.  . Ivan 2/10/99 
                                && (((end = start + strlen(word)) == NULL) */
			    && ( *(end = start + strlen(word)) == '\0'
                              || (*end == '\n')
                              || (*end == '\r')
                              || (*end == ' ')))
                        {
			  sprintf(bugbuf, "Mob %d: wordlist_check calls driver.", mob->pIndexData->vnum);
			  wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
			  mprog_driver(mprg->comlist, mob, actor, obj, vo);
			  break;
                        }
                        else
                            dupl = start + 1;
            }
        }

    return;

}

void mprog_percent_check(CHAR_DATA * mob, CHAR_DATA * actor, OBJ_DATA * obj,
                         void *vo, int type)
{
    MPROG_DATA *mprg;
    char bugbuf[MAX_STRING_LENGTH];
    if (!IS_NPC(mob))
      {
        bug("mprog_percent_check called on player!",0);
        return;
      }
    if (type != RAND_PROG) 
      {
        sprintf(bugbuf, "Mob %d: percent check of type %d.", mob->pIndexData->vnum, type);
        wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
      }

    for (mprg = mob->pIndexData->mobprogs; mprg != NULL; mprg = mprg->next)
        if ((mprg->type & type)
            && (number_percent() < atoi(mprg->arglist)))
        {
            if (type != RAND_PROG) 
              {
                sprintf(bugbuf, "Mob %d: percent_check calling mprog_driver. ", mob->pIndexData->vnum);
                wiznet(bugbuf, NULL, NULL, WIZ_MOBS, 0, 0);
              }
            mprog_driver(mprg->comlist, mob, actor, obj, vo);
            if (type != GREET_PROG && type != ALL_GREET_PROG)
                break;
        }

    return;

}

/* The triggers.. These are really basic, and since most appear only
 * once in the code (hmm. i think they all do) it would be more efficient
 * to substitute the code in and make the mprog_xxx_check routines global.
 * However, they are all here in one nice place at the moment to make it
 * easier to see what they look like. If you do substitute them back in,
 * make sure you remember to modify the variable names to the ones in the
 * trigger calls.
 */
void mprog_act_trigger(char *buf, CHAR_DATA * mob, CHAR_DATA * ch,
                       OBJ_DATA * obj, void *vo)
{

    MPROG_ACT_LIST *tmp_act;

    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & ACT_PROG))
    {
        tmp_act = alloc_mem(sizeof(MPROG_ACT_LIST));
        if (mob->mpactnum > 0)
            /*      tmp_act->next = mob->mpact->next; CND 12/4/96 */
            tmp_act->next = mob->mpact;
        else
            tmp_act->next = NULL;

        mob->mpact = tmp_act;
        mob->mpact->buf = str_dup(buf);
        mob->mpact->ch = ch;
        mob->mpact->obj = obj;
        mob->mpact->vo = vo;
        mob->mpactnum++;

    }
    return;

}

void mprog_bribe_trigger(CHAR_DATA * mob, CHAR_DATA * ch, int amount)
{

    char buf[MAX_STRING_LENGTH];
    MPROG_DATA *mprg;
    OBJ_DATA *obj;

    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & BRIBE_PROG))
    {
        obj = create_object(get_obj_index(OBJ_VNUM_MONEY_SOME), 0);
        sprintf(buf, obj->short_descr, amount);
        free_string(obj->short_descr);
        obj->short_descr = str_dup(buf);
        obj->value[0] = amount;
        obj_to_char(obj, mob);
        mob->gold -= amount;

        for (mprg = mob->pIndexData->mobprogs; mprg != NULL; mprg = mprg->next)
            if ((mprg->type & BRIBE_PROG)
                && (amount >= atoi(mprg->arglist)))
            {
                mprog_driver(mprg->comlist, mob, ch, obj, NULL);
                break;
            }
    }

    return;

}

void mprog_death_trigger(CHAR_DATA * mob, CHAR_DATA * actor)
{

    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & DEATH_PROG))
    {
      mob->wait = 0;
      mprog_percent_check(mob, actor, NULL, NULL, DEATH_PROG);
    }

    death_cry(mob);
    return;

}

void mprog_entry_trigger(CHAR_DATA * mob)
{

    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & ENTRY_PROG))
        mprog_percent_check(mob, NULL, NULL, NULL, ENTRY_PROG);

    return;

}

void mprog_fight_trigger(CHAR_DATA * mob, CHAR_DATA * ch)
{

    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & FIGHT_PROG))
        mprog_percent_check(mob, ch, NULL, NULL, FIGHT_PROG);

    return;

}

void mprog_give_trigger(CHAR_DATA * mob, CHAR_DATA * ch, OBJ_DATA * obj)
{

    char buf[MAX_INPUT_LENGTH];
    MPROG_DATA *mprg;

    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & GIVE_PROG))
        for (mprg = mob->pIndexData->mobprogs; mprg != NULL; mprg = mprg->next)
        {
            one_argument(mprg->arglist, buf);
            if ((mprg->type & GIVE_PROG)
                && ((!str_cmp(obj->name, mprg->arglist))
                    || (!str_cmp("all", buf))))
            {
                mprog_driver(mprg->comlist, mob, ch, obj, NULL);
                break;
            }
        }

    return;

}

void mprog_greet_trigger(CHAR_DATA * ch)
{

    CHAR_DATA *vmob;

    for (vmob = ch->in_room->people; vmob != NULL; vmob = vmob->next_in_room)
        if (IS_NPC(vmob)
            && ch != vmob
            && can_see(vmob, ch)
            && (vmob->fighting == NULL)
            && IS_AWAKE(vmob)
            && (vmob->pIndexData->progtypes & GREET_PROG))
            mprog_percent_check(vmob, ch, NULL, NULL, GREET_PROG);
        else if (IS_NPC(vmob)
                 && (vmob->fighting == NULL)
                 && IS_AWAKE(vmob)
                 && (vmob->pIndexData->progtypes & ALL_GREET_PROG))
            mprog_percent_check(vmob, ch, NULL, NULL, ALL_GREET_PROG);

    return;

}

void mprog_hitprcnt_trigger(CHAR_DATA * mob, CHAR_DATA * ch)
{

    MPROG_DATA *mprg;

    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & HITPRCNT_PROG))
        for (mprg = mob->pIndexData->mobprogs; mprg != NULL; mprg = mprg->next)
            if ((mprg->type & HITPRCNT_PROG)
                && ((100 * mob->hit / mob->max_hit) < atoi(mprg->arglist)))
            {
                mprog_driver(mprg->comlist, mob, ch, NULL, NULL);
                break;
            }

    return;

}

void mprog_random_trigger(CHAR_DATA * mob)
{

    if (mob->pIndexData->progtypes & RAND_PROG)
        mprog_percent_check(mob, NULL, NULL, NULL, RAND_PROG);

    return;

}

void mprog_speech_trigger(char *txt, CHAR_DATA * mob)
{

    CHAR_DATA *vmob;

    for (vmob = mob->in_room->people; vmob != NULL; vmob = vmob->next_in_room)
        if (IS_NPC(vmob) && (vmob->pIndexData->progtypes & SPEECH_PROG))
            if (vmob != mob)
                mprog_wordlist_check(txt, vmob, mob, NULL, NULL, SPEECH_PROG);

    return;

}

void mprog_give_word_trigger(CHAR_DATA * mob, CHAR_DATA * giver, OBJ_DATA * obj)
{
    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & GIVE_WORD_PROG))
        mprog_wordlist_check(obj->name, mob, giver, obj, NULL, GIVE_WORD_PROG);

    return;
}

/* bored_trigger copied from death_trigger March 2000 by Lorn */
void mprog_bored_trigger(CHAR_DATA * mob)
{
    if (IS_NPC(mob)
        && (mob->pIndexData->progtypes & BORED_PROG))
    {
      mob->wait = 0;
      mprog_percent_check(mob, NULL, NULL, NULL, BORED_PROG);
    }

    return;
}


bool mprog_exit_trigger(CHAR_DATA *ch, int dir)
{
    CHAR_DATA *mob;
    MPROG_DATA *mprg;

    for ( mob = ch->in_room->people; mob != NULL; mob = mob->next_in_room )
    {
        if ( IS_NPC( mob )
        &&  ( mob->pIndexData->progtypes & EXIT_PROG
           || mob->pIndexData->progtypes & EXALL_PROG ) )
        {
            for (mprg = mob->pIndexData->mobprogs; mprg != NULL; mprg = mprg->next)
            {
                /*
                 * Exit trigger works only if the mobile is not busy
                 * (fighting etc.). If you want to be sure all players
                 * are caught, use ExAll trigger
                 */
                if ( mprg->type == EXIT_PROG
                &&  dir == atoi( mprg->arglist )
                &&  mob->position == mob->pIndexData->default_pos
                &&  can_see( mob, ch ) )
                {
                    mprog_driver(mprg->comlist, mob, ch, NULL, NULL);
                    return TRUE;
                }
                else if ( mprg->type == EXALL_PROG
                &&   dir == atoi( mprg->arglist ) )
                {
                    mprog_driver(mprg->comlist, mob, ch, NULL, NULL);
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/* Added by Coy 8/01 for isaff mobprog condition */
int mp_aff_translate(int aff) {

	/* Translated affect number (return value) */
	int trans;

	switch (aff) {
	case 1:
	case 33:
		trans = A;
		break;
	case 2:
	case 34:
		trans = B;
		break;
	case 3:
	case 35:
		trans = C;
		break;
	case 4:
	case 36:
		trans = D;
		break;
	case 5:
	case 37:
		trans = E;
		break;
	case 6:
	case 38:
		trans = F;
		break;
	case 7:
	case 39:
		trans = G;
		break;
	case 8:
	case 40:
		trans = H;
		break;
	case 9:
	case 41:
		trans = I;
		break;
	case 10:
	case 42:
		trans = J;
		break;
	case 11:
	case 43:
		trans = K;
		break;
	case 12:
	case 44:
		trans = L;
		break;
	case 13:
	case 45:
		trans = M;
		break;
	case 14:
	case 46:
		trans = N;
		break;
	case 15:
	case 47:
		trans = O;
		break;
	case 16:
	case 48:
		trans = P;
		break;
	case 17:
		trans = Q;
		break;
	case 18:
	case 49:
		trans = R;
		break;
	case 19:
	case 50:
		trans = S;
		break;
	case 20:
	case 51:
		trans = T;
		break;
	case 21:
	case 52:
		trans = U;
		break;
	case 22:
	case 53:
		trans = V;
		break;
	case 23:
		trans = W;
		break;
	case 24:
	case 54:
		trans = X;
		break;
	case 25:
		trans = Y;
		break;
	case 26:
		trans = Z;
		break;
	case 27:
		trans = aa;
		break;
	case 28:
		trans = bb;
		break;
	case 29:
		trans = cc;
		break;
	case 30:
		trans = dd;
		break;
	case 31:
		trans = ee;
		break;
/*	case 32:
		trans = ff;
		break;
*/
	default:
		trans = 0;
		break;
	}
	
	return trans;
}
