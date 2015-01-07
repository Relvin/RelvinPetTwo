#!/bin/bash

####################邮件相关####################
lua GenerateCppCodeFromCCBFile.lua ccb/box_reward_frame.ccb CcbBoxRewardFrame
lua GenerateCppCodeFromCCBFile.lua ccb/mail_frame.ccb CcbMailFrameLayer
lua GenerateCppCodeFromCCBFile.lua ccb/mail_text.ccb CcbMailDetailLayer
lua GenerateCppCodeFromCCBFile.lua ccb/mail_list.ccb CcbMailListLayer

################################################