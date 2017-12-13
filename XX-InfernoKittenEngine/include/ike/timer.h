#ifndef IKE_TIMER_H
#define IKE_TIMER_H

/**
 * \brief Updates global timer values.
 *
 * Use this to update ellapsed, delta, current frame and last frame times,
 * usually called when updating presenter.
 */
void ikeGlobalTimerUpdate();

/**
 * \brief Returns the global delta time.
 */
double ikeDeltaTime();

/**
 * \brief Returns the global ellapsed time.
 */
double ikeEllapsedTime();

#endif /* IKE_TIMER_H */
