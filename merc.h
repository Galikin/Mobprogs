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
 *  these copyright notices.        
 *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/*
 * $Log: merc.h,v $
 * Revision 1.149  2003/08/13 18:00:20  sjofn
 * changed family notes to kvetsh notes -Neut
 *
 * Revision 1.148  2003/06/16 05:45:29  mull
 * Mull: Added reimburse_skills() to give back trains/pracs from lost skills
 *
 * Revision 1.147  2003/05/17 04:46:32  mull
 * Mull: Added exit/exall trigger type for mobprogs
 *
 * Revision 1.146  2003/01/24 01:43:51  coyotilo
 * Coy: Ton of stuff for the song driver.  Added utility function chprintf.
 *
 * Revision 1.145  2003/01/10 00:39:05  mull
 * Mull: Added new extra flag for quest items (X) and associated code
 *
 * Revision 1.144  2002/12/19 16:46:15  coyotilo
 * Coy: More obj and room prog stuff.
 *
 * Revision 1.142  2002/12/18 16:01:27  coyotilo
 * Coy: Added object and room progs.
 *
 * Revision 1.141  2002/12/17 00:51:49  coyotilo
 * Coy: Small amount of log information trying to catch the ojb_update crashing.
 *
 * Revision 1.140  2002/07/15 06:52:38  mull
 * Mull: Added in working versions of 'bola' and 'deadly strike'
 *
 * Revision 1.139  2002/04/04 19:35:50  sjofn
 * removed mermeric burn from hunter special
 *
 * Revision 1.138  2002/03/24 20:10:49  icnec
 * Icnec: Slayer is ready for testing now, I think :)  I also fixed a bug with autoauction.
 *
 * Revision 1.137  2001/12/18 19:29:52  sjofn
 * * Revision 1.136  2001/12/15 20:53:40  icnec
 * Icnec: I completed the owhere immortal command.
 *            code was added to a variety of areas, but in particular
 *            interp.c, merc.h, act_wiz.c
 *
 * correct makefile, updated max continents, commented out owehre til it can be
 * tested - neut
 *
 * Revision 1.135  2001/12/13 09:46:50  coyotilo
 * Coy: Cleaned up the addition to name checking and some other
 * minor tweaks.
 *
 * Revision 1.134  2001/12/04 05:46:30  coyotilo
 * Coy: Fixed scan/farsight and decoy problem, tweaked scan and
 * farsight so players can't tell if a wizi mob is in an empty room with
 * them.  Added parenthised prefix to players (like white aura, etc)
 * if they have decoy or camouflage on, but they only show up when
 * holylight is on.  Super tweak to decoy which allows a players to
 * create a decoy from an object in their inventory.
 *
 * Revision 1.133  2001/09/24 08:39:25  coyotilo
 * Coy: More fixes from code mixup.
 *
 * Revision 1.132  2001/09/22 09:55:03  coyotilo
 * Coy: Reinstating some of my bard code.
 *
 * Revision 1.131  2001/09/22 08:27:40  coyotilo
 * Coy: Attempt to return bard code without erasure.
 *
 * Revision 1.130  2001/09/22 07:38:07  coyotilo
 * Coy: Attempt to return code to a earlier state
 * (before bard changes)
 *
 * Revision 1.128  2001/09/11 05:45:48  nalathni
 * Nalathni: uncommenting commands in interp, updating other so marriage code now works
 *
 * Revision 1.126  2001/08/21 15:05:30  sjofn
 * adding champagne to liquids and added 2 to Max_LIQ in merc.h -Neut
 *
 * Revision 1.125  2001/08/21 14:26:20  coyotilo
 * Coy: Fixing an errant commit.
 *
 * Revision 1.123  2001/08/20 16:59:30  sjofn
 * added spells to const.c, changed collect back to collect rain, though it
 * works with collect as well. -neut
 *
 * Revision 1.122  2001/08/17 13:00:24  nalathni
 * Nalathni: fixes to preserve, strike, and collect rain is now collect
 *
 * Revision 1.121  2001/08/08 13:44:54  sjofn
 * tribe leaders will get a note when someone initiates or rejects their tribe.
 * -Neut
 *
 * Revision 1.120  2001/08/04 23:44:25  coyotilo
 * Coy: Added isaff mobprog.
 *
 * Revision 1.119  2001/08/04 08:01:23  coyotilo
 * Coy: Tweaks for Righteous Magic, Chaotic Shift, Orb of the Sun,
 * Aegis, Firststrike, and Blessed Weapon.
 *
 * Revision 1.118  2001/07/18 02:02:23  coyotilo
 * Coy: Added dirty and no_comm room flags and supporting code
 * to make them functional.
 *
 * Revision 1.117  2001/06/08 22:11:34  nalathni
 * Nalathni: adding collect rain
 *
 * Revision 1.116  2001/06/08 16:48:51  coyotilo
 * Coy: Added Decoy.
 *
 * Revision 1.115  2001/06/08 01:22:54  coyotilo
 * Coy: Adding Blessed Weapon
 *
 * Revision 1.114  2001/06/07 22:27:20  coyotilo
 * Coy: Added Firststrike.
 *
 * Revision 1.113  2001/06/07 19:19:17  coyotilo
 * Coy: Adding Aegis spell.
 *
 * Revision 1.112  2001/06/07 08:31:32  coyotilo
 * Coy: Added Chaotic Shift, Orb of the Sun, and Righteous Magic.
 *
 * Revision 1.111  2001/05/18 13:26:19  sjofn
 * removing the lawyer thing from mccoy. it was supposed to be taken out when
 * the other lawyer stuff was. -Neut
 *
 * Revision 1.110  2001/05/17 20:15:31  nalathni
 * Nalathni: adding strike, fix on steak for preserve
 *
 * Revision 1.109  2001/04/23 21:11:09  sjofn
 *  added fortitude to the rb skills and more skills and groups to merc.h -neut
 *
 * Revision 1.108  2001/04/07 17:22:55  coyotilo
 * Coy: A couple message modifications/changes.  Changed
 * durations for purpose, bloodstrike, and sharpen from test
 * values (short durations so less time to wait) to the actual
 * game ready durations.  Added a more weapon types onto
 * the list of weapons that can't be sharpened, and added
 * NPC forms that can't be bloodstriked (bloodstricken?)
 *
 * Revision 1.107  2001/04/04 04:41:11  nalathni
 * Nalathni: adding ITEM_FLINT
 *
 * Revision 1.106  2001/03/27 21:25:25  coyotilo
 * Coy: Changes to pkill code, location command fix, added
 * bloodstrike and sharpen.
 *
 * Revision 1.105  2001/03/25 05:56:14  icnec
 * Icnec: Added concentration skill, and healing aura, and energy shield spells
 *
 * Revision 1.104  2001/03/23 03:33:15  coyotilo
 * Coy: Adding create medicine.  Bug report from fread_char
 * fixed (only one of them, the other is from the spouse code).
 *
 * Revision 1.103  2001/03/19 09:17:16  coyotilo
 * Coy: Uncommenting aff2_purpose in merc.h
 *
 * Revision 1.102  2001/03/18 07:12:52  coyotilo
 * Coy: Adding Purpose skill, Naturecall skill, and changed
 * duration for restoration to its real value for actual
 * implementation.
 *
 * Revision 1.101  2001/03/16 18:19:53  sjofn
 *
 *  expanded vnums (this should probably also affect a lot fo other things) so
 * we can go to 4 billion rooms. cleaned up the .dat files for the cvs versions.
 *
 *  -neut (and thor)
 *
 * Revision 1.100  2001/02/27 21:35:04  icnec
 * Icnec: changed timing for auction back to normal
 *
 * Revision 1.99  2001/02/27 21:29:26  icnec
 * Icnec:  Implemented a bunch of stuff for auto-auction and fixed
 * a move problem with under_water rooms
 *
 * Revision 1.98  2001/02/27 19:35:42  coyotilo
 * Coy:  Tricky way to make a wait state between casts of
 * restoration.  Added some missing bit names for stat.  Fixed
 * the unknown affect location error for camp.
 *
 * Revision 1.97  2001/02/19 03:24:31  icnec
 * Icnec:  Made fixes to auto-auction, can now tell auctioneer
 * something if on the same continent.
 *
 * Revision 1.96  2001/02/18 21:01:30  coyotilo
 * Coy: Adding Sleigh of Hand skill and Fortitude spell.
 *
 * Revision 1.95  2001/02/13 22:26:07  icnec
 * Icnec: Increased time between auction updates
 *
 * Revision 1.94  2001/02/13 04:06:00  icnec
 * Icnec: I added the auto-auction capability to the mud, doesn't save or load
 * to/from a file at this point. The main auction functions are in
 * auction.c
 *
 * Revision 1.93  2001/02/09 14:18:18  nalathni
 * Nalathni: adding obj_vnum for spices
 *
 * Revision 1.92  2001/02/05 01:40:39  icnec
 * Icnec: put finishing touches on swim skill
 *
 * Revision 1.91  2001/02/04 12:19:53  coyotilo
 * Coy: Fixed the closed corpse bug and added farsight skill.
 *
 * Revision 1.90  2001/02/04 09:15:26  icnec
 * Icnec: I implemented a faster decrease of duration when a person
 * in a group with bubble casts on it, leaves the room.  Changes
 * were made to update.c and some messages for moves in act_move.c
 * as well as some message adjustments in magic.c
 *
 * Revision 1.89  2001/02/03 20:34:27  coyotilo
 * Coy: Fixed advanced circle for rogues per Xander.  Added
 * overboard command (still needs real vnums entered into table
 * in act_move.c).
 *
 * Revision 1.88  2001/02/01 02:27:57  nalathni
 * Nalathni: added spices to object list
 *
 * Revision 1.87  2001/01/31 09:03:35  icnec
 * Icnec:  I added the Bubble Spell
 *
 * Revision 1.86  2001/01/30 22:02:45  coyotilo
 * Coy: Added some comments on changes made to scan_rooms
 * and pc_in_room dealing with the no_track flag.  Flip flopped
 * the numbers of COLOR_TRIBE and COLOR_NEWBIE in
 * merc.h.
 *
 * Revision 1.85  2001/01/30 06:03:25  icnec
 * Adjusted some spacing in merc.h
 *
 * Revision 1.84  2001/01/29 21:32:43  coyotilo
 * Coy: Added addition functionality to reading mobs from area
 * files to allow aff2 affects to be perm affects.
 *
 * Revision 1.83  2001/01/29 00:10:37  coyotilo
 * Coy: Added evade skill.
 *
 * Revision 1.82  2001/01/27 19:26:33  coyotilo
 * Coy: Color scheme fixes to allow for proper use of the
 * tribe channel.  Mini fix from last commit changed back
 * to original form.
 *
 * Revision 1.81  2001/01/25 14:41:05  nalathni
 * Nalathni: remort2 stuff
 *
 * Revision 1.80  2001/01/22 13:01:42  nalathni
 * Nalathni: some remort2 stuff and max_food increased by one
 *
 * Revision 1.79  2001/01/21 22:50:53  icnec
 * Added the huge integer value defined by gg... also fixed some spacing
 * in act_move.c
 *
 * Revision 1.78  2001/01/21 22:09:21  icnec
 * Added a parenthesis that was crashing in the underwater update function
 *
 * Revision 1.77  2001/01/20 18:28:03  icnec
 * I added a SWIM_AFF flag now...it is implemented as "gg"
 * this should clear up the conflict problem
 *
 * Revision 1.76  2001/01/20 06:57:43  icnec
 * Icnec - I implemented the drowning room update...made changes to update.c ,
 * merc.h, and act_move.c
 *
 * Revision 1.75  2001/01/19 12:08:46  coyotilo
 * Coy: Did a bunch of conversion stuff for 'super shield' to 'ward'.
 * The conversion takes place *crosses fingers* in save.c in
 * function fread_char.  I just commented out many of the
 * declarations rather than deleting entirely (me being paranoid
 * maybe).  It, 'ward', at this point of the conversion, works exactly
 * as 'super shield' did.
 *
 * Revision 1.74  2001/01/18 04:17:06  nalathni
 * Nalathni: adding steak to obj_vnum list
 *
 * Revision 1.73  2001/01/17 05:24:35  coyotilo
 * Coy: Halflings load a pipe on creation and fixed hit percentage
 *         for smoke rings.
 *
 * Revision 1.72  2001/01/15 21:08:03  sjofn
 *
 *  Hopfully this is just adding tracking to the things that you can't do in a
 * quest. I don't know what was editted in those other files.
 *
 *  -neut
 *
 * Revision 1.71  2000/12/19 02:59:28  coyotilo
 * Coy: Quick fix for smoke rings skill
 *
 * Revision 1.70  2000/12/12 19:06:44  coyotilo
 * Coy: Added stuff for smoke rings skill.
 *
 * Revision 1.69  2000/11/13 14:54:19  nalathni
 * Nalathni: tribe fixes
 *
 * Revision 1.68  2000/11/07 18:59:02  nalathni
 * Nalathni: tribe fixes
 *
 * Revision 1.67  2000/11/07 15:36:44  nalathni
 * Nalathni: tribe fix
 *
 * Revision 1.66  2000/11/06 19:16:19  nalathni
 * Nalathni: added line to make tribe work
 *
 * Revision 1.65  2000/11/06 18:59:29  sjofn
 *
 *  commented out stances and songs, add tribe to interp.c
 *
 * -neut
 *
 * Revision 1.64  2000/10/25 19:50:03  nalathni
 * Nalathni: adding line for camp
 *
 * Revision 1.63  2000/10/24 13:56:28  nalathni
 * Nalathni: adding tribe channel stuff
 *
 * Revision 1.62  2000/10/23 19:35:24  nalathni
 * Nalathni: remort2 stuff
 *
 * Revision 1.61  2000/10/16 03:44:28  nalathni
 * Nalathni: fixes to marry
 *
 * Revision 1.60  2000/09/26 17:35:55  nalathni
 * Nalathni: adding restoration
 *
 * Revision 1.59  2000/09/26 01:50:12  nalathni
 * Nalathni: adding camp
 *
 * Revision 1.58  2000/08/16 03:21:39  nalathni
 * Nalathni: adding squeeze
 *
 * Revision 1.57  2000/08/15 04:08:25  nalathni
 * Nalathni: removing butcher
 *
 * Revision 1.56  2000/08/14 23:51:36  sjofn
 * changed order of rebirth rooms - neut
 *
 * Revision 1.55  2000/08/12 01:30:52  nalathni
 * Nalathni: Adding preserve
 *
 * Revision 1.54  2000/07/25 04:31:13  nalathni
 * Nalathni: adding butcher
 *
 * Revision 1.53  2000/06/13 17:52:10  lorn
 * Lorn: necromancy work
 *
 * Revision 1.52  2000/06/07 03:32:56  nalathni
 * Nalathni: adding gsn for spells
 *
 * Revision 1.50  2000/05/15 21:33:52  nalathni
 * Nalathni: added the PLR_CONSENT flag to char*data
 *
 * Revision 1.48  2000/04/14 06:36:29  mythos
 * Mythos: more song/stance additions
 *
 * Revision 1.47  2000/04/12 15:20:42  nalathni
 * Nalathni: Changed the bool spouse to char * spouse in pcdata
 *
 * Revision 1.45  2000/04/09 23:44:23  nalathni
 * Nalathni:  added spouse to pcdata, and added PLR_CONSENT to act flags
 *
 * Revision 1.43  2000/04/07 04:42:26  mythos
 * Mythos: song/stance_type info, song gsn's, max_skill increase
 *
 * Revision 1.42  2000/03/30 17:26:34  lorn
 * Lorn: animate dead and bored_prog
 *
 * Revision 1.41  2000/03/09 17:40:50  lorn
 * Lorn: bug fixes, clan_recall to celestial_recall
 *
 * Revision 1.40  2000/03/07 04:22:20  lorn
 * Lorn: second wield skill check fix
 *
 * Revision 1.38  2000/02/26 07:34:01  mythos
 * Mythos: added create goat, clan recall, ride tweak, sushi can now poison
 *
 * Revision 1.37  2000/02/25 04:26:00  lorn
 * Lorn: recharge skill
 *
 * Revision 1.36  2000/02/17 08:18:41  mythos
 * Mythos: ride command added, associated adjustments
 *
 * Revision 1.35  2000/02/10 04:46:04  mythos
 * Mythos: added create sushi, minor clanskill tweaks
 *
 * Revision 1.34  2000/02/06 07:12:43  mythos
 * Mythos: added guinness dream and forge blade clanspells
 *
 * Revision 1.33  2000/02/03 02:40:30  mythos
 * Mythos: level info is now a toggle, do_mount tweak, do_cast tweak
 *
 * Revision 1.32  2000/01/30 05:47:50  mythos
 * X: added cskill and cpose commands (clanskill/pose), fixed init/join bug
 *
 * Revision 1.31  2000/01/27 07:26:22  mythos
 * X: gate catalyst, bow weapon_type, two-hander fixes, etc bug fixes
 *
 * Revision 1.30  2000/01/23 08:25:19  mythos
 * X: extracted is_exact_name from check_parse_name; fixed notes bug
 *
 * Revision 1.29  2000/01/23 00:54:18  mythos
 * X: addict flag 0-20%, 2*xp on saturday, bug fixes/ride-prep
 *
 * Revision 1.28  2000/01/03 16:01:37  sjofn
 * add the new dam messages -Neut
 *
 * Revision 1.27  1999/12/14 03:31:03  sjofn
 *
 * add IG channel -Neut
 *
 * Revision 1.26  1999/11/08 17:58:53  cvsuser
 * Lorn: black plague not bplague, send_ship_info and some messaging stuff
 *
 * Revision 1.25  1999/11/06 21:51:02  cvsuser
 * Lorn: black plague
 *
 * Revision 1.24  1999/11/06 19:30:08  cvsuser
 * added a few things for black plague. Couldn't get them all to work
 * so I took the parts out of handler.c and magic.c
 * Neut
 *
 * Revision 1.23  1999/10/22 19:52:52  cvsuser
 * Lorn: send_ship_info
 *
 * Revision 1.22  1999/09/27 23:04:32  cvsuser
 * Lorn: engulf stuff
 *
 * Revision 1.21  1999/09/21 17:51:12  cvsuser
 * Lorn: clan points mods, quiet on whois, palm fix
 *
 * Revision 1.20  1999/09/15 01:22:26  cvsuser
 * Lorn: palm, location, empty and newbie moves to 150
 *
 * Revision 1.19  1999/09/09 00:56:04  cvsuser
 * Ivan: Clan points added. CPADD gives clan points, CPSUBTRACT takes
 *       them away. You must be leader of the clan the victim belongs
 *       to in order to use these commands.
 *
 * Revision 1.18  1999/09/08 02:29:06  cvsuser
 * Ivan: Fixes continued.
 *
 * Revision 1.17  1999/09/07 21:54:00  cvsuser
 * Lorn: ship->port = null, declared global int port variable
 *
 * Revision 1.16  1999/09/06 07:31:50  cvsuser
 * give_word_prog created and motorball repairs
 *
 * Revision 1.15  1999/09/05 19:03:07  cvsuser
 * Ivan: Custom entry and exit message capability added.
 *
 * Revision 1.14  1999/08/19 00:16:55  cvsuser
 * search command, pc_only_bit_name, pkill mob
 *
 * Revision 1.13  1999/08/17 18:13:24  cvsuser
 * Ivan: Added Lorn's spec_chase_pc.
 *
 * Revision 1.12  1999/08/12 22:15:10  cvsuser
 * Ivan: Pirates & a few minor changes. Nothing documentable.
 *
 * Revision 1.11  1999/06/03 22:54:52  cvsuser
 * Ivan: Changes to qpadd, qpsubtract, scatter, removed call to
 *       gethostbyaddr, fixed formatting in area detail and
 *       mstat, allowed cps to be trained down(only to 41) after
 *       rebirth, added continent name to custom prompt system.
 *
 * Revision 1.10  1999/05/17 16:11:21  cvsuser
 * Ivan: Numerous security fixes, fix for the cloning weapon bug, fix for
 *       redirect, modified rebirth code to try to eliminate recent
 *       crash bug, added simple scatter command, modified format of
 *       mstat command to make it more readable, fixed random_room_
 *       in_world crash bug for 0 room areas.
 *
 * Revision 1.9  1999/04/19 01:08:43  cvsuser
 * Ivan: Fix the potion/food/container bug. There's also some code for the
 *       ships in here, but it shouldn't affect any toher part of the game.
 *
 * Revision 1.8  1999/04/17 14:22:03  cvsuser
 * Ivan: Pfiles can now hold a web page link. If defined, name becomes
 *       an anchor on the wholist web page.
 *
 * Revision 1.7  1999/04/10 12:44:35  cvsuser
 * Ivan: Fixed web page who list so incognito imms don't show, the anchors
 *       work properly now, color's in titles work and clan names link
 *       to the clan page, clan.html.
 *
 * Revision 1.6  1999/04/06 18:07:17  cvsuser
 * Ivan: Added rb & rm remove command, added wiz newban and newallow
 *       commands, other small fixes requested by Neut.
 *
 * Revision 1.5  1999/04/01 20:19:58  cvsuser
 * Ivan: Paged output of table skill show and areas commands.
 *
 * Revision 1.4  1999/04/01 03:13:11  cvsuser
 * Ivan: Minor mods. Clan only eq can't be used by recruits. Only aggro mobs
 *       are extracted after a nofollow. Removed case sensitivity and other
 *       bugs in table command, stripped all the ^Ms out of all files.
 *
 * Revision 1.3  1999/03/23 21:49:49  cvsuser
 * Ivan: Added RESETAREA command, resets a specified area on command. Minor mods
 *       to clear up Solaris warning messages.
 *
 * Revision 1.2  1999/03/22 23:47:35  cvsuser
 * Ivan: Create food & feast now select randomly from a food list. In db.c,
 *       fix_food_list verifies the list and takes appropriate action.
 *
 * Revision 1.1.1.1  1999/03/19 19:10:18  sjofn
 * Importing Ivan's tree as aesir-0.1
 *
 * Use: cvs checkout aesir-0.1
 *
 * Revision 1.1.1.1  1999/03/10 21:21:58  viviano
 * Inital Checkin
 *
 */

