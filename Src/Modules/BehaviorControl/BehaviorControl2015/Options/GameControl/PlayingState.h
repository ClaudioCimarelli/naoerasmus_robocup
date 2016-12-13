option(PlayingState)
{
  initial_state(play)
  {
	transition{
		if(state_time > 6000){
				//theHeadControlMode = HeadControl::lookForward;
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
     if(Global::getSettings().isGoalkeeper)//else if(theRobotInfo.number==3)
    	 PenaltyKeeper();
     else if(theGameInfo.kickOffTeam == theOwnTeamInfo.teamNumber){
    	 PenaltyKicker();
     }
    }
  }
}
