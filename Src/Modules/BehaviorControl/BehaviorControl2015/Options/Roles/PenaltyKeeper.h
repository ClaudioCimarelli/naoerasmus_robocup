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

		SpecialAction(SpecialActionRequest::sitDown);

	}

	state(saveShot){

	}
}