/*
 * Accommodate old non-Ansi compilers.
 */
#include "protocol.h"

#if defined(TRADITIONAL)
#define const
#define args( list )                    ( )
#define DECLARE_DO_FUN( fun )           void fun( )
#define DECLARE_SPEC_FUN( fun )         bool fun( )
#define DECLARE_SPELL_FUN( fun )        void fun( )
#define DECLARE_SONG_FUN( fun )        void fun( )
/* Object and room progs - Coy 12/02*/
#define DECLARE_OBJ_FUN( fun )		void fun( )
#define DECLARE_ROOM_FUN( fun )		void fun( )
#else
#define args( list )                    list
#define DECLARE_DO_FUN( fun )           DO_FUN    fun
#define DECLARE_SPEC_FUN( fun )         SPEC_FUN  fun
#define DECLARE_SPELL_FUN( fun )        SPELL_FUN fun
#define DECLARE_SONG_FUN( fun )        SONG_FUN fun
/* Object and room progs - Coy 12/02 */
#define DECLARE_OBJ_FUN( fun )		OBJ_FUN	  fun
#define DECLARE_ROOM_FUN( fun )		ROOM_FUN  fun
#endif

/* special stuff for Handful */
#ifdef TELS
extern int srandom(unsigned);
extern int ungetc(int, FILE *);
extern int fseek(FILE *, long, int);
extern int time();
extern int fclose(FILE *);
extern void perror(const char *);
extern int fprintf(FILE *, const char *,...);
extern int printf(const char *,...);
extern int fscanf(FILE *,...);

#endif



/* system calls */
int unlink();
int system();

/*
 * Short scalar types.
 * Diavolo reports AIX compiler has bugs with short types.
 */
#if     !defined(FALSE)
#define FALSE    0
#endif

#if     !defined(TRUE)
#define TRUE     1
#endif

#if     defined(_AIX)
#if     !defined(const)
#define const
#endif
typedef int sh_int;
typedef int bool;

#define unix
#else
/* Changed by THOR from: typedef short int sh_int; */
typedef  int sh_int;
typedef unsigned char bool;

#endif

/*
 * Structure types.
 */
typedef struct affect_data AFFECT_DATA;
typedef struct auction_data AUCTION_DATA;
typedef struct owhereobj OWHERE_DATA;
typedef struct area_data AREA_DATA;
typedef struct ban_data BAN_DATA;
typedef struct buf_type BUFFER;
typedef struct char_data CHAR_DATA;
typedef struct descriptor_data DESCRIPTOR_DATA;
typedef struct exit_data EXIT_DATA;
typedef struct extra_descr_data EXTRA_DESCR_DATA;
typedef struct help_data HELP_DATA;
typedef struct kill_data KILL_DATA;
typedef struct mem_data MEM_DATA;
typedef struct mob_index_data MOB_INDEX_DATA;
typedef struct randomizer_data RANDOMIZER_DATA;
typedef struct note_data NOTE_DATA;
typedef struct obj_data OBJ_DATA;
typedef struct obj_index_data OBJ_INDEX_DATA;
typedef struct pc_data PC_DATA;
typedef struct gen_data GEN_DATA;
typedef struct reset_data RESET_DATA;
typedef struct room_index_data ROOM_INDEX_DATA;
typedef struct shop_data SHOP_DATA;
typedef struct time_info_data TIME_INFO_DATA;
typedef struct weather_data WEATHER_DATA;
typedef struct mob_prog_data MPROG_DATA;
typedef struct mob_prog_act_list MPROG_ACT_LIST;
typedef struct clan_list CLAN_LIST;
typedef struct tribe_list TRIBE_LIST;
typedef struct hometown HOMETOWN;
typedef struct continent CONTINENT;
typedef struct class_list CLASS_LIST;
typedef struct race_type RACE_TYPE;
typedef struct pc_race_type PC_RACE_LIST;
typedef struct skill_type SKILL_TYPE;
typedef struct port PORT;
typedef struct ship SHIP;
typedef struct  trivia_data         TRIVIA_DATA;
typedef struct song_type SONG_TYPE;
typedef struct song_playing SONG_PL;
typedef struct  changes_data            CHANGE_DATA;  //New changes
typedef struct  gquest_data         GQUEST; //Added for Global Quests - Galius 4/16/2013
/* Object and room progs - Coy 12/02 */
typedef struct  follow_type             FOLLOW_TYPE; //list of followers
typedef struct  prog_list               PROG_LIST;
typedef struct  prog_code               PROG_CODE;



/*
 * Function types.
 */
typedef void DO_FUN args((CHAR_DATA * ch, char *argument));
typedef bool SPEC_FUN args((CHAR_DATA * ch));
typedef void SPELL_FUN args((int sn, int level, CHAR_DATA * ch, void *vo));
typedef void SONG_FUN args((int sn, int level, CHAR_DATA * ch, void *vo));
/* Object and room progs - Coy 12/02 */
typedef void OBJ_FUN	args( ( OBJ_DATA *obj, char *argument ) );
typedef void ROOM_FUN	args( ( ROOM_INDEX_DATA *room, char *argument ) );

/*
 * String and memory management parameters.
 */
#define MAX_KEY_HASH             1024
#define MAX_STRING_LENGTH        6000
#define MAX_PAGE_BUFFER         33000
#define MAX_INPUT_LENGTH          256
#define PAGELEN                    22


#define MSL MAX_STRING_LENGTH
#define MIL MAX_INPUT_LENGTH

/* Constant used for timer routines to catch freezes. (Ivan) */

#define ALARM_FREQUENCY           180
extern char last_command[MAX_STRING_LENGTH];

/*
 * Game parameters.
 * Increase the max'es if you add more of something.
 * Adjust the pulse numbers to suit yourself.
 */
#define RACE_SKILL_RATING           5
#define CP_PER_REBIRTH              3

#define MAX_SOCIALS               540 /* changed to allow for tribe channel (hopefully) */
#define MAX_SKILL                 380
/* The actual number of songs is (MAX_SONG - 500).  The addition of 500 is used so there
 * aren't any overlap of gsn number of skills and song */
#define MAX_SONG				  504
/* This is to removed the use of int literals when dealing with songs. */
#define SONG_SN_START			  500
#define MAX_LINES_PER_SONG		   20
#define MAX_CLASS                  24 /*add +1 for each new class*/
#define MAX_GROUP                  100 /*add +1 for each new group*/
#define MAX_IN_GROUP               11
#define MAX_START_CLASS             8
#define MAX_PC_RACE                25   /* number of pc races */
#define MAX_RACE                   75   /* number of non-pc races */
#define MAX_STAT                   25   /* highest stat (str, int, wis, dex, con) */
#define MAX_LEVEL                 100
#define MAX_DAMAGE_MESSAGE         79
#define MAX_DAMAGE               25000 //Changed Max Damage from 6k to 25k (breaking weapons is stupid)
#define MAX_NEWBIES               256
#define MAX_GQUEST_MOB          25 //Added for Global Quests - Galius 4/16/2013
#define LEVEL_HERO                 (MAX_LEVEL - 9)
#define LEVEL_IMMORTAL             (MAX_LEVEL - 8)
#define MAX_ZOOM		   21
#define PULSE_PER_SECOND            10
#define PULSE_VIOLENCE            ( 2 * PULSE_PER_SECOND)
#define PULSE_MOBILE              ( 3 * PULSE_PER_SECOND)
#define PULSE_AUCTION		      (6 * PULSE_PER_SECOND)
#define PULSE_TICK                (20 * PULSE_PER_SECOND)
#define PULSE_UNDERWATER          (20 * PULSE_PER_SECOND)
#define PULSE_AREA                (50 * PULSE_PER_SECOND)
#define PULSE_SONG                (PULSE_PER_SECOND)
#define PULSE_HEALING             (5 * PULSE_PER_SECOND)
#define AUCTION_LENGTH		  	6
#define PULSE_COOLDOWN				(1 * PULSE_PER_SECOND)  //Cooldowns go down each second.

//Real time:
#define TIME_ONE_SECOND				(1)
#define TIME_FIVE_SECONDS			(5)
#define TIME_TEN_SECONDS			(10)
#define TIME_ONE_MINUTE				(60)
#define TIME_ONE_HOUR				(60 * 60)	
//Game time:
#define TIME_TWICE_PER_DAY			((24 * 60) / 2)
#define TIME_THREE_PER_DAY			((24 * 60) / 3)
#define TIME_ONE_DAY				(24 * 60)
#define TIME_ONE_WEEK				(168 * 60)
#define TIME_ONE_MONTH				((4 * 168) * 60)

/* added this constant so we can play with frequency of autosaving easier (Ivan) */
#define AUTOSAVE_FREQUENCY      60

#define IMPLEMENTOR             MAX_LEVEL
#define CREATOR                 (MAX_LEVEL - 1)
#define SUPREME                 (MAX_LEVEL - 2)
#define DEITY                   (MAX_LEVEL - 3)
#define GOD                     (MAX_LEVEL - 4)
#define IMMORTAL                (MAX_LEVEL - 5)
#define DEMI                    (MAX_LEVEL - 6)
#define ANGEL                   (MAX_LEVEL - 7)
#define SAINT                   (MAX_LEVEL - 8)
#define HERO                    LEVEL_HERO

/*
 * Color stuff by Lope of Loping Through The MUD
 */
#define CLEAR           "[0m"  /* Resets Color */
#define C_RED           "[0;31m"  /* Normal Colors        */
#define C_GREEN         "[0;32m"
#define C_YELLOW        "[0;33m"
#define C_BLUE          "[0;34m"
#define C_MAGENTA       "[0;35m"
#define C_CYAN          "[0;36m"
#define C_WHITE         "[0;37m"
#define C_D_GREY        "[1;30m"  /* Light Colors         */
#define C_B_RED         "[1;31m"
#define C_B_GREEN       "[1;32m"
#define C_B_YELLOW      "[1;33m"
#define C_B_BLUE        "[1;34m"
#define C_B_MAGENTA     "[1;35m"
#define C_B_CYAN        "[1;36m"
#define C_B_WHITE       "[1;37m"

/*
 * Web page color - Ivan 4/9/1999
 */
#define W_RED           "<FONT color=\"#7D0000\">"
#define W_GREEN         "<FONT color=\"#007D00\">"
#define W_YELLOW        "<FONT color=\"#7D7D00\">"
#define W_BLUE          "<FONT color=\"#00007D\">"
#define W_MAGENTA       "<FONT color=\"#7F007D\">"
#define W_CYAN          "<FONT color=\"#007D7D\">"
#define W_WHITE         "<FONT color=\"#7D7D7D\">"
#define W_D_GREY        "<FONT color=\"#FF0000\">"
#define W_B_RED         "<FONT color=\"#FF0000\">"
#define W_B_GREEN       "<FONT color=\"#00FF00\">"
#define W_B_YELLOW      "<FONT color=\"#FF0000\">"
#define W_B_BLUE        "<FONT color=\"#0000FF\">"
#define W_B_MAGENTA     "<FONT color=\"#FF00FF\">"
#define W_B_CYAN        "<FONT color=\"#FF0000\">"
#define W_B_WHITE       "<FONT color=\"#FFFFFF\">"

/* More color stuff, for customization, added by Ivan */

#define COLOR_NAME            0
#define COLOR_TITLE           1
#define COLOR_PROMPT          2
#define COLOR_SAY             3
#define COLOR_TELL            4
#define COLOR_OOC             5
#define COLOR_GRATZ           6
#define COLOR_CLAN            7
#define COLOR_IG              8
#define COLOR_IC              9
#define COLOR_AUCTION         10
#define COLOR_MUSIC           11
#define COLOR_IMMTALK         12
#define COLOR_YELL            13
#define COLOR_GTELL           14
#define COLOR_WIZNET          15
#define COLOR_INFO            16
#define COLOR_QUEST           17
#define COLOR_PRAY            18
#define COLOR_TRIBE	      19
#define COLOR_NEWBIE          20

/* There are 26 possible color scheme positions  Coy 1/01*/
#define COLOR_SCHEME_LENGTH   26

#define MAX_DIR	6
/*
 * Site ban structure.
 */
struct ban_data
{
    BAN_DATA *next;
    char *name;
};

/*
 * Drunk struct
 */
struct struckdrunk
{
    int min_drunk_level;
    int number_of_rep;
    char *replacement[11];
};

struct buf_type
{
    BUFFER *next;
    bool valid;
    sh_int state;               /* error state of the buffer */
    sh_int size;                /* size in k */
    char *string;               /* buffer's string */
};

/*
 * Time and weather stuff.
 */
#define SUN_DARK                    0
#define SUN_RISE                    1
#define SUN_LIGHT                   2
#define SUN_SET                     3

#define SKY_CLOUDLESS               0
#define SKY_CLOUDY                  1
#define SKY_RAINING                 2
#define SKY_LIGHTNING               3

struct clan_list
{
  char *name;
  char *leader;
  int room;
  char *who_name;
  HOMETOWN *hometown;
  char *skill;
};

/* Ship stuff - Ivan 4/17/99 */
struct ship
{
  char *name;
  int gang_plank_vnum;
  int sinkable;
  int pirate_vnum[10]; /* Pirate mob vnums, if you define your own */
  int pirate_chance; /* chance of a pirate encounter */
  int pirate_count; /* number of pirates in the raiding party */
  PORT *port;
  int num_ports;
};

struct port
{
  char *name;
  int room_vnum;
  int cost;
  int day;
  PORT *next_port;
};
/* End of ship stuff */

/* Ivan's Hometown stuff */
struct hometown
{
  char *name;
  CONTINENT *continent;
  int   recall[MAX_CLASS];
};

struct continent
{
  char *name;
  int   recall;
  int   morgue;
  int   healer;
  AREA_DATA *area_list;
  int   num_areas;
};

struct tribe_list
{
  char *name;
  char *leader;
  int room;
  char *who_name;
  HOMETOWN *hometown;
};

struct time_info_data
{
    int hour;
    int day;
    int month;
    int year;
};

struct weather_data
{
    int mmhg;
    int change;
    int sky;
    int sunlight;
};

//New changes system
struct changes_data
{
 
char * change;
char * coder;
char * date;
char * type;
time_t mudtime;
};
struct  trivia_data
{
	bool   running;
	char  *question;
	char  *answer;
	sh_int reward;
	sh_int qnumber;
	sh_int timer;
};

/*
 * OWhere state for a player (use for the owhere imm command)
 */
#define OWHERE_END					0
#define OWHERE_START					1
#define OWHERE_GET_TYPE					2
#define OWHERE_GET_WEAR					3
#define OWHERE_GET_WEAPON_TYPE				4
#define OWHERE_GET_UPPER_DAM_LIMIT			5
#define OWHERE_GET_LOWER_DAM_LIMIT			6
#define OWHERE_GET_DAM_TYPE				7
#define OWHERE_GET_UPPER_LEV_LIMIT			8
#define OWHERE_GET_LOWER_LEV_LIMIT			9
#define OWHERE_GET_APPLY_FLAGS				10
#define OWHERE_GET_SPELL_LIQUID				11
#define OWHERE_GET_RELATIONSHIP_TYPE		        12


struct owhereobj
{
	bool inuse;
	int objtype;
	int wearflag;
	int weapontype;
	int greater_avg_dam;
	int less_avg_dam;
	int damtype;
	int greater_lev;
	int less_lev;
	int applyflags[18];
	int aflags_inuse;
	int things_displayed[24]; // false = AND, true = OR
	int spell_liquid;	
};





/*
 * Connected state for a channel.
 */
#define CON_PLAYING                      0
#define CON_GET_NAME                     1
#define CON_GET_OLD_PASSWORD             2
#define CON_CONFIRM_NEW_NAME             3
#define CON_GET_NEW_PASSWORD             4
#define CON_CONFIRM_NEW_PASSWORD         5
#define CON_GET_NEW_RACE                 6
#define CON_GET_NEW_SEX                  7
#define CON_GET_NEW_CLASS                8
#define CON_GET_ALIGNMENT                9
#define CON_DEFAULT_CHOICE              10
#define CON_GEN_GROUPS                  11
#define CON_PICK_WEAPON                 12
#define CON_READ_IMOTD                  13
#define CON_READ_MOTD                   14
#define CON_BREAK_CONNECT               15
#define CON_GET_CODEWORD                16
#define CON_COPYOVER_RECOVER 			17

/*
 * Descriptor (channel) structure.
 */
struct descriptor_data
{
    DESCRIPTOR_DATA *next;
    DESCRIPTOR_DATA *snoop_by;
    CHAR_DATA *character;
    CHAR_DATA *original;
    char *host;
    sh_int descriptor;
    sh_int connected;
    bool fcommand;
    char inbuf[4 * MAX_INPUT_LENGTH];
    char incomm[MAX_INPUT_LENGTH];
    char inlast[MAX_INPUT_LENGTH];
    char *              run_buf; // added for jog
    char *              run_head; //added for jog
    int repeat;
    char *outbuf;
    int outsize;
    int outtop;
    char *showstr_head;
    char *showstr_point;
	void *              pEdit;		/* OLC */
    char **             pString;	/* OLC */
    int			editor;		/* OLC */
	protocol_t *        pProtocol;
};

/*
 * Attribute bonus structures.
 */
struct str_app_type
{
    sh_int tohit;
    sh_int todam;
    sh_int carry;
    sh_int wield;
};

struct int_app_type
{
    sh_int learn;
};

struct wis_app_type
{
    sh_int practice;
};

struct dex_app_type
{
    sh_int defensive;
};

struct con_app_type
{
    sh_int hitp;
    sh_int shock;
};

struct wiznet_type
{
    char *name;
    long flag;
    int level;
};

/* WIZnet flags */
#define WIZ_ON                  (A)
#define WIZ_TICKS               (B)
#define WIZ_LOGINS              (C)
#define WIZ_SITES               (D)
#define WIZ_LINKS               (E)
#define WIZ_DEATHS              (F)
#define WIZ_RESETS              (G)
#define WIZ_MOBDEATHS           (H)
#define WIZ_FLAGS               (I)
#define WIZ_PENALTIES           (J)
#define WIZ_SACCING             (K)
#define WIZ_LEVELS              (L)
#define WIZ_SECURE              (M)
#define WIZ_SWITCHES            (N)
#define WIZ_SNOOPS              (O)
#define WIZ_RESTORE             (P)
#define WIZ_LOAD                (Q)
#define WIZ_NEWBIE              (R)
#define WIZ_PREFIX              (S)
#define WIZ_SPAM                (T)
#define WIZ_BUGS                (U)
#define WIZ_MOBS                (V)
#define WIZ_MEM			(W)

AUCTION_DATA *auction_list;
bool wiznet_mob_prog_debug;  
/* WARNING:  global variable to disable wiznet mob progs 
   to prevent wasting cpu time */
bool wiznet_debug_bugs;  
/* WARNING:  global variable to disable wiznet bugs
   because it is capable of launching an infinite loop,
   but seeing bug reports online is useful enough to have 
   the function sometimes.   --Lorn 9/99  */

int count_diag_calls;

/* global variable for diag() function in diag.c
   that exists to control log file spam.  
   added by Lorn, Dec 1998  */
int arena;
int arena_countdown;
bool double_damage;
bool double_exp;
bool double_qp;
bool double_regen;
bool                    special_day;
int                     global_exp;
int                     global_qp;
int                     global_regen;  
int                     global_damage;


/*
 * TO types for act.
 */
#define TO_ROOM             0
#define TO_NOTVICT          1
#define TO_VICT             2
#define TO_CHAR             3

/*
 * TIMER stuff - for temporary mobs
 */
