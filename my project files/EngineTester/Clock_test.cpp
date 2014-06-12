// for the Google test framework
#include <gtest\gtest.h>

// for the class under stest
#include <timing\clock.h>
using Timing::Clock;

// for Qt's "sleep" function
#include <Qt\qtest.h>

#include <iostream>
using std::cout;
using std::endl;

TEST(Clock, Initialize)
{
   Clock clock;
   EXPECT_TRUE(clock.initialize());
   EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, Frame_Time_Measuring)
{
   Clock clock;
   EXPECT_TRUE(clock.initialize());

   // start timing, wait for one second, get the elapsed time, and check that 
   // the fraction of the second that pased is ~1
   QTest::qSleep(1000);
   clock.new_frame();
   float timed_time = clock.time_elapsed_last_frame();
   EXPECT_TRUE(0.9f < timed_time);
   EXPECT_TRUE(timed_time < 1.1f);
   
   // do the same for a half second
   clock.new_frame();
   QTest::qSleep(500);
   clock.new_frame();
   timed_time = clock.time_elapsed_last_frame();
   EXPECT_TRUE(0.4f < timed_time);
   EXPECT_TRUE(timed_time > 0.6f);


   // now check various random times
   const int NUM_TESTS = 10 + (rand() % 100);
   const float THRESHOLD = 0.1f;
   cout << "running '" << NUM_TESTS <<
      "' tests with threshold = '" << THRESHOLD << "'" << endl;
   for (int count = 0; count < NUM_TESTS; count += 1)
   {
      int this_test_milliseconds = rand() % 10000;
      float this_test_seconds = this_test_milliseconds / 1000.0f;

      cout << "test '" << count << "' of '" << NUM_TESTS << "'; " <<
         "sleeping for '" << this_test_seconds << "'" << endl;

      // reset the timer, sleep, and measure delta time
      clock.new_frame();
      QTest::qSleep(this_test_milliseconds);
      clock.new_frame();
      float elapsed_seconds = clock.time_elapsed_last_frame();
      EXPECT_TRUE((this_test_seconds - THRESHOLD) < elapsed_seconds);
      EXPECT_TRUE((this_test_seconds + THRESHOLD) > elapsed_seconds);
   }

   EXPECT_TRUE(clock.shutdown());
}