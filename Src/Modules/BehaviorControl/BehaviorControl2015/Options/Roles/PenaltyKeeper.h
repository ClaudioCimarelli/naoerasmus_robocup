option(PenaltyKeeper) {
	initial_state(start) {
		transition
		    {
		      if(state_time > 1000)
		        goto detectShot;
		    }
		    action
		    {
		      theHeadControlMode = HeadControl::lookForward;
		      Stand();
		    }
	}

	state(detectShot){
		transition
			{
			  if(state_time > 1000)
				goto saveShot;
			}
			action
			{
			  theHeadControlMode = HeadControl::lookForward;

			}

	}

	state(saveShot){

		SpecialAction(SpecialActionRequest::sitDown);

	}
}
