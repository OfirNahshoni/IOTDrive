# framework/src/CMakeLists.txt

# shared libraries
add_library(handleton_shared_lib SHARED Handleton.cpp)

# static libraries
add_library(logger_static_lib STATIC Logger.cpp)
add_library(asocket_static_lib STATIC ASocket.cpp)
add_library(reactor_static_lib STATIC Reactor.cpp)
add_library(fw_tptask_static_lib STATIC FWTPTask.cpp)
add_library(scheduler_static_lib STATIC Scheduler.cpp)
add_library(framework_static_lib STATIC Framework.cpp)
add_library(udp_socket_static_lib STATIC UDPSocket.cpp)
add_library(dll_loader_static_lib STATIC DllLoader.cpp)
add_library(thread_pool_static_lib STATIC ThreadPool.cpp)
add_library(dir_monitor_static_lib STATIC DirMonitor.cpp)
add_library(linux_listener_static_lib STATIC LinuxListener.cpp)
add_library(tcp_conn_socket_static_lib STATIC TCPConnSocket.cpp)
add_library(async_injection_static_lib STATIC AsyncInjection.cpp)
add_library(tcp_listener_socket_static_lib STATIC TCPListenerSocket.cpp)

# link libraries
target_link_libraries(asocket_static_lib PRIVATE asocket_lib)
target_link_libraries(logger_static_lib PRIVATE ts_waitable_queue_lib
                                                        handleton_shared_lib)
target_link_libraries(reactor_static_lib PRIVATE linux_listener_static_lib
                                            reactor_lib handleton_shared_lib)
target_link_libraries(fw_tptask_static_lib PRIVATE itp_task_lib itask_args_lib)
target_link_libraries(scheduler_static_lib PRIVATE ischeduler_task_lib)
target_link_libraries(udp_socket_static_lib PRIVATE udp_socket_lib)
target_link_libraries(thread_pool_static_lib PRIVATE ts_waitable_queue_lib
                                                                itp_task_lib)
target_link_libraries(framework_static_lib PRIVATE iinput_proxy_lib
                    icommand_lib dll_loader_static_lib dir_monitor_static_lib
                    reactor_static_lib fw_tptask_static_lib handleton_shared_lib
            thread_pool_static_lib async_injection_static_lib logger_static_lib)
target_link_libraries(dir_monitor_static_lib PRIVATE dispatch_callback_lib
                                                        dll_loader_static_lib)
target_link_libraries(linux_listener_static_lib PRIVATE ilistener_lib)
target_link_libraries(tcp_conn_socket_static_lib PRIVATE asocket_static_lib)
target_link_libraries(async_injection_static_lib PRIVATE scheduler_static_lib
                                                        handleton_shared_lib)
target_link_libraries(tcp_listener_socket_static_lib PRIVATE asocket_static_lib
                            tcp_conn_socket_static_lib tcp_listener_socket_lib)
