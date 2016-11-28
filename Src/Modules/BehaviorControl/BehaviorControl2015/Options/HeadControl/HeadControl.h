option(HeadControl)
{
  common_transition
  {
    if(!theGroundContactState.contact && theGameInfo.state != STATE_INITIAL)
      goto lookForward;

    switch(theHeadControlMode)
    {
      case HeadControl::off: goto off;
      case HeadControl::lookForward: goto lookForward;
      case HeadControl::lookAround: goto lookAround;
      case HeadControl::lookAtBall: goto lookAtBall;
      default: goto none;
    }
  }

  initial_state(none) {}
  state(off) {action SetHeadPanTilt(JointAngles::off, JointAngles::off, 0.f);}
  state(lookForward) {action LookForward();}
  state(lookAround) {action LookAround();}
  state(lookAtBall) {action LookAtBall();}
}

struct HeadControl
{
  ENUM(Mode,
  {,
    none,
    off,
    lookForward,
    lookAround,
    lookAtBall,
  });
};

HeadControl::Mode theHeadControlMode = HeadControl::Mode::none; /**< The head control mode executed by the option HeadControl. */
