// Copyright 2024 Wilson Liang
#include <gtest/gtest.h>

#include "MyApp.h"
// Demonstrate some basic assertions.
TEST(MyAppUnitTests, DatabaseSavingAndRead) {
  MyApp app = MyApp();
  app.run("setup");
  app.onTermination();
  app.run("read");
  MyApp app1 = MyApp();
  app1.run("setup");
  MyFileDatabase* db = app.getDatabase();
  MyFileDatabase* db1 = app1.getDatabase();
  for (auto dpitem : db->getDepartmentMapping()) {
    EXPECT_EQ(dpitem.second, db1->getDepartmentMapping()[dpitem.first]);
  }
}
TEST(MyAppUnitTests, Override) {
  MyFileDatabase* db = new MyFileDatabase(1, "");
  MyApp app = MyApp();
  std::string deptCode = "COMS";
  std::map<std::string, std::shared_ptr<Course>> courses;
  std::string departmentChair = "Jacky";
  int numberOfMajors = 5;
  std::shared_ptr<Course> coms3311 = std::make_shared<Course>(
      250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  coms3311->setEnrolledStudentCount(100);
  courses["3311"] = coms3311;
  Department tempDepartment =
      Department(deptCode, courses, departmentChair, numberOfMajors);
  std::map<std::string, Department> Depart;
  Depart["COMS"] = tempDepartment;
  db->setMapping(Depart);
  MyApp::overrideDatabase(db);

  EXPECT_EQ(Depart, app.getDatabase()->getDepartmentMapping());
}
