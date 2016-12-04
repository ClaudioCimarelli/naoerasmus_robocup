option(PlayingState)
{
  initial_state(play)
  {
	transition{
		if(state_time > 150 || (state_time > 15000 && action_done)){
				theHeadControlMode = HeadControl::lookForward;
				goto selectRole;
		}
	}
	action
	      {

		if(theRobotInfo.number==3){
			//trying to get real pos for the kicker
			//TODO: use bootstrap method instead for the kicker to adjust is RobotPose
			//particularly lack in getting the right side of the field
			//const Pose2f tempPose (180_deg, -0.4f, 0.f);
			//theRobotPose = tempPose;
			//BootstrapPose();
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