#define TIMER_QUIT 30
#define TIMER_void 12
#define TIMER_MOB_BOREDOM 15

/*
 * Help table types.
 */
struct help_data
{
    HELP_DATA *next;
    sh_int level;
    char *keyword;
    char *text;
};

/*
 * Shop types.
 */
#define MAX_TRADE        4  /* changed from 5 to 4, Feb 1999 by Lorn */

/* below added Feb 1999 by Lorn */
#define SHOP_SELL_KILLER        (A)
#define SHOP_SELL_THIEF         (B)
#define SHOP_CAN_FIGHT          (C)   /* not yet implemented */

struct shop_data
{
    SHOP_DATA *next;            /* Next shop in list            */
    sh_int keeper;              /* Vnum of shop keeper mob      */
    sh_int buy_type[MAX_TRADE]; /* Item types shop will buy     */
    int shop_flags;             /* flags for special options */ /* added by Lorn, 2/99 */
    sh_int profit_buy;          /* Cost multiplier for buying   */
    sh_int profit_sell;         /* Cost multiplier for selling  */
    sh_int open_hour;           /* First opening hour           */
    sh_int close_hour;          /* First closing hour           */
};

/*
 * Per-class stuff.
 */

#define MAX_GUILD       2
#define MAX_STATS       5
#define STAT_STR        0
#define STAT_INT        1
#define STAT_WIS        2
#define STAT_DEX        3
#define STAT_CON        4

struct class_list
{
    char *name;                 /* the full name of the class */
    char *who_name;             /* Three-letter name for 'who'  */
    sh_int attr_prime;          /* Prime attribute              */
    sh_int weapon;              /* First weapon                 */
    sh_int guild[MAX_GUILD];    /* Vnum of guild rooms          */
    sh_int skill_adept;         /* Maximum skill level          */
    sh_int thac0_00;            /* Thac0 for level  0           */
    sh_int thac0_32;            /* Thac0 for level 32           */
    sh_int hp_min;              /* Min hp gained on leveling    */
    sh_int hp_max;              /* Max hp gained on leveling    */
    bool fMana;                 /* Class gains mana on level    */
    bool move_bonus;            /* Class gains move on level    */
    char *base_group;           /* base skills gained           */
    char *default_group;        /* default skills gained        */
    float rebirth_mana;         /* Multiplier mana at rebirth   */
    float rebirth_hit;          /* Multiplier hit pts at rebth  */
    HOMETOWN *hometown;         /* Classes hometown, unused now */
};

struct attack_type
{
    char *name;                 /* name and message */
    int damage;                 /* damage class */
};

struct race_type
{
    char *name;                 /* call name of the race */
    bool pc_race;               /* can be chosen by pcs */
    long act;                   /* act bits for the race */
    long aff;                   /* aff bits for the race */
    long off;                   /* off bits for the race */
    long imm;                   /* imm bits for the race */
    long res;                   /* res bits for the race */
    long vuln;                  /* vuln bits for the race */
    long form;                  /* default form flag for the race */
    long parts;                 /* default parts for the race */
    HOMETOWN *hometown;         /* race's hometown, currently unused */
};

struct pc_race_type             /* additional data for pc races */
{
    char *name;                 /* MUST be in race_type */
    char who_name[11];
    sh_int points;              /* cost in points of the race */
    sh_int class_mult[MAX_CLASS];  /* exp multiplier for class, * 100 */
    char *skills[5];            /* bonus skills for the race */
    sh_int stats[MAX_STATS];    /* starting stats */
    sh_int max_stats[MAX_STATS];  /* maximum stats */
    sh_int size;                /* aff bits for the race */
};

/*
 * Data structure for notes.
 */
#define NOTE_NOTE       0
#define NOTE_KVETSH     1
#define NOTE_PENALTY    2
#define NOTE_IDEA       3
#define NOTE_CHANGES    4
#define NOTE_QWEST      5
#define NOTE_RPNOTE     6
#define NOTE_INOTE      7


struct note_data
{
    NOTE_DATA *next;
    bool valid;
    sh_int type;
    char *sender;
    char *date;
    char *to_list;
    char *subject;
    char *text;
    time_t date_stamp;
};

/*
 * An affect.
 */
struct affect_data
{
    AFFECT_DATA *next;
    CHAR_DATA *caster; /* added to track who cast the spell on the pc*/
	sh_int type;
    sh_int level;
    sh_int duration;
    sh_int location;
    sh_int modifier;
    int bitvector;
    int whichbitvector;  /* added by Lorn, 6/98 */
};

/* player stat code */
typedef struct stat_data STAT_DATA;


/* for statlist command*/
#define PK_KILLS         0
#define REBIRTHS         0
#define MOB_KILLS        1
#define PK_DEATHS        2
#define QUESTS_POINTSAUTO        2
#define MOB_DEATHS       3
#define QUESTS_COMPLETE  4
#define QUESTS_FAIL      5
#define IMMORTAL_POINTS   6
#define PK_KILLS		 7
#define PK_DEATHS	 8
#define SELF_DEATHS	 9
#define ARENA_KILLS	 10
#define ARENA_DEATHS	 11
#define GQUESTS_DONE	12
#define MAX_GAMESTAT     13
//add change more here

struct stat_data {
    STAT_DATA *next;
    bool valid;
    char *name;                     // name of character
    long gamestat[MAX_GAMESTAT];    // stat data
};

extern long TopGameStat[MAX_GAMESTAT];  // keeps track of the highest stats.


#define STAT_FILE       "statlist.dat"
/* end player stat code */

/*
 * A kill structure (indexed by level).
 */
struct kill_data
{
    sh_int number;
    sh_int killed;
};

#define EQ_LEVEL_OFFSET         +15

/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (Start of section ... start here)                     *
 *                                                                         *
 ***************************************************************************/

/*
 * Well known mob virtual numbers.
 * Defined in #MOBILES.
 */
#define MOB_VNUM_FIDO              15021
#define MOB_VNUM_CITYGUARD         15019
#define MOB_VNUM_VAMPIRE           3404
#define MOB_VNUM_LAWYER            1208    /* Moses for a placeholder */
#define MOB_VNUM_REGISTAR			15025
//Joe:Lockers	These defines locker object and room vnums
#define	LOCKER_VNUM		13004
#define	LOCKER_ROOM		15114	//Set this to your temple pit or whatever

/* RT ASCII conversions -- used so we can have letters in this file */

#define A                       1
#define B                       2
#define C                       4
#define D                       8
#define E                       16
#define F                       32
#define G                       64
#define H                       128

#define I                       256
#define J                       512
#define K                       1024
#define L                       2048
#define M                       4096
#define N                       8192
#define O                       16384
#define P                       32768

#define Q                       65536
#define R                       131072
#define S                       262144
#define T                       524288
#define U                       1048576
#define V                       2097152
#define W                       4194304
#define X                       8388608

#define Y                       16777216
#define Z                       33554432
#define aa                      67108864  /* doubled due to conflicts */
#define bb                      134217728
#define cc                      268435456
#define dd                      536870912
#define ee                      1073741824
#define ff                      2147483648
/*#define gg                      4294967296 */

/*
 * ACT bits for mobs.
 * Used in #MOBILES.
 */
#define ACT_IS_NPC              (A)  /* Auto set for mobs    */
#define ACT_SENTINEL            (B)  /* Stays in one room    */
#define ACT_SCAVENGER           (C)  /* Picks up objects     */
#define ACT_USE_NEW_AC          (D)
#define ACT_WIZI                (E)
#define ACT_AGGRESSIVE          (F)  /* Attacks PC's         */
#define ACT_STAY_AREA           (G)  /* Won't leave area     */
#define ACT_WIMPY               (H)
#define ACT_PET                 (I)  /* Auto set for pets    */
#define ACT_TRAIN               (J)  /* Can train PC's       */
#define ACT_PRACTICE            (K)  /* Can practice PC's    */
#define ACT_CHAMPION            (L)  /* overrides warrior and thief */
#define ACT_SORCEROR            (M)  /* powerful damage spells */
#define ACT_NASTY               (N)
#define ACT_UNDEAD              (O)
#define ACT_CLERIC              (Q)
#define ACT_MAGE                (R)
#define ACT_THIEF               (S)  
#define ACT_WARRIOR             (T)  /* overrides thief */
#define ACT_NOALIGN             (U)
#define ACT_NOALIGN             (U)
#define ACT_NOPURGE             (V)
#define ACT_DEST                (W)  /* destinations for ride command */
#define ACT_IS_HEALER           (aa)
#define ACT_GAIN                (bb)
#define ACT_UPDATE_ALWAYS       (cc)
#define ACT_TEMPORARY_MOB       (dd)
#define ACT_IS_AUCTIONEER       (ee)
#define ACT_NOQUEST	        (ff)


/* damage classes */
#define DAM_NONE                0
#define DAM_BASH                1
#define DAM_PIERCE              2
#define DAM_SLASH               3
#define DAM_FIRE                4
#define DAM_COLD                5
#define DAM_LIGHTNING           6
#define DAM_ACID                7
#define DAM_POISON              8
#define DAM_NEGATIVE            9
#define DAM_HOLY                10
#define DAM_ENERGY              11
#define DAM_MENTAL              12
#define DAM_DISEASE             13
#define DAM_DROWNING            14
#define DAM_LIGHT               15
#define DAM_OTHER               16  /* should not exist */
#define DAM_HARM                17  /* should not exist */
#define DAM_MAGIC               18  /* should not exist */
#define DAM_SOUND               19

/* OFF bits for mobiles */
#define OFF_AREA_ATTACK         (A)
#define OFF_CIRCLE              (B)   /* requires dagger wielded */
#define OFF_BASH                (C)
#define OFF_BERSERK             (D)
#define OFF_DISARM              (E)
#define OFF_DODGE               (F)   /* improves dodge chance */
#define OFF_FADE                (G)   /* being phased out, use affect flag */
#define OFF_FAST                (H)
#define OFF_KICK                (I)
#define OFF_KICK_DIRT           (J)
#define OFF_PARRY               (K)   /* improves parry chance */
#define OFF_RESCUE              (L)   /* not implemented */
/* M formerly tail, use part flag to do tail now */
                            /*  (M)  */
#define OFF_TRIP                (N)
#define OFF_CRUSH               (O)
#define OFF_CHARGE              (V)   /* not implemented */
#define OFF_SWEEP               (W)
#define ASSIST_ALL              (P)
#define ASSIST_ALIGN            (Q)
#define ASSIST_RACE             (R)
#define ASSIST_PLAYERS          (S)
#define ASSIST_GUARD            (T)
#define ASSIST_VNUM             (U)

/* return values for check_imm */
#define IS_NORMAL               0
#define IS_IMMUNE               1
#define IS_RESISTANT            2
#define IS_VULNERABLE           3

/* IMM bits for mobs */
#define IMM_SUMMON              (A)
#define IMM_CHARM               (B)
#define IMM_MAGIC               (C)
#define IMM_WEAPON              (D)
#define IMM_BASH                (E)
#define IMM_PIERCE              (F)
#define IMM_SLASH               (G)
#define IMM_FIRE                (H)
#define IMM_COLD                (I)
#define IMM_LIGHTNING           (J)
#define IMM_ACID                (K)
#define IMM_POISON              (L)
#define IMM_NEGATIVE            (M)
#define IMM_HOLY                (N)
#define IMM_ENERGY              (O)
#define IMM_MENTAL              (P)
#define IMM_DISEASE             (Q)
#define IMM_DROWNING            (R)
#define IMM_LIGHT               (S)
#define IMM_SOUND               (T)

/* RES bits for mobs */
#define RES_CHARM               (B)
#define RES_MAGIC               (C)
#define RES_WEAPON              (D)
#define RES_BASH                (E)
#define RES_PIERCE              (F)
#define RES_SLASH               (G)
#define RES_FIRE                (H)
#define RES_COLD                (I)
#define RES_LIGHTNING           (J)
#define RES_ACID                (K)
#define RES_POISON              (L)
#define RES_NEGATIVE            (M)
#define RES_HOLY                (N)
#define RES_ENERGY              (O)
#define RES_MENTAL              (P)
#define RES_DISEASE             (Q)
#define RES_DROWNING            (R)
#define RES_LIGHT               (S)
#define RES_SOUND               (T)

/* VULN bits for mobs */
#define VULN_MAGIC              (C)
#define VULN_WEAPON             (D)
#define VULN_BASH               (E)
#define VULN_PIERCE             (F)
#define VULN_SLASH              (G)
#define VULN_FIRE               (H)
#define VULN_COLD               (I)
#define VULN_LIGHTNING          (J)
#define VULN_ACID               (K)
#define VULN_POISON             (L)
#define VULN_NEGATIVE           (M)
#define VULN_HOLY               (N)
#define VULN_ENERGY             (O)
#define VULN_MENTAL             (P)
#define VULN_DISEASE            (Q)
#define VULN_DROWNING           (R)
#define VULN_LIGHT              (S)
#define VULN_SOUND              (T)
#define VULN_WOOD               (X)
#define VULN_SILVER             (Y)
#define VULN_IRON               (Z)

/* body form */
#define FORM_EDIBLE             (A)
#define FORM_POISON             (B)
#define FORM_MAGICAL            (C)
#define FORM_INSTANT_DECAY      (D)
#define FORM_OTHER              (E)  /* defined by material bit */

/* actual form */
#define FORM_ANIMAL             (G)
#define FORM_SENTIENT           (H)
#define FORM_UNDEAD             (I)
#define FORM_CONSTRUCT          (J)
#define FORM_MIST               (K)
#define FORM_INTANGIBLE         (L)

#define FORM_BIPED              (M)
#define FORM_CENTAUR            (N)
#define FORM_INSECT             (O)
#define FORM_SPIDER             (P)
#define FORM_CRUSTACEAN         (Q)
#define FORM_WORM               (R)
#define FORM_BLOB               (S)

#define FORM_MAMMAL             (V)
#define FORM_BIRD               (W)
#define FORM_REPTILE            (X)
#define FORM_SNAKE              (Y)
#define FORM_DRAGON             (Z)
#define FORM_AMPHIBIAN          (aa)
#define FORM_FISH               (bb)
#define FORM_COLD_BLOOD         (cc)

/* body parts */
#define PART_HEAD               (A)
#define PART_ARMS               (B)
#define PART_LEGS               (C)
#define PART_HEART              (D)
#define PART_BRAINS             (E)
#define PART_GUTS               (F)
#define PART_HANDS              (G)
#define PART_FEET               (H)
#define PART_FINGERS            (I)
#define PART_EAR                (J)
#define PART_EYE                (K)
#define PART_LONG_TONGUE        (L)
#define PART_EYESTALKS          (M)
#define PART_TENTACLES          (N)
#define PART_FINS               (O)
#define PART_WINGS              (P)
#define PART_TAIL               (Q)
/* for combat */
#define PART_CLAWS              (U)
#define PART_FANGS              (V)
#define PART_HORNS              (W)
#define PART_SCALES             (X)
#define PART_TUSKS              (Y)

/*
 * Bits for 'affected_by'.
 * Used in #MOBILES.
 */
#define AFF_BLIND               (A)
#define AFF_INVISIBLE           (B)
#define AFF_DETECT_EVIL         (C)
#define AFF_DETECT_INVIS        (D)
#define AFF_DETECT_MAGIC        (E)
#define AFF_DETECT_HIDDEN       (F)
#define AFF_SUPER_SANC          (G)  /* Changed from hold to this */
#define AFF_SANCTUARY           (H)

#define AFF_FAERIE_FIRE         (I)
#define AFF_INFRARED            (J)
#define AFF_CURSE               (K)
#define AFF_WEAPON_MASTER       (L)
#define AFF_POISON              (M)
#define AFF_PROTECT             (N)
#define AFF_FADE                (O)
#define AFF_SNEAK               (P)

#define AFF_HIDE                (Q)
#define AFF_SLEEP               (R)
#define AFF_CHARM               (S)
#define AFF_FLYING              (T)
#define AFF_PASS_DOOR           (U)
#define AFF_HASTE               (V)
#define AFF_CALM                (W)
#define AFF_PLAGUE              (X)
/* #define AFF_WEAKEN              (Y)  */
#define AFF_SANCTIFY            (Y)
/* The difference between aff and aff2 is that aff can be assigned 
   permanently to mobs.  This allows safe mobs */
#define AFF_DARK_VISION         (Z)
#define AFF_BERSERK             (aa)
#define AFF_HOLD                (bb)
#define AFF_REGENERATION        (cc)
#define AFF_DETECT_GOOD         (dd)
#define AFF_SLOW                (ee)
#define AFF_DICED               (ff)

/* bits for Affect2
   affected2_by     */
#define AFF2_BLUR               (A)
#define AFF2_ENDURE             (B)
/* #define AFF2_SANCTIFY           (C) */
#define AFF2_BLACK_PLAGUE       (C)
/* sanctify originally created here, but moved to first affect vector 
   to make safe mobs */
#define AFF2_CAMO               (D)
#define AFF2_MEDITATE           (E)
#define AFF2_CELERITY           (F)
#define AFF2_DEADLY_AURA        (G)
#define AFF2_REDIRECT           (H)
#define AFF2_TRUE_SIGHT         (I)
#define AFF2_AMNESIA            (J)
#define AFF2_GUILT              (K)
#define AFF2_ENGULF             (L)
#define AFF2_NO_TRACK		(M)
#define AFF2_BUBBLE             (N)
#define AFF2_SWIM		(O)
#define AFF2_FORTITUDE		(P)
#define AFF2_RESTORATION_WAIT	(Q)
#define AFF2_PURPOSE		(R)
#define AFF2_CONCENTRATE        (S)
#define AFF2_HEALING_AURA       (T)
#define AFF2_ENERGY_SHIELD      (U)
#define AFF2_BLOOD_STRIKE       (V)



/* Added by Coy.  When applies are added to objects it must be applied to a bit vector
 * just like if it were added to a player. So, unless we create separate bit vectors
 * for players and weapons (which is slightly redundant, but more efficnent in the
 * long run I guess), both players and weapons have to use the same aff(2) flags. A 
 * special flag is needed here so the weapon does nothing (as far as the actual aff
 * location) to the player when the item is worn.  Example: I tested putting the affect
 * H onto bit vector 1 (Sanctuary), and when the item was worn, the player recieved a
 * free sanct for the duration of the affect on the object.  Not what we want I don't
 * think.
 */
#define AFF2_SHARPEN		(W)
#define AFF2_DECOY		(X)
#define AFF2_CAMP	        (Y)
#define AFF2_WALLOFFORCE        (Z)
#define AFF2_ALLURE             (aa)
#define AFF2_SAFETY_HEAL        (bb)
#define AFF2_STUN               (cc)
#define AFF2_LIGHT_HEAL         (dd)
#define AFF2_HEAVY_HEAL         (ee)
/* bitvectors to apply affects too */
#define AFF1_VECTOR              1
#define AFF2_VECTOR              2
#define AFF_RESIST_VECTOR        3
#define AFF_VULN_VECTOR          4
#define AFF_IMMUNE_VECTOR        5

/* Races for use in code (numbering is dependent on how the races are
 * organized in race.dat - Coy 6/01
 *
 * !!! WARNING, IF THE RACES ARE REORGANIZED IN RACE.DAT, THESE NUMBERS MUST BE
 * !!! MODIFIED OR THINGS MAY NOT WORK CORRECTLY!!!
 */
#define RACE_HUMAN		1
#define RACE_ELF		2
#define RACE_DWARF		3
#define RACE_GIANT		4
#define RACE_DRAGON		5
#define RACE_VAMPIRE	6
#define RACE_FELINE		7
#define RACE_GARGOYLE	8
#define RACE_CARTOON	9
#define RACE_FAIRY		10
#define RACE_SATYR		11
#define RACE_WOLF		12
#define RACE_DROW		13
#define RACE_DRYAD		14
#define RACE_GOBLIN		15
#define RACE_MINOTAUR	16
#define RACE_GHOST		17
#define RACE_BEAR		18
#define RACE_ORC		19
#define RACE_CENTAUR	20
#define RACE_GNOME		21
#define RACE_TITAN		22
#define RACE_MOOGLE             23
#define RACE_HALFLING	24

