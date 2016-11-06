option(PlayingState)
{
  initial_state(play)
  {

    action
    {
     if(std::abs(libCodeRelease.distanceToOwnGoal) < 3_deg)
    	 PenaltyKeeper();
     else
    	 PenaltyKicker();
    }
  }
}
