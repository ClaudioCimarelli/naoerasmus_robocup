option(PlayingState)
{
  initial_state(play)
  {
	transition{
		if(state_time > 10000)
				goto selectRole;
	}
	action
	      {
	        theHeadControlMode = HeadControl::lookForward;
	        WalkAtSpeedPercentage(Pose2f(1.f, 0.f, 0.f));
	      }
  }
  state(selectRole){
    action
    {
     if(std::abs(libCodeRelease.distanceToOwnGoal) < 500.f)
    	 PenaltyKeeper();
     else
    	 PenaltyKicker();
    }
  }
}