/* Arbitrary numbering of affects for use in mobprog "isaff" - Coy 8/01 */
#define MP_BLIND               1
#define MP_INVISIBLE           2
#define MP_DETECT_EVIL         3
#define MP_DETECT_INVIS        4
#define MP_DETECT_MAGIC        5
#define MP_DETECT_HIDDEN       6
#define MP_SUPER_SANC          7
#define MP_SANCTUARY           8
#define MP_FAERIE_FIRE         9
#define MP_INFRARED            10
#define MP_CURSE               11
#define MP_WEAPON_MASTER       12
#define MP_POISON              13
#define MP_PROTECT             14
#define MP_FADE                15
#define MP_SNEAK               16
#define MP_HIDE                17
#define MP_SLEEP               18
#define MP_CHARM               19
#define MP_FLYING              20
#define MP_PASS_DOOR           21
#define MP_HASTE               22
#define MP_CALM                23
#define MP_PLAGUE              24
#define MP_SANCTIFY            25
#define MP_DARK_VISION         26
#define MP_BERSERK             27
#define MP_HOLD                28
#define MP_REGENERATION        29
#define MP_DETECT_GOOD         30
#define MP_SLOW                31
#define MP_CAMP				   32
#define MP_VECT2_START       33 /* AFF2 starts here */               
#define MP_BLUR                33
#define MP_ENDURE              34
#define MP_BLACK_PLAGUE        35
#define MP_CAMO                36 
#define MP_MEDITATE            37
#define MP_CELERITY            38
#define MP_DEADLY_AURA         39
#define MP_REDIRECT            40
#define MP_TRUE_SIGHT          41
#define MP_AMNESIA             42
#define MP_GUILT               43
#define MP_ENGULF              44
#define MP_NO_TRACK            45
#define MP_BUBBLE              46
#define MP_SWIM                47
#define MP_FORTITUDE           48
#define MP_PURPOSE             49
#define MP_CONCENTRATE         50
#define MP_HEALING_AURA        51
#define MP_ENERGY_SHIELD       52
#define MP_BLOOD_STRIKE        53
#define MP_DECOY               54
#define MP_ALLURE              55
/*
 * Sex.
 * Used in #MOBILES.
 */
#define SEX_NEUTRAL                   0
#define SEX_MALE                      1
#define SEX_FEMALE                    2

/* AC types */
#define AC_PIERCE                       0
#define AC_BASH                         1
#define AC_SLASH                        2
#define AC_EXOTIC                       3

/* dice */
#define DICE_NUMBER                     0
#define DICE_TYPE                       1
#define DICE_BONUS                      2

/* size */
#define SIZE_TINY                       0
#define SIZE_SMALL                      1
#define SIZE_MEDIUM                     2
#define SIZE_LARGE                      3
#define SIZE_GIANT                      4    /* HUGE used to be 4 */
#define SIZE_HUGE                       5    /* and GIANT used to be 5 */
                                             /* but giants are size 4, so this */
                                             /* actually makes sense */ 
/*
 * Well known object virtual numbers.
 * Defined in #OBJECTS.
 */
#define OBJ_VNUM_MONEY_ONE            2
#define OBJ_VNUM_MONEY_SOME           3
#define OBJ_VNUM_BERRIES              4
#define OBJ_VNUM_HERB_HEAL            5
#define OBJ_VNUM_HERB_POISON          6
#define OBJ_VNUM_HERB_DISEASE         7

#define OBJ_VNUM_CORPSE_NPC          10
#define OBJ_VNUM_CORPSE_PC           11
#define OBJ_VNUM_SEVERED_HEAD        12
#define OBJ_VNUM_TORN_HEART          13
#define OBJ_VNUM_SLICED_ARM          14
#define OBJ_VNUM_SLICED_LEG          15
#define OBJ_VNUM_GUTS                16
#define OBJ_VNUM_BRAINS              17

#define OBJ_VNUM_SPICES				  9 /* for preserve */
#define OBJ_VNUM_STEAK				 39 /* for preserve */
#define OBJ_VNUM_FLINT				  8	
#define OBJ_VNUM_MUSHROOM            20
#define OBJ_VNUM_LIGHT_BALL          21
#define OBJ_VNUM_SPRING              22
#define OBJ_VNUM_MUDPIE              23
#define OBJ_VNUM_ACIDPIE             24
#define OBJ_VNUM_JOKEBOOK            25
#define OBJ_VNUM_PORTAL              26
#define OBJ_VNUM_ROSE                44
#define OBJ_VNUM_WARPSTONE           27
#define OBJ_VNUM_PIT               3010
#define OBJ_VNUM_PIPE				 43
#define OBJ_CREATE_MED_POT_1		 44
#define OBJ_CREATE_MED_POT_2		 45
#define OBJ_CREATE_MED_POT_3		 46
#define OBJ_CREATE_MED_POT_4		 47
#define OBJ_CREATE_MED_POT_5		 48
#define OBJ_VNUM_SCHOOL_MACE       3703
#define OBJ_VNUM_SCHOOL_DAGGER     3702
#define OBJ_VNUM_SCHOOL_SWORD      3701
#define OBJ_VNUM_SCHOOL_VEST       3704
#define OBJ_VNUM_SCHOOL_SHIELD     3705
#define OBJ_VNUM_SCHOOL_BANNER     3707
#define OBJ_VNUM_SCHOOL_WHIP       3718
#define OBJ_VNUM_SCHOOL_POLEARM    3719
#define OBJ_VNUM_MAP               15145
#define OBJ_VNUM_REBIRTH1          7960
#define OBJ_VNUM_REBIRTH2          7961
#define OBJ_VNUM_REBIRTH3          7962
#define OBJ_VNUM_REBIRTH4          7963
#define OBJ_VNUM_REBIRTH5          7964
#define OBJ_VNUM_REBIRTH6          7965
#define OBJ_VNUM_REBIRTH7          7966
/*reawake items*/
#define OBJ_VNUM_REAWAKE1	   7960 /*reawake items needed will need to be changed*/
#define OBJ_VNUM_REAWAKE2	   7961
#define OBJ_VNUM_REAWAKE3	   7962
#define OBJ_VNUM_REAWAKE4	   7963
#define OBJ_VNUM_REAWAKE5	   7964
#define OBJ_VNUM_REAWAKE6	   7965
#define OBJ_VNUM_REAWAKE7	   7966
#define OBJ_VNUM_EVOLVE1           6567
#define OBJ_VNUM_EVOLVE2           6568
#define OBJ_VNUM_EVOLVE3           6569
#define OBJ_VNUM_EVOLVE4           6570
#define OBJ_VNUM_EVOLVE5           6571
#define OBJ_VNUM_EVOLVE6           6572
#define OBJ_VNUM_EVOLVE7           6573
/* vnums for items in remort area */
#define  OBJ_VNUM_TOKEN_WIZ      10760
#define  OBJ_VNUM_TOKEN_PRO      10761
#define  OBJ_VNUM_TOKEN_ROG      10762      
#define  OBJ_VNUM_TOKEN_CHA      10763
#define  OBJ_VNUM_TOKEN_SHO      10764
#define  OBJ_VNUM_TOKEN_TEM      10765
#define  OBJ_VNUM_TOKEN_ZEA      10766
#define  OBJ_VNUM_TOKEN_HUN      10767
/* vnums for items in remort2 area */
#define  OBJ_VNUM_TOKEN_SOR	 28239
#define  OBJ_VNUM_TOKEN_MYS	 13401
#define  OBJ_VNUM_TOKEN_NJA	 13402
#define  OBJ_VNUM_TOKEN_BAR	 13403
#define  OBJ_VNUM_TOKEN_RON	 13404
#define  OBJ_VNUM_TOKEN_PAL	 13405
#define  OBJ_VNUM_TOKEN_MMK	 13406
#define  OBJ_VNUM_TOKEN_STR	 13407

/* motorball vnums */
#define OBJ_VNUM_MOTORBALL      100
#define OBJ_VNUM_MOTORBALL1     101
#define OBJ_VNUM_MOTORBALL2     102
#define OBJ_VNUM_MOTORBALL3     103
#define OBJ_VNUM_MOTORBALL_TOKEN   108

/*
 * Item types.
 * Used in #OBJECTS.
 */
#define ITEM_LIGHT                    1
#define ITEM_SCROLL                   2
#define ITEM_WAND                     3
#define ITEM_STAFF                    4
#define ITEM_WEAPON                   5
#define ITEM_TREASURE                 8
#define ITEM_ARMOR                    9
#define ITEM_POTION                  10
#define ITEM_CLOTHING                11
#define ITEM_FURNITURE               12
#define ITEM_TRASH                   13
#define ITEM_CONTAINER               15
#define ITEM_DRINK_CON               17
#define ITEM_KEY                     18
#define ITEM_FOOD                    19
#define ITEM_MONEY                   20
#define ITEM_BOAT                    22
#define ITEM_CORPSE_NPC              23
#define ITEM_CORPSE_PC               24
#define ITEM_FOUNTAIN                25
#define ITEM_PILL                    26
#define ITEM_PROTECT                 27
#define ITEM_MAP                     28
#define ITEM_PORTAL                  29
#define ITEM_WARP_STONE              30
#define ITEM_GATE_CATALYST           31
#define ITEM_SMOKE_PIPE				 32
#define ITEM_SPICES					 33
#define ITEM_FLINT					 34
#define ITEM_TOME					 35
#define ITEM_SOCKETS				 36
/*
 * Extra flags.
 * Used in #OBJECTS.
 */
#define ITEM_GLOW               (A)
#define ITEM_HUM                (B)
#define ITEM_DARK               (C)
#define ITEM_LOCK               (D)
#define ITEM_EVIL               (E)
#define ITEM_INVIS              (F)
#define ITEM_MAGIC              (G)
#define ITEM_NODROP             (H)
#define ITEM_BLESS              (I)
#define ITEM_ANTI_GOOD          (J)
#define ITEM_ANTI_EVIL          (K)
#define ITEM_ANTI_NEUTRAL       (L)
#define ITEM_NOREMOVE           (M)
#define ITEM_INVENTORY          (N)  /* rots away when mob carrying it dies */
#define ITEM_NOPURGE            (O)
#define ITEM_ROT_DEATH          (P)  /* rots away shortly after mob carrying it dies */
#define ITEM_VIS_DEATH          (Q)  /* invisible until mob carrying it dies */
#define ITEM_GOOD               (R)
#define ITEM_NONMETAL           (S)  /* prevents heat metal -- good idea */
#define ITEM_BURN_PROOF         (T)  /* does nothing, do not use  9/30/98 */
#define ITEM_NO_LOCATE          (U)
#define ITEM_INDESTRUCTIBLE     (V)
#define ITEM_NO_IDENTIFY        (W)
#define ITEM_QUEST              (X)
#define ITEM_INLAY1				(Y)
#define ITEM_INLAY2				(Z)
#define ITEM_KEEP				(aa)
/*
 * Wear flags.
 * Used in #OBJECTS.
 */
#define ITEM_TAKE               (A)
#define ITEM_WEAR_FINGER        (B)
#define ITEM_WEAR_NECK          (C)
#define ITEM_WEAR_BODY          (D)
#define ITEM_WEAR_HEAD          (E)
#define ITEM_WEAR_LEGS          (F)
#define ITEM_WEAR_FEET          (G)
#define ITEM_WEAR_HANDS         (H)
#define ITEM_WEAR_ARMS          (I)
#define ITEM_WEAR_SHIELD        (J)
#define ITEM_WEAR_ABOUT         (K)
#define ITEM_WEAR_WAIST         (L)
#define ITEM_WEAR_WRIST         (M)
#define ITEM_WIELD              (N)
#define ITEM_HOLD               (O)
#define ITEM_TWO_HANDS          (P)
/* #define ITEM_WEAR_SECONDARY     (Q) */ /* not used, no idea for use */
#define ITEM_WEAR_EARS          (R)
#define ITEM_WEAR_ANKLE         (S)
#define ITEM_MEMBERS_ONLY       (T)
#define ITEM_WEAR_FLOAT         (U)
#define ITEM_WEAR_FACE		(V)

/* weapon class */
#define WEAPON_EXOTIC           0
#define WEAPON_SWORD            1
#define WEAPON_DAGGER           2
#define WEAPON_SPEAR            3
#define WEAPON_MACE             4
#define WEAPON_AXE              5
#define WEAPON_FLAIL            6
#define WEAPON_WHIP             7
#define WEAPON_POLEARM          8
#define WEAPON_BOW              9

/* weapon types */
#define WEAPON_FLAMING          (A)
#define WEAPON_FROST            (B)
#define WEAPON_VAMPIRIC         (C)
#define WEAPON_SHARP            (D)
#define WEAPON_VORPAL           (E)
#define WEAPON_TWO_HANDS        (F)

/* gate flags */
#define GATE_NORMAL_EXIT        (A)
#define GATE_NOCURSE            (B)
#define GATE_AUTO_REVERSE       (C)
#define GATE_BUGGY              (D)
#define GATE_RANDOM             (E)  /* these two mean the same */
#define GATE_RANDOM_AREA        (E)  /* these two mean the same */
#define GATE_RANDOM_CONT        (F)
#define GATE_RANDOM_WORLD       (G)
#define GATE_RANDOM_SPEC_AREA   (H)
#define GATE_QUEST              (I)

/* rebirth definitions */
#define NUM_CHAMBERS 8
#define NUM_RCHAMBERS 2    /* remort chambers */
#define NUM_R2CHAMBERS 2   /* remort2 chambers */
#define NO_ROOMS_PER_CHAMBER 8
#define NO_ROOMS_PER_RCHAMBER 167 /* don't know if this is needed */
#define NO_ROOMS_PER_R2CHAMBER 250 /* just in case it is needed */
#define NUM_RACHAMBERS 2

/* this constant is not in merc.h - but check_parse_name says
 * 8 for MSDOS and 12 for Mac and Unix */
#define MAX_CHAR_NAME 12

extern char TopScorer[MAX_GAMESTAT][MAX_CHAR_NAME];

#define LAST_COMMAND_FILE "last_command.txt"
#define REBIRTH_FILE "rebirth.dat"
#define REMORT_FILE "remort.dat"
#define REMORT2_FILE "remort2.dat"
#define REAWAKE_FILE "reawake.dat"
#define TEMP_REBIRTH_FILE "rebirth.bak"
#define TEMP_REMORT_FILE "remort.bak"
#define TEMP_REMORT2_FILE "remort2.bak"
#define TEMP_REAWAKE_FILE "reawake.bak"
#define REBIRTH_LOCK_FILE ".rebirth"
#define REMORT_LOCK_FILE ".remort"
#define REMORT2_LOCK_FILE ".remort2"
#define REAWAKE_LOCK_FILE ".reawake"
#define FREE_STRING "empty_and_free"

/*
 * Apply types (for affects).
 * Used in #OBJECTS.
 */
#define APPLY_NONE                    0
#define APPLY_STR                     1
#define APPLY_DEX                     2
#define APPLY_INT                     3
#define APPLY_WIS                     4
#define APPLY_CON                     5
#define APPLY_SEX                     6
#define APPLY_CLASS                   7
#define APPLY_LEVEL                   8
#define APPLY_AGE                     9
#define APPLY_HEIGHT                 10
#define APPLY_WEIGHT                 11
#define APPLY_MANA                   12
#define APPLY_HIT                    13
#define APPLY_MOVE                   14
#define APPLY_GOLD                   15
#define APPLY_EXP                    16
#define APPLY_AC                     17
#define APPLY_HITROLL                18
#define APPLY_DAMROLL                19
#define APPLY_SAVING_PARA            20
#define APPLY_SAVING_ROD             21
#define APPLY_SAVING_PETRI           22
#define APPLY_SAVING_BREATH          23
#define APPLY_SAVING_SPELL           24
#define APPLY_SPELL                  25  /* aka powerup */
#define APPLY_SPELL_AFFECT           30

/*  Spell definitions for eq affects */
#define SPELL_SUPER_SANC         1
#define SPELL_FADE               2                
#define SPELL_INVISIBLE          3
#define SPELL_SANCTUARY          4
#define SPELL_WEAPON_MASTER      5
#define SPELL_CURSE              6
#define SPELL_HASTE              7
#define SPELL_SLOW               8
#define SPELL_POISON             9
#define SPELL_PLAGUE             10
#define SPELL_BLIND              11
#define SPELL_DETECT_INVIS       12
#define SPELL_DETECT_HIDDEN      13
#define SPELL_PROTECT            14
#define SPELL_FLYING             15

/*arena*/
#define FIGHT_OPEN                    0
#define FIGHT_START                   1
#define FIGHT_BUSY                    2
#define FIGHT_LOCK                    3



/*
 * Values for containers (value[1]).
 * Used in #OBJECTS.
 */
#define CONT_CLOSEABLE                1
#define CONT_PICKPROOF                2
#define CONT_CLOSED                   4
#define CONT_LOCKED                   8

/*
  * Values for socketing items (value[0]).
  * Used in #OBJECTS.
  */
#define SOC_SAPPHIRE         1
#define SOC_RUBY             2
#define SOC_EMERALD          3
#define SOC_DIAMOND          4
#define SOC_TOPAZ            5
#define SOC_ONYX             6

  /*
   * Values for socketing items (value[1]).
   * used in #OBJECTS
   */
#define GEM_CHIPPED      2
#define GEM_FLAWED       4
#define GEM_FLAWLESS     6
#define GEM_PERFECT      10

/*
 * Well known room virtual numbers.
 * Defined in #ROOMS.
 */
#define ROOM_VNUM_LIMBO               2
#define ROOM_VNUM_QUESTMOB	   3
#define ROOM_VNUM_CHAT             3
#define ROOM_VNUM_TEMPLE           15013
#define ROOM_VNUM_ALTAR            15114
#define ROOM_VNUM_SCHOOL           3700
#define ROOM_VNUM_MORGE            15019
#define ROOM_VNUM_REBIRTH          7900
#define ROOM_VNUM_ARENA            50000
#define ROOM_VNUM_AWINNER	   50014
#define ROOM_VNUM_ALOSER	   50015
#define ROOM_VNUM_EVOLVE           6560
#define ROOM_VNUM_IMMORTAL         1210
#define ROOM_VNUM_DONATION1        15117       
#define ROOM_VNUM_DONATION2        15118
#define ROOM_VNUM_DONATION3        15119
#define ROOM_VNUM_DONATION4        15120
#define ROOM_VNUM_DONATION5        15121
#define ROOM_VNUM_ASATRU_ALT_RECALL			15207
#define ROOM_VNUM_NORNIR_ALT_RECALL			24157


/*
 * Room flags.
 * Used in #ROOMS.
 */
#define ROOM_DARK               (A)
#define ROOM_BANK               (B)
#define ROOM_NO_MOB             (C)
#define ROOM_INDOORS            (D)
#define ROOM_PURSER             (E)

#define ROOM_PRIVATE            (J)
#define ROOM_SAFE               (K)
#define ROOM_SOLITARY           (L)
#define ROOM_PET_SHOP           (M)
#define ROOM_NO_RECALL          (N)
#define ROOM_IMP_ONLY           (O)
#define ROOM_GODS_ONLY          (P)
#define ROOM_HEROES_ONLY        (Q)
#define ROOM_NEWBIES_ONLY       (R)
#define ROOM_LAW                (S)
#define ROOM_ARENA              (T)
#define ROOM_NO_TELEPORT        (U)
#define ROOM_UNDER_WATER        (V)
#define ROOM_OVERBOARD			(W)
#define ROOM_DIRTY				(X)
#define ROOM_NO_COMM			(Y)
#define ROOM_SLOT_PENNY				(aa)
#define ROOM_SLOT_NICKEL				(bb)
#define ROOM_SLOT_QUARTER			(cc)
#define ROOM_SLOT_DOLLAR				(dd)
#define ROOM_SLOT_HIGHROLLER			(ee)

/*
 * Directions.
 * Used in #ROOMS.
 */
#define DIR_NORTH                     0
#define DIR_EAST                      1
#define DIR_SOUTH                     2
#define DIR_WEST                      3
#define DIR_UP                        4
#define DIR_DOWN                      5

/*
 * Exit flags.
 * Used in #ROOMS.
 */
#define EX_ISDOOR                     (A)
#define EX_LOCKS                      (B)
#define EX_CLOSED                     (C)
#define EX_LOCKED                     (D)
#define EX_NOPASS                     (E)
#define EX_PICKPROOF                  (F)

/* values changed by Lorn, Feb 1999 from below */
/*
#define EX_ISDOOR                     (A)
#define EX_CLOSED                     (B)
#define EX_LOCKED                     (C)
#define EX_PICKPROOF                  (F)
#define EX_NOPASS                     (E)
*/

/*
 * Sector types.
 * Used in #ROOMS.
 */
#define SECT_INSIDE                   0
#define SECT_CITY                     1
#define SECT_FIELD                    2
#define SECT_FOREST                   3
#define SECT_HILLS                    4
#define SECT_MOUNTAIN                 5
#define SECT_WATER_SWIM               6
#define SECT_WATER_NOSWIM             7
#define SECT_SNOW                     8
#define SECT_AIR                      9
#define SECT_DESERT                  10
#define SECT_ICE                     11
#define SECT_MOUNTAIN_SNOW           12
#define SECT_MAX                     13

/*
 * Equpiment wear locations.
 * Used in #RESETS.
 */
