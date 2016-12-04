option(PlayingState)
{
  initial_state(play)
  {
	transition{
		if(state_time > 5000){
				theHeadControlMode = HeadControl::lookForward;
				goto selectRole;
		}
	}
	action
	      {
			theHeadControlMode = HeadControl::lookAround;
	     }
  }

  state(selectRole){
    action
    {
     if(Global::getSettings().isGoalkeeper)
    	 PenaltyKeeper();
     else if(theGameInfo.kickOffTeam == theOwnTeamInfo.teamNumber){
    	 PenaltyKicker();

     }
    }
  }
}
