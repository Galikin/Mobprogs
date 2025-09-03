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
 *  such installation can be found in INSTALL.  Enjoy........    N'Atas-Ha *
 ***************************************************************************/

/*
 * $Log: mob_commands.c,v $
 * Revision 1.15  2003/08/13 18:00:20  sjofn
 * changed family notes to kvetsh notes -Neut
 *
 * Revision 1.14  2003/07/22 00:29:08  coyotilo
 * Coy: Updated groups (after spell loss), remove rm2 command from mortals,
 * and made cloaked mobprogs visible to Deity and up.
 *
 * Revision 1.13  2003/05/27 04:31:19  mull
 * Mull: Added new mobprog commands - mpgforce and mpgtransfer,
 * 	to manipulate a whole group of players at once.
 *
 * Revision 1.12  2003/05/17 04:46:32  mull
 * Mull: Added exit/exall trigger type for mobprogs
 *
 * Revision 1.11  2002/12/18 16:01:27  coyotilo
 * Coy: Added object and room progs.
 *
 * Revision 1.10  2001/09/24 08:39:25  coyotilo
 * Coy: More fixes from code mixup.
 *
 * Revision 1.8  2001/09/12 05:13:18  coyotilo
 * Coy: Mostly bard stuff, got rid of some compile time warnings, fix
 * to calm, and some misc. special projects.
 *
 * Revision 1.7  2001/07/16 21:50:39  coyotilo
 * Coy: Added fail messages to Damned Blade, fixed a typo in the msg
 * for the peace command.  Worked with the code for perm affects
 * on eq, should be much better now (removing an item with a perm
 * affect does not remove all perm affects of the same type, also
 * removing an item manually (ie typing remove ring when the ring had
 * a perm affect could mess the characters stats) shouldn't cause
 * problems).
 *
 * Revision 1.6  2001/02/24 23:16:33  coyotilo
 * Coy: Fixed mass blindness bug, added functionality to
 * MPTRANSFER, and fixed something with transfer.
 *
 * Revision 1.5  2000/06/18 22:27:40  lorn
 * Lorn: rescue, mpcast, force version update to maintain sanity
 *
 * Revision 1.4  2000/03/30 17:26:35  lorn
 * Lorn: animate dead and bored_prog
 *
 * Revision 1.3  1999/09/06 07:31:50  cvsuser
 * give_word_prog created and motorball repairs
 *
 * Revision 1.2  1999/04/01 03:13:11  cvsuser
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

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merc.h"
#include "interp.h"

/* external functions */
void reset_area args((AREA_DATA * pArea));

/*
 * Local functions.
 */

char *mprog_type_to_name args((int type));
ROOM_INDEX_DATA *find_location args((CHAR_DATA * ch, char *arg));
void death_cry args((CHAR_DATA * ch));
void do_transfer args((CHAR_DATA * ch, char *argument));

/* This routine transfers between alpha and numeric forms of the
 *  mob_prog bitvector types. It allows the words to show up in mpstat to
 *  make it just a hair bit easier to see what a mob should be doing.
 */

char *mprog_type_to_name(int type)
{
    switch (type)
    {
        case IN_FILE_PROG:
            return "in_file_prog";
        case ACT_PROG:
            return "act_prog";
        case SPEECH_PROG:
            return "speech_prog";
        case RAND_PROG:
            return "rand_prog";
        case FIGHT_PROG:
            return "fight_prog";
        case HITPRCNT_PROG:
            return "hitprcnt_prog";
        case DEATH_PROG:
            return "death_prog";
        case ENTRY_PROG:
            return "entry_prog";
        case GREET_PROG:
            return "greet_prog";
        case ALL_GREET_PROG:
            return "all_greet_prog";
        case GIVE_PROG:
            return "give_prog";
        case BRIBE_PROG:
            return "bribe_prog";
        case GIVE_WORD_PROG:
            return "give_word_prog";
        case BORED_PROG:
            return "bored_prog";
	case EXIT_PROG:
            return "exit_prog";
    	case EXALL_PROG:
            return "exall_prog";
    	default:
            return "ERROR_PROG";
    }
}


/*
 * Prints the argument to all active players in the game
 *
 * Syntax: mob gecho [string]
 */