#define WEAR_NONE                    -1
#define WEAR_LIGHT                    0
#define WEAR_FINGER_L                 1
#define WEAR_FINGER_R                 2
#define WEAR_NECK_1                   3
#define WEAR_NECK_2                   4
#define WEAR_BODY                     5
#define WEAR_HEAD                     6
#define WEAR_LEGS                     7
#define WEAR_FEET                     8
#define WEAR_HANDS                    9
#define WEAR_ARMS                    10
#define WEAR_SHIELD                  11
#define WEAR_ABOUT                   12
#define WEAR_WAIST                   13
#define WEAR_WRIST_L                 14
#define WEAR_WRIST_R                 15
#define WEAR_WIELD                   16
#define WEAR_HOLD                    17
#define WEAR_SECONDARY               18
/* added by Rizuli */
#define WEAR_EARS                    19
#define WEAR_ANKLE_L                 20
#define WEAR_ANKLE_R                 21
/* end Rizuli      */
/* added by Sankin */
#define WEAR_FLOAT                   22
#define WEAR_FACE		     23
/* end Sankin addition */
#define MAX_WEAR                     24

/***************************************************************************
 *                                                                         *
 *                   VALUES OF INTEREST TO AREA BUILDERS                   *
 *                   (End of this section ... stop here)                   *
 *                                                                         *
 ***************************************************************************/

/*
 * Conditions.
 */
#define COND_DRUNK                    0
#define COND_FULL                     1
#define COND_THIRST                   2

/*
 * Positions.
 */
#define POS_DEAD                      0
#define POS_MORTAL                    1
#define POS_INCAP                     2
#define POS_STUNNED                   3
#define POS_SLEEPING                  4
#define POS_RESTING                   5
#define POS_SITTING                   6
#define POS_FIGHTING                  7
#define POS_STANDING                  8

/*
 * ACT bits for players.
 */
#define PLR_IS_NPC              (A)  /* Don't EVER set.      */
#define PLR_BOUGHT_PET          (B)

/* RT auto flags */
#define PLR_AUTOASSIST          (C)
#define PLR_AUTOEXIT            (D)
#define PLR_AUTOLOOT            (E)
#define PLR_AUTOSAC             (F)
#define PLR_AUTOGOLD            (G)
#define PLR_AUTOSPLIT           (H)
/* 5 bits reserved, I-M */  /* what in hell for?  --Lorn.....They are reserved because if you want to and RT auto flags you need these bits, if you use a bit later it pops up errors. --Galius */
#define PLR_ADDICT              (I)
#define PLR_HPBAR				(J)
#define PLR_HPBAR2              (K)
#define PLR_AUTOTRIVIA			(L)
#define PLR2_NO_EXP				(M)
/* RT personal flags */
#define PLR_HOLYLIGHT           (N)
#define PLR_WIZINVIS            (O)
#define PLR_CANLOOT             (P)
#define PLR_NOSUMMON            (Q)
#define PLR_NOFOLLOW            (R)
#define PLR_NOGATE              (S)  /* added by Rizuli */
#define PLR_COLOR               (T)  /* Color Flag By Lope */
/* 4 bits reserved, S-V */  /* what in hell for?  --Lorn */
/* penalty flags */
#define PLR_GQUEST				(U)
#define PLR_LOG                 (W)
#define PLR_DENY                (X)
#define PLR_FREEZE              (Y)
#define PLR_THIEF               (Z)
#define PLR_KILLER              (aa)
/* consent for marriage flag */
#define PLR_SERVE               (bb)
#define PLR_ISMARRIED           (cc)
#define PLR2_CHALLENGER	        (dd)
#define PLR2_CHALLENGED         (ee)
#define PLR_QUESTOR		(ff)


#define CLASS_MAG  0
#define CLASS_CLE  1
#define CLASS_THI  2
#define CLASS_WAR  3
#define CLASS_SAM  4
#define CLASS_CRU  5
#define CLASS_MON  6
#define CLASS_RAN  7
#define CLASS_WIZ  8
#define CLASS_PRO  9
#define CLASS_ROG  10
#define CLASS_CHA  11
#define CLASS_SHO  12
#define CLASS_TEM  13
#define CLASS_ZEA  14
#define CLASS_HUN  15
#define CLASS_SOR  16
#define CLASS_MYS  17
#define CLASS_NJA  18
#define CLASS_BAR  19
#define CLASS_RON  20
#define CLASS_PAL  21
#define CLASS_MMK  22
#define CLASS_STR  23


/* RT comm flags -- may be used on both mobs and chars */
#define COMM_QUIET              (A)
#define COMM_DEAF               (B)
#define COMM_NOWIZ              (C)
#define COMM_NOAUCTION          (D)
#define COMM_NOOOC              (E)
#define COMM_NOIC               (F)
#define COMM_NOQUEST            (G)
#define COMM_INFO               (H)
#define COMM_CLAN               (I)
#define COMM_NOGRATZ            (J)
#define COMM_NOIG               (K)
#define COMM_PRAY               (Y)
#define COMM_NOMIST             (Q)
#define COMM_NEWBIE             (S)
#define COMM_TRIBE				(dd)

extern int newbie_count;
extern char *newbie_table[MAX_NEWBIES];

/* display flags */
#define COMM_COMPACT            (L)
#define COMM_BRIEF              (M)
#define COMM_PROMPT             (N)
#define COMM_COMBINE            (O)
#define COMM_TELNET_GA          (ff)
#define COMM_AC_TEST            (P)
#define COMM_SAVE_TEST          (ee)
#define COMM_DAM_TEST           (R)
/* 3 flags reserved, Q-S     : This comment makes no sense.  6/98 */

/* penalties */
#define COMM_NOEMOTE            (T)
#define COMM_NOMUSIC            (U)
#define COMM_NOTELL             (V)
#define COMM_NOCHANNELS         (W)
#define COMM_NONOTE             (X)
#define COMM_NOPRAY             (Z)
#define COMM_AFK                (aa)
#define COMM_TELLS              (bb)
#define COMM_PUNISH             (cc)
#define COMM_WALL               (ee)


/* Object and room progs - Coy 12/02
 *
 * Object and room prog definitions
 */                   
/*
 * MOBprog definitions
 */                   
#define TRIG_ACT	(A)
#define TRIG_BRIBE	(B)
#define TRIG_DEATH	(C)
#define TRIG_ENTRY	(D)
#define TRIG_FIGHT	(E)
#define TRIG_GIVE	(F)
#define TRIG_GREET	(G)
#define TRIG_GRALL	(H)
#define TRIG_KILL	(I)
#define TRIG_HPCNT	(J)
#define TRIG_RANDOM	(K)
#define TRIG_SPEECH	(L)
#define TRIG_EXIT	(M)
#define TRIG_EXALL	(N)
#define TRIG_DELAY	(O)
#define TRIG_SURR	(P)
#define TRIG_GET        (Q)
#define TRIG_DROP	(R)
#define TRIG_SIT	(S)
#define TRIG_ALIAS	(T)

/*
 * Prog types
 */
#define PRG_MPROG	0
#define PRG_OPROG	1
#define PRG_RPROG	2

struct prog_list
{
    int                 trig_type;
    char *              trig_phrase;
    sh_int              vnum;
    char *              code;
    PROG_LIST *         next;
    bool                valid;
	int					chance;
};

struct prog_code
{
    sh_int              vnum;
    char *              code;
    PROG_CODE *         next;
};

struct flag_type
{
    char * name;
    int  bit;
    bool settable;
};

struct position_type
{
    char *name;
    char *short_name;
};


struct item_type
{
    int		type;
    char *	name;
};

// End of prog stuff

struct mem_data
{
    MEM_DATA *next;
    bool valid;
    int id;
    int reaction;
    time_t when;
};

//Added for Global Quests - Galius 4/16/2013
#define		GQUEST_OFF              0
#define		GQUEST_WAITING		1
#define		GQUEST_RUNNING		2

struct gquest_data
{
    int mobs[MAX_GQUEST_MOB];
    char *who;
    int mob_count;
    int timer;
    int involved;
    int qpoints;
    int gold;
    int minlevel;
    int maxlevel;
    int running;
    int next;
};

/*
 * Prototype for a mob.
 * This is the in-memory version of #MOBILES.
 */
struct mob_index_data
{
    MOB_INDEX_DATA *next;
    SPEC_FUN *spec_fun;
    SHOP_DATA *pShop;
    sh_int vnum;
    bool new_format;
    sh_int count;
    sh_int killed;
    char *player_name;
    char *short_descr;
    char *long_descr;
    char *description;
    long act;
    long affected_by;
	long affected2_by;
    sh_int alignment;
    sh_int level;
    sh_int hitroll;
    sh_int hit[3];
    sh_int mana[3];
    sh_int damage[3];
    sh_int ac[4];
    sh_int dam_type;
    long off_flags;
    long imm_flags;
    long res_flags;
    long vuln_flags;
    RANDOMIZER_DATA *random_irv;
    sh_int start_pos;
    sh_int default_pos;
    sh_int sex;
    sh_int race;
    long gold;
    long form;
    long parts;
    sh_int size;
    sh_int material;
    MPROG_DATA *mobprogs;
	PROG_LIST *mprogs;
	long                mprog_flags;
    int progtypes;
	 AREA_DATA *		area;		/* OLC */
};

struct randomizer_data
{
    char type;
    int target;
    int arg1;         /* locked immune */
    int arg2;         /* min extra immune */
    int arg3;         /* max extra immune */
    int arg4;         /* locked resist */
    int arg5;         /* min extra resist */
    int arg6;         /* max extra resist */
    int arg7;         /* locked vuln */
    int arg8;         /* min extra vuln */
    int arg9;         /* max extra vuln */
    int arg10;        /* locked normal */
};

struct auction_data
{
    AUCTION_DATA *next;
    OBJ_DATA *item;
    CHAR_DATA *owner;
    CHAR_DATA *high_bidder;
    sh_int status;
    long current_bid;
    long gold_held;
    long min_bid;
    bool valid;
};

struct follow_type {
   CHAR_DATA *follower;
   struct FOLLOW_TYPE *next;
};

/*
 * One character (PC or NPC).
 */
struct char_data
{
    CHAR_DATA *next;
    CHAR_DATA *challenger;
    CHAR_DATA *challenged;
    CHAR_DATA *gladiator; /*person bet on*/
    CHAR_DATA *next_in_room;
    CHAR_DATA *master;
    CHAR_DATA *leader;
    CHAR_DATA *fighting;
    CHAR_DATA *reply;
    CHAR_DATA *pet;
    CHAR_DATA *mount;
    SPEC_FUN *spec_fun;
    CHAR_DATA *questgiver; /* Vassago */
    MOB_INDEX_DATA *pIndexData;
    DESCRIPTOR_DATA *desc;
    AFFECT_DATA *affected;
    NOTE_DATA *pnote;
    OBJ_DATA *carrying;
    ROOM_INDEX_DATA *in_room;
    ROOM_INDEX_DATA *was_in_room;
    PC_DATA *pcdata;
    GEN_DATA *gen_data;
    char *name;
    sh_int version;
    char *short_descr;
    char *long_descr;
    char *description;
    char *decoy;
    char *prompt;
    char *color_scheme;
    sh_int sex;
	int owherestate;
    sh_int pet_count;
    sh_int class;
    sh_int race;
    sh_int level;
    sh_int              countdown; /* Vassago */
    sh_int              questobj; /* Vassago */
    sh_int              questmob; /* Vassago */
	long				cooldowns[MAX_SKILL];//skill cooldowns
/*    sh_int stance; */
    sh_int trust;
    sh_int tv;                  /* Rizuli */
    int played;
    int lines;                  /* for the pager */
    time_t logon;
    sh_int timer;
    sh_int wait;
    sh_int hit;
    sh_int max_hit;
    sh_int mana;
    sh_int max_mana;
    sh_int move;
    sh_int max_move;
    long gold;
    int exp;
    long act;
    long comm;                  /* RT added to pad the vector */
    long wiznet;                /* wiz stuff */
    long imm_flags;
    long res_flags;
    long vuln_flags;
    sh_int invis_level;
    sh_int incognito_level;
    int affected_by;
    int affected2_by;           /* added by Lorn, 6/98 */
    sh_int position;
    sh_int practice;
    sh_int train;
    sh_int carry_weight;
    sh_int carry_number;
    sh_int saving_throw;
    sh_int save_spell;
    sh_int save_rod;
    sh_int save_para;
    sh_int save_breath;
    sh_int save_petri;
    sh_int power_spell;
    sh_int alignment;
    sh_int hitroll;
    sh_int damroll;
    sh_int armor[4];
    sh_int wimpy;
    int ride_to[2];
    /* stats */
    sh_int perm_stat[MAX_STATS];
    sh_int mod_stat[MAX_STATS];
    /* parts stuff */
    long form;
    long parts;
    sh_int size;
    sh_int material;
    /* mobile stuff */
    long off_flags;
    sh_int damage[3];
    sh_int dam_type;
    sh_int start_pos;
    sh_int default_pos;
    /* MOBProgam stuff */
    MPROG_ACT_LIST *mpact;
	CHAR_DATA *         mprog_target;
	sh_int              mprog_delay;
    int mpactnum;
    long in_bank;
    /* added for marriage code */
    sh_int plr_consent;
    sh_int plr_ismarried;

    sh_int singing;                 // Is the song being sung or not 0 = no, 1 = yes.
    sh_int sing_sn;                 // The sn of the song (actual, meaning 500+ table entry)
    sh_int song_on_line;            // How far along in the lyrics, if any.
    CHAR_DATA *song_target;         // Target of the song when it finishes (if needed)
    
    sh_int playing;                 // Is a song being played or not, 0 = no, 1 = yes.
    sh_int play_sn;                 // The sn of the song (actual, meaning 500+ table entry)
//    char* singer;
    sh_int lag_time;
};

/*
 * Structures for Mob Procs
 */
struct mob_prog_act_list
{
    MPROG_ACT_LIST *next;
    char *buf;
    CHAR_DATA *ch;
    OBJ_DATA *obj;
    void *vo;
};

struct mob_prog_data
{
    MPROG_DATA *next;
    int type;
    char *arglist;
    char *comlist;
};

bool MOBtrigger;

#define ERROR_PROG        -1
#define IN_FILE_PROG       0
#define ACT_PROG           (A)
#define SPEECH_PROG        (B)
#define RAND_PROG          (C)
#define FIGHT_PROG         (D)
#define DEATH_PROG         (E)
#define HITPRCNT_PROG      (F)
#define ENTRY_PROG         (G)
#define GREET_PROG         (H)
#define ALL_GREET_PROG     (I)
#define GIVE_PROG          (J)
#define BRIBE_PROG         (K)
#define GIVE_WORD_PROG     (L)
#define BORED_PROG         (M)
#define EXIT_PROG          (N)
#define EXALL_PROG         (O)


#define PCDATA_NEW_CLANREC      (A)
#define PCDATA_NEW_PKILLER      (B)
#define PCDATA_NEW_BUILDER      (C)
#define PCDATA_NEW_TRIBEREC     (D)
#define PCDATA_NEW_NOLEVEL      (E)
#define PCDATA_NEW_SLAYER       (F)
#define PCDATA_NEW_SERVE		(G)
/*
 * Data which only PC's have.
 */
struct pc_data
{
    PC_DATA *next;
    char *pwd;
    char *bamfin;
    char *bamfout;
    char *title;
    char *web_page;
    time_t last_note;
    time_t last_kvetsh;
    time_t last_penalty;
    time_t last_idea;
    time_t last_changes;
    time_t last_qwest;
    time_t last_rpnote;
    time_t last_inote;
    CLAN_LIST *clan;                /* For clan belonged too */
    TRIBE_LIST *tribe;
    long new_flags;             /* new flags for players */
    sh_int pkiller_count;
	sh_int slayer_count;
    sh_int rebirth_count;
    sh_int reawake_count;
	sh_int remort_count;
    sh_int new_rebirth;         /* flag for exp_to_level calculation */
    sh_int quest_points;
    int                 questpoints;  /* Vassago */
	long                gq_mobs[MAX_GQUEST_MOB]; //Added for Global Quests - Galius 4/16/2013
	int rebirthpoints;
    sh_int              nextquest; /* Vassago */
	int 		security;	/* OLC */ /* Builder security */
	sh_int		gamewait;
    sh_int perm_hit;
    sh_int perm_mana;
    sh_int perm_move;
    sh_int true_sex;
    int last_level;
     int awins;
    int alosses;
    int plr_wager;
    bool can_zoom[MAX_ZOOM];
    sh_int condition[3];
    sh_int learned[MAX_SKILL];
    sh_int songs_learned[MAX_SONG-SONG_SN_START];
    bool group_known[MAX_GROUP];
    sh_int points;
    bool confirm_delete;
    bool confirm_pkill;
	bool confirm_slayer;
	bool confirm_serve;
    sh_int is_questing;
    sh_int timer;
    int clan_points;
    sh_int quest_stats[MAX_STATS];
	long gamestat[MAX_GAMESTAT];
    char *codeword;
    int killer_until;
    int walltimer;
    int punish_until;
    char *destination;
    char *custom_arrival;
    char *custom_exit;
    char *spouse_name;
	int quickkill_sn;
};

/* Data for generating characters -- only used during generation */
struct gen_data
{
    GEN_DATA *next;
    bool skill_chosen[MAX_SKILL];
    bool group_chosen[MAX_GROUP];
    int points_chosen;
};

/*
 * Liquids.
 */
#define LIQ_WATER        0
#define LIQ_BLOOD       13
#define LIQ_MAX         22

struct liq_type
{
    char *liq_name;
    char *liq_color;
    sh_int liq_affect[3];
};

/*
 * Extra description data for a room or object.
 */
struct extra_descr_data
{
    EXTRA_DESCR_DATA *next;     /* Next in list                     */
    char *keyword;              /* Keyword in look/examine          */
    char *description;          /* What to see                      */
};

/*
 * Prototype for an object.
 */
struct obj_index_data
{
    OBJ_INDEX_DATA *next;
    EXTRA_DESCR_DATA *extra_descr;
    AFFECT_DATA *affected;
    SPEC_FUN *spec_fun;
    bool new_format;
    char *name;
    char *short_descr;
    char *description;
    sh_int vnum;
    sh_int reset_num;
    sh_int material;
    sh_int item_type;
    int extra_flags;
    long wear_flags;
    CLAN_LIST *membership;     /* indicates who CAN wear item */
    sh_int level;
    sh_int condition;
    sh_int count;
    sh_int weight;
    int cost;
    int value[5];
    /* Object and room progs - Coy 12/02 */
    PROG_LIST *		oprogs;
    long	    	oprog_flags;
	AREA_DATA *		area;		/* OLC */
};

/*
 * One object.
 */
struct obj_data
{
    OBJ_DATA *next;
    OBJ_DATA *next_content;
    OBJ_DATA *contains;
    OBJ_DATA *in_obj;
    CHAR_DATA *carried_by;
    EXTRA_DESCR_DATA *extra_descr;
    AFFECT_DATA *affected;
    OBJ_INDEX_DATA *pIndexData;
    ROOM_INDEX_DATA *in_room;
    SPEC_FUN *spec_fun;
    bool enchanted;
    char *owner;
    char *name;
    char *short_descr;
    char *description;
    sh_int item_type;
    int extra_flags;
    long wear_flags;
    sh_int wear_loc;
    sh_int weight;
    int cost;
    sh_int level;
    sh_int condition;
    sh_int material;
    sh_int timer;
    int value[5];
    /* Error checking for obj_update crash bug - Coy. 11/02 */
    int ref_count;
    /* Object and room progs - Coy 12/02 */
    CHAR_DATA *	    oprog_target;
    sh_int			oprog_delay;
};

/*
 * Exit data.
 */
struct exit_data
{
    union
    {
        ROOM_INDEX_DATA *to_room;
        sh_int vnum;
    }
    u1;
    sh_int exit_info;
    sh_int key;
    char *keyword;
    char *description;
	EXIT_DATA *		next;		/* OLC */
    int			rs_flags;	/* OLC */
    int			orig_door;	/* OLC */
};

/*
 * Reset commands:
 *   '*': comment
 *   'M': read a mobile 
 *   'O': read an object
 *   'P': put object in object
 *   'G': give object to mobile
 *   'E': equip object to mobile
 *   'D': set state of door
 *   'R': randomize room exits
 *   'S': stop (end of list)
 */

/*
 * Area-reset definition.
 */
struct reset_data
{
    RESET_DATA *next;
    char command;
    sh_int arg1;
    sh_int arg2;
    sh_int arg3;
};

/*
 * Area definition.
 */
struct area_data
{
  AREA_DATA *next;
  // RESET_DATA *reset_first; - removed for rom olc
  // RESET_DATA *reset_last; - removed for rom olc
  char *name;
  CONTINENT *continent;
  sh_int age;
  sh_int nplayer;
  bool empty;
  char *		filename;	/* OLC */
  char *		builders;	/* OLC */ /* Listing of */
  int			security;	/* OLC */ /* Value 1-9  */
  int			lvnum;		/* OLC */ /* Lower vnum */
  int			uvnum;		/* OLC */ /* Upper vnum */
  int			vnum;		/* OLC */ /* Area vnum  */
  int			area_flags;	/* OLC */
  /* Bunch of new stuff added by Ivan 2/24/99 */
  char *author;
  int low_vnum;
  int high_vnum;
  int low_level;
  int high_level;
  int total_rooms;
  bool test_area;
  bool dont_show;
  ROOM_INDEX_DATA *room_list;
  AREA_DATA *prev_cont_area;
  SHIP *ship;
};

