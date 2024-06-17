# C++单元测试

### 第一步：安装 Boost

### 第二步：配置项目

### 第三步：编写测试用例

```c++
#include <boost/test/included/unit_test.hpp>
#include <boost/bind/bind.hpp>
using namespace boost::unit_test;

class test_class
{
public:
  void test_method1()
  {
    BOOST_TEST( true /* test assertion */ );
  }
  void test_method2()
  {
    BOOST_TEST( false /* test assertion */ );
  }
};

test_suite* init_unit_test_suite( int /*argc*/, char* /*argv*/[] )
{
  boost::shared_ptr<test_class> tester( new test_class );

  framework::master_test_suite().
    add( BOOST_TEST_CASE( boost::bind( &test_class::test_method1, tester )));
  framework::master_test_suite().
    add( BOOST_TEST_CASE( boost::bind( &test_class::test_method2, tester )));
  return 0;
}
//g++ -o my_tests main.cpp -lboost_unit_test_framework
```

### 第四步：编译和运行测试

```
g++ -o my_tests my_tests.cpp -lboost_unit_test_framework
./my_tests
```



