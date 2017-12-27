// See README.txt for information and build instructions.
#pragma warning(disable:4146)
#include <ctime>
#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>
#include <google/protobuf/descriptor.h>

#include "proto/addressbook.pb.h"

using namespace std;
using namespace google::protobuf;

using google::protobuf::util::TimeUtil;


int main(int argc, char* argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  string typeName = tutorial::Person::descriptor()->full_name();
  cout << "typename: " << typeName << endl;

  const Descriptor* descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
  cout << "FindMessageTypeByName() = " << descriptor << endl;
  cout << "Person::descriptor() = " << tutorial::Person::descriptor() << endl;
  cout << endl;

  const Message* protoType = MessageFactory::generated_factory()->GetPrototype(descriptor);
  cout << "GetPrototype() = " << protoType << endl;
  cout << "Person::default_instance() = " << &tutorial::Person::default_instance() << endl;
  cout << endl;

  tutorial::Person* obj = (tutorial::Person*)(protoType->New());
  assert(typeid(*obj) == typeid(tutorial::Person::default_instance()));
  cout << "protoType->New() = " << obj << endl;
  delete obj;

  tutorial::Person person;
  person.set_id(123456789);
  person.set_name("zhangkuo");
  person.set_email("vczk@foxmail.com");

  cout << person.DebugString() << endl;
  cout << person.SerializeAsString() << endl;
  cout << person.SerializePartialAsString() << endl;
  
  //cout << person.Serialize

  system("pause");
  return 0;
}