/*
 * Room type.
 */

#define MAX_ROOM_EXITS  6

struct room_index_data
{
    ROOM_INDEX_DATA *next;
    CHAR_DATA *people;
    OBJ_DATA *contents;
    EXTRA_DESCR_DATA *extra_descr;
    AREA_DATA *area;
    EXIT_DATA *exit[MAX_ROOM_EXITS];
    char *name;
    char *description;
    sh_int vnum;
    int room_flags;
    sh_int light;
    sh_int sector_type;
    /* Added by Ivan - 2/24/99 */
    ROOM_INDEX_DATA *prev_area_room;
    /* Object and room progs - Coy 12/02 */
    PROG_LIST *		rprogs;
    CHAR_DATA *		rprog_target;
    long		rprog_flags;
    sh_int		rprog_delay;
	    RESET_DATA *	reset_first;	/* OLC */
    RESET_DATA *	reset_last;	/* OLC */
};

/*****************************************************************************
 *                                    OLC                                    *
 *****************************************************************************/

/*
 * This structure is used in special.c to lookup spec funcs and
 * also in olc_act.c to display listings of spec funcs.
 */
struct spec_type
{
    char *	spec_name;
    SPEC_FUN *	spec_fun;
};

/*
 * Object defined in limbo.are
 * Used in save.c to load objects that don't exist.
 */
#define OBJ_VNUM_DUMMY	1



/*
 * Area flags.
 */
#define         AREA_NONE       0
#define         AREA_CHANGED    1	/* Area has been modified. */
#define         AREA_ADDED      2	/* Area has been added to. */
#define         AREA_LOADING    4	/* Used for counting in db.c */



#define MAX_DIR	6
#define NO_FLAG -99	/* Must not be used in flags or stats. */



/*
 * Interp.c
 */
DECLARE_DO_FUN( do_olc		);
DECLARE_DO_FUN( do_asave	);
DECLARE_DO_FUN( do_alist	);
DECLARE_DO_FUN( do_resets	);


/*
 * Global Constants
 */
extern	char *	const	dir_name        [];
extern	const	sh_int	rev_dir         [];          /* sh_int - ROM OLC */
extern	const	struct	spec_type	spec_table	[];



/*
 * Global variables
 */
extern          AREA_DATA *             area_first;
extern          AREA_DATA *             area_last;
extern  	SHOP_DATA *             shop_last;

extern          int                     top_affect;
extern          int                     top_area;
extern          int                     top_ed;
extern          int                     top_exit;
extern          int                     top_help;
extern          int                     top_mob_index;
extern          int                     top_obj_index;
extern 			int 					top_rprog_index;
extern			int						top_oprog_index;
extern          int                     top_reset;
extern          int                     top_room;
extern          int                     top_shop;

extern          int                     top_vnum_mob;
extern          int                     top_vnum_obj;
extern          int                     top_vnum_room;

extern          char                    str_empty       [1];

extern  MOB_INDEX_DATA *        mob_index_hash  [MAX_KEY_HASH];
extern  OBJ_INDEX_DATA *        obj_index_hash  [MAX_KEY_HASH];
extern  ROOM_INDEX_DATA *       room_index_hash [MAX_KEY_HASH];

/*
 * Types of attacks.
 * Must be non-overlapping with spell/skill types,
 * but may be arbitrary beyond that.
 */
#define TYPE_UNDEFINED               -1
#define TYPE_HIT                     1000

/*
 *  Target types.
 */
#define TAR_IGNORE                  0
#define TAR_CHAR_OFFENSIVE          1
#define TAR_CHAR_DEFENSIVE          2
#define TAR_CHAR_SELF               3
#define TAR_OBJ_INV                 4
#define TAR_OBJ_ROOM                5
/*
 * Target type for song - Coy 1/03 
 */
#define TAR_SONG_SELF               0
#define TAR_SONG_GROUP              1
#define TAR_SONG_DEFENSIVE          2
#define TAR_SONG_OFFENSIVE          3

/*
 * Skills include spells as a particular case.
 */
struct skill_type
{
    char *name;                     /* Name of skill                */
    sh_int skill_level[MAX_CLASS];  /* Level needed by class        */
    sh_int rating[MAX_CLASS];       /* How hard it is to learn      */
    union
    {
      SPELL_FUN *spell;             /* Pointer to spell or          */
      DO_FUN *skill;                /* pointer to skill             */
    }
    fun;
    sh_int type;                    /* Skill, spell or autoskill    */
    sh_int target;                  /* Legal targets                */
    sh_int minimum_position;        /* Position for caster / user   */
    sh_int *pgsn;                   /* Pointer to associated gsn    */
    sh_int slot;                    /* Slot for #OBJECT loading     */
    sh_int min_mana;                /* Minimum mana used            */
    sh_int min_move;                /* Minimum mana used            */
    sh_int beats;                   /* Waiting time after use       */
    char *noun_damage;              /* Damage message               */
    char *msg_off;                  /* Wear off message             */
	long		cooldown;				//how long before they can use again? 0 for none.

};

/* Skill types - Ivan */
#define TYPE_UNDEF     0
#define TYPE_SKILL     1
#define TYPE_SPELL     2
#define TYPE_AUTO      3
#define TYPE_SONG      4

/* Coy 8/01 */
struct song_type
{
    char *name;              /* Name of song                               */
    sh_int song_level;       /* Level needed to sing                       */
    sh_int speed;            /* Used primarily for offensive songs with -1 or -2 timing */
    
    sh_int rating;           /* How hard it is to learn                    */
    SONG_FUN *song;          /* Pointer to song                            */
    sh_int target;           /* Legal targets                              */
    sh_int minimum_position; /* Position for singer / user                 */
    sh_int *pgsn;            /* Pointer to associated gsn                  */
    sh_int deductor;         /* 0 = no cost
                              * ===
                              * 1 = mana
                              * 2 = hp
                              * 3 = moves								
                              * ===
                              * 4 = mana & hp
                              * 5 = mana & moves
                              * 6 = hp   & moves
                              * ===
                              * 7 = mana & hp & moves                      */
    sh_int min_points;       /* Minimum mana used                          */
    sh_int beats;            /* Waiting time after or before affect sticks */
    sh_int lyric_lines;      /* number of lines in the song                */
    sh_int drunk_cost;       /* drunk level required to sing               */
    char *noun_damage;       /* Damage message                             */
    char *msg_off;           /* Wear off message                           */
    char lyrics[MAX_LINES_PER_SONG][MAX_STRING_LENGTH];
    sh_int timing;           /* How long after the song is started the
                              * effect takes place                         */

};

struct song_lyrics
{
	char *name;
	char *lines[5];
};

/* Newbie gold allotment - Ivan */
#define NEWBIE_GOLD_AMOUNT 1000

struct group_type
{
    char *name;
    sh_int rating[MAX_CLASS];
    char *spells[MAX_IN_GROUP];
};

/*
 * These are skill_lookup return values for common skills and spells.
 */
/* New gsn list - Ivan 3/10/99 */
extern sh_int gsn_abomination;
extern sh_int gsn_acid_arrow;
extern sh_int gsn_acid_blast;
extern sh_int gsn_acid_breath;
extern sh_int gsn_acid_rain;
extern sh_int gsn_acidpie;
extern sh_int gsn_allure;
extern sh_int gsn_acupressure;
extern sh_int gsn_acupuncture;
extern sh_int gsn_aegis;
extern sh_int gsn_aid;
extern sh_int gsn_amnesia;
extern sh_int gsn_animate_dead;
extern sh_int gsn_angel_smite;
extern sh_int gsn_ankoku;
extern sh_int gsn_anvil;
extern sh_int gsn_armor;
extern sh_int gsn_arrow_barrage;
extern sh_int gsn_avalanche;
extern sh_int gsn_axe;
extern sh_int gsn_backstab;
extern sh_int gsn_banish;
extern sh_int gsn_banshee_wail;
extern sh_int gsn_bark_skin;
extern sh_int gsn_bash;
extern sh_int gsn_bearhug;
extern sh_int gsn_beastmaster;
extern sh_int gsn_berserk;
extern sh_int gsn_bind;
extern sh_int gsn_bite;
extern sh_int gsn_whirling_dervish;
extern sh_int gsn_dirty_tactics;
extern sh_int gsn_bless;
extern sh_int gsn_blessed_weapon;
extern sh_int gsn_blindness;
extern sh_int gsn_blur;
extern sh_int gsn_black_plague;
extern sh_int gsn_bloodstrike;
extern sh_int gsn_bola;
extern sh_int gsn_bow;
extern sh_int gsn_bubble;
extern sh_int gsn_burning_hands;
extern sh_int gsn_burning_light;
extern sh_int gsn_call_comet;
extern sh_int gsn_call_lightning;
extern sh_int gsn_calm;
extern sh_int gsn_camouflage;
extern sh_int gsn_camp;
extern sh_int gsn_cancellation;
extern sh_int gsn_cause_critical;
extern sh_int gsn_cause_light;
extern sh_int gsn_cause_serious;
extern sh_int gsn_celerity;
extern sh_int gsn_chain_lightning;
extern sh_int gsn_change_sex;
extern sh_int gsn_channel;
extern sh_int gsn_chaos_arrow;
extern sh_int gsn_chaotic_shift;
extern sh_int gsn_charge;
extern sh_int gsn_charm_person;
extern sh_int gsn_chikara;
extern sh_int gsn_chill_touch;
extern sh_int gsn_circle;
extern sh_int gsn_celestial_recall;
extern sh_int gsn_claw;
extern sh_int gsn_cleanse;
extern sh_int gsn_club;
extern sh_int gsn_colour_spray;
extern sh_int gsn_collect_rain;
extern sh_int gsn_composite_elemental;
extern sh_int gsn_ambush;
extern sh_int gsn_quick_feet;
extern sh_int gsn_quick_reflexes;
extern sh_int gsn_disrupt;
extern sh_int gsn_concentrate;
extern sh_int gsn_continual_light;
extern sh_int gsn_control_undead;
extern sh_int gsn_control_weather;
extern sh_int gsn_conversion;
extern sh_int gsn_create_darkness;
extern sh_int gsn_make_war;
extern sh_int gsn_create_feast;
extern sh_int gsn_create_food;
extern sh_int gsn_create_goat;
extern sh_int gsn_create_medicine;
extern sh_int gsn_create_rose;
extern sh_int gsn_create_spring;
extern sh_int gsn_create_sushi;
extern sh_int gsn_create_water;
extern sh_int gsn_critical_hit;
extern sh_int gsn_cure_blindness;
extern sh_int gsn_cure_critical;
extern sh_int gsn_cure_disease;
extern sh_int gsn_cure_light;
extern sh_int gsn_cure_plague;
extern sh_int gsn_cure_poison;
extern sh_int gsn_cure_serious;
extern sh_int gsn_curse;
extern sh_int gsn_cutthroat;
extern sh_int gsn_dagger;
extern sh_int gsn_damned_blade;
extern sh_int gsn_deadly_aura;
extern sh_int gsn_deadly_magic;
extern sh_int gsn_deadly_strike;
extern sh_int gsn_decoy;
extern sh_int gsn_demonfire;
extern sh_int gsn_detect_evil;
extern sh_int gsn_detect_good;
extern sh_int gsn_detect_hidden;
extern sh_int gsn_detect_invis;
extern sh_int gsn_detect_magic;
extern sh_int gsn_detect_poison;
extern sh_int gsn_energy_shield;
extern sh_int gsn_dice_roll;
extern sh_int gsn_dirt_kicking;
extern sh_int gsn_disarm;
extern sh_int gsn_dispel_defense;
extern sh_int gsn_diseased_touch;
extern sh_int gsn_toxic_bite;
extern sh_int gsn_dispel_magic;
extern sh_int gsn_distract;
extern sh_int gsn_dive;
extern sh_int gsn_dodge;
extern sh_int gsn_dragon_breath;
extern sh_int gsn_eagle_eye;
extern sh_int gsn_earthquake;
extern sh_int gsn_empower;
extern sh_int gsn_enchant_armor;
extern sh_int gsn_enchant_weapon;
extern sh_int gsn_energy_drain;
extern sh_int gsn_engulf;
extern sh_int gsn_enhanced_damage;
extern sh_int gsn_expert_magic;
extern sh_int gsn_extended_attack;
extern sh_int gsn_evade;
extern sh_int gsn_fade;
extern sh_int gsn_faerie_fire;
extern sh_int gsn_faerie_fog;
extern sh_int gsn_farsight;
extern sh_int gsn_fast_healing;
extern sh_int gsn_fast_regeneration;
extern sh_int gsn_fast_talk;
extern sh_int gsn_fifth_attack;
extern sh_int gsn_fire_breath;
extern sh_int gsn_water_breath;
extern sh_int gsn_firststrike;
extern sh_int gsn_fireball;
extern sh_int gsn_fireclone;
extern sh_int gsn_flail;
extern sh_int gsn_flamestrike;
extern sh_int gsn_flaming_arrow;
extern sh_int gsn_flare;
extern sh_int gsn_fly;
extern sh_int gsn_flying_kick;
extern sh_int gsn_forage;
extern sh_int gsn_fortitude;
extern sh_int gsn_fourth_attack;
extern sh_int gsn_frenzy;
extern sh_int gsn_frost_breath;
extern sh_int gsn_gambaro;
extern sh_int gsn_gas_breath;
extern sh_int gsn_gate;
extern sh_int gsn_general_purpose;
extern sh_int gsn_giant_strength;
extern sh_int gsn_grenade;
extern sh_int gsn_guilt;
extern sh_int gsn_guinness_dream;
extern sh_int gsn_haggle;
extern sh_int gsn_hand_to_hand;
extern sh_int gsn_harm;
extern sh_int gsn_haste;
extern sh_int gsn_headbutt;
extern sh_int gsn_heal;
extern sh_int gsn_healing_aura;
extern sh_int gsn_heat_metal;
extern sh_int gsn_henchmen;
extern sh_int gsn_herb_lore;
extern sh_int gsn_hex;
extern sh_int gsn_hide;
extern sh_int gsn_high_explosive;
extern sh_int gsn_hobble;
extern sh_int gsn_hogo;
extern sh_int gsn_holy_hands;
extern sh_int gsn_holy_word;
extern sh_int gsn_hotfoot;
extern sh_int gsn_ice_storm;
extern sh_int gsn_iceclone;
extern sh_int gsn_icefire;
extern sh_int gsn_identify;
extern sh_int gsn_infravision;
extern sh_int gsn_inspiration;
extern sh_int gsn_intimidate;
extern sh_int gsn_invigorate;
extern sh_int gsn_invis;
extern sh_int gsn_iron_grip;
extern sh_int gsn_ishi;
extern sh_int gsn_jishin;
extern sh_int gsn_joke;
extern sh_int gsn_kako;
extern sh_int gsn_kamikaze;
extern sh_int gsn_kendo;
extern sh_int gsn_kick;
extern sh_int gsn_know_alignment;
extern sh_int gsn_landslide;
extern sh_int gsn_leviathan;
extern sh_int gsn_life_drain;
extern sh_int gsn_life_tap;
extern sh_int gsn_lightning_bolt;
extern sh_int gsn_lightning_breath;
extern sh_int gsn_forge_blade;
extern sh_int gsn_locate_object;
extern sh_int gsn_lore;
extern sh_int gsn_mace;
extern sh_int gsn_magic_arrow;
extern sh_int gsn_magic_missile;
extern sh_int gsn_magical_extension;
extern sh_int gsn_major_healing;
extern sh_int gsn_superior_healing;
extern sh_int gsn_prayer;
extern sh_int gsn_firestorm;
extern sh_int gsn_make_resist;
extern sh_int gsn_mamoru;
extern sh_int gsn_mass_blindness;
extern sh_int gsn_mass_healing;
extern sh_int gsn_mass_invis;
extern sh_int gsn_master_weapon;
extern sh_int gsn_meditate;
extern sh_int gsn_meditation;
extern sh_int gsn_mend;
extern sh_int gsn_mesmeric_burn;
extern sh_int gsn_metal_skin;
extern sh_int gsn_moete;
extern sh_int gsn_monsoon;
extern sh_int gsn_moustache;
extern sh_int gsn_mudpie;
extern sh_int gsn_mug;
extern sh_int gsn_nature_spirit;
extern sh_int gsn_nature_strike;
extern sh_int gsn_naturecall;
extern sh_int gsn_necromancy;
extern sh_int gsn_nexus;
extern sh_int gsn_orb_of_the_sun;
extern sh_int gsn_overbord;
extern sh_int gsn_palm;
extern sh_int gsn_parry;
extern sh_int gsn_pass_door;
extern sh_int gsn_peek;
extern sh_int gsn_penance;
extern sh_int gsn_pick_lock;
extern sh_int gsn_pilfer;
extern sh_int gsn_plague;
extern sh_int gsn_poison;
extern sh_int gsn_poisoned_arrow;
extern sh_int gsn_polearm;
extern sh_int gsn_portal;
extern sh_int gsn_powersink;
extern sh_int gsn_powerword_kill;
extern sh_int gsn_preserve;
extern sh_int gsn_pressurepoint;
extern sh_int gsn_probing_fingers;
extern sh_int gsn_protection_evil;
extern sh_int gsn_psychosis;
extern sh_int gsn_purpose;
extern sh_int gsn_quicksand;
extern sh_int gsn_quivering_palms;
extern sh_int gsn_rainbow;
extern sh_int gsn_raise_skeleton;
extern sh_int gsn_rally;
extern sh_int gsn_razor_arrow;
extern sh_int gsn_recall;
extern sh_int gsn_recharge;
extern sh_int gsn_redirect;
extern sh_int gsn_reforge;
extern sh_int gsn_refresh;
extern sh_int gsn_remove_curse;
extern sh_int gsn_refresh_mana;
extern sh_int gsn_rescue;
extern sh_int gsn_restoration;
extern sh_int gsn_restoration_wait;
extern sh_int gsn_restore_mana;
extern sh_int gsn_resurrect;
extern sh_int gsn_retreat;
extern sh_int gsn_group_retreat;
extern sh_int gsn_ride;
extern sh_int gsn_righteous_magic;
extern sh_int gsn_rollmud;
extern sh_int gsn_roundhouse;
extern sh_int gsn_rush;
extern sh_int gsn_assassinate;
extern sh_int gsn_rampage;
extern sh_int gsn_counter;
extern sh_int gsn_phase;
extern sh_int gsn_safety;
extern sh_int gsn_sanctify;
extern sh_int gsn_sanctuary;
extern sh_int gsn_scrolls;
extern sh_int gsn_second_attack;
extern sh_int gsn_security_shield;
extern sh_int gsn_seeking_arrow;
extern sh_int gsn_sekkusu;
extern sh_int gsn_senko;
extern sh_int gsn_shadow;
extern sh_int gsn_sharpen;
extern sh_int gsn_shelter;
extern sh_int gsn_shield;
extern sh_int gsn_shield_block;
extern sh_int gsn_shocking_grasp;
extern sh_int gsn_shove;
extern sh_int gsn_shuryo;
extern sh_int gsn_sleep;
extern sh_int gsn_sleight_of_hand;
extern sh_int gsn_slow;
extern sh_int gsn_smash;
extern sh_int gsn_smoke_rings;
extern sh_int gsn_smite;
extern sh_int gsn_sneak;
extern sh_int gsn_sonic_arrow;
extern sh_int gsn_soulstrike;
extern sh_int gsn_spear;
extern sh_int gsn_splint;
extern sh_int gsn_squeeze;
extern sh_int gsn_starfire;
extern sh_int gsn_staves;
extern sh_int gsn_steal;
extern sh_int gsn_stitch;
extern sh_int gsn_stomp;
extern sh_int gsn_stone_skin;
extern sh_int gsn_strike;
extern sh_int gsn_stun;
extern sh_int gsn_inlay;
extern sh_int gsn_elemental_barrage;
extern sh_int gsn_summon;
extern sh_int gsn_super_sanctuary;
/* Removed by Coy 1/18/01. Change from super shield to ward */
/* extern sh_int gsn_super_shield; */
extern sh_int gsn_sweep;
extern sh_int gsn_swim;
extern sh_int gsn_sword;
extern sh_int gsn_tail;
extern sh_int gsn_tate;
extern sh_int gsn_teleport;
extern sh_int gsn_third_attack;
extern sh_int gsn_third_eye;
extern sh_int gsn_throw;
extern sh_int gsn_thrust;
extern sh_int gsn_tinker;
extern sh_int gsn_tobu;
extern sh_int gsn_trip;
extern sh_int gsn_true_sight;
extern sh_int gsn_unarmed_combat;
extern sh_int gsn_uppercut;
extern sh_int gsn_ventriloquate;
extern sh_int gsn_volzhd;
extern sh_int gsn_vortex;
extern sh_int gsn_wall_of_force;
extern sh_int gsn_wall_of_thorns;
extern sh_int gsn_wands;
extern sh_int gsn_ward;
extern sh_int gsn_waterspout;
extern sh_int gsn_weaken;
extern sh_int gsn_whip;
extern sh_int gsn_wind;
extern sh_int gsn_word_of_recall;
extern sh_int gsn_wrath;
extern sh_int gsn_zoom;
extern sh_int gsn_xyzreserved;
extern sh_int gsn_yoroi;
//Tome Abilities
extern sh_int gsn_extra_attack;
extern sh_int gsn_improved_damage;
extern sh_int gsn_improved_magic;
extern sh_int gsn_sixshooter;
extern sh_int gsn_foresee;
extern sh_int gsn_rain_of_swords;
extern sh_int gsn_leech_life;
extern sh_int gsn_instant;

