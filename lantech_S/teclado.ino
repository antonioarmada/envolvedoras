
void keypadEvent(KeypadEvent customKey){
  if (customKeypad.getState()== HOLD) {
    Tx_Msg(customKey);
    printDebug("HOLDEVENT:",String(customKey));
  }
}


