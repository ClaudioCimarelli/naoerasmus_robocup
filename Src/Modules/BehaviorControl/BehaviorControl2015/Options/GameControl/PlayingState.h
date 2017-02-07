option(PlayingState)
{
  initial_state(play)
  {
	transition{
		if(state_time > 1000){
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
	 if((theRobotInfo.number==2) ){
				KickerSupport();
			 }
     else if((theRobotInfo.number==3) || theGameInfo.kickOffTeam == theOwnTeamInfo.teamNumber){
    	 PenaltyKicker();
     }
     else if(theRobotInfo.number==1 || (Global::getSettings().isGoalkeeper))
    	 PenaltyKeeper();
    }
  }
}
