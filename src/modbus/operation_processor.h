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
#ifndef SRC_MODBUS_OPERATION_PROCESSOR_H_
#define SRC_MODBUS_OPERATION_PROCESSOR_H_

// We use boost json processor.

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <map>

namespace iota {
class ModbusOperationProcessor {
  public:
  ModbusOperationProcessor() {};
    ModbusOperationProcessor(std::stringstream& json_operations);
    virtual ~ModbusOperationProcessor() {};
    void read_operations(std::string modbus_operation_file);
    boost::property_tree::ptree& get_operation(std::string operation);
    std::vector<std::string>& get_mapped_labels(std::string operation);
  protected:
  private:
    std::map<std::string, boost::property_tree::ptree> _operations;
    std::map<std::string, std::vector<std::string> > _position_map;
    void read(std::stringstream& json_operations);
};
}

#endif
