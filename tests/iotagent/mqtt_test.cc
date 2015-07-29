/**
* Copyright 2015 Telefonica Investigación y Desarrollo, S.A.U
*
* This file is part of iotagent project.
*
* iotagent is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published
* by the Free Software Foundation, either version 3 of the License,
* or (at your option) any later version.
*
* iotagent is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with iotagent. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by the GNU Affero General Public License
* please contact with iot_support at tid dot es
*/
#include <iostream>
#include <cppunit/TestResult.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/XmlOutputter.h>
#include "mqttTest.h"


int main(int argc, char* argv[]) {

  // Logger
  pion::logger pion_logger(PION_GET_LOGGER("main"));
  PION_LOG_SETLEVEL_DEBUG(pion_logger);
  PION_LOG_CONFIG_BASIC;

  // Url base
  iota::Process& process = iota::Process::initialize("/TestMqtt",5);
  iota::Configurator::initialize("../../tests/iotagent/config_mongo.json");

  // Http Server and Admin Service
  pion::http::plugin_server_ptr http_server = process.add_http_server("", "127.0.0.1:1026");
  iota::AdminService* adm = new iota::AdminService();
  process.set_admin_service(adm);


  // Mqtt Service
  iota::esp::MqttService* mqttService = new iota::esp::MqttService();
  http_server->add_service("/TestMqtt/mqtt", mqttService);
  adm->add_service("/TestMqtt/mqtt", mqttService);

  // Mock
  MockService* mock = new MockService();
  http_server->add_service("/mock", mock);
  adm->add_service("/mock", mock);

  process.start();

  testing::GTEST_FLAG(throw_on_failure) = true;
  testing::InitGoogleMock(&argc, argv);

  CppUnit::TestResult    controller;
  CppUnit::TestResultCollector result;
  controller.addListener(&result);

  CppUnit::TextUi::TestRunner runner;
  runner.addTest(MqttTest::suite());
  runner.run(controller);

  // important stuff happens next
  std::ofstream xmlFileOut("mqttcpptestresults.xml");
  CppUnit::XmlOutputter xmlOut(&result, xmlFileOut);
  xmlOut.write();
  process.shutdown();
  return result.wasSuccessful() ? 0 : 1;
}
