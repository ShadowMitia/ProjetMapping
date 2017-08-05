
#ifdef tot

#pragma once

#include "ofMain.h"
#include "Avatar.h"
#include "wiiuse.h"

class Wiimotes : public ofThread {

  using Wiimote = struct wiimote_t;

  std::vector<Avatar>& players;

public:

  Wiimotes(unsigned int MAX_WIIMOTES, std::vector<Avatar>& players) : players(players){
    max_wiimotes = MAX_WIIMOTES;
    wiimotes = wiiuse_init(MAX_WIIMOTES);
    found = wiiuse_find(wiimotes, MAX_WIIMOTES, 5);

    if (!found)
      {
	std::cout << "No wiimotes found\n";
      }

    connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);

    // wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
    // wiiuse_set_leds(wiimotes[1], WIIMOTE_LED_2);
    // wiiuse_set_leds(wiimotes[2], WIIMOTE_LED_3);
    // wiiuse_set_leds(wiimotes[3], WIIMOTE_LED_4);

  }

  ~Wiimotes()
  {
    wiiuse_cleanup(wiimotes, max_wiimotes);
  }


  short any_wiimote_connected(Wiimote** wm, int wiimotes)
  {
    int i;
    if (!wm) {
      return 0;
    }

    for (i = 0; i < wiimotes; i++) {
      if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
	return 1;
      }
    }

    return 0;
  }

  void threadedFunction()
  {
    while (isThreadRunning())
      {
	//while (any_wiimote_connected(wiimotes, max_wiimotes)) {
	if (wiiuse_poll(wiimotes, max_wiimotes)) {
	  /*
	   *	This happens if something happened on any wiimote.
	   *	So go through each one and check if anything happened.
	   */
	  for (int i = 0; i < connected; ++i) {
	    switch (wiimotes[i]->event) {
	    case WIIUSE_EVENT:
	      /* a generic event occurred */
	      handle_event(wiimotes[i], i);
	      break;

	    case WIIUSE_STATUS:
	      /* a status event occurred */
	      handle_ctrl_status(wiimotes[i]);
	      break;

	    case WIIUSE_DISCONNECT:
	    case WIIUSE_UNEXPECTED_DISCONNECT:
	      /* the wiimote disconnected */
	      std::cout << "WIIMOTE " << wiimotes[i]->unid << " DISCONNECTED\n";
	      break;

	    case WIIUSE_READ_DATA:
	      /*
	       *	Data we requested to read was returned.
	       *	Take a look at wiimotes[i]->read_req
	       *	for the data.
	       */
	      break;

	    case WIIUSE_NUNCHUK_INSERTED:
	      /*
	       *	a nunchuk was inserted
	       *	This is a good place to set any nunchuk specific
	       *	threshold values.  By default they are the same
	       *	as the wiimote.
	       */
	      /* wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f); */
	      /* wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100); */
	      printf("Nunchuk inserted.\n");
	      break;

	    case WIIUSE_MOTION_PLUS_ACTIVATED:
	      printf("Motion+ was activated\n");
	      break;

	    case WIIUSE_NUNCHUK_REMOVED:
	    case WIIUSE_MOTION_PLUS_REMOVED:
	      handle_ctrl_status(wiimotes[i]);
	      printf("An expansion was removed.\n");
	      break;

	    default:
	      break;
	    }
	  }
	}
	//}
      }
  }


  Wiimote** wiimotes;

  int found, connected;

  void handle_ctrl_status(Wiimote* wm) {
    printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

    printf("attachment:      %i\n", wm->exp.type);
    printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
    printf("ir:              %i\n", WIIUSE_USING_IR(wm));
    printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
    printf("battery:         %f %%\n", wm->battery_level);
  }

  void handle_read(Wiimote* wm, byte* data, unsigned short len) {
    printf("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
    printf("finished read of size %i\n", len);
    for (int i = 0; i < len; ++i) {
      if (!(i % 16)) {
	printf("\n");
      }
      printf("%x ", data[i]);
    }
    printf("\n\n");
  }

  void handle_event(Wiimote* wm, int player) {
    printf("\n\n--- EVENT [id %i, player %i] ---\n", wm->unid, player);

    /* if a button is pressed, report it */
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
      printf("A pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
      printf("B pressed\n");

    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
      printf("UP pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN))	{
      printf("DOWN pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	{
      printf("LEFT pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	{
      printf("RIGHT pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	{
      printf("MINUS pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	{
      printf("PLUS pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
      printf("ONE pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
      printf("TWO pressed\n");
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	{
      printf("HOME pressed\n");
    }

    /*
     *	Pressing minus will tell the wiimote we are no longer interested in movement.
     *	This is useful because it saves battery power.
     */
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) {
      wiiuse_motion_sensing(wm, 0);
    }

    /*
     *	Pressing plus will tell the wiimote we are interested in movement.
     */
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) {
      wiiuse_motion_sensing(wm, 1);
    }

    /*
     *	Pressing B will toggle the rumble
     *
     *	if B is pressed but is not held, toggle the rumble
     */
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
      players[player].jump();
    }

    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
      players[player].goingLeft(true);
    }

    if (IS_RELEASED(wm, WIIMOTE_BUTTON_UP)) {
      players[player].goingLeft(false);
    }

    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
      players[player].goingRight(true);
    }

    if (IS_RELEASED(wm, WIIMOTE_BUTTON_DOWN)) {
      players[player].goingRight(false);
    }

  }


private:
  int max_wiimotes;

};

#endif