/** Pun intended. Looks straight ahead in a way that the Nao V4's cameras cover the area in front of its feet as well as everything else in front of the robot.*/
option(LookAround, (float) (0.5f) pan, (float) (0.15f) tilt)
{
  /** Simply sets the necessary angles */
  initial_state(lookAroundLeft)
  {
	transition{
		if(action_done)
			goto lookAroundRight;
	}
    action
    {
      SetHeadPanTilt(pan, tilt, 10_deg);
    }
  }

  state(lookAroundRight)
    {
  	transition{
  		if(action_done)
  			goto lookAroundLeft;
  	}
      action
      {
        SetHeadPanTilt(-pan, tilt, 10_deg);
      }
    }
}
