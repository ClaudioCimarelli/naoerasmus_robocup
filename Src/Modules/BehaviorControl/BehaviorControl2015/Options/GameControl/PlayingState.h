option(PlayingState)
{
  initial_state(play)
  {
	transition{
		if(state_time > 7000 && std::abs(libCodeRelease.angleToGoal) < 3_deg)
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
     if(std::abs(libCodeRelease.distanceToOwnGoal) < 300.f)
    	 PenaltyKeeper();
     else
    	 PenaltyKicker();
    }
  }
}