void do_mpgecho( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;

    if ( argument[0] == '\0' )
    {
	bug( "MpGEcho: missing argument from vnum %d",
	    IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }

    for ( d = descriptor_list; d; d = d->next )
    {
	if ( d->connected == CON_PLAYING )
 	{
	    if ( IS_IMMORTAL(d->character) )
		send_to_char( "Mob echo> ", d->character );
	    send_to_char( argument, d->character );
	    send_to_char( "\n\r", d->character );
	}
    }
}

/*
 * Prints the argument to all players in the same area as the mob
 *
 * Syntax: mob zecho [string]
 */
void do_mpzecho( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;

    if ( argument[0] == '\0' )
    {
	bug( "MpZEcho: missing argument from vnum %d",
	    IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }

    if ( ch->in_room == NULL )
	return;

    for ( d = descriptor_list; d; d = d->next )
    {
	if ( d->connected == CON_PLAYING 
	&&   d->character->in_room != NULL 
	&&   d->character->in_room->area == ch->in_room->area )
 	{
	    if ( IS_IMMORTAL(d->character) )
		send_to_char( "Mob echo> ", d->character );
	    send_to_char( argument, d->character );
	    send_to_char( "\n\r", d->character );
	}
    }
}

/*
 * Lets the mobile assist another mob or player
 *
 * Syntax: mob assist [character]
 */
void do_mpassist( CHAR_DATA *ch, char *argument )
{
    char      arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;

    one_argument( argument, arg );

    if ( arg[0] == '\0' )
	return;

    if ( ( victim = prog_char_room( ch, NULL, arg ) ) == NULL )
	return;

    if ( victim == ch || ch->fighting != NULL || victim->fighting == NULL )
	return;

    multi_hit( ch, victim->fighting, TYPE_UNDEFINED );
    return;
}
/*
*
 * Lets the mobile to transfer an object. The object must be in the same
 * room with the mobile.
 *
 * Syntax: mob otransfer [item name] [location]
 */
void do_mpotransfer( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    ROOM_INDEX_DATA *location;
    char arg[ MAX_INPUT_LENGTH ];
    char buf[ MAX_INPUT_LENGTH ];

    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	bug( "MpOTransfer - Missing argument from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    one_argument( argument, buf );
    if ( ( location = find_location( ch, buf ) ) == NULL )
    {
	bug( "MpOTransfer - No such location from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    if ( (obj = get_obj_here( ch, NULL, arg )) == NULL )
	return;
    if ( obj->carried_by == NULL )
	obj_from_room( obj );
    else
    {
	if ( obj->wear_loc != WEAR_NONE )
	    unequip_char( ch, obj );
	obj_from_char( obj );
    }
    obj_to_room( obj, location );
}

/*
 * Forces all mobiles of certain vnum to do something (except ch)
 *
 * Syntax: mob vforce [vnum] [commands]
 */
void do_mpvforce( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim, *victim_next;
    char arg[ MAX_INPUT_LENGTH ];
    int vnum;

    argument = one_argument( argument, arg );

    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
	bug( "MpVforce - Bad syntax from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }

    if ( !is_number( arg ) )
    {
	bug( "MpVforce - Non-number argument vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }

    vnum = atoi( arg );

    for ( victim = char_list; victim; victim = victim_next )
    {
	victim_next = victim->next;
	if ( IS_NPC(victim) && victim->pIndexData->vnum == vnum
	&&   ch != victim && victim->fighting == NULL )
	    interpret( victim, argument, 0 );
    }
    return;
}

/*
 * Lets mob cause unconditional damage to someone. Nasty, use with caution.
 * Also, this is silent, you must show your own damage message...
 *
 * Syntax: mob damage [victim] [min] [max] {kill}
 */
void do_mpdamage( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim = NULL, *victim_next;
    char target[ MAX_INPUT_LENGTH ],
	 min[ MAX_INPUT_LENGTH ],
	 max[ MAX_INPUT_LENGTH ];
    int low, high;
    bool fAll = FALSE, fKill = FALSE;

    argument = one_argument( argument, target );
    argument = one_argument( argument, min );
    argument = one_argument( argument, max );

    if ( target[0] == '\0' )
    {
	bug( "MpDamage - Bad syntax from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    if( !str_cmp( target, "all" ) )
	fAll = TRUE;
    else if( ( victim = prog_char_room( ch, NULL, target ) ) == NULL )
	return;

    if ( is_number( min ) )
	low = atoi( min );
    else
    {
	bug( "MpDamage - Bad damage min vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    if ( is_number( max ) )
	high = atoi( max );
    else
    {
	bug( "MpDamage - Bad damage max vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    one_argument( argument, target );

    /*
     * If kill parameter is omitted, this command is "safe" and will not
     * kill the victim.
     */

    if ( target[0] != '\0' )
	fKill = TRUE;
    if ( fAll )
    {
	for( victim = ch->in_room->people; victim; victim = victim_next )
	{
	    victim_next = victim->next_in_room;
	    if ( victim != ch )
    		damage( victim, victim, 
		    fKill ? 
		    number_range(low,high) : UMIN(victim->hit,number_range(low,high)),
	        TYPE_UNDEFINED, DAM_NONE, FALSE );
	}
    }
    else
    	damage( victim, victim, 
	    fKill ? 
	    number_range(low,high) : UMIN(victim->hit,number_range(low,high)),
        TYPE_UNDEFINED, DAM_NONE, FALSE );
    return;
}

/*
 * Lets the mobile to remember a target. The target can be referred to
 * with $q and $Q codes in MOBprograms. See also "mob forget".
 *
 * Syntax: mob remember [victim]
 */
void do_mpremember( CHAR_DATA *ch, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    one_argument( argument, arg );
    if ( arg[0] != '\0' )
	ch->mprog_target = get_char_world( ch, arg );
    else
	bug( "MpRemember: missing argument from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
}

/*
 * Reverse of "mob remember".
 *
 * Syntax: mob forget
 */
void do_mpforget( CHAR_DATA *ch, char *argument )
{
    ch->mprog_target = NULL;
}
/*
 * Sets a delay for MOBprogram execution. When the delay time expires,
 * the mobile is checked for a MObprogram with DELAY trigger, and if
 * one is found, it is executed. Delay is counted in PULSE_MOBILE
 *
 * Syntax: mob delay [pulses]
 */
void do_mpdelay( CHAR_DATA *ch, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];

    one_argument( argument, arg );
    if ( !is_number( arg ) )
    {
	bug( "MpDelay: invalid arg from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    ch->mprog_delay = atoi( arg );
}

/*
 * Reverse of "mob delay", deactivates the timer.
 *
 * Syntax: mob cancel
 */
void do_mpcancel( CHAR_DATA *ch, char *argument )
{
   ch->mprog_delay = -1;
}
/*
 * Lets the mobile to call another MOBprogram withing a MOBprogram.
 * This is a crude way to implement subroutines/functions. Beware of
 * nested loops and unwanted triggerings... Stack usage might be a problem.
 * Characters and objects referred to must be in the same room with the
 * mobile.
 *
 * Syntax: mob call [vnum] [victim|'null'] [object1|'null'] [object2|'null']
 *
 */
void do_mpcall( CHAR_DATA *ch, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *vch;
    OBJ_DATA *obj1, *obj2;
    PROG_CODE *prg;
    extern void program_flow( sh_int, char *, CHAR_DATA *, OBJ_DATA *, ROOM_INDEX_DATA *, CHAR_DATA *, const void *, const void * );

    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	bug( "MpCall: missing arguments from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    if ( ( prg = get_prog_index( atoi(arg), PRG_MPROG ) ) == NULL )
    {
	bug( "MpCall: invalid prog from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    vch = NULL;
    obj1 = obj2 = NULL;
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
        vch = prog_char_room( ch, NULL, arg );
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
    	obj1 = get_obj_here( ch, NULL, arg );
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
    	obj2 = get_obj_here( ch, NULL, arg );
    program_flow( prg->vnum, prg->code, ch, NULL, NULL, vch, (void *)obj1, (void *)obj2 );
}

/*
 * Forces the mobile to flee.
 *
 * Syntax: mob flee
 *
 */
void do_mpflee( CHAR_DATA *ch, char *argument )
{
    ROOM_INDEX_DATA *was_in;
    EXIT_DATA *pexit;
    int door, attempt;

    if ( ch->fighting != NULL )
	return;

    if ( (was_in = ch->in_room) == NULL )
	return;

    for ( attempt = 0; attempt < 6; attempt++ )
    {
        door = number_door( );
        if ( ( pexit = was_in->exit[door] ) == 0
        ||   pexit->u1.to_room == NULL
        ||   IS_SET(pexit->exit_info, EX_CLOSED)
        || ( IS_NPC(ch)
        &&   IS_SET(pexit->u1.to_room->room_flags, ROOM_NO_MOB) ) )
            continue;

        move_char( ch, door, FALSE );
        if ( ch->in_room != was_in )
	    return;
    }
}
/*
 * Lets the mobile to strip an object or all objects from the victim.
 * Useful for removing e.g. quest objects from a character.
 *
 * Syntax: mob remove [victim] [object vnum|'all']
 */
void do_mpremove( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA *obj, *obj_next;
    sh_int vnum = 0;
    bool fAll = FALSE;
    char arg[ MAX_INPUT_LENGTH ];

    argument = one_argument( argument, arg );
    if ( ( victim = prog_char_room( ch, NULL, arg ) ) == NULL )
	return;

    one_argument( argument, arg );
    if ( !str_cmp( arg, "all" ) )
	fAll = TRUE;
    else if ( !is_number( arg ) )
    {
	bug ( "MpRemove: Invalid object from vnum %d.", 
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }
    else
	vnum = atoi( arg );

    for ( obj = victim->carrying; obj; obj = obj_next )
    {
	obj_next = obj->next_content;
	if ( fAll || obj->pIndexData->vnum == vnum )
	{
	     unequip_char( victim, obj );
	     obj_from_char( obj );
	     extract_obj( obj );
	}
    }
}

/* prints the argument to all the rooms aroud the mobile */

void do_mpasound(CHAR_DATA * ch, char *argument)
{

    ROOM_INDEX_DATA *was_in_room;
    int door;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    if (argument[0] == '\0')
    {
        bug("Mpasound - No argument: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    was_in_room = ch->in_room;
    for (door = 0; door <= 5; door++)
    {
        EXIT_DATA *pexit;

        if ((pexit = was_in_room->exit[door]) != NULL
            && pexit->u1.to_room != NULL
            && pexit->u1.to_room != was_in_room)
        {
            ch->in_room = pexit->u1.to_room;
            MOBtrigger = FALSE;
            act(argument, ch, NULL, NULL, TO_ROOM);
        }
    }

    ch->in_room = was_in_room;
    return;

}

/* lets the mobile kill any player or mobile without murder */

void do_mpkill(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    one_argument(argument, arg);

    if (arg[0] == '\0')
    {
        bug("MpKill - no argument: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if ((victim = get_char_room(ch, NULL, arg)) == NULL)
    {
        bug("MpKill - Victim not in room: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if (victim == ch)
    {
        bug("MpKill - Bad victim to attack: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if (IS_AFFECTED(ch, AFF_CHARM) && ch->master == victim)
    {
        bug("MpKill - Charmed mob attacking master: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if (ch->position == POS_FIGHTING)
    {
        bug("MpKill - Already fighting: vnum %d",
            ch->pIndexData->vnum);
        return;
    }

    bug("MpKill reached call to multi_hit: vnum %d",
	ch->pIndexData->vnum);
    /*    return; Ivan testing 1/20/99 */

    multi_hit(ch, victim, TYPE_UNDEFINED);
    return;
}

/* lets the mobile destroy an object in its inventory
 * it can also destroy a worn object and it can destroy 
 * items using all.xxxxx or just plain all of them */

void do_mpjunk(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    one_argument(argument, arg);

    if (arg[0] == '\0')
    {
        bug("Mpjunk - No argument: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if (str_cmp(arg, "all") && str_prefix("all.", arg))
    {
        if ((obj = get_obj_wear(ch, arg, TRUE)) != NULL)
        {
            unequip_char(ch, obj);
            extract_obj(obj);
            return;
        }
        if ((obj = get_obj_carry(ch, arg, ch)) == NULL)
            return;
        extract_obj(obj);
    }
    else
        for (obj = ch->carrying; obj != NULL; obj = obj_next)
        {
            obj_next = obj->next_content;
            if (arg[3] == '\0' || is_name(&arg[4], obj->name))
            {
                if (obj->wear_loc != WEAR_NONE)
                    unequip_char(ch, obj);
                extract_obj(obj);
            }
        }

    return;

}

/* prints the message to everyone in the room other than the mob and victim */

void do_mpechoaround(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    argument = one_argument(argument, arg);

    if (arg[0] == '\0')
    {
        bug("Mpechoaround - No argument:  vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if (!(victim = get_char_room(ch, NULL, arg)))
    {
        bug("Mpechoaround - victim does not exist: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    act(argument, ch, NULL, victim, TO_NOTVICT);
    return;
}

/* prints the message to only the victim */

void do_mpechoat(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    argument = one_argument(argument, arg);

    if (arg[0] == '\0' || argument[0] == '\0')
    {
        bug("Mpechoat - No argument:  vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if (!(victim = get_char_room(ch, NULL, arg)))
    {
        bug("Mpechoat - victim does not exist: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    act(argument, ch, NULL, victim, TO_VICT);
    return;
}

/* prints the message to the room at large */

void do_mpecho(CHAR_DATA * ch, char *argument)
{
    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    if (argument[0] == '\0')
    {
        bug("Mpecho - called w/o argument: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    act(argument, ch, NULL, NULL, TO_ROOM);
    return;

}

/* lets the mobile load an item or mobile.  All items
 * are loaded into inventory.  you can specify a level with
 * the load object portion as well. */

void do_mpmload(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    MOB_INDEX_DATA *pMobIndex;
    CHAR_DATA *victim;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    one_argument(argument, arg);

    if (arg[0] == '\0' || !is_number(arg))
    {
        bug("Mpmload - Bad vnum as arg: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if ((pMobIndex = get_mob_index(atoi(arg))) == NULL)
    {
        bug("Mpmload - Bad mob vnum: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    victim = create_mobile(pMobIndex);
    char_to_room(victim, ch->in_room);
    return;
}

void do_mpoload(CHAR_DATA * ch, char *argument)
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA *obj;
    int level;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    argument = one_argument(argument, arg1);
    argument = one_argument(argument, arg2);

    if (arg1[0] == '\0' || !is_number(arg1))
    {
        bug("Mpoload - Bad syntax: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if (arg2[0] == '\0')
    {
        level = get_trust(ch);
    }
    else
    {
        /*
         * New feature from Alander.
         */
        if (!is_number(arg2))
        {
            bug("Mpoload - Bad syntax: vnum %d.", ch->pIndexData->vnum);
            return;
        }
        level = atoi(arg2);
        if (level < 0 || level > get_trust(ch))
        {
            bug("Mpoload - Bad level: vnum %d.", ch->pIndexData->vnum);
            return;
        }
    }

    if ((pObjIndex = get_obj_index(atoi(arg1))) == NULL)
    {
        bug("Mpoload - Bad vnum arg: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    obj = create_object(pObjIndex, level);
    if (CAN_WEAR(obj, ITEM_TAKE))
    {
        obj_to_char(obj, ch);
    }
    else
    {
        obj_to_room(obj, ch->in_room);
    }

    return;
}

/* lets the mobile purge all objects and other npcs in the room,
 * or purge a specified object or mob in the room.  It can purge
 * itself, but this had best be the last command in the MOBprogram
 * otherwise ugly stuff will happen */

void do_mppurge(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *obj;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    one_argument(argument, arg);

    if (arg[0] == '\0')
    {
        /* 'purge' */
        CHAR_DATA *vnext;
        OBJ_DATA *obj_next;

        for (victim = ch->in_room->people; victim != NULL; victim = vnext)
        {
            vnext = victim->next_in_room;
            if (IS_NPC(victim) && victim != ch)
                extract_char(victim, TRUE);
        }

        for (obj = ch->in_room->contents; obj != NULL; obj = obj_next)
        {
            obj_next = obj->next_content;
            extract_obj(obj);
        }

        return;
    }

    if (!(victim = get_char_room(ch, NULL, arg)))
    {
        if ((obj = get_obj_here(ch, NULL, arg)))
        {
            extract_obj(obj);
        }
        else
        {
            bug("Mppurge - Bad argument: vnum %d.", ch->pIndexData->vnum);
        }
        return;
    }

    if (!IS_NPC(victim))
    {
        bug("Mppurge - Purging a PC: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    extract_char(victim, TRUE);
    return;
}

/* lets the mobile goto any location it wishes that is not private */

void do_mpgoto(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    ROOM_INDEX_DATA *location;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    one_argument(argument, arg);
    if (arg[0] == '\0')
    {
        bug("Mpgoto - No argument: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if ((location = find_location(ch, arg)) == NULL)
    {
        bug("Mpgoto - No such location: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if (ch->fighting != NULL)
        stop_fighting(ch, TRUE);

    char_from_room(ch);
    char_to_room(ch, location);

    return;
}

/* lets the mobile do a command at another location. Very useful */

void do_mpat(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];
    ROOM_INDEX_DATA *location;
    ROOM_INDEX_DATA *original;
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *wch;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    argument = one_argument(argument, arg);

    if (arg[0] == '\0' || argument[0] == '\0')
    {
        bug("Mpat - Bad argument: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if ((location = find_location(ch, arg)) == NULL)
    {
        sprintf(buf, "Mpat - mob vnum %d - No such location as %s.", 
                     ch->pIndexData->vnum,
                     arg);
        bug(buf, 0);
        wiznet(buf, NULL, NULL, WIZ_MOBS, 0, 0);
        return;
    }

    original = ch->in_room;
    char_from_room(ch);
    char_to_room(ch, location);
    interpret(ch, argument, 0);

    /*
     * See if 'ch' still exists before continuing!
     * Handles 'at XXXX quit' case.
     */
    for (wch = char_list; wch != NULL; wch = wch->next)
    {
        if (wch == ch)
        {
            char_from_room(ch);
            char_to_room(ch, original);
            break;
        }
    }

    return;
}

/* lets the mobile transfer people.  the all argument transfers
 * everyone in the current room to the specified location */

void do_mptransfer(CHAR_DATA * ch, char *argument)
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    ROOM_INDEX_DATA *location;
    CHAR_DATA *victim;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }
    argument = one_argument(argument, arg1);
    argument = one_argument(argument, arg2);

    if (arg1[0] == '\0')
    {
        bug("Mptransfer - Bad syntax: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if (!str_cmp(arg1, "all"))
    {
      for (victim = ch->in_room->people; victim != NULL;)
        {
            if (victim != ch
                && can_see(ch, victim))
            {
                char buf[MAX_STRING_LENGTH];
                sprintf(buf, "%s %s", victim->name, arg2);
		victim = victim->next_in_room;
                do_mptransfer(ch, buf);
		continue;
            }
	    victim = victim->next_in_room;
        }
        return;
    }

    /*
     * Thanks to Grodyn for the optional location parameter.
     */
    if (arg2[0] == '\0')
    {
        location = ch->in_room;
    }
    else
    {
        if ((location = find_location(ch, arg2)) == NULL)
        {
            bug("Mptransfer - No such location: vnum %d.",
                ch->pIndexData->vnum);
            return;
        }

        if (room_is_private(location))
        {
            bug("Mptransfer - Private room: vnum %d.",
                ch->pIndexData->vnum);
            return;
        }
    }

    if ((victim = get_char_world(ch, arg1)) == NULL)
    {
        bug("Mptransfer - No such person: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if (victim->in_room == NULL)
    {
        bug("Mptransfer - Victim in Limbo: vnum %d.",
            ch->pIndexData->vnum);
        return;
    }

    if (victim->fighting != NULL)
        stop_fighting(victim, TRUE);

    char_from_room(victim);
    char_to_room(victim, location);

    return;
}

/*
 * Lets the mobile transfer all chars in same group as the victim.
 *
 * Syntax: mpgtransfer [victim] [location]
 */
void do_mpgtransfer( CHAR_DATA *ch, char *argument )
{
    char             arg1[ MAX_INPUT_LENGTH ];
    char             arg2[ MAX_INPUT_LENGTH ];
    char	     buf[MAX_STRING_LENGTH];
    CHAR_DATA       *who, *victim, *victim_next;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' )
    {
	bug( "Mpgtransfer - Bad syntax from vnum %d.",
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }

    if ( (who = get_char_room( ch, NULL, arg1 )) == NULL )
	return;

    for ( victim = ch->in_room->people; victim; victim = victim_next )
    {
    	victim_next = victim->next_in_room;
    	if( is_same_group( who,victim ) )
    	{
	    sprintf( buf, "%s %s", victim->name, arg2 );
	    do_mptransfer( ch, buf );
    	}
    }
    return;
}

/* lets the mobile force someone to do something.  must be mortal level
 * and the all argument only affects those in the room with the mobile */
void do_mpforce(CHAR_DATA * ch, char *argument)
{
    char arg[MAX_INPUT_LENGTH];

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }

    argument = one_argument(argument, arg);

    if (arg[0] == '\0' || argument[0] == '\0')
    {
        bug("Mpforce - Bad syntax: vnum %d.", ch->pIndexData->vnum);
        return;
    }

    if (!str_cmp(arg, "all"))
    {
        CHAR_DATA *vch;
        CHAR_DATA *vch_next;

        for (vch = char_list; vch != NULL; vch = vch_next)
        {
            vch_next = vch->next;

            if (vch->in_room == ch->in_room
                && get_trust(vch) < get_trust(ch)
                && can_see(ch, vch))
            {
                interpret(vch, argument, 0);
            }
        }
    }
    else
    {
        CHAR_DATA *victim;

        if ((victim = get_char_room(ch, NULL, arg)) == NULL)
        {
            bug("Mpforce - No such victim: vnum %d.",
                ch->pIndexData->vnum);
            return;
        }

        if (victim == ch)
        {
            bug("Mpforce - Forcing oneself: vnum %d.",
                ch->pIndexData->vnum);
            return;
        }

        interpret(victim, argument, 0);
    }

    return;
}

/*
 * Lets the mobile force a group something. Must be mortal level.
 *
 * Syntax: mpgforce [victim] [commands]
 */
void do_mpgforce( CHAR_DATA *ch, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim, *vch, *vch_next;

    argument = one_argument( argument, arg );

    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
	bug( "MpGforce - Bad syntax from vnum %d.",
		IS_NPC(ch) ? ch->pIndexData->vnum : 0 );
	return;
    }

    if ( ( victim = get_char_room( ch, NULL, arg ) ) == NULL )
	return;

    if ( victim == ch )
	return;

    for ( vch = victim->in_room->people; vch != NULL; vch = vch_next )
    {
	vch_next = vch->next_in_room;

	if ( is_same_group(victim,vch) )
        {
	    interpret( vch, argument, 0 );
	}
    }
    return;
}

void do_mpcast(CHAR_DATA * ch, char *argument)
{
    int sn, mana;
    void *vo;
    CHAR_DATA *victim;
    char spell[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    char arg2[MAX_INPUT_LENGTH];

    argument = one_argument(argument, spell);
    argument = one_argument(argument, arg2);
    vo = NULL;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }
    if ((sn = skill_lookup(spell)) < 0)
        return;
    if (skill_table[sn].type != TYPE_SPELL)
    {
        send_to_char("That's not a spell!\n\r", ch);
        sprintf(buf, "Mpcast - mob vnum %d - Casting non spell, sn = %d.",
                     ch->pIndexData->vnum, sn);
        wiznet(buf, NULL, NULL, WIZ_MOBS, 0, 0);
        return;
    }

    /* ok, I put this here to prevent any spell casting, if you only want */
    /* it to work on specific spell types, just put this in the switch    */     
    if (IS_AFFECTED2(ch, AFF2_AMNESIA) )
      {
        send_to_char("You can't remember the spell!.\n\r",ch);
        return;
      }
    if (ch->position < skill_table[sn].minimum_position)
    {
        send_to_char("You can't concentrate enough.\n\r", ch);
        sprintf(buf, "Mpcast - mob vnum %d - Position too low at %d.",
                     ch->pIndexData->vnum, ch->position);
        wiznet(buf, NULL, NULL, WIZ_MOBS, 0, 0);
        return;
    }

    switch (skill_table[sn].target)
    {
        default:
            bug("Do_mpcast: bad target for sn %d.", sn);
            return;

        case TAR_IGNORE:
            break;

        case TAR_CHAR_OFFENSIVE:
            /* Now allowing mpcast to initiate combat.  yikes. 
               -- Lorn, June 2000 */
            if (arg2[0] == '\0')
            {
                if ((victim = ch->fighting) == NULL)
                {
                    send_to_char("Cast the spell on whom?\n\r", ch);
                    return;
                }
            }
            else
            {
                if ((victim = get_char_room(ch, NULL, arg2)) == NULL)
                {
                    send_to_char("They aren't here.\n\r", ch);
                    sprintf(buf, "Mpcast - mob vnum %d - Target not found.",
                                 ch->pIndexData->vnum);
                    wiznet(buf, NULL, NULL, WIZ_MOBS, 0, 0);
                    return;
                }
            }
            /* before June 2000, was only the commented out if below */
            /*
            if ((victim = ch->fighting) == NULL)
            {
                send_to_char("Cast the spell on whom?\n\r", ch);
                return;
            }
            */

            /* Since mpcast can now start combat, have to check is_target_safe.
               --Lorn, June 2000 */
            if (is_target_safe(ch, victim))
                return;

            /* Ivan's blindness modification */
            if (IS_AFFECTED(ch, AFF_BLIND))
            {
                send_to_char("You can't see a thing!!!.\n\r", ch);
                return;
            }

            if (IS_AFFECTED(ch, AFF_CHARM) && ch->master == victim)
            {
                send_to_char("You can't do that on your own follower.\n\r", ch);
                return;
            }

            vo = (void *)victim;
            break;

        case TAR_CHAR_DEFENSIVE:
            victim = ch;
            vo = (void *)victim;
            break;

        case TAR_CHAR_SELF:
            vo = (void *)ch;
            break;

        case TAR_OBJ_INV:
            return;
            break;
    }
    /* do_cast has a large additional section for offensive spells that
       I do not think is needed here and I don't want to go figure out again.
       Mythos and I had enough fun figuring it out the first time.
       --Lorn, June 2000 */

    /* mana and wait state implemented in June 2000 by Lorn */
    mana = CALCULATE_MANA(ch, sn);
    ch->mana -= mana;
    WAIT_STATE(ch, skill_table[sn].beats);

    (*skill_table[sn].fun.spell) (sn, ch->level, ch, vo);
    return;
}

void do_mpmotorball_score(CHAR_DATA * ch, char *argument)
{
    char arg1[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    ROOM_INDEX_DATA* start_room;
    CHAR_DATA *winner;
    OBJ_DATA *obj, *obj2;
    int ball_vnum = 100;
    int circuit = 0;
    int tokens = 0;

    if (ch == NULL) 
        return;
    else if (!IS_NPC(ch))
        {
            send_to_char("Huh?\n\r", ch);
            return;
        }

    argument = one_argument(argument, arg1);
    if ((winner = get_char_room(ch, NULL, arg1)) == NULL)
    {
        sprintf(buf,"MpMotorball - mob %d.  No such person as %s.", ch->pIndexData->vnum, arg1);
        bug(buf,0);
        return;
    }

    switch(ch->in_room->vnum)
    {
        case 8821:  
            ball_vnum = 8803; 
            circuit = 3;  
            start_room = get_room_index(8822);
            break;
        default:
            sprintf(buf, "mpmotorball_score: calling character %s in unexpected room %d.", ch->name, ch->in_room->vnum);
            bug(buf, 0);
            send_to_char(buf,ch);
            return;
    }
    obj = get_obj_carry_by_vnum(winner, ball_vnum);
    if (obj == NULL)
    {
        sprintf(buf,"MpMotorball - mob %d.  Object %d not found on winner %s.", ch->pIndexData->vnum, ball_vnum, winner->name);
        bug(buf,0);
        return;
    }

    obj2 = get_obj_carry_by_vnum(winner, OBJ_VNUM_MOTORBALL_TOKEN);
    if (obj2 != NULL)
    {
        extract_obj(obj2);
        for (obj2 = ch->carrying; obj2 != NULL; obj2 = obj2->next)
        {
            if (obj2->pIndexData->vnum == OBJ_VNUM_MOTORBALL_TOKEN)
              tokens++;
        }
    }
    if (tokens == 1)
      sprintf(buf, "%s has completed a lap on circuit %d!  Now on LAST lap!", winner->name, circuit);
    else if (tokens > 1)
      sprintf(buf, "%s has completed a lap on circuit %d!  %d laps remaining!", winner->name, circuit, tokens);
    else  /* tokens == 0, winner! */
    {
        sprintf(buf, "We have a winner!  The new motorball champion of circuit %d, %s!", circuit, winner->name);
        extract_obj(obj);
        if (!IS_NPC(winner))
            motorball_award_prize(winner, circuit);
        do_mpmotorball_reset(ch, "31");
    }
    if (tokens != 0)  /* start next lap */
    {
        char_from_room(winner);
        char_to_room(winner, start_room);
        if (IS_NPC(winner) || !IS_SET(winner->act, PLR_WIZINVIS) )
            act("$n has arrived.", winner, NULL, NULL, TO_ROOM);
        send_to_char("You move around the track into the next lap.",winner);
        do_look(winner, "auto");
    }

    do_yell(ch, buf);

    return;
}

void do_mpmotorball_reset(CHAR_DATA * ch, char *argument)
{
    char arg1[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    int type = 0;
    int room;
    CHAR_DATA *rch, *rch_next;
    ROOM_INDEX_DATA *room_index, *dressing_room;

    if (ch == NULL) 
        return;
    else if (!IS_NPC(ch))
        {
            send_to_char("Huh?\n\r", ch);
            return;
        }

    argument = one_argument(argument, arg1);

    if ( (arg1[0] == '\0') )
    {
        sprintf(buf, "MpMotorball - Bad syntax: vnum %d.", ch->pIndexData->vnum);
        bug(buf,0);
        return;
    }
    type = atoi(arg1);

    switch (type)
    {
      default: 
        sprintf(buf,"mpmotorball_reset bad syntax from vnum %d, argument %d.", ch->pIndexData->vnum, type);
        bug(buf,0);
        break;
      case 31:   /* set zone 3 inactive */
        /* all referees, finish line and the starter sit down */
        /* actually written below as destroying all npcs on circuit 
           and resetting the entire area  */
        /* removes all player characters from the circuit */
        dressing_room = get_room_index(8819);
        for (room = 8820; room <= 8834; room++)
        {
            room_index = get_room_index(room);
            if (room_index == NULL)
            {
                sprintf(buf,"Mpmotorball_reset: invalid room number %d.", room);
                bug(buf,0);
                return;
            }
            for (rch = room_index->people; rch != NULL; rch = rch_next)
            {
                rch_next = rch->next_in_room;
                if (IS_NPC(rch))
                    extract_char(rch, TRUE);
                else
                {
                    char_from_room(rch);
                    char_to_room(rch, dressing_room);
                    if (IS_NPC(rch) || !IS_SET(rch->act, PLR_WIZINVIS) )
                      act("$n has arrived.", rch, NULL, NULL, TO_ROOM);
                    send_to_char("You have been returned to the dressing room.",rch);
                    do_look(rch, "auto");
                }
            }
        }
        reset_area(room_index->area);

        wiznet("Motorball circuit 3 now inactive.\n\r", NULL, NULL, WIZ_RESETS, 0, 0);
        break;
      case 32:   /* set zone 3 active */
        /* all referees, finish line and the starter stand up */
        /* need to restore all mobs on the circuit to natural state */
        /* setting inactive resets the area, setting active does not need to as well */
        /* so all going active needs to do is set position on starter and finisher */

        room_index = get_room_index(8821);  /* finish line */
        if (room_index == NULL)
        {
            sprintf(buf,"Mpmotorball_reset: invalid room number %d.", room_index->vnum);
            bug(buf,0);
            return;
        }
        for (rch = room_index->people; rch != NULL; rch = rch_next)
        {
            rch_next = rch->next_in_room;
            if ( IS_NPC(rch) && (rch->pIndexData->vnum == 8840) )
              rch->position = POS_STANDING;
        }

        room_index = get_room_index(8819);  /* dressing room */
        if (room_index == NULL)
        {
            sprintf(buf,"Mpmotorball_reset: invalid room number %d.", room_index->vnum);
            bug(buf,0);
            return;
        }
        for (rch = room_index->people; rch != NULL; rch = rch_next)
        {
            rch_next = rch->next_in_room;
            if ( IS_NPC(rch) && (rch->pIndexData->vnum == 8843) )
              rch->position = POS_STANDING;
        }

        wiznet("Motorball circuit 3 now active.\n\r", NULL, NULL, WIZ_RESETS, 0, 0);
        break;
      case 33:   /* announce new player in circuit 3 */
        do_yell(ch, "New player in circuit 3!");
        break;
    }
    return;
}         /* end do_mpmotorball_reset */

void do_mpmotorball_play(CHAR_DATA * ch, char *argument)
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *winner, *victim;

    if (!IS_NPC(ch))
    {
        send_to_char("Huh?\n\r", ch);
        return;
    }
    argument = one_argument(argument, arg1);
    argument = one_argument(argument, arg2);

    if ( (arg1[0] == '\0') || (arg2[0] == '\0') )
    {
        sprintf(buf, "MpMotorball - Bad syntax: vnum %d.", ch->pIndexData->vnum);
        bug(buf,0);
        return;
    }

    if ((winner = get_char_room(ch, NULL, arg1)) == NULL)
    {
        sprintf(buf,"MpMotorball - mob %d.  No such person as %s.", ch->pIndexData->vnum, arg1);
        bug(buf,0);
        return;
    }

    if ((victim = get_char_room(ch, NULL, arg2)) == NULL)
    {
        sprintf(buf,"MpMotorball - mob %d.  No such person as %s.", ch->pIndexData->vnum, arg2);
        bug(buf,0);
        return;
    }

    motorball_move_ball(winner, victim);

    return;
}
