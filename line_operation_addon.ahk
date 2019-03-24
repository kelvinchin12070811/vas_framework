^m::
	Send, {Right}{Right}{Right}{Backspace}{Backspace}
	Send, **
	Send, {End}{Space}
	Send, */
	return
	
^+m::
	InputBox, lineHeight, Enter Line Height, Please enter line height
	if (lineHeight < 1)
		return
	itr = 0
	Send, {Home}{Right}{Right}{Right}{Delete}{Enter}
	Send, {Space}*{Space}
	while (itr < lineHeight - 1)
	{
		Send, {Down}{Home}
		Send, {Shift down}{Up}{End}{Shift up}
		Send, {Backspace}{Enter}
		Send, *{Space}
		itr += 1
	}
	Send, {Down}{Home}{Space}
	return
	
^+c::
	Send, {Ctrl down}{Left}{Left}{Left}{Left}{Left}{Ctrl up}
	Send, {Ctrl down}{Shift down}{Left}{Shift up}{Ctrl up}
	Send, ^c
	send, {End}{Space}
	Send, /**< @throw std::logic_error if datatype is not
	Send, {Space}
	Send, ^v
	Send, {Space}*
	return
	
::mut::
	Send, {Shift down}{Home}{Shift up}
	Send, {Raw}* ####Mutators
	return

::acc::
	Send, {Shift down}{Home}{Shift up}
	Send, {Raw}* ####Accessors
	return

^+Enter::
	Send, {Enter}*{Space}
	return
	
^+Backspace::
	Send, {End}{Shift down}{up}{End}{Shift up}{Delete}
