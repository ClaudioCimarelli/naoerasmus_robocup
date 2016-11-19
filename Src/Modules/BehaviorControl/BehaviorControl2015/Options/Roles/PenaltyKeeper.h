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
			  if(libCodeRelease.shootDetected)
				goto saveShot;
			}
			action
			{
			  theHeadControlMode = HeadControl::lookForward;
			}

	}

	state(saveShot){
		transition{
			if((state_time > 10000 && action_done)){
				Stand();
			}
		}
		action{
		if(std::abs(libCodeRelease.detectedShootDirection)<3_deg)
			SpecialAction(SpecialActionRequest::sitDown);
		else if (libCodeRelease.detectedShootDirection>=3_deg)
			SpecialAction(SpecialActionRequest::diveLeft);
		else
			SpecialAction(SpecialActionRequest::diveRight);

		}
	}

}
