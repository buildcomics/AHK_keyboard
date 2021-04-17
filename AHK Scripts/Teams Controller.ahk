#UseHook
F14::
;#HotkeyInterval 200

WinGet, active_id, ID, A
SetTitleMatchMode, 2
;DetectHiddenWindows, On
WinGet, fensterID, List, ahk_exe Teams.exe
Loop, %fensterID% { ; will run loop for number of windows in array
  WinActivate, % "ahk_id " fensterID%A_Index%
  Send ^+m
  break
}
WinActivate, ahk_id %active_id%
Return

F15::
;#HotkeyInterval 200

WinGet, active_id, ID, A
SetTitleMatchMode, 2
;DetectHiddenWindows, On
WinGet, fensterID, List, ahk_exe Teams.exe
Loop, %fensterID% { ; will run loop for number of windows in array
  WinActivate, % "ahk_id " fensterID%A_Index%
  Send ^+o
  break
}
WinActivate, ahk_id %active_id%
Return

F16::
Send ^+a

F17::
Send ^+d

; Loop adapted from: https://autohotkey.com/board/topic/29871-cycling-through-all-windows-that-match-wintitle/
; Script adapted from: https://www.lprp.fr/2020/03/keyboard-shortcut-to-mute-teams-with-autohotkey/