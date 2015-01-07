#!/bin/bash

####################竞技场相关####################
lua GenerateCppCodeFromCCBFile.lua ccb/arena_index.ccb CcbArenaIndexLayer
lua GenerateCppCodeFromCCBFile.lua ccb/arena_rank.ccb CcbArenaRankLayer
lua GenerateCppCodeFromCCBFile.lua ccb/arena_battle.ccb CcbArenaBattleLayer

lua GenerateCppCodeFromCCBFile.lua ccb/arena_myinform.ccb CcbArenaMyInfoLayer
lua GenerateCppCodeFromCCBFile.lua ccb/arena_reward.ccb CcbArenaRewardLayer

lua GenerateCppCodeFromCCBFile.lua ccb/arena_fight_list.ccb CcbArenaFightListLayer


################################################