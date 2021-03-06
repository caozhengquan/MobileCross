//
// Created by Rex on 2018/3/17.
//

#ifndef HUAYALOGIN_WEBSOCKET_H
#define HUAYALOGIN_WEBSOCKET_H

#include <string>
#include "bs.h"
#include "libwebsockets.h"
#include "thread.h"

using namespace std;

typedef enum {
    WS_STATUS_CONNECTING,
    WS_STATUS_CONNECTED,
    WS_STATUS_UNCONNECTED
}ws_status_t;

class WebSocket: public LoopThread{
public:
    WebSocket(const char* ca = NULL, const char* cert = NULL, const char* cert_key = NULL);
    ~WebSocket();
    bool connect(const char* host=NULL, int port=0, const char* path=NULL);
    bool exit();

    virtual void opened() = 0;
    virtual void message(const char* msg, uint32_t size) = 0;
    virtual void error() = 0;
    virtual void cloesed() = 0;

    virtual void loop();

    int send(const char* msg, uint32_t size=0);
    bool alive();
    void pingpong();
    inline void setStatus(ws_status_t s){
        m_status = s;
    }

    void create(const char* ca, const char* cert, const char* cert_key);

    static WebSocket*   m_instance;
protected:
    struct lws_context*                 m_context;
    struct lws *                        m_lws;
    struct lws_context_creation_info    m_create_info;
    struct lws_client_connect_info      m_conn_info;

    ws_status_t    m_status;
    string  m_host;
    int     m_port;
    string  m_path;

    int     m_use_ssl;
};


#endif //HUAYALOGIN_WEBSOCKET_H
