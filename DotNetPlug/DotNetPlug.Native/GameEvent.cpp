#include "GameEvent.h"
#include <stdio.h>

const char* const g_CSGO_EventNames[] = {
	//0-4
	NULL,
	"player_death",
	"player_hurt",
	"item_purchase",
	"bomb_beginplant",

	"bomb_abortplant",
	"bomb_planted",
	"bomb_defused",
	"bomb_exploded",
	"bomb_dropped",

	"bomb_pickup",
	"defuser_dropped",
	"defuser_pickup",
	"announce_phase_end",
	"cs_intermission",

	"bomb_begindefuse",
	"bomb_abortdefuse",
	"hostage_follows",
	"hostage_hurt",
	"hostage_killed",

	"hostage_rescued",
	"hostage_stops_following",
	"hostage_rescued_all",
	"hostage_call_for_help",
	"vip_escaped",

	"vip_killed",
	"player_radio",
	"bomb_beep",
	"weapon_fire",
	"weapon_fire_on_empty",

	"weapon_outofammo",
	"weapon_reload",
	"weapon_zoom",
	"silencer_detach",
	"inspect_weapon",

	"weapon_zoom_rifle",
	"player_spawned",
	"item_pickup",
	"ammo_pickup",
	"item_equip",

	"enter_buyzone",
	"exit_buyzone",
	"buytime_ended",
	"enter_bombzone",
	"exit_bombzone",

	"enter_rescue_zone",
	"exit_rescue_zone",
	"silencer_off",
	"silencer_on",
	"buymenu_open",

	"buymenu_close",
	"round_prestart",
	"round_poststart",
	"round_start",
	"round_end",

	"grenade_bounce",
	"hegrenade_detonate",
	"flashbang_detonate",
	"smokegrenade_detonate",
	"smokegrenade_expired",

	"molotov_detonate",
	"decoy_detonate",
	"decoy_started",
	"inferno_startburn",
	"inferno_expire",

	"inferno_extinguish",
	"decoy_firing",
	"bullet_impact",
	"player_footstep",
	"player_jump",

	"player_blind",
	"player_falldamage",
	"door_moving",
	"round_freeze_end",
	"mb_input_lock_success",

	"mb_input_lock_cancel",
	"nav_blocked",
	"nav_generate",
	"player_stats_updated",
	"achievement_info_loaded",

	"spec_target_updated",
	"spec_mode_updated",
	"hltv_changed_mode",
	"cs_game_disconnected",
	"cs_win_panel_round",

	"cs_win_panel_match",
	"cs_match_end_restart",
	"cs_pre_restart",
	"show_freezepanel",
	"hide_freezepanel",

	"freezecam_started",
	"player_avenged_teammate",
	"achievement_earned",
	"achievement_earned_local",
	"item_found",

	"item_gifted",
	"repost_xbox_achievements",
	"match_end_conditions",
	"round_mvp",
	"player_decal",

	"teamplay_round_start",
	"client_disconnect",
	"gg_player_levelup",
	"ggtr_player_levelup",
	"ggprogressive_player_levelup",

	"gg_killed_enemy",
	"gg_final_weapon_achieved",
	"gg_bonus_grenade_achieved",
	"switch_team",
	"gg_leader",

	"gg_player_impending_upgrade",
	"write_profile_data",
	"trial_time_expired",
	"update_matchmaking_stats",
	"player_reset_vote",

	"enable_restart_voting",
	"sfuievent",
	"start_vote",
	"player_given_c4",
	"gg_reset_round_start_sounds",

	"tr_player_flashbanged",
	"tr_highlight_ammo",
	"tr_mark_complete",
	"tr_mark_best_time",
	"tr_exit_hint_trigger",

	"bot_takeover",
	"tr_show_finish_msgbox",
	"tr_show_exit_msgbox",
	"reset_player_controls",
	"jointeam_failed",

	"teamchange_pending",
	"material_default_complete",
	"cs_prev_next_spectator",
	"cs_handle_ime_event",
	"nextlevel_changed",

	"seasoncoin_levelup",
	"tournament_reward",
	"start_halftime",

	NULL //MAX
};