/**************************************************************************
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

/**************************************************************************
*	ROM 2.4 is copyright 1993-1995 Russ Taylor			                   *
*	ROM has been brought to you by the ROM consortium		               *
*	    Russ Taylor (rtaylor@pacinfo.com)				                   *
*	    Gabrielle Taylor (gtaylor@pacinfo.com)			                   *
*	    Brian Moore (rom@rom.efn.org)				                       *
*	By using this code, you have agreed to follow the terms of the	       *
*	ROM license, in the file Rom24/doc/rom.license			               *
***************************************************************************/

/**************************************************************************
*                                                                         *
*  Based on MERC 2.2 MOBprograms by N'Atas-ha.                            *
*  Written and adapted to ROM 2.4 by                                      *
*          Markku Nylander (markku.nylander@uta.fi)                       *
*                                                                         *
***************************************************************************/

/**************************************************************************
*                                                                         *
*  Ported for Aesir by Coyotilo 12/02                                     *
*                                                                         *
***************************************************************************/

/*
 * $Log: obj_room_cmds.c,v $
 * Revision 1.3  2002/12/19 16:46:16  coyotilo
 * Coy: More obj and room prog stuff.
 *
 * Revision 1.1  2002/12/18 16:01:27  coyotilo
 * Coy: Added object and room progs.
 *
 */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merc.h"
#include "obj_room_cmds.h"

DECLARE_DO_FUN( do_look 	);
extern ROOM_INDEX_DATA *find_location( CHAR_DATA *, char * );

/*
 * MOBcommand table.
 */
const	struct	mob_cmd_type	mob_cmd_table	[] =
{
    {	"asound", 	do_mpasound	},
    {	"gecho",	do_mpgecho	},
    {	"zecho",	do_mpzecho	},
    {	"kill",		do_mpkill	},
    {	"assist",	do_mpassist	},
    {	"junk",		do_mpjunk	},
    {	"echo",		do_mpecho	},
    {	"echoaround",	do_mpechoaround	},
    {	"echoat",	do_mpechoat	},
    {	"mload",	do_mpmload	},
    {	"oload",	do_mpoload	},
    {	"purge",	do_mppurge	},
    {	"goto",		do_mpgoto	},
    {	"at",		do_mpat		},
    {	"transfer",	do_mptransfer	},
    {	"gtransfer",	do_mpgtransfer	},
    {	"otransfer",	do_mpotransfer	},
    {	"force",	do_mpforce	},
    {	"gforce",	do_mpgforce	},
    {	"vforce",	do_mpvforce	},
    {	"cast",		do_mpcast	},
    {	"damage",	do_mpdamage	},
    {	"remember",	do_mpremember	},
    {	"forget",	do_mpforget	},
    {	"delay",	do_mpdelay	},
    {	"cancel",	do_mpcancel	},
    {	"call",		do_mpcall	},
    {	"flee",		do_mpflee	},
    {	"remove",	do_mpremove	},
	    {"mpmotorballplay", do_mpmotorball_play},
    {"mpmotorballscore", do_mpmotorball_score},
    {"mpmotorballreset", do_mpmotorball_reset},
    {	"",		0		}
};


/*
* OBJcommand table.
*/
const	struct	obj_cmd_type	obj_cmd_table	[] =
{
    {	"gecho",       	do_opgecho	},
    {	"zecho",	do_opzecho	},
    {	"echo",		do_opecho	},
    {	"echoaround",	do_opechoaround	},
    {	"echoat",	do_opechoat	},
    {	"mload",	do_opmload	},
    {	"oload",	do_opoload	},
    {	"purge",	do_oppurge	},
    {	"goto",		do_opgoto	},
    {	"transfer",	do_optransfer	},
    {	"gtransfer",	do_opgtransfer	},
    {	"otransfer",	do_opotransfer	},
    {	"force",	do_opforce	},
    {	"gforce",	do_opgforce	},
    {	"vforce",	do_opvforce	},
    {	"damage",	do_opdamage	},
    {	"remember",	do_opremember	},
    {	"forget",	do_opforget	},
    {	"delay",	do_opdelay	},
    {	"cancel",	do_opcancel	},
    {	"call",		do_opcall	},
    {	"remove",	do_opremove	},
    {	"",		0		}
};

/*
* ROOMcommand table.
*/
const	struct  room_cmd_type	room_cmd_table	[] =
{
    {	"asound",	do_rpasound	},
    {	"gecho",	do_rpgecho	},
    {	"zecho",	do_rpzecho	},
    {	"echo",		do_rpecho 	},
    {	"echoaround",	do_rpechoaround },
    {	"echoat",	do_rpechoat 	},
    {	"mload",	do_rpmload 	},
    {	"oload",	do_rpoload 	},
    {	"purge",	do_rppurge 	},
    {	"transfer",	do_rptransfer 	},
    {	"gtransfer",	do_rpgtransfer 	},
    {	"otransfer",	do_rpotransfer 	},
    {	"force",	do_rpforce 	},
    {	"gforce",	do_rpgforce 	},
    {	"vforce",	do_rpvforce 	},
    {	"damage",       do_rpdamage 	},
    {	"remember",	do_rpremember 	},
    {	"forget",	do_rpforget 	},
    {	"delay",	do_rpdelay 	},
    {	"cancel",	do_rpcancel 	},
    {	"call",		do_rpcall 	},
    {	"remove",	do_rpremove 	},
    {	"",		0 		},
};

char *prog_type_to_name( int type )
{
    switch ( type )
    {
    case TRIG_ACT:             	return "ACT";
    case TRIG_SPEECH:          	return "SPEECH";
    case TRIG_RANDOM:          	return "RANDOM";
    case TRIG_FIGHT:           	return "FIGHT";
    case TRIG_HPCNT:           	return "HPCNT";
    case TRIG_DEATH:           	return "DEATH";
    case TRIG_ENTRY:           	return "ENTRY";
    case TRIG_GREET:           	return "GREET";
    case TRIG_GRALL:        	return "GRALL";
    case TRIG_GIVE:            	return "GIVE";
    case TRIG_BRIBE:           	return "BRIBE";
    case TRIG_KILL:	      	return "KILL";
    case TRIG_DELAY:           	return "DELAY";
    case TRIG_SURR:	      	return "SURRENDER";
    case TRIG_EXIT:	      	return "EXIT";
    case TRIG_EXALL:	      	return "EXALL";
    case TRIG_GET:		return "GET";
    case TRIG_DROP:		return "DROP";
    case TRIG_SIT:		return "SIT";
    case TRIG_ALIAS:		return "ALIAS";
    default:                  	return "ERROR";
    }
}

/*
 * MOBprog section
 */

void do_mob( CHAR_DATA *ch, char *argument )
{
    /*
     * Security check!
     */
    if ( ch->desc != NULL && get_trust(ch) < MAX_LEVEL )
	return;
    mob_interpret( ch, argument );
}
/*
 * Mob command interpreter. Implemented separately for security and speed
 * reasons. A trivial hack of interpret()
 */
