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
			  if(state_time>1000)
				goto saveShot;
			}
			action
			{
			  theHeadControlMode = HeadControl::lookForward;
			  libCodeRelease.shootAngle = 2_deg;
			  //TODO:detect ball movement
			  //save direction and send to saveshot
			}

	}

	state(saveShot){
		transition{
			if(state_time > 3000 || (state_time > 10 && action_done)){
				goto wait;
			}
		}
		action{
		if(std::abs(libCodeRelease.shootAngle)<3_deg)
			SpecialAction(SpecialActionRequest::sitDown);
		else if (libCodeRelease.shootAngle>=3_deg)
			SpecialAction(SpecialActionRequest::fallLeft);
		else
			SpecialAction(SpecialActionRequest::sitDown);

		}
	}

	 state(wait){
		  action{
			  theHeadControlMode = HeadControl::lookForward;

		  }
	  }
}
