#!/bin/bash

####################道具物品相关####################
lua GenerateCppCodeFromCCBFile.lua ccb/item_inform.ccb CcbItemInfoLayer
lua GenerateCppCodeFromCCBFile.lua ccb/item_list.ccb CcbItemListLayer
lua GenerateCppCodeFromCCBFile.lua ccb/item_icon.ccb CcbItemIconLayer

##################################################


####################技能升级界面####################
lua GenerateCppCodeFromCCBFile.lua ccb/skill_enhance.ccb CcbSkillEnhanceLayer
lua GenerateCppCodeFromCCBFile.lua ccb/skill_enhance_result.ccb CcbSkillEnhanceResultLayer

###################################################