void mob_interpret( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH], command[MAX_INPUT_LENGTH];
    int cmd;

    argument = one_argument( argument, command );

    /*
     * Look for command in command table.
     */
    for ( cmd = 0; mob_cmd_table[cmd].name[0] != '\0'; cmd++ )
    {
	if ( command[0] == mob_cmd_table[cmd].name[0]
	&&   !str_prefix( command, mob_cmd_table[cmd].name ) )
	{
	    (*mob_cmd_table[cmd].do_fun) ( ch, argument );
	    tail_chain( );
	    return;
	}
    }
    sprintf( buf, "Mob_interpret: invalid cmd from mob %d: '%s'",
	IS_NPC(ch) ? ch->pIndexData->vnum : 0, command );
    bug( buf, 0 );
}

/* 
 * Displays MOBprogram triggers of a mobile
 *
 * Syntax: mpstat [name]
 */
void do_mpstat(CHAR_DATA * ch, char *argument)
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    MPROG_DATA *mprg;
    CHAR_DATA *victim;

    one_argument(argument, arg);

    if (arg[0] == '\0')
    {
        send_to_char("MobProg stat whom?\n\r", ch);
        return;
    }

    if ((victim = get_char_world(ch, arg)) == NULL)
    {
        send_to_char("They aren't here.\n\r", ch);
        return;
    }

    if (!IS_NPC(victim))
    {
        send_to_char("Only Mobiles can have Programs!\n\r", ch);
        return;
    }

    if (!(victim->pIndexData->progtypes))
    {
        send_to_char("That Mobile has no Programs set.\n\r", ch);
        return;
    }

	/* Way to hide mobprogs, ONLY USE WITH PERMISION (and not to be
	 * general knowledge - Coyotilo 7/01
     * Deity and above can see cloaked pros - Coy 7/03 */
    if( IS_NPC(victim) && is_exact_name("xndr",victim->name)  &&
        ch->level > IMPLEMENTOR)
    {
	send_to_char("This mob's Programs have been cloaked.\n\r",ch);
	return;
    }

    sprintf(buf, "Name: %s.  Vnum: %d.\n\r",
            victim->name, victim->pIndexData->vnum);
    send_to_char(buf, ch);

    sprintf(buf, "Short description: %s.\n\rLong  description: %s",
            victim->short_descr,
            victim->long_descr[0] != '\0' ?
            victim->long_descr : "(none).\n\r");
    send_to_char(buf, ch);

    sprintf(buf, "Hp: %d/%d.  Mana: %d/%d.  Move: %d/%d. \n\r",
            victim->hit, victim->max_hit,
            victim->mana, victim->max_mana,
            victim->move, victim->max_move);
    send_to_char(buf, ch);

    for (mprg = victim->pIndexData->mobprogs; mprg != NULL;
         mprg = mprg->next)
    {
        sprintf(buf, ">%s %s\n\r%s\n\r",
                mprog_type_to_name(mprg->type),
                mprg->arglist,
                mprg->comlist);
        send_to_char(buf, ch);
    }

    return;

}

/*
 * Displays the source code of a given MOBprogram
 *
 * Syntax: mpdump [vnum]
 */
void do_mpdump( CHAR_DATA *ch, char *argument )
{
   char buf[ MAX_INPUT_LENGTH ];
   PROG_CODE *mprg;

   one_argument( argument, buf );
   if ( ( mprg = get_prog_index( atoi(buf), PRG_MPROG ) ) == NULL )
   {
	send_to_char( "No such MOBprogram.\n\r", ch );
	return;
   }
   page_to_char( mprg->code, ch );
}

/*
* OBJprog section
*/
void do_obj( OBJ_DATA *obj, char *argument )
{
/*
* Security check!
    */
    if ( obj->level < MAX_LEVEL )
        return;
    obj_interpret( obj, argument );
}
/*
* Obj command interpreter. Implemented separately for security and speed
* reasons. A trivial hack of interpret()
*/
void obj_interpret( OBJ_DATA *obj, char *argument )
{
    char buf[MAX_STRING_LENGTH], command[MAX_INPUT_LENGTH];
    int cmd;
    
    argument = one_argument( argument, command );
    
    /*
    * Look for command in command table.
    */
    for ( cmd = 0; obj_cmd_table[cmd].name[0] != '\0'; cmd++ )
    {
        if ( command[0] == obj_cmd_table[cmd].name[0]
            &&   !str_prefix( command, obj_cmd_table[cmd].name ) )
        {
            (*obj_cmd_table[cmd].obj_fun) ( obj, argument );
            tail_chain( );
            return;
        }
    }
    sprintf( buf, "Obj_interpret: invalid cmd from obj %d: '%s'",
        obj->pIndexData->vnum, command );
    bug( buf, 0 );
}

/* 
* Displays OBJprogram triggers of an object
*
* Syntax: opstat [name]
*/
void do_opstat( CHAR_DATA *ch, char *argument )
{
    char        arg[ MAX_STRING_LENGTH  ];
    PROG_LIST  *oprg;
    OBJ_DATA   *obj;
    int i;
    
    one_argument( argument, arg );
    
    if ( arg[0] == '\0' )
    {
        send_to_char( "Opstat what?\n\r", ch );
        return;
    }
    
    if ( ( obj = get_obj_world( ch, arg ) ) == NULL )
    {
        send_to_char( "No such object.\n\r", ch );
        return;
    }
    
    sprintf( arg, "Object #%-6d [%s]\n\r",
        obj->pIndexData->vnum, obj->short_descr );
    send_to_char( arg, ch );
    
    sprintf( arg, "Delay   %-6d [%s]\n\r",
        obj->oprog_delay,
        obj->oprog_target == NULL 
        ? "No target" : obj->oprog_target->name );
    send_to_char( arg, ch );
    
    if ( !obj->pIndexData->oprog_flags )
    {
        send_to_char( "[No programs set]\n\r", ch);
        return;
    }
    
    for ( i = 0, oprg = obj->pIndexData->oprogs; oprg != NULL;
    oprg = oprg->next )
        
    {
        sprintf( arg, "[%2d] Trigger [%-8s] Program [%4d] Phrase [%s]\n\r",
            ++i,
            prog_type_to_name( oprg->trig_type ),
            oprg->vnum,
            oprg->trig_phrase );
        send_to_char( arg, ch );
    }
    
    return;
    
}

/*
* Displays the source code of a given OBJprogram
*
* Syntax: opdump [vnum]
*/
void do_opdump( CHAR_DATA *ch, char *argument )
{
    char buf[ MAX_INPUT_LENGTH ];
    PROG_CODE *oprg;
    
    one_argument( argument, buf );
    if ( ( oprg = get_prog_index( atoi(buf), PRG_OPROG ) ) == NULL )
    {
        send_to_char( "No such OBJprogram.\n\r", ch );
        return;
    }
    page_to_char( oprg->code, ch );
}

/*
* Prints the argument to all active players in the game
*
* Syntax: obj gecho [string]
*/
void do_opgecho( OBJ_DATA *obj, char *argument )
{
    DESCRIPTOR_DATA *d;
    
    if ( argument[0] == '\0' )
    {
        bug( "OpGEcho: missing argument from vnum %d",
            obj->pIndexData->vnum );
        return;
    }
    
    for ( d = descriptor_list; d; d = d->next )
    {
        if ( d->connected == CON_PLAYING )
        {
            if ( IS_IMMORTAL(d->character) )
                send_to_char( "Obj echo> ", d->character );
            send_to_char( argument, d->character );
            send_to_char( "\n\r", d->character );
        }
    }
}

