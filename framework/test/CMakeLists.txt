# framework/test/CMakeLists.txt

project(Framework)
include_directories(ShapesForFactory plugins_src)

# libraries for test_factory
add_library(shape_static_lib STATIC ShapesForFactory/Shape.cpp)
add_library(line_static_lib STATIC ShapesForFactory/Line.cpp)
add_library(rectangle_static_lib STATIC ShapesForFactory/Rectangle.cpp)
add_library(square_static_lib STATIC ShapesForFactory/Square.cpp)
add_library(circle_static_lib STATIC ShapesForFactory/Circle.cpp)
# libraries for test_handleton
add_library(ht1_shared_lib SHARED plugins_src/ht1.cpp)
add_library(ht2_shared_lib SHARED plugins_src/ht2.cpp)

# executables
add_executable(test_async_injection TestAsyncInjection.cpp)
add_executable(test_dir_monitor TestDirMonitor.cpp)
add_executable(test_dispatch_callback TestDispatchCallback.cpp)
add_executable(test_factory TestFactory.cpp)
add_executable(test_framework TestFramework.cpp)
add_executable(test_handleton TestHandleton.cpp)
add_executable(test_logger TestLogger.cpp)
add_executable(test_reactor TestReactor.cpp)
add_executable(test_scheduler TestScheduler.cpp)
add_executable(test_thread_pool TestThreadPool.cpp)
add_executable(test_waitable_queue TestWaitableQueue.cpp)

# link libraries to executables
target_link_libraries(test_async_injection PRIVATE async_injection_static_lib)
target_link_libraries(test_dir_monitor PRIVATE dir_monitor_static_lib)
target_link_libraries(test_dispatch_callback PRIVATE dispatch_callback_lib)
target_link_libraries(test_factory PRIVATE factory_lib shape_static_lib
                        line_static_lib rectangle_static_lib square_static_lib
                                        circle_static_lib handleton_shared_lib)
target_link_libraries(test_framework PRIVATE framework_static_lib)
target_link_libraries(test_handleton PRIVATE ht1_shared_lib ht2_shared_lib
                                                        handleton_shared_lib)
target_link_libraries(test_logger PRIVATE logger_static_lib)
target_link_libraries(test_reactor PRIVATE reactor_static_lib asocket_static_lib
                                udp_socket_static_lib tcp_conn_socket_static_lib
                                                tcp_listener_socket_static_lib)
target_link_libraries(test_scheduler PRIVATE scheduler_static_lib)
target_link_libraries(test_thread_pool PRIVATE thread_pool_static_lib)
target_link_libraries(test_waitable_queue PRIVATE ts_waitable_queue_lib)