/* Mythos: song gsn's, we'll mix them in later... */
extern sh_int gsn_aminas_ballad;
extern sh_int gsn_ayre_of_airs;
extern sh_int gsn_blessed_be_the_weak;
extern sh_int gsn_crystal_rose;
extern sh_int gsn_death_knell;
extern sh_int gsn_drunkards_rage;
extern sh_int gsn_happiness;
extern sh_int gsn_maeves_battlesong;
extern sh_int gsn_niaves_grief;
extern sh_int gsn_odins_thunder;
extern sh_int gsn_ryme_of_duotime;
extern sh_int gsn_stiehlsong;
extern sh_int gsn_stray_gnome_strut;
extern sh_int gsn_warriors_of_the_wind;
extern sh_int gsn_watcher;
extern sh_int gsn_without_glory;
extern sh_int gsn_woe_be_the_strong;

/*
 * Utility macros.
 */
#define IS_VALID(data)          ((data) != NULL && (data)->valid)
#define VALIDATE(data)          ((data)->valid = TRUE)
#define INVALIDATE(data)        ((data)->valid = FALSE)
#define UMIN(a, b)              ((a) < (b) ? (a) : (b))
#define UMAX(a, b)              ((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)         ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define LOWER(c)                ((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)                ((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define IS_SET(flag, bit)       ((flag) & (bit))
#define SET_BIT(var, bit)       ((var) |= (bit))
#define REMOVE_BIT(var, bit)    ((var) &= ~(bit))
#define IS_NULLSTR(str)		((str) == NULL || (str)[0] == '\0')

/*
 * Character macros.
 */
#define IS_NPC(ch)              (IS_SET((ch)->act, ACT_IS_NPC))
#define IS_IMMORTAL(ch)         (get_trust(ch) >= LEVEL_IMMORTAL)
#define IS_HERO(ch)             (get_trust(ch) >= LEVEL_HERO)
#define IS_TRUSTED(ch,level)    (get_trust((ch)) >= (level))
#define IS_AFFECTED(ch, sn)     (IS_SET((ch)->affected_by, (sn)))
#define IS_AFFECTED2(ch, sn)    (IS_SET((ch)->affected2_by, (sn)))

#define GET_AGE(ch)       ((int) (17 + ((ch)->played + current_time - (ch)->logon )/72000))
#define IS_GOOD(ch)             (ch->alignment >= 350)
#define IS_EVIL(ch)             (ch->alignment <= -350)
#define IS_NEUTRAL(ch)          (!IS_GOOD(ch) && !IS_EVIL(ch))
#define IS_QUESTOR(ch)     (IS_SET((ch)->act, PLR_QUESTOR))
#define IS_AWAKE(ch)            (ch->position > POS_SLEEPING)
#define GET_AC(ch,type)         get_ac(ch,type)
/*  #define GET_AC(ch,type)         ((ch)->armor[type] + (IS_AWAKE(ch) ? dex_app[get_curr_stat(ch,STAT_DEX)].defensive : 0 ))  */
#define GET_HITROLL(ch) ((ch)->hitroll+str_app[get_curr_stat(ch,STAT_STR)].tohit)
#define GET_DAMROLL(ch) ((ch)->damroll+str_app[get_curr_stat(ch,STAT_STR)].todam)

#define IS_OUTSIDE(ch)          (!IS_SET((ch)->in_room->room_flags,ROOM_INDOORS))

#define WAIT_STATE(ch, npulse)  ((ch)->wait = UMAX((ch)->wait, (npulse)))
#define GWAIT_STATE(ch, npulse)	((ch)->pcdata->gamewait = UMAX((ch)->pcdata->gamewait, (npulse)))
#define ON_GQUEST(ch)           (!IS_NPC(ch) && IS_SET((ch)->act, PLR_GQUEST) && gquest_info.running != GQUEST_OFF) //Added for Global Quests - Galius 4/16/2013
/* Object and room progs - Coy 12/02 */
#define HAS_TRIGGER_MOB(ch,trig) (IS_SET((ch)->pIndexData->mprog_flags,(trig)))
#define HAS_TRIGGER_OBJ(obj,trig) (IS_SET((obj)->pIndexData->oprog_flags,(trig)))
#define HAS_TRIGGER_ROOM(room,trig) (IS_SET((room)->rprog_flags,(trig)))

/* Macro for mana cost calculation - Ivan 3/27/99 */
#define CALCULATE_MANA(ch, sn)		   (skill_table[sn].min_mana)

/* Macro for movement cost calculation - Sankin 6/3/09   */
/* This is carbon copy of Ivans mana calculations but    */
/* for movement                                          */
#define CALCULATE_MOVE(ch, sn)                           \
	(IS_NPC(ch) ? skill_table[sn].min_move :         \
   UMAX( skill_table[sn].min_move,                       \
     100 / UMAX( 2,                                      \
       ( 2 + ch->level -                                 \
         ( is_race_skill( ch, skill_table[sn].name ) ?   \
           1 : skill_table[sn].skill_level[ch->class])))))

/* Macros identifying rebirth and remort items - Ivan 4/5/99 */

#define IS_REBIRTH_ITEM(obj)                     \
((obj)->pIndexData->vnum == OBJ_VNUM_REBIRTH1 || \
 (obj)->pIndexData->vnum == OBJ_VNUM_REBIRTH2 || \
 (obj)->pIndexData->vnum == OBJ_VNUM_REBIRTH3 || \
 (obj)->pIndexData->vnum == OBJ_VNUM_REBIRTH4 || \
 (obj)->pIndexData->vnum == OBJ_VNUM_REBIRTH5 || \
 (obj)->pIndexData->vnum == OBJ_VNUM_REBIRTH6 || \
 (obj)->pIndexData->vnum == OBJ_VNUM_REBIRTH7)

#define IS_REMORT_ITEM(obj)         \
((obj)->pIndexData->vnum > 10700 && \
 (obj)->pIndexData->vnum < 10890)

/* These numbers will have to be changed later, just getting
	basic stuff in for rm2 - Nalathni */

#define IS_REMORT2_ITEM(obj)        \
((obj)->pIndexData->vnum > 10700 && \
 (obj)->pIndexData->vnum < 10890)

/*
 * Object macros.
 */
#define CAN_WEAR(obj, part)     (IS_SET((obj)->wear_flags,  (part)))
#define IS_OBJ_STAT(obj, stat)  (IS_SET((obj)->extra_flags, (stat)))
#define IS_WEAPON_STAT(obj,stat)(IS_SET((obj)->value[4],(stat)))
#define WEIGHT_MULT(obj)	((obj)->item_type == ITEM_CONTAINER ? \
	(obj)->value[4] : 100)
/*
 * Description macros.
 */
#define PERS(ch, looker)	( can_see( looker, (ch) ) ? ( IS_NPC(ch) ? (ch)->short_descr : (ch)->name)  : "someone" )
							
/*
 * Structure for a social in the socials table.
 */
struct social_type
{
    char name[20];
    char *char_no_arg;
    char *others_no_arg;
    char *char_found;
    char *others_found;
    char *vict_found;
    char *char_not_found;
    char *char_auto;
    char *others_auto;
};

/*
 * Global constants.
 */
extern const struct str_app_type str_app[36];
extern const struct int_app_type int_app[36];
extern const struct wis_app_type wis_app[36];
extern const struct dex_app_type dex_app[36];
extern const struct con_app_type con_app[36];

extern const struct attack_type attack_table[MAX_DAMAGE_MESSAGE];
extern const struct pc_race_type pc_race_table[];
extern const struct wiznet_type wiznet_table[];
extern const struct liq_type liq_table[LIQ_MAX];
extern const struct group_type group_table[MAX_GROUP];
extern struct social_type social_table[MAX_SOCIALS];
extern char *const title_table[MAX_CLASS] [MAX_LEVEL + 1] [2];
/* Object and room progs - Coy 12/02 */
extern	const	struct	flag_type	oprog_flags[];
extern	const	struct	flag_type	rprog_flags[];

/* Ivan's tablization project 2/18/99 - Hometown stuff */
#define MAX_HOMETOWNS      10
extern         HOMETOWN              *     ht_table[MAX_HOMETOWNS];
extern int last_hometown;
#define HOMETOWN_FILE     "../tables/hometown.dat"

/* Ivan's tablization project 2/18/99 - Continent stuff */
#define MAX_CONTINENTS      11
extern         CONTINENT              *     continent_table[MAX_CONTINENTS];
extern int last_continent;
#define CONTINENT_FILE     "../tables/continent.dat"

/* Ivan's tablization project 2/18/99 - Clan table */
#define MAX_CLANS      10
extern         CLAN_LIST              *     clan_table[MAX_CLANS];
extern int last_clan;
#define CLAN_FILE     "../tables/clan.dat"
#define NO_CLAN         0

/* Ivan's tablization project 2/18/99 - Tribe table */
#define MAX_TRIBES      30
extern         TRIBE_LIST              *     tribe_table[MAX_TRIBES];
extern int last_tribe;
#define TRIBE_FILE     "../tables/tribe.dat"
#define NO_TRIBE        0

/* Ivan's tablization project 2/18/99 - Class table */
extern         CLASS_LIST              class_table[MAX_CLASS];
extern int last_class;
#define CLASS_FILE     "../tables/class.dat"
#define NO_CLASS        0

/* Ivan's tablization project 2/18/99 - Race table */
extern         RACE_TYPE              race_table[MAX_RACE];
extern int last_race;
#define RACE_FILE     "../tables/race.dat"

/* Ivan's tablization project 2/18/99 - Skill table */
extern         SKILL_TYPE              skill_table[MAX_SKILL];
extern int last_skill;
#define SKILL_FILE     "../tables/skill.dat"

/* Song table (for bards) - Coy 8/01
 * 
 * The indexing number for songs in the song table will actually
 * be (MAX_SONG - 500).  So, we need to initialize the array to
 * be smaller rather than using just MAX_SONG like the other tables.
 * The reason for this is to have gsn numbers that don't overlap with
 * skill/spell gsn's.
 */
extern         SONG_TYPE              song_table[MAX_SONG - SONG_SN_START];
extern int last_song;
#define SONG_FILE     "../tables/song.dat"

/* Ivan's earlier mods - redone alarm catcher stuff */
extern int TimeOut;
extern int top_area;
extern AREA_DATA *area_first;

/* Food list for create_food spells - Ivan 3/22/99 */

#define MAX_FOODS 26 /*adding one for steak - Nalathni */
extern int food_list[MAX_FOODS];
extern int last_food;

/* Default pirate list */

#define MAX_PIRATE_VNUMS 10
extern int default_pirate_vnum[MAX_PIRATE_VNUMS];

/*
 * Global variables.
 */
extern HELP_DATA *help_first;
extern SHOP_DATA *shop_first;

extern BAN_DATA *ban_list;
extern BAN_DATA *newban_list;
extern CHAR_DATA *char_list;
extern DESCRIPTOR_DATA *descriptor_list;
extern NOTE_DATA *note_list;
extern OBJ_DATA *object_list;
extern TRIVIA_DATA *trivia;
extern AFFECT_DATA *affect_free;
extern BAN_DATA *ban_free;
extern CHAR_DATA *char_free;
extern DESCRIPTOR_DATA *descriptor_free;
extern EXTRA_DESCR_DATA *extra_descr_free;
extern NOTE_DATA *note_free;
extern OBJ_DATA *obj_free;
extern PC_DATA *pcdata_free;
extern MEM_DATA *mem_data_free;
extern BUFFER *buf_free;
extern char bug_buf[];
extern time_t current_time;
extern bool fLogAll;
extern FILE *fpReserve;
extern KILL_DATA kill_table[];
extern char log_buf[];
extern TIME_INFO_DATA time_info;
extern WEATHER_DATA weather_info;
extern bool real_time_status;
/* Object and room progs - Coy 12/02 */
extern          PROG_CODE         *     rprog_list;
extern          PROG_CODE         *     oprog_list;
int top_mob_index;
int top_obj_index;
extern OBJ_INDEX_DATA *obj_index_hash[MAX_KEY_HASH];
extern OWHERE_DATA *main_owhere_obj;
extern int owhere_obj_vnums[6000];

/* port global variable to differentiate test and real mud. -- Lorn 10/99 */

/*
 * OS-dependent declarations.
 * These are all very standard library functions,
 *   but some systems have incomplete or non-ansi header files.
 */
#if     defined(_AIX)
char *crypt args((const char *key, const char *salt));

#endif

#if     defined(apollo)
int atoi args((const char *string));
void *calloc args((unsigned nelem, size_t size));
char *crypt args((const char *key, const char *salt));

#endif

#if     defined(hpux)
char *crypt args((const char *key, const char *salt));

#endif

#if     defined(linux)
char *crypt args((const char *key, const char *salt));

#endif

#if     defined(macintosh)
#define NOCRYPT
#if     defined(unix)
#undef  unix
#endif
#endif

#if     defined(MIPS_OS)
char *crypt args((const char *key, const char *salt));

#endif

#if     defined(MSDOS)
#define NOCRYPT
#if     defined(unix)
#undef  unix
#endif
#endif

#if     defined(NeXT)
char *crypt args((const char *key, const char *salt));

#endif

#if     defined(sequent)
char *crypt args((const char *key, const char *salt));
int fclose args((FILE * stream));
int fprintf args((FILE * stream, const char *format,...));
int fread args((void *ptr, int size, int n, FILE * stream));
int fseek args((FILE * stream, long offset, int ptrname));
void perror args((const char *s));
int ungetc args((int c, FILE * stream));

#endif
/*
 * #if     defined(sun)
 * char *  crypt           args( ( const char *key, const char *salt ) );
 * int     fclose          args( ( FILE *stream ) );
 * int     fprintf         args( ( FILE *stream, const char *format, ... ) );
 * #if     defined(SYSV)
 * siz_t   fread           args( ( void *ptr, size_t size, size_t n, 
 * FILE *stream) );
 * #else
 * int     fread           args( ( void *ptr, int size, int n, FILE *stream ) );
 * #endif
 * int     fseek           args( ( FILE *stream, long offset, int ptrname ) );
 * void    perror          args( ( const char *s ) );
 * int     ungetc          args( ( int c, FILE *stream ) );
 * #endif
 */
#if     defined(ultrix)
char *crypt args((const char *key, const char *salt));

#endif

/*
 * The crypt(3) function is not available on some operating systems.
 * In particular, the U.S. Government prohibits its export from the
 *   United States to foreign countries.
 * Turn on NOCRYPT to keep passwords in plain text.
 */
#if     defined(NOCRYPT)
#define crypt(s1, s2)   (s1)
#endif

/*
 * Data files used by the server.
 *
 * AREA_LIST contains a list of areas to boot.
 * All files are read in completely at bootup.
 * Most output files (bug, idea, typo, shutdown) are append-only.
 *
 * The NULL_FILE is held open so that we have a stream handle in reserve,
 *   so players can go ahead and telnet to all the other descriptors.
 * Then we close it whenever we need to open a file (e.g. a save file).
 */
#if defined(macintosh)
#define PLAYER_DIR      ""      /* Player files                 */
#define PLAYER_TEMP     "temp"
#define NULL_FILE       "proto.are"  /* To reserve one stream        */
#endif

#if defined(MSDOS)
#define PLAYER_DIR      "../player/"
#define PLAYER_TEMP     "temp"
#define NULL_FILE       "nul"   /* To reserve one stream        */
#define MOB_DIR         "mobprogs/"  /* added for Lorn's computer */
#endif

#if defined(unix)
#define PLAYER_DIR      "../player/"  /* Player files                 */
#define PLAYER_TEMP     "../player/temp"
#define GOD_DIR         "../gods/"  /* list of gods                 */
#define NULL_FILE       "/dev/null"  /* To reserve one stream        */
#define MOB_DIR         "MOBProgs/"  /* MOBProg files                */
#endif

#define AREA_LIST       "../area/area.lst"  /* List of areas                */
#define BUG_FILE        "bugs.txt"  /* For 'bug' and bug( )         */
#define IDEA_FILE       "ideas.txt"  /* For 'idea'                   */
#define TYPO_FILE       "typos.txt"  /* For 'typo'                   */
#define NOTE_FILE       "notes.txt"  /* For 'notes'                  */
#define PENALTY_FILE    "penalty.txt"  /* For 'penalties'              */
#define KVETSH_FILE     "kvetsh.txt"  /* For 'complaining'               */
#define NEWS_FILE       "news.txt"  /* For 'news'                   */
#define CHANGES_FILE    "changes.txt"  /* For 'changes'                */
#define QWEST_FILE      "qwest.txt"  /* For 'qwests'               */
#define RPNOTE_FILE     "rpnotes.txt" /* for 'rpnotes'          */
#define INOTE_FILE      "inotes.txt"  /* for 'inotes'           */
#define SHUTDOWN_FILE   "shutdown.txt"  /* For 'shutdown'               */
#define BAN_FILE        "banned.txt"  /* For 'banned sites'           */
#define NEWBAN_FILE     "newbanned.txt"  /* For 'newbanned sites'           */
#define CHANGE_FILE     "changes.dat"  /* Changes.dat for changes command  */
#define GQUEST_FILE     "gquest.dat" //Added for Global Quests - Galius 4/16/2013

/*
 * Our function prototypes.
 * One big lump ... this is every function in Merc.
 */
#define CD      CHAR_DATA
#define MID     MOB_INDEX_DATA
#define OD      OBJ_DATA
#define OID     OBJ_INDEX_DATA
#define RID     ROOM_INDEX_DATA
#define SF      SPEC_FUN

/*arena.c*/
void check_arena args ( ( CHAR_DATA * ch, CHAR_DATA * victim) );
void do_gmessage args ( ( char *argument));



/* auction.c */
void auction_channel args ( ( char *msg, bool iauc ) );
int count_auc ( CHAR_DATA * ch );
void reset_auc ( AUCTION_DATA * auc );
void update_auc ( void );
AUCTION_DATA *new_auction ( void );
void free_auction ( AUCTION_DATA * auction );
void do_trivia args(( CHAR_DATA *ch, char*argument ));

/* act_comm.c */
bool is_note_to args((CHAR_DATA * ch, NOTE_DATA * pnote));
void check_sex args((CHAR_DATA * ch));
void add_follower args((CHAR_DATA * ch, CHAR_DATA * master));
void stop_follower args((CHAR_DATA * ch));
void nuke_pets args((CHAR_DATA * ch));
void die_follower args((CHAR_DATA * ch));
bool is_same_group args((CHAR_DATA * ach, CHAR_DATA * bch));
void send_info args((CHAR_DATA * ch, char *argument, bool ToChar));
void god_info args((CHAR_DATA * ch, char *argument));
void set_addict args((void));
void send_ship_info args((AREA_DATA *ship_area, char *argument));

/* changes.c */
void load_changes args( (void) );
void save_changes args( (void) );
void delete_change args( (int num) );
DESCRIPTOR_DATA *new_descriptor(void);
void init_descriptor(int control);

/* act_enter.c */
ROOM_INDEX_DATA *get_random_room args((CHAR_DATA * ch));
ROOM_INDEX_DATA *random_room_in_continent args((CHAR_DATA * ch, CONTINENT * cont));
ROOM_INDEX_DATA *random_room_in_world args((CHAR_DATA * ch));

/* act_info.c */
void set_title args((CHAR_DATA * ch, char *title));
void do_look args((CHAR_DATA * ch, char *argument));

/* act_move.c */
void move_char args((CHAR_DATA * ch, int door, bool follow));
void do_rebirth args((CHAR_DATA * ch, char *argument));
void do_evolve args((CHAR_DATA * ch, char *argument));
void remort_player args((CHAR_DATA * ch));
void remort2_player args((CHAR_DATA * ch));

/* act_obj.c */
bool can_loot args((CHAR_DATA * ch, OBJ_DATA * obj));
void do_second args((CHAR_DATA * ch, char *argument));
void get_obj args((CHAR_DATA * ch, OBJ_DATA * obj,
                   OBJ_DATA * container));