/*
* Prints the argument to all players in the same area as the mob
*
* Syntax: obj zecho [string]
*/
void do_opzecho( OBJ_DATA *obj, char *argument )
{
    DESCRIPTOR_DATA *d;
    
    if ( argument[0] == '\0' )
    {
        bug( "OpZEcho: missing argument from vnum %d",
            obj->pIndexData->vnum );
        return;
    }
    
    if ( obj->in_room == NULL && (obj->carried_by == NULL || obj->carried_by->in_room == NULL) )
        return;
    
    for ( d = descriptor_list; d; d = d->next )
    {
        if ( d->connected == CON_PLAYING 
            &&   d->character->in_room != NULL 
            &&   ( (obj->in_room && d->character->in_room->area == obj->in_room->area)
            || (obj->carried_by && d->character->in_room->area == obj->carried_by->in_room->area) ) )
        {
            if ( IS_IMMORTAL(d->character) )
                send_to_char( "Obj echo> ", d->character );
            send_to_char( argument, d->character );
            send_to_char( "\n\r", d->character );
        }
    }
}

/*
* Prints the message to everyone in the room other than the mob and victim
*
* Syntax: obj echoaround [victim] [string]
*/

void do_opechoaround( OBJ_DATA *obj, char *argument )
{
    char       arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim, *vch;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' )
        return;
    
    if ( ( victim=get_char_room( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg ) ) == NULL )
        return;
    
    if ( obj->in_room && obj->in_room->people )
        vch = obj->in_room->people;
    else if ( obj->carried_by && obj->carried_by->in_room )
        vch = obj->carried_by->in_room->people;
    else
        vch = NULL;
    
    for ( ; vch; vch = vch->next_in_room )
    {
        if ( vch == victim )
            continue;
        send_to_char( argument, vch );
    }
}

/*
* Prints the message to only the victim
*
* Syntax: obj echoat [victim] [string]
*/
void do_opechoat( OBJ_DATA *obj, char *argument )
{
    char       arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
        return;
    
    if ( ( victim = get_char_room( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg ) ) == NULL )
        return;
    
    act( argument, obj->carried_by?obj->carried_by:obj->in_room->people, obj, victim, TO_VICT );
}

/*
* Prints the message to the room at large
*
* Syntax: obj echo [string]
*/
void do_opecho( OBJ_DATA *obj, char *argument )
{
    if ( argument[0] == '\0' )
        return;
    
    if ( !obj->carried_by && !obj->in_room->people )
        return;
    
    act( argument, obj->carried_by?obj->carried_by:obj->in_room->people, NULL, NULL, TO_ROOM );
    act( argument, obj->carried_by?obj->carried_by:obj->in_room->people, NULL, NULL, TO_CHAR );
}

/*
* Lets the object load a mobile.
*
* Syntax: obj mload [vnum]
*/
void do_opmload( OBJ_DATA *obj, char *argument )
{
    char            arg[ MAX_INPUT_LENGTH ];
    MOB_INDEX_DATA *pMobIndex;
    CHAR_DATA      *victim;
    int vnum;
    
    one_argument( argument, arg );
    
    if ( (obj->in_room == NULL
        && (obj->carried_by == NULL || obj->carried_by->in_room == NULL))
        || arg[0] == '\0' || !is_number(arg) )
        return;
    
    vnum = atoi(arg);
    if ( ( pMobIndex = get_mob_index( vnum ) ) == NULL )
    {
        sprintf( arg, "Opmload: bad mob index (%d) from obj %d",
            vnum, obj->pIndexData->vnum );
        bug( arg, 0 );
        return;
    }
    victim = create_mobile( pMobIndex );
    char_to_room( victim, obj->in_room?obj->in_room:obj->carried_by->in_room );
    return;
}

