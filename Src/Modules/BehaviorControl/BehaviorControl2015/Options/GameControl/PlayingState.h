option(PlayingState)
{
  initial_state(play)
  {
	transition{
		if(state_time > 15000 && std::abs(libCodeRelease.angleToGoal) < 3_deg)
				theHeadControlMode = HeadControl::lookForward;
				goto selectRole;
	}
	action
	      {
		if(theRobotInfo.number==3){
			//trying to get real pos for the kicker
			//TODO: use bootstrap method instead for the kicker to adjust is RobotPose
			//particularly lack in getting the right side of the field
			theHeadControlMode = HeadControl::lookAround;
			WalkAtSpeedPercentage(Pose2f(1.f, 0.f, 0.f));
			}
	     }
  }
  state(selectRole){
    action
    {
     if(theRobotInfo.number==1)
    	 PenaltyKeeper();
     else if(theRobotInfo.number==3){
    	 PenaltyKicker();
     }
    }
  }
}