void show_list_to_char	args( ( OBJ_DATA *list, CHAR_DATA *ch, bool fShort, bool fShowNothing ) );

/* act_wiz.c */
/* act_wiz.c */
void wiznet args((char *string, CHAR_DATA * ch, OBJ_DATA * obj,
                  long flag, long flag_skip, int min_level));
void do_table args((CHAR_DATA * ch, char *argument));
void copyover_recover args((void));
/* locker.c */

//Joe:Lockers	Declaration for useful functions
OBJ_DATA *get_obj_locker_room args(( CHAR_DATA *ch, sh_int vnum ));
OBJ_DATA *get_locker args (( CHAR_DATA *ch));
/* bard.c */
int song_lookup args((const char *name));
void song_null args((int sn, int level, CHAR_DATA * ch, void *vo));
void check_song_improve args((CHAR_DATA * ch, int sn, bool success, int multiplier));
void song_update args((void));

/* bit.c */
extern const struct flag_type 	area_flags[];
extern const struct flag_type	sex_flags[];
extern const struct flag_type	exit_flags[];
extern const struct flag_type	door_resets[];
extern const struct flag_type	room_flags[];
extern const struct flag_type	sector_flags[];
extern const struct flag_type	type_flags[];
extern const struct flag_type	extra_flags[];
extern const struct flag_type	wear_flags[];
extern const struct flag_type	act_flags[];
extern const struct flag_type	affect_flags[];
extern const struct flag_type	apply_flags[];
extern const struct flag_type	wear_loc_strings[];
extern const struct flag_type	wear_loc_flags[];
extern const struct flag_type	weapon_flags[];
extern const struct flag_type	container_flags[];
extern const struct flag_type	liquid_flags[];

/* comm.c */
void show_string args((struct descriptor_data * d, char *input));
void close_socket args((DESCRIPTOR_DATA * dclose));
void write_to_buffer args((DESCRIPTOR_DATA * d, const char *txt,
                           int length));
void send_to_char args((const char *txt, CHAR_DATA * ch));
void page_to_char args((const char *txt, CHAR_DATA * ch));
void     printf_to_char      args( ( CHAR_DATA *, char *, ... ) );
void act args((const char *format, CHAR_DATA * ch,
               const void *arg1, const void *arg2, int type));
void act_new args((const char *format, CHAR_DATA * ch,
                   const void *arg1, const void *arg2, int type,
                   int min_pos));
void examine_last_command args((void));
void install_other_handlers args((void));
void send_to_room args((char* txt, ROOM_INDEX_DATA* room));
void nasty_signal_handler args((int no));
int		chprintf( CHAR_DATA* ch, const char *format, ... ); /* Added by Coy 1/03 */

/*
 * Color stuff by Lope of Loping Through The MUD
 */
int color args((char type, CHAR_DATA * ch, char *string));
void colorconv args((char *buffer, const char *txt, CHAR_DATA * ch));
void send_to_char_bw args((const char *txt, CHAR_DATA * ch));
void page_to_char_bw args((const char *txt, CHAR_DATA * ch));

/* diag.c */
void diag args((void));

/* db.c */
void reset_area args((AREA_DATA * pArea));
void	reset_room	args( ( ROOM_INDEX_DATA *pRoom ) );
char *print_flags args((int flag));
void boot_db args((void));
void area_update args((void));
CD *create_mobile args((MOB_INDEX_DATA * pMobIndex));
void clone_mobile args((CHAR_DATA * parent, CHAR_DATA * clone));
OD *create_object args((OBJ_INDEX_DATA * pObjIndex, int level));
void clone_object args((OBJ_DATA * parent, OBJ_DATA * clone));
void clear_char args((CHAR_DATA * ch));
void free_char args((CHAR_DATA * ch));
char *get_extra_descr args((const char *name, EXTRA_DESCR_DATA * ed));
MID *get_mob_index args((int vnum));
OID *get_obj_index args((int vnum));
RID *get_room_index args((int vnum));
char fread_letter args((FILE * fp));
int fread_number args((FILE * fp));
long fread_flag args((FILE * fp));
char *fread_string args((FILE * fp));
char *fread_string_eol args((FILE * fp));
void fread_to_eol args((FILE * fp));
char *fread_word args((FILE * fp));
long flag_convert args((char letter));
void *alloc_mem args((int sMem));
bool can_alloc_mem args((int sMem));
void *alloc_perm args((int sMem));
void free_mem args((void *pMem, int sMem));
char *str_dup args((const char *str));
void free_string args((char *pstr));
int number_fuzzy args((int number));
int number_range args((int from, int to));
int number_percent args((void));
int number_door args((void));
int number_bits args((int width));
int number_mm args((void));
int dice args((int number, int size));
int interpolate args((int level, int value_00, int value_32));
void smash_tilde args((char *str));
bool str_cmp args((const char *astr, const char *bstr));
bool str_prefix args((const char *astr, const char *bstr));
bool str_infix args((const char *astr, const char *bstr));
bool str_suffix args((const char *astr, const char *bstr));
char *capitalize args((const char *str));
void append_file args((CHAR_DATA * ch, char *file, char *str));
void bug args((const char *str, int param));
void log_string args((const char *str));
void tail_chain args((void));
CONTINENT *get_continent args((const char *continent_name));
HOMETOWN *get_hometown args((const char *hometown_name));
CLAN_LIST *get_clan args((const char * clan_name));
TRIBE_LIST *get_tribe args((const char * tribe_name));
int get_class_number args((const char * class_name));
AREA_DATA *get_area args((char * name));

/* db2.c */
void send_newbie args((  char *argument ));
void load_newbies args(( FILE * fp ));

/* fight.c */
bool is_safe args((CHAR_DATA * ch, CHAR_DATA * victim));
bool is_safe_spell args((CHAR_DATA * ch, CHAR_DATA * victim, bool area));
bool is_target_safe args((CHAR_DATA * ch, CHAR_DATA * victim));
bool is_area_safe args((CHAR_DATA * ch, CHAR_DATA * victim));
void violence_update args((void));
void multi_hit args((CHAR_DATA * ch, CHAR_DATA * victim, int dt));
bool damage args((CHAR_DATA * ch, CHAR_DATA * victim, int dam,
                  int dt, int class, bool show));
bool new_damage args((CHAR_DATA * ch, CHAR_DATA * victim, int dam,
                      int dt, int dam_type, int dam_mat,
                      int dam_pct, bool can_kill, bool show));
void update_pos args((CHAR_DATA * victim));
void stop_fighting args((CHAR_DATA * ch, bool fBoth));
bool break_hold args((CHAR_DATA * ch, int type));
void check_killer args((CHAR_DATA * ch, CHAR_DATA * victim));
int get_dive_percent(CHAR_DATA * ch, CHAR_DATA * victim);
void set_fighting args((CHAR_DATA * ch, CHAR_DATA * victim));
CHAR_DATA *attack_skill args((CHAR_DATA *ch, char *argument, int sn));
void skill_null args((CHAR_DATA *ch, char *argument));
bool chance args ( ( int num ) );


/* handler.c */
long wiznet_lookup args((const char *name));
int check_immune args((CHAR_DATA * ch, int dam_type));
int material_lookup args((const char *name));
int race_lookup args((const char *name));
int class_lookup args((const char *name));
char *  material_name   args( ( sh_int num ) );
bool is_old_mob args((CHAR_DATA * ch));
int get_skill args((CHAR_DATA * ch, int sn));
int get_weapon_sn args((CHAR_DATA * ch, bool secondary));
int get_weapon_skill args((CHAR_DATA * ch, int sn));
int get_age args((CHAR_DATA * ch));
void reset_char args((CHAR_DATA * ch));
int get_trust args((CHAR_DATA * ch));
int get_curr_stat args((CHAR_DATA * ch, int stat));
int get_max_train args((CHAR_DATA * ch, int stat));
int can_carry_n args((CHAR_DATA * ch));
int can_carry_w args((CHAR_DATA * ch));
bool is_name args((char *str, char *namelist));
bool is_exact_name args((char *str, char *namelist));
void affect_to_char args((CHAR_DATA * ch, AFFECT_DATA * paf));
void affect_to_obj args((OBJ_DATA * obj, AFFECT_DATA * paf));
void affect_remove args((CHAR_DATA * ch, AFFECT_DATA * paf));
void affect_modify args((CHAR_DATA * ch, AFFECT_DATA * paf, bool fAdd));
void affect_remove_obj args((OBJ_DATA * obj, AFFECT_DATA * paf));
void affect_strip args((CHAR_DATA * ch, int sn));
bool is_affected args((CHAR_DATA * ch, int sn));
void affect_join args((CHAR_DATA * ch, AFFECT_DATA * paf));
void char_from_room args((CHAR_DATA * ch));
void char_to_room args((CHAR_DATA * ch, ROOM_INDEX_DATA * pRoomIndex));
void obj_to_char args((OBJ_DATA * obj, CHAR_DATA * ch));
void obj_from_char args((OBJ_DATA * obj));
int apply_ac args((OBJ_DATA * obj, int iWear, int type));
OD *get_eq_char args((CHAR_DATA * ch, int iWear));
void equip_char args((CHAR_DATA * ch, OBJ_DATA * obj, int iWear));
void unequip_char args((CHAR_DATA * ch, OBJ_DATA * obj));
int count_obj_list args((OBJ_INDEX_DATA * obj, OBJ_DATA * list));
void obj_from_room args((OBJ_DATA * obj));
void obj_to_room args((OBJ_DATA * obj, ROOM_INDEX_DATA * pRoomIndex));
void obj_to_obj args((OBJ_DATA * obj, OBJ_DATA * obj_to));
void obj_from_obj args((OBJ_DATA * obj));
void extract_obj args((OBJ_DATA * obj));
void extract_char args((CHAR_DATA * ch, bool fPull));
CHAR_DATA *prog_char_room args( ( CHAR_DATA *ch, ROOM_INDEX_DATA *pRoom, char *argument ) );
/* CD *get_char_room args((CHAR_DATA * ch, char *argument));
 * Object and room progs - Coy 12/02
 * replaces above */
CD *    get_char_room		args( ( CHAR_DATA *ch, ROOM_INDEX_DATA *room, char *argument ) );

CD *get_char_world args((CHAR_DATA * ch, char *argument));
OD *get_obj_type args((OBJ_INDEX_DATA * pObjIndexData));
OD *get_obj_list args((CHAR_DATA * ch, char *argument,
                       OBJ_DATA * list));
OD *get_obj_carry args((CHAR_DATA * ch, char *argument, CHAR_DATA *viewer ));
OD *get_obj_carry_by_vnum args((CHAR_DATA * ch, int Vnum));

/* OD *get_obj_wear args((CHAR_DATA * ch, char *argument));
 * Object and room progs - Coy 12/02
 * replaces above */
OD *get_obj_wear	args( ( CHAR_DATA *ch, char *argument, bool character ));

/* OD *get_obj_here args((CHAR_DATA * ch, char *argument));
 * Object and room progs - Coy 12/02
 * replaces above */
OD *	get_obj_here	args( ( CHAR_DATA *ch, ROOM_INDEX_DATA *room, char *argument ) );

OD *get_obj_world args((CHAR_DATA * ch, char *argument));
OD *create_money args((int amount));
int get_obj_number args((OBJ_DATA * obj));
int get_obj_weight args((OBJ_DATA * obj));
int	get_true_weight	args( ( OBJ_DATA *obj ) );
bool remove_obj args((CHAR_DATA * ch, int iWear, bool fReplace));
bool room_is_dark args((ROOM_INDEX_DATA * pRoomIndex));
bool room_is_private args((ROOM_INDEX_DATA * pRoomIndex));
bool can_exit args((CHAR_DATA* ch, EXIT_DATA* pexit));
bool can_see args((CHAR_DATA * ch, CHAR_DATA * victim));
bool can_see_obj args((CHAR_DATA * ch, OBJ_DATA * obj));
bool can_see_room args((CHAR_DATA * ch, ROOM_INDEX_DATA * pRoomIndex));
bool can_drop_obj args((CHAR_DATA * ch, OBJ_DATA * obj));
char *item_type_name args((OBJ_DATA * obj));
char *affect_loc_name args((int location));
char *sector_type_name args((int type));
char *eq_affect_name args((int spell));
char *affect_bit_name args((int vector));
char *affect2_bit_name args((int vector));
char *extra_bit_name args((int extra_flags));
char *wear_bit_name args((int wear_flags));
char *act_bit_name args((int act_flags));
char *off_bit_name args((int off_flags));
char *imm_bit_name args((int imm_flags));
char *form_bit_name args((int form_flags));
char *part_bit_name args((int part_flags));
char *weapon_bit_name args((int weapon_flags));
char *comm_bit_name args((int comm_flags));
char *room_bit_name args((int type));
char *pc_only_bit_name args((int new_flags));
int get_ac args((CHAR_DATA * ch, int type));
void flagprint args((long flagvalue, CHAR_DATA * ch));
bool container_search args((OBJ_DATA * obj, int depth, int type));
char *flagstring args((long flagvalue));
void strip_rb_and_rm_items args(( CHAR_DATA * ch ));
int damage_class_to_bit args(( int dam_class ));


//doug.c
bool chances                args(( int num ));
bool bigchances             args(( int num ));
/* interp.c */
void interpret args((CHAR_DATA * ch, char *argument, int type));
bool is_number args((char *arg));
int number_argument args((char *argument, char *arg));
char *one_argument args((char *argument, char *arg_first));

/* Gquest.c */
bool    load_gquest_data args((void));
bool    save_gquest_data args((void));
void    auto_gquest args((void));
bool    start_gquest args((CHAR_DATA * ch, char *argument));
void    end_gquest args((void));
void    gquest_update args((void));
void    gquest_wait args((void));
bool    generate_gquest args((CHAR_DATA * who));
int     count_gqmobs args((CHAR_DATA * ch));
int     is_gqmob args((CHAR_DATA * ch, int vnum));
void    reset_gqmob args((CHAR_DATA * ch, int value));
bool    is_random_gqmob args((int vnum));
void do_mob_tell args((CHAR_DATA * ch, CHAR_DATA * victim, char *argument));

/* magic.c */
int mana_cost(CHAR_DATA * ch, int min_mana, int level);
int skill_lookup args((const char *name));
int slot_lookup args((int slot));
bool saves_spell args((int level, CHAR_DATA * victim));
void obj_cast_spell args((int sn, int level, CHAR_DATA * ch,
                          CHAR_DATA * victim, OBJ_DATA * obj));

/* magic2.c */
bool saves_bind args( (int level, CHAR_DATA * victim, CHAR_DATA * caster) );

/* note.c */
void load_notes args((void));
void system_note args((char *to, char *subject, char *text));

/* obj_room_cmds.c */
void obj_interpret	args( ( OBJ_DATA *obj, char *argument ) );
void room_interpret	args( ( ROOM_INDEX_DATA *room, char *argument ) );
int flag_lookup args( ( const char *word, const struct flag_type *flag_table ) );

/* obj_room_prog.c */
void	program_flow	args( ( sh_int vnum, char *source, CHAR_DATA *mob, 
				OBJ_DATA *obj, ROOM_INDEX_DATA *room,
				CHAR_DATA *ch, const void *arg1,
				const void *arg2 ) );
void	p_act_trigger	args( ( char *argument, CHAR_DATA *mob, 
				OBJ_DATA *obj, ROOM_INDEX_DATA *room,
				CHAR_DATA *ch, const void *arg1,
				const void *arg2, int type ) );
bool	p_percent_trigger args( ( CHAR_DATA *mob, OBJ_DATA *obj,
				ROOM_INDEX_DATA *room, CHAR_DATA *ch, 
				const void *arg1, const void *arg2, int type ) );
//void	p_bribe_trigger  args( ( CHAR_DATA *mob, CHAR_DATA *ch, int amount ) );
bool	p_exit_trigger   args( ( CHAR_DATA *ch, int dir, int type ) );
void	p_give_trigger   args( ( CHAR_DATA *mob, OBJ_DATA *obj, 
				ROOM_INDEX_DATA *room, CHAR_DATA *ch,
				OBJ_DATA *dropped, int type ) );
void 	p_greet_trigger  args( ( CHAR_DATA *ch, int type ) );
//void	p_hprct_trigger  args( ( CHAR_DATA *mob, CHAR_DATA *ch ) );

/* olc.c */
bool	run_olc_editor	args( ( DESCRIPTOR_DATA *d ) );
char	*olc_ed_name	args( ( CHAR_DATA *ch ) );
char	*olc_ed_vnum	args( ( CHAR_DATA *ch ) );

/* ROM OLC: */

extern const struct flag_type   material_type[];
extern const struct flag_type   form_flags[];
extern const struct flag_type   part_flags[];
extern const struct flag_type   ac_type[];
extern const struct flag_type   size_flags[];
extern const struct flag_type   off_flags[];
extern const struct flag_type   imm_flags[];
extern const struct flag_type   res_flags[];
extern const struct flag_type   vuln_flags[];
extern const struct flag_type   position_flags[];
extern const struct flag_type   weapon_class[];
extern const struct flag_type   weapon_type[];

/* save.c */
void save_char_obj args((CHAR_DATA * ch, bool savestats));
bool load_char_obj args((DESCRIPTOR_DATA * d, char *name));

/* skills.c */
bool parse_gen_groups args((CHAR_DATA * ch, char *argument));
void list_group_costs args((CHAR_DATA * ch));
void list_group_known args((CHAR_DATA * ch));
int exp_per_level args((CHAR_DATA * ch, int points));
void check_improve args((CHAR_DATA * ch, int sn, bool success,
                         int multiplier));
int group_lookup args((const char *name));
void gn_add args((CHAR_DATA * ch, int gn));
void gn_remove args((CHAR_DATA * ch, int gn));
void group_add args((CHAR_DATA * ch, const char *name, bool deduct));
void group_remove args((CHAR_DATA * ch, const char *name));
bool is_race_skill args((CHAR_DATA * ch, const char *name));
bool is_rb_skill args((const char *name));
bool is_tome_skill args((const char *name));
void remove_decoy_string args((CHAR_DATA * ch));
void reimburse_skills args((CHAR_DATA *ch));

/* smart.c */
ROOM_INDEX_DATA *scan_rooms args((CHAR_DATA * ch));

/* special.c */
SF *spec_lookup args((const char *name));
bool is_motorball args((int vnum));
void motorball_move_ball args((CHAR_DATA *ch, CHAR_DATA *victim));
void motorball_award_prize args((CHAR_DATA *winner, int circuit));
char *	spec_string	args( ( SPEC_FUN *fun ) );	/* OLC */

/* string.c */
void	string_edit	args( ( CHAR_DATA *ch, char **pString ) );
void    string_append   args( ( CHAR_DATA *ch, char **pString ) );
char *	string_replace	args( ( char * orig, char * old, char * new ) );
void    string_add      args( ( CHAR_DATA *ch, char *argument ) );
char *  format_string   args( ( char *oldstring /*, bool fSpace */ ) );
char *format_mprog_string(char *oldstring);
char *  first_arg       args( ( char *argument, char *arg_first, bool fCase ) );
char *	string_unpad	args( ( char * argument ) );
char *	string_proper	args( ( char * argument ) );

/* update.c */
void advance_level args((CHAR_DATA * ch));
void update_bonuses args((void));
void gain_exp args((CHAR_DATA * ch, int gain));
void gain_condition args((CHAR_DATA * ch, int iCond, int value));
void update_handler args((void));

/* drunk.c */
char *makedrunk args((char *string, CHAR_DATA * ch));

/* Ivan 2/2/99 Adding web page who list */
/* websvr.c */
void init_web(int port);
void handle_web(void);
void shutdown_web(void);

/* Ivan 2/18/99 The start of the great tablization project - hometowns */
/* tables.c */
void load_skill_table();
void save_skill_table();
void init_skill_table();
void load_hometown_table();
void save_hometown_table();
void load_clan_table();
void save_clan_table();
void load_tribe_table();
void save_tribe_table();
void load_continent_table();
void save_continent_table();
void load_class_table();
void save_class_table();
void load_race_table();
void save_race_table();
/* Coy 8/01 */
void load_song_table();
void save_song_table();
void init_song_table();
/* Object and room progs - Coy 12/02 */
extern const	struct	flag_type	affect_flags[];
extern const	struct	flag_type	off_flags[];
extern const	struct	flag_type	imm_flags[];
extern const	struct	flag_type	act_flags[];
extern const	struct	position_type	position_table[];
extern  const   struct  item_type	item_table	[];
extern  GQUEST                  gquest_info; //Added for Global Quests - Galius 4/16/2013
int	item_lookup	args( ( const char *name) );
int	position_lookup	args( (const char *name) );
PROG_CODE * get_prog_index args( ( int vnum, int type ) );





#undef  CD
#undef  MID
#undef  OD
#undef  OID
#undef  RID
#undef  SF


