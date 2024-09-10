// Copyright 2024 Wilson Liang
#include <gtest/gtest.h>

#include "MyFileDatabase.h"
// Demonstrate some basic assertions.
TEST(MyFileDataBaseUnitTests, DisplayFunction) {
  std::string times[] = {"11:40-12:55", "4:10-5:25", "10:10-11:25",
                         "2:40-3:55"};
  std::string locations[] = {"417 IAB", "309 HAV", "301 URIS"};
  std::map<std::string, std::shared_ptr<Course>> courses;
  auto econ1105 =
      std::make_shared<Course>(210, "Waseem Noor", locations[1], times[3]);
  econ1105->setEnrolledStudentCount(187);
  courses["1105"] = econ1105;

  Department econ("ECON", courses, "Michael Woodford", 2345);
  std::map<std::string, Department> mapping;
  mapping["ECON"] = econ;
  MyFileDatabase db(1, "database.bin");
  db.setMapping(mapping);
  std::string expectOutput =
      "For the ECON department:\nECON 1105: \nInstructor: Waseem Noor; "
      "Location: 309 HAV; Time: 2:40-3:55\n\n";
  EXPECT_EQ(db.display(), expectOutput);
}

TEST(MyFileDataBaseUnitTests, DatabaseSavingAndRead) {
  std::string times[] = {"11:40-12:55", "4:10-5:25", "10:10-11:25",
                         "2:40-3:55"};
  std::string locations[] = {"417 IAB", "309 HAV", "301 URIS"};
  std::map<std::string, std::shared_ptr<Course>> courses;
  auto econ1105 =
      std::make_shared<Course>(210, "Waseem Noor", locations[1], times[3]);
  econ1105->setEnrolledStudentCount(187);
  courses["1105"] = econ1105;

  Department econ("ECON", courses, "Michael Woodford", 2345);
  std::map<std::string, Department> mapping;
  mapping["ECON"] = econ;
  MyFileDatabase db(1, "database.bin");
  db.setMapping(mapping);
  db.saveContentsToFile();
  MyFileDatabase db1(0, "database.bin");
  for (auto dpitem : db.getDepartmentMapping()) {
    EXPECT_EQ(dpitem.second, db1.getDepartmentMapping()[dpitem.first]);
  }
}
