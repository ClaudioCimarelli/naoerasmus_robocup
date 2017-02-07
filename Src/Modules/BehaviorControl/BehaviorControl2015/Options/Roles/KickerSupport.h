/** Kicker Support - task kick goal after penelaty kicker */
option(KickerSupport) {
    
    initial_state(start){
        transition {
            if(libCodeRelease.timeSinceBallWasSeen() < 200 && state_time>7000)
                goto turnToBall;
        }
        action {
        	//theHeadControlMode = HeadControl::lookForward;
        	if(libCodeRelease.timeSinceBallWasSeen() < 900 && state_time>5500)
        		LookAtBall();
        	else
        		LookAround(0.1f, 0.5f);
            //Stand();
        }
    }

    // Striker turns to the ball's direction
    state(turnToBall)
    {
      transition
      {
        if (std::abs(theBallModel.estimate.position.y()) < 120.f) // If the ball is in front of the robot
          goto walkToBall; // Striker can walk to the ball
      }
      action
      {
        theHeadControlMode = HeadControl::lookAtBall; // Robot keeps his head looking forward
        WalkToTarget( Pose2f(40.f, 0.f, 0.f)  // Robot rotates to the ball's position
                    , Pose2f(theBallModel.estimate.position.angle()
                    , 0.f, 0.f));
      }
    }

        
    state(walkToBall) {
        transition {
        	if(theBallModel.estimate.position.x() < 750.f)
				goto alignBehindGoal;
        	if (std::abs(theBallModel.estimate.position.y()) > 120.f)
        		goto turnToBall;
        }
        action {
            //theHeadControlMode = HeadControl::lookAtBall;
        	LookAround(0.f, 0.2f);
            WalkToTarget(Pose2f(0.f,20.f,20.f), Pose2f(0.f, theBallModel.estimate.position.x(), theBallModel.estimate.position.y() + 110));
        }
    }

    state(turnRight) {
    		transition {
    			if(state_time>3500)
    				goto alignBehindBallRight;
    			if(theBallModel.estimate.position.x() > 950.f){
    				goto walkToBall;
    			}
    			if(libCodeRelease.timeSinceBallWasSeen() > 1200)
    				goto searchForBall;
    		}
    		action {
    			theHeadControlMode = HeadControl::lookAtBall;
    			//LookAround(0.1f, 0.6f);
    			WalkToTarget( Pose2f(30.f, 0.f, 10.f), Pose2f(35_deg, 0.f, 250.f));
    		}
    	}




    state(alignBehindGoal) {
		transition {
			if(std::abs(libCodeRelease.angleToGoal) < 35_deg && theBallModel.estimate.position.y() < 200)
				goto alignBehindBallRight;
			if(theBallModel.estimate.position.x() > 950.f){
				goto walkToBall;
			}
			if(libCodeRelease.timeSinceBallWasSeen() > 1200)
				goto searchForBall;
		}
		action {
			theHeadControlMode = HeadControl::lookAtBall;
			//LookAround(0.1f, 0.6f);
			WalkToTarget( Pose2f(1.f, 5.f, 15.f), Pose2f(libCodeRelease.angleToGoal + 25_deg, 0.f, theBallModel.estimate.position.y() + 160.f));
		}
	}

    state(alignBehindBallRight) {
            transition {
            	if(libCodeRelease.between(theBallModel.estimate.position.y(), 50.f, 55.f)
            	                && libCodeRelease.between(theBallModel.estimate.position.x(), 160.f, 170.f))
            	                goto kickRight;
            	if(theBallModel.estimate.position.x() > 850.f){
            		goto walkToBall;
            	}

            }
            action {
            	/*if (std::abs(theBallModel.estimate.position.angle()) > 10_deg)
            		WalkToTarget(Pose2f(40.f, 0.f, 0.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
    			//theHeadControlMode = HeadControl::lookAtBall;*/
            	WalkToTarget(Pose2f(0.f, 10.f, 10.f), Pose2f(0.f, theBallModel.estimate.position.x() - 165.f, theBallModel.estimate.position.y() - 53.f));
                }
        }

        
    state(kickRight) {
        transition {
        	if((theBallModel.estimate.position.x() > 400.f && (libCodeRelease.shootDetected)) || (state_time>4000))
				goto wait;
			if(libCodeRelease.between(theBallModel.estimate.position.x(), 170.f,400.f) && !(libCodeRelease.shootDetected)&& (state_time>1400))
				goto walkToBall;
			if(libCodeRelease.timeSinceBallWasSeen() > 1200)
				goto searchForBall;
        }
        action {
            theHeadControlMode = HeadControl::lookAtBall;
            //InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal - 25_deg, theBallModel.estimate.position.x() - 100.f, theBallModel.estimate.position.y() - 145.f));
            InWalkKick(WalkRequest::left, Pose2f(0.f, theBallModel.estimate.position.x() + 155.f, theBallModel.estimate.position.y() - 50.f));
        }
    }


    state(searchForBall) {
        transition {
            if(libCodeRelease.timeSinceBallWasSeen() < 500)
                goto turnToBall;
        }
        action {
        	if(state_time > 6000)
        		WalkAtSpeedPercentage(Pose2f(0.3f, 0.f, 0.f));
            theHeadControlMode = HeadControl::none;
            LookAround(0.2f);
        }
    }

        
    state(wait) {
        transition {
            if(libCodeRelease.timeSinceBallWasSeen() > 2000)
                goto searchForBall;
        }
        action {
        	Stand();
            theHeadControlMode = HeadControl::lookForward;
        }
    }
    
}
