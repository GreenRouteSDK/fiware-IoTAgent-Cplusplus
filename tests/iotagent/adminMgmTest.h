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
#ifndef SRC_TESTS_IOTAGENT_ADMINMGMTEST_H_
#define SRC_TESTS_IOTAGENT_ADMINMGMTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "services/admin_service.h"

class AdminMgmTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(AdminMgmTest);

    CPPUNIT_TEST(testProtocol);
    CPPUNIT_TEST(testServiceManagement);

    CPPUNIT_TEST_SUITE_END();

  public:
    AdminMgmTest();
    virtual ~AdminMgmTest();
    void setUp();
    void tearDown();

    static const std::string HOST;
    static const std::string CONTENT_JSON;

    static const int POST_RESPONSE_CODE;
    //GET ALL empty
    static const std::string GET_EMPTY_RESPONSE_DEVICES;
    static const int GET_RESPONSE_CODE;
    static const int GET_RESPONSE_CODE_NOT_FOUND;

    //PROTOCOL
    static const std::string URI_PROTOCOLS;
    static const std::string POST_PROTOCOLS1;
    static const std::string POST_PROTOCOLS2;
    static const std::string POST_PROTOCOLS3;
    static const std::string POST_PROTOCOLS4;
    static const std::string GET_PROTOCOLS_RESPONSE;

    // SERVICE_MANAGEMENT
    static const std::string URI_SERVICES_MANAGEMET;
    static const std::string POST_SERVICE_MANAGEMENT1;
    static const std::string POST_SERVICE_MANAGEMENT2;
    static const std::string GET_SERVICE_MANAGEMENT_RESPONSE;


    //DEVICE_MANAGEMENT
    static const std::string URI_DEVICES_MANAGEMEMT;
    static const std::string POST_DEVICE_MANAGEMENT1;
    static const std::string GET_DEVICE_MANAGEMENT_RESPONSE;

    int http_test(const std::string& uri,
                  const std::string& method,
                  const std::string& service,
                  const std::string& service_path,
                  const std::string& content_type,
                  const std::string& body,
                  const std::map<std::string,std::string>& headers,
                  const std::string& query_string,
                  std::string& response);

  private:

    void testProtocol();
    void testServiceManagement();

    iota::AdminService* adm;
    pion::http::plugin_server_ptr wserver;
    pion::one_to_one_scheduler scheduler;
};

#endif

