option(PenaltyKeeper) {
	float shootAngle = 0.f;

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
			  if(action_done)
				goto saveShot;
			}
			action
			{
			  theHeadControlMode = HeadControl::lookForward;
			  shootAngle = 0_deg;
			  //TODO:detect ball movement
			  //save direction and send to saveshot

			}

	}

	state(saveShot){
		if(shootAngle<3_deg && shootAngle>-3_deg)
			SpecialAction(SpecialActionRequest::sitDown);
		else if (shootAngle>=3_deg)
			SpecialAction(SpecialActionRequest::sitDown);
		else
			SpecialAction(SpecialActionRequest::sitDown);


	}
}
