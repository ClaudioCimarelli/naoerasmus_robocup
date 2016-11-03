/* 
 * File:   PenaltyKicker.h
 * Author: leandrogil
 *
 * Created on November 3, 2016, 1:33 PM
 *
 * A behaviour that represents a penalty kicker to be used during penalty kicks
 */

option(PenaltyKicker) {
    initial_state(start) {
        transition {
            if(state_time > 1000)
                goto alignToGoal;
        }
        action {
            theHeadControlMode = HeadControl::lookForward;
            Stand();
        }
    }
    
    state(alignToGoal) {
        transition {
            if(action_done)
                goto kick;
        }
        action {
            /* TODO: make the robot align to a spot on the goal that the keeper is not guarding */
            /* TODO: test it! */
            theHeadControlMode = HeadControl::lookForward;
            WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
        }
    }
    
    state(kick) {
        transition {
            if(state_time > 3000 || (state_time > 10 && action_done))
                goto start;
        }
        action {
            Annotation("Alive and Kickin'");
            theHeadControlMode = HeadControl::lookForward;
            InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
        }
    }
}


