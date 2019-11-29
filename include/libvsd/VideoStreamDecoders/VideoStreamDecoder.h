//
// Created by hejia on 18-2-13.
//

#ifndef GOKU_VIDEODETECTTHREAD_H
#define GOKU_VIDEODETECTTHREAD_H

#include <Poco/Thread.h>
#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

#include "libvsd/CommonStruct.h"
#include "libvsd/ErrCode.h"

using FrameCBFunc = void(const ImageFrame &);

class VideoStreamDecoder : public Poco::Runnable, public Poco::RefCountedObject {
 public:
  typedef Poco::AutoPtr<VideoStreamDecoder> Ptr;

  VideoStreamDecoder(const AppConfig &config, Poco::Logger &logger);
  virtual ~VideoStreamDecoder();

  virtual void run() = 0;
  virtual void Start(const std::function<FrameCBFunc> &cb);
  virtual void Exit();
  virtual bool Init() = 0;
  virtual VID_ERR Connect() = 0;

 protected:
  const AppConfig &m_config;
  Poco::Logger &m_logger;
  bool m_stop = false;
  Poco::Thread m_thread;
  bool m_bConnected = false;

  std::function<FrameCBFunc> m_frameCallback;
};

#endif //GOKU_VIDEODETECTTHREAD_H
