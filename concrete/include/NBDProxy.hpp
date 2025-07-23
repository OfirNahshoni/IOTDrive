/**
* @file: NBDProxy.hpp
* @author: Ofir Nahshoni
* @file: This is a file that defines an API of Proxy, that can communicate
* with the NBD Client and Server to get a ATaskArgs for every FD that is
* detected as active by the system. this TaskArgs is sent then to the Framework
* as a ITaskArgs (and the Framework then creates a task and transfer to its
* system.
*/

#ifndef ILRD_RD1645_NBD_PROXY_HPP
#define ILRD_RD1645_NBD_PROXY_HPP

#include <map>                      // std::map
#include <array>
#include <memory>                   // std::shared_ptr
#include <mutex>

#include "ATaskArgs.hpp"
#include "NBDServer.hpp"
#include "IInputProxy.hpp"
#include "TCPConnSocket.hpp"
#include "DispatchCallback.hpp"

namespace ilrd
{

class NBDProxy : public IInputProxy
{
public:
    friend class Handleton;
    ~NBDProxy() = default;
    void Init(NBDServer& nbd);
    int GetSocketFD() const;
    std::shared_ptr<ITaskArgs> GetTaskArgs(int fd, Mode mode);
    void RespondToReadNBD(const UID& uid, bool status, size_t length,
                                                std::shared_ptr<char[]> buffer);
    void RespondToWriteNBD(const UID& uid, bool status);
    void RegisterForNewTaskArgs(ACallback<std::shared_ptr<ATaskArgs>>* callback);
    
private:
    std::mutex m_mutex;
    std::optional<TCPConnSocket> m_tcpSocket;
    std::map<UID, std::array<char, 8>> m_map;
    Dispatcher<std::shared_ptr<ATaskArgs>> m_dispatcherNewTaskArgs;

    NBDProxy();
};  // class NBDProxy

}   // namespace ilrd

#endif  // ILRD_RD1645_NBD_PROXY_HPP