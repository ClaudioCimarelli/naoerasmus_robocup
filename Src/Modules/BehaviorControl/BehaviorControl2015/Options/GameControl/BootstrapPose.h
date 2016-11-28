option(BootstrapPose)
{
  initial_state(setRequest)
  {
	transition{
		if(state_time > 20000 && std::abs(libCodeRelease.angleToGoal) < 2_deg)
				goto requestIsExecuted;
	}
	action
	      {
	        theHeadControlMode = HeadControl::lookAround;
	        WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));
	      }
  }
  /** The motion process has started executing the request. */
  target_state(requestIsExecuted)
  {
    transition
    {
      if(std::abs(libCodeRelease.angleToGoal) > 2_deg)
        goto setRequest;
    }
    action
    {
    	theHeadControlMode = HeadControl::lookAround;
    }
  }
}