/*
* Lets the object load another object
*
* Syntax: obj oload [vnum] [level]
*/
void do_opoload( OBJ_DATA *obj, char *argument )
{
    char arg1[ MAX_INPUT_LENGTH ];
    char arg2[ MAX_INPUT_LENGTH ];
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA       *nobj;
    int             level;
    
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    
    if ( arg1[0] == '\0' || !is_number( arg1 ) )
    {
        bug( "Opoload - Bad syntax from vnum %d.",
            obj->pIndexData->vnum );
        return;
    }
    
    if ( arg2[0] == '\0' )
    {
        level = obj->level;
    }
    else
    {
    /*
    * New feature from Alander.
        */
        if ( !is_number( arg2 ) )
        {
            bug( "Opoload - Bad syntax from vnum %d.", 
                obj->pIndexData->vnum );
            return;
        }
        level = atoi( arg2 );
        /*if ( level < 0 || level > obj->level )
        {
            bug( "Opoload - Bad level from vnum %d.", 
                obj->pIndexData->vnum );
            return;
        }*/
    }
    
    if ( ( pObjIndex = get_obj_index( atoi( arg1 ) ) ) == NULL )
    {
        bug( "Opoload - Bad vnum arg from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    nobj = create_object( pObjIndex, level );
    obj_to_room( nobj, obj->in_room?obj->in_room:obj->carried_by->in_room );
    
    return;
}

/*
* Lets the object purge all other objects and npcs in the room,
* or purge a specified object or mob in the room. The object cannot
* purge itself for safety reasons.
*
* syntax obj purge {target}
*/
void do_oppurge( OBJ_DATA *obj, char *argument )
{
    char       arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;
    OBJ_DATA  *vobj;
    
    one_argument( argument, arg );
    
    if ( arg[0] == '\0' )
    {
        /* 'purge' */
        CHAR_DATA *vnext;
        OBJ_DATA  *obj_next;
        
        if ( obj->in_room && obj->in_room->people )
            victim = obj->in_room->people;
        else if ( obj->carried_by && obj->carried_by->in_room )
            victim = obj->carried_by->in_room->people;
        else
            victim = NULL;
        
        for ( ; victim != NULL; victim = vnext )
        {
            vnext = victim->next_in_room;
            if ( IS_NPC( victim )
                &&   !IS_SET(victim->act, ACT_NOPURGE) )
                extract_char( victim, TRUE );
        }
        
        if ( obj->in_room )
            vobj = obj->in_room->contents;
        else
            vobj = obj->carried_by->in_room->contents;
        
        for ( ; vobj != NULL; vobj = obj_next )
        {
            obj_next = vobj->next_content;
            if ( !IS_SET(vobj->extra_flags, ITEM_NOPURGE) && vobj != obj )
                extract_obj( vobj );
        }
        
        return;
    }
    
    if ( ( victim = get_char_room( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg ) ) == NULL )
    {
        if ( ( vobj = get_obj_here( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg ) ) )
        {
            extract_obj( vobj );
        }
        else if ( obj->carried_by && (vobj = get_obj_carry( obj->carried_by, arg, NULL )) != NULL)
        {
            extract_obj( vobj );
        }
        else if ( obj->carried_by && (vobj = get_obj_wear( obj->carried_by, arg, FALSE )) != NULL )
        {
            unequip_char( vobj->carried_by, vobj );
            extract_obj( vobj );
        } /*
        else
        {
            bug( "Oppurge - Bad argument from vnum %d.",
                obj->pIndexData->vnum );
        }*/
        return;
    }
    
    if ( !IS_NPC( victim ) )
    {
        bug( "Oppurge - Purging a PC from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    extract_char( victim, TRUE );
    return;
}


/*
* Lets the object goto any location it wishes that is not private.
*
* Syntax: obj goto [location]
*/
void do_opgoto( OBJ_DATA *obj, char *argument )
{
    char             arg[ MAX_INPUT_LENGTH ];
    ROOM_INDEX_DATA *location;
    CHAR_DATA *victim;
    OBJ_DATA *dobj;
    
    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
        bug( "Opgoto - No argument from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( is_number(arg) )
        location = get_room_index( atoi( arg ) );
    else if ( (victim = get_char_world( NULL, arg )) != NULL )
        location = victim->in_room;
    else if ( ( dobj = get_obj_world( NULL, arg )) != NULL )
        location = dobj->in_room;
    else
    {
        bug( "Opgoto - No such location from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( obj->in_room != NULL )
        obj_from_room( obj );
    else if ( obj->carried_by != NULL )
        obj_from_char( obj );
    obj_to_room( obj, location );
    
    return;
}

/*
* Lets the object transfer people.  The 'all' argument transfers
*  everyone in the current room to the specified location
*
* Syntax: obj transfer [target|'all'] [location]
*/
void do_optransfer( OBJ_DATA *obj, char *argument )
{
    char             arg1[ MAX_INPUT_LENGTH ];
    char             arg2[ MAX_INPUT_LENGTH ];
    char	     buf[MAX_STRING_LENGTH];
    ROOM_INDEX_DATA *location;
    CHAR_DATA       *victim;
    OBJ_DATA	    *dobj;
    
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    
    if ( arg1[0] == '\0' )
    {
        bug( "Optransfer - Bad syntax from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( !str_cmp( arg1, "all" ) )
    {
        CHAR_DATA *victim_next;
        
        if ( obj->in_room && obj->in_room->people )
            victim = obj->in_room->people;
        else if ( obj->carried_by )
            victim = obj->carried_by->in_room->people;
        else
            victim = NULL;
        for ( ; victim != NULL; victim = victim_next )
        {
            victim_next = victim->next_in_room;
            if ( !IS_NPC(victim) )
            {
                sprintf( buf, "%s %s", victim->name, arg2 );
                do_optransfer( obj, buf );
            }
        }
        return;
    }
    
    /*
    * Thanks to Grodyn for the optional location parameter.
    */
    if ( arg2[0] == '\0' )
    {
        location = obj->in_room?obj->in_room:obj->carried_by->in_room;
    }
    else
    {
        if ( is_number(arg2))
            location = get_room_index( atoi(arg2) );
        else if ( (victim = get_char_world( NULL, arg2 )) != NULL )
            location = victim->in_room;
        else if ( ( dobj = get_obj_world( NULL, arg2 )) != NULL )
            location = dobj->in_room;
        else
        {
            bug( "Optransfer - No such location from vnum %d.",
                obj->pIndexData->vnum );
            return;
        }
        
        if ( room_is_private( location ) )
            return;
    }
    
    if ( ( victim = get_char_world( NULL, arg1 ) ) == NULL )
        return;
    
    if ( victim->in_room == NULL )
        return;
    
    if ( victim->fighting != NULL )
        stop_fighting( victim, TRUE );
    char_from_room( victim );
    char_to_room( victim, location );
    do_look( victim, "auto" );
    
    return;
}

/*
* Lets the object transfer all chars in same group as the victim.
*
* Syntax: obj gtransfer [victim] [location]
*/
void do_opgtransfer( OBJ_DATA *obj, char *argument )
{
    char             arg1[ MAX_INPUT_LENGTH ];
    char             arg2[ MAX_INPUT_LENGTH ];
    char	     buf[MAX_STRING_LENGTH];
    CHAR_DATA       *who, *victim, *victim_next;
    
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    
    if ( arg1[0] == '\0' )
    {
        bug( "Opgtransfer - Bad syntax from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( (who = get_char_room( NULL, (obj->in_room)?obj->in_room:obj->carried_by->in_room, arg1 )) == NULL )
        return;
    
    if ( obj->in_room && obj->in_room->people )
        victim = obj->in_room->people;
    else if ( obj->carried_by && obj->carried_by->in_room)
        victim = obj->carried_by->in_room->people;
    else
        victim = NULL;
    
    for ( ; victim; victim = victim_next )
    {
        victim_next = victim->next_in_room;
        if( is_same_group( who,victim ) )
        {
            sprintf( buf, "%s %s", victim->name, arg2 );
            do_optransfer( obj, buf );
        }
    }
    return;
}

/*
* Lets the object force someone to do something. Must be mortal level
* and the all argument only affects those in the room with the object.
*
* Syntax: obj force [victim] [commands]
*/
void do_opforce( OBJ_DATA *obj, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
        bug( "Opforce - Bad syntax from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( !obj->in_room && !obj->carried_by )
        return;
    if ( obj->in_room && !obj->in_room->people )
        return;
    if ( obj->carried_by && !obj->carried_by->in_room )
        return;
    
    if ( !str_cmp( arg, "all" ) )
    {
        CHAR_DATA *vch;
        CHAR_DATA *vch_next;
        
        for ( vch = char_list; vch != NULL; vch = vch_next )
        {
            vch_next = vch->next;
            
            if ( ((obj->in_room && vch->in_room == obj->in_room)
                || (obj->carried_by && vch->in_room == obj->carried_by->in_room))
                && get_trust( vch ) < obj->level )
            {
                interpret( vch, argument, 0 );
            }
        }
    }
    else
    {
        CHAR_DATA *victim;
        
        if ( ( victim = get_char_room( NULL, (obj->in_room)?obj->in_room:obj->carried_by->in_room, arg ) ) == NULL )
            return;
        
        interpret( victim, argument, 0 );
    }
    
    return;
}

/*
* Lets the object force a group something. Must be mortal level.
*
* Syntax: obj gforce [victim] [commands]
*/
void do_opgforce( OBJ_DATA *obj, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim, *vch, *vch_next;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
        bug( "OpGforce - Bad syntax from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( ( victim = get_char_room( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg ) ) == NULL )
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

/*
* Forces all mobiles of certain vnum to do something
*
* Syntax: obj vforce [vnum] [commands]
*/
void do_opvforce( OBJ_DATA *obj, char *argument )
{
    CHAR_DATA *victim, *victim_next;
    char arg[ MAX_INPUT_LENGTH ];
    int vnum;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
        bug( "OpVforce - Bad syntax from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( !is_number( arg ) )
    {
        bug( "OpVforce - Non-number argument vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    vnum = atoi( arg );
    
    for ( victim = char_list; victim; victim = victim_next )
    {
        victim_next = victim->next;
        if ( IS_NPC(victim) && victim->pIndexData->vnum == vnum
            && victim->fighting == NULL )
            interpret( victim, argument, 0 );
    }
    return;
}

/*
* Lets obj cause unconditional damage to someone. Nasty, use with caution.
* Also, this is silent, you must show your own damage message...
*
* Syntax: obj damage [victim] [min] [max] {kill}
*/
void do_opdamage( OBJ_DATA *obj, char *argument )
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
        bug( "OpDamage - Bad syntax from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    if( !str_cmp( target, "all" ) )
        fAll = TRUE;
    else if( ( victim = get_char_room( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, target ) ) == NULL )
        return;
    
    if ( is_number( min ) )
        low = atoi( min );
    else
    {
        bug( "OpDamage - Bad damage min vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    if ( is_number( max ) )
        high = atoi( max );
    else
    {
        bug( "OpDamage - Bad damage max vnum %d.", 
            obj->pIndexData->vnum );
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
        if ( obj->in_room && obj->in_room->people )
            victim = obj->in_room->people;
        else if ( obj->carried_by )
            victim = obj->carried_by->in_room->people;
        else
            victim = NULL;
        
        for( ; victim; victim = victim_next )
        {
            victim_next = victim->next_in_room;
            if ( obj->carried_by && victim != obj->carried_by )
                damage( victim, victim, 
                fKill ? 
                number_range(low,high) : UMIN(victim->hit,number_range(low,high)),
                TYPE_UNDEFINED, DAM_NONE, FALSE);
        }
    }
    else
        damage( victim, victim, 
        fKill ? 
        number_range(low,high) : UMIN(victim->hit,number_range(low,high)),
        TYPE_UNDEFINED, DAM_NONE, FALSE);
    return;
}

/*
* Lets the object to remember a target. The target can be referred to
* with $q and $Q codes in OBJprograms. See also "obj forget".
*
* Syntax: obj remember [victim]
*/
void do_opremember( OBJ_DATA *obj, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    one_argument( argument, arg );
    if ( arg[0] != '\0' )
        obj->oprog_target = get_char_world( NULL, arg );
    else
        bug( "OpRemember: missing argument from vnum %d.", 
        obj->pIndexData->vnum );
}

/*
* Reverse of "obj remember".
*
* Syntax: obj forget
*/
void do_opforget( OBJ_DATA *obj, char *argument )
{
    obj->oprog_target = NULL;
}

/*
* Sets a delay for OBJprogram execution. When the delay time expires,
* the object is checked for a OBJprogram with DELAY trigger, and if
* one is found, it is executed. Delay is counted in PULSE_TICK
*
* Syntax: obj delay [pulses]
*/
void do_opdelay( OBJ_DATA *obj, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    
    one_argument( argument, arg );
    if ( !is_number( arg ) )
    {
        bug( "OpDelay: invalid arg from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    obj->oprog_delay = atoi( arg );
}

/*
* Reverse of "obj delay", deactivates the timer.
*
* Syntax: obj cancel
*/
void do_opcancel( OBJ_DATA *obj, char *argument )
{
    obj->oprog_delay = -1;
}
/*
* Lets the object to call another OBJprogram withing a OBJprogram.
* This is a crude way to implement subroutines/functions. Beware of
* nested loops and unwanted triggerings... Stack usage might be a problem.
* Characters and objects referred to must be in the same room with the
* mobile.
*
* Syntax: obj call [vnum] [victim|'null'] [object1|'null'] [object2|'null']
*
*/
void do_opcall( OBJ_DATA *obj, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *vch;
    OBJ_DATA *obj1, *obj2;
    PROG_CODE *prg;
    extern void program_flow( sh_int, char *, CHAR_DATA *, OBJ_DATA *, ROOM_INDEX_DATA *, CHAR_DATA *, const void *, const void * );
    
    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
        bug( "OpCall: missing arguments from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    if ( ( prg = get_prog_index( atoi(arg), PRG_OPROG ) ) == NULL )
    {
        bug( "OpCall: invalid prog from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    vch = NULL;
    obj1 = obj2 = NULL;
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
        vch = get_char_room( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg );
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
        obj1 = get_obj_here( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg );
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
        obj2 = get_obj_here( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg );
    program_flow( prg->vnum, prg->code, NULL, obj, NULL, vch, (void *)obj1, (void *)obj2 );
}

/*
* Lets the object to transfer an object. The object must be in the same
* room with the object.
*
* Syntax: obj otransfer [item name] [location]
*/
void do_opotransfer( OBJ_DATA *obj, char *argument )
{
    OBJ_DATA *obj1, *dobj;
    ROOM_INDEX_DATA *location;
    char arg[ MAX_INPUT_LENGTH ];
    char buf[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;
    
    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
        bug( "OpOTransfer - Missing argument from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    one_argument( argument, buf );
    if ( is_number( buf ) )
        location = get_room_index( atoi(buf) );
    else if ( (victim = get_char_world( NULL, buf )) != NULL )
        location = victim->in_room;
    else if ( ( dobj = get_obj_world( NULL, arg )) != NULL )
        location = dobj->in_room;
    else
    {
        bug( "OpOTransfer - No such location from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    
    if ( (obj1 = get_obj_here( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg )) == NULL )
        return;
    if ( obj1->carried_by == NULL )
        obj_from_room( obj1 );
    else
    {
        if ( obj1->wear_loc != WEAR_NONE )
            unequip_char( obj1->carried_by, obj1 );
        obj_from_char( obj1 );
    }
    obj_to_room( obj1, location );
}

/*
* Lets the object to strip an object or all objects from the victim.
* Useful for removing e.g. quest objects from a character.
*
* Syntax: obj remove [victim] [object vnum|'all']
*/
void do_opremove( OBJ_DATA *obj, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA *obj1, *obj_next;
    sh_int vnum = 0;
    bool fAll = FALSE;
    char arg[ MAX_INPUT_LENGTH ];
    
    argument = one_argument( argument, arg );
    if ( ( victim = get_char_room( NULL, obj->in_room?obj->in_room:obj->carried_by->in_room, arg ) ) == NULL )
        return;
    
    one_argument( argument, arg );
    if ( !str_cmp( arg, "all" ) )
        fAll = TRUE;
    else if ( !is_number( arg ) )
    {
        bug ( "OpRemove: Invalid object from vnum %d.", 
            obj->pIndexData->vnum );
        return;
    }
    else
        vnum = atoi( arg );
    
    for ( obj1 = victim->carrying; obj1; obj1 = obj_next )
    {
        obj_next = obj->next_content;
        if ( fAll || obj1->pIndexData->vnum == vnum )
        {
            if ( obj1->wear_loc != WEAR_NONE )
                unequip_char( victim, obj1 );
            obj_from_char( obj1 );
            extract_obj( obj1 );
        }
    }
}

/*
* ROOMprog section
*/

void do_room( ROOM_INDEX_DATA *room, char *argument )
{
    room_interpret( room, argument );
}

/*
* Room command interpreter. Implemented separately for security and speed
* reasons. A trivial hack of interpret()
*/
void room_interpret( ROOM_INDEX_DATA *room, char *argument )
{
    char buf[MAX_STRING_LENGTH], command[MAX_INPUT_LENGTH];
    int cmd;
    
    argument = one_argument( argument, command );
    
    /*
    * Look for command in command table.
    */
    for ( cmd = 0; room_cmd_table[cmd].name[0] != '\0'; cmd++ )
    {
        if ( command[0] == room_cmd_table[cmd].name[0]
            &&   !str_prefix( command, room_cmd_table[cmd].name ) )
        {
            (*room_cmd_table[cmd].room_fun) ( room, argument );
            tail_chain( );
            return;
        }
    }
    sprintf( buf, "Room_interpret: invalid cmd from room %d: '%s'",
        room->vnum, command );
    bug( buf, 0 );
}

/* 
* Displays ROOMprogram triggers of a room
*
* Syntax: rpstat [name]
*/
void do_rpstat( CHAR_DATA *ch, char *argument )
{
    char        arg[ MAX_STRING_LENGTH  ];
    PROG_LIST  *rprg;
    ROOM_INDEX_DATA   *room;
    int i;
    
    one_argument( argument, arg );
    
    if ( arg[0] == '\0' )
        room = ch->in_room;
    else if ( !is_number( arg ) )
    {
        send_to_char( "You must provide a number.\n\r", ch );
        return;
    }
    else if ( ( room = get_room_index( atoi(arg) ) ) == NULL )
    {
        send_to_char( "No such room.\n\r", ch );
        return;
    }
    
    sprintf( arg, "Room #%-6d [%s]\n\r",
        room->vnum, room->name );
    send_to_char( arg, ch );
    
    sprintf( arg, "Delay   %-6d [%s]\n\r",
        room->rprog_delay,
        room->rprog_target == NULL 
        ? "No target" : room->rprog_target->name );
    send_to_char( arg, ch );
    
    if ( !room->rprog_flags )
    {
        send_to_char( "[No programs set]\n\r", ch);
        return;
    }
    
    for ( i = 0, rprg = room->rprogs; rprg != NULL;
    rprg = rprg->next )
        
    {
        sprintf( arg, "[%2d] Trigger [%-8s] Program [%4d] Phrase [%s]\n\r",
            ++i,
            prog_type_to_name( rprg->trig_type ),
            rprg->vnum,
            rprg->trig_phrase );
        send_to_char( arg, ch );
    }
    
    return;
    
}

/*
* Displays the source code of a given ROOMprogram
*
* Syntax: rpdump [vnum]
*/
void do_rpdump( CHAR_DATA *ch, char *argument )
{
    char buf[ MAX_INPUT_LENGTH ];
    PROG_CODE *rprg;
    
    one_argument( argument, buf );
    if ( ( rprg = get_prog_index( atoi(buf), PRG_RPROG ) ) == NULL )
    {
        send_to_char( "No such ROOMprogram.\n\r", ch );
        return;
    }
    page_to_char( rprg->code, ch );
}

/*
* Prints the argument to all active players in the game
*
* Syntax: room gecho [string]
*/
void do_rpgecho( ROOM_INDEX_DATA *room, char *argument )
{
    DESCRIPTOR_DATA *d;
    
    if ( argument[0] == '\0' )
    {
        bug( "RpGEcho: missing argument from vnum %d",
            room->vnum );
        return;
    }
    
    for ( d = descriptor_list; d; d = d->next )
    {
        if ( d->connected == CON_PLAYING )
        {
            if ( IS_IMMORTAL(d->character) )
                send_to_char( "Room echo> ", d->character );
            send_to_char( argument, d->character );
            send_to_char( "\n\r", d->character );
        }
    }
}

/*
* Prints the argument to all players in the same area as the room
*
* Syntax: room zecho [string]
*/
void do_rpzecho( ROOM_INDEX_DATA *room, char *argument )
{
    DESCRIPTOR_DATA *d;
    
    if ( argument[0] == '\0' )
    {
        bug( "RpZEcho: missing argument from vnum %d",
            room->vnum );
        return;
    }
    
    for ( d = descriptor_list; d; d = d->next )
    {
        if ( d->connected == CON_PLAYING 
            &&   d->character->in_room != NULL 
            &&   d->character->in_room->area == room->area )
        {
            if ( IS_IMMORTAL(d->character) )
                send_to_char( "Room echo> ", d->character );
            send_to_char( argument, d->character );
            send_to_char( "\n\r", d->character );
        }
    }
}

/*
* Prints the argument to all the rooms aroud the room
*
* Syntax: room asound [string]
*/
void do_rpasound( ROOM_INDEX_DATA *room, char *argument )
{
    int              door;
    
    if ( argument[0] == '\0' )
        return;
    
    for ( door = 0; door < 6; door++ )
    {
        EXIT_DATA       *pexit;
        
        if ( ( pexit = room->exit[door] ) != NULL
            &&   pexit->u1.to_room != NULL
            &&   pexit->u1.to_room != room
            &&   pexit->u1.to_room->people != NULL )
        {
            act( argument, pexit->u1.to_room->people, NULL, NULL, TO_ROOM );
            act( argument, pexit->u1.to_room->people, NULL, NULL, TO_CHAR );
        }
    }
    return;
    
}

/*
* Prints the message to everyone in the room other than the victim
*
* Syntax: room echoaround [victim] [string]
*/

void do_rpechoaround( ROOM_INDEX_DATA *room, char *argument )
{
    char       arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' )
        return;
    
    if ( ( victim=get_char_room( NULL, room, arg ) ) == NULL )
        return;
    
    act( argument, victim, NULL, victim, TO_NOTVICT );
}

/*
* Prints the message to only the victim
*
* Syntax: room echoat [victim] [string]
*/
void do_rpechoat( ROOM_INDEX_DATA *room, char *argument )
{
    char       arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
        return;
    
    if ( ( victim = get_char_room( NULL, room, arg ) ) == NULL )
        return;
    
    act( argument, victim, NULL, NULL, TO_CHAR );
}

/*
* Prints the message to the room at large
*
* Syntax: rpecho [string]
*/
void do_rpecho( ROOM_INDEX_DATA *room, char *argument )
{
    if ( argument[0] == '\0' )
        return;
    
    if ( !room->people )
        return;
    
    act( argument, room->people, NULL, NULL, TO_ROOM );
    act( argument, room->people, NULL, NULL, TO_CHAR );
}

/*
* Lets the room load a mobile.
*
* Syntax: room mload [vnum]
*/
void do_rpmload( ROOM_INDEX_DATA *room, char *argument )
{
    char            arg[ MAX_INPUT_LENGTH ];
    MOB_INDEX_DATA *pMobIndex;
    CHAR_DATA      *victim;
    int vnum;
    
    one_argument( argument, arg );
    
    if ( arg[0] == '\0' || !is_number(arg) )
        return;
    
    vnum = atoi(arg);
    if ( ( pMobIndex = get_mob_index( vnum ) ) == NULL )
    {
        sprintf( arg, "Rpmload: bad mob index (%d) from room %d",
            vnum, room->vnum );
        bug( arg, 0 );
        return;
    }
    victim = create_mobile( pMobIndex );
    char_to_room( victim, room );
    return;
}

/*
* Lets the room load an object
*
* Syntax: room oload [vnum] [level]
*/
void do_rpoload( ROOM_INDEX_DATA *room, char *argument )
{
    char arg1[ MAX_INPUT_LENGTH ];
    char arg2[ MAX_INPUT_LENGTH ];
    char arg3[ MAX_INPUT_LENGTH ];
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA       *obj;
    int             level;
    
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    one_argument( argument, arg3 );
    
    if ( arg1[0] == '\0' || !is_number( arg1 ) || arg2[0] == '\0' 
        || !is_number( arg2 ) )
    {
        bug( "Rpoload - Bad syntax from vnum %d.",
            room->vnum );
        return;
    }
    
    level = atoi( arg2 );
    /*if ( level < 0 || level > LEVEL_IMMORTAL )
    {
        bug( "Rpoload - Bad level from vnum %d.", room->vnum );
        return;
    }*/
    
    if ( ( pObjIndex = get_obj_index( atoi( arg1 ) ) ) == NULL )
    {
        bug( "Rpoload - Bad vnum arg from vnum %d.", room->vnum );
        return;
    }
    
    obj = create_object( pObjIndex, level );
    obj_to_room( obj, room );
    
    return;
}

/*
* Lets the room purge all objects npcs in the room,
* or purge a specified object or mob in the room.
*
* syntax room purge {target}
*/
void do_rppurge( ROOM_INDEX_DATA *room, char *argument )
{
    char       arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;
    OBJ_DATA  *obj;
    
    one_argument( argument, arg );
    
    if ( arg[0] == '\0' )
    {
        /* 'purge' */
        CHAR_DATA *vnext;
        OBJ_DATA  *obj_next;
        
        for ( victim = room->people; victim != NULL; victim = vnext )
        {
            vnext = victim->next_in_room;
            if ( IS_NPC( victim ) 
                &&   !IS_SET(victim->act, ACT_NOPURGE) )
                extract_char( victim, TRUE );
        }
        
        for ( obj = room->contents; obj != NULL; obj = obj_next )
        {
            obj_next = obj->next_content;
            if ( !IS_SET(obj->extra_flags, ITEM_NOPURGE) )
                extract_obj( obj );
        }
        
        return;
    }
    
    if ( ( victim = get_char_room( NULL, room, arg ) ) == NULL )
    {
        if ( ( obj = get_obj_here( NULL, room, arg ) ) )
        {
            extract_obj( obj );
        }
        else
        {
            bug( "Rppurge - Bad argument from vnum %d.", room->vnum );
        }
        return;
    }
    
    if ( !IS_NPC( victim ) )
    {
        bug( "Rppurge - Purging a PC from vnum %d.", room->vnum );
        return;
    }
    extract_char( victim, TRUE );
    return;
}

/*
* Lets the room transfer people.  The 'all' argument transfers
*  everyone in the room to the specified location
*
* Syntax: room transfer [target|'all'] [location]
*/
void do_rptransfer( ROOM_INDEX_DATA *room, char *argument )
{
    char             arg1[ MAX_INPUT_LENGTH ];
    char             arg2[ MAX_INPUT_LENGTH ];
    char	     buf[MAX_STRING_LENGTH];
    ROOM_INDEX_DATA *location;
    CHAR_DATA       *victim;
    OBJ_DATA	    *tobj;
    
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    
    if ( arg1[0] == '\0' )
    {
        bug( "Rptransfer - Bad syntax from vnum %d.", room->vnum );
        return;
    }
    
    if ( !str_cmp( arg1, "all" ) )
    {
        CHAR_DATA *victim_next;
        
        for ( victim = room->people; victim != NULL; victim = victim_next )
        {
            victim_next = victim->next_in_room;
            if ( !IS_NPC(victim) )
            {
                sprintf( buf, "%s %s", victim->name, arg2 );
                do_rptransfer( room, buf );
            }
        }
        return;
    }
    
    /*
    * Thanks to Grodyn for the optional location parameter.
    */
    if ( arg2[0] == '\0' )
    {
        location = room;
    }
    else
    {
        if ( is_number(arg2))
            location = get_room_index( atoi(arg2) );
        else if ( (victim = get_char_world( NULL, arg2 )) != NULL )
            location = victim->in_room;
        else if ( ( tobj = get_obj_world( NULL, arg2 )) != NULL )
            location = tobj->in_room;
        else
        {
            bug( "Rptransfer - No such location from vnum %d.", room->vnum );
            return;
        }
        
        if ( room_is_private( location ) )
            return;
    }
    
    if ( ( victim = get_char_world( NULL, arg1 ) ) == NULL )
        return;
    
    if ( victim->in_room == NULL )
        return;
    
    if ( victim->fighting != NULL )
        stop_fighting( victim, TRUE );
    char_from_room( victim );
    char_to_room( victim, location );
    do_look( victim, "auto" );
    
    return;
}

/*
* Lets the room transfer all chars in same group as the victim.
*
* Syntax: room gtransfer [victim] [location]
*/
void do_rpgtransfer( ROOM_INDEX_DATA *room, char *argument )
{
    char             arg1[ MAX_INPUT_LENGTH ];
    char             arg2[ MAX_INPUT_LENGTH ];
    char	     buf[MAX_STRING_LENGTH];
    CHAR_DATA       *who, *victim, *victim_next;
    
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    
    if ( arg1[0] == '\0' )
    {
        bug( "Rpgtransfer - Bad syntax from vnum %d.", room->vnum );
        return;
    }
    
    if ( (who = get_char_room( NULL, room, arg1 )) == NULL )
        return;
    
    for ( victim = room->people; victim; victim = victim_next )
    {
        victim_next = victim->next_in_room;
        if( is_same_group( who,victim ) )
        {
            sprintf( buf, "%s %s", victim->name, arg2 );
            do_rptransfer( room, buf );
        }
    }
    return;
}

/*
* Lets the room force someone to do something. Must be mortal level
* and the all argument only affects those in the room.
*
* Syntax: room force [victim] [commands]
*/
void do_rpforce( ROOM_INDEX_DATA *room, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
        bug( "Rpforce - Bad syntax from vnum %d.", room->vnum );
        return;
    }
    
    if ( !str_cmp( arg, "all" ) )
    {
        CHAR_DATA *vch;
        CHAR_DATA *vch_next;
        
        for ( vch = char_list; vch != NULL; vch = vch_next )
        {
            vch_next = vch->next;
            
            if ( vch->in_room == room && !IS_IMMORTAL( vch ) )
                interpret( vch, argument, 0  );
        }
    }
    else
    {
        CHAR_DATA *victim;
        
        if ( ( victim = get_char_room( NULL, room, arg ) ) == NULL )
            return;
        
        interpret( victim, argument, 0  );
    }
    
    return;
}

/*
* Lets the room force a group something. Must be mortal level.
*
* Syntax: room gforce [victim] [commands]
*/
void do_rpgforce( ROOM_INDEX_DATA *room, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim, *vch, *vch_next;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
        bug( "RpGforce - Bad syntax from vnum %d.", room->vnum );
        return;
    }
    
    if ( ( victim = get_char_room( NULL, room, arg ) ) == NULL )
        return;
    
    for ( vch = victim->in_room->people; vch != NULL; vch = vch_next )
    {
        vch_next = vch->next_in_room;
        
        if ( is_same_group(victim,vch) )
            interpret( vch, argument, 0  );
    }
    return;
}

/*
* Forces all mobiles of certain vnum to do something
*
* Syntax: room vforce [vnum] [commands]
*/
void do_rpvforce( ROOM_INDEX_DATA *room, char *argument )
{
    CHAR_DATA *victim, *victim_next;
    char arg[ MAX_INPUT_LENGTH ];
    int vnum;
    
    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
        bug( "RpVforce - Bad syntax from vnum %d.", room->vnum );
        return;
    }
    
    if ( !is_number( arg ) )
    {
        bug( "RpVforce - Non-number argument vnum %d.", room->vnum );
        return;
    }
    
    vnum = atoi( arg );
    
    for ( victim = char_list; victim; victim = victim_next )
    {
        victim_next = victim->next;
        if ( IS_NPC(victim) && victim->pIndexData->vnum == vnum
            && victim->fighting == NULL )
            interpret( victim, argument, 0  );
    }
    return;
}

/*
* Lets room cause unconditional damage to someone. Nasty, use with caution.
* Also, this is silent, you must show your own damage message...
*
* Syntax: room damage [victim] [min] [max] {kill}
*/
void do_rpdamage( ROOM_INDEX_DATA *room, char *argument )
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
        bug( "RpDamage - Bad syntax from vnum %d.", room->vnum );
        return;
    }
    if( !str_cmp( target, "all" ) )
        fAll = TRUE;
    else if( ( victim = get_char_room( NULL, room, target ) ) == NULL )
        return;
    
    if ( is_number( min ) )
        low = atoi( min );
    else
    {
        bug( "RpDamage - Bad damage min vnum %d.", room->vnum );
        return;
    }
    if ( is_number( max ) )
        high = atoi( max );
    else
    {
        bug( "RpDamage - Bad damage max vnum %d.", room->vnum );
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
        for( victim = room->people; victim; victim = victim_next )
        {
            victim_next = victim->next_in_room;
            damage( victim, victim, 
                fKill ? 
                number_range(low,high) : UMIN(victim->hit,number_range(low,high)),
                TYPE_UNDEFINED, DAM_NONE, FALSE);
        }
    }
    else
        damage( victim, victim, 
        fKill ? 
        number_range(low,high) : UMIN(victim->hit,number_range(low,high)),
        TYPE_UNDEFINED, DAM_NONE, FALSE);
    return;
}

/*
* Lets the room remember a target. The target can be referred to
* with $q and $Q codes in ROOMprograms. See also "room forget".
*
* Syntax: room remember [victim]
*/
void do_rpremember( ROOM_INDEX_DATA *room, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    one_argument( argument, arg );
    if ( arg[0] != '\0' )
        room->rprog_target = get_char_world( NULL, arg );
    else
        bug( "RpRemember: missing argument from vnum %d.", room->vnum );
}

/*
* Reverse of "room remember".
*
* Syntax: room forget
*/
void do_rpforget( ROOM_INDEX_DATA *room, char *argument )
{
    room->rprog_target = NULL;
}

/*
* Sets a delay for ROOMprogram execution. When the delay time expires,
* the room is checked for a ROOMprogram with DELAY trigger, and if
* one is found, it is executed. Delay is counted in PULSE_AREA
*
* Syntax: room delay [pulses]
*/
void do_rpdelay( ROOM_INDEX_DATA *room, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    
    one_argument( argument, arg );
    if ( !is_number( arg ) )
    {
        bug( "RpDelay: invalid arg from vnum %d.", room->vnum );
        return;
    }
    room->rprog_delay = atoi( arg );
}

/*
* Reverse of "room delay", deactivates the timer.
*
* Syntax: room cancel
*/
void do_rpcancel( ROOM_INDEX_DATA *room, char *argument )
{
    room->rprog_delay = -1;
}
/*
* Lets the room call another ROOMprogram within a ROOMprogram.
* This is a crude way to implement subroutines/functions. Beware of
* nested loops and unwanted triggerings... Stack usage might be a problem.
* Characters and objects referred to must be in the room.
*
* Syntax: room call [vnum] [victim|'null'] [object1|'null'] [object2|'null']
*
*/
void do_rpcall( ROOM_INDEX_DATA *room, char *argument )
{
    char arg[ MAX_INPUT_LENGTH ];
    CHAR_DATA *vch;
    OBJ_DATA *obj1, *obj2;
    PROG_CODE *prg;
    extern void program_flow( sh_int, char *, CHAR_DATA *, OBJ_DATA *, ROOM_INDEX_DATA *, CHAR_DATA *, const void *, const void * );
    
    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
        bug( "RpCall: missing arguments from vnum %d.", room->vnum );
        return;
    }
    if ( ( prg = get_prog_index( atoi(arg), PRG_RPROG ) ) == NULL )
    {
        bug( "RpCall: invalid prog from vnum %d.", room->vnum );
        return;
    }
    vch = NULL;
    obj1 = obj2 = NULL;
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
        vch = get_char_room( NULL, room, arg );
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
        obj1 = get_obj_here( NULL, room, arg );
    argument = one_argument( argument, arg );
    if ( arg[0] != '\0' )
        obj2 = get_obj_here( NULL, room, arg );
    program_flow( prg->vnum, prg->code, NULL, NULL, room, vch, (void *)obj1, (void *)obj2 );
}

/*
* Lets the room transfer an object. The object must be in the room.
*
* Syntax: room otransfer [item name] [location]
*/
void do_rpotransfer( ROOM_INDEX_DATA *room, char *argument )
{
    OBJ_DATA *obj, *tobj;
    ROOM_INDEX_DATA *location;
    char arg[ MAX_INPUT_LENGTH ];
    char buf[ MAX_INPUT_LENGTH ];
    CHAR_DATA *victim;
    
    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
        bug( "RpOTransfer - Missing argument from vnum %d.", room->vnum );
        return;
    }
    one_argument( argument, buf );
    
    if ( is_number( buf ) )
        location = get_room_index( atoi(buf) );
    else if ( (victim = get_char_world( NULL, buf )) != NULL )
        location = victim->in_room;
    else if ( ( tobj = get_obj_world( NULL, arg )) != NULL )
        location = tobj->in_room;
    else
    {
        bug( "RpOTransfer - No such location from vnum %d.", room->vnum );
        return;
    }
    
    if ( (obj = get_obj_here( NULL, room, arg )) == NULL )
        return;
    
    if ( obj->carried_by == NULL )
        obj_from_room( obj );
    else
    {
        if ( obj->wear_loc != WEAR_NONE )
            unequip_char( obj->carried_by, obj );
        obj_from_char( obj );
    }
    obj_to_room( obj, location );
}

/*
* Lets the room strip an object or all objects from the victim.
* Useful for removing e.g. quest objects from a character.
*
* Syntax: room remove [victim] [object vnum|'all']
*/
void do_rpremove( ROOM_INDEX_DATA *room, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA *obj, *obj_next;
    sh_int vnum = 0;
    bool fAll = FALSE;
    char arg[ MAX_INPUT_LENGTH ];
    
    argument = one_argument( argument, arg );
    if ( ( victim = get_char_room( NULL, room, arg ) ) == NULL )
        return;
    
    one_argument( argument, arg );
    if ( !str_cmp( arg, "all" ) )
        fAll = TRUE;
    else if ( !is_number( arg ) )
    {
        bug ( "RpRemove: Invalid object from vnum %d.", room->vnum );
        return;
    }
    else
        vnum = atoi( arg );
    
    for ( obj = victim->carrying; obj; obj = obj_next )
    {
        obj_next = obj->next_content;
        if ( fAll || obj->pIndexData->vnum == vnum )
        {
            if ( obj->wear_loc != WEAR_NONE )
                unequip_char( victim, obj );
            obj_from_char( obj );
            extract_obj( obj );
        }
    }
}
